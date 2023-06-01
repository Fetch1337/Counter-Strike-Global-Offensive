#pragma once

#include "../SourceSDK/SDK.hpp"

enum class EKeyState : int
{
	NONE,
	DOWN,
	UP,
	RELEASED
};

enum class EKeyMode : int
{
	TOGGLE,
	HOLD,
	ALWAYS
};

class CKeyBinds
{
public:
	CKeyBinds( int iKey = NULL, int iMode = ( int )EKeyMode::TOGGLE ) :
		m_iKeySelected( iKey ), m_iModeSelected( iMode ) { }

	int m_iKeySelected = NULL;
	int m_iModeSelected = ( int )EKeyMode::TOGGLE;
};

class CInputManager
{
public:
	bool Create( );
	void Destroy( );
	bool Process( UINT uMsg, WPARAM wParam, LPARAM lParam );
	bool IsBindActive( CKeyBinds KeyBind );

	HWND	m_hWindow = nullptr;
	WNDPROC m_pOldWndProc = nullptr;

private:
	std::array<std::array< bool, 256 >, 2> m_arrKeys = { };
};

inline CInputManager InputManager;