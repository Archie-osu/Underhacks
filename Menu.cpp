#include "Menu.hpp"
#include <string>

void nMenu::DrawMenu()
{
	if (ImGui::Begin(szMenuName, nullptr, MenuWindowFlags))
	{
		if (!bInitializedWindow) {
			ImGui::SetWindowPos(ImVec2(10, 10));
			ImGui::SetWindowSize(vMenuSize);

			ImGuiStyle& Style = ImGui::GetStyle();
			Style.FrameBorderSize = 1.0f;
			Style.WindowPadding = ImVec2(7.0f, 4.0f);
			Style.FramePadding = ImVec2(6.0f, 2.0f);
			Style.ItemSpacing = ImVec2(8.0f, 6.0f);
			Style.WindowTitleAlign = ImVec2(0.5f, 0.5f);
			Style.ButtonTextAlign = ImVec2(0.5f, 0.5f);
			Style.WindowBorderSize = 1.0f;
			Style.WindowRounding = 6.0f;
			Style.ChildRounding = 1.0f;
			Style.FrameRounding = 6.0f;
			Style.GrabRounding = 6.0f;
			Style.PopupRounding = 1.0f;
			Style.TabRounding = 5.0f;
			Style.GrabMinSize = 7.0f;

			ImVec4* colors = ImGui::GetStyle().Colors;
			colors[ImGuiCol_Text] = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
			colors[ImGuiCol_TextDisabled] = ImVec4(0.50f, 0.50f, 0.50f, 1.00f);
			colors[ImGuiCol_WindowBg] = ImVec4(0.00f, 0.00f, 0.00f, 0.95f);
			colors[ImGuiCol_ChildBg] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
			colors[ImGuiCol_PopupBg] = ImVec4(0.08f, 0.08f, 0.08f, 0.94f);
			colors[ImGuiCol_Border] = ImVec4(0.43f, 0.43f, 0.50f, 0.50f);
			colors[ImGuiCol_BorderShadow] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
			colors[ImGuiCol_FrameBg] = ImVec4(0.00f, 0.00f, 0.00f, 0.92f);
			colors[ImGuiCol_FrameBgHovered] = ImVec4(0.14f, 0.06f, 0.31f, 0.40f);
			colors[ImGuiCol_FrameBgActive] = ImVec4(0.40f, 0.15f, 0.49f, 0.67f);
			colors[ImGuiCol_TitleBg] = ImVec4(0.00f, 0.00f, 0.00f, 0.71f);
			colors[ImGuiCol_TitleBgActive] = ImVec4(0.52f, 0.00f, 0.00f, 1.00f);
			colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.00f, 0.00f, 0.00f, 0.51f);
			colors[ImGuiCol_MenuBarBg] = ImVec4(0.00f, 0.00f, 0.00f, 0.50f);
			colors[ImGuiCol_ScrollbarBg] = ImVec4(0.04f, 0.02f, 0.02f, 0.53f);
			colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.34f, 0.31f, 0.31f, 1.00f);
			colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.41f, 0.41f, 0.41f, 1.00f);
			colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.51f, 0.51f, 0.51f, 1.00f);
			colors[ImGuiCol_CheckMark] = ImVec4(1.00f, 0.00f, 0.00f, 1.00f);
			colors[ImGuiCol_SliderGrab] = ImVec4(0.98f, 0.00f, 0.00f, 0.71f);
			colors[ImGuiCol_SliderGrabActive] = ImVec4(1.00f, 0.00f, 0.00f, 1.00f);
			colors[ImGuiCol_Button] = ImVec4(0.71f, 0.00f, 0.00f, 0.39f);
			colors[ImGuiCol_ButtonHovered] = ImVec4(0.36f, 0.00f, 0.22f, 0.46f);
			colors[ImGuiCol_ButtonActive] = ImVec4(0.23f, 0.00f, 0.29f, 1.00f);
			colors[ImGuiCol_Header] = ImVec4(0.23f, 0.59f, 0.98f, 0.31f);
			colors[ImGuiCol_HeaderHovered] = ImVec4(0.26f, 0.00f, 0.31f, 1.00f);
			colors[ImGuiCol_HeaderActive] = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
			colors[ImGuiCol_Separator] = ImVec4(0.43f, 0.43f, 0.50f, 0.50f);
			colors[ImGuiCol_SeparatorHovered] = ImVec4(0.10f, 0.40f, 0.75f, 0.78f);
			colors[ImGuiCol_SeparatorActive] = ImVec4(0.10f, 0.40f, 0.75f, 1.00f);
			colors[ImGuiCol_ResizeGrip] = ImVec4(0.26f, 0.59f, 0.98f, 0.25f);
			colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.26f, 0.59f, 0.98f, 0.67f);
			colors[ImGuiCol_ResizeGripActive] = ImVec4(0.26f, 0.59f, 0.98f, 0.95f);
			colors[ImGuiCol_Tab] = ImVec4(0.63f, 0.00f, 0.00f, 0.86f);
			colors[ImGuiCol_TabHovered] = ImVec4(0.00f, 0.59f, 0.98f, 0.80f);
			colors[ImGuiCol_TabActive] = ImVec4(0.04f, 0.19f, 0.54f, 1.00f);
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
			colors[ImGuiCol_NavWindowingDimBg] = ImVec4(0.80f, 0.80f, 0.80f, 0.34f);
			colors[ImGuiCol_ModalWindowDimBg] = ImVec4(0.80f, 0.80f, 0.80f, 0.35f);

			bInitializedWindow = true;
		}

		if (ImGui::BeginMenuBar())
		{
			if (ImGui::MenuItem("Info", "0", false))
				nCurrentTab = TAB_INFO;
			if (ImGui::MenuItem("Player", "0", false))
				nCurrentTab = TAB_PLAYER;
			if (ImGui::MenuItem("World", "0", false))
				nCurrentTab = TAB_WORLD;

			ImGui::EndMenuBar();
		}

		switch (nCurrentTab)
		{
		case TAB_INFO:
			ImGui::Text("Info");
			
			ImGui::NewLine();

			ImGui::Text("Underhacks version: 1.2.1");
			ImGui::Text(std::string("Base Pointer: " + std::string("0x") + DecToHex(gVars::dwBase)).c_str()); //This is really messy :/
			ImGui::Text(std::string("UserCmd Address: " + std::string("0x") + DecToHex(gVars::dwUserCmd)).c_str());
			ImGui::Text(std::string("Current Room: " + std::to_string(*nFuncs::GetRoomPointer())).c_str());
			ImGui::Text(std::string("GoToRoom Function: " + DecToHex(gVars::dwRoom_GoTo)).c_str());
			ImGui::Text(std::string("global.interact: " + std::to_string(nFuncs::GetCmd()->m_Interact)).c_str());

			if (ImGui::Button("Recalculate Addresses", ImVec2(175, 20)))
				gVars::Initialize();

			break;
		case TAB_PLAYER:
			ImGui::Text("Player");

			ImGui::NewLine();

			ImGui::SliderDouble("Health", &nFuncs::GetCmd()->m_nHealth, 0, nFuncs::GetCmd()->m_nMaxHealth, "%.0f");
			ImGui::SliderDouble("Max Health", &nFuncs::GetCmd()->m_nMaxHealth, nFuncs::GetCmd()->m_nHealth, 99.00, "%.0f");
			ImGui::SliderDouble("LOVE", &nFuncs::GetCmd()->m_nLOVE, 0.0, 20.0, "%.0f");
			ImGui::SliderDouble("EXP", &nFuncs::GetCmd()->m_nEXP, 0.0, 50000.0, "%.0f", 2.0f);
			ImGui::SliderDouble("Gold", &nFuncs::GetCmd()->m_nGold, 0.0, 9999.0, "%.0f", 2.0f);

			break;
		case TAB_WORLD:
			ImGui::Text("World Tab");

			ImGui::NewLine();

			if (ImGui::Button("Previous Room", ImVec2(110, 20)))
				nFuncs::room_goto_previous();

			ImGui::SameLine();

			if (ImGui::Button("Next Room", ImVec2(75, 20)))
				nFuncs::room_goto_next();

			static const char* szTeleports[] { "Normal", "Meme" };

			ImGui::PushItemWidth(vMenuSize.x / 4);
			ImGui::Combo("Teleportation Method", &nTeleportMethod, szTeleports, IM_ARRAYSIZE(szTeleports));
			ImGui::PopItemWidth();

			ImGui::Combo("Desired room", &nRoomToWarp, szRooms, 335);

			if (ImGui::Button("Warp!", ImVec2(75, 20))) {
				if (nTeleportMethod == 0)
					nFuncs::room_goto(static_cast<DWORD>(nRoomToWarp));
				else
					nFuncs::room_goto_meme(nRoomToWarp);
			}

			ImGui::SameLine();

			if (ImGui::Button("Restart Room", ImVec2(100, 20))) {
				nFuncs::room_restart();
			}

			break;
		}
		ImGui::End();
	}
}

void nMenu::Start(LPDIRECT3DDEVICE9 pDevice)
{
	if (!bInitializedGraphics)
	{
		ImGui::CreateContext();
		ImGui_ImplWin32_Init(FindWindowA(0, "UNDERTALE"));
		ImGui_ImplDX9_Init(pDevice);

		bInitializedGraphics = true;
	}

	if (GetAsyncKeyState(VK_INSERT) & 1)
		bOpen = !bOpen;

	if (!bOpen)
		return;

	ImGui_ImplDX9_NewFrame(); 
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	if (gVars::nTeleportsLeft != 0 && nTeleportMethod == 1)
		nFuncs::room_goto_meme(gVars::nLastRequested);

	DrawMenu();

	ImGui::EndFrame();
	ImGui::Render();
	ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());
}


