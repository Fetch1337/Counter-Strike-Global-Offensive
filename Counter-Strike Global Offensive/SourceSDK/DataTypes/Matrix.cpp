#include "../../SourceSDK/SDK.hpp"

float* matrix3x4_t::operator [ ] ( const std::uint32_t index )
{
	return m[ index ];
}

const float* matrix3x4_t::operator [ ] ( const std::uint32_t index ) const
{
	return m[ index ];
}

float* VMatrix::operator [ ] ( const std::uint32_t index )
{
	return m[ index ];
}

const float* VMatrix::operator [ ] ( const std::uint32_t index ) const
{
	return m[ index ];
}