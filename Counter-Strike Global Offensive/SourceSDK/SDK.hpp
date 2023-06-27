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

#define TIME_TO_TICKS( dt ) ( int( 0.5f + float( dt ) / Source->Interfaces.m_pGlobalVars->m_flIntervalPerTick ) )
#define TICKS_TO_TIME( t )  ( Source->Interfaces.m_pGlobalVars->m_flIntervalPerTick * float( t ) )
#define ROUND_TO_TICKS( t ) ( Source->Interfaces.m_pGlobalVars->m_flIntervalPerTick * TIME_TO_TICKS( t ) )
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

enum ESendPropType : int
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

enum EMapLoadType : int
{
	MapLoad_NewGame = 0,
	MapLoad_LoadGame,
	MapLoad_Transition,
	MapLoad_Background,
};

enum EClientFrameStage : int
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

enum EFontFlags : int
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

enum EItemDefinitionIndex : short
{
	WEAPON_NONE = 0,
	WEAPON_DEAGLE = 1,
	WEAPON_ELITE = 2,
	WEAPON_FIVESEVEN = 3,
	WEAPON_GLOCK = 4,
	WEAPON_AK47 = 7,
	WEAPON_AUG = 8,
	WEAPON_AWP = 9,
	WEAPON_FAMAS = 10,
	WEAPON_G3SG1 = 11,
	WEAPON_GALILAR = 13,
	WEAPON_M249 = 14,
	WEAPON_M4A1 = 16,
	WEAPON_MAC10 = 17,
	WEAPON_P90 = 19,
	WEAPON_ZONE_REPULSOR = 20,
	WEAPON_MP5SD = 23,
	WEAPON_UMP45 = 24,
	WEAPON_XM1014 = 25,
	WEAPON_BIZON = 26,
	WEAPON_MAG7 = 27,
	WEAPON_NEGEV = 28,
	WEAPON_SAWEDOFF = 29,
	WEAPON_TEC9 = 30,
	WEAPON_TASER = 31,
	WEAPON_HKP2000 = 32,
	WEAPON_MP7 = 33,
	WEAPON_MP9 = 34,
	WEAPON_NOVA = 35,
	WEAPON_P250 = 36,
	WEAPON_SHIELD = 37,
	WEAPON_SCAR20 = 38,
	WEAPON_SG556 = 39,
	WEAPON_SSG08 = 40,
	WEAPON_KNIFE_GG = 41,
	WEAPON_KNIFE = 42,
	WEAPON_FLASHBANG = 43,
	WEAPON_HEGRENADE = 44,
	WEAPON_SMOKEGRENADE = 45,
	WEAPON_MOLOTOV = 46,
	WEAPON_DECOY = 47,
	WEAPON_INCGRENADE = 48,
	WEAPON_C4 = 49,
	WEAPON_HEALTHSHOT = 57,
	WEAPON_KNIFE_T = 59,
	WEAPON_M4A1_SILENCER = 60,
	WEAPON_USP_SILENCER = 61,
	WEAPON_CZ75A = 63,
	WEAPON_REVOLVER = 64,
	WEAPON_TAGRENADE = 68,
	WEAPON_FISTS = 69,
	WEAPON_BREACHCHARGE = 70,
	WEAPON_TABLET = 72,
	WEAPON_MELEE = 74,
	WEAPON_AXE = 75,
	WEAPON_HAMMER = 76,
	WEAPON_SPANNER = 78,
	WEAPON_KNIFE_GHOST = 80,
	WEAPON_FIREBOMB = 81,
	WEAPON_DIVERSION = 82,
	WEAPON_FRAG_GRENADE = 83,
	WEAPON_SNOWBALL = 84,
	WEAPON_BUMPMINE = 85,
	WEAPON_KNIFE_BAYONET = 500,
	WEAPON_KNIFE_CSS = 503,
	WEAPON_KNIFE_FLIP = 505,
	WEAPON_KNIFE_GUT = 506,
	WEAPON_KNIFE_KARAMBIT = 507,
	WEAPON_KNIFE_M9_BAYONET = 508,
	WEAPON_KNIFE_TACTICAL = 509,
	WEAPON_KNIFE_FALCHION = 512,
	WEAPON_KNIFE_SURVIVAL_BOWIE = 514,
	WEAPON_KNIFE_BUTTERFLY = 515,
	WEAPON_KNIFE_PUSH = 516,
	WEAPON_KNIFE_CORD = 517,
	WEAPON_KNIFE_CANIS = 518,
	WEAPON_KNIFE_URSUS = 519,
	WEAPON_KNIFE_GYPSY_JACKKNIFE = 520,
	WEAPON_KNIFE_OUTDOOR = 521,
	WEAPON_KNIFE_STILETTO = 522,
	WEAPON_KNIFE_WIDOWMAKER = 523,
	WEAPON_KNIFE_SKELETON = 525,
	GLOVE_STUDDED_BROKENFANG = 4725,
	GLOVE_STUDDED_BLOODHOUND = 5027,
	GLOVE_T = 5028,
	GLOVE_CT = 5029,
	GLOVE_SPORTY = 5030,
	GLOVE_SLICK = 5031,
	GLOVE_LEATHER_HANDWRAPS = 5032,
	GLOVE_MOTORCYCLE = 5033,
	GLOVE_SPECIALIST = 5034,
	GLOVE_STUDDED_HYDRA = 5035,
	SPECIAL_AGENT_BLUEBERRIES_BUCKSHOT = 4619,
	SPECIAL_AGENT_TWO_TIMES_MCCOY_TACP = 4680,
	SPECIAL_AGENT_COMMANDOR_MAE_JAMISON = 4711,
	SPECIAL_AGENT_1ST_LIEUTENANT_FARLOW,
	SPECIAL_AGENT_JOHN_KASK,
	SPECIAL_AGENT_BIO_HAZ_SPECIALIST,
	SPECIAL_AGENT_SERGEANT_BOMBSON,
	SPECIAL_AGENT_CHEM_HAZ_SPECIALIST,
	SPECIAL_AGENT_REZAN_THE_REDSHIRT = 4718,
	SPECIAL_AGENT_SIR_BLOODY_MIAMI_DARRYL = 4726,
	SPECIAL_AGENT_SAFECRACKER_VOLTZMANN,
	SPECIAL_AGENT_LITTLE_KEV,
	SPECIAL_AGENT_GETAWAY_SALLY = 4730,
	SPECIAL_AGENT_NUMBER_K = 4732,
	SPECIAL_AGENT_SIR_BLOODY_SILENT_DARRYL = 4733,
	SPECIAL_AGENT_SIR_BLOODY_SKULLHEAD_DARRYL,
	SPECIAL_AGENT_SIR_BLOODY_DARRYL_ROYALE,
	SPECIAL_AGENT_SIR_BLOODY_LOUDMOUTH_DARRYL,
	SPECIAL_AGENT_T = 5036,
	SPECIAL_AGENT_CT = 5037,
	SPECIAL_AGENT_GROUND_REBEL = 5105,
	SPECIAL_AGENT_OSIRIS,
	SPECIAL_AGENT_SHAHMAT,
	SPECIAL_AGENT_MUHLIK,
	SPECIAL_AGENT_SOLDIER = 5205,
	SPECIAL_AGENT_ENFORCER,
	SPECIAL_AGENT_SLINGSHOT,
	SPECIAL_AGENT_STREET_SOLDIER,
	SPECIAL_AGENT_OPERATOR = 5305,
	SPECIAL_AGENT_MARKUS_DELROW,
	SPECIAL_AGENT_MICHAEL_SYFERS,
	SPECIAL_AGENT_AVA,
	SPECIAL_AGENT_3RD_COMMANDO_COMPANY = 5400,
	SPECIAL_AGENT_SEAL_TEAM_6_SOLDIER,
	SPECIAL_AGENT_BUCKSHOT,
	SPECIAL_AGENT_TWO_TIMES_MCCOY_USAF,
	SPECIAL_AGENT_RICKSAW,
	SPECIAL_AGENT_DRAGOMIR = 5500,
	SPECIAL_AGENT_MAXIMUS,
	SPECIAL_AGENT_REZAN_THE_READY,
	SPECIAL_AGENT_BLACKWOLF = 5503,
	SPECIAL_AGENT_THE_DOCTOR,
	SPECIAL_AGENT_DRAGOMIR_FOOTSOLDIERS,
	SPECIAL_AGENT_B_SQUADRON_OFFICER = 5601
};

