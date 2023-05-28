#include "InputManager.hpp"
#include "../Core/Source.hpp"
#include "../Core/Hooking/Hooks.hpp"
#include "../Core/Includes/Global.hpp"

bool CInputManager::Create( )
{
	D3DDEVICE_CREATION_PARAMETERS CreationParameters = { };
	while ( FAILED( Source.Interfaces.m_pDirectDevice->GetCreationParameters( &CreationParameters ) ) )
		std::this_thread::sleep_for( 200ms );

	m_hWindow = CreationParameters.hFocusWindow;
	if ( !m_hWindow )
		return false;

	m_pOldWndProc = reinterpret_cast< WNDPROC >( SetWindowLongPtrW( m_hWindow, GWLP_WNDPROC, reinterpret_cast< LONG_PTR >( Hooked.WndProc ) ) );
	if ( !m_pOldWndProc )
		return false;

	return true;
}

void CInputManager::Destroy( )
{
	if ( m_pOldWndProc )
	{
		SetWindowLongPtrW( m_hWindow, GWLP_WNDPROC, reinterpret_cast< LONG_PTR >( m_pOldWndProc ) );
		m_pOldWndProc = nullptr;
	}

	Source.Interfaces.m_pInputSystem->EnableInput( true );
}

bool CInputManager::Process( UINT uMsg, WPARAM wParam, LPARAM lParam )
{
	bool bIsHandlePossible = true;

	if ( Source.Interfaces.m_pEngine->IsConnected( ) && Source.Interfaces.m_pEngine->IsInGame( ) )
	{
		if ( Source.Interfaces.m_pEngine->IsConsoleVisible( ) )
		{
			bIsHandlePossible = false;
			if ( uMsg == WM_LBUTTONDOWN || uMsg == WM_LBUTTONUP || uMsg == WM_RBUTTONDOWN || uMsg == WM_RBUTTONUP || uMsg == WM_XBUTTONDOWN || uMsg == WM_XBUTTONUP || uMsg == WM_MBUTTONDOWN || uMsg == WM_MBUTTONUP )
				bIsHandlePossible = true;

			if ( uMsg == WM_KEYDOWN || uMsg == WM_KEYUP )
				if ( wParam == VK_INSERT )
					bIsHandlePossible = true;
		}
	}

	if ( bIsHandlePossible )
	{
		switch ( uMsg )
		{
		case WM_LBUTTONDOWN:
			m_arrKeys[ ( int )EKeyMode::TOGGLE ][ VK_LBUTTON ] = !m_arrKeys[ ( int )EKeyMode::TOGGLE ][ VK_LBUTTON ];
			m_arrKeys[ ( int )EKeyMode::HOLD ][ VK_LBUTTON ] = true;
			break;
		case WM_LBUTTONUP:
			m_arrKeys[ ( int )EKeyMode::HOLD ][ VK_LBUTTON ] = false;
			break;
		case WM_XBUTTONDOWN:
			if ( GET_XBUTTON_WPARAM( wParam ) == XBUTTON1 )
			{
				m_arrKeys[ ( int )EKeyMode::HOLD ][ VK_XBUTTON1 ] = true;
				m_arrKeys[ ( int )EKeyMode::TOGGLE ][ VK_XBUTTON1 ] = !m_arrKeys[ ( int )EKeyMode::TOGGLE ][ VK_XBUTTON1 ];
			}

			if ( GET_XBUTTON_WPARAM( wParam ) == XBUTTON2 )
			{
				m_arrKeys[ ( int )EKeyMode::HOLD ][ VK_XBUTTON2 ] = true;
				m_arrKeys[ ( int )EKeyMode::TOGGLE ][ VK_XBUTTON2 ] = !m_arrKeys[ ( int )EKeyMode::TOGGLE ][ VK_XBUTTON2 ];
			}
			break;
		case WM_XBUTTONUP:
			if ( GET_XBUTTON_WPARAM( wParam ) == XBUTTON1 )
				m_arrKeys[ ( int )EKeyMode::HOLD ][ VK_XBUTTON1 ] = false;

			if ( GET_XBUTTON_WPARAM( wParam ) == XBUTTON2 )
				m_arrKeys[ ( int )EKeyMode::HOLD ][ VK_XBUTTON2 ] = false;
			break;
		case WM_MBUTTONDOWN:
			m_arrKeys[ ( int )EKeyMode::HOLD ][ VK_MBUTTON ] = true;
			m_arrKeys[ ( int )EKeyMode::TOGGLE ][ VK_MBUTTON ] = !m_arrKeys[ ( int )EKeyMode::TOGGLE ][ VK_MBUTTON ];
			break;
		case WM_MBUTTONUP:
			m_arrKeys[ ( int )EKeyMode::HOLD ][ VK_MBUTTON ] = false;
			break;
		case WM_RBUTTONDOWN:
			m_arrKeys[ ( int )EKeyMode::TOGGLE ][ VK_RBUTTON ] = !m_arrKeys[ ( int )EKeyMode::TOGGLE ][ VK_RBUTTON ];
			m_arrKeys[ ( int )EKeyMode::HOLD ][ VK_RBUTTON ] = true;
			break;
		case WM_RBUTTONUP:
			m_arrKeys[ ( int )EKeyMode::HOLD ][ VK_RBUTTON ] = false;
			break;
		case WM_KEYDOWN:
		case WM_SYSKEYDOWN:
			m_arrKeys[ ( int )EKeyMode::TOGGLE ][ wParam ] = !m_arrKeys[ ( int )EKeyMode::TOGGLE ][ wParam ];
			m_arrKeys[ ( int )EKeyMode::HOLD ][ wParam ] = true;
			break;
		case WM_KEYUP:
		case WM_SYSKEYUP:
			m_arrKeys[ ( int )EKeyMode::HOLD ][ wParam ] = false;
			break;
		default: break;
		}
	}

	if ( !Globals.m_pLocal )
	{
		for ( int iKey = 0; iKey < 256; iKey++ )
		{
			if ( iKey == VK_INSERT || iKey == VK_END )
				continue;

			m_arrKeys[ ( int )EKeyMode::TOGGLE ][ iKey ] = false;
			m_arrKeys[ ( int )EKeyMode::HOLD ][ iKey ] = false;
		}
	}

	return true;
}

bool CInputManager::IsBindActive( CKeyBinds KeyBind )
{
	switch ( KeyBind.m_iModeSelected )
	{
	case ( int )EKeyMode::TOGGLE:
		return m_arrKeys[ ( int )EKeyMode::TOGGLE ][ KeyBind.m_iKeySelected ];
	case ( int )EKeyMode::HOLD:
		return m_arrKeys[ ( int )EKeyMode::HOLD ][ KeyBind.m_iKeySelected ];
	case ( int )EKeyMode::ALWAYS:
		return true;
	}

	return false;
}