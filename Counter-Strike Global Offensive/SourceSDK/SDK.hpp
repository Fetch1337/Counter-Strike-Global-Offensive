#pragma once

#include "../Core/Includes/Common.hpp"

#include "DataTypes/Color.hpp"
#include "DataTypes/Vector.hpp"
#include "DataTypes/Vector2D.hpp"
#include "DataTypes/Vector4D.hpp"
#include "DataTypes/QAngle.hpp"
#include "DataTypes/Matrix.hpp"
#include "DataTypes/UtlMemory.hpp"
#include "DataTypes/UtlStack.hpp"
#include "DataTypes/UtlVector.hpp"

// 
// macros
// 
#pragma region decl_macros
#define MULTIPLAYER_BACKUP 150

#define FL_ONGROUND ( 1 << 0 )
#define FL_DUCKING ( 1 << 1 )

#define IN_ATTACK ( 1 << 0 )
#define IN_JUMP ( 1 << 1 )
#define IN_DUCK ( 1 << 2 )
#define IN_FORWARD ( 1 << 3 )
#define IN_BACK ( 1 << 4 )
#define IN_USE ( 1 << 5 )
#define IN_CANCEL ( 1 << 6 )
#define IN_LEFT ( 1 << 7 )
#define IN_RIGHT ( 1 << 8 )
#define IN_MOVELEFT ( 1 << 9 )
#define IN_MOVERIGHT ( 1 << 10 )
#define IN_ATTACK2 ( 1 << 11 )
#define IN_RUN ( 1 << 12 )
#define IN_RELOAD ( 1 << 13 )
#define IN_ALT1 ( 1 << 14 )
#define IN_ALT2 ( 1 << 15 )
#define IN_SCORE ( 1 << 16 )
#define IN_SPEED ( 1 << 17 )
#define IN_WALK ( 1 << 18 )
#define IN_ZOOM ( 1 << 19 )
#define IN_WEAPON1 ( 1 << 20 )
#define IN_WEAPON2 ( 1 << 21 )
#define IN_BULLRUSH ( 1 << 22 )
#define IN_GRENADE1 ( 1 << 23 )
#define IN_GRENADE2 ( 1 << 24 )
#pragma endregion

// 
// enums
// 
#pragma region decl_enums
enum ELifeState : int
{
	LIFE_ALIVE = 0,
	LIFE_DYING,
	LIFE_DEAD,
	LIFE_RESPAWNABLE,
	LIFE_DISCARDBODY
};

enum EMoveType : int
{
	MOVETYPE_NONE = 0,
	MOVETYPE_ISOMETRIC,
	MOVETYPE_WALK,
	MOVETYPE_STEP,
	MOVETYPE_FLY,
	MOVETYPE_FLYGRAVITY,
	MOVETYPE_VPHYSICS,
	MOVETYPE_PUSH,
	MOVETYPE_NOCLIP,
	MOVETYPE_LADDER,
	MOVETYPE_OBSERVER,
	MOVETYPE_CUSTOM,
	MOVETYPE_LAST = MOVETYPE_CUSTOM,
	MOVETYPE_MAX_BITS = 4
};

enum ESendPropType
{
	DPT_Int = 0,
	DPT_Float,
	DPT_Vector,
	DPT_VectorXY,
	DPT_String,
	DPT_Array,
	DPT_DataTable,
	DPT_NUMSendPropTypes,
};

enum EMapLoadType
{
	MapLoad_NewGame = 0,
	MapLoad_LoadGame,
	MapLoad_Transition,
	MapLoad_Background,
};

enum EClientFrameStage
{
	FRAME_UNDEFINED = -1,
	FRAME_START,
	FRAME_NET_UPDATE_START,
	FRAME_NET_UPDATE_POSTDATAUPDATE_START,
	FRAME_NET_UPDATE_POSTDATAUPDATE_END,
	FRAME_NET_UPDATE_END,
	FRAME_RENDER_START,
	FRAME_RENDER_END,
};

enum EFontDrawType : int
{
	FONT_DRAW_DEFAULT = 0,
	FONT_DRAW_NONADDITIVE,
	FONT_DRAW_ADDITIVE,
	FONT_DRAW_TYPE_COUNT = 2
};