enum EWeaponType : int
{
	WEAPONTYPE_KNIFE = 0,
	WEAPONTYPE_PISTOL = 1,
	WEAPONTYPE_SUBMACHINEGUN = 2,
	WEAPONTYPE_RIFLE = 3,
	WEAPONTYPE_SHOTGUN = 4,
	WEAPONTYPE_SNIPER = 5,
	WEAPONTYPE_MACHINEGUN = 6,
	WEAPONTYPE_C4 = 7,
	WEAPONTYPE_PLACEHOLDER = 8,
	WEAPONTYPE_GRENADE = 9,
	WEAPONTYPE_HEALTHSHOT = 11,
	WEAPONTYPE_FISTS = 12,
	WEAPONTYPE_BREACHCHARGE = 13,
	WEAPONTYPE_BUMPMINE = 14,
	WEAPONTYPE_TABLET = 15,
	WEAPONTYPE_MELEE = 16
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
struct TypeDescription_t;
struct DataMap_t;
struct PlayerInfo_t;
struct AimMatrixTransition_t;
struct AnimstatePose_t;
struct ProceduralFoot_t;
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
class CRecvProp;
class CRecvTable;

class CClientClass;
class CUserCmd;
class CVerifiedUserCmd;
class CGlobalVarsBase;
class CGlobalVars;
class CMoveData;
class CEventInfo;
class CConVar;
class CViewSetup;
class CWeaponInfo;
class CPlayerAnimationState;
class CAnimationLayer;
#pragma endregion

// 
// interfaces
// 
#pragma region decl_interfaces
class IBaseClientDLL;
class IClientModeShared;
class IClientEntityListener;
class IClientEntityList;
class IGameMovement;
class IPrediction;
class IMoveHelper;
class IInput;
class IInputSystem;
class IVEngineClient;
class INetChannel;
class IClientState;
class IPanel;
class IAppSystem;
class ISurface;
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
using IntRect = int[ 4 ];
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
	EFieldTypes			m_nFieldType;
	const char*			m_szFieldName;
	int					m_iFieldOffset;
	unsigned short		m_nFieldSize;
	short				m_nFlags;
	const char*			m_szExternalName;
	void*				m_pSaveRestoreOps;
	void*				m_pInputFunc;
	DataMap_t*			m_pDataMap;
	int					m_iFieldSizeInBytes;
	TypeDescription_t*	m_pOverrideField;
	int					m_iOverrideCount;
	float				m_flFieldTolerance;
	int					m_iFlatOffset[ TD_OFFSET_COUNT ];
	unsigned short		m_nFlatGroup;
};

struct DataMap_t
{
	TypeDescription_t*	m_pDataDesc;
	int					m_nDataFields;
	const char*			m_szDataClassName;
	DataMap_t*			m_pBaseMap;
	int					m_iPackedSize;
	void*				m_pOptimizedDataMap;
};

