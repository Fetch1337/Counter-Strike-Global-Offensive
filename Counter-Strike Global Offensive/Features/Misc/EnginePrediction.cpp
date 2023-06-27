#include "EnginePrediction.hpp"
#include "../../SourceSDK/Objects/Player.hpp"
#include "../../SourceSDK/Objects/Weapon.hpp"
#include "../../Core/Includes/Global.hpp"
#include "../../Core/Source.hpp"

void CEnginePrediction::Begin( CUserCmd* pCmd )
{
	if ( !Globals->m_pCmd || !Globals->m_pLocal || !Globals->m_pLocal->IsAlive( ) )
		return;

	m_pWeapon = Source->Interfaces.m_pEntList->Get<CWeaponCSBaseGun>( Globals->m_pLocal->GetActiveWeapon( ) );
	if ( !m_pWeapon )
		return;

	m_fFlags = Globals->m_pLocal->GetFlags( );

	m_flCurrentTime = Source->Interfaces.m_pGlobalVars->m_flCurrentTime;
	m_flFrameTime = Source->Interfaces.m_pGlobalVars->m_flFrameTime;

	Globals->m_pLocal->SetCurrentCommand( pCmd );

	CBaseEntity::SetPredictionRandomSeed( pCmd );
	CBaseEntity::SetPredictionPlayer( Globals->m_pLocal );

	Source->Interfaces.m_pGlobalVars->m_flCurrentTime = TICKS_TO_TIME( Globals->m_pLocal->GetTickBase( ) );
	Source->Interfaces.m_pGlobalVars->m_flFrameTime = Source->Interfaces.m_pGlobalVars->m_flIntervalPerTick;

	CMoveData Move = { };
	memset( &Move, 0, sizeof( Move ) );

	Source->Interfaces.m_pMoveHelper->SetHost( Globals->m_pLocal );
	Source->Interfaces.m_pPrediction->SetupMove( Globals->m_pLocal, pCmd, Source->Interfaces.m_pMoveHelper, &Move );
	Source->Interfaces.m_pGameMovement->ProcessMovement( Globals->m_pLocal, &Move );
	Source->Interfaces.m_pPrediction->FinishMove( Globals->m_pLocal, pCmd, &Move );
}

void CEnginePrediction::End( )
{
	if ( !Globals->m_pCmd || !Globals->m_pLocal || !Globals->m_pLocal->IsAlive( ) || !m_pWeapon )
		return;

	Source->Interfaces.m_pMoveHelper->SetHost( nullptr );

	Source->Interfaces.m_pGlobalVars->m_flCurrentTime = m_flCurrentTime;
	Source->Interfaces.m_pGlobalVars->m_flFrameTime = m_flFrameTime;

	CBaseEntity::SetPredictionRandomSeed( nullptr );
	CBaseEntity::SetPredictionPlayer( nullptr );

	Globals->m_pLocal->SetCurrentCommand( nullptr );
}

int CEnginePrediction::GetFlags( )
{
	return m_fFlags;
}