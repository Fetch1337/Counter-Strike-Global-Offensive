#include "Variables.hpp"
#include "../Source.hpp"
#include <fstream>

bool CVariables::Save( )
{
	CreateDirectoryA( "C:\\Cheat", NULL );

	Source.Interfaces.m_pConVar->ConsolePrintf( "Successfully saved config.\n", 0 );

	std::string strFilePath = "C:\\Cheat\\" + std::to_string( Parametrs.m_iCurrentConfig + 1 ) + ".bin";

	std::fstream File( strFilePath, std::ios::out | std::ios::in | std::ios::trunc );
	File.close( );

	File.open( strFilePath, std::ios::out | std::ios::in );
	if ( !File.is_open( ) )
	{
		File.close( );
		return false;
	}

	const size_t SettingsSize = sizeof( Parametrs_t );
	for ( int i = 0; i < SettingsSize; i++ )
	{
		byte CurrentByte = *reinterpret_cast< byte* >( uintptr_t( &Parametrs ) + i );
		for ( int x = 0; x < 8; x++ )
			File << ( int ) ( ( CurrentByte >> x ) & 1 );
	}

	File.close( );

	return true;
}

bool CVariables::Load( )
{
	CreateDirectoryA( "C:\\Cheat", NULL );

	Source.Interfaces.m_pConVar->ConsolePrintf( "Successfully saved config.\n", 0 );

	std::string strFilePath = "C:\\Cheat\\" + std::to_string( Parametrs.m_iCurrentConfig + 1 ) + ".bin";

	std::fstream File;
	File.open( strFilePath, std::ios::out | std::ios::in );
	if ( !File.is_open( ) )
	{
		File.close( );
		return false;
	}

	std::string strLine;
	while ( File )
	{
		std::getline( File, strLine );

		const size_t SettingsSize = sizeof( Parametrs_t );
		if ( strLine.size( ) > ( SettingsSize * 8 ) )
		{
			File.close( );
			return false;
		}
		for ( int i = 0; i < SettingsSize; i++ )
		{
			byte CurrentByte = *reinterpret_cast< byte* >( uintptr_t( &Parametrs ) + i );
			for ( size_t x = 0; x < 8; x++ )
			{
				if ( strLine.size( ) < ( i * 8 ) + x || strLine[ ( i * 8 ) + x ] == '1' )
					CurrentByte |= 1 << x;
				else
					CurrentByte &= ~( 1 << x );
			}
			*reinterpret_cast< byte* >( uintptr_t( &Parametrs ) + i ) = CurrentByte;
		}
	}

	File.close( );

	return true;
}