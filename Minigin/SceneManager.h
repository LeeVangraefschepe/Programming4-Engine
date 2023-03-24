#pragma once
#include <vector>
#include <string>
#include <memory>
#include "Singleton.h"

namespace dae
{
	class Scene;
	class SceneManager final : public Singleton<SceneManager>
	{
	public:
		Scene& CreateScene(const std::string& name);

		void Update();
		void Render();
		void RemoveAllScenes();

		void SetDimensions(int width, int height) { m_screenWidth = width; m_screenHeight = height; }
		int GetWidth() const { return m_screenWidth; }
		int GetHeight() const { return m_screenHeight; }
	private:
		friend class Singleton<SceneManager>;
		SceneManager() = default;
		std::vector<std::shared_ptr<Scene>> m_scenes;

		int m_screenWidth{};
		int m_screenHeight{};
	};
}
