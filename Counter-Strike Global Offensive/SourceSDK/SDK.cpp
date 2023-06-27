#include "SDK.hpp"
#include "../Core/Source.hpp"

const char* String_t::ToCStr( ) const
{
	return ( pszValue ) ? pszValue : "";
}

CRC32_t CUserCmd::GetChecksum( ) const
{
	CRC32_t CRC;

	CRC32_Init( &CRC );
	CRC32_ProcessBuffer( &CRC, &m_iCommandNumber, sizeof( m_iCommandNumber ) );
	CRC32_ProcessBuffer( &CRC, &m_iTickCount, sizeof( m_iTickCount ) );
	CRC32_ProcessBuffer( &CRC, &m_angViewAngles, sizeof( m_angViewAngles ) );
	CRC32_ProcessBuffer( &CRC, &m_vecAimDirection, sizeof( m_vecAimDirection ) );
	CRC32_ProcessBuffer( &CRC, &m_flForwardMove, sizeof( m_flForwardMove ) );
	CRC32_ProcessBuffer( &CRC, &m_flSideMove, sizeof( m_flSideMove ) );
	CRC32_ProcessBuffer( &CRC, &m_flUpMove, sizeof( m_flUpMove ) );
	CRC32_ProcessBuffer( &CRC, &m_iButtons, sizeof( m_iButtons ) );
	CRC32_ProcessBuffer( &CRC, &m_uImpulse, sizeof( m_uImpulse ) );
	CRC32_ProcessBuffer( &CRC, &m_iWeaponSelect, sizeof( m_iWeaponSelect ) );
	CRC32_ProcessBuffer( &CRC, &m_iWeaponSubtype, sizeof( m_iWeaponSubtype ) );
	CRC32_ProcessBuffer( &CRC, &m_iRandomSeed, sizeof( m_iRandomSeed ) );
	CRC32_ProcessBuffer( &CRC, &m_sMouseDx, sizeof( m_sMouseDx ) );
	CRC32_ProcessBuffer( &CRC, &m_sMouseDy, sizeof( m_sMouseDy ) );
	CRC32_Final( &CRC );

	return CRC;
}

const char* CConVar::GetName( )
{
	using Fn = const char* ( __thiscall* )( void* );
	return Memory->GetVFunc<Fn>( this, 5 )( this );
}

float CConVar::GetFloat( )
{
	std::uint32_t uXored = *reinterpret_cast< std::uint32_t* >( &m_pParent->m_flValue ) ^ reinterpret_cast< std::uint32_t >( this );
	return *reinterpret_cast< float* >( &uXored );
}

int CConVar::GetInt( )
{
	return static_cast< int >( m_pParent->m_iValue ^ reinterpret_cast< int >( this ) );
}

bool CConVar::GetBool( )
{
	return !!GetInt( );
}

const char* CConVar::GetString( )
{
	char const* szValue = m_pParent->m_szString;
	return szValue ? szValue : "";
}

void CConVar::SetValue( const char* szValue )
{
	using Fn = void( __thiscall* )( void*, const char* );
	return Memory->GetVFunc<Fn>( this, 14 )( this, szValue );
}

void CConVar::SetValue( float flValue )
{
	using Fn = void( __thiscall* )( void*, float );
	return Memory->GetVFunc<Fn>( this, 15 )( this, flValue );
}

void CConVar::SetValue( int iValue )
{
	using Fn = void( __thiscall* )( void*, int );
	return Memory->GetVFunc<Fn>( this, 16 )( this, iValue );
}

void CConVar::SetValue( Color colValue )
{
	using Fn = void( __thiscall* )( void*, Color );
	return Memory->GetVFunc<Fn>( this, 17 )( this, colValue );
}

CClientClass* IBaseClientDLL::GetAllClasses( )
{
	using Fn = CClientClass* ( __thiscall* )( void* );
	return Memory->GetVFunc<Fn>( this, 8 )( this );
}

void IGameMovement::ProcessMovement( CBasePlayer* pPlayer, CMoveData* pMove )
{
	using Fn = void ( __thiscall* )( void*, CBasePlayer*, CMoveData* );
	return Memory->GetVFunc<Fn>( this, 1 )( this, pPlayer, pMove );
}

void IGameMovement::StartTrackPredictionErrors( CBasePlayer* pPlayer )
{
	using Fn = void ( __thiscall* )( void*, CBasePlayer* );
	return Memory->GetVFunc<Fn>( this, 3 )( this, pPlayer );
}

void IGameMovement::FinishTrackPredictionErrors( CBasePlayer* pPlayer )
{
	using Fn = void ( __thiscall* )( void*, CBasePlayer* );
	return Memory->GetVFunc<Fn>( this, 4 )( this, pPlayer );
}