struct PlayerInfo_t
{
	std::uint64_t	ullVersion = 0ULL;
	union
	{
		std::uint64_t ullXuid;
		struct
		{
			std::uint32_t nXuidLow;
			std::uint32_t nXuidHigh;
		};
	};

	char			szName[ 128 ];
	int				nUserID;
	char			szSteamID[ 33 ];
	std::uint32_t	nFriendsID;
	char			szFriendsName[ 128 ];
	bool			bFakePlayer;
	bool			bIsHLTV;
	CRC32_t			uCustomFiles[ 4 ];
	std::uint8_t	dFilesDownloaded;
};

struct AimMatrixTransition_t
{
	void Init( void )
	{
		m_flDurationStateHasBeenValid = 0;
		m_flDurationStateHasBeenInValid = 0;
		m_flHowLongToWaitUntilTransitionCanBlendIn = 0.3f;
		m_flHowLongToWaitUntilTransitionCanBlendOut = 0.3f;
		m_flBlendValue = 0;
	}

	AimMatrixTransition_t( ) { Init( ); }

	float	m_flDurationStateHasBeenValid;
	float	m_flDurationStateHasBeenInValid;
	float	m_flHowLongToWaitUntilTransitionCanBlendIn;
	float	m_flHowLongToWaitUntilTransitionCanBlendOut;
	float	m_flBlendValue;
};

struct AnimstatePose_t
{
	bool		m_bInitialized;
	int			m_nIndex;
	const char* m_szName;

	AnimstatePose_t( )
	{
		m_bInitialized = false;
		m_nIndex = -1;
		m_szName = "";
	}
};

struct ProceduralFoot_t
{
	Vector	m_vecPosAnim;
	Vector	m_vecPosAnimLast;
	Vector	m_vecPosPlant;
	Vector	m_vecPlantVel;
	float	m_flLockAmount;
	float	m_flLastPlantTime;
};
#pragma endregion

#pragma region impl_classes
class DVariant
{
public:
	union
	{
		float		m_Float;
		int			m_Int;
		const char* m_pString;
		void*		m_pData;
		float		m_Vector[ 3 ];
	};
	ESendPropType m_Type;
};

class CRecvProxyData
{
public:
	const CRecvProp*	m_pRecvProp;
	char				pad0[ 0x4 ];
	DVariant			m_Value;
	int					m_iElement;
	int					m_ObjectID;
};

class CRecvProp
{
public:
	const char*		m_pVarName;
	ESendPropType	m_RecvType;
	int				m_Flags;
	int				m_StringBufferSize;
	bool			m_bInsideArray;
	const void*		m_pExtraData;
	CRecvProp*		m_pArrayProp;
	void*			m_ArrayLengthProxy;
	RecvVarProxyFn	m_ProxyFn;
	void*			m_DataTableProxyFn;
	CRecvTable*		m_pDataTable;
	int				m_Offset;
	int				m_ElementStride;
	int				m_nElements;
	const char*		m_pParentArrayPropName;
};

class CRecvTable
{
public:
	CRecvProp*	m_pProps;
	int			m_nProps;
	void*		m_pDecoder;
	const char* m_pNetTableName;
	bool		m_bInitialized;
	bool		m_bInMainList;
};

class CClientClass
{
public:
	void*			m_pCreateFn;
	void*			m_pCreateEventFn;
	const char*		m_pNetworkName;
	CRecvTable*		m_pRecvTable;
	CClientClass*	m_pNext;
	int				m_ClassID;
};

class CUserCmd
{
public:
	virtual			~CUserCmd( ) { };
	int				m_iCommandNumber = 0;
	int				m_iTickCount = 0;
	QAngle			m_angViewAngles = { };
	Vector			m_vecAimDirection = { };
	float			m_flForwardMove = 0.0f;
	float			m_flSideMove = 0.0f;
	float			m_flUpMove = 0.0f;
	int				m_iButtons = 0;
	std::uint8_t	m_uImpulse = 0u;
	int				m_iWeaponSelect = 0;
	int				m_iWeaponSubtype = 0;
	int				m_iRandomSeed = 0;
	short			m_sMouseDx = 0;
	short			m_sMouseDy = 0;
	bool			m_bHasBeenPredicted = false;
	QAngle			m_angHeadAngles = { };
	Vector			m_vecHeadOffset = { };

	CRC32_t GetChecksum( ) const;
};

class CVerifiedUserCmd
{
public:
	CUserCmd	m_Cmd = { };
	CRC32_t		m_Crc = 0u;
};

class CGlobalVarsBase
{
public:
	float	m_flRealTime = 0.0f;
	int		m_iFrameCount = 0;
	float	m_flAbsoluteFrameTime = 0.0f;
	float	m_flAbsoluteFrameStartTimeStdDev = 0.0f;
	float	m_flCurrentTime = 0.0f;
	float	m_flFrameTime = 0.0f;
	int		m_iMaxClients = 0;
	int		m_iTickCount = 0;
	float	m_flIntervalPerTick = 0.0f;
	float	m_flInterpolationAmount = 0.0f;
	int		m_iSimTicksThisFrame = 0;
	int		m_iNetworkProtocol = 0;
	void*	m_pSaveData = nullptr;
	bool	m_bClient = false;
	int		m_iTimestampNetworkingBase = 0;
	int		m_iTimestampRandomizeWindow = 0;
};

