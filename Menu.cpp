#include "Menu.hpp"
#include <string>

void nMenu::DrawMenu()
{
	if (ImGui::Begin(szMenuName, nullptr, MenuWindowFlags))
	{
		if (!bInitializedWindow) {
			ImGui::SetWindowPos(ImVec2(10, 10));
			ImGui::SetWindowSize(vMenuSize);

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

			ImGui::Text("Underhacks version: 1.1.0 dev");
			ImGui::Text(std::string("Base Pointer: " + std::string("0x") + DecToHex(gVars::dwBase)).c_str()); //This is really messy :/
			ImGui::Text(std::string("UserCmd Address: " + std::string("0x") + DecToHex(gVars::dwUserCmd)).c_str());
			ImGui::Text(std::string("Static Room: " + std::to_string(*gVars::GetRoomPointer())).c_str());
			ImGui::Text(std::string("CUserCmd Room: " + std::to_string(gVars::GetCmd()->m_nRoom)).c_str());
			ImGui::Text(std::string("mov [UNDERTALE.exe+618A0,esi]: " + DecToHex(gVars::dwChangeRoomFn)).c_str());

			if (ImGui::Button("Recalculate Addresses", ImVec2(175, 20)))
				gVars::Initialize();

			break;
		case TAB_PLAYER:
			ImGui::Text("Player");

			ImGui::NewLine();

			ImGui::SliderDouble("Health", &gVars::GetCmd()->m_nHealth, 0, gVars::GetCmd()->m_nMaxHealth, "%.0f");
			ImGui::SliderDouble("Max Health", &gVars::GetCmd()->m_nMaxHealth, gVars::GetCmd()->m_nHealth, 99.00, "%.0f");
			ImGui::SliderDouble("LOVE", &gVars::GetCmd()->m_nLOVE, 0.0, 20.0, "%.0f");
			ImGui::SliderDouble("EXP", &gVars::GetCmd()->m_nEXP, 0.0, 50000.0, "%.0f", 10.0f);

			break;
		case TAB_WORLD:
			ImGui::Text("World Tab");

			ImGui::NewLine();

			if (ImGui::Button("why tf does this not work", ImVec2(200, 20)))
				gVars::SetRoom(0x108);

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

	DrawMenu();

	ImGui::EndFrame();
	ImGui::Render();
	ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());
}


