#pragma once
#include "SDK.hpp"
#include "imgui.h"
#include "imgui_impl_dx9.h"
#include "imgui_impl_win32.h"

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

enum Tabs_t
{
	TAB_INFO,
	TAB_PLAYER,
	TAB_WORLD
};

namespace nMenu
{
	extern const char* szRooms[];
	inline int nRoomToWarp = 0;


	inline bool bInitializedGraphics = false;
	inline bool bInitializedWindow = false;
	inline bool bOpen = true;

	static ImVec2 vMenuSize = ImVec2((float)350, (float)300);
	static const char* szMenuName = "Underhacks - Main Window";
	static ImGuiWindowFlags MenuWindowFlags = (ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse
		| ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoScrollbar);

	static int nCurrentTab = TAB_INFO;

	void DrawMenu();
	void Start(LPDIRECT3DDEVICE9 pDevice);
}