#pragma once
#include <memory>
#include <vector>

#include "Transform.h"
#include "BaseComponent.h"
#include "TextRenderer.h"

namespace dae
{
	class Texture2D;

	class GameObject final
	{
	public:
		GameObject();
		~GameObject();

		virtual void Update();
		virtual void Render() const;


		template<typename T, typename... Args>
		T* AddComponent(Args&&... args)
		{
			static_assert(std::is_base_of<BaseComponent, T>::value, "T must be derived from BaseComponent");
			T* component = new T(this, std::forward<Args>(args)...);
			m_pComponents.push_back(component);
			return component;
		}
		template<typename T>
		T* AddComponent(T* component)
		{
			m_pComponents.push_back(component);
			return component;
		}

		template<typename T>
		T* GetComponent() const
		{
			for (const auto p : m_pComponents)
			{
				if (typeid(*p) == typeid(T))
				{
					return static_cast<T*>(p);
				}
			}
			return nullptr;
		}

		template<typename T>
		void RemoveComponent() {
			for (auto it = m_pComponents.begin(); it != m_pComponents.end(); ++it) {
				T* pComponent = dynamic_cast<T*>(*it);
				if (pComponent != nullptr) {
					delete pComponent;
					pComponent = nullptr;
					//m_pComponents.erase(it);
					return;
				}
			}
		}
		
		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;

	private:
		std::vector<BaseComponent*> m_pComponents{};
	};
}