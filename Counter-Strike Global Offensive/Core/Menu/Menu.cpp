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
		ImGui::BeginChild( "Main", ImVec2( ), true );
		{
			ImGui::Checkbox( "Checkbox", &Variables.Parametrs.m_bCheckbox );
			ImGui::SliderInt( "Slider int", &Variables.Parametrs.m_SliderInt, 0, 100 );
			ImGui::SliderFloat( "Slider float", &Variables.Parametrs.m_SliderFloat, 0.0f, 100.0f );

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