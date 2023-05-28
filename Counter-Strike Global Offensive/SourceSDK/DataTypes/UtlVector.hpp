#pragma once
#include "UtlMemory.hpp"

template <class T>
void Destruct( T* pMemory )
{
	pMemory->~T( );
}

template <class T>
T* Construct( T* pMemory )
{
	return new( pMemory ) T;
}

template< class T >
T* Copy( T* pMemory, T const& src )
{
	return new( pMemory ) T( src );
}

template <class T, class A = CUtlMemory<T>>
class CUtlVector
{
	using CAllocator = A;
public:
	T* Begin( ) noexcept;
	int End( ) noexcept;

	T* Begin( ) const noexcept;
	int End( ) const noexcept;

	T& operator[]( int i );
	const T& operator[]( int i ) const;

	T& Element( int i );
	const T& Element( int i ) const;

	T* Base( );
	int Count( ) const;
	int& Size( );

	void GrowVector( int nCount = 1 );

	void ShiftElementsRight( const int nElement, const int nShift = 1 );
	void ShiftElementsLeft( const int nElement, const int nShift = 1 );

	int InsertBefore( const int nElement );
	int InsertBefore( int nElement, const T& src );

	int AddToTail( );
	int AddToTail( const T& src );

	int Find( const T& src ) const;

	void Remove( const int nElement );
	void RemoveAll( );

	bool FindAndRemove( const T& src );

protected:
	CAllocator m_pMemory;
	int		   m_iSize;
	T*		   m_pElements;
};