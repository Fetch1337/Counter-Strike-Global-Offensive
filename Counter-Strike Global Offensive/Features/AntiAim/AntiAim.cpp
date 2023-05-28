#include "AntiAim.hpp"
#include "../../Core/Variables/Variables.hpp"

void CAntiAim::Instance( CBasePlayer* pLocal, CUserCmd* pCmd )
{
	if ( !Variables.Parametrs.m_bAntiAimEnable )
		return;

	ModifyPitch( pLocal, pCmd );
	ModifyYaw( pLocal, pCmd );

	/* Modify roll angle */
	pCmd->m_angViewAngles.z += Variables.Parametrs.m_iAntiAimRoll;
}

void CAntiAim::ModifyPitch( CBasePlayer* pLocal, CUserCmd* pCmd )
{
	switch ( Variables.Parametrs.m_iAntiAimPitch )
	{
	case 1:
		pCmd->m_angViewAngles.x = -89.f;
		break;
	case 2:
		pCmd->m_angViewAngles.x = 89.f;
		break;
	}
}

void CAntiAim::ModifyYaw( CBasePlayer* pLocal, CUserCmd* pCmd )
{
	switch ( Variables.Parametrs.m_iAntiAimYaw )
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
