#include "Game/Core/Core.hpp"
#include <Windows.h>

DWORD WINAPI Main(LPVOID lpReserved)
{
	IGame.Init();

	IGame.GMFuncs->window_set_size(1280, 720);

	return 0x0;
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved)
{
	if (ul_reason_for_call == DLL_PROCESS_ATTACH) {
		CloseHandle(CreateThread(nullptr, 0, Main, hModule, 0, nullptr));
	}

	if (ul_reason_for_call == DLL_PROCESS_DETACH) {
		IGame.Destroy();
		FreeLibrary(hModule);
	}

	return TRUE;
}