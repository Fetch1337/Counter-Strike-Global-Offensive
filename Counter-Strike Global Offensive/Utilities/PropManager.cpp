#include "PropManager.hpp"
#include "../Core/Source.hpp"

CPropManager::~CPropManager( )
{
	this->Destroy( );
}

bool CPropManager::Create( )
{
	if ( !Source.Interfaces.m_pClient )
	{
		Win32Print.Error( "IBaseClientDLL is nullptr ( PropManager::%s )", __FUNCTION__ );
		return false;
	}

	auto pEntry = Source.Interfaces.m_pClient->GetAllClasses( );

	if ( !pEntry )
	{
		Win32Print.Error( "ClientClass is nullptr ( PropManager::%s )", __FUNCTION__ );
		return false;
	}

	while ( pEntry )
	{
		auto pTable = pEntry->m_pRecvTable;

		if ( pTable )
			this->m_pTables.emplace_back( pTable );

		pEntry = pEntry->m_pNext;
	}

	if ( this->m_pTables.empty( ) )
	{
		Win32Print.Error( "std::vector<RecvTable*> is empty ( PropManager::%s )", __FUNCTION__ );
		return false;
	}

	return true;
}

void CPropManager::Destroy( )
{
	this->m_pTables.clear( );
}

int CPropManager::GetOffset( const std::string& strTableName, const std::string& strPropName )
{
	return this->GetNetProp( strTableName, strPropName );
}

int CPropManager::FindInDataMap( const DataMap_t* pMap, const std::string& strPropName )
{
	while ( pMap )
	{
		for ( int i = 0; i < pMap->m_nDataFields; i++ )
		{
			if ( !pMap->m_pDataDesc[ i ].m_szFieldName )
				continue;

			if ( pMap->m_pDataDesc[ i ].m_szFieldName == strPropName.c_str( ) )
				return pMap->m_pDataDesc[ i ].m_iFieldOffset[ TD_OFFSET_NORMAL ];

			if ( pMap->m_pDataDesc[ i ].m_iFieldType == FIELD_EMBEDDED )
			{
				if ( pMap->m_pDataDesc[ i ].m_pTypeDescription )
				{
					if ( const int iOffset = FindInDataMap( pMap->m_pDataDesc[ i ].m_pTypeDescription, strPropName ); iOffset != 0 )
						return iOffset;
				}
			}
		}

		pMap = pMap->m_pBaseMap;
	}

	return 0;
}

RecvVarProxyFn CPropManager::Hook( const RecvVarProxyFn Hooked, const std::string& strTableName, const std::string& strPropName )
{
	RecvProp* pProp = nullptr;

	if ( !GetNetProp( strTableName, strPropName, &pProp ) )
	{
		Win32Print.Warning( "Prop '%s::%s' not found ( PropManager::%s )", strTableName.c_str( ), strPropName.c_str( ), __FUNCTION__ );
		return nullptr;
	}

	auto Restore = pProp->m_ProxyFn;

	pProp->m_ProxyFn = Hooked;

	return Restore;
}

int CPropManager::GetNetProp( const std::string& strTableName, const std::string& strPropName, RecvProp** OutProp /*= nullptr */ )
{
	return ( this->GetNetProp( this->GetTable( strTableName ), strPropName, OutProp ) );
}

int CPropManager::GetNetProp( RecvTable* pTable, const std::string& strPropName, RecvProp** OutProp /*= nullptr */ )
{
	int iExtra = 0;

	for ( int i = 0; i < pTable->m_nProps; i++ )
	{
		auto pProp = &pTable->m_pProps[ i ];
		auto pChild = pProp->m_pDataTable;

		if ( pChild && pChild->m_nProps )
		{
			int iAdd = GetNetProp( pChild, strPropName, OutProp );

			if ( iAdd )
				iExtra += ( pProp->m_Offset + iAdd );
		}

		if ( strPropName.compare( pProp->m_pVarName ) == 0 )
		{
			if ( OutProp )
				*OutProp = pProp;

			return ( pProp->m_Offset + iExtra );
		}
	}

	return iExtra;
}

RecvTable* CPropManager::GetTable( const std::string& strName )
{
	if ( !this->m_pTables.empty( ) )
	{
		for ( auto& pTable : m_pTables )
		{
			if ( strName.compare( pTable->m_pNetTableName ) == 0 )
				return pTable;
		}
	}

	Win32Print.Warning( "Prop table '%s' not found ( PropManager::%s )", strName.c_str( ), __FUNCTION__ );
	return nullptr;
}