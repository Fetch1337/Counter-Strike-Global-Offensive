#pragma once

#include "../../SourceSDK/SDK.hpp"
#include "../../SourceSDK/Objects/Player.hpp"

class CAntiAim
{
public:
	void Instance( CCSPlayer* pLocal, CUserCmd* pCmd );

private:
	void ModifyPitch( CCSPlayer* pLocal, CUserCmd* pCmd );
	void ModifyYaw( CCSPlayer* pLocal, CUserCmd* pCmd );
};

inline CAntiAim AntiAim;