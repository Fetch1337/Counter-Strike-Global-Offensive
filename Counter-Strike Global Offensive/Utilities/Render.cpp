#include "Render.hpp"
#include "Math.hpp"
#include "InputManager.hpp"
#include "../../../SourceSDK/Objects/Entity.hpp"
#include "../../../SourceSDK/Objects/Player.hpp"
#include "../Core/Source.hpp"

#pragma region imgui_extended
static constexpr std::array<const char*, 166U> arrKeyNames =
{
	"",
	"Mouse 1", "Mouse 2", "Cancel", "Mouse 3", "Mouse 4", "Mouse 5", "",
	"Backspace", "Tab", "", "", "Clear", "Enter", "", "",
	"Shift", "Control", "Alt", "Pause", "Caps", "", "", "", "", "", "",
	"Escape", "", "", "", "", "Space", "Page up", "Page down",
	"End", "Home", "Left", "Up", "Right", "Down", "", "", "",
	"Print", "Insert", "Delete", "",
	"0", "1", "2", "3", "4", "5", "6", "7", "8", "9",
	"", "", "", "", "", "", "",
	"A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K",
	"L", "M", "N", "O", "P", "Q", "R", "S", "T", "U",
	"V", "W", "X", "Y", "Z", "LWin", "RWin", "", "", "",
	"Num0", "Num1", "Num2", "Num3", "Num4", "Num5",
	"Num6", "Num7", "Num8", "Num9",
	"*", "+", "", "-", ".", "/",
	"F1", "F2", "F3", "F4", "F5", "F6", "F7", "F8",
	"F9", "F10", "F11", "F12", "F13", "F14", "F15", "F16",
	"F17", "F18", "F19", "F20", "F21", "F22", "F23", "F24",
	"", "", "", "", "", "", "", "",
	"Num lock", "Scroll lock",
	"", "", "", "", "", "", "",
	"", "", "", "", "", "", "",
	"LShift", "RShift", "LCtrl",
	"RCtrl", "LMenu", "RMenu"
};

