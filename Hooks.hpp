#pragma once
#include "SDK.hpp"

namespace nHooks
{
	HRESULT APIENTRY EndScene_Hook(LPDIRECT3DDEVICE9 pDevice);

	LRESULT __stdcall WndProc_Hook(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

	inline WNDPROC windowProc;

	void Initialize();
}
