#pragma once

class CMemory
{
public:
	inline std::uintptr_t GetAbsoluteAddress( const std::uintptr_t uRelativeAddress )
	{
		return uRelativeAddress + 0x4 + *reinterpret_cast< std::int32_t* >( uRelativeAddress );
	}

	template <typename T = void*>
	constexpr T GetVFunc( void* thisptr, std::size_t nIndex )
	{
		return ( *static_cast< T** >( thisptr ) )[ nIndex ];
	}

	std::uintptr_t Scan( const std::string& strImageName, const std::string& strSignature );
};

inline const std::unique_ptr< CMemory > Memory{ new CMemory( ) };