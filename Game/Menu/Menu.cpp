#include "Menu.hpp"

#include "ImGui/imgui_impl_dx9.h"
#include "ImGui/imgui_impl_win32.h"

//THIS IS A DEVELOPMENT PREVIEW
//NOT ALL FEATURES ARE IMPLEMENTED!

void nMenu::SetStyle()
{
	if (!bInitializedWnd) {
		ImGui::SetWindowPos(ImVec2(10, 10));
		ImGui::SetWindowSize(vMenuSize);

		ImGuiStyle& Style = ImGui::GetStyle();
		Style.FrameBorderSize = 1.0f;
		Style.WindowPadding = ImVec2(7.0f, 4.0f);
		Style.FramePadding = ImVec2(5.0f, 2.0f);
		Style.ItemSpacing = ImVec2(8.0f, 6.0f);
		Style.ItemInnerSpacing = ImVec2(4.0f, 4.0f);
		Style.WindowTitleAlign = ImVec2(0.5f, 0.5f);
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

		bInitializedWnd = true;
	}
}

void nMenu::DrawGraphics(ImFont* pFont)
{
	if (ImGui::Begin(cszMenuName, nullptr, MenuWindowFlags))
	{
		SetStyle();

		ImGui::PushFont(pFont);

		if (ImGui::BeginMenuBar())
		{
			if (ImGui::MenuItem("Game", "0", false))
				nCurrentTab = TAB_PLAYER;

			if (ImGui::MenuItem("Debug", "0", false))
				nCurrentTab = TAB_DEBUG;

			ImGui::EndMenuBar();
		}

		switch (nCurrentTab)
		{
		case TAB_PLAYER:
			ImGui::SliderDouble("HP", &IGame.PlayerData->m_nHealth, 0, IGame.Underhacks->GetMaxHP(), "%.0f");
			ImGui::SliderDouble("Max HP", &IGame.PlayerData->m_nMaxHealth, 0, IGame.Underhacks->GetMaxHP(), "%.0f");
			ImGui::SliderDouble("LOVE", &IGame.PlayerData->m_nLOVE, 1, 20, "%.0f");
			break;
		case TAB_DEBUG:
			break;
		}

		ImGui::PopFont();
		ImGui::End();
	}
	
}

void nMenu::Start(LPDIRECT3DDEVICE9 pDevice)
{
	ImFont* g_pFont = nullptr;
	if (!bInitializedDX9)
	{
		ImGui::CreateContext();
		ImGui_ImplWin32_Init(FindWindowA(0, "UNDERTALE"));
		ImGui_ImplDX9_Init(pDevice);

		ImGuiIO& curIO = ImGui::GetIO();
		g_pFont = curIO.Fonts->AddFontFromFileTTF("C:\\Windows\\Fonts\\comic.ttf", 18.0f);

		bInitializedDX9 = true;
	}

	if (GetAsyncKeyState(VK_INSERT) & 1)
		bMenuOpen = !bMenuOpen;

	if (!bMenuOpen)
		return; //Don't draw anything if the Menu's not open.

	ImGui_ImplDX9_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	DrawGraphics(g_pFont);

	ImGui::EndFrame();
	ImGui::Render();
	ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());
}
