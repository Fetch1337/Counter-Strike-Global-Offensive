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

void CMath::FromAngleAll(const QAngle& angle, Vector* forward, Vector* right, Vector* up)
{
	float sr = std::sin(M_DEG2RAD(angle.z)),
		sp = std::sin(M_DEG2RAD(angle.x)),
		sy = std::sin(M_DEG2RAD(angle.y)),
		cr = std::cos(M_DEG2RAD(angle.z)),
		cp = std::cos(M_DEG2RAD(angle.x)),
		cy = std::cos(M_DEG2RAD(angle.y));

	if (forward)
	{
		forward->x = cp * cy;
		forward->y = cp * sy;
		forward->z = -sp;
	}

	if (right)
	{
		right->x = (-1 * sr * sp * cy + -1 * cr * -sy);
		right->y = (-1 * sr * sp * sy + -1 * cr * cy);
		right->z = -1 * sr * cp;
	}

	if (up)
	{
		up->x = (cr * sp * cy + -sr * -sy);
		up->y = (cr * sp * sy + -sr * cy);
		up->z = cr * cp;
	}
}