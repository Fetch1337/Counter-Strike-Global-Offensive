#include "UtlStack.hpp"

template<class T, class M>
T& CUtlStack<T, M>::operator[]( int i )
{
	return m_pMemory[ i ];
}

template<class T, class M>
const T& CUtlStack<T, M>::operator[]( int i ) const
{
	return m_pMemory[ i ];
}

template<class T, class M>
T& CUtlStack<T, M>::Element( int i )
{
	return m_pMemory[ i ];
}

template<class T, class M>
const T& CUtlStack<T, M>::Element( int i ) const
{
	return m_pMemory[ i ];
}

template<class T, class M>
T* CUtlStack<T, M>::Base( )
{
	return m_pMemory.Base( );
}

template<class T, class M>
const T* CUtlStack<T, M>::Base( ) const
{
	return m_pMemory.Base( );
}

template<class T, class M>
T& CUtlStack<T, M>::Top( )
{
	return Element( m_iSize - 1 );
}

template<class T, class M>
const T& CUtlStack<T, M>::Top( ) const
{
	return Element( m_iSize - 1 );
}

template<class T, class M>
int CUtlStack<T, M>::Count( ) const
{
	return m_iSize;
}