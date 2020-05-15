#include "SDK.hpp"
#include "../Core/Core.hpp"
#include <TlHelp32.h>

#pragma warning(disable : 4731)

void CGMFunctions::CallGMLFunc(const char* szFuncName, DWORD dwFuncBase, PVOID arg1, PVOID arg2, PVOID arg3)
{
	if (dwFuncBase == 0)
		return;

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
	if (arg3 != nullptr)
		__asm push arg3

	if (arg2 != nullptr)
		__asm push arg2

	if (arg1 != nullptr)
		__asm push arg1

	__asm
	{
		call dwFuncBase

		//Fix the stack
		mov ebp, nStackBase
		mov esp, nStackPointer
	}
}

void CGMFunctions::room_goto(int nRoomNumber)
{
	return CallGMLFunc("room_goto", IGame.Offsets->room_goto, (PVOID)nRoomNumber);
}

void CGMFunctions::room_goto_meme(int nRoomNumber)
{
	//To be implemented
	//or maybe not
}

void CGMFunctions::audio_stop_all()
{
	return CallGMLFunc("audio_stop_all", IGame.Offsets->audio_stop_all);
}

void CGMFunctions::room_goto_previous()
{
	return CallGMLFunc("room_goto_previous", IGame.Offsets->room_goto_previous);
}

void CGMFunctions::room_goto_next()
{
	return CallGMLFunc("room_goto_next", IGame.Offsets->room_goto_next);
}

void CGMFunctions::window_set_fullscreen(bool bFullscreen)
{
	return CallGMLFunc("window_set_fullscreen", IGame.Offsets->window_set_fullscreen, (PVOID)bFullscreen);
}

void CGMFunctions::room_restart()
{
	return CallGMLFunc("room_restart", IGame.Offsets->room_restart);
}

void CGMFunctions::window_set_size(int x, int y)
{
	return CallGMLFunc("window_set_size", IGame.Offsets->window_set_size, (PVOID)x, (PVOID)y);
}

HMODULE Memory::GetModuleHandleSafe(const wchar_t* pszModuleName)
{
	HMODULE hmModuleHandle = nullptr;

	do {
		hmModuleHandle = GetModuleHandleW(pszModuleName);
		Sleep(1);
	} while (hmModuleHandle == nullptr);

	return hmModuleHandle;
}

DWORD Memory::FindPattern(const char* szModule, const char* pattern, const char* mask)
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

MODULEINFO Memory::GetModuleInfo(const char* szModule)
{
	MODULEINFO modinfo = { 0 };
	HMODULE hModule = GetModuleHandleSafe(L"UNDERTALE.exe");
	if (hModule == 0)
		return modinfo;
	GetModuleInformation(GetCurrentProcess(), hModule, &modinfo, sizeof(MODULEINFO));
	return modinfo;
}

DWORD* Memory::ReadPointerPath(DWORD dwBase, std::vector<DWORD> vPointers)
{
	DWORD* pTraversal = (DWORD*)dwBase;

	for (DWORD offset : vPointers)
	{
		pTraversal = reinterpret_cast<DWORD*>(*(pTraversal + (offset / sizeof(DWORD))));
	}

	return (DWORD*)pTraversal;
}

DWORD Memory::FindUTPattern(const char* szPattern, const char* szMask)
{
	return FindPattern("UNDERTALE.exe", szPattern, szMask);
}

BOOL __stdcall DirectX::EnumWindowsCallback(HWND handle, LPARAM lParam)
{
	DWORD wndProcId;
	GetWindowThreadProcessId(handle, &wndProcId);

	if (GetCurrentProcessId() != wndProcId)
		return true; // skip to next window

	hwWindow = handle;
	return false;
}

HWND DirectX::GetProcessWindow()
{
	hwWindow = NULL;
	EnumWindows(EnumWindowsCallback, NULL);
	return hwWindow;
}

bool DirectX::GetDirectDevice(void** pTable, size_t Size)
{
	if (!pTable)
		return false;

	IDirect3D9* pD3D = Direct3DCreate9(D3D_SDK_VERSION);

	if (!pD3D)
		return false;

	IDirect3DDevice9* pDummyDevice = NULL;

	// options to create dummy device
	D3DPRESENT_PARAMETERS d3dpp = {};
	d3dpp.Windowed = true;
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

bool TrampHook::Hook(char* szSource, char* szDestination, int nLenght)
{
	if (nLenght < 5) return false;

	DWORD curProtection;

	VirtualProtect(szSource, nLenght, PAGE_EXECUTE_READWRITE, &curProtection);

	memset(szSource, 0x90, nLenght);

	uintptr_t relativeAddress = (uintptr_t)(szDestination - szSource - 5);

	*szSource = (char)0xE9;
	*(uintptr_t*)(szSource + 1) = (uintptr_t)relativeAddress;

	DWORD temp;
	VirtualProtect(szSource, nLenght, curProtection, &temp);

	return true;
}

char* TrampHook::Trampoline(char* szSource, char* szDestination, unsigned int nLenght)
{
	if (nLenght < 5) return 0;

	// Create the gateway (len + 5 for the overwritten bytes + the jmp)
	char* gateway = (char*)VirtualAlloc(0, nLenght + 5, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);

	// Put the bytes that will be overwritten in the gateway
	memcpy(gateway, szSource, nLenght);

	// Get the gateway to destination addy
	uintptr_t gateJmpAddy = (uintptr_t)(szSource - gateway - 5);

	// Add the jmp opcode to the end of the gateway
	*(gateway + nLenght) = (char)0xE9;

	// Add the address to the jmp
	*(uintptr_t*)(gateway + nLenght + 1) = gateJmpAddy;

	// Place the hook at the destination
	if (Hook(szSource, szDestination, nLenght))
	{
		return gateway;
	}
	else return nullptr;
}

void CCheat::DoubleProxy()
{
	//This function sets the CPlayerData or whatever is represented as a double
	//to their bool representation respectively.

	IGame.PlayerData->m_nDebug = static_cast<double>(this->bDebugMode);
}

int CCheat::GetMaxHP()
{
	int LOVE = static_cast<int>(IGame.PlayerData->m_nLOVE);

	if (LOVE == 20)
		return 99;

	if (LOVE <= 19)
		return 20 + ((LOVE - 1) * 4);

	return -1;
}
