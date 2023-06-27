#pragma once

#include "../SourceSDK/SDK.hpp"

class CSource
{
public:
	bool Create( );
	void Destroy( );

	struct Patterns_t
	{
		std::uintptr_t m_uAnimationOverlays = 0u;
		std::uintptr_t m_uPredictionRandomSeed = 0u;
		std::uintptr_t m_uPredictionPlayer = 0u;
		std::uintptr_t m_uMoveHelper = 0u;
		std::uintptr_t m_uInput = 0u;
		std::uintptr_t m_uIsDepthOfFieldEnabled = 0u;
		std::uintptr_t m_uClientState = 0u;
		std::uintptr_t m_uDirectDevice = 0u;
	} Patterns;

	struct Function_t
	{
		std::uintptr_t m_uRandomSeed = 0u;
		std::uintptr_t m_uRandomFloat = 0u;
		std::uintptr_t m_uRandomInt = 0u;
	} Functions;

	struct Interfaces_t
	{
		IBaseClientDLL* m_pClient = nullptr;
		IClientModeShared* m_pClientMode = nullptr;
		IVEngineClient* m_pEngine = nullptr;
		IClientEntityList* m_pEntList = nullptr;
		IGameMovement* m_pGameMovement = nullptr;
		IPrediction* m_pPrediction = nullptr;
		IInputSystem* m_pInputSystem = nullptr;
		IMoveHelper* m_pMoveHelper = nullptr;
		IInput* m_pInput = nullptr;
		IClientState* m_pClientState = nullptr;
		IConVar* m_pConVar = nullptr;
		ISurface* m_pSurface = nullptr;
		IPanel* m_pPanel = nullptr;
		IMaterialSystem* m_pMaterialSystem = nullptr;
		IDirect3DDevice9* m_pDirectDevice = nullptr;
		CGlobalVars* m_pGlobalVars = nullptr;
	} Interfaces;

private:
	bool SetupPatterns( );
	bool SetupFunction( );
	bool SetupInterfaces( );

	void* CreateInterface( const std::string& strImageName, const std::string& strName, bool bForce = false );
};

inline const std::unique_ptr< CSource > Source{ new CSource( ) };