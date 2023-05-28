#include "../Hooks.hpp"
#include "../../Source.hpp"
#include "../../../SourceSDK/Objects/Player.hpp"
#include "../../../SourceSDK/Objects/Weapon.hpp"
#include "../../../Features/AntiAim/AntiAim.hpp"
#include "../../../Features/Misc/Movement.hpp"
#include "../../../Features/Misc/EnginePrediction.hpp"
#include "../../Includes/Global.hpp"

void FASTCALL CHooked::FrameStageNotify( void* pEcx, void* pEdx, EClientFrameStage Stage )
{
	static auto oFrameStageNotify = DTR::FrameStageNotify.GetOriginal<decltype( &FrameStageNotify )>( );

	switch ( Stage )
	{
	case FRAME_NET_UPDATE_POSTDATAUPDATE_START:
	{
		/*
		 * data has been received and we are going to start calling postdataupdate
		 * e.g. resolver or skinchanger and other visuals
		 */

		break;
	}
	case FRAME_NET_UPDATE_POSTDATAUPDATE_END:
	{
		/*
		 * data has been received and called postdataupdate on all data recipients
		 * e.g. now we can modify interpolation, other lagcompensation stuff
		 */

		break;
	}
	case FRAME_NET_UPDATE_END:
	{
		/*
		 * received all packets, now do interpolation, prediction, etc
		 * e.g. backtrack stuff
		 */

		break;
	}
	case FRAME_RENDER_START:
	{
		/*
		 * start rendering the scene
		 * e.g. remove visual punch, thirdperson, other render/update stuff
		 */

		if ( Source.Interfaces.m_pInput->m_bCameraInThirdPerson )
		{
			if ( Globals.m_pLocal && Globals.m_pLocal->IsAlive( ) )
				*Globals.m_pLocal->RenderAngles( ) = Globals.m_pCmd->m_angViewAngles;
		}

		break;
	}
	case FRAME_RENDER_END:
	{
		/*
		 * finished rendering the scene
		 * here we can restore our modified things
		 */

		break;
	}
	default:
		break;
	}

	oFrameStageNotify( pEcx, pEdx, Stage );
}

void FASTCALL CHooked::CreateMove( void* pEcx, void* pEdx, int iSequenceNumber, float flInputSampleFrametime, bool bActive, bool& bSendPacket )
{
	static auto oCreateMove = DTR::CreateMoveProxy.GetOriginal<decltype( &CreateMoveProxy )>( );
	oCreateMove( pEcx, pEdx, iSequenceNumber, flInputSampleFrametime, bActive );

	auto pCmd = Source.Interfaces.m_pInput->GetUserCmd( iSequenceNumber );
	auto pVerifiedCmd = Source.Interfaces.m_pInput->GetVerifiedUserCmd( iSequenceNumber );

	if ( !pCmd || !pVerifiedCmd || !bActive )
		return;

	auto pLocal = CCSPlayer::GetLocalPlayer( );

	Globals.m_pCmd = pCmd;
	Globals.m_pLocal = pLocal;

	if ( pLocal && pLocal->IsAlive( ) )
	{
		auto WishAngle = pCmd->m_angViewAngles;

		EnginePrediction.Begin( pCmd );
		{
			AntiAim.Instance( pLocal, pCmd );
			Movement.Instance( pLocal, pCmd );
		}
		EnginePrediction.End( );

		Movement.Rotate( pLocal, pCmd, WishAngle );
	}

	pVerifiedCmd->m_Cmd = *pCmd;
	pVerifiedCmd->m_Crc = pCmd->GetChecksum( );
}

__declspec( naked ) void FASTCALL CHooked::CreateMoveProxy( void* pEcx, void* pEdx, int iSequenceNumber, float flInputSampleFrametime, bool bActive )
{
	__asm
	{
		push	ebp;
		mov		ebp, esp;
		push	ebx;
		push	esp;
		push	dword ptr[ bActive ];
		push	dword ptr[ flInputSampleFrametime ];
		push	dword ptr[ iSequenceNumber ];
		call	CreateMove;
		pop		ebx;
		pop		ebp;
		retn	0Ch;
	}
}