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
	ICollideable* GetCollideable( );
	IClientNetworkable* GetClientNetworkable( );
	IClientRenderable* GetClientRenderable( );
	IClientEntity* GetIClientEntity( );
	CBaseEntity* GetBaseEntity( );
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
	ClientClass* GetClientClass( );
	bool IsDormant( );
	int EntIndex( );
};

class IClientRenderable
{
public:
	const Model_t* GetModel( );
	bool SetupBones( matrix3x4_t* pBoneToWorld, int nMaxBones, int iBoneMask, float flCurrentTime );
};

class IClientEntity : public IClientUnknown
{
public:
	const Vector& OBBMins( );
	const Vector& OBBMaxs( );

	DataMap_t* GetDataDescMap( );
	DataMap_t* GetPredictionDescMap( );

	ClientClass* GetClientClass( );
	bool IsDormant( );
	int EntIndex( );

	const Model_t* GetModel( );
	bool SetupBones( matrix3x4_t* pBoneToWorld, int nMaxBones, int iBoneMask, float flCurrentTime );
};

class CBaseEntity : public IClientEntity
{
public:
	bool IsPlayer( );
	matrix3x4_t& m_rgflCoordinateFrame( );

	int& m_iTeamNum( );
	int& m_MoveType( );
	Vector& m_vecOrigin( );

public:
	static void SetPredictionRandomSeed( const CUserCmd* pCmd );
	static void SetPredictionPlayer( CBasePlayer* pPlayer );
};

class CBaseCombatCharacter : public CBaseEntity
{
public:
	CBaseHandle& m_hActiveWeapon( );
};