class CGlobalVars : public CGlobalVarsBase
{
public:
	String_t		m_strMapName = { };
	String_t		m_strMapGroupName = { };
	int				m_iMapVersion = 0;
	String_t		m_strStartSpot = { };
	EMapLoadType	m_eLoadType = MapLoad_NewGame;
	bool			m_bMapLoadFailed = false;
	bool			m_bDeathMatch = false;
	bool			m_bCoop = false;
	bool			m_bTeamPlay = false;
	int				m_iMaxEntities = 0;
	int				m_iServerCount = 0;
	void*			m_pEdicts = nullptr;
};

class CMoveData
{
private:
	char pad0[ 1024 ];
};

class CEventInfo
{
public:
	short				m_nClassID;
	float				m_flFireDelay;
	const void*			m_pSendTable;
	const CClientClass*	m_pClientClass;
	void*				m_pData;
	std::intptr_t		m_iPackedBits;
	int					m_iFlags;
	char				pad0[ 0x16 ];
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
	int		m_iX;
	int		m_iUnscaledX;
	int		m_iY;
	int		m_iUnscaledY;
	int		m_iWidth;
	int		m_iUnscaledWidth;
	int		m_iHeight;
	int		m_iUnscaledHeight;
	bool	m_bOrtho;
	char	pad0[ 0x8F ];
	float	m_flFOV;
	float	m_flViewModelFOV;
	Vector	m_vecOrigin;
	QAngle	m_angView;
	float	m_flNearZ;
	float	m_flFarZ;
	float	m_flNearViewmodelZ;
	float	m_flFarViewmodelZ;
	float	m_flAspectRatio;
	float	m_flNearBlurDepth;
	float	m_flNearFocusDepth;
	float	m_flFarFocusDepth;
	float	m_flFarBlurDepth;
	float	m_flNearBlurRadius;
	float	m_flFarBlurRadius;
	float	m_flDoFQuality;
	int		m_nMotionBlurMode;
	float	m_flShutterTime;
	Vector	m_vecShutterOpenPosition;
	QAngle	m_vecShutterOpenAngles;
	Vector	m_vecShutterClosePosition;
	QAngle	m_vecShutterCloseAngles;
	float	m_flOffCenterTop;
	float	m_flOffCenterBottom;
	float	m_flOffCenterLeft;
	float	m_flOffCenterRight;
	bool	m_bOffCenter;
	bool	m_bRenderToSubrectOfLargerScreen;
	bool	m_bDoBloomAndToneMapping;
	bool	m_bDoDepthOfField;
	bool	m_bHDRTarget;
	bool	m_bDrawWorldNormal;
	bool	m_bCullFontFaces;
	bool	m_bCacheFullSceneState;
	bool	m_bCSMView;
};

class CWeaponInfo
{
public:
	void*	m_pVTable;
	char	m_strConsoleName;
	char	pad0[ 0xC ];
	int		m_iMaxClip1;
	int		m_iMaxClip2;
	int		m_iDefaultClip1;
	int		m_iDefaultClip2;
	char	pad1[ 0x8 ];
	char*	m_szWorldModel;
	char*	m_szViewModel;
	char*	m_szDroppedMode;
	char	pad2[ 0x4 ];
	char*	m_szShotSound;
	char	pad3[ 0x38 ];
	char*	m_szEmptySound;
	char	pad4[ 0x4 ];
	char*	m_szBulletType;
	char	pad5[ 0x4 ];
	char*	m_szHudName;
	char*	m_szWeaponName;
	char	pad6[ 0x38 ];
	int		m_iWeaponType;
	char	pad7[ 0x4 ];
	int		m_iWeaponPrice;
	int		m_iKillAward;
	char*	m_szAnimationPrefix;
	float	m_flCycleTime;
	float	m_flCycleTimeAlt;
	float	m_flTimeToIdle;
	float	m_flIdleInterval;
	bool	m_bFullAuto;
	char	pad8[ 0x3 ];
	int		m_iDamage;
	float	m_flHeadShotMultiplier;
	float	m_flArmorRatio;
	int		m_iBullets;
	float	m_flPenetration;
	float	m_flFlinchVelocityModifierLarge;
	float	m_flFlinchVelocityModifierSmall;
	float	m_flRange;
	float	m_flRangeModifier;
	float	m_flThrowVelocity;
	char	pad9[ 0xC ];
	bool	m_bHasSilencer;
	char	pad10[ 0x3 ];
	char*	m_pSilencerModel;
	int		m_iCrosshairMinDistance;
	int		m_iCrosshairDeltaDistance;
	float	m_flMaxPlayerSpeed;
	float	m_flMaxPlayerSpeedAlt;
	float	m_flMaxPlayerSpeedMod;
	float	m_flSpread;
	float	m_flSpreadAlt;
	float	m_flInaccuracyCrouch;
	float	m_flInaccuracyCrouchAlt;
	float	m_flInaccuracyStand;
	float	m_flInaccuracyStandAlt;
	float	m_flInaccuracyJumpInitial;
	float	m_flInaccuracyJump;
	float	m_flInaccuracyJumpAlt;
	float	m_flInaccuracyLand;
	float	m_flInaccuracyLandAlt;
	float	m_flInaccuracyLadder;
	float	m_flInaccuracyLadderAlt;
	float	m_flInaccuracyFire;
	float	m_flInaccuracyFireAlt;
	float	m_flInaccuracyMove;
	float	m_flInaccuracyMoveAlt;
	float	m_flInaccuracyReload;
	int		m_iRecoilSeed;
	float	m_flRecoilAngle;
	float	m_flRecoilAngleAlt;
	float	m_flRecoilAngleVariance;
	float	m_flRecoilAngleVarianceAlt;
	float	m_flRecoilMagnitude;
	float	m_flRecoilMagnitudeAlt;
	float	m_flRecoilMagnitudeVariance;
	float	m_flRecoilMagnitudeVarianceAlt;
	float	m_flRecoveryTimeCrouch;
	float	m_flRecoveryTimeStand;
	float	m_flRecoveryTimeCrouchFinal;
	float	m_flRecoveryTimeStandFinal;
	char	pad11[ 0x28 ];
	char*	m_szWeaponClass;
	char	pad12[ 0x8 ];
	char*	m_szEjectBrassEffect;
	char*	m_szTracerEffect;
	int		m_iTracerFrequency;
	int		m_iTracerFrequencyAlt;
	char*	m_szMuzzleFlashEffect_1stPerson;
	char	pad13[ 0x4 ];
	char*	m_szMuzzleFlashEffect_3rdPerson;
	char	pad14[ 0x4 ];
	char*	m_szMuzzleSmokeEffect;
	float	m_flHeatPerShot;
	char*	m_szZoomInSound;
	char*	m_szZoomOutSound;
	float	m_flInaccuracyPitchShift;
	float	m_flInaccuracySoundThreshold;
	float	m_flBotAudibleRange;
	char	pad15[ 0xC ];
	bool	m_bHasBurstMode;
	bool	m_bIsRevolver;
};

