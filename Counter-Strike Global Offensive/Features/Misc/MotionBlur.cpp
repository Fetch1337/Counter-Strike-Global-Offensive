#include "MotionBlur.hpp"
#include "../../Core/Source.hpp"
#include "../../Core/Variables/Variables.hpp"
#include "../../Utilities/Math.hpp"
#include "../../Core/Includes/Global.hpp"

void CMotionBlur::Instance( CViewSetup* pSetup )
{
    if ( !Globals->m_pLocal || !Variables->Parametrs.Misc.m_bMotionBlur )
        return;

    static MotionBlurHistory History;
    static float flMotionBlurValues[ 4 ] = { 0.0f, 0.0f, 0.0f, 0.0f };
    if ( pSetup )
    {
        const float flTimeElapsed = Source->Interfaces.m_pGlobalVars->m_flRealTime - History.m_flLastTimeUpdate;

        const auto angViewangles = pSetup->m_angView;

        const float flCurrentPitch = Math->NormalizeAngle( angViewangles.x );
        const float flCurrentYaw = Math->NormalizeAngle( angViewangles.y );

        Vector vecCurrentSideVector;
        Vector vecCurrentForwardVector;
        Vector vecCurrentUpVector;

        Math->FromAngleAll( angViewangles, &vecCurrentForwardVector, &vecCurrentSideVector, &vecCurrentUpVector );

        Vector vecCurrentPosition = pSetup->m_vecOrigin;
        Vector vecPositionChange = History.m_vecPreviousPositon - vecCurrentPosition;

        if ( ( vecPositionChange.Length( ) > 30.0f ) && ( flTimeElapsed >= 0.5f ) )
        {
            flMotionBlurValues[ 0 ] = 0.0f;
            flMotionBlurValues[ 1 ] = 0.0f;
            flMotionBlurValues[ 2 ] = 0.0f;
            flMotionBlurValues[ 3 ] = 0.0f;
        }
        else if ( flTimeElapsed > ( 1.0f / 15.0f ) )
        {
            flMotionBlurValues[ 0 ] = 0.0f;
            flMotionBlurValues[ 1 ] = 0.0f;
            flMotionBlurValues[ 2 ] = 0.0f;
            flMotionBlurValues[ 3 ] = 0.0f;
        }
        else if ( vecPositionChange.Length( ) > 50.0f )
        {
            History.m_flNoRotationalMotionBlurUntil = Source->Interfaces.m_pGlobalVars->m_flRealTime + 1.0f;
        }
        else
        {
            const float flHorizontalFov = pSetup->m_flFOV;
            const float flVerticalFov = ( pSetup->m_flAspectRatio <= 0.0f ) ? ( pSetup->m_flFOV ) : ( pSetup->m_flFOV / pSetup->m_flAspectRatio );
            const float flViewdotMotion = vecCurrentForwardVector.Dot( vecPositionChange );

            flMotionBlurValues[ 2 ] = flViewdotMotion;

            const float flSidedotMotion = vecCurrentSideVector.Dot( vecPositionChange );
            float flYawDiffOriginal = History.m_flPreviousYaw - flCurrentYaw;
            if ( ( ( History.m_flPreviousYaw - flCurrentYaw > 180.0f ) || ( History.m_flPreviousYaw - flCurrentYaw < -180.0f ) ) &&
                ( ( History.m_flPreviousYaw + flCurrentYaw > -180.0f ) && ( History.m_flPreviousYaw + flCurrentYaw < 180.0f ) ) )
                flYawDiffOriginal = History.m_flPreviousYaw + flCurrentYaw;

            float flYawDiffAdjusted = flYawDiffOriginal + ( flSidedotMotion / 3.0f );

            if ( flYawDiffOriginal < 0.0f )
                flYawDiffAdjusted = std::clamp( flYawDiffAdjusted, flYawDiffOriginal, 0.0f );
            else
                flYawDiffAdjusted = std::clamp( flYawDiffAdjusted, 0.0f, flYawDiffOriginal );

            const float flUndampenedYaw = flYawDiffAdjusted / flHorizontalFov;
            flMotionBlurValues[ 0 ] = flUndampenedYaw * ( 1.0f - ( fabsf( flCurrentPitch ) / 90.0f ) );

            const float flPitchCompensateMask = 1.0f - ( ( 1.0f - fabsf( vecCurrentForwardVector[ 2 ] ) ) * ( 1.0f - fabsf( vecCurrentForwardVector[ 2 ] ) ) );
            const float flPitchDiffOriginal = History.m_flPreviousPitch - flCurrentPitch;
            float flPitchDiffAdjusted = flPitchDiffOriginal;

            if ( flCurrentPitch > 0.0f )
                flPitchDiffAdjusted = flPitchDiffOriginal - ( ( flViewdotMotion / 2.0f ) * flPitchCompensateMask );
            else
                flPitchDiffAdjusted = flPitchDiffOriginal + ( ( flViewdotMotion / 2.0f ) * flPitchCompensateMask );


            if ( flPitchDiffOriginal < 0.0f )
                flPitchDiffAdjusted = std::clamp( flPitchDiffAdjusted, flPitchDiffOriginal, 0.0f );
            else
                flPitchDiffAdjusted = std::clamp( flPitchDiffAdjusted, 0.0f, flPitchDiffOriginal );

            flMotionBlurValues[ 1 ] = flPitchDiffAdjusted / flVerticalFov;
            flMotionBlurValues[ 3 ] = flUndampenedYaw;
            flMotionBlurValues[ 3 ] *= ( fabs( flCurrentPitch ) / 90.0f ) * ( fabs( flCurrentPitch ) / 90.0f ) * ( fabs( flCurrentPitch ) / 90.0f );

            if ( flTimeElapsed > 0.0f )
                flMotionBlurValues[ 2 ] /= flTimeElapsed * 30.0f;
            else
                flMotionBlurValues[ 2 ] = 0.0f;

            flMotionBlurValues[ 2 ] = std::clamp( ( fabsf( flMotionBlurValues[ 2 ] ) - 10.f ) / 5.0f, 0.0f, 1.0f ) *
                ( flMotionBlurValues[ 2 ] >= 0.0f ? 1.0f : -1.0f );

            flMotionBlurValues[ 2 ] /= 30.0f;
            flMotionBlurValues[ 0 ] *= 4.f * .15f * Variables->Parametrs.Misc.m_flMotionBlurStrength;
            flMotionBlurValues[ 1 ] *= 4.f * .15f * Variables->Parametrs.Misc.m_flMotionBlurStrength;
            flMotionBlurValues[ 2 ] *= 3.f * .15f * Variables->Parametrs.Misc.m_flMotionBlurStrength;
            flMotionBlurValues[ 3 ] *= 3.f * .15f * Variables->Parametrs.Misc.m_flMotionBlurStrength;

        }

        if ( Source->Interfaces.m_pGlobalVars->m_flRealTime < History.m_flNoRotationalMotionBlurUntil )
        {
            flMotionBlurValues[ 0 ] = 0.0f;
            flMotionBlurValues[ 1 ] = 0.0f;
            flMotionBlurValues[ 3 ] = 0.0f;
        }
        else
        {
            History.m_flNoRotationalMotionBlurUntil = 0.0f;
        }
        History.m_vecPreviousPositon = vecCurrentPosition;

        History.m_flPreviousPitch = flCurrentPitch;
        History.m_flPreviousYaw = flCurrentYaw;
        History.m_flLastTimeUpdate = Source->Interfaces.m_pGlobalVars->m_flRealTime;
        return;
    }

    const auto Material = Source->Interfaces.m_pMaterialSystem->FindMaterial( "dev/motion_blur", "RenderTargets", false );
    if ( !Material )
        return;

    const auto MotionBlurInternal = Material->FindVar( "$MotionBlurInternal", nullptr, false );

    MotionBlurInternal->SetVecComponentValue( flMotionBlurValues[ 0 ], 0 );
    MotionBlurInternal->SetVecComponentValue( flMotionBlurValues[ 1 ], 1 );
    MotionBlurInternal->SetVecComponentValue( flMotionBlurValues[ 2 ], 2 );
    MotionBlurInternal->SetVecComponentValue( flMotionBlurValues[ 3 ], 3 );

    const auto MotionBlurViewPortInternal = Material->FindVar( "$MotionBlurViewportInternal", nullptr, false );

    MotionBlurViewPortInternal->SetVecComponentValue( 0.0f, 0 );
    MotionBlurViewPortInternal->SetVecComponentValue( 0.0f, 1 );
    MotionBlurViewPortInternal->SetVecComponentValue( 1.0f, 2 );
    MotionBlurViewPortInternal->SetVecComponentValue( 1.0f, 3 );

    DrawScreenEffect( Material );
}

void CMotionBlur::DrawScreenEffect( IMaterial* pMaterial )
{	
	using Fn = void( __fastcall* )( void*, IMaterial*, int, int, int );
	static auto DrawScreenEffectMaterial = ( Fn ) Memory->Scan( "client.dll", "55 8B EC 83 E4 ? 83 EC ? 53 56 57 8D 44 24 ? 89 4C" );

	int iWidth, iHeight;
	Source->Interfaces.m_pEngine->GetScreenSize( iWidth, iHeight );	
	__asm 
	{ 
		__asm push iHeight
		__asm push iWidth	
		__asm push 0 
		__asm xor edx, edx 
		__asm mov ecx, pMaterial 
		__asm call DrawScreenEffectMaterial
		__asm add esp, 12 
	} 
}
