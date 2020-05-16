#include "Menu.hpp"

#include <string>

#include "ImGui/imgui_impl_dx9.h"
#include "ImGui/imgui_impl_win32.h"

void nMenu::SetStyleDefault()
{
	if (!bInitializedWnd)
	{
		ImGui::SetWindowPos(ImVec2(10, 10));
		ImGui::SetWindowSize(vMenuSize);
		bInitializedWnd = true;
	}

	ImGuiStyle& Style = ImGui::GetStyle();
	Style.FrameBorderSize = 1.0f;
	Style.WindowPadding = ImVec2(7.0f, 4.0f);
	Style.FramePadding = ImVec2(5.0f, 2.0f);
	Style.ItemSpacing = ImVec2(8.0f, 6.0f);
	Style.ItemInnerSpacing = ImVec2(4.0f, 4.0f);
	Style.WindowTitleAlign = ImVec2(0.02f, 0.5f);
	Style.ButtonTextAlign = ImVec2(0.5f, 0.5f);
	Style.WindowBorderSize = 1.0f;
	Style.WindowRounding = 6.0f;
	Style.ChildRounding = 0.0f;
	Style.FrameRounding = 0.0f;
	Style.GrabRounding = 0.0f;
	Style.PopupRounding = 2.0f;
	Style.TabRounding = 5.0f;
	Style.GrabMinSize = 7.0f;

	ImVec4* colors = ImGui::GetStyle().Colors;
	colors[ImGuiCol_Text] = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
	colors[ImGuiCol_TextDisabled] = ImVec4(0.50f, 0.50f, 0.50f, 1.00f);
	colors[ImGuiCol_WindowBg] = ImVec4(0.06f, 0.06f, 0.06f, 0.94f);
	colors[ImGuiCol_ChildBg] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
	colors[ImGuiCol_PopupBg] = ImVec4(0.08f, 0.08f, 0.08f, 0.94f);
	colors[ImGuiCol_Border] = ImVec4(1.00f, 0.00f, 1.00f, 0.50f);
	colors[ImGuiCol_BorderShadow] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
	colors[ImGuiCol_FrameBg] = ImVec4(0.69f, 0.00f, 1.00f, 0.27f);
	colors[ImGuiCol_FrameBgHovered] = ImVec4(0.00f, 0.59f, 1.00f, 0.46f);
	colors[ImGuiCol_FrameBgActive] = ImVec4(0.13f, 0.59f, 1.00f, 0.67f);
	colors[ImGuiCol_TitleBg] = ImVec4(0.00f, 0.00f, 0.00f, 0.82f);
	colors[ImGuiCol_TitleBgActive] = ImVec4(0.27f, 0.00f, 1.00f, 0.99f);
	colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.00f, 0.00f, 0.00f, 0.51f);
	colors[ImGuiCol_MenuBarBg] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
	colors[ImGuiCol_ScrollbarBg] = ImVec4(0.02f, 0.02f, 0.02f, 0.53f);
	colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.31f, 0.31f, 0.31f, 1.00f);
	colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.41f, 0.41f, 0.41f, 1.00f);
	colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.51f, 0.51f, 0.51f, 1.00f);
	colors[ImGuiCol_CheckMark] = ImVec4(0.26f, 0.78f, 1.00f, 1.00f);
	colors[ImGuiCol_SliderGrab] = ImVec4(0.24f, 0.52f, 0.88f, 1.00f);
	colors[ImGuiCol_SliderGrabActive] = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
	colors[ImGuiCol_Button] = ImVec4(0.26f, 0.59f, 0.98f, 0.40f);
	colors[ImGuiCol_ButtonHovered] = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
	colors[ImGuiCol_ButtonActive] = ImVec4(0.06f, 0.53f, 0.98f, 1.00f);
	colors[ImGuiCol_Header] = ImVec4(0.26f, 0.59f, 0.98f, 0.31f);
	colors[ImGuiCol_HeaderHovered] = ImVec4(0.26f, 0.59f, 0.98f, 0.80f);
	colors[ImGuiCol_HeaderActive] = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
	colors[ImGuiCol_Separator] = ImVec4(0.43f, 0.43f, 0.50f, 0.50f);
	colors[ImGuiCol_SeparatorHovered] = ImVec4(0.10f, 0.40f, 0.75f, 0.78f);
	colors[ImGuiCol_SeparatorActive] = ImVec4(0.10f, 0.40f, 0.75f, 1.00f);
	colors[ImGuiCol_ResizeGrip] = ImVec4(0.26f, 0.59f, 0.98f, 0.25f);
	colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.26f, 0.59f, 0.98f, 0.67f);
	colors[ImGuiCol_ResizeGripActive] = ImVec4(0.26f, 0.59f, 0.98f, 0.95f);
	colors[ImGuiCol_Tab] = ImVec4(0.18f, 0.35f, 0.58f, 0.86f);
	colors[ImGuiCol_TabHovered] = ImVec4(0.26f, 0.59f, 0.98f, 0.80f);
	colors[ImGuiCol_TabActive] = ImVec4(0.20f, 0.41f, 0.68f, 1.00f);
	colors[ImGuiCol_TabUnfocused] = ImVec4(0.07f, 0.10f, 0.15f, 0.97f);
	colors[ImGuiCol_TabUnfocusedActive] = ImVec4(0.14f, 0.26f, 0.42f, 1.00f);
	colors[ImGuiCol_PlotLines] = ImVec4(0.61f, 0.61f, 0.61f, 1.00f);
	colors[ImGuiCol_PlotLinesHovered] = ImVec4(1.00f, 0.43f, 0.35f, 1.00f);
	colors[ImGuiCol_PlotHistogram] = ImVec4(0.90f, 0.70f, 0.00f, 1.00f);
	colors[ImGuiCol_PlotHistogramHovered] = ImVec4(1.00f, 0.60f, 0.00f, 1.00f);
	colors[ImGuiCol_TextSelectedBg] = ImVec4(0.26f, 0.59f, 0.98f, 0.35f);
	colors[ImGuiCol_DragDropTarget] = ImVec4(1.00f, 1.00f, 0.00f, 0.90f);
	colors[ImGuiCol_NavHighlight] = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
	colors[ImGuiCol_NavWindowingHighlight] = ImVec4(1.00f, 1.00f, 1.00f, 0.70f);
	colors[ImGuiCol_NavWindowingDimBg] = ImVec4(0.80f, 0.80f, 0.80f, 0.20f);
	colors[ImGuiCol_ModalWindowDimBg] = ImVec4(0.80f, 0.80f, 0.80f, 0.35f);
}

