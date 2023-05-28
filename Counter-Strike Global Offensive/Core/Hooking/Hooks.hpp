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
	inline CDetourHook AllocKeyValuesMemory;
	inline CDetourHook CreateMoveProxy;
	inline CDetourHook WriteUsercmdDeltaToBuffer;
	inline CDetourHook FrameStageNotify;
	inline CDetourHook OverrideView;
	inline CDetourHook OverrideMouseInput;
	inline CDetourHook SendNetMsg;
	inline CDetourHook SendDatagram;
	inline CDetourHook GetViewModelFOV;
	inline CDetourHook DoPostScreenEffects;
	inline CDetourHook IsConnected;
	inline CDetourHook IsPaused;
	inline CDetourHook IsHLTV;
	inline CDetourHook PacketStart;
	inline CDetourHook PacketEnd;
	inline CDetourHook RenderSmokeOverlay;
	inline CDetourHook GetScreenSizeAspectRatio;
	inline CDetourHook ListLeavesInBox;
	inline CDetourHook PaintTraverse;
	inline CDetourHook DrawModel;
	inline CDetourHook RunCommand;
	inline CDetourHook SendMessageGC;
	inline CDetourHook RetrieveMessage;
	inline CDetourHook LockCursor;
	inline CDetourHook PlaySoundSurface;
	inline CDetourHook ModifyEyePosition;
	inline CDetourHook SetupAliveLoop;
	inline CDetourHook PhysicsSimulate;
	inline CDetourHook CalcView;
	inline CDetourHook SetupBones;
	inline CDetourHook UpdateClientsideAnimations;
	inline CDetourHook ShouldSkipAnimFrame;
	inline CDetourHook DoExtraBonesProcessing;
	inline CDetourHook BuildTransformations;
	inline CDetourHook StandardBlendingRules;
	inline CDetourHook SvCheatsGetBool;
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
	static long D3DAPI	 Reset( IDirect3DDevice9* pDevice, D3DPRESENT_PARAMETERS* pPresentationParameters );
	static long D3DAPI	 Present( IDirect3DDevice9* pDevice, RECT* pRect, RECT* pDestRect, HWND DestHwndOverride, RGNDATA* pDirtyRegion );
	static long	STDCALL  WndProc( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam );
};

inline CHooked Hooked;