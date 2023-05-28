#include "EnginePrediction.hpp"
#include "../../SourceSDK/Objects/Player.hpp"
#include "../../SourceSDK/Objects/Weapon.hpp"
#include "../../Core/Source.hpp"

void CEnginePrediction::Begin( CUserCmd* pCmd )
{
	m_pCmd = pCmd;
	if ( !m_pCmd )
		return;

	m_pPlayer = CCSPlayer::GetLocalPlayer( );
	if ( !m_pPlayer || !m_pPlayer->IsAlive( ) )
		return;

	m_pWeapon = ( CWeaponCSBaseGun* )( Source.Interfaces.m_pEntList->GetClientEntityFromHandle( m_pPlayer->m_hActiveWeapon( ) ) );
	if ( !m_pWeapon )
		return;

	m_fFlags = m_pPlayer->m_fFlags( );

	m_flCurrentTime = Source.Interfaces.m_pGlobalVars->m_flCurrentTime;
	m_flFrameTime = Source.Interfaces.m_pGlobalVars->m_flFrameTime;

	m_pPlayer->SetCurrentCommand( pCmd );

	CBaseEntity::SetPredictionRandomSeed( pCmd );
	CBaseEntity::SetPredictionPlayer( m_pPlayer );

	Source.Interfaces.m_pGlobalVars->m_flCurrentTime = static_cast<float>( m_pPlayer->m_nTickBase( ) ) * Source.Interfaces.m_pGlobalVars->m_flIntervalPerTick;
	Source.Interfaces.m_pGlobalVars->m_flFrameTime = Source.Interfaces.m_pGlobalVars->m_flIntervalPerTick;

	CMoveData Move = { };
	memset( &Move, 0, sizeof( Move ) );

	Source.Interfaces.m_pMoveHelper->SetHost( m_pPlayer );
	Source.Interfaces.m_pPrediction->SetupMove( m_pPlayer, pCmd, Source.Interfaces.m_pMoveHelper, &Move );
	Source.Interfaces.m_pGameMovement->ProcessMovement( m_pPlayer, &Move );
	Source.Interfaces.m_pPrediction->FinishMove( m_pPlayer, pCmd, &Move );
}

void CEnginePrediction::End( )
{
	if ( !m_pCmd || !m_pPlayer || !m_pWeapon )
		return;

	Source.Interfaces.m_pMoveHelper->SetHost( nullptr );

	Source.Interfaces.m_pGlobalVars->m_flCurrentTime = m_flCurrentTime;
	Source.Interfaces.m_pGlobalVars->m_flFrameTime = m_flFrameTime;

	CBaseEntity::SetPredictionRandomSeed( nullptr );
	CBaseEntity::SetPredictionPlayer( nullptr );

	m_pPlayer->SetCurrentCommand( nullptr );
}

int CEnginePrediction::GetFlags( )
{
	return m_fFlags;
}

void CEnginePrediction::OnFrameStageNotify( EClientFrameStage Stage )
{
	if ( Stage != FRAME_NET_UPDATE_POSTDATAUPDATE_START )
		return;

	auto pLocal = CCSPlayer::GetLocalPlayer( );
	if ( !pLocal )
		return;

	auto iSlot = pLocal->m_nTickBase( );
	auto pData = &m_Data[ iSlot % MULTIPLAYER_BACKUP ];

	pLocal->m_aimPunchAngle( ) = pData->m_aimPunchAngle;
	//pLocal->m_vecBaseVelocity( ) = pData->m_vecBaseVelocity;
	pLocal->m_flFallVelocity( ) = pData->m_flFallVelocity;
}

void CEnginePrediction::OnRunCommand( CBasePlayer* pPlayer )
{
	auto pLocal = CCSPlayer::GetLocalPlayer( );
	if ( !pLocal || pLocal != pPlayer )
		return;

	auto iSlot = pLocal->m_nTickBase( );
	auto pData = &m_Data[ iSlot % MULTIPLAYER_BACKUP ];

	pData->m_aimPunchAngle = pLocal->m_aimPunchAngle( );
	//pData->m_vecBaseVelocity = pLocal->m_vecBaseVelocity( );
	pData->m_flFallVelocity = pLocal->m_flFallVelocity( );
}