#pragma once
#include "../SourceSDK/SDK.hpp"

enum class EDrawType : int
{
	NONE = 0,
	LINE,
	RECT,
	RECT_MULTICOLOR,
	CIRCLE,
	TRIANGLE,
	POLYGON,
	TEXT,
	IMAGE
};

struct DrawObject_t
{
	DrawObject_t( const EDrawType nType, std::any&& pObject ) :
		m_nType( nType ), m_pObject( std::move( pObject ) ) { }

	EDrawType m_nType = EDrawType::NONE;
	std::any m_pObject = { };
};

#pragma region draw_objects_enumerations
enum ERectRenderFlags : unsigned int
{
	DRAW_RECT_NONE = 0,
	DRAW_RECT_OUTLINE = ( 1 << 0 ),
	DRAW_RECT_BORDER = ( 1 << 1 ),
	DRAW_RECT_FILLED = ( 1 << 2 )
};

enum ECircleRenderFlags : unsigned int
{
	DRAW_CIRCLE_NONE = 0,
	DRAW_CIRCLE_OUTLINE = ( 1 << 0 ),
	DRAW_CIRCLE_FILLED = ( 1 << 1 )
};

enum ETriangleRenderFlags : unsigned int
{
	DRAW_TRIANGLE_NONE = 0,
	DRAW_TRIANGLE_OUTLINE = ( 1 << 0 ),
	DRAW_TRIANGLE_FILLED = ( 1 << 1 )
};

enum EPolygonRenderFlags : unsigned int
{
	DRAW_POLYGON_NONE = 0,
	DRAW_POLYGON_OUTLINE = ( 1 << 0 ),
	DRAW_POLYGON_FILLED = ( 1 << 1 )
};

enum ETextRenderFlags : unsigned int
{
	DRAW_TEXT_NONE = 0,
	DRAW_TEXT_DROPSHADOW = ( 1 << 0 ),
	DRAW_TEXT_OUTLINE = ( 1 << 1 )
};
#pragma endregion

#pragma region draw_objects_structures
struct LineObject_t
{
	ImVec2 m_vecStart = { };
	ImVec2 m_vecEnd = { };
	ImU32 m_colLine = 0x0;
	float m_flThickness = 0.f;
};

struct RectObject_t
{
	ImVec2 m_vecMin = { };
	ImVec2 m_vecMax = { };
	ImU32 m_colRect = 0x0;
	unsigned int m_uFlags = 0x0;
	ImU32 m_colOutline = 0x0;
	float m_flRounding = 0.f;
	ImDrawCornerFlags m_RoundingCorners = ImDrawCornerFlags_None;
	float m_flThickness = 0.f;
};

struct RectMultiColorObject_t
{
	ImVec2 m_vecMin = { };
	ImVec2 m_vecMax = { };
	ImU32 m_colUpperLeft = 0x0;
	ImU32 m_colUpperRight = 0x0;
	ImU32 m_colBottomRight = 0x0;
	ImU32 m_colBottomLeft = 0x0;
};

struct CircleObject_t
{
	ImVec2 m_vecCenter = { };
	float m_flRadius = 0.f;
	ImU32 m_colCircle = 0x0;
	int m_nSegments = 0;
	unsigned int m_uFlags = 0x0;
	ImU32 m_colOutline = 0x0;
	float m_flThickness = 0.f;
};

struct TriangleObject_t
{
	ImVec2 m_vecFirst = { };
	ImVec2 m_vecSecond = { };
	ImVec2 m_vecThird = { };
	ImU32 m_colTriangle = 0x0;
	unsigned int m_uFlags = 0x0;
	ImU32 m_colOutline = 0x0;
	float m_flThickness = 0.f;
};

struct PolygonObject_t
{
	std::vector<ImVec2> m_vecPoints = { };
	ImU32 m_colPolygon = 0x0;
	unsigned int m_uFlags = 0x0;
	ImU32 m_colOutline = 0x0;
	bool m_bClosed = false;
	float m_flThickness = 0.f;
};

