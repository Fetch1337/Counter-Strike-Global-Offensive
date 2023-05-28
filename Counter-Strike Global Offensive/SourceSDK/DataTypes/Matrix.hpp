#pragma once

class matrix3x4_t
{
public:
	float* operator [ ] ( const std::uint32_t index );
	const float* operator [ ] ( const std::uint32_t index ) const;

public:
	float m[ 3 ][ 4 ] = { };
};

class VMatrix
{
public:
	float* operator [ ] ( const std::uint32_t index );
	const float* operator [ ] ( const std::uint32_t index ) const;

public:
	float m[ 4 ][ 4 ] = { };
};