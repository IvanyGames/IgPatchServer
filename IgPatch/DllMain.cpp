#include "Header.h"

typedef void (__thiscall* PtrFunc_Unknown0)(void *this1);
PtrFunc_Unknown0 pfnUnknown0 = (PtrFunc_Unknown0)_Game_Unknown0_Address;

void __fastcall Hook_Unknown0(void *this1, void *None)
{
	//printf("[IgPatchServer.dll][Hook_Unknown0]: Ñalled\n");
}

#include <intrin.h>
#pragma intrinsic(_ReturnAddress)

struct CGameObject;

typedef void (__thiscall* PtrFunc_CGameObject_DoInvokeRMI)(CGameObject *this1, void *pBody, unsigned int where0, int channel);
PtrFunc_CGameObject_DoInvokeRMI pfnCGameObject_DoInvokeRMI = (PtrFunc_CGameObject_DoInvokeRMI)0x07A1110;

void __fastcall Hook_CGameObject_DoInvokeRMI(CGameObject *this1, void *None, void *pBody, unsigned int where0, int channel)
{
	DWORD returnAddress = (DWORD)_ReturnAddress();
	printf("[IgPatchServer.dll][Hook_CGameObject_DoInvokeRMI]: Called where:%x ret:%x\n", where0, returnAddress);
	pfnCGameObject_DoInvokeRMI(this1, pBody, where0, channel);
}

struct CEntitySystem;

typedef int (__thiscall* PtrFunc_CEntitySystem_GetEntity)(CEntitySystem *this1, unsigned int id);
PtrFunc_CEntitySystem_GetEntity pfnCEntitySystem_GetEntity = (PtrFunc_CEntitySystem_GetEntity)0x04FEE10;

int __fastcall Hook_CEntitySystem_GetEntity(CEntitySystem *this1, void *None, unsigned int id)
{
	DWORD returnAddress = (DWORD)_ReturnAddress();
	//printf("[IgPatchServer.dll][Hook_CEntitySystem_GetEntity]: Called id:%u ret:%x\n", id, returnAddress);
	return pfnCEntitySystem_GetEntity(this1, id);
}

struct CPlayer;

typedef unsigned int (__thiscall* PtrFunc_CPlayer_GetPlatformId)(CPlayer *this1);
PtrFunc_CPlayer_GetPlatformId pfnCPlayer_GetPlatformId = (PtrFunc_CPlayer_GetPlatformId)0x0DAEBB0;

unsigned int __fastcall Hook_CPlayer_GetPlatformId(CPlayer *this1, void *None)
{
	DWORD returnAddress = (DWORD)_ReturnAddress();
	unsigned int res0 = pfnCPlayer_GetPlatformId(this1);
	printf("[IgPatchServer.dll][Hook_CPlayer_GetPlatformId]: Called res:%u ret:%x\n", res0, returnAddress);
	return res0;
}

void DllMain_On_Game_PreInit()
{
	PatchAi_PreInit();
	PatchOther_PreInit();
}

void DllMain_On_Game_PostInit()
{
	if(_Game_Unknown0_Address != -1){
		MH_CreateHook((void*)_Game_Unknown0_Address, Hook_Unknown0, (LPVOID*)&pfnUnknown0);
		MH_EnableHook((void*)_Game_Unknown0_Address);
	}
	
	PatchAi_PostInit();
	PatchDamage_PostInit();
	PatchKick_PostInit();
	
	/*
	MH_CreateHook((void*)0x07A1110, Hook_CGameObject_DoInvokeRMI, (LPVOID*)&pfnCGameObject_DoInvokeRMI);
	MH_EnableHook((void*)0x07A1110);

	MH_CreateHook((void*)0x04FEE10, Hook_CEntitySystem_GetEntity, (LPVOID*)&pfnCEntitySystem_GetEntity);
	MH_EnableHook((void*)0x04FEE10);

	MH_CreateHook((void*)0x0DAEBB0, Hook_CPlayer_GetPlatformId, (LPVOID*)&pfnCPlayer_GetPlatformId);
	MH_EnableHook((void*)0x0DAEBB0);
	*/
}

FARPROC DllMain_fp_User32_SystemParametersInfoA;

typedef BOOL (__stdcall* DllMain_PtrFunc_SystemParametersInfoA)(UINT uiAction, UINT uiParam, PVOID pvParam, UINT fWinIni);
DllMain_PtrFunc_SystemParametersInfoA DllMain_pfnSystemParametersInfoA;

BOOL __stdcall DllMain_Hook_SystemParametersInfoA(UINT uiAction, UINT uiParam, PVOID pvParam, UINT fWinIni)
{
	//printf("[IgPatchServer.dll][DllMain_Hook_SystemParametersInfoA]: Ñalled %u %u\n", uiAction, uiParam);

	if(uiAction == 0x3Au && uiParam == 8u)
	{
		MH_DisableHook((void*)DllMain_fp_User32_SystemParametersInfoA);
		DllMain_On_Game_PostInit();
	}

	return DllMain_pfnSystemParametersInfoA(uiAction, uiParam, pvParam, fWinIni);
}