struct TextObject_t
{
	const ImFont* m_pFont = nullptr;
	float m_flFontSize = 0.f;
	ImVec2 m_vecPosition = { };
	std::string m_szText = { };
	ImU32 m_colText = 0x0;
	unsigned int m_uFlags = 0x0;
	ImU32 m_colOutline = 0x0;
};

struct ImageObject_t
{
	ImTextureID m_pTexture = nullptr;
	ImVec2 m_vecMin = { };
	ImVec2 m_vecMax = { };
	ImU32 m_colImage = 0x0;
	float m_flRounding = 0.f;
	ImDrawCornerFlags m_RoundingCorners = ImDrawCornerFlags_None;
};
#pragma endregion

class CRender
{
public:
	void Create( IDirect3DDevice9* pDevice, unsigned int uFontFlags = 0x0 );
	void Destroy( );

	void RenderDrawData( ImDrawList* pDrawList );
	void ClearDrawData( );
	void SwapDrawData( );

	void AddLine( const ImVec2& vecStart, const ImVec2& vecEnd, const Color& colLine, float flThickness = 1.0f );
	void AddRect( const ImVec2& vecMin, const ImVec2& vecMax, const Color& colRect, unsigned int uFlags = DRAW_RECT_NONE, const Color& colOutline = Color( 0, 0, 0, 255 ), float flRounding = 0.f, ImDrawCornerFlags roundingCorners = ImDrawCornerFlags_All, float flThickness = 1.0f );
	void AddRectMultiColor( const ImVec2& vecMin, const ImVec2& vecMax, const Color& colUpperLeft, const Color& colUpperRight, const Color& colBottomRight, const Color& colBottomLeft );
	void AddCircle( const ImVec2& vecCenter, float flRadius, const Color& colCircle, int nSegments = 12, unsigned int uFlags = DRAW_CIRCLE_NONE, const Color& colOutline = Color( 0, 0, 0, 255 ), float flThickness = 1.0f );
	void AddTriangle( const ImVec2& vecFirst, const ImVec2& vecSecond, const ImVec2& vecThird, const Color& colTriangle, unsigned int uFlags = DRAW_TRIANGLE_NONE, const Color& colOutline = Color( 0, 0, 0, 255 ), float flThickness = 1.0f );
	void AddPolygon( std::vector<ImVec2>& vecPoints, const Color& colPolygon, unsigned int uFlags = DRAW_POLYGON_FILLED, const Color& colOutline = Color( 0, 0, 0, 255 ), bool bClosed = true, float flThickness = 1.0f );
	void AddText( const ImFont* pFont, float flFontSize, const ImVec2& vecPosition, const std::string& szText, const Color& colText, unsigned int uFlags = DRAW_TEXT_NONE, const Color& colOutline = Color( 0, 0, 0, 255 ) );
	void AddText( const ImVec2& vecPosition, const std::string& szText, const Color& colText, int iFlags = DRAW_TEXT_NONE, const Color& colOutline = Color( 0, 0, 0, 255 ) );
	void AddImage( ImTextureID pTexture, const ImVec2& vecMin, const ImVec2& vecMax, const Color& colImage = Color( 255, 255, 255, 255 ), float flRounding = 0.f, ImDrawCornerFlags roundingCorners = ImDrawCornerFlags_All );

	void AddDrawListRect( ImDrawList* pDrawList, const ImVec2& vecMin, const ImVec2& vecMax, ImU32 colRect, unsigned int uFlags = DRAW_RECT_NONE, ImU32 colOutline = IM_COL32( 0, 0, 0, 255 ), float flRounding = 0.f, ImDrawCornerFlags roundingCorners = ImDrawCornerFlags_All, float flThickness = 1.0f );
	void AddDrawListText( ImDrawList* pDrawList, const ImFont* pFont, float flFontSize, const ImVec2& vecPosition, const std::string& szText, ImU32 colText, unsigned int uFlags = DRAW_TEXT_NONE, ImU32 colOutline = IM_COL32( 0, 0, 0, 255 ) );

	bool m_bInitialized = false;

private:
	std::deque<DrawObject_t> m_vecDrawData = { };
	std::deque<DrawObject_t> m_vecSafeDrawData = { };
	std::shared_mutex m_DrawMutex = { };
};

inline CRender Render;