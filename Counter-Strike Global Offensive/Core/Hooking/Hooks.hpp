#pragma once

#include "../../Utilities/Hook.hpp"
#include "../../SourceSDK/SDK.hpp"

#define FASTCALL __fastcall
#define STDCALL __stdcall
#define VECTORCALL __vectorcall

namespace DTR
{
	inline CDetourHook Reset;
	inline CDetourHook Present;
	inline CDetourHook CreateMoveProxy;
	inline CDetourHook FrameStageNotify;
	inline CDetourHook OverrideView;
	inline CDetourHook RunCommand;
	inline CDetourHook PaintTraverse;
	inline CDetourHook LockCursor;
}

class CHooked
{
public:
	static void FASTCALL CreateMove( void* pEcx, void* pEdx, int iSequenceNumber, float flInputSampleFrametime, bool bActive, bool& bSendPacket );
	static void FASTCALL CreateMoveProxy( void* pEcx, void* pEdx, int iSequenceNumber, float flInputSampleFrametime, bool bActive );
	static void FASTCALL FrameStageNotify( void* pEcx, void* pEdx, EClientFrameStage Stage );
	static void FASTCALL RunCommand( void* pEcx, void* pEdx, CBasePlayer* pPlayer, CUserCmd* pCmd, IMoveHelper* pMoveHelper );
	static void FASTCALL PaintTraverse( void* pEcx, void* pEdx, unsigned int vguiPanel, bool bForceRepaint, bool bAllowForce );
	static void FASTCALL LockCursor( void* pEcx, void* pEdx );
	static void FASTCALL OverrideView( void* pEcx, void* pEdx, CViewSetup* pSetupView );
	static long D3DAPI	 Reset( IDirect3DDevice9* pDevice, D3DPRESENT_PARAMETERS* pPresentationParameters );
	static long D3DAPI	 Present( IDirect3DDevice9* pDevice, RECT* pRect, RECT* pDestRect, HWND DestHwndOverride, RGNDATA* pDirtyRegion );
	static long	STDCALL  WndProc( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam );
};

inline const std::unique_ptr< CHooked > Hooked{ new CHooked( ) };