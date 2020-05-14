#pragma once
#include "../Core/Core.hpp"
#include "ImGui/imgui.h"

namespace nMenu
{
	static const char* cszThemes[] = { "Underhacks", "sans."};
	extern const char* cszRooms[];

	enum MenuTabs_t
	{
		TAB_PLAYER,
		TAB_TOOL
	};

	enum MenuThemes_t
	{
		THEME_NORMAL,
		THEME_sans //sans
	};

	void Start(LPDIRECT3DDEVICE9 pDevice);
	void DrawGraphics();
	void SetStyleDefault();
	void SetStyleSans();
	void SetStyle();

	inline bool bInitializedWnd		= false; //Only used in the menu for initializing the window and graphics.
	inline bool bInitializedDX9		= false;
	inline bool bMenuOpen			= true; //Used to convey if the menu should be drawn.
	
	inline int	nCurrentTab			= 0; //Represents the current Menu Tab (Game -> Debug)
	inline int	nTheme				= 0; //Represents the current Theme (Underhacks -> sans. -> Genocide)

	inline ImFont* fontDefault		= nullptr; //Bahnschrift.
	inline ImFont* fontSans			= nullptr; //comic sans
	inline ImFont* fontChara		= nullptr; //Do NOT force this =)

	const ImVec2 vMenuSize = ImVec2((float)400, (float)340);
	constexpr const char* cszMenuName = "Underhacks v1.3";
	
	static ImGuiWindowFlags MenuWindowFlags = (ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse
		| ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_MenuBar);
}