#include "Movement.hpp"
#include "EnginePrediction.hpp"
#include "../../Core/Source.hpp"

void CMovement::Instance( CCSPlayer* pLocal, CUserCmd* pCmd )
{
	BunnyHop( pLocal, pCmd );
}

void CMovement::BunnyHop( CCSPlayer* pLocal, CUserCmd* pCmd )
{
	if ( !( EnginePrediction.GetFlags( ) & FL_ONGROUND ) )
		pCmd->m_iButtons &= ~IN_JUMP;
}

void CMovement::Rotate( CCSPlayer* pLocal, CUserCmd* pCmd, QAngle& angWish )
{
    if ( pLocal->m_MoveType( ) == MOVETYPE_NOCLIP || pLocal->m_MoveType( ) == MOVETYPE_LADDER )
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

    const float flMaxForwardSpeed = Source.Interfaces.m_pConVar->FindVar( "cl_forwardspeed" )->GetFloat( );
    const float flMaxBackSpeed = Source.Interfaces.m_pConVar->FindVar( "cl_backspeed" )->GetFloat( );
    const float flMaxSideSpeed = Source.Interfaces.m_pConVar->FindVar( "cl_sidespeed" )->GetFloat( );

    pCmd->m_iButtons &= ~( IN_FORWARD | IN_BACK | IN_MOVERIGHT | IN_MOVELEFT );

    if ( ( pCmd->m_flForwardMove = std::clamp( pCmd->m_flForwardMove, -flMaxBackSpeed, flMaxForwardSpeed ) ) )
        pCmd->m_iButtons |= pCmd->m_flForwardMove > 0.f ? IN_FORWARD : IN_BACK;

    if ( ( pCmd->m_flSideMove = std::clamp( pCmd->m_flSideMove, -flMaxSideSpeed, flMaxSideSpeed ) ) )
        pCmd->m_iButtons |= pCmd->m_flSideMove > 0.f ? IN_MOVERIGHT : IN_MOVELEFT;
}