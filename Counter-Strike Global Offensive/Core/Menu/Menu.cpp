#include "Menu.hpp"

void CMenu::MainWindow( IDirect3DDevice9* pDevice )
{
	if ( !m_bMainOpened )
		return;

	ImGuiIO& IO = ImGui::GetIO( );
	ImVec2 vecScreenSize = IO.DisplaySize;

	ImGui::SetNextWindowSize( ImVec2( 350, 250 ), ImGuiCond_Always );
	ImGui::SetNextWindowPos( ImVec2( vecScreenSize.x * 0.5f, vecScreenSize.y * 0.5f ), ImGuiCond_Once, ImVec2( 0.5f, 0.5f ) );

	ImGui::Begin( "Counter-Strike Global Offensive" , &m_bMainOpened, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse | ImGuiWindowFlags_NoCollapse );
	{
		static bool bAntiAimEnable = false;
		static bool bMiscEnable = false;

		ImGui::BeginChild( "AntiAim", ImVec2( ), true, ImGuiWindowFlags_MenuBar );
		{
			ImGui::Checkbox( "Enable", &bAntiAimEnable );
		}
		ImGui::EndChild( );
	}
	ImGui::End( );
}