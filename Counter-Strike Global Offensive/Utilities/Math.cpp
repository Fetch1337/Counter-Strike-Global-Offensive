#include "../SourceSDK/SDK.hpp"

float CMath::NormalizeAngle( float flAngle )
{
	flAngle = fmod( flAngle, 360.0f );
	if ( flAngle > 180.0f )
		flAngle -= 360.0f;
	if ( flAngle < -180.0f )
		flAngle += 360.0f;

	return flAngle;
}

float CMath::AngleDiff( float flDestAngle, float flSrcAngle )
{
	float flDelta = fmodf( flDestAngle - flSrcAngle, 360.0f );
	if ( flDestAngle > flSrcAngle )
	{
		if ( flDelta >= 180 )
			flDelta -= 360;
	}
	else
	{
		if ( flDelta <= -180 )
			flDelta += 360;
	}
	return flDelta;
}