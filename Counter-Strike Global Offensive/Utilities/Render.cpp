#include "Render.hpp"
#include "InputManager.hpp"
#include "../Core/Source.hpp"

#pragma region draw_get
void CRender::Create( IDirect3DDevice9* pDevice, unsigned int uFontFlags )
{
	ImGui::CreateContext( );

	ImGui_ImplWin32_Init( InputManager.m_hWindow );
	ImGui_ImplDX9_Init( pDevice );

#pragma region draw_style
	ImGuiStyle& style = ImGui::GetStyle( );
	style.Alpha = 1.0f;
	style.WindowPadding = ImVec2( 8, 8 );
	style.WindowRounding = 4.0f;
	style.WindowBorderSize = 1.0f;
	style.WindowMinSize = ImVec2( 32, 32 );
	style.WindowTitleAlign = ImVec2( 0.5f, 0.5f );
	style.ChildRounding = 4.0f;
	style.ChildBorderSize = 1.0f;
	style.PopupRounding = 4.0f;
	style.PopupBorderSize = 1.0f;
	style.FramePadding = ImVec2( 4, 2 );
	style.FrameRounding = 2.0f;
	style.FrameBorderSize = 1.0f;
	style.ItemSpacing = ImVec2( 8, 4 );
	style.ItemInnerSpacing = ImVec2( 4, 4 );
	style.IndentSpacing = 6.0f;
	style.ColumnsMinSpacing = 6.0f;
	style.ScrollbarSize = 6.0f;
	style.ScrollbarRounding = 9.0f;
	style.GrabMinSize = 0.0f;
	style.GrabRounding = 4.0f;
	style.TabRounding = 4.0f;
	style.TabBorderSize = 1.0f;
	style.ButtonTextAlign = ImVec2( 0.5f, 0.5f );
	style.SelectableTextAlign = ImVec2( 0.0f, 0.5f );
	style.MouseCursorScale = 0.75f;
#pragma endregion

#pragma region draw_style_color
	style.Colors[ ImGuiCol_Text ] = ImVec4( 1.00f, 1.00f, 1.00f, 1.00f );					// primtv 0
	style.Colors[ ImGuiCol_TextDisabled ] = ImVec4( 0.75f, 0.75f, 0.75f, 0.85f );			// primtv 2
	style.Colors[ ImGuiCol_TextSelectedBg ] = ImVec4( 0.22f, 0.00f, 0.40f, 0.85f );			// accent 1

	style.Colors[ ImGuiCol_WindowBg ] = ImVec4( 0.11f, 0.14f, 0.20f, 1.00f );				// primtv 3
	style.Colors[ ImGuiCol_ChildBg ] = ImVec4( 0.08f, 0.08f, 0.12f, 0.60f );				// primtv 1
	style.Colors[ ImGuiCol_PopupBg ] = ImVec4( 0.08f, 0.08f, 0.12f, 0.85f );				// primtv 1

	style.Colors[ ImGuiCol_Border ] = ImVec4( 0.00f, 0.00f, 0.00f, 0.10f );					// primtv 4
	style.Colors[ ImGuiCol_BorderShadow ] = ImVec4( 0.00f, 0.00f, 0.00f, 0.00f );			// clear

	style.Colors[ ImGuiCol_FrameBg ] = ImVec4( 0.11f, 0.14f, 0.20f, 1.00f );				// primtv 3
	style.Colors[ ImGuiCol_FrameBgHovered ] = ImVec4( 0.22f, 0.00f, 0.40f, 1.00f );			// accent 1
	style.Colors[ ImGuiCol_FrameBgActive ] = ImVec4( 0.55f, 0.15f, 0.90f, 1.00f );			// accent 0

	style.Colors[ ImGuiCol_TitleBg ] = ImVec4( 0.55f, 0.15f, 0.90f, 0.20f );				// accent 0
	style.Colors[ ImGuiCol_TitleBgActive ] = ImVec4( 0.22f, 0.00f, 0.40f, 0.50f );			// accent 1
	style.Colors[ ImGuiCol_TitleBgCollapsed ] = ImVec4( 0.22f, 0.00f, 0.40f, 0.20f );		// accent 1

	style.Colors[ ImGuiCol_MenuBarBg ] = ImVec4( 0.08f, 0.08f, 0.12f, 0.70f );				// primtv 1

	style.Colors[ ImGuiCol_ScrollbarBg ] = ImVec4( 0.11f, 0.14f, 0.20f, 0.30f );			// primtv 3
	style.Colors[ ImGuiCol_ScrollbarGrab ] = ImVec4( 0.30f, 0.20f, 0.40f, 1.00f );			// accent 3
	style.Colors[ ImGuiCol_ScrollbarGrabHovered ] = ImVec4( 0.30f, 0.30f, 0.30f, 0.90f );	// primtv 5
	style.Colors[ ImGuiCol_ScrollbarGrabActive ] = ImVec4( 0.75f, 0.75f, 0.75f, 0.10f );	// primtv 2

	style.Colors[ ImGuiCol_CheckMark ] = ImVec4( 0.55f, 0.15f, 0.90f, 1.00f );				// accent 0

	style.Colors[ ImGuiCol_SliderGrab ] = ImVec4( 0.55f, 0.15f, 0.90f, 1.00f );				// accent 0
	style.Colors[ ImGuiCol_SliderGrabActive ] = ImVec4( 0.22f, 0.00f, 0.40f, 1.00f );		// accent 1

	style.Colors[ ImGuiCol_Button ] = ImVec4( 0.11f, 0.14f, 0.20f, 1.00f );					// primtv 3
	style.Colors[ ImGuiCol_ButtonHovered ] = ImVec4( 0.30f, 0.30f, 0.30f, 1.00f );			// primtv 5
	style.Colors[ ImGuiCol_ButtonActive ] = ImVec4( 0.55f, 0.15f, 0.90f, 1.00f );			// accent 0

	style.Colors[ ImGuiCol_Header ] = ImVec4( 0.55f, 0.15f, 0.90f, 1.00f );					// accent 0
	style.Colors[ ImGuiCol_HeaderHovered ] = ImVec4( 0.30f, 0.30f, 0.30f, 1.00f );			// primtv 5
	style.Colors[ ImGuiCol_HeaderActive ] = ImVec4( 0.11f, 0.14f, 0.20f, 1.00f );			// primtv 3

	style.Colors[ ImGuiCol_Separator ] = ImVec4( 0.11f, 0.14f, 0.20f, 1.00f );				// primtv 3
	style.Colors[ ImGuiCol_SeparatorHovered ] = ImVec4( 0.30f, 0.30f, 0.30f, 1.00f );		// primtv 5
	style.Colors[ ImGuiCol_SeparatorActive ] = ImVec4( 0.55f, 0.15f, 0.90f, 1.00f );		// accent 0

	style.Colors[ ImGuiCol_ResizeGrip ] = ImVec4( 0.55f, 0.15f, 0.90f, 1.00f );				// accent 0
	style.Colors[ ImGuiCol_ResizeGripHovered ] = ImVec4( 0.30f, 0.30f, 0.30f, 0.70f );		// primtv 5
	style.Colors[ ImGuiCol_ResizeGripActive ] = ImVec4( 0.22f, 0.00f, 0.40f, 1.00f );		// accent 1

	style.Colors[ ImGuiCol_Tab ] = ImVec4( 0.08f, 0.08f, 0.12f, 0.80f );					// primtv 1
	style.Colors[ ImGuiCol_TabHovered ] = ImVec4( 0.30f, 0.30f, 0.30f, 0.80f );				// primtv 5
	style.Colors[ ImGuiCol_TabActive ] = ImVec4( 0.55f, 0.15f, 0.90f, 0.70f );				// accent 0
	style.Colors[ ImGuiCol_TabUnfocused ] = ImVec4( 0.30f, 0.30f, 0.30f, 0.70f );			// primtv 5
	style.Colors[ ImGuiCol_TabUnfocusedActive ] = ImVec4( 0.55f, 0.15f, 0.90f, 0.60f );		// accent 0

	style.Colors[ ImGuiCol_PlotLines ] = ImVec4( 0.55f, 0.15f, 0.90f, 1.00f );				// accent 0
	style.Colors[ ImGuiCol_PlotLinesHovered ] = ImVec4( 0.55f, 0.15f, 0.90f, 0.50f );		// accent 0
	style.Colors[ ImGuiCol_PlotHistogram ] = ImVec4( 0.55f, 0.15f, 0.90f, 1.00f );			// accent 0
	style.Colors[ ImGuiCol_PlotHistogramHovered ] = ImVec4( 0.55f, 0.15f, 0.90f, 0.50f );	// accent 0

	style.Colors[ ImGuiCol_DragDropTarget ] = ImVec4( 0.30f, 0.20f, 0.40f, 0.80f );			// accent 3
	style.Colors[ ImGuiCol_ModalWindowDimBg ] = ImVec4( 0.00f, 0.00f, 0.00f, 0.25f );		// primtv 4
#pragma endregion

	m_bInitialized = true;
}

