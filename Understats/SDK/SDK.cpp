#include "SDK.hpp"
#include <Psapi.h>
#pragma warning( disable : 4731 ) //WARNINGS BEGONE
#define INRANGE(x,a,b)    ((x) >= (a) && (x) <= (b))
#define INRANGE(x,a,b)    ((x) >= (a) && (x) <= (b))
#define getBits( x )    (INRANGE(((x)&(~0x20)),'A','F') ? (((x)&(~0x20)) - 'A' + 0xa) : (INRANGE(x,'0','9') ? (x) - '0' : 0))
#define getByte( x )    (getBits((x)[0]) << 4 | getBits((x)[1]))

#pragma region DirectX

BOOL __stdcall nDX::EnumWindowsCallback(HWND handle, LPARAM lParam)
{
	DWORD wndProcId;
	GetWindowThreadProcessId(handle, &wndProcId);

	if (GetCurrentProcessId() != wndProcId)
		return TRUE; // skip to next window

	window = handle;
	return FALSE; // window found abort search
}

HWND nDX::GetProcessWindow()
{
	window = NULL;
	EnumWindows(EnumWindowsCallback, NULL);
	return window;
}

bool nDX::GetD3D9Device(void** pTable, size_t Size)
{
	if (!pTable)
		return false;

	IDirect3D9* pD3D = Direct3DCreate9(D3D_SDK_VERSION);

	if (!pD3D)
		return false;

	IDirect3DDevice9* pDummyDevice = NULL;

	// options to create dummy device
	D3DPRESENT_PARAMETERS d3dpp = {};
	d3dpp.Windowed = false;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.hDeviceWindow = GetProcessWindow();

	HRESULT dummyDeviceCreated = pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, d3dpp.hDeviceWindow, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dpp, &pDummyDevice);

	if (dummyDeviceCreated != S_OK)
	{
		// may fail in windowed fullscreen mode, trying again with windowed mode
		d3dpp.Windowed = !d3dpp.Windowed;

		dummyDeviceCreated = pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, d3dpp.hDeviceWindow, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dpp, &pDummyDevice);

		if (dummyDeviceCreated != S_OK)
		{
			pD3D->Release();
			return false;
		}
	}

	memcpy(pTable, *reinterpret_cast<void***>(pDummyDevice), Size);

	pDummyDevice->Release();
	pD3D->Release();
	return true;
}

#pragma endregion 

#pragma region Game

void gVars::Initialize()
{
	dwBase = reinterpret_cast<DWORD>(nMemory::GetModuleHandleSafe(L"UNDERTALE.exe"));
	dwUserCmd = (DWORD)nMemory::ReadPointerPath(dwBase + nMemory::dwCommandOffset, { 0x0, 0x0, 0x44, 0x10, 0x364 }) - 0x30;
	dwRoom_GoTo = nMemory::FindPattern("UNDERTALE.exe", "\xA1\x00\x00\x00\x00\x8B\x4C\x24\x14\x50", "x????xxxxx"); //room_goto
	dwRoom_Prev = nMemory::FindPattern("UNDERTALE.exe", "\xE8\x00\x00\x00\x00\x8B\x0D\x00\x00\x00\x00\x3B\xC8\x75\x1A", "x????xx????xxxx"); //room_goto_previous
	dwRoom_Restart = nMemory::FindPattern("UNDERTALE.exe", "\xA1\x00\x00\x00\x00\x50\xA3\x00\x00\x00\x00", "x????xx????"); //room_restart
	dwAudio_Stop_All = nMemory::FindPattern("UNDERTALE.exe", "\x80\x3D\x00\x00\x00\x00\x00\x75\x08\x6A\x00", "xx?????xxxx");
	dwRoom_Next = dwRoom_Prev + 0x50;
	dwRoom_GoTo -= 0x3F240;
	dwWindow_SetFullScreen = dwRoom_GoTo - 0x778B0;
}

CUserCmd* nFuncs::GetCmd()
{
	return reinterpret_cast<CUserCmd*>(gVars::dwUserCmd);
}

int* nFuncs::GetRoomPointer()
{
	return reinterpret_cast<int*>(nMemory::dwRoomNumberPtr);
}

void nFuncs::CallGMLFunc(const char* szFuncName, DWORD dwFuncBase, int nArgNumber = 0, PVOID arg1 = nullptr, PVOID arg2 = nullptr, PVOID arg3 = nullptr)
{
	//Create the variables that will store information about the base of the stack.
	unsigned int nStackBase;
	unsigned int nStackPointer;

	__asm
	{
		//Setup the variables for recovering the stack
		mov nStackBase, ebp
		mov nStackPointer, esp

		//Now let the game know which function we're gonna call.
		mov esi, szFuncName
	}

	//Now let's push the arguments
	if (nArgNumber)
	{
		if (nArgNumber >= 3)
			__asm push arg3
		
		if (nArgNumber >= 2)
			__asm push arg2

		if (nArgNumber >= 1)
			__asm push arg1
	}

	__asm
	{
		call dwFuncBase
		
		//Fix the stack
		mov ebp, nStackBase
		mov esp, nStackPointer
	}
}

