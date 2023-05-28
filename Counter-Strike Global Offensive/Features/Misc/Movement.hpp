#pragma once

#include "../../SourceSDK/SDK.hpp"
#include "../../SourceSDK/Objects/Player.hpp"

class CMovement
{
public:
	void Instance( CCSPlayer* pLocal, CUserCmd* pCmd );
	void Rotate( CCSPlayer* pLocal, CUserCmd* pCmd, QAngle& angWish );

private:
	void BunnyHop( CCSPlayer* pLocal, CUserCmd* pCmd );
};

inline CMovement Movement;