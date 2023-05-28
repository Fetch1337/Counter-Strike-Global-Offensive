#pragma once

#include "Entity.hpp"

class CBaseCombatWeapon : public CBaseEntity
{
public:
	float& m_flNextPrimaryAttack( );
	float& m_flNextSecondaryAttack( );
	CBaseHandle& m_hOwner( );
	int& m_iClip1( );
	int& m_iItemDefinitionIndex( );
};

class CWeaponCSBaseGun : public CBaseCombatWeapon
{
public:
	float& m_flRecoilIndex( );

	float GetSpread( );
	float GetInaccuracy( );
	void UpdateAccuracyPenalty( );

	bool IsFireTime( );
	bool IsSecondaryFireTime( );
};