class CAnimationState
{
public:
	void*					m_pAnimlayerOrderPreset;
	bool					m_bFirstRunSinceInit;
	bool					m_bFirstFootPlantSinceInit;
	int						m_iLastUpdateFrame;
	int						m_flEyePositionSmoothLerp;
	int						m_flStrafeChangeWeightSmoothFalloff;
	AimMatrixTransition_t	m_tStandWalkAim;
	AimMatrixTransition_t	m_tStandRunAim;
	AimMatrixTransition_t	m_tCrouchWalkAim;
	int						m_iModelIndex;
	int						m_iUnknownArray[ 2 ];
	LPVOID					m_pWeaponLastBoneSetup;
	CBasePlayer*			m_pBasePlayer;
	LPVOID					m_pWeapon;
	LPVOID					m_pWeaponLast;
	float					m_flLastUpdateTime;
	int						m_nLastUpdateFrame;
	float					m_flLastUpdateIncrement;
	float					m_flEyeYaw;
	float					m_flEyePitch;
	float					m_flFootYaw;
	float					m_flFootYawLast;
	float					m_flMoveYaw;
	float					m_flMoveYawIdeal;
	float					m_flMoveYawCurrentToIdeal;
	float					m_flTimeToAlignLowerBody;
	float					m_flPrimaryCycle;
	float					m_flMoveWeight;
	float					m_flMoveWeightSmoothed;
	float					m_flAnimDuckAmount;
	float					m_flDuckAdditional;
	float					m_flRecrouchWeight;
	Vector					m_vecPositionCurrent;
	Vector					m_vecPositionLast;
	Vector					m_vecVelocity;
	Vector					m_vecVelocityNormalized;
	Vector					m_vecVelocityNormalizedNonZero;
	float					m_flVelocityLengthXY;
	float					m_flVelocityLengthZ;
	float					m_flSpeedAsPortionOfRunTopSpeed;
	float					m_flSpeedAsPortionOfWalkTopSpeed;
	float					m_flSpeedAsPortionOfCrouchTopSpeed;
	float					m_flDurationMoving;
	float					m_flDurationStill;
	bool					m_bOnGround;
	bool					m_bLanding;
	char					m_pad0[ 0x2 ];
	float					m_flJumpToFall;
	float					m_flDurationInAir;
	float					m_flLeftGroundHeight;
	float					m_flLandAnimMultiplier;
	float					m_flWalkToRunTransition;
	bool					m_bLandedOnGroundThisFrame;
	bool					m_bLeftTheGroundThisFrame;
	float					m_flInAirSmoothValue;
	bool					m_bOnLadder;
	float					m_flLadderWeight;
	float					m_flLadderSpeed;
	bool					m_bWalkToRunTransitionState;
	bool					m_bDefuseStarted;
	bool					m_bPlantAnimStarted;
	bool					m_bTwitchAnimStarted;
	bool					m_bAdjustStarted;
	char					m_ActivityModifiers[ 20 ];
	float					m_flNextTwitchTime;
	float					m_flTimeOfLastKnownInjury;
	float					m_flLastVelocityTestTime;
	Vector					m_vecVelocityLast;
	Vector					m_vecTargetAcceleration;
	Vector					m_vecAcceleration;
	float					m_flAccelerationWeight;
	float					m_flAimMatrixTransition;
	float					m_flAimMatrixTransitionDelay;
	bool					m_bFlashed;
	float					m_flStrafeChangeWeight;
	float					m_flStrafeChangeTargetWeight;
	float					m_flStrafeChangeCycle;
	int						m_nStrafeSequence;
	bool					m_bStrafeChanging;
	float					m_flDurationStrafing;
	float					m_flFootLerp;
	bool					m_bFeetCrossed;
	bool					m_bPlayerIsAccelerating;
	AnimstatePose_t			m_tPoseParamMappings[ 20 ];
	float					m_flDurationMoveWeightIsTooHigh;
	float					m_flStaticApproachSpeed;
	int						m_nPreviousMoveState;
	float					m_flStutterStep;
	float					m_flActionWeightBiasRemainder;
	ProceduralFoot_t		m_FootLeft;
	ProceduralFoot_t		m_FootRight;
	float					m_flCameraSmoothHeight;
	bool					m_bSmoothHeightValid;
	float					m_flLastTimeVelocityOverTen;
	char					m_pad1[ 0x4 ];
	float					m_flAimYawMin;
	float					m_flAimYawMax;
	float					m_flAimPitchMin;
	float					m_flAimPitchMax;
	int						m_nAnimstateModelVersion;
};

