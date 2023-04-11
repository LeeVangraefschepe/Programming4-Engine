#pragma once
#include <vector>
#include <string>
#include <memory>
#include "Singleton.h"
#include "Scene.h"

namespace dae
{
	class Scene;
	class SceneManager final : public Singleton<SceneManager>
	{
	public:
		void SetActiveScene(Scene* scene);
		Scene* GetActiveScene();

		void Update();
		void Render();
		void RemoveAllScenes();

		void SetDimensions(int width, int height) { m_screenWidth = width; m_screenHeight = height; }
		int GetWidth() const { return m_screenWidth; }
		int GetHeight() const { return m_screenHeight; }
	private:
		friend class Singleton<SceneManager>;
		SceneManager() = default;

		std::unique_ptr<Scene> m_activeScene;

		int m_screenWidth{};
		int m_screenHeight{};
	};
}