void nFuncs::room_goto_previous()
{
	CallGMLFunc("room_goto_previous", gVars::dwRoom_Prev);

	nFuncs::GetCmd()->m_Interact = 0.0;
}

void nFuncs::room_goto_next()
{
	CallGMLFunc("room_goto_next", gVars::dwRoom_Next);

	nFuncs::GetCmd()->m_Interact = 0.0;
}

void nFuncs::window_set_fullscreen(bool bFullscreen)
{
	CallGMLFunc("window_set_fullscreen", gVars::dwWindow_SetFullScreen, 1, (PVOID)bFullscreen);
}

void nFuncs::room_restart()
{
	CallGMLFunc("room_restart", gVars::dwRoom_Restart);

	nFuncs::GetCmd()->m_Interact = 0.0;
}

void nFuncs::window_set_size(int x, int y)
{
	static const DWORD dwFunction = 0x43CC80;

	CallGMLFunc("window_set_size", dwFunction, 2, (PVOID)x, (PVOID)y);
}

void nFuncs::room_goto(DWORD nIndex)
{
	audio_stop_all();

	CallGMLFunc("room_goto", gVars::dwRoom_GoTo, 1, (PVOID)nIndex);

	gVars::nTeleportsLeft = 0;
	gVars::nLastRequested = nIndex;
}

void nFuncs::room_goto_meme(int nRoom)
{
	int nCurRoom = *GetRoomPointer();

	if (nRoom > nCurRoom) {
		room_goto_next();
		gVars::nTeleportsLeft = nRoom - (nCurRoom - 1);
	}
	else if (nRoom < nCurRoom) {
		room_goto_previous();
		gVars::nTeleportsLeft = (nCurRoom - 1) - nRoom;
	}

	if (gVars::nTeleportsLeft == 0)
		room_restart();

	nFuncs::GetCmd()->m_Interact = 0; //Movement Fix

	gVars::nLastRequested = nRoom;
}

void nFuncs::audio_stop_all()
{
	CallGMLFunc("audio_stop_all", gVars::dwAudio_Stop_All);
}

DWORD* nMemory::ReadPointerPath(DWORD dwBase, std::vector<DWORD> vPointers)
{
	DWORD* pTraversal = (DWORD*)dwBase;

	for (DWORD offset : vPointers)
	{
		pTraversal = reinterpret_cast<DWORD*>(*(pTraversal + (offset / sizeof(DWORD))));
	}

	return (DWORD*)pTraversal;
}

HMODULE nMemory::GetModuleHandleSafe(const wchar_t* pszModuleName)
{
	HMODULE hmModuleHandle = nullptr;

	do {
		hmModuleHandle = GetModuleHandleW(pszModuleName);
		Sleep(1);
	} while (hmModuleHandle == nullptr);

	return hmModuleHandle;
}

#pragma endregion

#pragma region Memory and Stuff
std::string DecToHex(int v)
{
	std::stringstream stream;
	stream << std::hex << v;
	std::string result(stream.str());

	return result;
}

MODULEINFO GetModuleInfo(const char* szModule)
{
	MODULEINFO modinfo = { 0 };
	HMODULE hModule = nMemory::GetModuleHandleSafe(L"UNDERTALE.exe");
	if (hModule == 0)
		return modinfo;
	GetModuleInformation(GetCurrentProcess(), hModule, &modinfo, sizeof(MODULEINFO));
	return modinfo;
}

DWORD nMemory::FindPattern(const char* szModule, const char* pattern, const char* mask)
{
	//Get all module related information
	MODULEINFO mInfo = GetModuleInfo(szModule);

	//Assign our base and module size
	DWORD base = (DWORD)mInfo.lpBaseOfDll;
	DWORD size = (DWORD)mInfo.SizeOfImage;

	//Get length for our mask, this will allow us to loop through our array
	DWORD patternLength = (DWORD)strlen(mask);

	for (DWORD i = 0; i < size - patternLength; i++)
	{
		bool found = true;
		for (DWORD j = 0; j < patternLength; j++)
		{
			//if we have a ? in our mask then we have true by default,
			//or if the bytes match then we keep searching until finding it or not
			found &= mask[j] == '?' || pattern[j] == *(char*)(base + i + j);
		}

		//found = true, our entire pattern was found
		if (found)
		{
			return base + i;
		}
	}
	return NULL;
}

#pragma endregion