void CRender::Destroy( )
{
	ImGui_ImplDX9_Shutdown( );
	ImGui_ImplWin32_Shutdown( );

	ImGui::DestroyContext( );
}

void CRender::RenderDrawData( ImDrawList* pDrawList )
{
	std::unique_lock<std::shared_mutex> lock( m_DrawMutex );

	if ( !Source.Interfaces.m_pEngine->IsInGame( ) )
		return;

	if ( m_vecSafeDrawData.empty( ) )
		return;

	for ( const auto& data : m_vecSafeDrawData )
	{
		if ( !data.m_pObject.has_value( ) )
			continue;

		switch ( data.m_nType )
		{
		case EDrawType::LINE:
		{
			const auto& pObject = std::any_cast< LineObject_t >( data.m_pObject );
			pDrawList->AddLine( pObject.m_vecStart, pObject.m_vecEnd, pObject.m_colLine, pObject.m_flThickness );
			break;
		}
		case EDrawType::RECT:
		{
			const auto& pObject = std::any_cast< RectObject_t >( data.m_pObject );
			AddDrawListRect( pDrawList, pObject.m_vecMin, pObject.m_vecMax, pObject.m_colRect, pObject.m_uFlags, pObject.m_colOutline, pObject.m_flRounding, pObject.m_RoundingCorners, pObject.m_flThickness );
			break;
		}
		case EDrawType::RECT_MULTICOLOR:
		{
			const auto& pObject = std::any_cast< RectMultiColorObject_t >( data.m_pObject );
			pDrawList->AddRectFilledMultiColor( pObject.m_vecMin, pObject.m_vecMax, pObject.m_colUpperLeft, pObject.m_colUpperRight, pObject.m_colBottomRight, pObject.m_colBottomLeft );
			break;
		}
		case EDrawType::CIRCLE:
		{
			const auto& pObject = std::any_cast< CircleObject_t >( data.m_pObject );

			if ( pObject.m_uFlags & DRAW_CIRCLE_FILLED )
				pDrawList->AddCircleFilled( pObject.m_vecCenter, pObject.m_flRadius, pObject.m_colCircle, pObject.m_nSegments );
			else
				pDrawList->AddCircle( pObject.m_vecCenter, pObject.m_flRadius, pObject.m_colCircle, pObject.m_nSegments, pObject.m_flThickness );

			if ( pObject.m_uFlags & DRAW_CIRCLE_OUTLINE )
				pDrawList->AddCircle( pObject.m_vecCenter, pObject.m_flRadius + 1.0f, pObject.m_colOutline, pObject.m_nSegments, pObject.m_flThickness + 1.0f );

			break;
		}
		case EDrawType::TRIANGLE:
		{
			const auto& pObject = std::any_cast< TriangleObject_t >( data.m_pObject );

			if ( pObject.m_uFlags & DRAW_TRIANGLE_FILLED )
				pDrawList->AddTriangleFilled( pObject.m_vecFirst, pObject.m_vecSecond, pObject.m_vecThird, pObject.m_colTriangle );
			else
				pDrawList->AddTriangle( pObject.m_vecFirst, pObject.m_vecSecond, pObject.m_vecThird, pObject.m_colTriangle, pObject.m_flThickness );

			if ( pObject.m_uFlags & DRAW_TRIANGLE_OUTLINE )
				pDrawList->AddTriangle( pObject.m_vecFirst, pObject.m_vecSecond, pObject.m_vecThird, pObject.m_colOutline, pObject.m_flThickness + 1.0f );

			break;
		}
		case EDrawType::POLYGON:
		{
			const auto& pObject = std::any_cast< PolygonObject_t >( data.m_pObject );

			if ( pObject.m_uFlags & DRAW_POLYGON_FILLED )
				pDrawList->AddConvexPolyFilled( pObject.m_vecPoints.data( ), pObject.m_vecPoints.size( ), pObject.m_colPolygon );
			else
				pDrawList->AddPolyline( pObject.m_vecPoints.data( ), pObject.m_vecPoints.size( ), pObject.m_colPolygon, pObject.m_bClosed, pObject.m_flThickness );

			if ( pObject.m_uFlags & DRAW_POLYGON_OUTLINE )
				pDrawList->AddPolyline( pObject.m_vecPoints.data( ), pObject.m_vecPoints.size( ), pObject.m_colOutline, pObject.m_bClosed, pObject.m_flThickness + 1.0f );

			break;
		}
		case EDrawType::TEXT:
		{
			const auto& pObject = std::any_cast< TextObject_t >( data.m_pObject );
			AddDrawListText( pDrawList, pObject.m_pFont, pObject.m_flFontSize, pObject.m_vecPosition, pObject.m_szText, pObject.m_colText, pObject.m_uFlags, pObject.m_colOutline );
			break;
		}
		case EDrawType::IMAGE:
		{
			const auto& pObject = std::any_cast< ImageObject_t >( data.m_pObject );
			pDrawList->AddImageRounded( pObject.m_pTexture, pObject.m_vecMin, pObject.m_vecMax, ImVec2( 0, 0 ), ImVec2( 1, 1 ), pObject.m_colImage, pObject.m_flRounding, pObject.m_RoundingCorners );
			break;
		}
		default:
			break;
		}
	}
}

