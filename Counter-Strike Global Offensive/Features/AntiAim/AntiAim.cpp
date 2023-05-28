#include "AntiAim.hpp"

void CAntiAim::Instance( CCSPlayer* pLocal, CUserCmd* pCmd )
{
	pCmd->m_angViewAngles.x = 89.f;
	pCmd->m_angViewAngles.y += 180.f;
}