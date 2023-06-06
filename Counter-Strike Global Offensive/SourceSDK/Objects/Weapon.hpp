#pragma once

#include "Entity.hpp"
#include "Player.hpp"

class CBaseCombatWeapon : public CBaseEntity
{
public:
	CBaseHandle&	GetOwner( );
	float&			GetNextPrimaryAttack( );
	float&			GetNextSecondaryAttack( );
	int&			GetClip1( );
	int&			GetItemDefinitionIndex( );
};

class CWeaponCSBaseGun : public CBaseCombatWeapon
{
public:

	float&	GetRecoilIndex( );
	float&	GetPostponeFireReadyTime( );
	int&	GetZoomLevel( );
	int&	GetBurstShotsRemaining( );

	float			GetSpread( );
	float			GetInaccuracy( );
	void			UpdateAccuracyPenalty( );
	CWeaponInfo*	GetCSWeaponData( );

	bool IsBurstMode( );
	bool IsFireTime( );
	bool IsSecondaryFireTime( );
};