#pragma once
#include <Windows.h>
#include <Psapi.h>
#include <vector>
#include <d3d9.h>

namespace Memory
{
	HMODULE GetModuleHandleSafe(const wchar_t* pszModuleName);
	DWORD FindPattern(const char* szModule, const char* pattern, const char* mask);
	MODULEINFO GetModuleInfo(const char* szModule);
	DWORD* ReadPointerPath(DWORD dwBase, std::vector<DWORD> vPointers);
	DWORD FindUTPattern(const char* szPattern, const char* szMask);
}

namespace DirectX
{
	bool GetDirectDevice(void** pTable, size_t Size);
}

namespace TrampHook
{
	bool Hook(char* szSource, char* szDestination, int nLenght);
	char* Trampoline(char* szSource, char* szDestination, unsigned int nLenght);
}

namespace Hooks
{
	HRESULT __stdcall hkEndScene(LPDIRECT3DDEVICE9 pDevice);
	LRESULT __stdcall hkWndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
}