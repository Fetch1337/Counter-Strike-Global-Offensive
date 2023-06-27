#include "../Hooks.hpp"
#include "../../Source.hpp"
#include "../../../Utilities/InputManager.hpp"
#include "../../../Utilities/Render.hpp"
#include "../../Menu/Menu.hpp"

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler( HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam );

long D3DAPI CHooked::Reset( IDirect3DDevice9* pDevice, D3DPRESENT_PARAMETERS* pPresentationParameters )
{
	static auto oReset = DTR::Reset.GetOriginal<decltype( &Reset )>( );

	if ( !Render->m_bInitialized )
		return oReset( pDevice, pPresentationParameters );

	ImGui_ImplDX9_InvalidateDeviceObjects( );

	if ( oReset( pDevice, pPresentationParameters ) == D3D_OK )
		ImGui_ImplDX9_CreateDeviceObjects( );

	return oReset( pDevice, pPresentationParameters );
}

long D3DAPI CHooked::Present( IDirect3DDevice9* pDevice, RECT* pRect, RECT* pDestRect, HWND DestHwndOverride, RGNDATA* pDirtyRegion )
{
	static auto oPresent = DTR::Present.GetOriginal<decltype( &Present )>( );

	if ( !Render->m_bInitialized )
		Render->Create( pDevice );

	IDirect3DVertexDeclaration9* pVertDec;
	pDevice->GetVertexDeclaration( &pVertDec );

	IDirect3DVertexShader9* pVertShader;
	pDevice->GetVertexShader( &pVertShader );

	ImGui_ImplDX9_NewFrame( );
	ImGui_ImplWin32_NewFrame( );
	ImGui::NewFrame( );

	Render->RenderDrawData( ImGui::GetBackgroundDrawList( ) );
	Menu->MainWindow( );

	ImGui::EndFrame( );
	ImGui::Render( );

	ImGui_ImplDX9_RenderDrawData( ImGui::GetDrawData( ) );

	pDevice->SetVertexShader( pVertShader );
	pDevice->SetVertexDeclaration( pVertDec );

	return oPresent( pDevice, pRect, pDestRect, DestHwndOverride, pDirtyRegion );
}

long STDCALL CHooked::WndProc( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam )
{
	InputManager->Process( uMsg, wParam, lParam );

	Menu->m_bMainOpened = false;
	if ( InputManager->IsBindActive( CKeyBinds( VK_INSERT, ( int )EKeyMode::TOGGLE ) ) )
		Menu->m_bMainOpened = true;

	Source->Interfaces.m_pInputSystem->EnableInput( !Menu->m_bMainOpened );

	if ( Render->m_bInitialized && Menu->m_bMainOpened && ImGui_ImplWin32_WndProcHandler( hWnd, uMsg, wParam, lParam ) )
		return 1L;

	return CallWindowProcW( InputManager->m_pOldWndProc, hWnd, uMsg, wParam, lParam );
}