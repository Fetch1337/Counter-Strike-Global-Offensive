#pragma once

#include "../../SourceSDK/SDK.hpp"
#include "../../SourceSDK/Objects/Player.hpp"

class CPlayerESP
{
public:
	void Instance( );

private:
	void DrawBox( CBasePlayer* pPlayer, RECT BBox );
};

inline CPlayerESP PlayerESP;