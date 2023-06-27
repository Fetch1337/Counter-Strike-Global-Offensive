#pragma once

#include "../../SourceSDK/SDK.hpp"

struct MotionBlurHistory
{
    float m_flLastTimeUpdate{ };
    float m_flPreviousPitch{ };
    float m_flPreviousYaw{ };

    Vector m_vecPreviousPositon{ };

    float m_flNoRotationalMotionBlurUntil{ };
};

class CMotionBlur
{
public:
    void Instance( CViewSetup* pSetup );
private:
    void DrawScreenEffect( IMaterial* pMaterial );
};

inline const std::unique_ptr< CMotionBlur > MotionBlur{ new CMotionBlur( ) };