void IPrediction::SetupMove( CBasePlayer* pPlayer, CUserCmd* pCmd, IMoveHelper* pHelper, CMoveData* pMove )
{
	using Fn = void ( __thiscall* )( void*, CBasePlayer*, CUserCmd*, IMoveHelper*, CMoveData* );
	return Memory->GetVFunc<Fn>( this, 20 )( this, pPlayer, pCmd, pHelper, pMove );
}

void IPrediction::FinishMove( CBasePlayer* pPlayer, CUserCmd* pCmd, CMoveData* pMove )
{
	using Fn = void ( __thiscall* )( void*, CBasePlayer*, CUserCmd*, CMoveData* );
	return Memory->GetVFunc<Fn>( this, 21 )( this, pPlayer, pCmd, pMove );
}

void IMoveHelper::SetHost( CBaseEntity* pHost )
{
	using Fn = void ( __thiscall* )( void*, CBaseEntity* );
	return Memory->GetVFunc<Fn>( this, 1 )( this, pHost );
}

CUserCmd* IInput::GetUserCmd( int iSequenceNumber )
{
	return &m_pCommands[ iSequenceNumber % MULTIPLAYER_BACKUP ];
}

CVerifiedUserCmd* IInput::GetVerifiedUserCmd( int iSequenceNumber )
{
	return &m_pVerifiedCommands[ iSequenceNumber % MULTIPLAYER_BACKUP ];
}

void IInputSystem::EnableInput( bool bEnable )
{
	using Fn = void( __thiscall* )( void*, bool );
	return Memory->GetVFunc<Fn>( this, 11 )( this, bEnable );
}

bool IInputSystem::IsButtonDown( EButtonCode buttonCode )
{
	using Fn = bool( __thiscall* )( void*, EButtonCode );
	return Memory->GetVFunc<Fn>( this, 15 )( this, buttonCode );
}

void IInputSystem::ResetInputState( )
{
	using Fn = void( __thiscall* )( void* );
	return Memory->GetVFunc<Fn>( this, 39 )( this );
}

const char* IInputSystem::ButtonCodeToString( EButtonCode buttonCode )
{
	using Fn = const char*( __thiscall* )( void*, EButtonCode );
	return Memory->GetVFunc<Fn>( this, 40 )( this, buttonCode );
}

EButtonCode IInputSystem::VirtualKeyToButtonCode( int iVirtualKey )
{
	using Fn = EButtonCode( __thiscall* )( void*, int );
	return Memory->GetVFunc<Fn>( this, 45 )( this, iVirtualKey );
}

void IInputSystem::GetCursorPosition( int* pX, int* pY )
{
	using Fn = void( __thiscall* )( void*, int*, int* );
	return Memory->GetVFunc<Fn>( this, 56 )( this, pX, pY );
}

void IVEngineClient::GetScreenSize( int& iWidth, int& iHeight )
{
	using Fn = void ( __thiscall* )( void*, int&, int& );
	return Memory->GetVFunc<Fn>( this, 5 )( this, iWidth, iHeight );
}

bool IVEngineClient::GetPlayerInfo( int iIndex, PlayerInfo_t* pInfo )
{
	using Fn = bool( __thiscall* )( void*, int, PlayerInfo_t* );
	return Memory->GetVFunc<Fn>( this, 8 )( this, iIndex, pInfo );
}

bool IVEngineClient::IsConsoleVisible( )
{
	using Fn = bool( __thiscall* )( void* );
	return Memory->GetVFunc<Fn>( this, 11 )( this );
}

int IVEngineClient::GetLocalPlayer( )
{
	using Fn = int ( __thiscall* )( void* );
	return Memory->GetVFunc<Fn>( this, 12 )( this );
}

float IVEngineClient::Time( )
{
	using Fn = float ( __thiscall* )( void* );
	return Memory->GetVFunc<Fn>( this, 14 )( this );
}

void IVEngineClient::GetViewAngles( QAngle& angOutput )
{
	using Fn = void ( __thiscall* )( void*, QAngle& );
	return Memory->GetVFunc<Fn>( this, 18 )( this, angOutput );
}

void IVEngineClient::SetViewAngles( QAngle& angInput )
{
	using Fn = void ( __thiscall* )( void*, QAngle& );
	return Memory->GetVFunc<Fn>( this, 19 )( this, angInput );
}

int IVEngineClient::GetMaxClients( )
{
	using Fn = int ( __thiscall* )( void* );
	return Memory->GetVFunc<Fn>( this, 20 )( this );
}

