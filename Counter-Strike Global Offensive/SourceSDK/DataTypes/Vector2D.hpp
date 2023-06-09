#pragma once

class Vector2D
{
public:
	Vector2D( );
	Vector2D( float x, float y );
	Vector2D( const Vector2D& v );
	Vector2D( const float* v );

public:
	void Set( float x = 0.0f, float y = 0.0f );

	float Dot( const Vector2D& v ) const;

	float LengthSquared( ) const;
	float Length( ) const;

public:
	float operator [ ] ( const std::uint32_t index );
	const float operator [ ] ( const std::uint32_t index ) const;

	Vector2D& operator = ( const Vector2D& v );
	Vector2D& operator = ( const float* v );

	Vector2D& operator += ( const Vector2D& v );
	Vector2D& operator -= ( const Vector2D& v );
	Vector2D& operator *= ( const Vector2D& v );
	Vector2D& operator /= ( const Vector2D& v );

	Vector2D& operator += ( float fl );
	Vector2D& operator -= ( float fl );
	Vector2D& operator *= ( float fl );
	Vector2D& operator /= ( float fl );

	Vector2D operator + ( const Vector2D& v ) const;
	Vector2D operator - ( const Vector2D& v ) const;
	Vector2D operator * ( const Vector2D& v ) const;
	Vector2D operator / ( const Vector2D& v ) const;

	Vector2D operator + ( float fl ) const;
	Vector2D operator - ( float fl ) const;
	Vector2D operator * ( float fl ) const;
	Vector2D operator / ( float fl ) const;

public:
	float x = 0,
		  y = 0;
};