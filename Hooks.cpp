#include "SDK.hpp"
#include "Hooks.hpp"
#include "Menu.hpp"

bool bInit;
nHooks::tEndScene oEndScene = nullptr;
LPDIRECT3DDEVICE9 pD3DDevice = nullptr;
void* pDevice[119];

HRESULT APIENTRY nHooks::hkEndScene(LPDIRECT3DDEVICE9 pDevice)
{
	if (bInit == false)
	{
		pD3DDevice = pDevice;
		bInit = true;
	}

	pDevice->SetRenderState(D3DRS_COLORWRITEENABLE, 0xFFFFFFFF);

	long originalReturn = oEndScene(pDevice);

	nMenu::Start(pDevice);

	return originalReturn;
}

LRESULT __stdcall nHooks::hkWndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	if (ImGui_ImplWin32_WndProcHandler(hWnd, uMsg, wParam, lParam))
		return true;

	return CallWindowProc(windowProc, hWnd, uMsg, wParam, lParam);
}

void nHooks::Initialize()
{
	if (nDX::GetD3D9Device(pDevice, sizeof(pDevice)))
		oEndScene = (tEndScene)nHookBase::TrampHook((char*)pDevice[42], (char*)hkEndScene, 7);

	windowProc = (WNDPROC)(SetWindowLongW(FindWindowA(0, "UNDERTALE"), GWLP_WNDPROC, (LONG_PTR)(&hkWndProc)));
}
