#include "AntiAim.hpp"
#include "../../Core/Variables/Variables.hpp"

void CAntiAim::Instance( CCSPlayer* pLocal, CUserCmd* pCmd )
{
	if ( !Variables.Parametrs.m_bAntiAimEnable )
		return;

	ModifyPitch( pLocal, pCmd );
	ModifyYaw( pLocal, pCmd );
}

void CAntiAim::ModifyPitch( CCSPlayer* pLocal, CUserCmd* pCmd )
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

void CAntiAim::ModifyYaw( CCSPlayer* pLocal, CUserCmd* pCmd )
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
