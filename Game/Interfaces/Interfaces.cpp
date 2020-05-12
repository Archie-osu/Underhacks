#include "Interfaces.hpp"

void CUndertale::Init()
{
	//There's room for more here, shall you wish =)
	Offsets.Initialize();
}

void CUndertale::Destroy()
{
	//Let's be a clean coder =)
	delete this->GMFuncs;
	delete this->PlayerData;
}

void COffsets::Initialize()
{
	//This is where all the addresses are found. If you make changes to the core of Underhacks, be sure to call this function.
	dwBase = reinterpret_cast<DWORD>(Memory::GetModuleHandleSafe(L"UNDERTALE.exe"));

	room_goto						= Memory::FindUTPattern("\xA1\x00\x00\x00\x00\x8B\x4C\x24\x14\x50", "x????xxxxx");
	room_goto_previous		= Memory::FindUTPattern("\xE8\x00\x00\x00\x00\x8B\x0D\x00\x00\x00\x00\x3B\xC8\x75\x1A", "x????xx????xxxx") - 0x3F240;
	room_goto_next				= room_goto_previous + 0x50;
	room_restart					= Memory::FindUTPattern("\xA1\x00\x00\x00\x00\x50\xA3\x00\x00\x00\x00", "x????xx????");
	audio_stop_all					= Memory::FindUTPattern("\x80\x3D\x00\x00\x00\x00\x00\x75\x08\x6A\x00", "xx?????xxxx");
	window_set_fullscreen	= room_goto - 0x778B0;
	window_set_size				= window_set_fullscreen - 0x3EC10;
}