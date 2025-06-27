#pragma once
#include <Windows.h>
#include <iostream>
#include "MH/MinHook.h"

#include "Versions/Ru_1.1.1.129.h"
//#include "Versions/Ru_1.1.1.426.h"

////Include CryString.h////

#include <cassert>

#define NOT_USE_CRY_MEMORY_MANAGER

#define CryModuleMalloc malloc

inline size_t CryModuleFree(void *p) {
	size_t size = 0;
	if (p)
	{
		size = _msize(p);
		free(p);
	}
	return size;
}

template<class D, class S>
inline D check_cast(S const& s)
{
	D d = D(s);
	assert(S(d) == s);
	return d;
}

template<class D, class S>
inline D& check_convert(D& d, S const& s)
{
	d = D(s);
	assert(S(d) == s);
	return d;
}

template<class D>
struct CheckConvert
{
	CheckConvert(D& d)
		: dest(&d) {}

	template<class S>
	D& operator=(S const& s)
	{
		return check_convert(*dest, s);
	}

protected:
	D*	dest;
};

template<class D>
inline CheckConvert<D> check_convert(D& d)
{
	return d;
}

#include "CryString.h"
typedef CryStringT<char> string;

////Include CryString.h////

struct XmlString : public string
{
	XmlString() {};
	XmlString( const char *str ) : string(str) {};
	operator const char*() const { return c_str(); }
};

struct IXmlNode
{
	bool getAttr(const char *key, const char **value);
};

struct IConsoleCmdArgs
{
	const char* GetArg( int nIndex );
};

typedef void (*ConsoleCommandFunc)( IConsoleCmdArgs* );

struct IConsole
{
	void AddCommand( const char *sCommand, ConsoleCommandFunc func, int nFlags=0, const char *sHelp=NULL );
};

struct INetChannel
{
	int GetProfileId();
	void Disconnect( int cause, const char * fmt);
};

struct IActor
{
	unsigned __int16 GetChannelId();
};

struct IActorIterator
{
	IActor* Next();
	void Release();
};

struct IActorSystem
{
	void CreateActorIterator(IActorIterator **pOutIter);
};

struct IGameFramework
{
	IActorSystem *GetIActorSystem();
	INetChannel *GetNetChannel(unsigned __int16 channelId);
};

struct IGame
{
	IGameFramework * GetIGameFramework();
};

struct I3DEngine;
struct IScriptSystem;
struct IPhysicalWorld;
struct ICryPak;
struct ITimer;
struct IEntitySystem;
struct ISystem;
struct ILog;
struct IAISystem;

struct SSystemGlobalEnvironment
{
	I3DEngine *p3DEngine();
	IScriptSystem *pScriptSystem();
	IPhysicalWorld *pPhysicalWorld();
	ICryPak *pCryPak();
	ITimer *pTimer();
	IGame *pGame();
	IEntitySystem *pEntitySystem();
	IConsole *pConsole();
	ISystem *pSystem();
	ILog *pLog();
	IAISystem *pAISystem();
};

extern SSystemGlobalEnvironment *gEnv();


typedef unsigned int				uint32;
typedef void (*FrameProfilerSectionCallback)( class CFrameProfilerSection *pSection );

struct SPlatformInfo
{
	unsigned int numCoresAvailableToProcess;

#if defined(WIN32) || defined(WIN64)
	enum EWinVersion
	{
		WinUndetected,
		Win2000,
		WinXP,
		WinSrv2003,
		WinVista,
		Win7
	};

	EWinVersion winVer;
	bool win64Bit;
	bool vistaKB940105Required;
#endif
};

struct SSystemInitParams
{
	typedef void* (*ProtectedFunction)( void *param1,void *param2 );
};

enum ESystemProtectedFunctions
{
	eProtectedFunc_Save = 0,
	eProtectedFunc_Load = 1,
	eProtectedFuncsLast = 10,
};
//

struct SSystemGlobalEnvironment_2011
{
	void*             pDialogSystem;//0
	I3DEngine*                 p3DEngine;//1
	void*                  pNetwork;//2
	IScriptSystem*             pScriptSystem;//3
	IPhysicalWorld*            pPhysicalWorld;//4
	void*               pFlowSystem;//5
	void*                    pInput;//6
	void*              pMusicSystem;//7
	void*			   pStatoscope;//8
	void*        pFileChangeMonitor;
	ICryPak*                   pCryPak;//10
	void* None1;
	void*         pProfileLogSystem;//12 ???
	void*          pParticleManager;//13
	void*       pFrameProfileSystem;//14
	ITimer*                    pTimer;//15
	void*                  pCryFont;//16
	IGame*                     pGame;//17
	void*		   pLocalMemoryUsage;//18
	IEntitySystem*             pEntitySystem;//19
	IConsole*                  pConsole;//20
	void*              pSoundSystem;//21
	ISystem*                   pSystem;//22
	void*         pCharacterManager;//23
	IAISystem*                 pAISystem;//24
	ILog*                      pLog;//25
	void*		   pCodeCheckpointMgr;//26
	void*              pMovieSystem;//27
	void*                pNameTable;//28
	void*                pVisualLog;//29
	void*                 pRenderer;//30
	void*            pAuxGeomRenderer;//31
	void*            pHardwareMouse;//32 ???
	void*          pMaterialEffects;//33
	void*          pSystemScheduler;//34 //136
	uint32										 mMainThreadId;//140
	uint32                     nMainFrameID;
	const char*                szCmdLine;
	enum { MAX_DEBUG_STRING_LENGTH = 128 };
	char											szDebugStatus[MAX_DEBUG_STRING_LENGTH];
	bool                       bServer;//280
	bool											 bMultiplayer;//281
	bool                       bHostMigrating;//282
	bool                       bProfilerEnabled;//283
	FrameProfilerSectionCallback callbackStartSection;//284
	FrameProfilerSectionCallback callbackEndSection;//288
	bool											bIgnoreAllAsserts;//292
	bool											bNoAssertDialog;//293
	bool											bTesting;//294
	bool											bNoRandomSeed;//295
	SPlatformInfo pi;//296
	SSystemInitParams::ProtectedFunction pProtectedFunctions[eProtectedFuncsLast];//308
	bool											bIsOutOfMemory;//348
	bool bClient;//349
	bool bEditor;//350
	bool bEditorGameMode;//351
	bool bDedicated;//352
	bool m_isFMVPlaying;//353
};

struct Vec3
{
  float x;
  float y;
  float z;
};

struct CTimeValue
{
  __int64 m_lValue;
};

extern SSystemGlobalEnvironment_2011 *gEnv_2011;

extern void PatchAi_PreInit();
extern void PatchAi_PostInit();
extern void PatchOther_PreInit();
extern void PatchDamage_PostInit();
extern void PatchKick_PostInit();

template< typename cData >
cData vFun_Call(PVOID BaseClass, DWORD vIndex)
{
	PDWORD *vPointer = (PDWORD *)BaseClass;
	PDWORD vFunction = *vPointer;
	DWORD dwAddress = vFunction[(vIndex / 4)];
	return (cData)(dwAddress);
};