enum EFontFlags
{
	FONTFLAG_NONE,
	FONTFLAG_ITALIC = 0x001,
	FONTFLAG_UNDERLINE = 0x002,
	FONTFLAG_STRIKEOUT = 0x004,
	FONTFLAG_SYMBOL = 0x008,
	FONTFLAG_ANTIALIAS = 0x010,
	FONTFLAG_GAUSSIANBLUR = 0x020,
	FONTFLAG_ROTARY = 0x040,
	FONTFLAG_DROPSHADOW = 0x080,
	FONTFLAG_ADDITIVE = 0x100,
	FONTFLAG_OUTLINE = 0x200,
	FONTFLAG_CUSTOM = 0x400,
	FONTFLAG_BITMAP = 0x800,
};

enum EButtonCode : int
{
	BUTTON_CODE_INVALID = -1,
	BUTTON_CODE_NONE = 0,

	KEY_FIRST = 0,
	KEY_NONE = KEY_FIRST,

	/* keys */
	KEY_0,
	KEY_1,
	KEY_2,
	KEY_3,
	KEY_4,
	KEY_5,
	KEY_6,
	KEY_7,
	KEY_8,
	KEY_9,
	KEY_A,
	KEY_B,
	KEY_C,
	KEY_D,
	KEY_E,
	KEY_F,
	KEY_G,
	KEY_H,
	KEY_I,
	KEY_J,
	KEY_K,
	KEY_L,
	KEY_M,
	KEY_N,
	KEY_O,
	KEY_P,
	KEY_Q,
	KEY_R,
	KEY_S,
	KEY_T,
	KEY_U,
	KEY_V,
	KEY_W,
	KEY_X,
	KEY_Y,
	KEY_Z,
	KEY_PAD_0,
	KEY_PAD_1,
	KEY_PAD_2,
	KEY_PAD_3,
	KEY_PAD_4,
	KEY_PAD_5,
	KEY_PAD_6,
	KEY_PAD_7,
	KEY_PAD_8,
	KEY_PAD_9,
	KEY_PAD_DIVIDE,
	KEY_PAD_MULTIPLY,
	KEY_PAD_MINUS,
	KEY_PAD_PLUS,
	KEY_PAD_ENTER,
	KEY_PAD_DECIMAL,
	KEY_LBRACKET,
	KEY_RBRACKET,
	KEY_SEMICOLON,
	KEY_APOSTROPHE,
	KEY_BACKQUOTE,
	KEY_COMMA,
	KEY_PERIOD,
	KEY_SLASH,
	KEY_BACKSLASH,
	KEY_MINUS,
	KEY_EQUAL,
	KEY_ENTER,
	KEY_SPACE,
	KEY_BACKSPACE,
	KEY_TAB,
	KEY_CAPSLOCK,
	KEY_NUMLOCK,
	KEY_ESCAPE,
	KEY_SCROLLLOCK,
	KEY_INSERT,
	KEY_DELETE,
	KEY_HOME,
	KEY_END,
	KEY_PAGEUP,
	KEY_PAGEDOWN,
	KEY_BREAK,
	KEY_LSHIFT,
	KEY_RSHIFT,
	KEY_LALT,
	KEY_RALT,
	KEY_LCONTROL,
	KEY_RCONTROL,
	KEY_LWIN,
	KEY_RWIN,
	KEY_APP,
	KEY_UP,
	KEY_LEFT,
	KEY_DOWN,
	KEY_RIGHT,
	KEY_F1,
	KEY_F2,
	KEY_F3,
	KEY_F4,
	KEY_F5,
	KEY_F6,
	KEY_F7,
	KEY_F8,
	KEY_F9,
	KEY_F10,
	KEY_F11,
	KEY_F12,
	KEY_CAPSLOCKTOGGLE,
	KEY_NUMLOCKTOGGLE,
	KEY_SCROLLLOCKTOGGLE,

	KEY_LAST = KEY_SCROLLLOCKTOGGLE,
	KEY_COUNT = KEY_LAST - KEY_FIRST + 1,

	/* mouse */
	MOUSE_FIRST = KEY_LAST + 1,

