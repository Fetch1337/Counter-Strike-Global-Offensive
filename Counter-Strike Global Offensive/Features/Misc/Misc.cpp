#include "Misc.hpp"
#include "EnginePrediction.hpp"
#include "../../Core/Source.hpp"
#include "../../Core/Variables/Variables.hpp"
#include "../../Core/Includes/Global.hpp"

void CMisc::Instance( CBasePlayer* pLocal, CUserCmd* pCmd, bool& bSendPacket )
{
	BunnyHop( pLocal, pCmd );
    FakeLag( pLocal, pCmd, bSendPacket );
}

void CMisc::BunnyHop( CBasePlayer* pLocal, CUserCmd* pCmd )
{
    if ( !Variables->Parametrs.Misc.m_bBunnyHop )
        return;

	if ( !( EnginePrediction->GetFlags( ) & FL_ONGROUND ) )
		pCmd->m_iButtons &= ~IN_JUMP;
}

void CMisc::Rotate( CBasePlayer* pLocal, CUserCmd* pCmd, QAngle& angWish )
{
    if ( pLocal->GetMoveType( ) == MOVETYPE_NOCLIP || pLocal->GetMoveType( ) == MOVETYPE_LADDER )
        return;

    Vector vecRight;
    Vector vecForward = pCmd->m_angViewAngles.ToVectors( &vecRight );

    if ( vecForward.z )
    {
        vecForward.z = 0.f;
        vecForward.Normalize( );
    }

    if ( vecRight.z )
    {
        vecRight.z = 0.f;
        vecRight.Normalize( );
    }

    if ( const auto div = vecRight.y * vecForward.x - vecRight.x * vecForward.y )
    {
        Vector vecWishRight;
        Vector vecWishForward = angWish.ToVectors( &vecWishRight );

        if ( vecWishForward.z )
        {
            vecWishForward.z = 0.f;
            vecWishForward.Normalize( );
        }

        if ( vecWishRight.z )
        {
            vecWishRight.z = 0.f;
            vecWishRight.Normalize( );
        }

        const Vector2D vecWishVelocity = Vector2D(
            vecWishForward.x * pCmd->m_flForwardMove + vecWishRight.x * pCmd->m_flSideMove,
            vecWishForward.y * pCmd->m_flForwardMove + vecWishRight.y * pCmd->m_flSideMove
        );

        pCmd->m_flSideMove = ( vecWishVelocity.y * vecForward.x - vecWishVelocity.x * vecForward.y ) / div;
        pCmd->m_flForwardMove = ( vecWishVelocity.x * vecRight.y - vecWishVelocity.y * vecRight.x ) / div;
    }

    const float flMaxForwardSpeed = Source->Interfaces.m_pConVar->FindVar( "cl_forwardspeed" )->GetFloat( );
    const float flMaxBackSpeed = Source->Interfaces.m_pConVar->FindVar( "cl_backspeed" )->GetFloat( );
    const float flMaxSideSpeed = Source->Interfaces.m_pConVar->FindVar( "cl_sidespeed" )->GetFloat( );

    pCmd->m_iButtons &= ~( IN_FORWARD | IN_BACK | IN_MOVERIGHT | IN_MOVELEFT );

    if ( ( pCmd->m_flForwardMove = std::clamp( pCmd->m_flForwardMove, -flMaxBackSpeed, flMaxForwardSpeed ) ) )
        pCmd->m_iButtons |= pCmd->m_flForwardMove > 0.f ? IN_FORWARD : IN_BACK;

    if ( ( pCmd->m_flSideMove = std::clamp( pCmd->m_flSideMove, -flMaxSideSpeed, flMaxSideSpeed ) ) )
        pCmd->m_iButtons |= pCmd->m_flSideMove > 0.f ? IN_MOVERIGHT : IN_MOVELEFT;
}

void CMisc::FakeLag( CBasePlayer* pLocal, CUserCmd* pCmd, bool& bSendPacket )
{
    if ( !Variables->Parametrs.Misc.m_bFakeLag )
        return;

    static CConVar* pMaxUsrcmdProcessTicks = Source->Interfaces.m_pConVar->FindVar( "sv_maxusrcmdprocessticks" );
    if ( !pMaxUsrcmdProcessTicks )
        return;

    bSendPacket = Source->Interfaces.m_pClientState->m_nChokedCommands >= pMaxUsrcmdProcessTicks->GetInt( ) - 2;
}