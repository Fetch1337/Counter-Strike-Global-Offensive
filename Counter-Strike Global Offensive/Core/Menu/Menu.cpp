#include "Menu.hpp"
#include "../Variables/Variables.hpp"

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
		ImGui::BeginChild( "AntiAim", ImVec2( ), true );
		{
			ImGui::Checkbox( "Enable", &Variables.Parametrs.m_bAntiAimEnable );
			ImGui::Combo( "Pitch", &Variables.Parametrs.m_iAntiAimPitch,"None\0Up\0Down\0" );
			ImGui::Combo( "Yaw", &Variables.Parametrs.m_iAntiAimYaw,"None\0Left\0Right\0Back\0" );

			if ( ImGui::Button( "Save config" ) )
				Variables.Save( );

			ImGui::SameLine( );

			if ( ImGui::Button( "Load Config" ) )
				Variables.Load( );
		}
		ImGui::EndChild( );
	}
	ImGui::End( );
}