void DllMain_Init_SystemParametersInfoA_Hook()
{
	HMODULE hm_User32 = GetModuleHandleA("User32.dll");
	
	if(hm_User32 == 0)
	{
		printf("[IgPatchServer.dll][DllMain_Init_SystemParametersInfoA_Hook]: failed to 'GetModuleHandleA' of 'User32.dll'\n");
		Sleep(1000);
		return;
	}

	DllMain_fp_User32_SystemParametersInfoA = GetProcAddress(hm_User32, "SystemParametersInfoA");

	if(DllMain_fp_User32_SystemParametersInfoA == 0)
	{
		printf("[IgPatchServer.dll][DllMain_Init_SystemParametersInfoA_Hook]: failed to 'GetProcAddress' of 'SystemParametersInfoA'\n");
		Sleep(1000);
		return;
	}
	
	if(MH_CreateHook((void *)DllMain_fp_User32_SystemParametersInfoA, DllMain_Hook_SystemParametersInfoA, (LPVOID *)&DllMain_pfnSystemParametersInfoA) != 0)
	{
		printf("[IgPatchServer.dll][DllMain_Init_SystemParametersInfoA_Hook]: failed to create hook 'SystemParametersInfoA'\n");
		Sleep(1000);
		return;
	}

	if(MH_EnableHook((void *)DllMain_fp_User32_SystemParametersInfoA) != 0)
	{
		printf("[IgPatchServer.dll][DllMain_Init_SystemParametersInfoA_Hook]: failed to enable hook 'SystemParametersInfoA'\n");
		Sleep(1000);
		return;
	}
}

FARPROC DllMain_fp_Kernel32_CreateMutexA;

typedef HANDLE (__stdcall* DllMain_PtrFunc_CreateMutexA)(LPSECURITY_ATTRIBUTES lpMutexAttributes, BOOL bInitialOwner, LPCSTR lpName);
DllMain_PtrFunc_CreateMutexA DllMain_pfnCreateMutexA;

HANDLE __stdcall DllMain_Hook_CreateMutexA(LPSECURITY_ATTRIBUTES lpMutexAttributes, BOOL bInitialOwner, LPCSTR lpName)
{
	//printf("[IgPatchServer.dll][DllMain_Hook_CreateMutexA]: Ñalled %s\n", lpName);

	if(lpName != 0 && strcmp(lpName, "CrytekApplication") == 0)
	{
		MH_DisableHook((void*)DllMain_fp_Kernel32_CreateMutexA);
		DllMain_On_Game_PreInit();
		return 0;
	}

	return DllMain_pfnCreateMutexA(lpMutexAttributes, bInitialOwner, lpName);
}

void DllMain_Init_CreateMutexA_Hook()
{
	HMODULE hm_Kernel32 = GetModuleHandleA("Kernel32.dll");
	
	if(hm_Kernel32 == 0)
	{
		printf("[IgPatchServer.dll][DllMain_Init_CreateMutexA_Hook]: failed to 'GetModuleHandleA' of 'Kernel32.dll'\n");
		Sleep(1000);
		return;
	}

	DllMain_fp_Kernel32_CreateMutexA = GetProcAddress(hm_Kernel32, "CreateMutexA");

	if(DllMain_fp_Kernel32_CreateMutexA == 0)
	{
		printf("[IgPatchServer.dll][DllMain_Init_CreateMutexA_Hook]: failed to 'GetProcAddress' of 'CreateMutexA'\n");
		Sleep(1000);
		return;
	}
	
	if(MH_CreateHook((void *)DllMain_fp_Kernel32_CreateMutexA, DllMain_Hook_CreateMutexA, (LPVOID *)&DllMain_pfnCreateMutexA) != 0)
	{
		printf("[IgPatchServer.dll][DllMain_Init_CreateMutexA_Hook]: failed to create hook 'CreateMutexA'\n");
		Sleep(1000);
		return;
	}

	if(MH_EnableHook((void *)DllMain_fp_Kernel32_CreateMutexA) != 0)
	{
		printf("[IgPatchServer.dll][DllMain_Init_CreateMutexA_Hook]: failed to enable hook 'CreateMutexA'\n");
		Sleep(1000);
		return;
	}
}

void DllMain_Init_Printf()
{
	AllocConsole();
	FILE *stream;
	freopen_s(&stream, "CON", "w", stdout);
	printf("[IgPatchServer.dll][DllMain_Init_Printf]: Ok\n");
}

BOOL APIENTRY DllMain(HMODULE hModule,
	DWORD  ul_reason_for_call,
	LPVOID lpReserved
)
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
		DllMain_Init_Printf();
		MH_Initialize();
		DllMain_Init_CreateMutexA_Hook();
		DllMain_Init_SystemParametersInfoA_Hook();
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}