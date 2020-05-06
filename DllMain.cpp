#include "SDK.hpp"
#include "Hooks.hpp"

DWORD WINAPI Init(HMODULE hModule)
{
	nHooks::Initialize();
	gVars::Initialize();

	return 0;
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved)
{
	if (ul_reason_for_call == DLL_PROCESS_ATTACH)
		CloseHandle(CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)Init, hModule, 0, nullptr));
	if (ul_reason_for_call == DLL_PROCESS_DETACH)
		FreeLibrary(hModule);

	return TRUE;
}