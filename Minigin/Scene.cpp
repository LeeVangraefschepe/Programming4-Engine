#include "Scene.h"

using namespace dae;

unsigned int Scene::m_idCounter = 0;

Scene::Scene(const std::string& name) : m_name(name)
{
	m_rootObject = std::make_unique<GameObject>();
}

Scene::~Scene() = default;

void Scene::Add(GameObject* object)
{
	object->SetParent(m_rootObject.get(), false);
}

void Scene::Remove(GameObject* object)
{
	m_destroyObjects.push_back(object);
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
	for (const auto destroyObject : m_destroyObjects)
	{
		destroyObject->SetParent(nullptr, false);
	}

	m_rootObject->Update();
}

void Scene::Render() const
{
	m_rootObject->Render();
}

