#include "Header.h"

void Patch_CryAISystemSliceLoadCrash(int address, int size) {
	DWORD *pDword0 = (DWORD*)address;
	DWORD old0;
	VirtualProtect((LPVOID)pDword0, size, PAGE_READWRITE, &old0);
	memset((void*)pDword0, 0x90, size);
	VirtualProtect((LPVOID)pDword0, size, old0, &old0);
}

void Patch_CryAISystem_Int_Vtable_Call(int address, int offset){
	int *pInt = (int*)(address+0x02);
	DWORD old;
	VirtualProtect((LPVOID)pInt, 4, PAGE_READWRITE, &old);
	*pInt = offset;
	VirtualProtect((LPVOID)pInt, 4, old, &old);
}

void Patch_CryAISystem_Char_Vtable_Call(int address, char offset){
	char *pChar = (char*)(address+0x02);
	DWORD old;
	VirtualProtect((LPVOID)pChar, 1, PAGE_READWRITE, &old);
	*pChar = offset;
	VirtualProtect((LPVOID)pChar, 1, old, &old);
}

typedef bool (__thiscall* PtrFunc_CSystem_IntializeEngineModule)(void *this1, const char *dllName, const char *moduleClassName, const DWORD &initParams, bool bQuitIfNotFound);
PtrFunc_CSystem_IntializeEngineModule pfnCSystem_IntializeEngineModule = (PtrFunc_CSystem_IntializeEngineModule)_Game_CSystem_IntializeEngineModule_Address;

bool __fastcall Hook_CSystem_IntializeEngineModule(void *this1, void *None, const char *dllName, const char *moduleClassName, const DWORD &initParams, bool bQuitIfNotFound)
{
	//printf("[IgPatchServer.dll][Hook_CSystem_IntializeEngineModule]: Called %s\n", dllName);
	
	if(_Game_ForceCryAISystemInitialization_Ñondition == true && strcmp(dllName, "CryAnimation") == 0){
		pfnCSystem_IntializeEngineModule(this1, "CryAISystem", "EngineModule_CryAISystem", initParams, bQuitIfNotFound);
	}

	bool result = pfnCSystem_IntializeEngineModule(this1, dllName, moduleClassName, initParams, bQuitIfNotFound);

	gEnv_2011->p3DEngine = gEnv()->p3DEngine();
	gEnv_2011->pScriptSystem = gEnv()->pScriptSystem();
	gEnv_2011->pPhysicalWorld = gEnv()->pPhysicalWorld();
	gEnv_2011->pCryPak = gEnv()->pCryPak();
	gEnv_2011->pTimer = gEnv()->pTimer();
	gEnv_2011->pEntitySystem = gEnv()->pEntitySystem();
	gEnv_2011->pConsole = gEnv()->pConsole();
	gEnv_2011->pSystem = gEnv()->pSystem();
	gEnv_2011->pLog = gEnv()->pLog();
	gEnv_2011->pAISystem = gEnv()->pAISystem();
	
	return result;
}

typedef bool (__cdecl* PtrFunc_CryCreateClassInstance)(const char* cname, DWORD *a2);
PtrFunc_CryCreateClassInstance pfnCryCreateClassInstance = (PtrFunc_CryCreateClassInstance)_Game_CryCreateClassInstance_Address;

