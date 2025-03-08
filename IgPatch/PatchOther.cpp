#include "Header.h"

void PathOther_EnableReadInDirectory_Init(){
	BYTE *pDword0 = (BYTE*)_Game_PathOther_EnableReadInDirectory_Address;
	DWORD old0;
	VirtualProtect((LPVOID)pDword0, 1, PAGE_READWRITE, &old0);
	*pDword0 = 0x00;
	VirtualProtect((LPVOID)pDword0, 1, old0, &old0);
	//printf("[IgPatchServer.dll][PathOther_EnableReadInDirectory_Init]: Ok\n");
}

void PathOther_Damage_Init(){

	DWORD *pDword0 = (DWORD*)(_Game_PathOther_Damage_Address+0x01);
	DWORD old0;
	VirtualProtect((LPVOID)pDword0, 4, PAGE_READWRITE, &old0);
	*pDword0 = 0 - ((DWORD)pDword0 - ((DWORD)_Game_PathOther_Damage_Address1 - 4));
	VirtualProtect((LPVOID)pDword0, 4, old0, &old0);
	//printf("[IgPatchServer.dll][PathOther_Damage_Init]: Ok\n");
}

void PatchOther_Init()
{
	if(_Game_PathOther_EnableReadInDirectory_Address != -1){
		PathOther_EnableReadInDirectory_Init();
	}

	if(_Game_PathOther_Damage_Address != -1){
		PathOther_Damage_Init();
	}
}