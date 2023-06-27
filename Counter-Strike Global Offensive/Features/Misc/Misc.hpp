#pragma once

#include "../../SourceSDK/SDK.hpp"
#include "../../SourceSDK/Objects/Player.hpp"

class CMisc
{
public:
	void Instance( CBasePlayer* pLocal, CUserCmd* pCmd, bool& bSendPacket );
	void Rotate( CBasePlayer* pLocal, CUserCmd* pCmd, QAngle& angWish );

private:
	void BunnyHop( CBasePlayer* pLocal, CUserCmd* pCmd );
	void FakeLag( CBasePlayer* pLocal, CUserCmd* pCmd, bool& bSendPacket );
};

inline const std::unique_ptr< CMisc > Misc{ new CMisc( ) };