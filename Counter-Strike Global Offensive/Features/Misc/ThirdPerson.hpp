#pragma once

#include "../../SourceSDK/SDK.hpp"
#include "../../SourceSDK/Objects/Player.hpp"

class CThirdPerson
{
public:
	void Instance( );
};

inline const std::unique_ptr< CThirdPerson > ThirdPerson{ new CThirdPerson( ) };