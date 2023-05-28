#include "../Hooks.hpp"
#include "../../../Features/Misc/EnginePrediction.hpp"

void FASTCALL CHooked::RunCommand( void* pEcx, void* pEdx, CBasePlayer* pPlayer, CUserCmd* pCmd, IMoveHelper* pMoveHelper )
{
	static auto oRunCommand = DTR::RunCommand.GetOriginal<decltype( &RunCommand )>( );
	oRunCommand( pEcx, pEdx, pPlayer, pCmd, pMoveHelper );
}