void nMenu::SetStyleSans()
{
	ImVec4* colors = ImGui::GetStyle().Colors;
	colors[ImGuiCol_Text] = ImVec4(0.00f, 0.00f, 0.00f, 1.00f);
	colors[ImGuiCol_TextDisabled] = ImVec4(0.60f, 0.60f, 0.60f, 1.00f);
	colors[ImGuiCol_WindowBg] = ImVec4(1.00f, 1.00f, 1.00f, 0.90f);
	colors[ImGuiCol_ChildBg] = ImVec4(0.00f, 0.00f, 1.00f, 0.00f);
	colors[ImGuiCol_PopupBg] = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
	colors[ImGuiCol_Border] = ImVec4(0.50f, 0.50f, 0.50f, 0.78f);
	colors[ImGuiCol_BorderShadow] = ImVec4(0.00f, 0.00f, 0.00f, 0.29f);
	colors[ImGuiCol_FrameBg] = ImVec4(0.43f, 0.43f, 0.43f, 0.20f);
	colors[ImGuiCol_FrameBgHovered] = ImVec4(0.47f, 0.47f, 0.69f, 0.40f);
	colors[ImGuiCol_FrameBgActive] = ImVec4(0.42f, 0.41f, 0.64f, 0.68f);
	colors[ImGuiCol_TitleBg] = ImVec4(0.00f, 0.47f, 1.00f, 0.55f);
	colors[ImGuiCol_TitleBgActive] = ImVec4(0.00f, 0.85f, 0.97f, 0.86f);
	colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.40f, 0.40f, 0.80f, 0.20f);
	colors[ImGuiCol_MenuBarBg] = ImVec4(0.16f, 0.48f, 0.88f, 1.00f);
	colors[ImGuiCol_ScrollbarBg] = ImVec4(0.20f, 0.25f, 0.30f, 0.60f);
	colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.40f, 0.40f, 0.80f, 0.30f);
	colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.40f, 0.40f, 0.80f, 0.40f);
	colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.41f, 0.39f, 0.80f, 0.60f);
	colors[ImGuiCol_CheckMark] = ImVec4(0.97f, 0.00f, 0.00f, 1.00f);
	colors[ImGuiCol_SliderGrab] = ImVec4(1.00f, 0.00f, 0.00f, 1.00f);
	colors[ImGuiCol_SliderGrabActive] = ImVec4(1.00f, 0.00f, 0.00f, 1.00f);
	colors[ImGuiCol_Button] = ImVec4(0.00f, 0.67f, 1.00f, 0.34f);
	colors[ImGuiCol_ButtonHovered] = ImVec4(0.02f, 0.24f, 0.86f, 0.79f);
	colors[ImGuiCol_ButtonActive] = ImVec4(0.46f, 0.54f, 0.80f, 1.00f);
	colors[ImGuiCol_Header] = ImVec4(0.40f, 0.40f, 0.90f, 0.45f);
	colors[ImGuiCol_HeaderHovered] = ImVec4(0.45f, 0.45f, 0.90f, 0.80f);
	colors[ImGuiCol_HeaderActive] = ImVec4(0.53f, 0.53f, 0.87f, 0.80f);
	colors[ImGuiCol_Separator] = ImVec4(0.50f, 0.50f, 0.50f, 0.71f);
	colors[ImGuiCol_SeparatorHovered] = ImVec4(0.60f, 0.60f, 0.70f, 1.00f);
	colors[ImGuiCol_SeparatorActive] = ImVec4(0.70f, 0.70f, 0.90f, 1.00f);
	colors[ImGuiCol_ResizeGrip] = ImVec4(1.00f, 1.00f, 1.00f, 0.16f);
	colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.78f, 0.82f, 1.00f, 0.60f);
	colors[ImGuiCol_ResizeGripActive] = ImVec4(0.78f, 0.82f, 1.00f, 0.90f);
	colors[ImGuiCol_Tab] = ImVec4(0.34f, 0.34f, 0.68f, 0.27f);
	colors[ImGuiCol_TabHovered] = ImVec4(0.45f, 0.45f, 0.90f, 0.80f);
	colors[ImGuiCol_TabActive] = ImVec4(0.40f, 0.40f, 0.73f, 0.84f);
	colors[ImGuiCol_TabUnfocused] = ImVec4(0.28f, 0.28f, 0.57f, 0.82f);
	colors[ImGuiCol_TabUnfocusedActive] = ImVec4(0.35f, 0.35f, 0.65f, 0.84f);
	colors[ImGuiCol_PlotLines] = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
	colors[ImGuiCol_PlotLinesHovered] = ImVec4(0.90f, 0.70f, 0.00f, 1.00f);
	colors[ImGuiCol_PlotHistogram] = ImVec4(0.90f, 0.70f, 0.00f, 1.00f);
	colors[ImGuiCol_PlotHistogramHovered] = ImVec4(1.00f, 0.60f, 0.00f, 1.00f);
	colors[ImGuiCol_TextSelectedBg] = ImVec4(0.00f, 0.00f, 1.00f, 0.35f);
	colors[ImGuiCol_DragDropTarget] = ImVec4(1.00f, 1.00f, 0.00f, 0.90f);
	colors[ImGuiCol_NavHighlight] = ImVec4(0.45f, 0.45f, 0.90f, 0.80f);
	colors[ImGuiCol_NavWindowingHighlight] = ImVec4(1.00f, 1.00f, 1.00f, 0.70f);
	colors[ImGuiCol_NavWindowingDimBg] = ImVec4(0.80f, 0.80f, 0.80f, 0.20f);
	colors[ImGuiCol_ModalWindowDimBg] = ImVec4(0.20f, 0.20f, 0.20f, 0.35f);
}