void CRender::ClearDrawData( )
{
	if ( !m_vecDrawData.empty( ) )
		m_vecDrawData.clear( );
}

void CRender::SwapDrawData( )
{
	std::unique_lock<std::shared_mutex> lock( m_DrawMutex );
	m_vecDrawData.swap( m_vecSafeDrawData );
}
#pragma endregion

#pragma region draw_render
void CRender::AddLine( const ImVec2& vecStart, const ImVec2& vecEnd, const Color& colLine, float flThickness )
{
	m_vecDrawData.emplace_back( EDrawType::LINE, std::make_any<LineObject_t>( vecStart, vecEnd, colLine.GetU32( ), flThickness ) );
}

void CRender::AddRect( const ImVec2& vecMin, const ImVec2& vecMax, const Color& colRect, unsigned int uFlags, const Color& colOutline, float flRounding, ImDrawCornerFlags roundingCorners, float flThickness )
{
	m_vecDrawData.emplace_back( EDrawType::RECT, std::make_any<RectObject_t>( vecMin, vecMax, colRect.GetU32( ), uFlags, colOutline.GetU32( ), flRounding, roundingCorners, flThickness ) );
}

void CRender::AddRectMultiColor( const ImVec2& vecMin, const ImVec2& vecMax, const Color& colUpperLeft, const Color& colUpperRight, const Color& colBottomRight, const Color& colBottomLeft )
{
	m_vecDrawData.emplace_back( EDrawType::RECT_MULTICOLOR, std::make_any<RectMultiColorObject_t>( vecMin, vecMax, colUpperLeft.GetU32( ), colUpperRight.GetU32( ), colBottomRight.GetU32( ), colBottomLeft.GetU32( ) ) );
}

