#pragma once
#include "SDK.hpp"

namespace nHooks
{
	typedef HRESULT(APIENTRY* tEndScene)(LPDIRECT3DDEVICE9 pDevice);

	HRESULT APIENTRY hkEndScene(LPDIRECT3DDEVICE9 pDevice);

	LRESULT __stdcall hkWndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

	inline WNDPROC windowProc;

	void Initialize();
}