bool IVEngineClient::IsInGame( )
{
	using Fn = bool ( __thiscall* )( void* );
	return Memory->GetVFunc<Fn>( this, 26 )( this );
}

bool IVEngineClient::IsConnected( )
{
	using Fn = bool ( __thiscall* )( void* );
	return Memory->GetVFunc<Fn>( this, 27 )( this );
}

const VMatrix& IVEngineClient::WorldToScreenMatrix( )
{
	using Fn = const VMatrix& ( __thiscall* )( void* );
	return Memory->GetVFunc<Fn>( this, 37 )( this );
}

void IVEngineClient::ClientCmd_Unrestricted( const char* szCmdString )
{
	using Fn = void ( __thiscall* )( void*, const char* );
	return Memory->GetVFunc<Fn>( this, 114 )( this, szCmdString );
}

const char* IPanel::GetName( VPANEL vguiPanel )
{
	using Fn = const char* ( __thiscall* )( void*, VPANEL );
	return Memory->GetVFunc<Fn>( this, 36 )( this, vguiPanel );
}

IMaterial* IMaterialSystem::FindMaterial( char const* pMaterialName, const char* pTextureGroupName, bool complain, const char* pComplainPrefix )
{
	using Fn = IMaterial* ( __thiscall* )( void*, char const*, char const*, bool, char const* );
	return Memory->GetVFunc<Fn>( this, 84 )( this, pMaterialName, pTextureGroupName, complain, pComplainPrefix );
}

void IMaterialVar::SetValue( float flValue )
{
	using Fn = void ( __thiscall* )( void*, float );
	return Memory->GetVFunc<Fn>( this, 4 )( this, flValue );
}

void IMaterialVar::SetVectorValue( float flX, float flY, float flZ )
{
	using Fn = void ( __thiscall* )( void*, float, float, float );
	return Memory->GetVFunc<Fn>( this, 11 )( this, flX, flY, flZ );
}

void IMaterialVar::SetVecComponentValue( float flValue, int iComp )
{
	using Fn = void ( __thiscall* )( void*, float, int );
	return Memory->GetVFunc<Fn>( this, 26 )( this, flValue, iComp );
}

#pragma region impl_functions
void RandomSeed( unsigned int iSeed )
{
	using Fn = void ( * )( unsigned int );
	auto Procedure = ( Fn )( Source->Functions.m_uRandomSeed );

	if( Procedure )
		Procedure( iSeed );
}

float RandomFloat( float flMin, float flMax )
{
	using Fn = float ( * )( float, float );
	auto Procedure = ( Fn )( Source->Functions.m_uRandomFloat );

	return ( Procedure ? Procedure( flMin, flMax ) : 0.0f );
}

int RandomInt( int iMin, int iMax )
{
	using Fn = int ( * )( int, int );
	auto Procedure = ( Fn )( Source->Functions.m_uRandomInt );

	return ( Procedure ? Procedure( iMin, iMax ) : 0 );
}

#pragma region impl_crc32
#define CRC32_INIT_VALUE 0xFFFFFFFFUL
#define CRC32_XOR_VALUE  0xFFFFFFFFUL

#define NUM_BYTES 256

