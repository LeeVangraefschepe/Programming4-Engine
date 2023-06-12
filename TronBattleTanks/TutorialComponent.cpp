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
		ImGui::Text("CONTROLLER INPUT");
		ImGui::Text("DPAD: Move");
		ImGui::Text("South button: Shoot");
		ImGui::Text("A: Confirm");
		ImGui::Text("DPAD: NAME");

		ImGui::Text("\n\n\nKEYBOARD INPUT");
		ImGui::Text("WASD: Move");
		ImGui::Text("Space bar: Shoot");
		ImGui::Text("A: Confirm");
		ImGui::Text("ARROWS: NAME");
	}
	ImGui::End();
}
