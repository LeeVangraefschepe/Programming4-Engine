#include "SceneManager.h"
#include "Scene.h"

dae::Scene* dae::SceneManager::GetActiveScene()
{
	if (m_tempScene)
	{
		return m_tempScene;
	}
	return m_activeScene.get();
}

void dae::SceneManager::Update()
{
	if (m_tempScene)
	{
		m_activeScene = std::unique_ptr<Scene>(m_tempScene);
		m_tempScene = nullptr;
	}
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
	m_tempScene = scene;
}
