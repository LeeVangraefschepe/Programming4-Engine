#include "SceneManager.h"
#include "Scene.h"

dae::Scene* dae::SceneManager::GetActiveScene()
{
	return m_activeScene.get();
}

void dae::SceneManager::Update()
{
	if (!m_activeScene) {return;}
	m_activeScene->Update();
}

void dae::SceneManager::Render()
{
	if (!m_activeScene) { return; }
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
