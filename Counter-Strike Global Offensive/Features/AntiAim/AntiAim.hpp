#pragma once

#include "../../SourceSDK/SDK.hpp"
#include "../../SourceSDK/Objects/Player.hpp"

class CAntiAim
{
public:
	void Instance( CBasePlayer* pLocal, CUserCmd* pCmd, bool& bSendPacket );

private:
	void Pitch( CBasePlayer* pLocal, CUserCmd* pCmd );
	void Yaw( CBasePlayer* pLocal, CUserCmd* pCmd );
	void Desync( CBasePlayer* pLocal, CUserCmd* pCmd, bool& bSendPacket );
};

inline CAntiAim AntiAim;