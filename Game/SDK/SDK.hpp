#pragma once
#include <Windows.h>
#include <Psapi.h>
#include <vector>

namespace Memory
{
	HMODULE GetModuleHandleSafe(const wchar_t* pszModuleName);
	DWORD FindPattern(const char* szModule, const char* pattern, const char* mask);
	MODULEINFO GetModuleInfo(const char* szModule);
	DWORD* ReadPointerPath(DWORD dwBase, std::vector<DWORD> vPointers);
	DWORD FindUTPattern(const char* szPattern, const char* szMask);
}