void CRender::AddCircle( const ImVec2& vecCenter, float flRadius, const Color& colCircle, int nSegments, unsigned int uFlags, const Color& colOutline, float flThickness )
{
	m_vecDrawData.emplace_back( EDrawType::CIRCLE, std::make_any<CircleObject_t>( vecCenter, flRadius, colCircle.GetU32( ), nSegments, uFlags, colOutline.GetU32( ), flThickness ) );
}

void CRender::AddTriangle( const ImVec2& vecFirst, const ImVec2& vecSecond, const ImVec2& vecThird, const Color& colTriangle, unsigned int uFlags, const Color& colOutline, float flThickness )
{
	m_vecDrawData.emplace_back( EDrawType::TRIANGLE, std::make_any<TriangleObject_t>( vecFirst, vecSecond, vecThird, colTriangle.GetU32( ), uFlags, colOutline.GetU32( ), flThickness ) );
}

void CRender::AddPolygon( std::vector<ImVec2>& vecPoints, const Color& colPolygon, unsigned int uFlags, const Color& colOutline, bool bClosed, float flThickness )
{
	m_vecDrawData.emplace_back( EDrawType::POLYGON, std::make_any<PolygonObject_t>( std::move( vecPoints ), colPolygon.GetU32( ), uFlags, colOutline.GetU32( ), bClosed, flThickness ) );
}

