#include "../../SourceSDK/SDK.hpp"

Color::Color( )
{
	this->Set( );
}

Color::Color( const int r, const int g, const int b )
{
	this->Set( r, g, b );
}

Color::Color( const int r, const int g, const int b, const int a )
{
	this->Set( r, g, b, a );
}

Color::Color( const Color& color )
{
	this->Set( color.r, color.g, color.b, color.a );
}

void Color::Set( int r /*= 0*/, int g /*= 0*/, int b /*= 0*/, int a /*= 0*/ )
{
	this->r = r;
	this->g = g;
	this->b = b;
	this->a = a;
	this->Normalize( );
}

void Color::Normalize( )
{
	this->r = std::clamp( this->r, 0, 255 );
	this->g = std::clamp( this->g, 0, 255 );
	this->b = std::clamp( this->b, 0, 255 );
	this->a = std::clamp( this->a, 0, 255 );
}

D3DCOLOR Color::GetD3D( ) const
{
	return D3DCOLOR_ARGB( this->a, this->r, this->g, this->b );
}

ImU32 Color::GetU32( const float flAlphaMultiplier ) const
{
	return ImGui::GetColorU32( this->GetVec4( flAlphaMultiplier ) );
}

ImVec4 Color::GetVec4( const float flAlphaMultiplier ) const
{
	return ImVec4( /*this->Base<COLOR_R>( ), this->Base<COLOR_G>( ), this->Base<COLOR_B>( ), this->Base<COLOR_A>( ) * flAlphaMultiplier*/ );
}

Color& Color::operator = ( const Color& color )
{
	this->Set( color.r, color.g, color.b, color.a );

	return ( *this );
}

Color& Color::operator += ( const Color& color )
{
	this->r += color.r;
	this->g += color.g;
	this->b += color.b;
	this->a += color.a;
	this->Normalize( );

	return ( *this );
}

Color& Color::operator -= ( const Color& color )
{
	this->r -= color.r;
	this->g -= color.g;
	this->b -= color.b;
	this->a -= color.a;
	this->Normalize( );

	return ( *this );
}

Color& Color::operator *= ( const Color& color )
{
	this->r *= color.r;
	this->g *= color.g;
	this->b *= color.b;
	this->a *= color.a;
	this->Normalize( );

	return ( *this );
}

Color& Color::operator /= ( const Color& color )
{
	this->r /= color.r;
	this->g /= color.g;
	this->b /= color.b;
	this->a /= color.a;
	this->Normalize( );

	return ( *this );
}

Color Color::operator + ( const Color& color ) const
{
	Color Result;

	Result.r = this->r + color.r;
	Result.g = this->g + color.g;
	Result.b = this->b + color.b;
	Result.a = this->a + color.a;
	Result.Normalize( );

	return Result;
}

Color Color::operator - ( const Color& color ) const
{
	Color Result;

	Result.r = this->r - color.r;
	Result.g = this->g - color.g;
	Result.b = this->b - color.b;
	Result.a = this->a - color.a;
	Result.Normalize( );

	return Result;
}

Color Color::operator * ( const Color& color ) const
{
	Color Result;

	Result.r = this->r * color.r;
	Result.g = this->g * color.g;
	Result.b = this->b * color.b;
	Result.a = this->a * color.a;
	Result.Normalize( );

	return Result;
}

Color Color::operator / ( const Color& color ) const
{
	Color Result;

	Result.r = this->r / color.r;
	Result.g = this->g / color.g;
	Result.b = this->b / color.b;
	Result.a = this->a / color.a;
	Result.Normalize( );

	return Result;
}