#pragma once
#include "../../Utilities/Render.hpp"

class CMenu
{
public:
	void MainWindow( IDirect3DDevice9* pDevice );

	bool m_bMainOpened = false;
};

inline CMenu Menu;