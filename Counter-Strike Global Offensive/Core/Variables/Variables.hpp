#pragma once

#include "../../SourceSDK/SDK.hpp"

class CVariables
{
public:
	bool Save( );
	bool Load( );

	struct Parametrs_t
	{
		int m_iCurrentConfig = 0;

		#pragma region antiaim
		bool m_bAntiAimEnable = false;
		int m_iAntiAimPitch = 0;
		int m_iAntiAimYaw = 0;
		int m_iAntiAimRoll = 0;
		#pragma endregion

		#pragma region misc
		bool m_bMiscBunnyHop = false;
		bool m_bMiscThirdPerson = false;
		#pragma endregion

	} Parametrs;
};

inline CVariables Variables;