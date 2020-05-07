#pragma once
#pragma comment(lib, "d3d9.lib")
#include <Windows.h>
#include <d3d9.h>
#include <TlHelp32.h>
#include "HookBase.hpp"
#include <sstream>
#include <vector>

namespace nDX //These functions should not be touched - they're only used by the DirectX library I'm using
{
	typedef HRESULT(APIENTRY* tEndScene)(LPDIRECT3DDEVICE9 pDevice);

	static HWND window;

	BOOL CALLBACK EnumWindowsCallback(HWND handle, LPARAM lParam);

	HWND GetProcessWindow();

	bool GetD3D9Device(void** pTable, size_t Size);
}

struct CUserCmd
{
	double m_nIsInFight; //Set to 0 if we are not fighting, 1 if we are.
	UCHAR pad0[0xC8];
	double m_nKills; //Current amount of monsters killed
	UCHAR pad1[0x238];
	double m_nRoom; //Backup Room, used to return the player to a valid room after a fight.
	UCHAR pad2[0xF8];
	double m_nLOVE; //Level of Violence
	UCHAR pad3[0x4];
	double m_nEXP; //Execution Points
	UCHAR pad4[0x4];
	double m_nGold; //Gold
	UCHAR pad5[0xB8];
	double m_nMaxHealth; //Maximum Health
	UCHAR pad6[0x8];
	double m_nHealth; //Current Health
};

struct vec4
{
	float x, y, z, w;
};

using matrix44 = float[4][4];


struct WeirdStuff
{
	union {
		__int32 v32;
		__int64 v64;
		double    val;                        // value when real
		union {
			union {
				vec4* pVec4;
				matrix44* pMatrix44;
				void* ptr;
			};
		};
	};
	int        flags;                            // use for flags (Hijack for Enumerable and Configurable bits in JavaScript)  (Note: probably will need a visibility as well, to support private variables that are promoted to object scope, but should not be seen (is that just not enumerated????) )
	int        kind;                            // kind of value

};

namespace nFuncs
{
	CUserCmd* GetCmd();
	int* GetRoomPointer();

	void room_goto_proxy(int nRoom); //NOT the room_goto function! Just a proxy for room_goto_previous
	void room_goto_previous();
	void room_restart();
}

namespace gVars
{
	inline HANDLE hCurrentProcess;
	inline DWORD dwBase;
	inline DWORD dwUserCmd;
	inline DWORD dwRoom_GoTo;
	inline DWORD dwRoom_Prev;
	inline DWORD dwRoom_Restart;

	void Initialize();
}

std::string DecToHex(int v);

namespace nMemory //Every function related to Memory
{
	inline DWORD dwCommandOffset		= 0x3F9F44;
	inline DWORD dwRoomNumberPtr		= 0xA18EA0; //Pointer to a 4byte Room Number value. Separate from CUserCmd.

	DWORD* ReadPointerPath(DWORD dwBase, std::vector<DWORD> vPointers);

	HMODULE GetModuleHandleSafe(const wchar_t* pszModuleName);

	DWORD FindPattern(const char* szModule, const char* pattern, const char* mask);
}