class CAnimationLayer
{
public:
	void*	m_pThis;
	float	m_flAnimationTime;
	float	m_flFadeoutTime;
	int		m_nFlags;
	int		m_iActivity;
	int		m_nOrder;
	int		m_nSequence;
	float	m_flPrevCycle;
	float	m_flWeight;
	float	m_flWeightDeltaRate;
	float	m_flPlaybackRate;
	float	m_flCycle;
	void*	m_pOwner;
	int		m_nBitFlags;
};
#pragma endregion

#pragma region impl_interfaces
class IBaseClientDLL
{
public:
	CClientClass* GetAllClasses( );
};

class IClientModeShared
{
public:
	char		pad0[ 0x1B ];
	void*		m_pViewport;
	IHudChat*	m_pChatElement;
	HCursor		m_hCursorNone;
	void*		m_pWeaponSelection;
	int			m_nRootSize[ 2 ];
};

class IClientEntityListener
{
public:
	virtual void OnEntityCreated( CBaseEntity* pEntity ) { }
	virtual void OnEntityDeleted( CBaseEntity* pEntity ) { }
};

class IClientEntityList
{
public:
	virtual IClientNetworkable* GetClientNetworkable( int nIndex ) = 0;
	virtual IClientNetworkable* GetClientNetworkableFromHandle( CBaseHandle hNetworkable ) = 0;
	virtual IClientUnknown*		GetClientUnknownFromHandle( CBaseHandle hUnknown ) = 0;
	virtual IClientEntity*		GetClientEntity( int nIndex ) = 0;
	virtual IClientEntity*		GetClientEntityFromHandle( CBaseHandle hEntity ) = 0;
	virtual int					NumberOfEntities( bool bIncludeNonNetworkable ) = 0;
	virtual int					GetHighestEntityIndex( ) = 0;
	virtual void				SetMaxEntities( int iMax ) = 0;
	virtual int					GetMaxEntities( ) = 0;

	template <class T = IClientEntity>
	inline T* Get( const int nIndex )
	{
		return static_cast< T* >( GetClientEntity( nIndex ) );
	}

	template <class T = IClientEntity>
	inline T* Get( const CBaseHandle hEntity )
	{
		return static_cast< T* >( GetClientEntityFromHandle( hEntity ) );
	}

	void AddListenerEntity( IClientEntityListener* pListener )
	{
		m_vecEntityListeners.AddToTail( pListener );
	}

	void RemoveListenerEntity( IClientEntityListener* pListener )
	{
		m_vecEntityListeners.FindAndRemove( pListener );
	}

private:
	CUtlVector<IClientEntityListener*> m_vecEntityListeners;
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
	char				pad0[ 0xC ];
	bool				m_bTrackIRAvailable;
	bool				m_bMouseInitialized;
	bool				m_bMouseActive;
	char				pad1[ 0x9A ];
	bool				m_bCameraInThirdPerson;
	char				pad2[ 0x2 ];
	Vector				m_vecCameraOffset;
	char				pad3[ 0x38 ];
	CUserCmd*			m_pCommands;
	CVerifiedUserCmd*	m_pVerifiedCommands;

	CUserCmd*			GetUserCmd( int iSequenceNumber );
	CVerifiedUserCmd*	GetVerifiedUserCmd( int iSequenceNumber );
};

class IInputSystem
{
public:
	void		EnableInput( bool bEnable );
	bool		IsButtonDown( EButtonCode buttonCode );
	void		ResetInputState( );
	const char* ButtonCodeToString( EButtonCode buttonCode );
	EButtonCode VirtualKeyToButtonCode( int iVirtualKey );
	void		GetCursorPosition( int* pX, int* pY );
};

class IVEngineClient
{
public:
	void	GetScreenSize( int& iWidth, int& iHeight );
	bool	GetPlayerInfo( int iIndex, PlayerInfo_t* pInfo );
	bool	IsConsoleVisible( );
	int		GetLocalPlayer( );
	float	Time( );
	void	GetViewAngles( QAngle& angOutput );
	void	SetViewAngles( QAngle& angInput );
	int		GetMaxClients( );
	bool	IsInGame( );
	bool	IsConnected( );
	const	VMatrix& WorldToScreenMatrix( );
	void	ClientCmd_Unrestricted( const char* szCmdString );
};

class IClientState
{
public:
	char			pad0[ 0x9C ];
	INetChannel*	m_pNetChannel;
	int				m_iChallengeNr;
	char			pad1[ 0x64 ];
	int				m_iSignonState;
	char			pad2[ 0x8 ];
	float			m_flNextCmdTime;
	int				m_nServerCount;
	int				m_iCurrentSequence;
	char			pad3[ 0x4 ];
	int				m_iClockDriftMgr;
	char			pad4[ 0x44 ];
	int				m_iServerTick;
	int				m_iClientTick;
	int				m_iDeltaTick;
	bool			m_bPaused;
	char			pad5[ 0x7 ];
	int				m_iViewEntity;
	int				m_iPlayerSlot;
	char			m_szLevelName[ MAX_PATH ];
	char			m_szLevelNameShort[ 80 ];
	char			m_szMapGroupName[ 80 ];
	char			m_szLastLevelNameShort[ 80 ];
	char			pad6[ 0xC ];
	int				m_nMaxClients;
	char			pad7[ 0x498C ];
	float			m_flLastServerTickTime;
	bool			m_bInSimulation;
	char			pad8[ 0x3 ];
	int				m_iOldTickcount;
	float			m_flTickRemainder;
	float			m_flFrameTime;
	int				m_iLastOutgoingCommand;
	int				m_nChokedCommands;
	int				m_iLastCommandAck;
	int				m_iCommandAck;
	int				m_iSoundSequence;
	char			pad9[ 0x50 ];
	QAngle			m_angViewPoint;
	char			pad10[ 0xD0 ];
	CEventInfo*		m_pEvents;
};

