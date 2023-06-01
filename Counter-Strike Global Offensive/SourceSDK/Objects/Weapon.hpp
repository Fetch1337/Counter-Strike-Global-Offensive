#pragma once

#include "Entity.hpp"
#include "Player.hpp"

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
	float& m_flPostponeFireReadyTime( );
	int& m_zoomLevel( );
	int& m_iBurstShotsRemaining( );

	float GetSpread( );
	float GetInaccuracy( );
	void UpdateAccuracyPenalty( );
	CWeaponInfo* GetCSWeaponData( );

	bool IsBurstMode( );
	bool IsFireTime( );
	bool IsSecondaryFireTime( );
};