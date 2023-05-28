#pragma once

#include "../../SourceSDK/SDK.hpp"

struct PlayerData_t
{
	QAngle m_aimPunchAngle = { };
	Vector m_vecBaseVelocity = { };
	float m_flFallVelocity = 0.0f;
};

class CEnginePrediction
{
public:
	void Begin( CUserCmd* pCmd );
	void End( );

	int GetFlags( );

	void OnFrameStageNotify( EClientFrameStage Stage );
	void OnRunCommand( CBasePlayer* pPlayer );

private:
	CUserCmd* m_pCmd = nullptr;

	CCSPlayer* m_pPlayer = nullptr;
	CWeaponCSBaseGun* m_pWeapon = nullptr;

	int m_fFlags = 0;

	float m_flCurrentTime = 0.0f;
	float m_flFrameTime = 0.0f;

	PlayerData_t m_Data[ 128 ] = { };
};

inline CEnginePrediction EnginePrediction;