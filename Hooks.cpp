#include "Game/Core/Core.hpp"
#include "Game/Menu/Menu.hpp"
#include "Game/Menu/ImGui/imgui_impl_win32.h"

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

HRESULT __stdcall Hooks::hkEndScene(LPDIRECT3DDEVICE9 pDevice)
{
	if (!IGame.CORE->pD3DDevice)
		IGame.CORE->pD3DDevice = pDevice;

	pDevice->SetRenderState(D3DRS_COLORWRITEENABLE, 0xFFFFFFFF);

	long originalReturn = IGame.CORE->oEndScene(pDevice);

	nMenu::Start(pDevice);

	return originalReturn;
}

LRESULT __stdcall Hooks::hkWndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	if (ImGui_ImplWin32_WndProcHandler(hWnd, uMsg, wParam, lParam))
		return true;

	return CallWindowProc(IGame.CORE->windowProc, hWnd, uMsg, wParam, lParam);
}
