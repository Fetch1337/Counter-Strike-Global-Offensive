#pragma once

template <class T, class N = int>
class CUtlMemory
{
public:
	T& operator[]( N i );
	const T& operator[]( N i ) const;

	T* Base( );

	int  NumAllocated( ) const;
	bool IsExternallyAllocated( ) const;
	void Grow( const int iCount = 1 );

protected:
	T* m_pMemory;
	int m_iAllocationCount;
	int m_iGrowSize;
};