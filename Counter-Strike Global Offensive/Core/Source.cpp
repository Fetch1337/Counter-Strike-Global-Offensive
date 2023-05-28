#include "Source.hpp"
#include "../Utilities/PropManager.hpp"
#include "../Utilities/Render.hpp"
#include "../Utilities/InputManager.hpp"
#include "../SourceSDK/Objects/Entity.hpp"
#include "../SourceSDK/Objects/Player.hpp"
#include "../SourceSDK/Objects/Weapon.hpp"
#include "Hooking/Hooks.hpp"

bool CSource::Create( )
{
#pragma region patterns
	Patterns.m_uMoveHelper = Memory.Scan( "client.dll", "8B 0D ?? ?? ?? ?? 8B 45 ?? 51 8B D4 89 02 8B 01" ) + 0x2;
	Patterns.m_uInput = Memory.Scan( "client.dll", "B9 ?? ?? ?? ?? F3 0F 11 04 24 FF 50 10" ) + 0x1;
	Patterns.m_uPredictionRandomSeed = Memory.Scan( "client.dll", "8B 0D ?? ?? ?? ?? BA ?? ?? ?? ?? E8 ?? ?? ?? ?? 83 C4 04" ) + 0x2;
	Patterns.m_uPredictionPlayer = Memory.Scan( "client.dll", "89 ?? ?? ?? ?? ?? F3 0F 10 48 20" ) + 0x2 ;
	Patterns.m_uDirectDevice = Memory.Scan( "shaderapidx9.dll", "A1 ? ? ? ? 50 8B 08 FF 51 0C" ) + 0x1;
#pragma endregion

#pragma region functions
	auto hImageVstdlib = GetModuleHandleA( "vstdlib.dll" );

	Functions.m_uRandomSeed = ( std::uintptr_t )( GetProcAddress( hImageVstdlib, "RandomSeed" ) );
	Functions.m_uRandomFloat = ( std::uintptr_t )( GetProcAddress( hImageVstdlib, "RandomFloat" ) );
	Functions.m_uRandomInt = ( std::uintptr_t )( GetProcAddress( hImageVstdlib, "RandomInt" ) );
#pragma endregion

#pragma region interfaces
	Interfaces.m_pClient = ( IBaseClientDLL* )CreateInterface( "client.dll", "VClient" );
	if ( !Interfaces.m_pClient )
	{
		Win32Print.Error( "IBaseClientDLL is nullptr ( Source::%s )", __FUNCTION__ );
		return false;
	}

	Interfaces.m_pEngine = ( IVEngineClient* )CreateInterface( "engine.dll", "VEngineClient" );
	if ( !Interfaces.m_pEngine )
	{
		Win32Print.Error( "IVEngineClient is nullptr ( Source::%s )", __FUNCTION__ );
		return false;
	}

	Interfaces.m_pEntList = ( IClientEntityList* )CreateInterface( "client.dll", "VClientEntityList" );
	if ( !Interfaces.m_pEntList )
	{
		Win32Print.Error( "IClientEntityList is nullptr ( Source::%s )", __FUNCTION__ );
		return false;
	}

	Interfaces.m_pGameMovement = ( IGameMovement* )CreateInterface( "client.dll", "GameMovement" );
	if ( !Interfaces.m_pGameMovement )
	{
		Win32Print.Error( "IGameMovement is nullptr ( Source::%s )", __FUNCTION__ );
		return false;
	}

	Interfaces.m_pPrediction = ( IPrediction* )CreateInterface( "client.dll", "VClientPrediction" );
	if ( !Interfaces.m_pPrediction )
	{
		Win32Print.Error( "IPrediction is nullptr ( Source::%s )", __FUNCTION__ );
		return false;
	}

	Interfaces.m_pConVar = ( IConVar* )CreateInterface( "vstdlib.dll", "VEngineCvar" );
	if ( !Interfaces.m_pConVar )
	{
		Win32Print.Error( "IConVar is nullptr ( Source::%s )", __FUNCTION__ );
		return false;
	}

	Interfaces.m_pSurface = ( ISurface* )CreateInterface( "vguimatsurface.dll", "VGUI_Surface" );
	if ( !Interfaces.m_pSurface )
	{
		Win32Print.Error( "ISurface is nullptr ( Source::%s )", __FUNCTION__ );
		return false;
	}

	Interfaces.m_pPanel = ( IPanel* )CreateInterface( "vgui2.dll", "VGUI_Panel" );
	if ( !Interfaces.m_pPanel )
	{
		Win32Print.Error( "IPanel is nullptr ( Source::%s )", __FUNCTION__ );
		return false;
	}

	Interfaces.m_pInputSystem = ( IInputSystem* )CreateInterface( "inputsystem.dll", "InputSystemVersion" );
	if ( !Interfaces.m_pInputSystem )
	{
		Win32Print.Error( "IInputSystem is nullptr ( Source::%s )", __FUNCTION__ );
		return false;
	}

	Interfaces.m_pMoveHelper = **( IMoveHelper*** )( Patterns.m_uMoveHelper );
	if ( !Interfaces.m_pMoveHelper )
	{
		Win32Print.Error( "IMoveHelper is nullptr ( Source::%s )", __FUNCTION__ );
		return false;
	}

	Interfaces.m_pInput = *( IInput** )( Patterns.m_uInput );
	if ( !Interfaces.m_pInput )
	{
		Win32Print.Error( "IInput is nullptr ( Source::%s )", __FUNCTION__ );
		return false;
	}

	Interfaces.m_pDirectDevice = **( IDirect3DDevice9*** )( Patterns.m_uDirectDevice );
	if ( !Interfaces.m_pDirectDevice )
	{
		Win32Print.Error( "IDirect3DDevice9 is nullptr ( Source::%s )", __FUNCTION__ );
		return false;
	}

	Interfaces.m_pGlobalVars = **( CGlobalVars*** )( ( *( DWORD** ) Interfaces.m_pClient )[ 0 ] + 0x1F );
	if ( !Interfaces.m_pGlobalVars )
	{
		Win32Print.Error( "CGlobalVars is nullptr ( Source::%s )", __FUNCTION__ );
		return false;
	}
#pragma endregion

#pragma region managers
	if ( !PropManager.Create( ) )
	{
		Win32Print.Error( "PropManager.Create failed ( Source::%s )", __FUNCTION__ );
		return false;
	}

	if ( !InputManager.Create( ) )
	{
		Win32Print.Error( "InputManager.Create failed ( Source::%s )", __FUNCTION__ );
		return false;
	}
#pragma endregion

#pragma region hooks
	if ( MH_Initialize( ) == MH_OK )
	{
		if ( !DTR::Reset.Create( Memory.GetVFunc( Interfaces.m_pDirectDevice, 16 ), &Hooked.Reset ) )
			return false;

		if ( !DTR::Present.Create( Memory.GetVFunc( Interfaces.m_pDirectDevice, 17 ), &Hooked.Present ) )
			return false;

		if ( !DTR::CreateMoveProxy.Create( Memory.GetVFunc( Interfaces.m_pClient, 22 ), &Hooked.CreateMoveProxy ) )
			return false;

		if ( !DTR::FrameStageNotify.Create( Memory.GetVFunc( Interfaces.m_pClient, 37 ), &Hooked.FrameStageNotify ) )
			return false;

		if ( !DTR::RunCommand.Create( Memory.GetVFunc( Interfaces.m_pPrediction, 19 ), &Hooked.RunCommand ) )
			return false;

		if ( !DTR::PaintTraverse.Create( Memory.GetVFunc( Interfaces.m_pPanel, 41 ), &Hooked.PaintTraverse ) )
			return false;

		if ( !DTR::LockCursor.Create( Memory.GetVFunc( Interfaces.m_pSurface, 67 ), &Hooked.LockCursor ) )
			return false;

		return true;
	}
#pragma endregion

	return false;
}

void CSource::Destroy( )
{
	Render.Destroy( );
	InputManager.Destroy( );

#pragma region hooks
	MH_DisableHook( MH_ALL_HOOKS );
	MH_RemoveHook( MH_ALL_HOOKS );

	MH_Uninitialize( );
#pragma endregion
}

void* CSource::CreateInterface( const std::string& strImageName, const std::string& strName )
{
	auto hImage = GetModuleHandleA( strImageName.c_str( ) );

	if ( !hImage )
		return nullptr;

	auto Fn = ( CreateInterfaceFn )( GetProcAddress( hImage, "CreateInterface" ) );

	if ( !Fn )
		return nullptr;

	char szFormat[ 1024 ] = { };

	for ( auto i = 0u; i < 1000u; i++ )
	{
		sprintf_s( szFormat, "%s%03u", strName.c_str( ), i );

		auto pFactory = Fn( szFormat, nullptr );

		if ( pFactory )
			return pFactory;
	}

	return nullptr;
}