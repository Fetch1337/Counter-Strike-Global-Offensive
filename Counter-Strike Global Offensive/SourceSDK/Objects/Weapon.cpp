#include "Weapon.hpp"
#include "../../Core/Source.hpp"
#include "../../Utilities/PropManager.hpp"

CBaseHandle& CBaseCombatWeapon::GetOwner( )
{
	static int iOffset = PropManager.GetOffset( "DT_BaseCombatWeapon", "m_hOwner" );
	return *( CBaseHandle* )( this + iOffset );
}

float& CBaseCombatWeapon::GetNextPrimaryAttack( )
{
	static int iOffset = PropManager.GetOffset( "DT_BaseCombatWeapon", "m_flNextPrimaryAttack" );
	return *( float* )( this + iOffset );
}

float& CBaseCombatWeapon::GetNextSecondaryAttack( )
{
	static int iOffset = PropManager.GetOffset( "DT_BaseCombatWeapon", "m_flNextSecondaryAttack" );
	return *( float* )( this + iOffset );
}

int& CBaseCombatWeapon::GetClip1( )
{
	static int iOffset = PropManager.GetOffset( "DT_BaseCombatWeapon", "m_iClip1" );
	return *( int* )( this + iOffset );
}

int& CBaseCombatWeapon::GetItemDefinitionIndex( )
{
	static int iOffset = PropManager.GetOffset( "DT_BaseCombatWeapon", "m_iItemDefinitionIndex" );
	return *( int* )( this + iOffset );
}

float& CWeaponCSBaseGun::GetRecoilIndex( )
{
	static int iOffset = PropManager.GetOffset( "DT_WeaponCSBase", "m_flRecoilIndex" );
	return *( float* )( this + iOffset );
}

float& CWeaponCSBaseGun::GetPostponeFireReadyTime( )
{
	static int iOffset = PropManager.GetOffset( "DT_WeaponCSBase", "m_flPostponeFireReadyTime" );
	return *( float* )( this + iOffset );
}

int& CWeaponCSBaseGun::GetZoomLevel( )
{
	static int iOffset = PropManager.GetOffset( "DT_WeaponCSBaseGun", "m_zoomLevel" );
	return *( int* )( this + iOffset );
}

int& CWeaponCSBaseGun::GetBurstShotsRemaining( )
{
	static int iOffset = PropManager.GetOffset( "DT_WeaponCSBaseGun", "m_iBurstShotsRemaining" );
	return *( int* )( this + iOffset );
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

CWeaponInfo* CWeaponCSBaseGun::GetCSWeaponData( )
{
	using Fn = CWeaponInfo * ( __thiscall* )( void* );
	return Memory.GetVFunc<Fn>( this, 461 )( this );
}

bool CWeaponCSBaseGun::IsBurstMode( )
{
	static int iOffset = PropManager.GetOffset( "DT_WeaponCSBase", "m_bBurstMode" );
	return *( bool* )( this + iOffset );
}

bool CWeaponCSBaseGun::IsFireTime( )
{
	return ( Source.Interfaces.m_pGlobalVars->m_flCurrentTime >= GetNextPrimaryAttack( ) );
}

bool CWeaponCSBaseGun::IsSecondaryFireTime( )
{
	return ( Source.Interfaces.m_pGlobalVars->m_flCurrentTime >= GetNextSecondaryAttack( ) );
}