#include "Menu.hpp"

void nMenu::DrawMenu()
{
	static bool bInitialized = false;

	if (!bInitializedWindow) {
		ImGui::SetWindowPos(ImVec2(10, 10));
		ImGui::SetWindowSize(vMenuSize);
		bInitializedWindow = true;
	}

	ImGui::Begin(szMenuName, nullptr, MenuWindowFlags);

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

		ImGui::Text("Info Tab");
		break;
	case TAB_PLAYER:
		ImGui::Text("Player Tab");
		break;
	case TAB_WORLD:
		ImGui::Text("World Tab");
		break;
	}
	ImGui::End();
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


