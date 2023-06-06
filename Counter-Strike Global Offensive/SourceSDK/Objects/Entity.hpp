#pragma once

#include "../SDK.hpp"

class IHandleEntity
{
public:
	void SetRefEHandle( const CBaseHandle& Handle );
	const CBaseHandle& GetRefEHandle( );
};

class IClientUnknown : public IHandleEntity
{
public:
	ICollideable*		GetCollideable( );
	IClientNetworkable*	GetClientNetworkable( );
	IClientRenderable*	GetClientRenderable( );
	IClientEntity*		GetIClientEntity( );
	CBaseEntity*		GetBaseEntity( );
};

class ICollideable
{
public:
	const Vector& OBBMins( );
	const Vector& OBBMaxs( );
};

class IClientNetworkable
{
public:
	CClientClass*	GetClientClass( );
	bool			IsDormant( );
	int				EntIndex( );
};

class IClientRenderable
{
public:
	const Model_t*	GetModel( );
	bool			SetupBones( matrix3x4_t* pBoneToWorld, int nMaxBones, int iBoneMask, float flCurrentTime );
};

class IClientEntity : public IClientUnknown
{
public:
	const Vector& OBBMins( );
	const Vector& OBBMaxs( );

	DataMap_t* GetDataDescMap( );
	DataMap_t* GetPredictionDescMap( );

	CClientClass*	GetClientClass( );
	bool			IsDormant( );
	int				EntIndex( );

	const Model_t*	GetModel( );
	bool			SetupBones( matrix3x4_t* pBoneToWorld, int nMaxBones, int iBoneMask, float flCurrentTime );
};

class CBaseEntity : public IClientEntity
{
public:
	matrix3x4_t&	GetCoordinateFrame( );
	Vector&			GetOrigin( );
	int&			GetTeamNum( );
	int&			GetMoveType( );

	bool IsPlayer( );

public:
	static void SetPredictionRandomSeed( const CUserCmd* pCmd );
	static void SetPredictionPlayer( CBasePlayer* pPlayer );
};

class CBaseCombatCharacter : public CBaseEntity
{
public:
	float&			GetNextAttack( );
	CBaseHandle&	GetActiveWeapon( );
};