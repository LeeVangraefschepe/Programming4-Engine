#include "SceneManager.h"
#include "Scene.h"

dae::Scene* dae::SceneManager::GetActiveScene()
{
	return m_activeScene;
}

void dae::SceneManager::Update()
{
	m_activeScene->Update();
}

void dae::SceneManager::Render()
{
	m_activeScene->Render();
}

void dae::SceneManager::RemoveAllScenes()
{
	m_scenes.clear();
}

dae::Scene* dae::SceneManager::CreateScene(const std::string& name)
{
	const auto& scene = std::shared_ptr<Scene>(new Scene(name));
	m_scenes.push_back(scene);
	return scene.get();
}

void dae::SceneManager::DeleteScene(Scene* scene)
{
	for (auto it = m_scenes.begin(); it != m_scenes.end(); ++it)
	{
		if (it->get() == scene)
		{
			m_scenes.erase(it);
			return;
		}
	}
}

void dae::SceneManager::SetActiveScene(Scene* scene)
{
	m_activeScene = scene;
}
