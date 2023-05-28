#pragma once

#include "../../SourceSDK/SDK.hpp"
#include "../../SourceSDK/Objects/Player.hpp"

class CThirdPerson
{
public:
	void Instance( CBasePlayer* pLocal );
};

inline CThirdPerson ThirdPerson;