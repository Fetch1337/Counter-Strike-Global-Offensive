#pragma once

#include "../SourceSDK/SDK.hpp"

#pragma region math_definitions
#define M_HPI			DirectX::XM_PIDIV2	// half pi
#define M_QPI			DirectX::XM_PIDIV4	// quarter pi
#define M_PI			DirectX::XM_PI		// pi const
#define M_2PI			DirectX::XM_2PI		// pi double
#define M_GPI			1.6180339887498f	// golden ratio
#define M_RADPI			57.295779513082f	// pi in radians

#define M_METRE2INCH( x )	( ( x ) / 0.0254f )
#define M_INCH2METRE( x )	( ( x ) * 0.0254f )
#define M_METRE2FOOT( x )	( ( x ) * 3.28f )
#define M_FOOT2METRE( x )	( ( x ) / 3.28f )
#define M_RAD2DEG( x )		DirectX::XMConvertToDegrees( x )
#define M_DEG2RAD( x )		DirectX::XMConvertToRadians( x )

#define M_CheckIfNonValidNumber( x ) ( fpclassify( x ) == FP_INFINITE || fpclassify( x ) == FP_NAN || fpclassify( x ) == FP_SUBNORMAL )
#pragma endregion

class CMath
{
public:
	float NormalizeAngle( float flAngle );
	float AngleDiff( float flDestAngle, float flSrcAngle );
	Vector VectorTransform( const Vector& vecTransform, const matrix3x4_t& Matrix );
	Vector VectorRotate( const Vector& vecRotate, const matrix3x4_t& Matrix );
};

inline CMath Math;