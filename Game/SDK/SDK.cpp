#include "SDK.hpp"
#include "../Interfaces/Interfaces.hpp"
#include <TlHelp32.h>

#pragma warning(disable : 4731)

void CGMFunctions::CallGMLFunc(const char* szFuncName, DWORD dwFuncBase, int nArgNumber = 0, PVOID arg1 = nullptr, PVOID arg2 = nullptr, PVOID arg3 = nullptr)
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
		if (nArgNumber >= 2 && arg2 != nullptr)
			__asm push arg2

		if (nArgNumber >= 1 && arg1 != nullptr)
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

void CGMFunctions::room_goto(int nRoomNumber)
{
	return CallGMLFunc("room_goto", IGame.Offsets.room_goto, 1, (PVOID)nRoomNumber);
}

void CGMFunctions::room_goto_meme(int nRoomNumber)
{
	//To be implemented
	//or maybe not
}

void CGMFunctions::audio_stop_all()
{
	return CallGMLFunc("audio_stop_all", IGame.Offsets.audio_stop_all);
}

void CGMFunctions::room_goto_previous()
{
	return CallGMLFunc("room_goto_previous", IGame.Offsets.room_goto_previous);
}

void CGMFunctions::room_goto_next()
{
	return CallGMLFunc("room_goto_next", IGame.Offsets.room_goto_next);
}

void CGMFunctions::window_set_fullscreen(bool bFullscreen)
{
	return CallGMLFunc("window_set_fullscreen", IGame.Offsets.window_set_fullscreen, 1, (PVOID)bFullscreen);
}

void CGMFunctions::room_restart()
{
	return CallGMLFunc("room_restart", IGame.Offsets.room_restart);
}

void CGMFunctions::window_set_size(int x, int y)
{
	return CallGMLFunc("window_set_size", IGame.Offsets.window_set_size, 2, (PVOID)x, (PVOID)y);
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
