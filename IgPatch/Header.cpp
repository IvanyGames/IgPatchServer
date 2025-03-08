#include "Header.h"

bool IXmlNode::getAttr(const char *key, const char **value)
{
	typedef bool(__thiscall* IXmlNodegetAttrClass)(PVOID, const char *, const char **);
	return vFun_Call<IXmlNodegetAttrClass>(this, _Game_IXmlNode_getAttr_Vtable_Offset)(this, key, value);
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