class IPanel
{
public:
	const char* GetName( VPANEL vguiPanel );
};

class IAppSystem
{
private:
	virtual bool                            Connect( CreateInterfaceFn factory ) = 0;
	virtual void                            Disconnect( ) = 0;
	virtual void*							QueryInterface( const char* pInterfaceName ) = 0;
	virtual int /*InitReturnVal_t*/         Init( ) = 0;
	virtual void                            Shutdown( ) = 0;
	virtual const void* /*AppSystemInfo_t*/ GetDependencies( ) = 0;
	virtual int /*AppSystemTier_t*/         GetTier( ) = 0;
	virtual void                            Reconnect( CreateInterfaceFn factory, const char* pInterfaceName ) = 0;
	virtual void                            UnkFunc( ) = 0;
};

class ISurface : public IAppSystem
{
public:
	virtual void          RunFrame( ) = 0;
	virtual VPANEL		  GetEmbeddedPanel( ) = 0;
	virtual void          SetEmbeddedPanel( VPANEL pPanel ) = 0;
	virtual void          PushMakeCurrent( VPANEL panel, bool useInsets ) = 0;
	virtual void          PopMakeCurrent( VPANEL panel ) = 0;
	virtual void          DrawSetColor( int r, int g, int b, int a ) = 0;
	virtual void          DrawSetColor( Color col ) = 0;
	virtual void          DrawFilledRect( int x0, int y0, int x1, int y1 ) = 0;
	virtual void          DrawFilledRectArray( IntRect* pRects, int numRects ) = 0;
	virtual void          DrawOutlinedRect( int x0, int y0, int x1, int y1 ) = 0;
	virtual void          DrawLine( int x0, int y0, int x1, int y1 ) = 0;
	virtual void          DrawPolyLine( int* px, int* py, int numPoints ) = 0;
	virtual void          DrawSetApparentDepth( float f ) = 0;
	virtual void          DrawClearApparentDepth( void ) = 0;
	virtual void          DrawSetTextFont( HFont font ) = 0;
	virtual void          DrawSetTextColor( int r, int g, int b, int a ) = 0;
	virtual void          DrawSetTextColor( Color col ) = 0;
	virtual void          DrawSetTextPos( int x, int y ) = 0;
	virtual void          DrawGetTextPos( int& x, int& y ) = 0;
	virtual void          DrawPrintText( const wchar_t* text, int textLen, EFontDrawType drawType = EFontDrawType::FONT_DRAW_DEFAULT ) = 0;
	virtual void          DrawUnicodeChar( wchar_t wch, EFontDrawType drawType = EFontDrawType::FONT_DRAW_DEFAULT ) = 0;
	virtual void          DrawFlushText( ) = 0;
	virtual void*		  CreateHTMLWindow( void* events, VPANEL context ) = 0;
	virtual void          PaintHTMLWindow( void* htmlwin ) = 0;
	virtual void          DeleteHTMLWindow( void* htmlwin ) = 0;
	virtual int           DrawGetTextureId( char const* filename ) = 0;
	virtual bool          DrawGetTextureFile( int id, char* filename, int maxlen ) = 0;
	virtual void          DrawSetTextureFile( int id, const char* filename, int hardwareFilter, bool forceReload ) = 0;
	virtual void          DrawSetTextureRGBA( int id, const unsigned char* rgba, int wide, int tall ) = 0;
	virtual void          DrawSetTexture( int id ) = 0;
	virtual void          DeleteTextureByID( int id ) = 0;
	virtual void          DrawGetTextureSize( int id, int& wide, int& tall ) = 0;
	virtual void          DrawTexturedRect( int x0, int y0, int x1, int y1 ) = 0;
	virtual bool          IsTextureIDValid( int id ) = 0;
	virtual int           CreateNewTextureID( bool procedural = false ) = 0;
	virtual void          GetScreenSize( int& wide, int& tall ) = 0;
	virtual void          SetAsTopMost( VPANEL panel, bool state ) = 0;
	virtual void          BringToFront( VPANEL panel ) = 0;
	virtual void          SetForegroundWindow( VPANEL panel ) = 0;
	virtual void          SetPanelVisible( VPANEL panel, bool state ) = 0;
	virtual void          SetMinimized( VPANEL panel, bool state ) = 0;
	virtual bool          IsMinimized( VPANEL panel ) = 0;
	virtual void          FlashWindow( VPANEL panel, bool state ) = 0;
	virtual void          SetTitle( VPANEL panel, const wchar_t* title ) = 0;
	virtual void          SetAsToolBar( VPANEL panel, bool state ) = 0;
	virtual void          CreatePopup( VPANEL panel, bool minimised, bool showTaskbarIcon = true, bool disabled = false, bool mouseInput = true, bool kbInput = true ) = 0;
	virtual void          SwapBuffers( VPANEL panel ) = 0;
	virtual void          Invalidate( VPANEL panel ) = 0;
	virtual void          SetCursor( unsigned long cursor ) = 0;
	virtual bool          IsCursorVisible( ) = 0;
	virtual void          ApplyChanges( ) = 0;
	virtual bool          IsWithin( int x, int y ) = 0;
	virtual bool          HasFocus( ) = 0;
	virtual bool          SupportsFeature( int /*SurfaceFeature_t*/ feature ) = 0;
	virtual void          RestrictPaintToSinglePanel( VPANEL panel, bool bForceAllowNonModalSurface = false ) = 0;
	virtual void          SetModalPanel( VPANEL ) = 0;
	virtual VPANEL		  GetModalPanel( ) = 0;
	virtual void          UnlockCursor( ) = 0;
	virtual void          LockCursor( ) = 0;
	virtual void          SetTranslateExtendedKeys( bool state ) = 0;
	virtual VPANEL		  GetTopmostPopup( ) = 0;
	virtual void          SetTopLevelFocus( VPANEL panel ) = 0;
	virtual HFont		  CreateFont_( ) = 0;
	virtual bool          SetFontGlyphSet( HFont font, const char* windowsFontName, int tall, int weight, int blur, int scanlines, int flags, int nRangeMin = 0, int nRangeMax = 0 ) = 0;
	virtual bool          AddCustomFontFile( const char* fontFileName ) = 0;
	virtual int           GetFontTall( HFont font ) = 0;
	virtual int           GetFontAscent( HFont font, wchar_t wch ) = 0;
	virtual bool          IsFontAdditive( HFont font ) = 0;
	virtual void          GetCharABCwide( HFont font, int ch, int& a, int& b, int& c ) = 0;
	virtual int           GetCharacterWidth( HFont font, int ch ) = 0;
	virtual void          GetTextSize( HFont font, const wchar_t* text, int& wide, int& tall ) = 0;
	virtual VPANEL		  GetNotifyPanel( ) = 0;
	virtual void          SetNotifyIcon( VPANEL context, unsigned long icon, VPANEL panelToReceiveMessages, const char* text ) = 0;
	virtual void          PlaySound_( const char* fileName ) = 0;
	virtual int           GetPopupCount( ) = 0;
	virtual VPANEL		  GetPopup( int index ) = 0;
	virtual bool          ShouldPaintChildPanel( VPANEL childPanel ) = 0;
	virtual bool          RecreateContext( VPANEL panel ) = 0;
	virtual void          AddPanel( VPANEL panel ) = 0;
	virtual void          ReleasePanel( VPANEL panel ) = 0;
	virtual void          MovePopupToFront( VPANEL panel ) = 0;
	virtual void          MovePopupToBack( VPANEL panel ) = 0;
	virtual void          SolveTraverse( VPANEL panel, bool forceApplySchemeSettings = false ) = 0;
	virtual void          PaintTraverse( VPANEL panel ) = 0;
	virtual void          EnableMouseCapture( VPANEL panel, bool state ) = 0;
	virtual void          GetWorkspaceBounds( int& x, int& y, int& wide, int& tall ) = 0;
	virtual void          GetAbsoluteWindowBounds( int& x, int& y, int& wide, int& tall ) = 0;
	virtual void          GetProportionalBase( int& width, int& height ) = 0;
	virtual void          CalculateMouseVisible( ) = 0;
	virtual bool          NeedKBInput( ) = 0;
	virtual bool          HasCursorPosFunctions( ) = 0;
	virtual void          SurfaceGetCursorPos( int& x, int& y ) = 0;
	virtual void          SurfaceSetCursorPos( int x, int y ) = 0;
	virtual void          DrawTexturedLine( const Vertex_t& a, const Vertex_t& b ) = 0;
	virtual void          DrawOutlinedCircle( int x, int y, int radius, int segments ) = 0;
	virtual void          DrawTexturedPolyLine( const Vertex_t* p, int n ) = 0;
	virtual void          DrawTexturedSubRect( int x0, int y0, int x1, int y1, float texs0, float text0, float texs1, float text1 ) = 0;
	virtual void          DrawTexturedPolygon( int n, Vertex_t* pVertice, bool bClipVertices = true ) = 0;
};