bool ImGui::HotKey( const char* szLabel, int* pValue, int* pMode )
{
	ImGuiContext& g = *GImGui;
	ImGuiWindow* pWindow = g.CurrentWindow;

	if ( pWindow->SkipItems )
		return false;

	ImGuiIO& io = g.IO;
	const ImGuiStyle& style = g.Style;
	const ImGuiID nIndex = pWindow->GetID( szLabel );

	const float flWidth = GetWindowWidth( );
	const float flHeight = GetFrameHeight( );

	const ImVec2 vecLabelSize = CalcTextSize( szLabel, nullptr, true );

	const ImRect rectFrame( pWindow->DC.CursorPos, pWindow->DC.CursorPos + ImVec2( flWidth, vecLabelSize.y + style.FramePadding.y * 2.0f ) );
	const ImRect rectTotal( rectFrame.Min, rectFrame.Max + ImVec2( vecLabelSize.x > 0.0f ? style.ItemInnerSpacing.x + vecLabelSize.x : 0.0f, 0.0f ) );

	ItemSize( rectTotal, style.FramePadding.y );
	if ( !ItemAdd( rectTotal, nIndex, &rectFrame ) )
		return false;

	const bool bHovered = ItemHoverable( rectFrame, nIndex );
	if ( bHovered )
	{
		SetHoveredID( nIndex );
		g.MouseCursor = ImGuiMouseCursor_TextInput;
	}

	const bool bClicked = bHovered && io.MouseClicked[ 0 ];
	const bool bStyleRequested = bHovered && io.MouseClicked[ 1 ];
	const bool bDoubleClicked = bHovered && g.IO.MouseDoubleClicked[ 0 ];
	if ( bClicked || bDoubleClicked )
	{
		if ( g.ActiveId != nIndex )
		{
			memset( io.MouseDown, 0, sizeof( io.MouseDown ) );
			memset( io.KeysDown, 0, sizeof( io.KeysDown ) );
			*pValue = 0;
		}

		SetActiveID( nIndex, pWindow );
		FocusWindow( pWindow );
	}

	bool bValueChanged = false;
	if ( int nKey = *pValue; g.ActiveId == nIndex )
	{
		for ( int n = 0; n < IM_ARRAYSIZE( io.MouseDown ); n++ )
		{
			if ( IsMouseDown( n ) )
			{
				switch ( n )
				{
				case 0:
					nKey = VK_LBUTTON;
					break;
				case 1:
					nKey = VK_RBUTTON;
					break;
				case 2:
					nKey = VK_MBUTTON;
					break;
				case 3:
					nKey = VK_XBUTTON1;
					break;
				case 4:
					nKey = VK_XBUTTON2;
					break;
				}

				bValueChanged = true;
				ClearActiveID( );
			}
		}

		if ( !bValueChanged )
		{
			for ( int n = VK_BACK; n <= VK_RMENU; n++ )
			{
				if ( IsKeyDown( ( ImGuiKey )n ) )
				{
					nKey = n;
					bValueChanged = true;
					ClearActiveID( );
				}
			}
		}

		if ( IsKeyPressed( ImGuiKey_Escape ) )
		{
			*pValue = 0;
			ClearActiveID( );
		}
		else
			*pValue = nKey;
	}
	else
	{
		if ( pMode )
		{
			bool bIsPopupOpen = IsPopupOpen( nIndex, ImGuiPopupFlags_None );

			if ( bStyleRequested && !bIsPopupOpen )
				OpenPopupEx( nIndex );

			if ( bIsPopupOpen ) {
				SetNextWindowSize( ImVec2( 100, CalcMaxPopupHeightFromItemCount( 3 ) ) );

				char szName[ 16 ];
				ImFormatString( szName, IM_ARRAYSIZE( szName ), "##Combo_%02d", g.BeginPopupStack.Size );

				if ( ImGuiWindow* pPopupWindow = FindWindowByName( szName ) )
				{
					if ( pPopupWindow->WasActive )
					{
						ImVec2 vecSizeExpected = CalcWindowNextAutoFitSize( pPopupWindow );
						ImRect vecOuter = GetPopupAllowedExtentRect( pPopupWindow );
						ImVec2 vecPos = FindBestWindowPosForPopupEx( rectFrame.GetBL( ), vecSizeExpected, &pPopupWindow->AutoPosLastDirection, vecOuter, rectFrame, ImGuiPopupPositionPolicy_ComboBox );
						SetNextWindowPos( vecPos );
					}
				}

				PushStyleVar( ImGuiStyleVar_WindowPadding, ImVec2( style.FramePadding.x, 0 ) );
				bool bRet = Begin( szName, NULL, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_Popup | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoSavedSettings );
				PopStyleVar( );

				ImGui::Spacing( );
				if ( Selectable( "Toggle", *pMode == 0 ) )
					*pMode = 0;

				if ( Selectable( "Hold", *pMode == 1 ) )
					*pMode = 1;

				if ( Selectable( "Always", *pMode == 2 ) )
					*pMode = 2;

				EndPopup( );
			}
		}
	}

	char chBuffer[ 64 ] = { };
	sprintf_s( chBuffer, sizeof( chBuffer ), "[ %s ]", *pValue != 0 && g.ActiveId != nIndex ? arrKeyNames.at( *pValue ) : g.ActiveId == nIndex ? "Press" : "None" );

	PushStyleVar( ImGuiStyleVar_FramePadding, ImVec2( style.FramePadding.x, -1 ) );
	pWindow->DrawList->AddText( ImVec2( rectFrame.Min.x + CalcTextSize( szLabel ).x + style.FramePadding.x, rectTotal.Min.y + style.FramePadding.y ), GetColorU32( g.ActiveId == nIndex ? ImGuiCol_Text : ImGuiCol_TextDisabled ), chBuffer );

	if ( vecLabelSize.x > 0.f )
		RenderText( ImVec2( rectTotal.Min.x, rectTotal.Min.y + style.FramePadding.y ), szLabel );

	PopStyleVar( );
	return bValueChanged;
}

