#pragma once

#include "../../SourceSDK/SDK.hpp"
#include "../../SourceSDK/Objects/Entity.hpp"
#include "../../SourceSDK/Objects/Player.hpp"
#include "../../SourceSDK/Objects/Weapon.hpp"
#include "../../Utilities/Render.hpp"

class CPlayerESP
{
public:
	void Instance( );

private:
	void DrawBox( CBasePlayer* pPlayer, Box_t BBox, int iPlayerType );
	void DrawName( CBasePlayer* pPlayer, Box_t BBox, int iPlayerType );
	void DrawHealth( CBasePlayer* pPlayer, Box_t BBox, int iPlayerType );
	void DrawAmmo( CBasePlayer* pPlayer, Box_t BBox, int iPlayerType );
};

inline CPlayerESP PlayerESP;