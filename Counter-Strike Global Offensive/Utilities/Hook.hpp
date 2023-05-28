#pragma once

#include <MinHook.h>
#pragma comment( lib, "libMinHook.x86.lib" )

class CDetourHook
{
public:
	CDetourHook( ) = default;

	explicit CDetourHook( void* pFunction, void* pDetour )
		: m_pBaseFn( pFunction ), m_pReplaceFn( pDetour ) { }

	bool Create( void* pFunction, void* pDetour );

	bool Replace( );
	bool Remove( );
	bool Restore( );

	template <typename Fn>
	Fn GetOriginal( )
	{
		return static_cast< Fn >( m_pOriginalFn );
	}

	inline bool IsHooked( ) const
	{
		return m_bIsHooked;
	}

private:
	bool m_bIsHooked = false;
	void* m_pBaseFn = nullptr;
	void* m_pReplaceFn = nullptr;
	void* m_pOriginalFn = nullptr;
};