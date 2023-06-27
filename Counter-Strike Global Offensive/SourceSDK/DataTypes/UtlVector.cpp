#include "UtlVector.hpp"

template<class T, class M>
T* CUtlVector<T, M>::Begin( ) noexcept
{
	return m_pMemory->Base( );
}

template<class T, class M>
int CUtlVector<T, M>::End( ) noexcept
{
	return m_pMemory->Base( ) + m_iSize;
}

template<class T, class M>
T* CUtlVector<T, M>::Begin( ) const noexcept
{
	return m_pMemory->Base( );
}

template<class T, class M>
int CUtlVector<T, M>::End( ) const noexcept
{
	return m_pMemory->Base( ) + m_iSize;
}

template<class T, class M>
T& CUtlVector<T, M>::operator[]( int i )
{
	return m_pMemory[ i ];
}

template<class T, class M>
const T& CUtlVector<T, M>::operator[]( int i ) const
{
	return m_pMemory[ i ];
}

template<class T, class M>
T& CUtlVector<T, M>::Element( int i )
{
	return m_pMemory[ i ];
}

template<class T, class M>
const T& CUtlVector<T, M>::Element( int i ) const
{
	return m_pMemory[ i ];
}

template<class T, class M>
T* CUtlVector<T, M>::Base( )
{
	return m_pMemory->Base( );
}

template<class T, class M>
int CUtlVector<T, M>::Count( ) const
{
	return m_iSize;
}

template<class T, class M>
int& CUtlVector<T, M>::Size( )
{
	return m_iSize;
}

template<class T, class M>
void CUtlVector<T, M>::GrowVector( int nCount )
{
	if ( m_iSize + nCount > m_pMemory->NumAllocated( ) )
		m_pMemory->Grow( m_iSize + nCount - m_pMemory->NumAllocated( ) );

	m_iSize += nCount;
}

template<class T, class M>
void CUtlVector<T, M>::ShiftElementsRight( const int nElement, const int nShift )
{
	const int nToMove = m_iSize - nElement - nShift;

	if ( nToMove > 0 && nShift > 0 )
		memmove( &Element( nElement + nShift ), &Element( nElement ), nToMove * sizeof( T ) );
}

template<class T, class M>
void CUtlVector<T, M>::ShiftElementsLeft( const int nElement, const int nShift )
{
	const int nToMove = m_iSize - nElement - nShift;

	if ( nToMove > 0 && nShift > 0 )
		memmove( &Element( nElement ), &Element( nElement + nShift ), nToMove * sizeof( T ) );
}

template<class T, class M>
int CUtlVector<T, M>::InsertBefore( const int nElement )
{
	GrowVector( );
	ShiftElementsRight( nElement );
	Construct( &Element( nElement ) );
	return nElement;
}

template<class T, class M>
int CUtlVector<T, M>::InsertBefore( int nElement, const T& src )
{
	GrowVector( );
	ShiftElementsRight( nElement );
	Copy( &Element( nElement ), src );
	return nElement;
}

template<class T, class M>
int CUtlVector<T, M>::AddToTail( )
{
	return InsertBefore( m_iSize );
}

template<class T, class M>
int CUtlVector<T, M>::AddToTail( const T& src )
{
	return InsertBefore( m_iSize, src );
}

template<class T, class M>
int CUtlVector<T, M>::Find( const T& src ) const
{
	for ( int i = 0; i < Count( ); ++i )
	{
		if ( Element( i ) == src )
			return i;
	}

	return -1;
}

template<class T, class M>
void CUtlVector<T, M>::Remove( const int nElement )
{
	Destruct( &Element( nElement ) );
	ShiftElementsLeft( nElement );
	--m_iSize;
}

template<class T, class M>
void CUtlVector<T, M>::RemoveAll( )
{
	for ( int i = m_iSize; --i >= 0;)
		Destruct( &Element( i ) );

	m_iSize = 0;
}

template<class T, class M>
bool CUtlVector<T, M>::FindAndRemove( const T& src )
{
	if ( const int nElement = Find( src ); nElement != -1 )
	{
		Remove( nElement );
		return true;
	}

	return false;
}