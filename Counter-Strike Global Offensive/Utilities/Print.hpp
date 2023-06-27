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

	void Trace( const char* pFormat, ... );
	void Warning( const char* pFormat, ... );
	void Error( const char* pFormat, ... );
};

inline const std::unique_ptr< CWin32Print > Win32Print{ new CWin32Print( ) };