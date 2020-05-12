#include "Game/SDK/SDK.hpp"
#include "Game/Interfaces/Interfaces.hpp"
#include <Windows.h>

DWORD WINAPI Main(LPVOID lpReserved)
{
	IGame.Init();

	IGame.GMFuncs->window_set_size(1280, 720); //Crash due to a nullptr exception.


	return 0x0;
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved)
{
	if (ul_reason_for_call == DLL_PROCESS_ATTACH) {
		MessageBoxA(0, "Injection Status: DLL_PROCESS_ATTACH", "Underhacks v1.3 Dev Preview 2", MB_OK | MB_ICONINFORMATION);
		CloseHandle(CreateThread(nullptr, 0, Main, hModule, 0, nullptr));
	}

	if (ul_reason_for_call == DLL_PROCESS_DETACH) {
		IGame.Destroy();
		FreeLibraryAndExitThread(hModule, 0);
	}

	return TRUE;
}