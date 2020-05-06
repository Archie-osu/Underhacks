#pragma once
#pragma comment(lib, "d3d9.lib")
#include <Windows.h>
#include <d3d9.h>
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
	UCHAR pad1[0x337];
	double m_nLOVE; //Level of Violence
	UCHAR pad2[0x4];
	double m_nEXP; //Execution Points
	UCHAR pad3[0x4];
	double m_nGold; //Gold
	UCHAR pad4[0xB8];
	double m_nMaxHealth; //Maximum Health
	UCHAR pad5[0x8];
	double m_nHealth; //Current Health
};


namespace gVars
{
	inline HANDLE hCurrentProcess;
	inline DWORD dwBase;
	inline DWORD dwUserCmd;
	inline DWORD dwRoom;

	void Initialize();
	CUserCmd* GetCmd();
}

std::string DecToHex(int v);

namespace nMemory //Every function related to Memory
{
	inline DWORD dwCommandOffset		= 0x3F9F44;
	inline DWORD dwRoomNumberOffset	= 0x618EA0; //used only for Room Number, more investigation has to be done
	//There may be some useful values around there in memory.

	DWORD* ReadPointerPath(DWORD dwBase, std::vector<DWORD> vPointers);

	HMODULE GetModuleHandleSafe(const wchar_t* pszModuleName);
}