bool __cdecl Hook_CryCreateClassInstance(const char* cname, DWORD *a2)
{	
	//printf("[IgPatchServer.dll][Hook_CryCreateClassInstance]: Ñalled %s\n", cname);

	if(strcmp(cname, "EngineModule_CryAISystem") == 0)
	{
		HMODULE handle = LoadLibraryA("CryAISystem.dll");
		
		Patch_CryAISystem_Int_Vtable_Call(0x31080EC4, _Game_IScriptSystem_BeginPreCachedBuffer_Vtable_Offset);
		Patch_CryAISystem_Int_Vtable_Call(0x310878DF, _Game_IScriptSystem_PreCacheBuffer_Vtable_Offset);
		Patch_CryAISystem_Int_Vtable_Call(0x310811A7, _Game_IScriptSystem_PreCacheBuffer_Vtable_Offset);
		Patch_CryAISystem_Int_Vtable_Call(0x31082404, _Game_IScriptSystem_PreCacheBuffer_Vtable_Offset);
		Patch_CryAISystem_Int_Vtable_Call(0x3108A4CD, _Game_IScriptSystem_PreCacheBuffer_Vtable_Offset);
		Patch_CryAISystem_Int_Vtable_Call(0x310F40EB, _Game_IScriptSystem_CompileBuffer_Vtable_Offset);
		Patch_CryAISystem_Char_Vtable_Call(0x3123C814, _Game_IEntitySystem_AddSink_Vtable_Offset);
		Patch_CryAISystem_Char_Vtable_Call(0x3116662E, _Game_IEntitySystem_AddSink_Vtable_Offset);
		Patch_CryAISystem_Char_Vtable_Call(0x311F34DE, _Game_IEntitySystem_AddSink_Vtable_Offset);
		Patch_CryAISystem_Char_Vtable_Call(0x311F33AE, _Game_IEntitySystem_RemoveSink_Vtable_Offset);
		Patch_CryAISystem_Char_Vtable_Call(0x3123DE60, _Game_IEntitySystem_RemoveSink_Vtable_Offset);
		Patch_CryAISystem_Int_Vtable_Call(0x31166642, _Game_IEntitySystem_GetIEntityPoolManager_Vtable_Offset);
		Patch_CryAISystem_Int_Vtable_Call(0x3100456D, _Game_IEntitySystem_GetIEntityPoolManager_Vtable_Offset);
		Patch_CryAISystem_Char_Vtable_Call(0x31235891, _Game_IEntitySystem_GetEntityIterator_Vtable_Offset);
		Patch_CryAISystem_Char_Vtable_Call(0x31238D18, _Game_IEntitySystem_GetEntityIterator_Vtable_Offset);		
		Patch_CryAISystem_Char_Vtable_Call(0x31150B5D, _Game_IEntitySystem_GetEntityFromPhysics_Vtable_Offset);
		Patch_CryAISystem_Int_Vtable_Call(0x310D3426, _Game_ICryPak_FindFirst_Vtable_Offset);
		Patch_CryAISystem_Int_Vtable_Call(0x3108D9B5, _Game_ICryPak_FindFirst_Vtable_Offset);
		Patch_CryAISystem_Int_Vtable_Call(0x3108E6F2, _Game_ICryPak_FindFirst_Vtable_Offset);
		Patch_CryAISystem_Int_Vtable_Call(0x311F4E42, _Game_ICryPak_FindFirst_Vtable_Offset);
		Patch_CryAISystem_Int_Vtable_Call(0x310A8339, _Game_ICryPak_FindFirst_Vtable_Offset);
		Patch_CryAISystem_Int_Vtable_Call(0x31224FF9, _Game_ICryPak_FindFirst_Vtable_Offset);
		Patch_CryAISystem_Int_Vtable_Call(0x3109FA59, _Game_ICryPak_FindFirst_Vtable_Offset);
		Patch_CryAISystem_Int_Vtable_Call(0x3107E24E, _Game_ICryPak_FindFirst_Vtable_Offset);
		Patch_CryAISystem_Int_Vtable_Call(0x3123BDE9, _Game_ICryPak_FindFirst_Vtable_Offset);
		Patch_CryAISystem_Int_Vtable_Call(0x310D3470, _Game_ICryPak_FindNext_Vtable_Offset);
		Patch_CryAISystem_Int_Vtable_Call(0x3108DD23, _Game_ICryPak_FindNext_Vtable_Offset);
		Patch_CryAISystem_Int_Vtable_Call(0x3108E867, _Game_ICryPak_FindNext_Vtable_Offset);
		Patch_CryAISystem_Int_Vtable_Call(0x311F5274, _Game_ICryPak_FindNext_Vtable_Offset);
		Patch_CryAISystem_Int_Vtable_Call(0x310A8473, _Game_ICryPak_FindNext_Vtable_Offset);
		Patch_CryAISystem_Int_Vtable_Call(0x31225134, _Game_ICryPak_FindNext_Vtable_Offset);
		Patch_CryAISystem_Int_Vtable_Call(0x3109FB93, _Game_ICryPak_FindNext_Vtable_Offset);
		Patch_CryAISystem_Int_Vtable_Call(0x3107E451, _Game_ICryPak_FindNext_Vtable_Offset);
		Patch_CryAISystem_Int_Vtable_Call(0x3123C4E4, _Game_ICryPak_FindNext_Vtable_Offset);
		Patch_CryAISystem_Int_Vtable_Call(0x310D3488, _Game_ICryPak_FindClose_Vtable_Offset);
		Patch_CryAISystem_Int_Vtable_Call(0x3108DDC1, _Game_ICryPak_FindClose_Vtable_Offset);
		Patch_CryAISystem_Int_Vtable_Call(0x3108E8C8, _Game_ICryPak_FindClose_Vtable_Offset);
		Patch_CryAISystem_Int_Vtable_Call(0x311F5297, _Game_ICryPak_FindClose_Vtable_Offset);
		Patch_CryAISystem_Int_Vtable_Call(0x310A848F, _Game_ICryPak_FindClose_Vtable_Offset);
		Patch_CryAISystem_Int_Vtable_Call(0x31225150, _Game_ICryPak_FindClose_Vtable_Offset);
		Patch_CryAISystem_Int_Vtable_Call(0x3109FBAF, _Game_ICryPak_FindClose_Vtable_Offset);
		Patch_CryAISystem_Int_Vtable_Call(0x3107E474, _Game_ICryPak_FindClose_Vtable_Offset);
		Patch_CryAISystem_Int_Vtable_Call(0x3123C507, _Game_ICryPak_FindClose_Vtable_Offset);
		Patch_CryAISystem_Int_Vtable_Call(0x31216B1E, _Game_ICryPak_FClose_Vtable_Offset);
		Patch_CryAISystem_Int_Vtable_Call(0x311CF473, _Game_ICryPak_FClose_Vtable_Offset);
		Patch_CryAISystem_Int_Vtable_Call(0x3125F2CA, _Game_ICryPak_FClose_Vtable_Offset);
		Patch_CryAISystem_Int_Vtable_Call(0x311959D8, _Game_ICryPak_FClose_Vtable_Offset);
		Patch_CryAISystem_Int_Vtable_Call(0x3117A44D, _Game_ICryPak_FClose_Vtable_Offset);
		Patch_CryAISystem_Int_Vtable_Call(0x3118C17B, _Game_ICryPak_FClose_Vtable_Offset);
		Patch_CryAISystem_Int_Vtable_Call(0x3118305F, _Game_ICryPak_FClose_Vtable_Offset);
		Patch_CryAISystem_Int_Vtable_Call(0x3116CD75, _Game_ICryPak_FClose_Vtable_Offset);
		Patch_CryAISystem_Char_Vtable_Call(0x31001061, _Game_ITimeOfDay_GetTime_Vtable_Offset);
		Patch_CryAISystem_Char_Vtable_Call(0x3116948B, _Game_SSystemGlobalEnvironment_pSystem_Offset_Offset);
		Patch_CryAISystem_Char_Vtable_Call(0x3116952D, _Game_SSystemGlobalEnvironment_pAISystem_Offset_Offset);
		Patch_CryAISystemSliceLoadCrash(0x3123DA01, 27);
		Patch_CryAISystemSliceLoadCrash(0x31179BB8, 28);
		Patch_CryAISystemSliceLoadCrash(0x31179988, 27);
		Patch_CryAISystemSliceLoadCrash(0x3117A0D7, 27);
		Patch_CryAISystemSliceLoadCrash(0x3125F223, 27);
		Patch_CryAISystemSliceLoadCrash(0x3125B7F6, 27);
		Patch_CryAISystemSliceLoadCrash(0x3125B5BD, 28);

		typedef void  *(*PtrFunc_ModuleInitISystem)(DWORD *pSystem, const char *moduleName);
		PtrFunc_ModuleInitISystem pfnModuleInitISystem = (PtrFunc_ModuleInitISystem) GetProcAddress(handle, "ModuleInitISystem");
		
		if (pfnModuleInitISystem)
		{	
			pfnModuleInitISystem((DWORD *)gEnv()->pSystem(), "CryAISystem");

			int *p0 = (int*)(0x312FAF2C);
			*p0 = (int)gEnv_2011;
		}
	}

	return pfnCryCreateClassInstance(cname, a2);
}

