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

CAnimationLayer* CBasePlayer::GetAnimationLayers( )
{
	return *( CAnimationLayer** )( this + Source.Patterns.m_uAnimationOverlays );
}

CAnimationState* CBasePlayer::GetAnimationState( )
{
	static int iOffset = PropManager.GetOffset( "DT_CSPlayer", "m_bIsScoped" ) - 0x14;
	return *( CAnimationState** )( this + iOffset );
}

QAngle* CBasePlayer::GetRenderAngles( )
{
	static int iOffset = PropManager.GetOffset( "DT_BasePlayer", "deadflag" ) + 0x4;
	return ( QAngle* )( this + iOffset );
}

QAngle& CBasePlayer::GetEyeAngles( )
{
	static int iOffset = PropManager.GetOffset( "DT_BasePlayer", "m_angEyeAngles" );
	return *( QAngle* )( this + iOffset );
}

QAngle& CBasePlayer::GetAimPunchAngle( )
{
	static int iOffset = PropManager.GetOffset( "DT_BasePlayer", "m_aimPunchAngle" );
	return *( QAngle* )( this + iOffset );
}

QAngle& CBasePlayer::GetViewPunchAngle( )
{
	static int iOffset = PropManager.GetOffset( "DT_BasePlayer", "m_viewPunchAngle" );
	return *( QAngle* )( this + iOffset );
}

Vector& CBasePlayer::GetViewOffset( )
{
	static int iOffset = PropManager.GetOffset( "DT_BasePlayer", "m_vecViewOffset" );
	return *( Vector* )( this + iOffset );
}

Vector& CBasePlayer::GetVelocity( )
{
	static int iOffset = PropManager.GetOffset( "DT_BasePlayer", "m_vecVelocity" );
	return *( Vector* )( this + iOffset );
}

Vector& CBasePlayer::GetBaseVelocity( )
{
	static int iOffset = PropManager.GetOffset( "DT_BasePlayer", "m_vecBaseVelocity" );
	return *( Vector* )( this + iOffset );
}

float& CBasePlayer::GetFallVelocity( )
{
	static int iOffset = PropManager.GetOffset( "DT_BasePlayer", "m_flFallVelocity" );
	return *( float* )( this + iOffset );
}

char& CBasePlayer::GetLifeState( )
{
	static int iOffset = PropManager.GetOffset( "DT_BasePlayer", "m_lifeState" );
	return *( char* )( this + iOffset );
}

int& CBasePlayer::GetTickBase( )
{
	static int iOffset = PropManager.GetOffset( "DT_BasePlayer", "m_nTickBase" );
	return *( int* )( this + iOffset );
}

int& CBasePlayer::GetHealth( )
{
	static int iOffset = PropManager.GetOffset( "DT_BasePlayer", "m_iHealth" );
	return *( int* )( this + iOffset );
}

int& CBasePlayer::GetFlags( )
{
	static int iOffset = PropManager.GetOffset( "DT_BasePlayer", "m_fFlags" );
	return *( int* )( this + iOffset );
}

bool CBasePlayer::IsAlive( )
{
	return this->GetLifeState( ) == LIFE_ALIVE;
}

bool CBasePlayer::IsEnemy( CBasePlayer* pPlayer )
{
	if ( this->GetTeamNum( ) != pPlayer->GetTeamNum( ) )
		return true;

	return false;
}

bool CBasePlayer::CanShoot( CWeaponCSBaseGun* pBaseWeapon )
{
	const float flServerTime = TICKS_TO_TIME( this->GetTickBase( ) );

	if ( pBaseWeapon->GetClip1( ) <= 0 )
		return false;

	if ( this->GetNextAttack( ) > flServerTime )
		return false;

	const short nDefinitionIndex = pBaseWeapon->GetItemDefinitionIndex( );

	if ( nDefinitionIndex == WEAPON_FAMAS || nDefinitionIndex == WEAPON_GLOCK )
	{
		if ( pBaseWeapon->IsBurstMode( ) && pBaseWeapon->GetBurstShotsRemaining( ) > 0 )
			return true;
	}

	if ( pBaseWeapon->GetNextPrimaryAttack( ) > flServerTime )
		return false;

	if ( nDefinitionIndex == WEAPON_REVOLVER && pBaseWeapon->GetPostponeFireReadyTime( ) > flServerTime )
		return false;

	return true;
}

void CBasePlayer::SetCurrentCommand( CUserCmd* pCmd )
{
	static int iOffset = PropManager.GetOffset( "DT_BasePlayer", "m_hConstraintEntity" ) - 0xC;
	*( CUserCmd** )( this + iOffset ) = pCmd;
}