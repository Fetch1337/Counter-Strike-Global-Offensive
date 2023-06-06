#include "../SourceSDK/SDK.hpp"

const char* pPrintTypes[ ] =
{
	"[ Trace ]",
	"[ Warning ]",
	"[ Error ]",
};

const wchar_t* pWidePrintTypes[ ] =
{
	L"[ Trace ]",
	L"[ Warning ]",
	L"[ Error ]",
};

void CWin32Print::DebugPrint( PrintType PrintType, const char* pMessage )
{
	char szOutput[ 4096 ] = { };

	auto pType = pPrintTypes[ static_cast<int>( PrintType ) ];
	sprintf_s( szOutput, "%s %s\r\n", pType, pMessage );

	printf( szOutput );
}

void CWin32Print::Trace( const char* pFormat, ... )
{
#ifdef _DEBUG
	char szMessage[ 2048 ] = { };

	va_list Args;
	va_start( Args, pFormat );
	int iLength = vsprintf_s( szMessage, pFormat, Args );
	va_end( Args );

	DebugPrint( PrintType::Trace, szMessage );
#endif
}

void CWin32Print::Warning( const char* pFormat, ... )
{
#ifdef _DEBUG
	char szMessage[ 2048 ] = { };

	va_list Args;
	va_start( Args, pFormat );
	int iLength = vsprintf_s( szMessage, pFormat, Args );
	va_end( Args );

	DebugPrint( PrintType::Warning, szMessage );
#endif
}

void CWin32Print::Error( const char* pFormat, ... )
{
#ifdef _DEBUG
	char szMessage[ 2048 ] = { };

	va_list Args;
	va_start( Args, pFormat );
	int iLength = vsprintf_s( szMessage, pFormat, Args );
	va_end( Args );

	DebugPrint( PrintType::Error, szMessage );
#endif
}