class IConVar : public IAppSystem
{
public:
	virtual CVarDLLIdentifier_t	AllocateDLLIdentifier( ) = 0;
	virtual void				RegisterConCommand( CConVar* pCommandBase, int iDefaultValue = 1 ) = 0;
	virtual void				UnregisterConCommand( CConVar* pCommandBase ) = 0;
	virtual void				UnregisterConCommands( CVarDLLIdentifier_t id ) = 0;
	virtual const char*			GetCommandLineValue( const char* szVariableName ) = 0;
	virtual CConBase*			FindCommandBase( const char* szName ) = 0;
	virtual const CConBase*		FindCommandBase( const char* szName ) const = 0;
	virtual CConVar*			FindVar( const char* szVariableName ) = 0;
	virtual const CConVar*		FindVar( const char* szVariableName ) const = 0;
	virtual CConCmd*			FindCommand( const char* szName ) = 0;
	virtual const CConCmd*		FindCommand( const char* szName ) const = 0;
	virtual void				InstallGlobalChangeCallback( ChangeCallback callback ) = 0;
	virtual void				RemoveGlobalChangeCallback( ChangeCallback callback ) = 0;
	virtual void				CallGlobalChangeCallbacks( CConVar* pVar, const char* szOldString, float flOldValue ) = 0;
	virtual void				InstallConsoleDisplayFunc( void* pDisplayFunc ) = 0;
	virtual void				RemoveConsoleDisplayFunc( void* pDisplayFunc ) = 0;
	virtual void				ConsoleColorPrintf( const Color& color, const char* pFormat, ... ) const = 0;
	virtual void				ConsolePrintf( const char* pFormat, ... ) const = 0;
	virtual void				ConsoleDPrintf( const char* pFormat, ... ) const = 0;
	virtual void				RevertFlaggedConVars( int nFlag ) = 0;
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