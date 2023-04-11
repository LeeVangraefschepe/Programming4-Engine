#pragma once
#include "SceneManager.h"
#include "GameObject.h"

namespace dae
{
	class Scene final
	{
	public:
		explicit Scene(const std::string& name);
		~Scene();

		void Add(GameObject* object);
		void Remove(GameObject* object);
		void RemoveAll();

		GameObject* GetRootObject();

		void Update();
		void Render() const;

		Scene(const Scene& other) = delete;

		Scene(Scene&& other) noexcept
			: m_name(std::move(other.m_name))
			, m_rootObject(std::move(other.m_rootObject))
			, m_destroyObjects(std::move(other.m_destroyObjects))
		{
		}


		Scene& operator=(const Scene& other) = delete;
		Scene& operator=(Scene&& other) = delete;

	private: 

		std::string m_name;

		std::unique_ptr<GameObject> m_rootObject;
		std::vector<GameObject*> m_destroyObjects{};

		static unsigned int m_idCounter; 
	};

}
