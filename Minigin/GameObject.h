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

			//Get type of component
			const bool isRender = std::is_base_of<RenderComponent, T>::value;
			const bool isUpdate = std::is_base_of<UpdateComponent, T>::value;
			const bool isData = isRender == false && isUpdate == false;

			//Add to correct data list
			if (isData)
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
			const bool isRender = std::is_base_of<RenderComponent, T>::value;
			const bool isUpdate = std::is_base_of<UpdateComponent, T>::value;
			const bool isData = isRender == false && isUpdate == false;

			if (isData)
			{
				std::cout << "Data removed\n";
				EraseComponent<T>(m_pDataComponents);
			}
			else
			{
				if (isRender)
				{
					std::cout << "Render removed\n";
					EraseComponent<T>(m_pRenderComponents);
				}
				if (isUpdate)
				{
					std::cout << "Update removed\n";
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

		std::vector<std::weak_ptr<BaseComponent>> m_pComponents{};
		std::vector<std::shared_ptr<BaseComponent>> m_pDataComponents{};
		std::vector<std::shared_ptr<RenderComponent>> m_pRenderComponents{};
		std::vector<std::shared_ptr<UpdateComponent>> m_pUpdateComponents{};
	};
}