static const CRC32_t pulCRCTable[ NUM_BYTES ] =
{
	0x00000000, 0x77073096, 0xee0e612c, 0x990951ba,
	0x076dc419, 0x706af48f, 0xe963a535, 0x9e6495a3,
	0x0edb8832, 0x79dcb8a4, 0xe0d5e91e, 0x97d2d988,
	0x09b64c2b, 0x7eb17cbd, 0xe7b82d07, 0x90bf1d91,
	0x1db71064, 0x6ab020f2, 0xf3b97148, 0x84be41de,
	0x1adad47d, 0x6ddde4eb, 0xf4d4b551, 0x83d385c7,
	0x136c9856, 0x646ba8c0, 0xfd62f97a, 0x8a65c9ec,
	0x14015c4f, 0x63066cd9, 0xfa0f3d63, 0x8d080df5,
	0x3b6e20c8, 0x4c69105e, 0xd56041e4, 0xa2677172,
	0x3c03e4d1, 0x4b04d447, 0xd20d85fd, 0xa50ab56b,
	0x35b5a8fa, 0x42b2986c, 0xdbbbc9d6, 0xacbcf940,
	0x32d86ce3, 0x45df5c75, 0xdcd60dcf, 0xabd13d59,
	0x26d930ac, 0x51de003a, 0xc8d75180, 0xbfd06116,
	0x21b4f4b5, 0x56b3c423, 0xcfba9599, 0xb8bda50f,
	0x2802b89e, 0x5f058808, 0xc60cd9b2, 0xb10be924,
	0x2f6f7c87, 0x58684c11, 0xc1611dab, 0xb6662d3d,
	0x76dc4190, 0x01db7106, 0x98d220bc, 0xefd5102a,
	0x71b18589, 0x06b6b51f, 0x9fbfe4a5, 0xe8b8d433,
	0x7807c9a2, 0x0f00f934, 0x9609a88e, 0xe10e9818,
	0x7f6a0dbb, 0x086d3d2d, 0x91646c97, 0xe6635c01,
	0x6b6b51f4, 0x1c6c6162, 0x856530d8, 0xf262004e,
	0x6c0695ed, 0x1b01a57b, 0x8208f4c1, 0xf50fc457,
	0x65b0d9c6, 0x12b7e950, 0x8bbeb8ea, 0xfcb9887c,
	0x62dd1ddf, 0x15da2d49, 0x8cd37cf3, 0xfbd44c65,
	0x4db26158, 0x3ab551ce, 0xa3bc0074, 0xd4bb30e2,
	0x4adfa541, 0x3dd895d7, 0xa4d1c46d, 0xd3d6f4fb,
	0x4369e96a, 0x346ed9fc, 0xad678846, 0xda60b8d0,
	0x44042d73, 0x33031de5, 0xaa0a4c5f, 0xdd0d7cc9,
	0x5005713c, 0x270241aa, 0xbe0b1010, 0xc90c2086,
	0x5768b525, 0x206f85b3, 0xb966d409, 0xce61e49f,
	0x5edef90e, 0x29d9c998, 0xb0d09822, 0xc7d7a8b4,
	0x59b33d17, 0x2eb40d81, 0xb7bd5c3b, 0xc0ba6cad,
	0xedb88320, 0x9abfb3b6, 0x03b6e20c, 0x74b1d29a,
	0xead54739, 0x9dd277af, 0x04db2615, 0x73dc1683,
	0xe3630b12, 0x94643b84, 0x0d6d6a3e, 0x7a6a5aa8,
	0xe40ecf0b, 0x9309ff9d, 0x0a00ae27, 0x7d079eb1,
	0xf00f9344, 0x8708a3d2, 0x1e01f268, 0x6906c2fe,
	0xf762575d, 0x806567cb, 0x196c3671, 0x6e6b06e7,
	0xfed41b76, 0x89d32be0, 0x10da7a5a, 0x67dd4acc,
	0xf9b9df6f, 0x8ebeeff9, 0x17b7be43, 0x60b08ed5,
	0xd6d6a3e8, 0xa1d1937e, 0x38d8c2c4, 0x4fdff252,
	0xd1bb67f1, 0xa6bc5767, 0x3fb506dd, 0x48b2364b,
	0xd80d2bda, 0xaf0a1b4c, 0x36034af6, 0x41047a60,
	0xdf60efc3, 0xa867df55, 0x316e8eef, 0x4669be79,
	0xcb61b38c, 0xbc66831a, 0x256fd2a0, 0x5268e236,
	0xcc0c7795, 0xbb0b4703, 0x220216b9, 0x5505262f,
	0xc5ba3bbe, 0xb2bd0b28, 0x2bb45a92, 0x5cb36a04,
	0xc2d7ffa7, 0xb5d0cf31, 0x2cd99e8b, 0x5bdeae1d,
	0x9b64c2b0, 0xec63f226, 0x756aa39c, 0x026d930a,
	0x9c0906a9, 0xeb0e363f, 0x72076785, 0x05005713,
	0x95bf4a82, 0xe2b87a14, 0x7bb12bae, 0x0cb61b38,
	0x92d28e9b, 0xe5d5be0d, 0x7cdcefb7, 0x0bdbdf21,
	0x86d3d2d4, 0xf1d4e242, 0x68ddb3f8, 0x1fda836e,
	0x81be16cd, 0xf6b9265b, 0x6fb077e1, 0x18b74777,
	0x88085ae6, 0xff0f6a70, 0x66063bca, 0x11010b5c,
	0x8f659eff, 0xf862ae69, 0x616bffd3, 0x166ccf45,
	0xa00ae278, 0xd70dd2ee, 0x4e048354, 0x3903b3c2,
	0xa7672661, 0xd06016f7, 0x4969474d, 0x3e6e77db,
	0xaed16a4a, 0xd9d65adc, 0x40df0b66, 0x37d83bf0,
	0xa9bcae53, 0xdebb9ec5, 0x47b2cf7f, 0x30b5ffe9,
	0xbdbdf21c, 0xcabac28a, 0x53b39330, 0x24b4a3a6,
	0xbad03605, 0xcdd70693, 0x54de5729, 0x23d967bf,
	0xb3667a2e, 0xc4614ab8, 0x5d681b02, 0x2a6f2b94,
	0xb40bbe37, 0xc30c8ea1, 0x5a05df1b, 0x2d02ef8d
};

