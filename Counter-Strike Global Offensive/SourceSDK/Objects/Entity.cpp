#include "Entity.hpp"
#include "../../Core/Source.hpp"
#include "../../Utilities/PropManager.hpp"

void IHandleEntity::SetRefEHandle( const CBaseHandle& Handle )
{
	using Fn = void ( __thiscall* )( void*, const CBaseHandle& );
	return Memory->GetVFunc<Fn>( this, 1 )( this, Handle );
}

const CBaseHandle& IHandleEntity::GetRefEHandle( )
{
	using Fn = const CBaseHandle& ( __thiscall* )( void* );
	return Memory->GetVFunc<Fn>( this, 2 )( this );
}

ICollideable* IClientUnknown::GetCollideable( )
{
	using Fn = ICollideable* ( __thiscall* )( void* );
	return Memory->GetVFunc<Fn>( this, 3 )( this );
}

IClientNetworkable* IClientUnknown::GetClientNetworkable( )
{
	using Fn = IClientNetworkable* ( __thiscall* )( void* );
	return Memory->GetVFunc<Fn>( this, 4 )( this );
}

IClientRenderable* IClientUnknown::GetClientRenderable( )
{
	using Fn = IClientRenderable* ( __thiscall* )( void* );
	return Memory->GetVFunc<Fn>( this, 5 )( this );
}

IClientEntity* IClientUnknown::GetIClientEntity( )
{
	using Fn = IClientEntity* ( __thiscall* )( void* );
	return Memory->GetVFunc<Fn>( this, 6 )( this );
}

CBaseEntity* IClientUnknown::GetBaseEntity( )
{
	using Fn = CBaseEntity* ( __thiscall* )( void* );
	return Memory->GetVFunc<Fn>( this, 7 )( this );
}

const Vector& ICollideable::OBBMins( )
{
	using Fn = const Vector& ( __thiscall* )( void* );
	return Memory->GetVFunc<Fn>( this, 1 )( this );
}

const Vector& ICollideable::OBBMaxs( )
{
	using Fn = const Vector& ( __thiscall* )( void* );
	return Memory->GetVFunc<Fn>( this, 2 )( this );
}

CClientClass* IClientNetworkable::GetClientClass( )
{
	using Fn = CClientClass * ( __thiscall* )( void* );
	return Memory->GetVFunc<Fn>( this, 2 )( this );
}

bool IClientNetworkable::IsDormant( )
{
	using Fn = bool ( __thiscall* )( void* );
	return Memory->GetVFunc<Fn>( this, 9 )( this );
}

int IClientNetworkable::EntIndex( )
{
	using Fn = int ( __thiscall* )( void* );
	return Memory->GetVFunc<Fn>( this, 10 )( this );
}

const Model_t* IClientRenderable::GetModel( )
{
	using Fn = const Model_t* ( __thiscall* )( void* );
	return Memory->GetVFunc<Fn>( this, 8 )( this );
}

bool IClientRenderable::SetupBones( matrix3x4_t* pBoneToWorld, int nMaxBones, int iBoneMask, float flCurrentTime )
{
	using Fn = bool ( __thiscall* )( void*, matrix3x4_t*, int, int, float );
	return Memory->GetVFunc<Fn>( this, 13 )( this, pBoneToWorld, nMaxBones, iBoneMask, flCurrentTime );
}

const Vector& IClientEntity::OBBMins( )
{
	auto pCollideable = GetCollideable( );
	return pCollideable->OBBMins( );
}

const Vector& IClientEntity::OBBMaxs( )
{
	auto pCollideable = GetCollideable( );
	return pCollideable->OBBMaxs( );
}

DataMap_t* IClientEntity::GetDataDescMap( )
{
	using Fn = DataMap_t* ( __thiscall* )( void* );
	return Memory->GetVFunc<Fn>( this, 15 )( this );
}

DataMap_t* IClientEntity::GetPredictionDescMap( )
{
	using Fn = DataMap_t* ( __thiscall* )( void* );
	return Memory->GetVFunc<Fn>( this, 17 )( this );
}

CClientClass* IClientEntity::GetClientClass( )
{
	auto pNetworkable = GetClientNetworkable( );
	return pNetworkable->GetClientClass( );
}

bool IClientEntity::IsDormant( )
{
	auto pNetworkable = GetClientNetworkable( );
	return pNetworkable->IsDormant( );
}

int IClientEntity::EntIndex( )
{
	auto pNetworkable = GetClientNetworkable( );
	return pNetworkable->EntIndex( );
}

const Model_t* IClientEntity::GetModel( )
{
	auto pRenderable = GetClientRenderable( );
	return pRenderable->GetModel( );
}

bool IClientEntity::SetupBones( matrix3x4_t* pBoneToWorld, int nMaxBones, int iBoneMask, float flCurrentTime )
{
	auto pRenderable = GetClientRenderable( );
	return pRenderable->SetupBones( pBoneToWorld, nMaxBones, iBoneMask, flCurrentTime );
}

bool CBaseEntity::IsPlayer( )
{
	using Fn = bool ( __thiscall* )( void* );
	return Memory->GetVFunc<Fn>( this, 158 )( this );
}

matrix3x4_t& CBaseEntity::GetCoordinateFrame( )
{
	static int iOffset = PropManager->FindInDataMap( this->GetDataDescMap( ), "m_rgflCoordinateFrame" );
	return *( matrix3x4_t* )( this + iOffset );
}

int& CBaseEntity::GetMoveType( )
{
	static int iOffset = PropManager->FindInDataMap( this->GetPredictionDescMap( ), "m_MoveType" );
	return *( int* )( this + iOffset );
}

int& CBaseEntity::GetTeamNum( )
{
	static int iOffset = PropManager->GetOffset( "DT_BaseEntity", "m_iTeamNum" );
	return *( int* )( this + iOffset );
}

Vector& CBaseEntity::GetOrigin( )
{
	static int iOffset = PropManager->GetOffset( "DT_BaseEntity", "m_vecOrigin" );
	return *( Vector* )( this + iOffset );
}

void CBaseEntity::SetPredictionRandomSeed( const CUserCmd* pCmd )
{
	**( int** )( Source->Patterns.m_uPredictionRandomSeed ) = pCmd ? pCmd->m_iRandomSeed : -1;
}

void CBaseEntity::SetPredictionPlayer( CBasePlayer* pPlayer )
{
	**( CBasePlayer*** )( Source->Patterns.m_uPredictionPlayer ) = pPlayer;
}

float& CBaseCombatCharacter::GetNextAttack( )
{
	static int iOffset = PropManager->GetOffset( "DT_BaseCombatCharacter", "m_flNextAttack" );
	return *( float* ) ( this + iOffset );
}

CBaseHandle& CBaseCombatCharacter::GetActiveWeapon( )
{
	static int iOffset = PropManager->GetOffset( "DT_BaseCombatCharacter", "m_hActiveWeapon" );
	return *( CBaseHandle* )( this + iOffset );
}