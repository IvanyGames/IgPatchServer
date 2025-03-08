#include "Header.h"

typedef void (__thiscall* PtrFunc_Unknown0)(void *this1);
PtrFunc_Unknown0 pfnUnknown0 = (PtrFunc_Unknown0)_Game_Unknown0_Address;

void __fastcall Hook_Unknown0(void *this1, void *None)
{
	//printf("[IgPatchServer.dll][Hook_Unknown0]: Ñalled\n");
}

void DllMain_On_Game_PreInit()
{
	PatchAi_PreInit();
	PatchOther_Init();
}

void DllMain_On_Game_PostInit()
{
	if(_Game_Unknown0_Address != -1){
		MH_CreateHook((void*)_Game_Unknown0_Address, Hook_Unknown0, (LPVOID*)&pfnUnknown0);
		MH_EnableHook((void*)_Game_Unknown0_Address);
	}
	
	PatchAi_PostInit();
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