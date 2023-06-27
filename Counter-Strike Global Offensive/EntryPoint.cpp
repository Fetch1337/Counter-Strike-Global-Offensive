#include "Core/Source.hpp"
#include "Utilities/InputManager.hpp"

void Entry( HMODULE hModule )
{
	if ( Source->Create( ) )
	{
		while ( !InputManager->IsBindActive( CKeyBinds( VK_END, ( int )EKeyMode::TOGGLE ) ) )
			std::this_thread::sleep_for( 500ms );

		Source->Destroy( );

		std::this_thread::sleep_for( 1000ms );
	}

	FreeLibraryAndExitThread( hModule, EXIT_SUCCESS );
}

BOOL APIENTRY DllMain( HMODULE hModule, DWORD dwReason, LPVOID lpReserved )
{
	if( dwReason == DLL_PROCESS_ATTACH )
	{
		DisableThreadLibraryCalls( hModule );
		CreateThread( nullptr, 0u, ( LPTHREAD_START_ROUTINE )Entry, hModule, 0u, nullptr );
	}

	return TRUE;
}