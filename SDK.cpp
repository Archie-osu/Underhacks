#include "SDK.hpp"
#include <Psapi.h>
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
	hCurrentProcess = GetCurrentProcess();
	dwBase = reinterpret_cast<DWORD>(nMemory::GetModuleHandleSafe(L"UNDERTALE.exe"));
	dwUserCmd = (DWORD)nMemory::ReadPointerPath(dwBase + nMemory::dwCommandOffset, { 0x0, 0x0, 0x44, 0x10, 0x364 }) - 0x30;
	dwRoom_GoTo = nMemory::FindPattern("UNDERTALE.exe", "\xA1\x00\x00\x00\x00\x8B\x4C\x24\x14\x50", "x????xxxxx");
	dwRoom_Prev = nMemory::FindPattern("UNDERTALE.exe", "\xE8\x00\x00\x00\x00\x8B\x0D\x00\x00\x00\x00\x3B\xC8\x75\x1A", "x????xx????xxxx");
	dwRoom_Restart = nMemory::FindPattern("UNDERTALE.exe", "\xA1\x00\x00\x00\x00\x50\xA3\x00\x00\x00\x00", "x????xx????");
}

CUserCmd* nFuncs::GetCmd()
{
	return reinterpret_cast<CUserCmd*>(gVars::dwUserCmd);
}

int* nFuncs::GetRoomPointer()
{
	return reinterpret_cast<int*>(nMemory::dwRoomNumberPtr);
}

void nFuncs::room_goto_previous()
{
	static auto room_prev = reinterpret_cast<int* (__cdecl*)()>(gVars::dwRoom_Prev);

	room_prev();
}

void nFuncs::room_restart()
{
	static auto room_restart = reinterpret_cast<int* (__cdecl*)()>(gVars::dwRoom_Restart); //Get the function for room_goto_previous

	room_restart();
}

void nFuncs::room_goto_proxy(int nRoom)
{
	static auto room_prev = reinterpret_cast<int* (__cdecl*)()>(gVars::dwRoom_Prev); //Get the function for room_goto_previous

	*GetRoomPointer() = nRoom + 1; //Overwrite our True Room Number with our desired room + one

	room_prev(); //Decrement our true room number by one and travel to that room.
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