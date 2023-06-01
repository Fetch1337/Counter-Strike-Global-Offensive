#include "AntiAim.hpp"
#include "../../Core/Source.hpp"
#include "../../Core/Variables/Variables.hpp"
#include "../../Utilities/InputManager.hpp"

void CAntiAim::Instance( CBasePlayer* pLocal, CUserCmd* pCmd, bool& bSendPacket )
{
	if ( !Variables.Parametrs.AntiAim.m_bEnable )
		return;

	if ( pLocal->m_MoveType( ) == MOVETYPE_LADDER || pLocal->m_MoveType( ) == MOVETYPE_NOCLIP )
		return;

	if ( pCmd->m_iButtons & IN_USE )
		return;

	CWeaponCSBaseGun* pWeapon = Source.Interfaces.m_pEntList->Get<CWeaponCSBaseGun>( pLocal->m_hActiveWeapon( ) );
	if ( !pWeapon )
		return;

	if ( pLocal->CanShoot( pWeapon ) )
	{
		if ( pCmd->m_iButtons & IN_ATTACK )
			return;
	}

	Pitch( pLocal, pCmd );
	Yaw( pLocal, pCmd );
	Desync( pLocal, pCmd, bSendPacket );

	pCmd->m_angViewAngles.z += Variables.Parametrs.AntiAim.m_iRoll;
}

void CAntiAim::Pitch( CBasePlayer* pLocal, CUserCmd* pCmd )
{
	switch ( Variables.Parametrs.AntiAim.m_iPitch )
	{
	case 1:
		pCmd->m_angViewAngles.x = -89.f;
		break;
	case 2:
		pCmd->m_angViewAngles.x = 89.f;
		break;
	}
}

void CAntiAim::Yaw( CBasePlayer* pLocal, CUserCmd* pCmd )
{
	switch ( Variables.Parametrs.AntiAim.m_iYaw )
	{
	case 1:
		pCmd->m_angViewAngles.y += 90.f;
		break;
	case 2:
		pCmd->m_angViewAngles.y -= 90.f;
		break;
	case 3:
		pCmd->m_angViewAngles.y += 180.f;
		break;
	}
}

void CAntiAim::Desync( CBasePlayer* pLocal, CUserCmd* pCmd, bool& bSendPacket )
{
	float flDesyncDegrees = Variables.Parametrs.AntiAim.m_iDesync * 2.f;
	if ( InputManager.IsBindActive( Variables.Parametrs.AntiAim.m_DesyncFlipKey ) )
		flDesyncDegrees = -Variables.Parametrs.AntiAim.m_iDesync * 2.f;

	if ( !bSendPacket )
		pCmd->m_angViewAngles.y += flDesyncDegrees;
}