#include <format>
#include "Hook.hpp"

bool CDetourHook::Create( void* pFunction, void* pDetour )
{
	m_pBaseFn = pFunction;

	if ( m_pBaseFn == nullptr )
		return false;

	m_pReplaceFn = pDetour;

	if ( m_pReplaceFn == nullptr )
		return false;

	const MH_STATUS status = MH_CreateHook( m_pBaseFn, m_pReplaceFn, &m_pOriginalFn );

	if ( status != MH_OK )
		throw std::runtime_error( std::vformat( "failed to create hook function, status: {}\nbase function -> {:#08X}", std::make_format_args( MH_StatusToString( status ), reinterpret_cast< std::uintptr_t >( m_pBaseFn ) ) ) );

	if ( !this->Replace( ) )
		return false;

	return true;
}

bool CDetourHook::Replace( )
{
	// check is hook be created
	if ( m_pBaseFn == nullptr )
		return false;

	// check is function not already hooked
	if ( m_bIsHooked )
		return false;

	const MH_STATUS status = MH_EnableHook( m_pBaseFn );

	if ( status != MH_OK )
		throw std::runtime_error( std::vformat( "failed to enable hook function, status: {}\nbase function -> {:#08X} address", std::make_format_args( MH_StatusToString( status ), reinterpret_cast< std::uintptr_t >( m_pBaseFn ) ) ) );

	// switch hook state
	m_bIsHooked = true;
	return true;
}

bool CDetourHook::Remove( )
{
	// restore it at first
	if ( !this->Restore( ) )
		return false;

	const MH_STATUS status = MH_RemoveHook( m_pBaseFn );

	if ( status != MH_OK )
		throw std::runtime_error( std::vformat( "failed to remove hook, status: {}\n base function -> {:#08X} address", std::make_format_args( MH_StatusToString( status ), reinterpret_cast< std::uintptr_t >( m_pBaseFn ) ) ) );

	return true;
}

bool CDetourHook::Restore( )
{
	// check is function hooked
	if ( !m_bIsHooked )
		return false;

	const MH_STATUS status = MH_DisableHook( m_pBaseFn );

	if ( status != MH_OK )
		throw std::runtime_error( std::vformat( "failed to restore hook, status: {}\n base function -> {:#08X} address", std::make_format_args( MH_StatusToString( status ), reinterpret_cast< std::uintptr_t >( m_pBaseFn ) ) ) );

	// switch hook state
	m_bIsHooked = false;
	return true;
}