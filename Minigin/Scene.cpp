#include "Scene.h"

using namespace dae;

unsigned int Scene::m_idCounter = 0;

Scene::Scene(const std::string& name) : m_name(name)
{
}

Scene::~Scene()
{
}

void Scene::Add(GameObject* object)
{
	object->SetParent(GetRootObject(), false);
}

void Scene::Remove(GameObject* object)
{
	object->Destroy();
}

void Scene::RemoveAll()
{
	m_rootObject.reset();
	m_rootObject = nullptr;
}

GameObject* Scene::GetRootObject()
{
	return m_rootObject.get();
}

void Scene::Update()
{
	m_rootObject->Update();
}

void Scene::Render() const
{
	m_rootObject->Render();
}