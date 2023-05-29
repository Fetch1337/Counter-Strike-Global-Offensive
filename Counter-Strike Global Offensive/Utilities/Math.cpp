#include "Math.hpp"

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

Vector CMath::VectorTransform( const Vector& vecTransform, const matrix3x4_t& Matrix )
{
	return Vector( vecTransform.Dot( Matrix[ 0 ] ) + Matrix[ 0 ][ 3 ],
		vecTransform.Dot( Matrix[ 1 ] ) + Matrix[ 1 ][ 3 ],
		vecTransform.Dot( Matrix[ 2 ] ) + Matrix[ 2 ][ 3 ] );
}

Vector CMath::VectorRotate( const Vector& vecRotate, const matrix3x4_t& Matrix )
{
	return Vector( vecRotate.Dot( Matrix[ 0 ] ),
		vecRotate.Dot( Matrix[ 1 ] ),
		vecRotate.Dot( Matrix[ 2 ] ) );
}