	MOUSE_LEFT = MOUSE_FIRST,
	MOUSE_RIGHT,
	MOUSE_MIDDLE,
	MOUSE_4,
	MOUSE_5,
	MOUSE_WHEEL_UP,		// A fake button which is 'pressed' and 'released' when the wheel is moved up 
	MOUSE_WHEEL_DOWN,	// A fake button which is 'pressed' and 'released' when the wheel is moved down

	MOUSE_LAST = MOUSE_WHEEL_DOWN,
	MOUSE_COUNT = MOUSE_LAST - MOUSE_FIRST + 1,
};

enum EFieldTypes : int
{
	FIELD_VOID = 0,			// No type or value
	FIELD_FLOAT,			// Any floating point value
	FIELD_STRING,			// A string ID (return from ALLOC_STRING)
	FIELD_VECTOR,			// Any vector, QAngle, or AngularImpulse
	FIELD_QUATERNION,		// A quaternion
	FIELD_INTEGER,			// Any integer or enum
	FIELD_BOOLEAN,			// boolean, implemented as an int, I may use this as a hint for compression
	FIELD_SHORT,			// 2 byte integer
	FIELD_CHARACTER,		// a byte
	FIELD_COLOR32,			// 8-bit per channel r,g,b,a (32bit color)
	FIELD_EMBEDDED,			// an embedded object with a datadesc, recursively traverse and embedded class/structure based on an additional typedescription
	FIELD_CUSTOM,			// special type that contains function pointers to it's read/write/parse functions
	FIELD_CLASSPTR,			// CBaseEntity*
	FIELD_EHANDLE,			// Entity handle
	FIELD_EDICT,			// edict_t*
	FIELD_POSITION_VECTOR,	// A world coordinate (these are fixed up across level transitions automagically)
	FIELD_TIME,				// a floating point time (these are fixed up automatically too!)
	FIELD_TICK,				// an integer tick count( fixed up similarly to time)
	FIELD_MODELNAME,		// Engine string that is a model name (needs precache)
	FIELD_SOUNDNAME,		// Engine string that is a sound name (needs precache)
	FIELD_INPUT,			// a list of inputed data fields (all derived from CMultiInputVar)
	FIELD_FUNCTION,			// A class function pointer (Think, Use, etc)
	FIELD_VMATRIX,			// a vmatrix (output coords are NOT worldspace)
	FIELD_VMATRIX_WORLDSPACE,// A VMatrix that maps some local space to world space (translation is fixed up on level transitions)
	FIELD_MATRIX3X4_WORLDSPACE,	// matrix3x4_t that maps some local space to world space (translation is fixed up on level transitions)
	FIELD_INTERVAL,			// a start and range floating point interval ( e.g., 3.2->3.6 == 3.2 and 0.4 )
	FIELD_MODELINDEX,		// a model index
	FIELD_MATERIALINDEX,	// a material index (using the material precache string table)
	FIELD_VECTOR2D,			// 2 floats
	FIELD_INTEGER64,		// 64bit integer
	FIELD_VECTOR4D,			// 4 floats
	FIELD_TYPECOUNT
};

enum
{
	TD_OFFSET_NORMAL = 0,
	TD_OFFSET_PACKED = 1,
	TD_OFFSET_COUNT
};
#pragma endregion

// 
// unimplemented
// 
#pragma region decl_unimplemented
struct Model_t;
class CSendProp;
class CConBase;
class CConCmd;
class IHudChat;
#pragma endregion

// 
// structs
// 
#pragma region decl_structs
struct String_t;
struct Vertex_t;
struct DataMap_t;
struct TypeDescription_t;
#pragma endregion

// 
// classes
// 
#pragma region decl_classes
class IHandleEntity;
class IClientUnknown;
class ICollideable;
class IClientNetworkable;
class IClientRenderable;
class IClientEntity;
class CBaseEntity;
class CBaseAnimating;
class CBaseCombatCharacter;
class CBasePlayer;
class CBaseCombatWeapon;
class CWeaponCSBaseGun;

class DVariant;
class CRecvProxyData;
class RecvProp;
class RecvTable;

class ClientClass;
class CUserCmd;
class CVerifiedUserCmd;
class CGlobalVarsBase;
class CGlobalVars;
class CMoveData;
class CConVar;
class CViewSetup;
#pragma endregion

