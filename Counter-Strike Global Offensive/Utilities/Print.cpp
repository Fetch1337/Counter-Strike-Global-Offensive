#include "../SourceSDK/SDK.hpp"

const char* m_pPrintTypes[ ] =
{
	"[ Trace ]",
	"[ Warning ]",
	"[ Error ]",
};

const wchar_t* m_pWidePrintTypes[ ] =
{
	L"[ Trace ]",
	L"[ Warning ]",
	L"[ Error ]",
};

void CWin32Print::DebugPrint( PrintType PrintType, const char* pMessage )
{
	char szOutput[ 4096 ] = { };

	auto pType = m_pPrintTypes[ static_cast<int>( PrintType ) ];
	sprintf_s( szOutput, "%s %s\r\n", pType, pMessage );

	OutputDebugStringA( szOutput );
}

void CWin32Print::DebugPrint( PrintType PrintType, const wchar_t* pMessage )
{
	wchar_t szOutput[ 4096 ] = { };

	auto pType = m_pWidePrintTypes[ static_cast<int>( PrintType ) ];
	wsprintfW( szOutput, L"%s %s\r\n", pType, pMessage );

	OutputDebugStringW( szOutput );
}

void CWin32Print::Trace( const char* pFormat, ... )
{
	char szMessage[ 2048 ] = { };

	va_list Args;
	va_start( Args, pFormat );
	int iLength = vsprintf_s( szMessage, pFormat, Args );
	va_end( Args );

	DebugPrint( PrintType::Trace, szMessage );
}

void CWin32Print::Trace( const wchar_t* pFormat, ... )
{
	wchar_t szMessage[ 2048 ] = { };

	va_list Args;
	va_start( Args, pFormat );
	int iLength = wvsprintfW( szMessage, pFormat, Args );
	va_end( Args );

	DebugPrint( PrintType::Trace, szMessage );
}

void CWin32Print::Warning( const char* pFormat, ... )
{
	char szMessage[ 2048 ] = { };

	va_list Args;
	va_start( Args, pFormat );
	int iLength = vsprintf_s( szMessage, pFormat, Args );
	va_end( Args );

	DebugPrint( PrintType::Warning, szMessage );
}

void CWin32Print::Warning( const wchar_t* pFormat, ... )
{
	wchar_t szMessage[ 2048 ] = { };

	va_list Args;
	va_start( Args, pFormat );
	int iLength = wvsprintfW( szMessage, pFormat, Args );
	va_end( Args );

	DebugPrint( PrintType::Warning, szMessage );
}

void CWin32Print::Error( const char* pFormat, ... )
{
	char szMessage[ 2048 ] = { };

	va_list Args;
	va_start( Args, pFormat );
	int iLength = vsprintf_s( szMessage, pFormat, Args );
	va_end( Args );

	DebugPrint( PrintType::Error, szMessage );
}

void CWin32Print::Error( const wchar_t* pFormat, ... )
{
	wchar_t szMessage[ 2048 ] = { };

	va_list Args;
	va_start( Args, pFormat );
	int iLength = wvsprintfW( szMessage, pFormat, Args );
	va_end( Args );

	DebugPrint( PrintType::Error, szMessage );
}