#include "Menu.hpp"
#include "../Variables/Variables.hpp"

void CMenu::MainWindow( )
{
	if ( !m_bMainOpened )
		return;

	ImGuiIO& IO = ImGui::GetIO( );
	ImGuiStyle& Style = ImGui::GetStyle( );

	ImVec2 vecScreenSize = IO.DisplaySize;

	ImGui::SetNextWindowSize( ImVec2( 345, 290 ), ImGuiCond_Always );
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
		ImGui::Checkbox( "Enable", &Variables->Parametrs.AntiAim.m_bEnable );
		ImGui::Combo( "Pitch", &Variables->Parametrs.AntiAim.m_iPitch, "None\0Up\0Down\0" );
		ImGui::Combo( "Yaw", &Variables->Parametrs.AntiAim.m_iYaw, "None\0Left\0Right\0Back\0" );
		ImGui::SliderInt( "Roll", &Variables->Parametrs.AntiAim.m_iRoll, -50, 50 );
		ImGui::SliderInt( "Desync", &Variables->Parametrs.AntiAim.m_iDesync, 0, 58 );
		ImGui::HotKey( "Desync switch", &Variables->Parametrs.AntiAim.m_DesyncFlipKey.m_iKeySelected, &Variables->Parametrs.AntiAim.m_DesyncFlipKey.m_iModeSelected );
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
	static int iPlayers{ };

	ImGui::BeginChild( "Main", ImVec2( ), true );
	{
		ImGui::Checkbox( "Enable", &Variables->Parametrs.PlayerESP.m_bEnable );

		ImGui::Combo( "Players", &iPlayers, "Local\0Team\0Enemy\0" );
		ImGui::Checkbox( "Box", &Variables->Parametrs.PlayerESP.Players[ iPlayers ].m_bBox );
		ImGui::Checkbox( "Name", &Variables->Parametrs.PlayerESP.Players[ iPlayers ].m_bName );
		ImGui::Checkbox( "Health", &Variables->Parametrs.PlayerESP.Players[ iPlayers ].m_bHealth );
		ImGui::Checkbox( "Ammo", &Variables->Parametrs.PlayerESP.Players[ iPlayers ].m_bAmmo );
	}
	ImGui::EndChild( );
}

void CMenu::RenderMisc( )
{
	ImGui::Columns( 2, nullptr, false );
	{
		ImGui::BeginChild( "Main", ImVec2( ), true );
		{
			ImGui::Checkbox( "Bunny hop", &Variables->Parametrs.Misc.m_bBunnyHop );
			ImGui::Checkbox( "Fake lag", &Variables->Parametrs.Misc.m_bFakeLag );
			ImGui::Checkbox( "Third person", &Variables->Parametrs.Misc.m_bThirdPerson );
		}
		ImGui::EndChild( );

		ImGui::NextColumn( );

		ImGui::BeginChild( "Configs", ImVec2( ), true );
		{
			if ( ImGui::Button( "Save config" ) )
				Variables->Save( );

			if ( ImGui::Button( "Load Config" ) )
				Variables->Load( );
		}
		ImGui::EndChild( );
	}
	ImGui::Columns( 1 );
}
#pragma endregion