void nMenu::SetStyle()
{
	ImVec4* colors = ImGui::GetStyle().Colors;
	colors[ImGuiCol_Text] = ImVec4(0.53f, 0.00f, 0.00f, 1.00f);
	colors[ImGuiCol_TextDisabled] = ImVec4(0.50f, 0.50f, 0.50f, 1.00f);
	colors[ImGuiCol_WindowBg] = ImVec4(0.06f, 0.06f, 0.06f, 1.00f);
	colors[ImGuiCol_ChildBg] = ImVec4(0.00f, 0.00f, 0.00f, 1.00f);
	colors[ImGuiCol_PopupBg] = ImVec4(0.08f, 0.08f, 0.08f, 0.94f);
	colors[ImGuiCol_Border] = ImVec4(1.00f, 0.00f, 0.00f, 0.43f);
	colors[ImGuiCol_BorderShadow] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
	colors[ImGuiCol_FrameBg] = ImVec4(0.10f, 0.10f, 0.10f, 0.54f);
	colors[ImGuiCol_FrameBgHovered] = ImVec4(0.34f, 0.07f, 0.07f, 0.40f);
	colors[ImGuiCol_FrameBgActive] = ImVec4(0.47f, 0.03f, 0.03f, 0.47f);
	colors[ImGuiCol_TitleBg] = ImVec4(0.00f, 0.00f, 0.00f, 1.00f);
	colors[ImGuiCol_TitleBgActive] = ImVec4(0.12f, 0.00f, 0.00f, 1.00f);
	colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.00f, 0.00f, 0.00f, 0.51f);
	colors[ImGuiCol_MenuBarBg] = ImVec4(0.08f, 0.08f, 0.08f, 1.00f);
	colors[ImGuiCol_ScrollbarBg] = ImVec4(0.02f, 0.02f, 0.02f, 0.53f);
	colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.31f, 0.31f, 0.31f, 1.00f);
	colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.41f, 0.41f, 0.41f, 1.00f);
	colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.51f, 0.51f, 0.51f, 1.00f);
	colors[ImGuiCol_CheckMark] = ImVec4(0.99f, 0.00f, 0.00f, 1.00f);
	colors[ImGuiCol_SliderGrab] = ImVec4(0.43f, 0.00f, 0.00f, 1.00f);
	colors[ImGuiCol_SliderGrabActive] = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
	colors[ImGuiCol_Button] = ImVec4(1.00f, 1.00f, 1.00f, 0.06f);
	colors[ImGuiCol_ButtonHovered] = ImVec4(1.00f, 0.27f, 0.27f, 0.16f);
	colors[ImGuiCol_ButtonActive] = ImVec4(1.00f, 0.27f, 0.27f, 0.12f);
	colors[ImGuiCol_Header] = ImVec4(0.26f, 0.59f, 0.98f, 0.45f);
	colors[ImGuiCol_HeaderHovered] = ImVec4(0.21f, 0.05f, 0.05f, 1.00f);
	colors[ImGuiCol_HeaderActive] = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
	colors[ImGuiCol_Separator] = ImVec4(0.43f, 0.43f, 0.50f, 0.50f);
	colors[ImGuiCol_SeparatorHovered] = ImVec4(0.10f, 0.40f, 0.75f, 0.85f);
	colors[ImGuiCol_SeparatorActive] = ImVec4(0.10f, 0.40f, 0.75f, 1.00f);
	colors[ImGuiCol_ResizeGrip] = ImVec4(0.26f, 0.59f, 0.98f, 0.25f);
	colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.26f, 0.59f, 0.98f, 0.67f);
	colors[ImGuiCol_ResizeGripActive] = ImVec4(0.26f, 0.59f, 0.98f, 0.95f);
	colors[ImGuiCol_Tab] = ImVec4(0.18f, 0.35f, 0.58f, 0.00f);
	colors[ImGuiCol_TabHovered] = ImVec4(0.17f, 0.07f, 0.07f, 1.00f);
	colors[ImGuiCol_TabActive] = ImVec4(1.00f, 0.04f, 0.04f, 0.19f);
	colors[ImGuiCol_TabUnfocused] = ImVec4(0.07f, 0.10f, 0.15f, 0.97f);
	colors[ImGuiCol_TabUnfocusedActive] = ImVec4(0.14f, 0.26f, 0.42f, 1.00f);
	colors[ImGuiCol_PlotLines] = ImVec4(0.61f, 0.61f, 0.61f, 1.00f);
	colors[ImGuiCol_PlotLinesHovered] = ImVec4(1.00f, 0.43f, 0.35f, 1.00f);
	colors[ImGuiCol_PlotHistogram] = ImVec4(0.90f, 0.70f, 0.00f, 1.00f);
	colors[ImGuiCol_PlotHistogramHovered] = ImVec4(1.00f, 0.60f, 0.00f, 1.00f);
	colors[ImGuiCol_TextSelectedBg] = ImVec4(0.26f, 0.59f, 0.98f, 0.35f);
	colors[ImGuiCol_DragDropTarget] = ImVec4(1.00f, 1.00f, 0.00f, 0.90f);
	colors[ImGuiCol_NavHighlight] = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
	colors[ImGuiCol_NavWindowingHighlight] = ImVec4(1.00f, 1.00f, 1.00f, 0.70f);
	colors[ImGuiCol_NavWindowingDimBg] = ImVec4(0.80f, 0.80f, 0.80f, 0.20f);
	colors[ImGuiCol_ModalWindowDimBg] = ImVec4(0.80f, 0.80f, 0.80f, 0.35f);
}

