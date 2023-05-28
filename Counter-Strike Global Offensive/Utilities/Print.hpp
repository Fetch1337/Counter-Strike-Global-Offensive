#pragma once

class CWin32Print
{
public:
	enum class PrintType
	{
		Trace = 0,
		Warning,
		Error,
	};

	void DebugPrint( PrintType PrintType, const char* pMessage );
	void DebugPrint( PrintType PrintType, const wchar_t* pMessage );

	void Trace( const char* pFormat, ... );
	void Trace( const wchar_t* pFormat, ... );
	void Warning( const char* pFormat, ... );
	void Warning( const wchar_t* pFormat, ... );
	void Error( const char* pFormat, ... );
	void Error( const wchar_t* pFormat, ... );
};

inline CWin32Print Win32Print;