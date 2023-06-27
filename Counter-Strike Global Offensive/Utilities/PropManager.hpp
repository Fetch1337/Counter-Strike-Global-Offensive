#pragma once

#include "../SourceSDK/SDK.hpp"

class CPropManager
{
public:
	~CPropManager( );

public:
	bool Create( );
	void Destroy( );

	int GetOffset( const std::string& strTableName, const std::string& strPropName );
	int FindInDataMap( const DataMap_t* pMap, const std::string& strPropName );

	RecvVarProxyFn Hook( const RecvVarProxyFn Hooked, const std::string& strTableName, const std::string& strPropName );

private:
	int GetNetProp( const std::string& strTableName, const std::string& strPropName, CRecvProp** OutProp = nullptr );
	int GetNetProp( CRecvTable* pTable, const std::string& strPropName, CRecvProp** OutProp = nullptr );

	CRecvTable* GetTable( const std::string& strName );

private:
	std::vector<CRecvTable*> m_pTables;
};

inline const std::unique_ptr< CPropManager > PropManager{ new CPropManager( ) };