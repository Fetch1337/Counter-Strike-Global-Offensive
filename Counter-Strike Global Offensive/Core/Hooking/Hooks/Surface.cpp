#include "../Hooks.hpp"
#include "../../Source.hpp"
#include "../../../Utilities/InputManager.hpp"
#include "../../../Utilities/Render.hpp"
#include "../../Menu/Menu.hpp"

void FASTCALL CHooked::PaintTraverse( void* pEcx, void* pEdx, unsigned int vguiPanel, bool bForceRepaint, bool bAllowForce )
{
	static auto oPaintTraverse = DTR::PaintTraverse.GetOriginal<decltype( &PaintTraverse )>( );
	oPaintTraverse( pEcx, pEdx, vguiPanel, bForceRepaint, bAllowForce );

	if ( Source.Interfaces.m_pPanel->GetName( vguiPanel ) == "FocusOverlayPanel" )
	{
		Render.ClearDrawData( );

		// TODO: store data to render

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