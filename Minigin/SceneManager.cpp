#include "SceneManager.h"
#include "Scene.h"

dae::Scene* dae::SceneManager::GetActiveScene()
{
	return m_activeScene.get();
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
	m_activeScene.reset();
	m_activeScene = nullptr;
}

void dae::SceneManager::SetActiveScene(Scene* scene)
{
	m_activeScene = std::unique_ptr<Scene>(scene);
}
