#pragma once

#include "../../SourceSDK/SDK.hpp"
#include "../../Utilities/InputManager.hpp"

class CVariables
{
public:
	bool Save( );
	bool Load( );

	struct Parametrs_t
	{
		int m_iCurrentConfig = 0;

		struct
		{
			bool m_bEnable{ };
			int m_iPitch{ };
			int m_iYaw{ };
			int m_iRoll{ };
			int m_iDesync{ };
			CKeyBinds m_DesyncFlipKey{ };
		} AntiAim;

		struct
		{
			bool m_bEnable{ };

			struct
			{
				bool m_bBox{ };
				bool m_bName{ };
				bool m_bHealth{ };
				bool m_bAmmo{ };
			} Players[ 3 ];
		} PlayerESP;

		struct
		{
			bool m_bBunnyHop{ };
			bool m_bFakeLag{ };
			bool m_bThirdPerson{ };
		} Misc;
	} Parametrs;
};

inline CVariables Variables;