// 
// interfaces
// 
#pragma region decl_interfaces
class IBaseClientDLL;
class IClientModeShared;
class IClientEntityList;
class IGameMovement;
class IPrediction;
class IMoveHelper;
class IInput;
class IInputSystem;
class ISurface;
class IVEngineClient;
class IPanel;
class IAppSystem;
class IConVar;
#pragma endregion

// 
// types
// 
#pragma region decl_types
using CRC32_t = unsigned int;
using VPANEL = unsigned int;
using HFont = unsigned long;
using HCursor = unsigned long;
using CBaseHandle = unsigned long;
using CVarDLLIdentifier_t = int;
#pragma endregion

// 
// function types
// 
#pragma region decl_function_types
using CreateInterfaceFn = void* ( * )( const char*, int* );
using RecvVarProxyFn = void ( * )( const CRecvProxyData*, void*, void* );
using CommandCallbackV1 = void( __cdecl* )( );
using ChangeCallback = void( __cdecl* )( void*, const char*, float );
#pragma endregion


// 
// implementation
// 
#pragma region impl_structs
struct String_t
{
public:
	const char* ToCStr( ) const;
protected:
	const char* pszValue;
};

struct Vertex_t
{
	Vertex_t( ) = default;

	Vertex_t( const Vector2D& vecPosition, const Vector2D& vecCoordinate = Vector2D( 0, 0 ) )
	{
		this->m_vecPosition = vecPosition;
		this->m_vecCoordinate = vecCoordinate;
	}

	void Init( const Vector2D& vecPosition, const Vector2D& vecCoordinate = Vector2D( 0, 0 ) )
	{
		this->m_vecPosition = vecPosition;
		this->m_vecCoordinate = vecCoordinate;
	}

	Vector2D m_vecPosition = { };
	Vector2D m_vecCoordinate = { };
};

struct TypeDescription_t
{
public:
	EFieldTypes m_iFieldType;
	const char* m_szFieldName;
	int m_iFieldOffset[ TD_OFFSET_COUNT ];
	unsigned short m_uFieldSize;
	short m_fFlags;
	char pad0[ 0xC ];
	DataMap_t* m_pTypeDescription;
	char pad1[ 0x18 ];
};

struct DataMap_t
{
	TypeDescription_t* m_pDataDesc;
	int m_nDataFields;
	const char* m_szDataClassName;
	DataMap_t* m_pBaseMap;
	bool m_bChainsValidated;
	bool m_bPackedOffsetsComputed;
	int m_iPackedSize;
};
#pragma endregion

#pragma region impl_classes
class DVariant
{
public:
	union
	{
		float m_Float;
		int m_Int;
		const char* m_pString;
		void* m_pData;
		float m_Vector[ 3 ];
	};
	ESendPropType m_Type;
};

class CRecvProxyData
{
public:
	const RecvProp* m_pRecvProp;
private:
	char pad0[ 0x4 ];
public:
	DVariant m_Value;
	int m_iElement;
	int m_ObjectID;
};

class RecvProp
{
public:
	const char* m_pVarName;
	ESendPropType m_RecvType;
	int m_Flags;
	int m_StringBufferSize;
	bool m_bInsideArray;
	const void* m_pExtraData;
	RecvProp* m_pArrayProp;
	void* m_ArrayLengthProxy;
	RecvVarProxyFn m_ProxyFn;
	void* m_DataTableProxyFn;
	RecvTable* m_pDataTable;
	int m_Offset;
	int m_ElementStride;
	int m_nElements;
	const char* m_pParentArrayPropName;
};

class RecvTable
{
public:
	RecvProp* m_pProps;
	int m_nProps;
	void* m_pDecoder;
	const char* m_pNetTableName;
	bool m_bInitialized;
	bool m_bInMainList;
};

class ClientClass
{
public:
	void* m_pCreateFn;
	void* m_pCreateEventFn;
	const char* m_pNetworkName;
	RecvTable* m_pRecvTable;
	ClientClass* m_pNext;
	int m_ClassID;
};

