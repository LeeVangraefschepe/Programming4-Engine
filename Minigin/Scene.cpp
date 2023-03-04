#include "Scene.h"
#include "GameObject.h"

using namespace dae;

unsigned int Scene::m_idCounter = 0;

Scene::Scene(const std::string& name) : m_name(name) {}

Scene::~Scene() = default;

void Scene::Add(std::shared_ptr<GameObject> object)
{
	m_objects.emplace_back(std::move(object));
}

void Scene::Remove(std::shared_ptr<GameObject> object)
{
	m_destroyObjects.push_back(object);
}

void Scene::RemoveAll()
{
	m_objects.clear();
}

void Scene::Update()
{
	if (m_destroyObjects.empty() == false)
	{
		for (const auto obj : m_destroyObjects)
		{
			std::erase(m_objects, obj);
		}
		m_destroyObjects.clear();
	}

	for(auto& object : m_objects)
	{
		object->Update();
	}
}

void Scene::Render() const
{
	for (const auto& object : m_objects)
	{
		object->Render();
	}
}