typedef bool(__thiscall* CBinaryXmlNode_getAttrClass)(IXmlNode *this1, const char *key, XmlString &value);
CBinaryXmlNode_getAttrClass CBinaryXmlNode_getAttr = (CBinaryXmlNode_getAttrClass)_Game_CBinaryXmlNode_getAttr_Address;

bool __fastcall CBinaryXmlNode_getAttrHook(IXmlNode *this1, void *None, const char *key, XmlString &value) 
{
	//printf("[IgPatchServer.dll][CBinaryXmlNode_getAttrHook]: Ñalled %s\n", key);
	const char*	v(NULL);
	bool  boHasAttribute(this1->getAttr(key,&v));
	value=v;
	return boHasAttribute;
}

typedef ISystem *(__cdecl* PtrFunc_CreateSystemInterface)(const SSystemInitParams *startupParams);
PtrFunc_CreateSystemInterface pfnCreateSystemInterface = (PtrFunc_CreateSystemInterface)_Game_CreateSystemInterface_Address;

ISystem * __cdecl Hook_CreateSystemInterface(const SSystemInitParams *startupParams)
{
	//printf("[IgPatchServer.dll][Hook_CreateSystemInterface]: Ñalled\n");

	ISystem *pSystem = pfnCreateSystemInterface(startupParams);

	MH_DisableHook((void *)_Game_CryCreateClassInstance_Address);
	MH_DisableHook((void *)_Game_CSystem_IntializeEngineModule_Address);
	MH_DisableHook((void *)_Game_CBinaryXmlNode_getAttr_Address);
	MH_DisableHook((void *)_Game_CreateSystemInterface_Address);

	return pSystem;
}

