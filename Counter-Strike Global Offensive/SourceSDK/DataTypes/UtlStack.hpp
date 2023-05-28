#pragma once
#include "UtlMemory.hpp"

template <class T, class M = CUtlMemory<T>>
class CUtlStack
{
public:
	T& operator[]( int i );
	const T& operator[]( int i ) const;

	T& Element( int i );
	const T& Element( int i ) const;

	T* Base( );
	const T* Base( ) const;

	T& Top( );
	const T& Top( ) const;

	int Count( ) const;

private:
	M	m_pMemory;
	int	m_iSize;
	T*	m_pElements;
};