DWORD nMenu::GetMenuKey()
{
	if (!nMenuKey) //If nMenuKey is zero
		return VK_INSERT;
	
	return VK_TAB; //Else do this..
}

void nMenu::DrawGraphics()
{
	switch (nTheme)
	{
	case THEME_NORMAL:
		ImGui::PushFont(fontDefault);
		break;
	case THEME_SANS:
		ImGui::PushFont(fontSans);
		break;
	default:
		ImGui::PushFont(fontChara);
		break;
	}


	if (ImGui::Begin(cszMenuName, nullptr, MenuWindowFlags))
	{
		switch (nTheme)
		{
		case THEME_NORMAL:
			SetStyleDefault();
			break;
		case THEME_SANS:
			SetStyleSans();
			break;
		default:
			SetStyle();
			break;
		}

		if (ImGui::BeginMenuBar())
		{
			if (ImGui::MenuItem("Game", "0", false))
				nCurrentTab = TAB_PLAYER;

			if (ImGui::MenuItem("Tool", "0", false))
				nCurrentTab = TAB_TOOL;

			ImGui::EndMenuBar();
		}

		switch (nCurrentTab)
		{
		case TAB_PLAYER:
			ImGui::SliderDouble("HP", &IGame.PlayerData->m_nHealth, 0, IGame.Underhacks->GetMaxHP(), "%.0f");
			ImGui::SliderDouble("Max HP", &IGame.PlayerData->m_nMaxHealth, 0, IGame.Underhacks->GetMaxHP(), "%.0f");
			ImGui::SliderDouble("LOVE", &IGame.PlayerData->m_nLOVE, 1, 20, "%.0f");
			ImGui::SliderDouble("EXP", &IGame.PlayerData->m_nEXP, 0, 50000, "%.0f");
			ImGui::SliderDouble("Gold", &IGame.PlayerData->m_nGold, 0, 10000, "%.0f");
			ImGui::Checkbox("Debug Mode", &IGame.Underhacks->bDebugMode);

			ImGui::Separator();

			ImGui::PushItemWidth(vMenuSize.x / 6);
			ImGui::InputInt("Window Width", &IGame.Underhacks->vGameProperties.iWidth, 0, 0);

			ImGui::SameLine();

			ImGui::InputInt("Window Height", &IGame.Underhacks->vGameProperties.iHeight, 0, 0);
			ImGui::Checkbox("Fullscreen", &IGame.Underhacks->vGameProperties.bFullscreen);

			ImGui::SameLine();

			if (ImGui::Button("Apply Properties", ImVec2(150, 23)))
			{
				IGame.GMFuncs->window_set_size(IGame.Underhacks->vGameProperties.iWidth, IGame.Underhacks->vGameProperties.iHeight);
				IGame.GMFuncs->window_set_fullscreen(IGame.Underhacks->vGameProperties.bFullscreen);
			}

			ImGui::Separator();

			ImGui::PopItemWidth();

			ImGui::Combo("Desired room", &IGame.Underhacks->nDesiredRoom, cszRooms, 336);

			if (ImGui::Button("Teleport", ImVec2(100, 23))) {
				IGame.GMFuncs->audio_stop_all();
				IGame.GMFuncs->room_goto(IGame.Underhacks->nDesiredRoom);
			}

			ImGui::SameLine();

			if (ImGui::Button("Next Room", ImVec2(100, 23))) {
				IGame.GMFuncs->room_goto_next();
			}

			ImGui::SameLine();

			if (ImGui::Button("Previous Room", ImVec2(125, 23))) {
				IGame.GMFuncs->room_goto_previous();
			}

			break;
		case TAB_TOOL:
			ImGui::Text("Version: 1.3.2");
			ImGui::Text("Authors: Pin & elite_pleb");
			ImGui::Text("Special thanks to: Grossleymoo, Jockeholm, colinator27");
			ImGui::Text("for supporting the development and helping in general.");
			ImGui::Separator();
			ImGui::Text(std::string("Current Room: " + IGame.Underhacks->GetRoomName(*IGame.Offsets->room_number)).c_str());

			ImGui::Combo("Theme", &nTheme, cszThemes, IM_ARRAYSIZE(cszThemes));
			ImGui::Combo("Menu Key", &nMenuKey, cszMenuKeys, IM_ARRAYSIZE(cszMenuKeys));
		}

		ImGui::PopFont();
		ImGui::End();
	}
	
}

void nMenu::Start(LPDIRECT3DDEVICE9 pDevice)
{
	if (!bInitializedDX9)
	{
		ImGui::CreateContext();
		ImGui_ImplWin32_Init(Memory::Windows::GetWindowByName(L"UNDERTALE.exe"));
		ImGui_ImplDX9_Init(pDevice);

		ImGuiIO& curIO = ImGui::GetIO();
		fontSans = curIO.Fonts->AddFontFromFileTTF("C:\\Windows\\Fonts\\comic.ttf", 20.0f);
		fontDefault = curIO.Fonts->AddFontFromFileTTF("C:\\Windows\\Fonts\\Bahnschrift.ttf", 18.0f);
		fontChara = curIO.Fonts->AddFontFromFileTTF("C:\\Windows\\Fonts\\times.ttf", 18.0f);

		bInitializedDX9 = true;
	}

	if (GetAsyncKeyState(GetMenuKey()) & 1)
		bMenuOpen = !bMenuOpen;

	if (!bMenuOpen)
		return; //Don't draw anything if the Menu's not open.

	ImGui_ImplDX9_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	DrawGraphics();
	IGame.Underhacks->DoubleProxy();

	ImGui::EndFrame();
	ImGui::Render();
	ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());
}
