#include "TutorialComponent.h"
#include "imgui.h"

dae::TutorialComponent::TutorialComponent(GameObject* pGameObject) : BaseComponent(pGameObject)
{

}

void dae::TutorialComponent::Render()
{
	ImGui::SetNextWindowSize(ImVec2(200, 500));
	if (ImGui::Begin("How to play"))
	{
		ImGui::Text("GOAL");
		ImGui::Text("Kill the other player.\nWhen you have 500+ score\nyou will unlock an\nachievement.");

		ImGui::Text("\n\n\nCONTROLLER INPUT (red)");
		ImGui::Text("DPAD: Move");
		ImGui::Text("South button: Shoot");

		ImGui::Text("\n\n\nKEYBOARD INPUT (green)");
		ImGui::Text("WASD: Move");
		ImGui::Text("Space bar: Shoot");
	}
	ImGui::End();
}
