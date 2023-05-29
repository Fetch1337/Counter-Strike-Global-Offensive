#include "../Hooks.hpp"
#include "../../Source.hpp"
#include "../../../Utilities/InputManager.hpp"
#include "../../../Utilities/Render.hpp"
#include "../../../Features/Visuals/WorldESP.hpp"
#include "../../../Features/Visuals/PlayerESP.hpp"
#include "../../Menu/Menu.hpp"

void FASTCALL CHooked::PaintTraverse( void* pEcx, void* pEdx, unsigned int vguiPanel, bool bForceRepaint, bool bAllowForce )
{
	static auto oPaintTraverse = DTR::PaintTraverse.GetOriginal<decltype( &PaintTraverse )>( );
	oPaintTraverse( pEcx, pEdx, vguiPanel, bForceRepaint, bAllowForce );

	static unsigned int iDrawPanel = 0;
	if ( !iDrawPanel )
	{
		const char* szPanelName = Source.Interfaces.m_pPanel->GetName( vguiPanel );

		if ( szPanelName[ 0 ] == 'M' && szPanelName[ 2 ] == 't' )
			iDrawPanel = vguiPanel;
	}

	if ( vguiPanel == iDrawPanel )
	{
		Render.ClearDrawData( );
		WorldESP.Instance( );
		PlayerESP.Instance( );
		Render.SwapDrawData( );
	}
}

void FASTCALL CHooked::LockCursor( void* pEcx, void* pEdx )
{
	static auto oLockCursor = DTR::LockCursor.GetOriginal<decltype( &LockCursor )>( );

	if ( Menu.m_bMainOpened )
	{
		Source.Interfaces.m_pSurface->UnLockCursor( );
		return;
	}

	oLockCursor( pEcx, pEdx );
}