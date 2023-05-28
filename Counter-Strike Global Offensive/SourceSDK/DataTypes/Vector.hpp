#pragma once

class QAngle;
class Vector2D;
class Vector4D;

class Vector
{
public:
	Vector( );
	Vector( float x, float y, float z );
	Vector( const Vector& v );
	Vector( const float* v );

public:
	void Set( float x = 0.0f, float y = 0.0f, float z = 0.0f );

	bool IsZero( float tolerance = 0.01f );

	float Normalize( );

	float Dot( const Vector& v ) const;

	float LengthSquared( ) const;
	float Length( ) const;

	float DistanceSquared( const Vector& v ) const;
	float Distance( const Vector& v ) const;

	Vector Normalized( );
	Vector Cross( const Vector& v );

	Vector2D ToVector2D( );
	Vector4D ToVector4D( float w = 0.0f );

	QAngle ToEulerAngles( Vector* pseudoup = nullptr );

public:
	float operator [ ] ( const std::uint32_t index );
	const float operator [ ] ( const std::uint32_t index ) const;

	Vector& operator = ( const Vector& v );
	Vector& operator = ( const float* v );

	Vector& operator += ( const Vector& v );
	Vector& operator -= ( const Vector& v );
	Vector& operator *= ( const Vector& v );
	Vector& operator /= ( const Vector& v );

	Vector& operator += ( float fl );
	Vector& operator -= ( float fl );
	Vector& operator *= ( float fl );
	Vector& operator /= ( float fl );

	Vector operator + ( const Vector& v ) const;
	Vector operator - ( const Vector& v ) const;
	Vector operator * ( const Vector& v ) const;
	Vector operator / ( const Vector& v ) const;

	Vector operator + ( float fl ) const;
	Vector operator - ( float fl ) const;
	Vector operator * ( float fl ) const;
	Vector operator / ( float fl ) const;

public:
	static Vector Zero;

public:
	float x = 0,
		  y = 0,
		  z = 0;
};