#pragma once

#include "../../SourceSDK/SDK.hpp"
#include "../../SourceSDK/Objects/Player.hpp"

class CAntiAim
{
public:
	void Instance( CBasePlayer* pLocal, CUserCmd* pCmd );

private:
	void ModifyPitch( CBasePlayer* pLocal, CUserCmd* pCmd );
	void ModifyYaw( CBasePlayer* pLocal, CUserCmd* pCmd );
};

inline CAntiAim AntiAim;