#pragma once

#include "../../SourceSDK/SDK.hpp"
#include "../../SourceSDK/Objects/Player.hpp"

class CMovement
{
public:
	void Instance( CBasePlayer* pLocal, CUserCmd* pCmd );
	void Rotate( CBasePlayer* pLocal, CUserCmd* pCmd, QAngle& angWish );

private:
	void BunnyHop( CBasePlayer* pLocal, CUserCmd* pCmd );
};

inline CMovement Movement;