class CUserCmd
{
public:
	CUserCmd( );
	CUserCmd( const CUserCmd& Cmd );
public:
	virtual ~CUserCmd( );
public:
	void Reset( );
	CRC32_t GetChecksum( ) const;
public:
	CUserCmd& operator = ( const CUserCmd& Cmd );
public:
	int m_iCommandNumber = 0;
	int m_iTickCount = 0;
	QAngle m_angViewAngles = { };
	Vector m_vecAimDirection = { };
	float m_flForwardMove = 0.0f;
	float m_flSideMove = 0.0f;
	float m_flUpMove = 0.0f;
	int m_iButtons = 0;
	std::uint8_t m_uImpulse = 0u;
	int m_iWeaponSelect = 0;
	int m_iWeaponSubtype = 0;
	int m_iRandomSeed = 0;
	short m_sMouseDx = 0;
	short m_sMouseDy = 0;
	bool m_bHasBeenPredicted = false;
	QAngle m_angHeadAngles = { };
	Vector m_vecHeadOffset = { };
};

class CVerifiedUserCmd
{
public:
	CUserCmd m_Cmd = { };
	CRC32_t m_Crc = 0u;
};

class CGlobalVarsBase
{
public:
	float m_flRealTime = 0.0f;
	int m_iFrameCount = 0;
	float m_flAbsoluteFrameTime = 0.0f;
	float m_flAbsoluteFrameStartTimeStdDev = 0.0f;
	float m_flCurrentTime = 0.0f;
	float m_flFrameTime = 0.0f;
	int m_iMaxClients = 0;
	int m_iTickCount = 0;
	float m_flIntervalPerTick = 0.0f;
	float m_flInterpolationAmount = 0.0f;
	int m_iSimTicksThisFrame = 0;
	int m_iNetworkProtocol = 0;
	void* m_pSaveData = nullptr;
	bool m_bClient = false;
	int m_iTimestampNetworkingBase = 0;
	int m_iTimestampRandomizeWindow = 0;
};

class CGlobalVars : public CGlobalVarsBase
{
public:
	String_t m_strMapName = { };
	String_t m_strMapGroupName = { };
	int m_iMapVersion = 0;
	String_t m_strStartSpot = { };
	EMapLoadType m_eLoadType = MapLoad_NewGame;
	bool m_bMapLoadFailed = false;
	bool m_bDeathMatch = false;
	bool m_bCoop = false;
	bool m_bTeamPlay = false;
	int m_iMaxEntities = 0;
	int m_iServerCount = 0;
	void* m_pEdicts = nullptr;
};

class CMoveData
{
private:
	char pad0[ 1024 ];
};

class CConVar
{
public:
	const char* GetName( );
	float		GetFloat( );
	int			GetInt( );
	bool		GetBool( );
	const char* GetString( );

	void SetValue( const char* szValue );
	void SetValue( float flValue );
	void SetValue( int iValue );
	void SetValue( Color colValue );

public:
	char							pad0[ 0x4 ];
	CConVar*						m_pNext;
	bool							m_bRegistered;
	const char*						m_szName;
	const char*						m_szHelpString;
	int								m_nFlags;
	CommandCallbackV1				m_pCallback;
	CConVar*						m_pParent;
	const char*						m_szDefaultValue;
	char*							m_szString;
	int								m_iStringLength;
	float							m_flValue;
	int								m_iValue;
	bool							m_bHasMin;
	float							m_flMinValue;
	bool							m_bHasMax;
	float							m_flMaxValue;
	CUtlVector<ChangeCallback>		m_fnChangeCallbacks;
};

