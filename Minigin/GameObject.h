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
		std::shared_ptr<T> AddComponent(Args&&... args)
		{
			//Make sure its a component
			static_assert(std::is_base_of<BaseComponent, T>::value, "T must be derived from BaseComponent");

			//Create shared pointer
			auto pComponent{ std::make_shared<T>(this, std::forward<Args>(args)...) };
			//Add to data list
			m_pComponents.push_back(pComponent);

			//Return to user
			return pComponent;
		}
		template<typename T>
		T* AddComponent(T* component)
		{
			m_pComponents.push_back(component);
			return component;
		}

		template<typename T>
		std::weak_ptr<T> GetComponent() const
		{
			for (const auto p : m_pComponents)
			{
				if (std::shared_ptr<T> derivedComponent{ std::dynamic_pointer_cast<T>(p) } )
				{
					return derivedComponent;
				}
			}
			return std::weak_ptr<T>();
		}

		template<typename T>
		void RemoveComponent() {
			for (auto it = m_pComponents.begin(); it != m_pComponents.end(); ++it) {
				std::shared_ptr<T> pComponent{ std::dynamic_pointer_cast<T>(*it) };
				if (pComponent != nullptr) {
					it->reset();
					m_pComponents.erase(it);
					return;
				}
			}
		}
		
		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;

	private:
		std::vector<std::shared_ptr<BaseComponent>> m_pComponents{};
	};
}