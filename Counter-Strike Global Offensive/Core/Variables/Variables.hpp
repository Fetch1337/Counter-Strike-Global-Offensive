#pragma once

#include "../../SourceSDK/SDK.hpp"

class CVariables
{
public:
	bool Save( );
	bool Load( );

	struct Parametrs_t
	{
		bool m_bAntiAimEnable = false;
		int m_iAntiAimPitch = 0;
		int m_iAntiAimYaw = 0;

		int m_iCurrentConfig = 0;
	} Parametrs;
};

inline CVariables Variables;