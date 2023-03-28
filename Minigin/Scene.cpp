#include "Scene.h"

using namespace dae;

unsigned int Scene::m_idCounter = 0;

Scene::Scene(const std::string& name) : m_name(name) {}

Scene::~Scene() = default;

void Scene::Add(GameObject* object)
{
	auto child = std::unique_ptr<GameObject>(object);
	m_objects.emplace_back(std::move(child));
}

void Scene::Remove(GameObject* object)
{
	m_destroyObjects.push_back(object);
}

void Scene::RemoveAll()
{
	m_objects.clear();
}

void Scene::Update()
{
	if (!m_destroyObjects.empty())
	{
		m_objects.erase(
			std::remove_if(
				m_objects.begin(),
				m_objects.end(),
				[&](const std::unique_ptr<GameObject>& obj) {
					return std::find(m_destroyObjects.begin(), m_destroyObjects.end(), obj.get()) != m_destroyObjects.end();
				}
			),
			m_objects.end()
					);

		m_destroyObjects.clear();
	}

	for(const auto& object : m_objects)
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

