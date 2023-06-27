#include "../Hooks.hpp"
#include "../../Source.hpp"
#include "../../../SourceSDK/Objects/Player.hpp"
#include "../../../Features/Misc/ThirdPerson.hpp"
#include "../../Includes/Global.hpp"

void FASTCALL CHooked::OverrideView( void* pEcx, void* pEdx, CViewSetup* pSetupView )
{
	static auto oOverrideView = DTR::OverrideView.GetOriginal<decltype( &OverrideView )>( );

	if ( !Globals->m_pLocal )
		return oOverrideView( pEcx, pEdx, pSetupView );

	if ( !Globals->m_pLocal->IsAlive( ) )
	{
		Source->Interfaces.m_pInput->m_bCameraInThirdPerson = false;
		return oOverrideView( pEcx, pEdx, pSetupView );
	}

	ThirdPerson->Instance( );
	return oOverrideView( pEcx, pEdx, pSetupView );
}
