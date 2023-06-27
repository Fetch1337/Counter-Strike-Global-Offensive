#pragma once

#include "../../SourceSDK/SDK.hpp"
#include "../../SourceSDK/Objects/Entity.hpp"
#include "../../SourceSDK/Objects/Player.hpp"
#include "../../SourceSDK/Objects/Weapon.hpp"
#include "../../Utilities/Render.hpp"

class CWorldESP
{
public:
	void Instance( );
};

inline const std::unique_ptr< CWorldESP > WorldESP{ new CWorldESP( ) };