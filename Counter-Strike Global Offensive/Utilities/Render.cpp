#include "Render.hpp"
#include "Math.hpp"
#include "InputManager.hpp"
#include "../../../SourceSDK/Objects/Entity.hpp"
#include "../../../SourceSDK/Objects/Player.hpp"
#include "../Core/Source.hpp"

#pragma region draw_get
void CRender::Create( IDirect3DDevice9* pDevice, unsigned int uFontFlags )
{
	ImGui::CreateContext( );

	ImGui_ImplWin32_Init( InputManager.m_hWindow );
	ImGui_ImplDX9_Init( pDevice );

	ImGui::StyleColorsDark( );

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
		pDrawList->AddRect( ImVec2( vecMin.x + 1.f, vecMin.y + 1.f ), ImVec2( vecMax.x - 1.f, vecMax.y - 1.f ), colOutline, flRounding, roundingCorners, 1.0f );

	if ( uFlags & DRAW_RECT_OUTLINE )
		pDrawList->AddRect( ImVec2( vecMin.x - 1.f, vecMin.y - 1.f ), ImVec2( vecMax.x + 1.f, vecMax.y + 1.f ), colOutline, flRounding, roundingCorners, 1.0f );
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

#pragma region utils
bool CRender::WorldToScreen( const Vector& vecOrigin, ImVec2& vecScreen )
{
	const VMatrix& matWorldToScreen = Source.Interfaces.m_pEngine->WorldToScreenMatrix( );
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

bool CRender::GetBoundingBox( CBaseEntity* pEntity, RECT* pBox )
{
	if ( !ImGui::GetCurrentContext( ) )
		return false;

	const Vector& vecOrigin = pEntity->m_vecOrigin( );
	const Vector vecMin = pEntity->OBBMins( ) + vecOrigin;
	const Vector vecMax = pEntity->OBBMaxs( ) + vecOrigin;

	pBox->left = pBox->top = std::numeric_limits<long>::max( );
	pBox->right = pBox->bottom = -std::numeric_limits<long>::max( );

	for ( size_t iCount = 0; iCount < 8; ++iCount )
	{
		const Vector vecPoints{ iCount & 1 ? vecMax.x : vecMin.x, iCount & 2 ? vecMax.y :
			vecMin.y, iCount & 4 ? vecMax.z : vecMin.z };

		ImVec2 vecScreen;
		if ( !WorldToScreen( vecPoints, vecScreen ) )
			return false;

		pBox->left = IM_FLOOR( std::min( ( float )pBox->left, vecScreen.x ) );
		pBox->top = IM_FLOOR( std::min( ( float )pBox->top, vecScreen.y ) );
		pBox->right = IM_FLOOR( std::max( ( float )pBox->right, vecScreen.x ) );
		pBox->bottom = IM_FLOOR( std::max( ( float )pBox->bottom, vecScreen.y ) );
	}

	return true;
}
#pragma endregion