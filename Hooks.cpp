#include "SDK.hpp"
#include "Hooks.hpp"
#include "Menu.hpp"

bool bInit;
nDX::tEndScene original = nullptr;
LPDIRECT3DDEVICE9 pD3DDevice = nullptr;
void* d3d9Device[119];

HRESULT APIENTRY nHooks::EndScene_Hook(LPDIRECT3DDEVICE9 pDevice)
{
	if (bInit == false)
	{
		pD3DDevice = pDevice;
		bInit = true;
	}

	pDevice->SetRenderState(D3DRS_COLORWRITEENABLE, 0xFFFFFFFF);

	long originalReturn = original(pDevice);

	nMenu::Start(pDevice);

	return originalReturn;
}

LRESULT __stdcall nHooks::WndProc_Hook(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	if (ImGui_ImplWin32_WndProcHandler(hWnd, uMsg, wParam, lParam))
		return true;

	return CallWindowProc(windowProc, hWnd, uMsg, wParam, lParam);
}

void nHooks::Initialize()
{
	if (nDX::GetD3D9Device(d3d9Device, sizeof(d3d9Device)))
		original = (nDX::tEndScene)nHookBase::TrampHook((char*)d3d9Device[42], (char*)EndScene_Hook, 7);

	windowProc = (WNDPROC)(SetWindowLongW(FindWindowA(0, "UNDERTALE"), GWLP_WNDPROC, (LONG_PTR)(&WndProc_Hook)));
}
