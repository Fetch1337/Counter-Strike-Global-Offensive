#pragma once
#include <functional>
#include "../../Utilities/Render.hpp"

enum class EMenuTabs : int
{
	RAGE,
	LEGIT,
	ANTIAIM,
	WORLD_ESP,
	PLAYER_ESP,
	MISC
};

class CMenuTab
{
public:
	const char* m_szName = nullptr;
	std::function<void( )> m_pRenderFunction = nullptr;
};

class CMenu
{
public:
	void MainWindow( );

private:
	template <std::size_t S>
	void RenderTabs( const char* szTabBar, const std::array<CMenuTab, S> arrTabs, int* nCurrentTab, const ImVec4& colActive, ImGuiTabBarFlags flags = ImGuiTabBarFlags_Reorderable | ImGuiTabBarFlags_NoCloseWithMiddleMouseButton | ImGuiTabBarFlags_NoTooltip );

	static void RenderRage( );
	static void RenderLegit( );
	static void RenderAnitAim( );
	static void RenderWorldESP( );
	static void RenderPlayerESP( );
	static void RenderMisc( );

	int m_iSelectedTab = 0;
	int m_iSelectedSubTab = 0;

public:
	bool m_bMainOpened = false;
};

inline CMenu Menu;