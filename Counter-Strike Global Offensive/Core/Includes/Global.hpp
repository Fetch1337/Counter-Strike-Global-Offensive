#pragma once
#include "../../SourceSDK/SDK.hpp"

class CGlobals
{
public:
	CBasePlayer* m_pLocal = nullptr;
	CUserCmd*	 m_pCmd = nullptr;
	QAngle		 m_angReal{ };
};

inline CGlobals Globals;