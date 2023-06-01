#include "Player.hpp"
#include "../../Core/Source.hpp"
#include "../../Utilities/PropManager.hpp"

CBasePlayer* CBasePlayer::GetLocalPlayer( )
{
	auto iIndex = Source.Interfaces.m_pEngine->GetLocalPlayer( );
	if ( !iIndex )
		return nullptr;

	auto pClient = Source.Interfaces.m_pEntList->GetClientEntity( iIndex );
	if ( !pClient )
		return nullptr;

	auto pBasePlayer = ( CBasePlayer* )pClient->GetBaseEntity( );
	if ( !pBasePlayer || !pBasePlayer->IsPlayer( ) )
		return nullptr;

	return pBasePlayer;
}

QAngle* CBasePlayer::RenderAngles( )
{
	static int iOffset = PropManager.GetOffset( "DT_BasePlayer", "deadflag" ) + 0x4;
	return ( QAngle* )( this + iOffset );
}

QAngle& CBasePlayer::m_angEyeAngles( )
{
	static int iOffset = PropManager.GetOffset( "DT_BasePlayer", "m_angEyeAngles" );
	return *( QAngle* )( this + iOffset );
}

QAngle& CBasePlayer::m_aimPunchAngle( )
{
	static int iOffset = PropManager.GetOffset( "DT_BasePlayer", "m_aimPunchAngle" );
	return *( QAngle* )( this + iOffset );
}

QAngle& CBasePlayer::m_viewPunchAngle( )
{
	static int iOffset = PropManager.GetOffset( "DT_BasePlayer", "m_viewPunchAngle" );
	return *( QAngle* )( this + iOffset );
}

Vector& CBasePlayer::m_vecViewOffset( )
{
	static int iOffset = PropManager.GetOffset( "DT_BasePlayer", "m_vecViewOffset" );
	return *( Vector* )( this + iOffset );
}

Vector& CBasePlayer::m_vecVelocity( )
{
	static int iOffset = PropManager.GetOffset( "DT_BasePlayer", "m_vecVelocity" );
	return *( Vector* )( this + iOffset );
}

Vector& CBasePlayer::m_vecBaseVelocity( )
{
	static int iOffset = PropManager.GetOffset( "DT_BasePlayer", "m_vecBaseVelocity" );
	return *( Vector* )( this + iOffset );
}

float& CBasePlayer::m_flFallVelocity( )
{
	static int iOffset = PropManager.GetOffset( "DT_BasePlayer", "m_flFallVelocity" );
	return *( float* )( this + iOffset );
}

char& CBasePlayer::m_lifeState( )
{
	static int iOffset = PropManager.GetOffset( "DT_BasePlayer", "m_lifeState" );
	return *( char* )( this + iOffset );
}

int& CBasePlayer::m_nTickBase( )
{
	static int iOffset = PropManager.GetOffset( "DT_BasePlayer", "m_nTickBase" );
	return *( int* )( this + iOffset );
}

int& CBasePlayer::m_iHealth( )
{
	static int iOffset = PropManager.GetOffset( "DT_BasePlayer", "m_iHealth" );
	return *( int* )( this + iOffset );
}

int& CBasePlayer::m_fFlags( )
{
	static int iOffset = PropManager.GetOffset( "DT_BasePlayer", "m_fFlags" );
	return *( int* )( this + iOffset );
}

bool CBasePlayer::IsAlive( )
{
	return ( this->m_lifeState( ) == LIFE_ALIVE );
}

bool CBasePlayer::IsEnemy( CBasePlayer* pPlayer )
{
	if ( this->m_iTeamNum( ) != pPlayer->m_iTeamNum( ) )
		return true;

	return false;
}

bool CBasePlayer::CanShoot( CWeaponCSBaseGun* pBaseWeapon )
{
	const float flServerTime = TICKS_TO_TIME( this->m_nTickBase( ) );

	if ( pBaseWeapon->m_iClip1( ) <= 0 )
		return false;

	if ( this->m_flNextAttack( ) > flServerTime )
		return false;

	const short nDefinitionIndex = pBaseWeapon->m_iItemDefinitionIndex( );

	if ( nDefinitionIndex == WEAPON_FAMAS || nDefinitionIndex == WEAPON_GLOCK )
	{
		if ( pBaseWeapon->IsBurstMode( ) && pBaseWeapon->m_iBurstShotsRemaining( ) > 0 )
			return true;
	}

	if ( pBaseWeapon->m_flNextPrimaryAttack( ) > flServerTime )
		return false;

	if ( nDefinitionIndex == WEAPON_REVOLVER && pBaseWeapon->m_flPostponeFireReadyTime( ) > flServerTime )
		return false;

	return true;
}

void CBasePlayer::SetCurrentCommand( CUserCmd* pCmd )
{
	static int iOffset = PropManager.GetOffset( "DT_BasePlayer", "m_hConstraintEntity" ) - 0xC;
	*( CUserCmd** )( this + iOffset ) = pCmd;
}