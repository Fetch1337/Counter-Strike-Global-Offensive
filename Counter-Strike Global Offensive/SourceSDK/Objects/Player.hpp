#pragma once

#include "Entity.hpp"

class CBasePlayer : public CBaseCombatCharacter
{
public:
	static CBasePlayer* GetLocalPlayer( );

	QAngle* RenderAngles();
	QAngle& m_angEyeAngles( );
	QAngle& m_aimPunchAngle( );
	QAngle& m_viewPunchAngle( );
	Vector& m_vecViewOffset( );
	Vector& m_vecVelocity( );
	Vector& m_vecBaseVelocity( );
	float& m_flFallVelocity( );
	char& m_lifeState( );
	int& m_nTickBase( );
	int& m_iHealth( );
	int& m_fFlags( );

	bool IsAlive( );
	void SetCurrentCommand( CUserCmd* pCmd );
};