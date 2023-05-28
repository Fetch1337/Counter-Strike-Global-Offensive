#include "Weapon.hpp"
#include "../../Core/Source.hpp"
#include "../../Utilities/PropManager.hpp"

float& CBaseCombatWeapon::m_flNextPrimaryAttack( )
{
	static int iOffset = PropManager.GetOffset( "DT_BaseCombatWeapon", "m_flNextPrimaryAttack" );
	return *( float* )( this + iOffset );
}

float& CBaseCombatWeapon::m_flNextSecondaryAttack( )
{
	static int iOffset = PropManager.GetOffset( "DT_BaseCombatWeapon", "m_flNextSecondaryAttack" );
	return *( float* )( this + iOffset );
}

CBaseHandle& CBaseCombatWeapon::m_hOwner( )
{
	static int iOffset = PropManager.GetOffset( "DT_BaseCombatWeapon", "m_hOwner" );
	return *( CBaseHandle* )( this + iOffset );
}

int& CBaseCombatWeapon::m_iClip1( )
{
	static int iOffset = PropManager.GetOffset( "DT_BaseCombatWeapon", "m_iClip1" );
	return *( int* )( this + iOffset );
}

int& CBaseCombatWeapon::m_iItemDefinitionIndex( )
{
	static int iOffset = PropManager.GetOffset( "DT_BaseCombatWeapon", "m_iItemDefinitionIndex" );
	return *( int* )( this + iOffset );
}

float& CWeaponCSBaseGun::m_flRecoilIndex( )
{
	static int iOffset = PropManager.GetOffset( "DT_WeaponCSBase", "m_flRecoilIndex" );
	return *( float* )( this + iOffset );
}

float CWeaponCSBaseGun::GetSpread( )
{
	using Fn = float ( __thiscall* )( void* );
	return Memory.GetVFunc<Fn>( this, 453 )( this );
}

float CWeaponCSBaseGun::GetInaccuracy( )
{
	using Fn = float ( __thiscall* )( void* );
	return Memory.GetVFunc<Fn>( this, 483 )( this );
}

void CWeaponCSBaseGun::UpdateAccuracyPenalty( )
{
	using Fn = void ( __thiscall* )( void* );
	return Memory.GetVFunc<Fn>( this, 484 )( this );
}

bool CWeaponCSBaseGun::IsFireTime( )
{
	return ( Source.Interfaces.m_pGlobalVars->m_flCurrentTime >= m_flNextPrimaryAttack( ) );
}

bool CWeaponCSBaseGun::IsSecondaryFireTime( )
{
	return ( Source.Interfaces.m_pGlobalVars->m_flCurrentTime >= m_flNextSecondaryAttack( ) );
}