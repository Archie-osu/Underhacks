#include "../Core/Core.hpp"

void CUndertale::Init()
{
	//There's room for more here, shall you wish =)
	CORE->Initialize();
	Offsets->Initialize();
}

void CUndertale::Destroy()
{
	//Let's be a clean coder =)
	delete this->GMFuncs;
	delete this->PlayerData;
	delete this->Offsets;
	delete this->Underhacks;
	delete this->CORE;
	delete this;
}

void COffsets::Initialize()
{
	//This is where all the addresses are found. If you make changes to the core of Underhacks, be sure to call this function.
	dwBase						= reinterpret_cast<DWORD>(Memory::GetModuleHandleSafe(L"UNDERTALE.exe"));
	IGame.PlayerData			= reinterpret_cast<CPlayerData*>(Memory::ReadPointerPath(dwBase + Memory::dwCommand, { 0x0, 0x0, 0x44, 0x10, 0x364 }) - 0x30 / sizeof(DWORD));
	room_goto					= Memory::FindUTPattern("\xA1\x00\x00\x00\x00\x8B\x4C\x24\x14\x50", "x????xxxxx");
	room_goto_previous			= Memory::FindUTPattern("\xE8\x00\x00\x00\x00\x8B\x0D\x00\x00\x00\x00\x3B\xC8\x75\x1A", "x????xx????xxxx") - 0x3F240;
	room_goto_next				= room_goto_previous + 0x50;
	room_restart				= Memory::FindUTPattern("\xA1\x00\x00\x00\x00\x50\xA3\x00\x00\x00\x00", "x????xx????");
	audio_stop_all				= Memory::FindUTPattern("\x80\x3D\x00\x00\x00\x00\x00\x75\x08\x6A\x00", "xx?????xxxx");
	window_set_fullscreen		= room_goto - 0x778B0;
	window_set_size				= window_set_fullscreen - 0x3EC10;
}

void CCORE::Initialize()
{
	//This is the CORE of the Core. Confusing, right? Well, simply said, this is where all the key functions reside.
	//Things like Hooks and things needed for Underhacks to function as it does.
	
	if (DirectX::GetDirectDevice(pDevice, sizeof(pDevice)))
		oEndScene = (tEndScene)TrampHook::Trampoline((char*)pDevice[42], (char*)Hooks::hkEndScene, 7);

	windowProc = (WNDPROC)(SetWindowLongW(FindWindowA(0, "UNDERTALE"), GWLP_WNDPROC, (LONG_PTR)(&Hooks::hkWndProc)));
}