class CViewSetup
{
public:
	int m_iX;
	int m_iUnscaledX;
	int m_iY;
	int m_iUnscaledY;
	int m_iWidth;
	int m_iUnscaledWidth;
	int m_iHeight;
	int m_iUnscaledHeight;
	bool m_bOrtho;
	char pad0[ 0x8F ];
	float m_flFOV;
	float m_flViewModelFOV;
	Vector m_vecOrigin;
	QAngle m_angView;
	float m_flNearZ;
	float m_flFarZ;
	float m_flNearViewmodelZ;
	float m_flFarViewmodelZ;
	float m_flAspectRatio;
	float m_flNearBlurDepth;
	float m_flNearFocusDepth;
	float m_flFarFocusDepth;
	float m_flFarBlurDepth;
	float m_flNearBlurRadius;
	float m_flFarBlurRadius;
	float m_flDoFQuality;
	int m_nMotionBlurMode;
	float m_flShutterTime;
	Vector m_vecShutterOpenPosition;
	QAngle m_vecShutterOpenAngles;
	Vector m_vecShutterClosePosition;
	QAngle m_vecShutterCloseAngles;
	float m_flOffCenterTop;
	float m_flOffCenterBottom;
	float m_flOffCenterLeft;
	float m_flOffCenterRight;
	bool m_bOffCenter;
	bool m_bRenderToSubrectOfLargerScreen;
	bool m_bDoBloomAndToneMapping;
	bool m_bDoDepthOfField;
	bool m_bHDRTarget;
	bool m_bDrawWorldNormal;
	bool m_bCullFontFaces;
	bool m_bCacheFullSceneState;
	bool m_bCSMView;
};
#pragma endregion

#pragma region impl_interfaces
class IBaseClientDLL
{
public:
	ClientClass* GetAllClasses( );
};

class IClientModeShared
{
public:
	char pad0[ 0x1B ];
	void* m_pViewport;
	IHudChat* m_pChatElement;
	HCursor m_hCursorNone;
	void* m_pWeaponSelection;
	int m_nRootSize[ 2 ];
};

class IClientEntityList
{
public:
	IClientEntity* GetClientEntity( int iEntNum );
	IClientEntity* GetClientEntityFromHandle( CBaseHandle hEnt );
	int GetHighestEntityIndex( );
};

class IGameMovement
{
public:
	void ProcessMovement( CBasePlayer* pPlayer, CMoveData* pMove );
	void StartTrackPredictionErrors( CBasePlayer* pPlayer );
	void FinishTrackPredictionErrors( CBasePlayer* pPlayer );
};

class IPrediction
{
public:
	void SetupMove( CBasePlayer* pPlayer, CUserCmd* pCmd, IMoveHelper* pHelper, CMoveData* pMove );
	void FinishMove( CBasePlayer* pPlayer, CUserCmd* pCmd, CMoveData* pMove );
};

class IMoveHelper
{
public:
	void SetHost( CBaseEntity* pHost );
};

class IInput
{
public:
	char pad0[ 0xC ];
	bool m_bTrackIRAvailable;
	bool m_bMouseInitialized;
	bool m_bMouseActive;
	char pad1[ 0x9A ];
	bool m_bCameraInThirdPerson;
	char pad2[ 0x2 ];
	Vector m_vecCameraOffset;
	char pad3[ 0x38 ];
	CUserCmd* m_pCommands;
	CVerifiedUserCmd* m_pVerifiedCommands;

	CUserCmd* GetUserCmd( int iSequenceNumber );
	CVerifiedUserCmd* GetVerifiedUserCmd( int iSequenceNumber );
};

class IInputSystem
{
public:
	void EnableInput( bool bEnable );
	bool IsButtonDown( EButtonCode buttonCode );
	void ResetInputState( );
	const char* ButtonCodeToString( EButtonCode buttonCode );
	EButtonCode VirtualKeyToButtonCode( int iVirtualKey );
	void GetCursorPosition( int* pX, int* pY );
};

class ISurface
{
public:
	void DrawSetColor( Color colDraw );
	void DrawSetColor( int r, int g, int b, int a );
	void DrawFilledRect( int x0, int y0, int x1, int y1 );
	void DrawFilledRectFade( int x0, int y0, int x1, int y1, uint32_t uAlpha0, uint32_t uAlpha1, bool bHorizontal );
	void DrawOutlinedRect( int x0, int y0, int x1, int y1 );
	void DrawLine( int x0, int y0, int x1, int y1 );
	void DrawPolyLine( int* x, int* y, int nPoints );
	void DrawSetTextFont( HFont hFont );
	void DrawSetTextColor( Color color );
	void DrawSetTextColor( int r, int g, int b, int a );
	void DrawSetTextPos( int x, int y );
	void DrawPrintText( const wchar_t* wszText, int nTextLength, EFontDrawType DrawType = FONT_DRAW_DEFAULT );
	void DrawSetTextureRGBA( int nIndex, const unsigned char* rgba, int iWide, int iTall );
	void DrawSetTexture( int nIndex );
	int CreateNewTextureID( bool bProcedural = false );
	void UnLockCursor( );
	void LockCursor( );
	HFont FontCreate( );
	bool SetFontGlyphSet( HFont hFont, const char* szWindowsFontName, int iTall, int iWeight, int iBlur, int nScanLines, int iFlags, int nRangeMin = 0, int nRangeMax = 0 );
	void GetTextSize( HFont hFont, const wchar_t* wszText, int& iWide, int& iTall );
	void PlaySoundSurface( const char* szFileName );
	void DrawOutlinedCircle( int x, int y, int iRadius, int nSegments );
	void DrawTexturedPolygon( int n, Vertex_t* pVertice, bool bClipVertices = true );
};

