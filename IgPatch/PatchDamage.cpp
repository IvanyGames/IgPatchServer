#include "Header.h"

struct IScriptTable;
struct SmartScriptTable;

struct CGameRules
{
	SmartScriptTable* m_scriptHitInfo()
	{
		return (SmartScriptTable*)((DWORD)this + _Game_CGameRules_m_scriptHitInfo_Vtable_Offset);
	}
	SmartScriptTable* m_serverStateScript()
	{
		return (SmartScriptTable*)*(DWORD*)((DWORD)this + _Game_CGameRules_m_serverStateScript_Vtable_Offset);
	}
};

struct CActor
{
	int GetHealth()
	{
		typedef int(__thiscall* CActorGetHealthClass)(PVOID);
		return vFun_Call<CActorGetHealthClass>(this, _Game_CActor_GetHealth_Vtable_Offset)(this);
	}
};

struct CGameRules;

struct SSharedGameHitInfo
{
  unsigned int shooterId;
  unsigned int targetId;
  int material;
  int typeId;
  int bulletType;
  int partId;
  Vec3 pos;
  Vec3 dir;
};

struct SSourceGameHitInfo
{
  int weaponGameObjectId;
  unsigned int projectileId;
  unsigned __int16 ammoClassId;
  float angle;
  Vec3 normal;
  CTimeValue hitTime;
  bool silencer;
};

struct SGameHitInfo
{
  SSharedGameHitInfo shared;
  SSourceGameHitInfo source;
  float damage;
};

typedef void (__thiscall* PtrFunc_CGameRules_CGameRules_CallScript)(CGameRules *this1, IScriptTable *pScript, const char *name, IScriptTable *p1);
PtrFunc_CGameRules_CGameRules_CallScript pfnCGameRules_CallScript = (PtrFunc_CGameRules_CGameRules_CallScript)_Game_CGameRules_CGameRules_CallScript_Address;

typedef void (__thiscall* PtrFunc_CGameRules_CreateScriptHitInfo)(CGameRules *this1, SmartScriptTable *scriptHitInfo, const SGameHitInfo *hitInfo);
PtrFunc_CGameRules_CreateScriptHitInfo pfnCGameRules_CreateScriptHitInfo = (PtrFunc_CGameRules_CreateScriptHitInfo)_Game_CGameRules_CreateScriptHitInfo_Address;

typedef CActor *(__thiscall* PtrFunc_CGameRules_GetActorByEntityId)(CGameRules *this1, unsigned int entityId);
PtrFunc_CGameRules_GetActorByEntityId pfnCGameRules_GetActorByEntityId = (PtrFunc_CGameRules_GetActorByEntityId)_Game_CGameRules_GetActorByEntityId_Address;

typedef int (__thiscall* PtrFunc_CGameRules_ProcessServerHit)(CGameRules *this1, const SGameHitInfo *hitInfo);
PtrFunc_CGameRules_ProcessServerHit pfnCGameRules_ProcessServerHit = (PtrFunc_CGameRules_ProcessServerHit)_Game_CGameRules_ProcessServerHit_Address;

int __fastcall Hook_CGameRules_ProcessServerHit(CGameRules *this1, void *None, const SGameHitInfo *hitInfo)
{
	CActor *pActor = pfnCGameRules_GetActorByEntityId(this1, hitInfo->shared.shooterId);

	if(pActor && pActor->GetHealth() < 1)
	{
		return 1;
	}
	
	pfnCGameRules_CreateScriptHitInfo(this1, this1->m_scriptHitInfo(), hitInfo);
	pfnCGameRules_CallScript(this1, (IScriptTable *)this1->m_serverStateScript(), "OnHit", (IScriptTable *)this1->m_scriptHitInfo());
	return 1;
}

struct SClientGameHitInfo;

typedef void(__thiscall* PtrFunc_CGameRules_CGameRules_AddServerHit)(CGameRules *this1, const SGameHitInfo *hitInfo);
PtrFunc_CGameRules_CGameRules_AddServerHit pfnCGameRules_AddServerHit = (PtrFunc_CGameRules_CGameRules_AddServerHit)_Game_CGameRules_AddServerHit_Address;

typedef float(__thiscall* PtrFunc_CGameRules_GetClientHitInfoDamage)(CGameRules *this1, const SClientGameHitInfo *clientHit);
PtrFunc_CGameRules_GetClientHitInfoDamage pfnCGameRules_GetClientHitInfoDamage = (PtrFunc_CGameRules_GetClientHitInfoDamage)_Game_CGameRules_GetClientHitInfoDamage_Address;

typedef void(__thiscall* PtrFunc_SGameHitInfo_SGameHitInfo)(SGameHitInfo *this1, const SClientGameHitInfo *clientHit);
PtrFunc_SGameHitInfo_SGameHitInfo pfnSGameHitInfo_SGameHitInfo = (PtrFunc_SGameHitInfo_SGameHitInfo)_Game_SGameHitInfo_SGameHitInfo_Address;

void __fastcall PatchDamage_CGameRules_NetServerHit(CGameRules *this1, void *, const SClientGameHitInfo *clientHit)
{
	SGameHitInfo hitInfo;
	pfnSGameHitInfo_SGameHitInfo(&hitInfo, clientHit);
	hitInfo.damage = pfnCGameRules_GetClientHitInfoDamage(this1, clientHit);
	pfnCGameRules_AddServerHit(this1, &hitInfo);
}

void PatchDamage_PostInit()
{
	if(_Game_PatchDamage_Address != -1){
		DWORD *pDword0 = (DWORD*)(_Game_PatchDamage_Address+0x01);
		DWORD old0;
		VirtualProtect((LPVOID)pDword0, 4, PAGE_READWRITE, &old0);
		*pDword0 = 0 - ((DWORD)pDword0 - ((DWORD)PatchDamage_CGameRules_NetServerHit - 4));
		VirtualProtect((LPVOID)pDword0, 4, old0, &old0);
	}
	
	if(_Game_CGameRules_ProcessServerHit_Address != -1){
		MH_CreateHook((void *)_Game_CGameRules_ProcessServerHit_Address, Hook_CGameRules_ProcessServerHit, (LPVOID *)&pfnCGameRules_ProcessServerHit);
		MH_EnableHook((void *)_Game_CGameRules_ProcessServerHit_Address);
	}
}