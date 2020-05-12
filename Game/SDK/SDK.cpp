#include "SDK.hpp"
#include "../Core/Core.hpp"
#include <TlHelp32.h>

#pragma warning(disable : 4731)

void CGMFunctions::CallGMLFunc(const char* szFuncName, DWORD dwFuncBase, int nArgNumber = 0, PVOID arg1 = nullptr, PVOID arg2 = nullptr, PVOID arg3 = nullptr)
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
	if (nArgNumber >= 3)
		__asm push arg3

	if (nArgNumber >= 2)
		__asm push arg2

	if (nArgNumber >= 1)
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
	return CallGMLFunc("room_goto", IGame.Offsets->room_goto, 1, (PVOID)nRoomNumber);
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
	return CallGMLFunc("window_set_fullscreen", IGame.Offsets->window_set_fullscreen, 1, (PVOID)bFullscreen);
}

void CGMFunctions::room_restart()
{
	return CallGMLFunc("room_restart", IGame.Offsets->room_restart);
}

void CGMFunctions::window_set_size(int x, int y)
{
	return CallGMLFunc("window_set_size", IGame.Offsets->window_set_size, 2, (PVOID)x, (PVOID)y);
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

bool DirectX::GetDirectDevice(void** pTable, size_t Size)
{
	return false;
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