class IVEngineClient
{
public:
	void GetScreenSize( int& iWidth, int& iHeight );
	bool IsConsoleVisible( );
	int GetLocalPlayer( );
	float Time( );
	void GetViewAngles( QAngle& angOutput );
	void SetViewAngles( QAngle& angInput );
	int GetMaxClients( );
	bool IsInGame( );
	bool IsConnected( );
	const VMatrix& WorldToScreenMatrix( );
	void ClientCmd_Unrestricted( const char* szCmdString );
};

class IPanel
{
public:
	const char* GetName( VPANEL vguiPanel );
};

class IAppSystem
{
private:
	virtual void function0( ) = 0;
	virtual void function1( ) = 0;
	virtual void function2( ) = 0;
	virtual void function3( ) = 0;
	virtual void function4( ) = 0;
	virtual void function5( ) = 0;
	virtual void function6( ) = 0;
	virtual void function7( ) = 0;
	virtual void function8( ) = 0;
};

class IConVar : public IAppSystem
{
public:
	virtual CVarDLLIdentifier_t	AllocateDLLIdentifier( ) = 0;
	virtual void			RegisterConCommand( CConVar* pCommandBase, int iDefaultValue = 1 ) = 0;
	virtual void			UnregisterConCommand( CConVar* pCommandBase ) = 0;
	virtual void			UnregisterConCommands( CVarDLLIdentifier_t id ) = 0;
	virtual const char*		GetCommandLineValue( const char* szVariableName ) = 0;
	virtual CConBase*		FindCommandBase( const char* szName ) = 0;
	virtual const CConBase* FindCommandBase( const char* szName ) const = 0;
	virtual CConVar*		FindVar( const char* szVariableName ) = 0;
	virtual const CConVar*	FindVar( const char* szVariableName ) const = 0;
	virtual CConCmd*		FindCommand( const char* szName ) = 0;
	virtual const CConCmd*	FindCommand( const char* szName ) const = 0;
	virtual void			InstallGlobalChangeCallback( ChangeCallback callback ) = 0;
	virtual void			RemoveGlobalChangeCallback( ChangeCallback callback ) = 0;
	virtual void			CallGlobalChangeCallbacks( CConVar* pVar, const char* szOldString, float flOldValue ) = 0;
	virtual void			InstallConsoleDisplayFunc( void* pDisplayFunc ) = 0;
	virtual void			RemoveConsoleDisplayFunc( void* pDisplayFunc ) = 0;
	virtual void			ConsoleColorPrintf( const Color& color, const char* pFormat, ... ) const = 0;
	virtual void			ConsolePrintf( const char* pFormat, ... ) const = 0;
	virtual void			ConsoleDPrintf( const char* pFormat, ... ) const = 0;
	virtual void			RevertFlaggedConVars( int nFlag ) = 0;
};

#pragma endregion

#pragma region decl_functions
void RandomSeed( unsigned int iSeed );
float RandomFloat( float flMin, float flMax );
int RandomInt( int flMin, int flMax );

void CRC32_Init( CRC32_t* pulCRC );
void CRC32_ProcessBuffer( CRC32_t* pulCRC, const void* pPointer, int iLen );
void CRC32_Final( CRC32_t* pulCRC );
CRC32_t CRC32_GetTableEntry( unsigned int iSlot );
#pragma endregion