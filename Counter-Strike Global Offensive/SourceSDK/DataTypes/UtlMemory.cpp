#include "UtlMemory.hpp"

template<class T, class N>
T& CUtlMemory<T, N>::operator[]( N i )
{
	return m_pMemory[ i ];
}

template<class T, class N>
const T& CUtlMemory<T, N>::operator[]( N i ) const
{
	return m_pMemory[ i ];
}

template<class T, class N>
T* CUtlMemory<T, N>::Base( )
{
	return m_pMemory;
}

template<class T, class N>
int CUtlMemory<T, N>::NumAllocated( ) const
{
	return m_iAllocationCount;
}

template<class T, class N>
bool CUtlMemory<T, N>::IsExternallyAllocated( ) const
{
	return m_iGrowSize < 0;
}

template<class T, class N>
void CUtlMemory<T, N>::Grow( const int iCount )
{
	if ( IsExternallyAllocated( ) )
		return;

	int iAllocationRequested = m_iAllocationCount + iCount;
	int iNewAllocationCount = 0;

	if ( m_iGrowSize )
		m_iAllocationCount = ( ( 1 + ( ( iAllocationRequested - 1 ) / m_iGrowSize ) ) * m_iGrowSize );
	else
	{
		if ( !m_iAllocationCount )
			m_iAllocationCount = ( 31 + sizeof( T ) ) / sizeof( T );

		while ( m_iAllocationCount < iAllocationRequested )
			m_iAllocationCount <<= 1;
	}

	if ( static_cast< int >( static_cast< N >( iNewAllocationCount ) ) < iAllocationRequested )
	{
		if ( static_cast< int >( static_cast< N >( iNewAllocationCount ) ) == 0 && static_cast< int >( static_cast< N >( iNewAllocationCount - 1 ) ) >= iAllocationRequested )
			--iNewAllocationCount;
		else
		{
			if ( static_cast< int >( static_cast< N >( iAllocationRequested ) ) != iAllocationRequested )
				return;

			while ( static_cast< int >( static_cast< N >( iNewAllocationCount ) ) < iAllocationRequested )
				iNewAllocationCount = ( iNewAllocationCount + iAllocationRequested ) / 2;
		}
	}

	m_iAllocationCount = iNewAllocationCount;

	if ( m_pMemory != nullptr )
		m_pMemory = static_cast< T* >( realloc( m_pMemory, m_iAllocationCount * sizeof( T ) ) );
	else
		m_pMemory = static_cast< T* >( malloc( m_iAllocationCount * sizeof( T ) ) );
}