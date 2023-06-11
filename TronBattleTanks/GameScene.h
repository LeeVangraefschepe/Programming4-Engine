#pragma once
#include "vector"
namespace dae
{
	class GameObject;
	class GameScene final
	{
	public:
		GameScene() = delete;
		static void Load();
	private:
		static void LoadSinglePlayer(std::vector<GameObject*>& players);
		static void LoadVersus(std::vector<GameObject*>& players);
		static void LoadCoop(std::vector<GameObject*>& players);
	};
}