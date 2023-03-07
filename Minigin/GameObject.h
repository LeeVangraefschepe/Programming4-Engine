#pragma once
#include <memory>
#include <vector>

#include "Transform.h"
#include "BaseComponent.h"
#include "SpriteRenderer.h"
#include <string>
#include <iostream>

namespace dae
{
	class Texture2D;

	class GameObject final : public std::enable_shared_from_this<GameObject>
	{
	public:
		explicit GameObject();
		~GameObject();

		virtual void Update();
		virtual void Render() const;

		void SetParent(std::weak_ptr<GameObject> parent, bool keepWorldPosition);
		std::weak_ptr<GameObject> GetParent() const { return m_pParent; }
		void AddChild(std::weak_ptr<GameObject> child);
		void RemoveChild(std::weak_ptr<GameObject> child);
		
		const std::vector<std::weak_ptr<GameObject>>& GetChildren() { return  m_pChildren; }
		bool HasChild(std::shared_ptr<GameObject> child) const;

#pragma region ComponentTemplate
		template<typename T, typename... Args>
		std::weak_ptr<T> AddComponent(Args&&... args)
		{
			//Make sure its a component
			static_assert(std::is_base_of<BaseComponent, T>::value, "T must be derived from BaseComponent");

			//Make sure the args match the constructor
			static_assert(std::is_constructible<T, GameObject*, Args...>::value, "Unable to construct T with the given arguments in function");

			//Check if component is already on object
			std::weak_ptr<T> attachedComp = GetComponent<T>();
			if (attachedComp.expired() == false)
			{
				return attachedComp;
			}

			//Create shared pointer
			auto pComponent{ std::make_shared<T>(this, std::forward<Args>(args)...) };

			//Add to global list
			m_pComponents.push_back(pComponent);

			//Return to user
			return pComponent;
		}

		template<typename T>
		std::weak_ptr<T> GetComponent() const
		{
			for (const auto& p : m_pComponents)
			{
				if (const auto sp = p)
				{
					if (auto derivedComponent = std::dynamic_pointer_cast<T>(sp))
					{
						return derivedComponent;
					}
				}
			}
			return std::weak_ptr<T>();
		}

		template<typename T>
		bool HasComponent() const
		{
			for (const auto& p : m_pComponents)
			{
				if (auto sp = p)
				{
					if (auto derivedComponent = std::dynamic_pointer_cast<T>(sp))
					{
						return true;
					}
				}
			}
			return false;
		}

		template<typename T>
		void RemoveComponent() {

			for (auto it = m_pComponents.begin(); it != m_pComponents.end(); ++it)
			{
				std::shared_ptr<T> pComponent{ std::dynamic_pointer_cast<T>(*it) };
				if (pComponent != nullptr)
				{
					m_pDestroyComponents.push_back(*it);
					return;
				}
			}
		}
#pragma endregion

		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;

	private:
		void EraseComponent(const std::shared_ptr<BaseComponent> component);
		bool IsValidParent(std::weak_ptr<GameObject> parent);

		std::weak_ptr<GameObject> m_pParent{};
		std::vector<std::weak_ptr<GameObject>> m_pChildren{};
		std::vector<std::shared_ptr<BaseComponent>> m_pComponents{};
		std::vector<std::weak_ptr<BaseComponent>> m_pDestroyComponents{};
	};
}
