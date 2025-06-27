#include "Header.h"

void CmdKickPid(IConsoleCmdArgs* pCmdArgs)
{
	int profile_id = atoi(pCmdArgs->GetArg(1));
	int cause = atoi(pCmdArgs->GetArg(2));

	SSystemGlobalEnvironment *pSSystemGlobalEnvironment = gEnv();
	IGame *pGame = pSSystemGlobalEnvironment->pGame();
	IGameFramework *pGameFramework = pGame->GetIGameFramework();
	IActorIterator *pActorIterator = NULL;
	
	pGameFramework->GetIActorSystem()->CreateActorIterator(&pActorIterator);
	while (IActor* pIActor = pActorIterator->Next())
	{
		if (INetChannel *pINetChannel = pGameFramework->GetNetChannel(pIActor->GetChannelId())) {
			if (profile_id == pINetChannel->GetProfileId()) {
				pINetChannel->Disconnect(cause, "Player is kicked by request");
				break;
			}
		}
	}

	if(pActorIterator != NULL){
		pActorIterator->Release();
	}
}

void PatchKick_PostInit()
{
	SSystemGlobalEnvironment *pSSystemGlobalEnvironment = gEnv();
	IConsole *pConsole = pSSystemGlobalEnvironment->pConsole();
	pConsole->AddCommand("kickpid", CmdKickPid);
}