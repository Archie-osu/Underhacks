#pragma once
#include "../Core/Core.hpp"
#include "ImGui/imgui.h"

namespace nMenu
{
	enum MenuTabs_t
	{
		TAB_PLAYER,
		TAB_DEBUG
	};

	void Start(LPDIRECT3DDEVICE9 pDevice);
	void DrawGraphics(ImFont* pFont);
	void SetStyle();

	inline bool bInitializedWnd		= false; //Only used in the menu for initializing the window and graphics.
	inline bool bInitializedDX9		= false;
	inline bool bMenuOpen			= true; //Used to convey if the menu should be drawn.
	inline int	nCurrentTab			= 0;
	const ImVec2 vMenuSize = ImVec2((float)350, (float)300);
	constexpr const char* cszMenuName = "Sanshacks v1.3";
	
	static ImGuiWindowFlags MenuWindowFlags = (ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse
		| ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoScrollbar);
}