#include "../SourceSDK/SDK.hpp"

#define IS_IN_RANGE( Value, Max, Min ) ( Value >= Max && Value <= Min )
#define GET_BITS( Value ) ( IS_IN_RANGE( Value, '0', '9' ) ? ( Value - '0' ) : ( ( Value & ( ~0x20 ) ) - 'A' + 0xA ) )
#define GET_BYTE( Value ) ( GET_BITS( Value[ 0 ] ) << 4 | GET_BITS( Value[ 1 ] ) )

std::uintptr_t CMemory::Scan( const std::string& strImageName, const std::string& strSignature )
{
	auto hImage = GetModuleHandleA( strImageName.c_str( ) );

	if ( !hImage )
	{
		Win32Print.Error( "GetModuleHandleA failed ( Horizon::Memory::%s )", __FUNCTION__ );
		return 0u;
	}

	auto uImageBase = ( std::uintptr_t )( hImage );
	auto pImageDosHdr = ( IMAGE_DOS_HEADER* )( uImageBase );

	if ( pImageDosHdr->e_magic != IMAGE_DOS_SIGNATURE )
	{
		Win32Print.Error( "IMAGE_DOS_HEADER::e_magic is invalid ( Horizon::Memory::%s )", __FUNCTION__ );
		return 0u;
	}

	auto pImageNtHdrs = ( IMAGE_NT_HEADERS* )( uImageBase + pImageDosHdr->e_lfanew );

	if ( pImageNtHdrs->Signature != IMAGE_NT_SIGNATURE )
	{
		Win32Print.Error( "IMAGE_NT_HEADERS::Signature is invalid ( Horizon::Memory::%s )", __FUNCTION__ );
		return 0u;
	}

	auto pScanBegin = ( std::uint8_t* )( uImageBase );
	auto pScanEnd = ( std::uint8_t* )( uImageBase + pImageNtHdrs->OptionalHeader.SizeOfImage );

	std::uint8_t* pScanResult = nullptr;
	std::uint8_t* pScanData = ( std::uint8_t* )( strSignature.c_str( ) );

	for ( auto pCurrent = pScanBegin; pCurrent < pScanEnd; pCurrent++ )
	{
		if ( *( std::uint8_t* )pScanData == '\?' || *pCurrent == GET_BYTE( pScanData ) )
		{
			if ( !pScanResult )
				pScanResult = pCurrent;

			if ( !pScanData[ 2 ] )
				return ( std::uintptr_t )( pScanResult );

			pScanData += ( *( std::uint16_t* )pScanData == '\?\?' || *( std::uint8_t* )pScanData != '\?' ) ? 3 : 2;

			if ( !*pScanData )
				return ( std::uintptr_t )( pScanResult );
		}
		else if ( pScanResult )
		{
			pCurrent = pScanResult;
			pScanData = ( std::uint8_t* )( strSignature.c_str( ) );
			pScanResult = nullptr;
		}
	}

	Win32Print.Warning( "Signature '%s' in module '%s' not found ( Horizon::Memory::%s )", strSignature.c_str( ), strImageName.c_str( ), __FUNCTION__ );

	return 0u;
}