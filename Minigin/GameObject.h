#pragma once
#include <memory>
#include <vector>

#include "Transform.h"
#include "BaseComponent.h"
#include "SpriteRenderer.h"
#include "UpdateComponent.h"
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

#pragma region ComponentTemplate
		template<typename T, typename... Args>
		std::weak_ptr<T> AddComponent(Args&&... args)
		{
			//Make sure its a component
			static_assert(std::is_base_of<BaseComponent, T>::value, "T must be derived from BaseComponent");


			//Check if component is already on object
			std::weak_ptr<T> attachedComp = GetComponent<T>();
			if (attachedComp.expired() == false)
			{
				return attachedComp;
			}

			//Create shared pointer
			auto pComponent{ std::make_shared<T>(this, std::forward<Args>(args)...) };

			//Get type of component
			bool isRender = std::is_base_of<RenderComponent, T>::value;
			bool isUpdate = std::is_base_of<UpdateComponent, T>::value;

			//Add to correct data list
			if (isRender == false && isUpdate == false)
			{
				auto pRenderComponent = std::dynamic_pointer_cast<BaseComponent>(pComponent);
				m_pDataComponents.push_back(pRenderComponent);
			}
			else
			{
				if (isRender)
				{
					auto pRenderComponent = std::dynamic_pointer_cast<RenderComponent>(pComponent);
					m_pRenderComponents.push_back(pRenderComponent);
				}
				if (isUpdate)
				{
					auto pRenderComponent = std::dynamic_pointer_cast<UpdateComponent>(pComponent);
					m_pUpdateComponents.push_back(pRenderComponent);
				}
			}

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
				if (auto sp = p.lock())
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
				if (auto sp = p.lock())
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
			//Get type of component
			bool isRender = std::is_base_of<RenderComponent, T>::value;
			bool isUpdate = std::is_base_of<UpdateComponent, T>::value;

			if (isRender == false && isUpdate == false)
			{
				EraseComponent<T>(m_pDataComponents);
			}
			else
			{
				if (isRender)
				{
					EraseComponent<T>(m_pRenderComponents);
				}
				if (isUpdate)
				{
					EraseComponent<T>(m_pUpdateComponents);
				}
			}

			for (auto it = m_pComponents.begin(); it != m_pComponents.end(); ++it) {
				std::shared_ptr<T> pComponent{ std::dynamic_pointer_cast<T>((it)->lock()) };
				if (pComponent != nullptr) {
					m_pComponents.erase(it);
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
		template<typename T, typename J>
		void EraseComponent(std::vector<std::shared_ptr<J>>& list)
		{
			for (auto it = list.begin(); it != list.end(); ++it) {
				std::shared_ptr<T> pComponent{ std::dynamic_pointer_cast<T>(*it) };
				if (pComponent != nullptr) {
					it->reset();
					list.erase(it);
					return;
				}
			}
		}

		bool IsValidParent(std::weak_ptr<GameObject> parent);

		std::weak_ptr<GameObject> m_pParent{};
		std::vector<std::weak_ptr<GameObject>> m_pChildren{};

		std::vector<std::weak_ptr<BaseComponent>> m_pComponents{};
		std::vector<std::shared_ptr<BaseComponent>> m_pDataComponents{};
		std::vector<std::shared_ptr<RenderComponent>> m_pRenderComponents{};
		std::vector<std::shared_ptr<UpdateComponent>> m_pUpdateComponents{};
	};
}
