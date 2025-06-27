#include "Header.h"

bool IXmlNode::getAttr(const char *key, const char **value)
{
	typedef bool(__thiscall* IXmlNodegetAttrClass)(PVOID, const char *, const char **);
	return vFun_Call<IXmlNodegetAttrClass>(this, _Game_IXmlNode_getAttr_Vtable_Offset)(this, key, value);
}

const char* IConsoleCmdArgs::GetArg( int nIndex )
{
	typedef const char*(__thiscall* IConsoleCmdArgsGetArgClass)(PVOID, int);
	return vFun_Call<IConsoleCmdArgsGetArgClass>(this, _Game_IConsoleCmdArgs_GetArg_Vtable_Offset)(this, nIndex);
}

void IConsole::AddCommand( const char *sCommand, ConsoleCommandFunc func, int nFlags, const char *sHelp )
{
	typedef void(__thiscall* IConsoleAddCommandClass)(PVOID, const char *, ConsoleCommandFunc, int, const char *);
	return vFun_Call<IConsoleAddCommandClass>(this, _Game_IConsole_AddCommand_Vtable_Offset)(this, sCommand, func, nFlags, sHelp);
}

int INetChannel::GetProfileId()
{
	typedef int(__thiscall* INetChannelGetProfileIdClass)(PVOID);
	return vFun_Call<INetChannelGetProfileIdClass>(this, _Game_INetChannel_GetProfileId_Vtable_Offset)(this);
}

void INetChannel::Disconnect( int cause, const char * fmt)
{
	typedef void(__cdecl* INetChannelDisconnectClass)(PVOID, int, const char *);
	return vFun_Call<INetChannelDisconnectClass>(this, _Game_INetChannel_Disconnect_Vtable_Offset)(this, cause, fmt);
}

unsigned __int16 IActor::GetChannelId()
{
	return (*(unsigned __int16 (__thiscall **)(DWORD))(**(DWORD **)(this + _Game_IActor_GetChannelId0_Vtable_Offset) + _Game_IActor_GetChannelId1_Vtable_Offset))(*(DWORD *)(this + _Game_IActor_GetChannelId0_Vtable_Offset));
}

IActor* IActorIterator::Next()
{
	typedef IActor*(__thiscall* IActorIteratorNextClass)(PVOID);
	return vFun_Call<IActorIteratorNextClass>(this, _Game_IActorIterator_Next_Vtable_Offset)(this);
}

void IActorIterator::Release()
{
	typedef void(__thiscall* IActorIteratorReleaseClass)(PVOID);
	return vFun_Call<IActorIteratorReleaseClass>(this, _Game_IActorIterator_Release_Vtable_Offset)(this);
}

void IActorSystem::CreateActorIterator(IActorIterator **pOutIter)
{
	typedef void(__thiscall* IActorSystemCreateActorIteratorClass)(PVOID, IActorIterator **);
	return vFun_Call<IActorSystemCreateActorIteratorClass>(this, _Game_IActorSystem_CreateActorIterator_Vtable_Offset)(this, pOutIter);
}

IActorSystem *IGameFramework::GetIActorSystem()
{
	typedef IActorSystem *(__thiscall* IGameFrameworkGetIActorSystemClass)(PVOID);
	return vFun_Call<IGameFrameworkGetIActorSystemClass>(this, _Game_IGameFramework_GetIActorSystem_Vtable_Offset)(this);
}

INetChannel *IGameFramework::GetNetChannel(unsigned __int16 channelId)
{
	typedef INetChannel *(__thiscall* IGameFrameworkGetNetChannelClass)(PVOID, unsigned __int16);
	return vFun_Call<IGameFrameworkGetNetChannelClass>(this, _Game_IGameFramework_GetNetChannel_Vtable_Offset)(this, channelId);
}

IGameFramework * IGame::GetIGameFramework()
{
	typedef IGameFramework *(__thiscall* IGameGetIGameFrameworkClass)(PVOID);
	return vFun_Call<IGameGetIGameFrameworkClass>(this, _Game_IGame_GetIGameFramework_Vtable_Offset)(this);
}

I3DEngine *SSystemGlobalEnvironment::p3DEngine()
{
	return (I3DEngine *) *(DWORD *)(this + _Game_SSystemGlobalEnvironment_p3DEngine_Offset_Offset);
}
IScriptSystem *SSystemGlobalEnvironment::pScriptSystem()
{
	return (IScriptSystem *) *(DWORD *)(this + _Game_SSystemGlobalEnvironment_pScriptSystem_Offset_Offset);
}
IPhysicalWorld *SSystemGlobalEnvironment::pPhysicalWorld()
{
	return (IPhysicalWorld *) *(DWORD *)(this + _Game_SSystemGlobalEnvironment_pPhysicalWorld_Offset_Offset);
}
ICryPak *SSystemGlobalEnvironment::pCryPak()
{
	return (ICryPak *) *(DWORD *)(this + _Game_SSystemGlobalEnvironment_pCryPak_Offset_Offset);
}
ITimer *SSystemGlobalEnvironment::pTimer()
{
	return (ITimer *) *(DWORD *)(this + _Game_SSystemGlobalEnvironment_pTimer_Offset_Offset);
}
IGame *SSystemGlobalEnvironment::pGame()
{
	return (IGame *) *(DWORD *)(this + _Game_SSystemGlobalEnvironment_pGame_Offset_Offset);
}
IEntitySystem *SSystemGlobalEnvironment::pEntitySystem()
{
	return (IEntitySystem *) *(DWORD *)(this + _Game_SSystemGlobalEnvironment_pEntitySystem_Offset_Offset);
}
IConsole *SSystemGlobalEnvironment::pConsole()
{
	return (IConsole *) *(DWORD *)(this + _Game_SSystemGlobalEnvironment_pConsole_Offset_Offset);
}
ISystem *SSystemGlobalEnvironment::pSystem()
{
	return (ISystem *) *(DWORD *)(this + _Game_SSystemGlobalEnvironment_pSystem_Offset_Offset);
}
ILog *SSystemGlobalEnvironment::pLog()
{
	return (ILog *) *(DWORD *)(this + _Game_SSystemGlobalEnvironment_pLog_Offset_Offset);
}
IAISystem *SSystemGlobalEnvironment::pAISystem()
{
	return (IAISystem *) *(DWORD *)(this + _Game_SSystemGlobalEnvironment_pAISystem_Offset_Offset);
}
SSystemGlobalEnvironment *gEnv()
{
	return (SSystemGlobalEnvironment *) *(DWORD *)_Game_gEnv;
}

SSystemGlobalEnvironment_2011 *gEnv_2011 = 0;