#pragma once

class Color
{
public:
	Color( );
	Color( const int r, const int g, const int b );
	Color( const int r, const int g, const int b, const int a );
	Color( const Color& color );

public:
	void Set( int r = 0, int g = 0, int b = 0, int a = 0 );
	void Normalize( );

	D3DCOLOR	GetD3D( ) const;
	ImU32		GetU32( const float flAlphaMultiplier = 1.0f ) const;
	ImVec4		GetVec4( const float flAlphaMultiplier = 1.0f ) const;

public:
	Color& operator = ( const Color& color );

	Color& operator += ( const Color& color );
	Color& operator -= ( const Color& color );
	Color& operator *= ( const Color& color );
	Color& operator /= ( const Color& color );

	Color operator + ( const Color& color ) const;
	Color operator - ( const Color& color ) const;
	Color operator * ( const Color& color ) const;
	Color operator / ( const Color& color ) const;

public:
	int r = 0,
		g = 0,
		b = 0,
		a = 0;
};