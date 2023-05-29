#include "PlayerESP.hpp"
#include "../../Core/Source.hpp"
#include "../../Utilities/Render.hpp"
#include "../../Core/Variables/Variables.hpp"

void CPlayerESP::Instance( )
{
	if ( !Render.m_bInitialized )
		return;

	if ( !Variables.Parametrs.m_bPlayerESPEnable )
		return;

	for ( int iPlayerID = 1; iPlayerID < Source.Interfaces.m_pEntList->GetMaxEntities( ); iPlayerID++ )
	{
		CBasePlayer* pPlayer = Source.Interfaces.m_pEntList->Get<CBasePlayer>( iPlayerID );
		if ( !pPlayer || !pPlayer->IsPlayer( ) || !pPlayer->IsAlive( ) || pPlayer->IsDormant( ) )
			continue;

		RECT BBox;
		if ( !Render.GetBoundingBox( pPlayer, &BBox ) )
			continue;

		DrawBox( pPlayer, BBox );
	}
}

void CPlayerESP::DrawBox( CBasePlayer* pPlayer, RECT BBox )
{
	if ( !Variables.Parametrs.m_bPlayerESPBox )
		return;

	ImVec2 vecBoxMin = ImVec2( ( float )BBox.left, ( float )BBox.top );
	ImVec2 vecBoxMax = ImVec2( ( float )BBox.right, ( float )BBox.bottom );

	Render.AddRect( vecBoxMin, vecBoxMax, Color( 255, 255, 255 ), DRAW_RECT_OUTLINE | DRAW_RECT_BORDER, Color( 10, 10, 10 ) );
}