bool ImGui::MultiCombo( const char* szLabel, std::vector<bool>& vecValues, const std::string_view* arrItems, int nItemsCount )
{
	ImGuiContext& g = *GImGui;
	ImGuiWindow* pWindow = g.CurrentWindow;

	if ( pWindow->SkipItems )
		return false;

	const ImGuiStyle& style = g.Style;
	const ImVec2 vecLabelSize = CalcTextSize( szLabel, nullptr, true );
	const float flActiveWidth = CalcItemWidth( ) - ( vecLabelSize.x > 0.0f ? style.ItemInnerSpacing.x + GetFrameHeight( ) : 0.0f );

	std::vector<std::string_view> vecActiveItems = { };

	for ( int i = 0; i < nItemsCount; i++ )
	{
		if ( vecValues[ i ] )
			vecActiveItems.push_back( arrItems[ i ] );
	}

	std::string szBuffer = { };
	for ( std::size_t i = 0U; i < vecActiveItems.size( ); i++ )
	{
		szBuffer.append( vecActiveItems[ i ] );

		if ( i < vecActiveItems.size( ) - 1U )
			szBuffer.append( ", " );
	}

	if ( szBuffer.empty( ) )
		szBuffer.assign( "None" );
	else
	{
		const char* szWrapPosition = g.Font->CalcWordWrapPositionA( GetCurrentWindow( )->FontWindowScale, &szBuffer[ 0 ], szBuffer.data( ) + szBuffer.length( ), flActiveWidth - style.FramePadding.x * 2.0f );
		const std::size_t nWrapLength = szWrapPosition - &szBuffer[ 0 ];

		if ( nWrapLength > 0U && nWrapLength < szBuffer.length( ) )
		{
			szBuffer.resize( nWrapLength );
			szBuffer.append( "..." );
		}
	}

	bool bValueChanged = false;
	if ( BeginCombo( szLabel, szBuffer.c_str( ) ) )
	{
		for ( int i = 0; i < nItemsCount; i++ )
		{
			if ( Selectable( arrItems[ i ].data( ), vecValues[ i ], ImGuiSelectableFlags_DontClosePopups ) )
			{
				vecValues[ i ] = !vecValues[ i ];
				bValueChanged = true;
			}
		}

		EndCombo( );
	}

	return bValueChanged;
}
#pragma endregion

#pragma region draw_get
void CRender::Create( IDirect3DDevice9* pDevice, unsigned int uFontFlags )
{
	ImGui::CreateContext( );

	ImGui_ImplWin32_Init( InputManager->m_hWindow );
	ImGui_ImplDX9_Init( pDevice );

	ImGui::StyleColorsDark( );

	ImGuiIO& IO = ImGui::GetIO( );

	constexpr ImWchar wRanges[] =
	{
		0x0020, 0x00FF, // Basic Latin + Latin Supplement
		0x0400, 0x052F, // Cyrillic + Cyrillic Supplement
		0x2DE0, 0x2DFF, // Cyrillic Extended-A
		0xA640, 0xA69F, // Cyrillic Extended-B
		0xE000, 0xE226, // icons
		0,
	};

	ImFontConfig imVerdanaConfig;
	imVerdanaConfig.GlyphRanges = wRanges;
	Fonts::pVerdana = IO.Fonts->AddFontFromFileTTF( "C:\\Windows\\Fonts\\Verdana.ttf", 14.f, &imVerdanaConfig, IO.Fonts->GetGlyphRangesCyrillic( ) );

	ImFontConfig imTahomaConfig;
	imTahomaConfig.GlyphRanges = wRanges;
	Fonts::pTahoma = IO.Fonts->AddFontFromFileTTF( "C:\\Windows\\Fonts\\Tahoma.ttf", 14.f, &imTahomaConfig, IO.Fonts->GetGlyphRangesCyrillic( ) );

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

	if ( !Source->Interfaces.m_pEngine->IsInGame( ) )
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
		pDrawList->AddRect( vecMin + ImVec2( 1.0f, 1.0f ), vecMax - ImVec2( 1.0f, 1.0f ), colOutline, flRounding, roundingCorners, 1.0f );

	if ( uFlags & DRAW_RECT_OUTLINE )
		pDrawList->AddRect( vecMin - ImVec2( 1.0f, 1.0f ), vecMax + ImVec2( 1.0f, 1.0f ), colOutline, flRounding, roundingCorners, 1.0f );
}

