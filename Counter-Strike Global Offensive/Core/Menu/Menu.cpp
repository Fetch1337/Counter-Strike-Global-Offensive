#include "Menu.hpp"
#include "../Variables/Variables.hpp"

void CMenu::MainWindow( )
{
	if ( !m_bMainOpened )
		return;

	ImGuiIO& IO = ImGui::GetIO( );
	ImGuiStyle& Style = ImGui::GetStyle( );

	ImVec2 vecScreenSize = IO.DisplaySize;

	ImGui::SetNextWindowSize( ImVec2( 370, 300 ), ImGuiCond_Always );
	ImGui::SetNextWindowPos( ImVec2( vecScreenSize.x * 0.5f, vecScreenSize.y * 0.5f ), ImGuiCond_Once, ImVec2( 0.5f, 0.5f ) );

	ImGui::Begin( "Counter-Strike Global Offensive" , &m_bMainOpened, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse );
	{
		static std::array<CMenuTab, 6U> const arrTabs =
		{
			CMenuTab{ "Rage", &RenderRage },
			CMenuTab{ "Legit", &RenderLegit },
			CMenuTab{ "Anti-aim", &RenderAnitAim },
			CMenuTab{ "World ESP", &RenderWorldESP },
			CMenuTab{ "Player ESP", &RenderPlayerESP },
			CMenuTab{ "Misc", &RenderMisc }
		};

		RenderTabs<arrTabs.size( )>( "Menu Tabs", arrTabs, &m_iSelectedTab, Style.Colors[ImGuiCol_TabActive] );
	}
	ImGui::End( );
}

#pragma region menu_tabs
template <std::size_t S>
void CMenu::RenderTabs( const char* szTabBar, const std::array<CMenuTab, S> arrTabs, int* nCurrentTab, const ImVec4& colActive, ImGuiTabBarFlags flags )
{
	if ( arrTabs.empty( ) )
		return;

	ImGui::PushStyleColor( ImGuiCol_TabActive, colActive );

	if ( ImGui::BeginTabBar( szTabBar, flags ) )
	{
		for ( std::size_t i = 0U; i < arrTabs.size( ); i++ )
		{
			if ( ImGui::BeginTabItem( arrTabs.at( i ).m_szName ) )
			{
				*nCurrentTab = i;
				ImGui::EndTabItem( );
			}
		}

		if ( arrTabs.at( *nCurrentTab ).m_pRenderFunction != nullptr )
			arrTabs.at( *nCurrentTab ).m_pRenderFunction( );

		ImGui::EndTabBar( );
	}
	ImGui::PopStyleColor( );
}

void CMenu::RenderRage( )
{
	ImGui::BeginChild( "Main", ImVec2( ), true );
	{

	}
	ImGui::EndChild( );
}

void CMenu::RenderLegit( )
{
	ImGui::BeginChild( "Main", ImVec2( ), true );
	{

	}
	ImGui::EndChild( );
}

void CMenu::RenderAnitAim( )
{
	ImGui::BeginChild( "Main", ImVec2( ), true );
	{
		ImGui::Checkbox( "Enable", &Variables.Parametrs.m_bAntiAimEnable );
		ImGui::Combo( "Pitch", &Variables.Parametrs.m_iAntiAimPitch, "None\0Up\0Down\0" );
		ImGui::Combo( "Yaw", &Variables.Parametrs.m_iAntiAimYaw, "None\0Left\0Right\0Back\0" );
		ImGui::SliderInt( "Roll", &Variables.Parametrs.m_iAntiAimRoll, -50, 50 );
	}
	ImGui::EndChild( );
}

void CMenu::RenderWorldESP( )
{
	ImGui::BeginChild( "Main", ImVec2( ), true );
	{

	}
	ImGui::EndChild( );
}

void CMenu::RenderPlayerESP( )
{
	ImGui::BeginChild( "Main", ImVec2( ), true );
	{

	}
	ImGui::EndChild( );
}

void CMenu::RenderMisc( )
{
	ImGui::Columns( 2, nullptr, false );
	{
		ImGui::BeginChild( "Main", ImVec2( ), true );
		{
			ImGui::Checkbox( "Bunny hop", &Variables.Parametrs.m_bMiscBunnyHop );
			ImGui::Checkbox( "Third person", &Variables.Parametrs.m_bMiscThirdPerson );
		}
		ImGui::EndChild( );

		ImGui::NextColumn( );

		ImGui::BeginChild( "Configs", ImVec2( ), true );
		{
			if ( ImGui::Button( "Save config" ) )
				Variables.Save( );

			if ( ImGui::Button( "Load Config" ) )
				Variables.Load( );
		}
		ImGui::EndChild( );
	}
	ImGui::Columns( 1 );
}
#pragma endregion