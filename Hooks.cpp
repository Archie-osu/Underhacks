#include "Game/Core/Core.hpp"

HRESULT __stdcall Hooks::hkEndScene(LPDIRECT3DDEVICE9 pDevice)
{
	if (!IGame.CORE->pD3DDevice)
		IGame.CORE->pD3DDevice = pDevice;

	pDevice->SetRenderState(D3DRS_COLORWRITEENABLE, 0xFFFFFFFF);

	long originalReturn = IGame.CORE->oEndScene(pDevice);

	//ImGui::Start(pDevice);

	return originalReturn;
}

LRESULT __stdcall Hooks::hkWndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	return CallWindowProc(IGame.CORE->windowProc, hWnd, uMsg, wParam, lParam);
}
