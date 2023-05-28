#pragma once

#include "../../SourceSDK/SDK.hpp"

class CVariables
{
public:
	bool Save( );
	bool Load( );

	struct Parametrs_t
	{
		bool m_bCheckbox = false;
		int m_SliderInt = 0;
		float m_SliderFloat = 0.0f;

		int m_iCurrentConfig = 0;
	} Parametrs;
};

inline CVariables Variables;