void PatchAi_PreInit()
{
	gEnv_2011 = new SSystemGlobalEnvironment_2011;

	memset(gEnv_2011, 0x00, sizeof(SSystemGlobalEnvironment_2011));

	gEnv_2011->bServer = true;
	gEnv_2011->bMultiplayer = true;
	gEnv_2011->bDedicated = true;

	MH_CreateHook((void *)_Game_CryCreateClassInstance_Address, Hook_CryCreateClassInstance, (LPVOID *)&pfnCryCreateClassInstance);
	MH_EnableHook((void *)_Game_CryCreateClassInstance_Address);
	
	MH_CreateHook((void *)_Game_CSystem_IntializeEngineModule_Address, Hook_CSystem_IntializeEngineModule, (LPVOID *)&pfnCSystem_IntializeEngineModule);
	MH_EnableHook((void *)_Game_CSystem_IntializeEngineModule_Address);
	
	MH_CreateHook((void *)_Game_CBinaryXmlNode_getAttr_Address, CBinaryXmlNode_getAttrHook, (LPVOID *)&CBinaryXmlNode_getAttr);
	MH_EnableHook((void *)_Game_CBinaryXmlNode_getAttr_Address);

	MH_CreateHook((void *)_Game_CreateSystemInterface_Address, Hook_CreateSystemInterface, (LPVOID *)&pfnCreateSystemInterface);
	MH_EnableHook((void *)_Game_CreateSystemInterface_Address);	
}

void PatchAi_PostInit()
{
	gEnv_2011->pGame = gEnv()->pGame();
}