#pragma once
#pragma comment(lib, "d3d9.lib")
#include <Windows.h>
#include <d3d9.h>
#include "HookBase.hpp"

namespace nDX //These functions should not be touched - they're only used by the DirectX library I'm using
{
	typedef HRESULT(APIENTRY* tEndScene)(LPDIRECT3DDEVICE9 pDevice);

	static HWND window;

	BOOL CALLBACK EnumWindowsCallback(HWND handle, LPARAM lParam);

	HWND GetProcessWindow();

	bool GetD3D9Device(void** pTable, size_t Size);
}

namespace nTestDrawing
{
	void DrawFilledRect(int x, int y, int w, int h, D3DCOLOR color, IDirect3DDevice9* dev);
}