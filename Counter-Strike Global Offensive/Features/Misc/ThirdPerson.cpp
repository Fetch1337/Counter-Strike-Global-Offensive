#include "ThirdPerson.hpp"
#include "../../Core/Variables/Variables.hpp"
#include "../../Core/Source.hpp"

void CThirdPerson::Instance( )
{
	if ( !Variables->Parametrs.Misc.m_bThirdPerson )
	{
		Source->Interfaces.m_pInput->m_bCameraInThirdPerson = false;
		return;
	}

	Source->Interfaces.m_pInput->m_bCameraInThirdPerson = true;
}