void CRender::AddText( const ImFont* pFont, float flFontSize, const ImVec2& vecPosition, const std::string& szText, const Color& colText, unsigned int uFlags, const Color& colOutline )
{
	if ( pFont->ContainerAtlas == nullptr )
		return;

	IM_ASSERT( ImIsPowerOfTwo( uFlags == DRAW_TEXT_NONE || uFlags & ( DRAW_TEXT_DROPSHADOW | DRAW_TEXT_OUTLINE ) ) );
	m_vecDrawData.emplace_back( EDrawType::TEXT, std::make_any<TextObject_t>( pFont, flFontSize, vecPosition, szText, colText.GetU32( ), uFlags, colOutline.GetU32( ) ) );
}

void CRender::AddText( const ImVec2& vecPosition, const std::string& szText, const Color& colText, int iFlags, const Color& colOutline )
{
	AddText( nullptr, 0.f, vecPosition, szText, colText, iFlags, colOutline );
}

void CRender::AddImage( ImTextureID pTexture, const ImVec2& vecMin, const ImVec2& vecMax, const Color& colImage, float flRounding, ImDrawCornerFlags roundingCorners )
{
	m_vecDrawData.emplace_back( EDrawType::IMAGE, std::make_any<ImageObject_t>( pTexture, vecMin, vecMax, colImage.GetU32( ), flRounding, roundingCorners ) );
}
#pragma endregion

#pragma region draw_bindings
void CRender::AddDrawListRect( ImDrawList* pDrawList, const ImVec2& vecMin, const ImVec2& vecMax, ImU32 colRect, unsigned int uFlags, ImU32 colOutline, float flRounding, ImDrawCornerFlags roundingCorners, float flThickness )
{
	if ( uFlags & DRAW_RECT_FILLED )
		pDrawList->AddRectFilled( vecMin, vecMax, colRect, flRounding, roundingCorners );
	else
		pDrawList->AddRect( vecMin, vecMax, colRect, flRounding, roundingCorners, flThickness );

	if ( uFlags & DRAW_RECT_BORDER )
		pDrawList->AddRect( ImVec2( vecMin.x + 1.f, vecMin.y + 1.f ), ImVec2( vecMin.x - 1.f, vecMin.y - 1.f ), colOutline, flRounding, roundingCorners, 1.0f );

	if ( uFlags & DRAW_RECT_OUTLINE )
		pDrawList->AddRect( ImVec2( vecMin.x - 1.f, vecMin.y - 1.f ), ImVec2( vecMin.x + 1.f, vecMin.y + 1.f ), colOutline, flRounding, roundingCorners, 1.0f );
}

void CRender::AddDrawListText( ImDrawList* pDrawList, const ImFont* pFont, float flFontSize, const ImVec2& vecPosition, const std::string& szText, ImU32 colText, unsigned int uFlags, ImU32 colOutline )
{
	pDrawList->PushTextureID( pFont->ContainerAtlas->TexID );

	if ( uFlags & DRAW_TEXT_DROPSHADOW )
		pDrawList->AddText( pFont, flFontSize, ImVec2( vecPosition.x + 1.f, vecPosition.y - 1.f ), colOutline, szText.c_str( ) );
	else if ( uFlags & DRAW_TEXT_OUTLINE )
	{
		pDrawList->AddText( pFont, flFontSize, ImVec2( vecPosition.x + 1.f, vecPosition.y - 1.f ), colOutline, szText.c_str( ) );
		pDrawList->AddText( pFont, flFontSize, ImVec2( vecPosition.x - 1.f, vecPosition.y + 1.f ), colOutline, szText.c_str( ) );
	}

	pDrawList->AddText( pFont, flFontSize, vecPosition, colText, szText.data( ) );
	pDrawList->PopTextureID( );
}
#pragma endregion