#include "PlayerESP.hpp"
#include "../../Core/Source.hpp"
#include "../../Core/Includes/Global.hpp"
#include "../../Core/Variables/Variables.hpp"

void CPlayerESP::Instance( )
{
	if ( !Render->m_bInitialized )
		return;

	if ( !Variables->Parametrs.PlayerESP.m_bEnable )
		return;

	for ( int iPlayerID = 1; iPlayerID < Source->Interfaces.m_pEntList->GetMaxEntities( ); iPlayerID++ )
	{
		CBasePlayer* pPlayer = Source->Interfaces.m_pEntList->Get<CBasePlayer>( iPlayerID );
		if ( !pPlayer || !pPlayer->IsPlayer( ) || !pPlayer->IsAlive( ) || pPlayer->IsDormant( ) )
			continue;

		Box_t BBox;
		if ( !Render->GetBoundingBox( pPlayer, &BBox ) )
			continue;

		int iPlayerType{ };
		if ( Globals->m_pLocal != pPlayer )
			iPlayerType = !Globals->m_pLocal->IsEnemy( pPlayer ) ? 1 : 2;

		DrawBox( pPlayer, BBox, iPlayerType );
		DrawName( pPlayer, BBox, iPlayerType );
		DrawHealth( pPlayer, BBox, iPlayerType );
		DrawAmmo( pPlayer, BBox, iPlayerType );
	}
}

void CPlayerESP::DrawBox( CBasePlayer* pPlayer, Box_t BBox, int iPlayerType )
{
	if ( !Variables->Parametrs.PlayerESP.Players[ iPlayerType ].m_bBox )
		return;

	ImVec2 vecBoxMin = ImVec2( BBox.m_flLeft, BBox.m_flTop );
	ImVec2 vecBoxMax = ImVec2( BBox.m_flRight, BBox.m_flBottom );

	Render->AddRect( vecBoxMin, vecBoxMax, Color( 255, 255, 255 ), DRAW_RECT_OUTLINE | DRAW_RECT_BORDER, Color( 10, 10, 10 ) );
}

void CPlayerESP::DrawName( CBasePlayer* pPlayer, Box_t BBox, int iPlayerType )
{
	if ( !Variables->Parametrs.PlayerESP.Players[ iPlayerType ].m_bName )
		return;

	PlayerInfo_t PlayerInfo;

	if ( Source->Interfaces.m_pEngine->GetPlayerInfo( pPlayer->EntIndex( ), &PlayerInfo ) )
	{
		std::string strName = PlayerInfo.szName;
		if ( strName.length( ) > 24U )
			strName = strName.substr( 0U, 24U ).append( "..." );

		const ImVec2 vecNameSize = Fonts::pTahoma->CalcTextSizeA( 12.f, FLT_MAX, 0.f, strName.c_str( ) );

		Render->AddText( Fonts::pTahoma, 12.f, ImVec2( BBox.m_flLeft + BBox.m_flWidth * 0.5f - vecNameSize.x * 0.5f, BBox.m_flTop - 15.f ), strName, Color( 255, 255, 255 ), DRAW_TEXT_DROPSHADOW );
	}
}

void CPlayerESP::DrawHealth( CBasePlayer* pPlayer, Box_t BBox, int iPlayerType )
{
	if ( !Variables->Parametrs.PlayerESP.Players[ iPlayerType ].m_bHealth )
		return;

	int iHealth = std::clamp( pPlayer->GetHealth( ), 0, 100 );
	float flHealthHeight = BBox.m_flHeight - ( int )( ( BBox.m_flHeight * iHealth ) / 100 );

	int iRed = 255 - static_cast< int >( iHealth * 2.55f );
	int iGreen = static_cast< int >( iHealth * 2.55f );

	ImVec2 vecBoxMin = ImVec2( BBox.m_flLeft - 6, BBox.m_flTop - 1 );
	ImVec2 vecBoxMax = ImVec2( BBox.m_flLeft - 2, BBox.m_flBottom + 1 );

	ImVec2 vecHealthMin = ImVec2( BBox.m_flLeft - 5, BBox.m_flTop + flHealthHeight );
	ImVec2 vecHealthMax = ImVec2( BBox.m_flLeft - 3, BBox.m_flBottom );

	Render->AddRect( vecBoxMin, vecBoxMax, Color( 80, 80, 80, 100 ), DRAW_RECT_FILLED );
	Render->AddRect( vecHealthMin, vecHealthMax, Color( iRed, iGreen, 0, 255 ), DRAW_RECT_FILLED );
}

void CPlayerESP::DrawAmmo( CBasePlayer* pPlayer, Box_t BBox, int iPlayerType )
{
	if ( !Variables->Parametrs.PlayerESP.Players[ iPlayerType ].m_bAmmo )
		return;

	CWeaponCSBaseGun* pWeapon = Source->Interfaces.m_pEntList->Get<CWeaponCSBaseGun>( pPlayer->GetActiveWeapon( ) );
	if ( !pWeapon )
		return;

	CWeaponInfo* pWeaponInfo = pWeapon->GetCSWeaponData( );
	if ( !pWeaponInfo )
		return;

	int iAmmo = std::clamp( pWeapon->GetClip1( ), 0, pWeaponInfo->m_iMaxClip1 );

	ImVec2 vecBoxMin = ImVec2( BBox.m_flLeft - 1, BBox.m_flBottom + 2 );
	ImVec2 vecBoxMax = ImVec2( BBox.m_flRight + 1, BBox.m_flBottom + 6 );

	float flFactor = static_cast< float >( iAmmo ) / static_cast< float >( pWeaponInfo->m_iMaxClip1 );

	ImVec2 vecAmmoMin = ImVec2( BBox.m_flLeft, BBox.m_flBottom + 3 );
	ImVec2 vecAmmoMax = ImVec2( BBox.m_flLeft + BBox.m_flWidth * flFactor, BBox.m_flBottom + 5 );

	Render->AddRect( vecBoxMin, vecBoxMax, Color( 80, 80, 80, 100 ), DRAW_RECT_FILLED );
	Render->AddRect( vecAmmoMin, vecAmmoMax, Color( 0, 190, 255, 255 ), DRAW_RECT_FILLED );
}