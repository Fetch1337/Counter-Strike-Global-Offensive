#pragma once

#include "Entity.hpp"
#include "Weapon.hpp"

class CBasePlayer : public CBaseCombatCharacter
{
public:
	static CBasePlayer* GetLocalPlayer( );

	CAnimationLayer*	GetAnimationLayers( );
	CAnimationState*	GetAnimationState( );
	QAngle*				GetRenderAngles();
	QAngle&				GetEyeAngles( );
	QAngle&				GetAimPunchAngle( );
	QAngle&				GetViewPunchAngle( );
	Vector&				GetViewOffset( );
	Vector&				GetVelocity( );
	Vector&				GetBaseVelocity( );
	float&				GetFallVelocity( );
	char&				GetLifeState( );
	int&				GetTickBase( );
	int&				GetHealth( );
	int&				GetFlags( );

	bool IsAlive( );
	bool IsEnemy( CBasePlayer* pPlayer );
	bool CanShoot( CWeaponCSBaseGun* pBaseWeapon );
	void SetCurrentCommand( CUserCmd* pCmd );
};