void CRender::AddDrawListText( ImDrawList* pDrawList, const ImFont* pFont, float flFontSize, const ImVec2& vecPosition, const std::string& szText, ImU32 colText, unsigned int uFlags, ImU32 colOutline )
{
	pDrawList->PushTextureID( pFont->ContainerAtlas->TexID );

	if ( uFlags & DRAW_TEXT_DROPSHADOW )
		pDrawList->AddText( pFont, flFontSize, vecPosition + ImVec2( 1.0f, -1.0f ), colOutline, szText.c_str( ) );
	else if ( uFlags & DRAW_TEXT_OUTLINE )
	{
		pDrawList->AddText( pFont, flFontSize, vecPosition + ImVec2( 1.0f, -1.0f ), colOutline, szText.c_str( ) );
		pDrawList->AddText( pFont, flFontSize, vecPosition + ImVec2( -1.0f, 1.0f ), colOutline, szText.c_str( ) );
	}

	pDrawList->AddText( pFont, flFontSize, vecPosition, colText, szText.data( ) );
	pDrawList->PopTextureID( );
}
#pragma endregion

#pragma region utils
bool CRender::WorldToScreen( const Vector& vecOrigin, ImVec2& vecScreen )
{
	const VMatrix& matWorldToScreen = Source->Interfaces.m_pEngine->WorldToScreenMatrix( );
	const float flWidth = matWorldToScreen[ 3 ][ 0 ] * vecOrigin.x + matWorldToScreen[ 3 ][ 1 ] * vecOrigin.y + matWorldToScreen[ 3 ][ 2 ] * vecOrigin.z + matWorldToScreen[ 3 ][ 3 ];

	if ( flWidth < 0.001f )
		return false;

	const float flInverse = 1.0f / flWidth;
	vecScreen.x = ( matWorldToScreen[ 0 ][ 0 ] * vecOrigin.x + matWorldToScreen[ 0 ][ 1 ] * vecOrigin.y + matWorldToScreen[ 0 ][ 2 ] * vecOrigin.z + matWorldToScreen[ 0 ][ 3 ] ) * flInverse;
	vecScreen.y = ( matWorldToScreen[ 1 ][ 0 ] * vecOrigin.x + matWorldToScreen[ 1 ][ 1 ] * vecOrigin.y + matWorldToScreen[ 1 ][ 2 ] * vecOrigin.z + matWorldToScreen[ 1 ][ 3 ] ) * flInverse;

	const ImVec2 vecDisplaySize = ImGui::GetIO( ).DisplaySize;
	vecScreen.x = ( vecDisplaySize.x * 0.5f ) + ( vecScreen.x * vecDisplaySize.x ) * 0.5f;
	vecScreen.y = ( vecDisplaySize.y * 0.5f ) - ( vecScreen.y * vecDisplaySize.y ) * 0.5f;

	return true;
}

bool CRender::GetBoundingBox( CBaseEntity* pEntity, Box_t* pBox )
{
	if ( !ImGui::GetCurrentContext( ) )
		return false;

	const Vector& vecOrigin = pEntity->GetOrigin( );
	const Vector vecMin = pEntity->OBBMins( ) + vecOrigin;
	const Vector vecMax = pEntity->OBBMaxs( ) + vecOrigin;

	pBox->m_flLeft = pBox->m_flTop = std::numeric_limits<float>::max( );
	pBox->m_flRight = pBox->m_flBottom = -std::numeric_limits<float>::max( );

	for ( size_t iCount = 0; iCount < 8; ++iCount )
	{
		const Vector vecPoints{ iCount & 1 ? vecMax.x : vecMin.x, iCount & 2 ? vecMax.y :
			vecMin.y, iCount & 4 ? vecMax.z : vecMin.z };

		ImVec2 vecScreen;
		if ( !WorldToScreen( vecPoints, vecScreen ) )
			return false;

		pBox->m_flLeft = IM_FLOOR( std::min( ( float )pBox->m_flLeft, vecScreen.x ) );
		pBox->m_flTop = IM_FLOOR( std::min( ( float )pBox->m_flTop, vecScreen.y ) );
		pBox->m_flRight = IM_FLOOR( std::max( ( float )pBox->m_flRight, vecScreen.x ) );
		pBox->m_flBottom = IM_FLOOR( std::max( ( float )pBox->m_flBottom, vecScreen.y ) );

		pBox->m_flWidth = pBox->m_flRight - pBox->m_flLeft;
		pBox->m_flHeight = pBox->m_flBottom - pBox->m_flTop;
	}

	return true;
}
#pragma endregion