void CRC32_Init( CRC32_t* pulCRC )
{
	*pulCRC = CRC32_INIT_VALUE;
}

void CRC32_ProcessBuffer( CRC32_t* pulCRC, const void* pPointer, int iLen )
{
	CRC32_t ulCrc = *pulCRC;
	unsigned char *pb = ( unsigned char * )pPointer;
	unsigned int nFront;
	int nMain;

JustAfew:

	switch ( iLen )
	{
	case 7:
		ulCrc  = pulCRCTable[ *pb++ ^ ( unsigned char )ulCrc ] ^ ( ulCrc >> 8 );

	case 6:
		ulCrc  = pulCRCTable[ *pb++ ^ ( unsigned char )ulCrc ] ^ ( ulCrc >> 8 );

	case 5:
		ulCrc  = pulCRCTable[ *pb++ ^ ( unsigned char )ulCrc ] ^ ( ulCrc >> 8 );

	case 4:
		ulCrc ^= ( *( CRC32_t * )pb );
		ulCrc  = pulCRCTable[ ( unsigned char )ulCrc ] ^ ( ulCrc >> 8 );
		ulCrc  = pulCRCTable[ ( unsigned char )ulCrc ] ^ ( ulCrc >> 8 );
		ulCrc  = pulCRCTable[ ( unsigned char )ulCrc ] ^ ( ulCrc >> 8 );
		ulCrc  = pulCRCTable[ ( unsigned char )ulCrc ] ^ ( ulCrc >> 8 );
		*pulCRC = ulCrc;
		return;

	case 3:
		ulCrc  = pulCRCTable[ *pb++ ^ ( unsigned char )ulCrc ] ^ ( ulCrc >> 8 );

	case 2:
		ulCrc  = pulCRCTable[ *pb++ ^ ( unsigned char )ulCrc ] ^ ( ulCrc >> 8 );

	case 1:
		ulCrc  = pulCRCTable[ *pb++ ^ ( unsigned char )ulCrc ] ^ ( ulCrc >> 8 );

	case 0:
		*pulCRC = ulCrc;
		return;
	}

	nFront = ( ( unsigned int )pb ) & 3;
	iLen -= nFront;
	switch ( nFront )
	{
	case 3:
		ulCrc  = pulCRCTable[ *pb++ ^ ( unsigned char )ulCrc ] ^ ( ulCrc >> 8 );
	case 2:
		ulCrc  = pulCRCTable[ *pb++ ^ ( unsigned char )ulCrc ] ^ ( ulCrc >> 8 );
	case 1:
		ulCrc  = pulCRCTable[ *pb++ ^ ( unsigned char )ulCrc ] ^ ( ulCrc >> 8 );
	}

	nMain = iLen >> 3;
	while ( nMain-- )
	{
		ulCrc ^= ( *( CRC32_t * )pb );
		ulCrc  = pulCRCTable[ ( unsigned char )ulCrc ] ^ ( ulCrc >> 8 );
		ulCrc  = pulCRCTable[ ( unsigned char )ulCrc ] ^ ( ulCrc >> 8 );
		ulCrc  = pulCRCTable[ ( unsigned char )ulCrc ] ^ ( ulCrc >> 8 );
		ulCrc  = pulCRCTable[ ( unsigned char )ulCrc ] ^ ( ulCrc >> 8 );
		ulCrc ^= ( *( CRC32_t * )( pb + 4 ) );
		ulCrc  = pulCRCTable[ ( unsigned char )ulCrc ] ^ ( ulCrc >> 8 );
		ulCrc  = pulCRCTable[ ( unsigned char )ulCrc ] ^ ( ulCrc >> 8 );
		ulCrc  = pulCRCTable[ ( unsigned char )ulCrc ] ^ ( ulCrc >> 8 );
		ulCrc  = pulCRCTable[ ( unsigned char )ulCrc ] ^ ( ulCrc >> 8 );
		pb += 8;
	}

	iLen &= 7;
	goto JustAfew;
}

void CRC32_Final( CRC32_t* pulCRC )
{
	*pulCRC ^= CRC32_XOR_VALUE;
}

CRC32_t CRC32_GetTableEntry( unsigned int iSlot )
{
	return pulCRCTable[ ( unsigned char )iSlot ];
}
#pragma endregion
#pragma endregion
