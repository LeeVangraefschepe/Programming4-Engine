#pragma once
#include <memory>
#include <vector>
#include "Subject.h"
#include "BaseComponent.h"

namespace dae
{
	class BaseComponent;
	
	class GameObject final
	{
	public:
		explicit GameObject();
		~GameObject();

		void Update();
		void Render() const;

#pragma region Observable
		void AddObservableObject(Observer* observer) const
		{
			m_notifyObject->AddObserver(observer);
		}
		void RemoveObserver(Observer* observer) const
		{
			m_notifyObject->RemoveObserver(observer);
		}
		const Subject* GetSubject() const
		{
			return m_notifyObject.get();
		}
#pragma endregion 

#pragma region Parenting
		void SetParent(GameObject* parent, bool keepWorldPosition);
		GameObject* GetParent() const { return m_pParent; }
		
		
		std::vector<GameObject*> GetChildren() const
		{
			std::vector<GameObject*> rawPointers;
			for (const auto& child : m_pChildren)
			{
				rawPointers.push_back(child.get());
			}
			return rawPointers;
		}

		bool HasChild(GameObject* child) const;
#pragma endregion

#pragma region ComponentTemplate
		template<typename T, typename... Args>
		T* AddComponent(Args&&... args)
		{
			//Make sure its a component
			static_assert(std::is_base_of<BaseComponent, T>::value, "T must be derived from BaseComponent");

			//Make sure the args match the constructor
			static_assert(std::is_constructible<T, GameObject*, Args...>::value, "Unable to construct T with the given arguments in function");

			//Check if component is already on object
			if (T* attachedComp = GetComponent<T>())
			{
				return attachedComp;
			}

			//Create shared pointer
			auto pComponent{ std::make_unique<T>(this, std::forward<Args>(args)...) };
			auto rawPointer = pComponent.get();

			//Add to global list
			m_pComponents.push_back(std::move(pComponent));

			//Return to user
			return rawPointer;
		}

		template<typename T>
		T* GetComponent() const
		{
			for (const auto& p : m_pComponents)
			{
				if (p)
				{
					if (auto* derivedComponent = dynamic_cast<T*>(p.get()))
					{
						return derivedComponent;
					}
				}
			}
			return nullptr;
		}

		template<typename T>
		bool HasComponent() const
		{
			for (const auto& p : m_pComponents)
			{
				if (p)
				{
					if (auto* derivedComponent = dynamic_cast<T*>(p.get()))
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
				auto* pComponent = dynamic_cast<T*>(it->get());
				if (pComponent != nullptr)
				{
					m_pDestroyComponents.push_back(it->get());
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
		bool IsValidParent(GameObject* parent) const;
		GameObject* m_pParent{};

		std::unique_ptr<Subject> m_notifyObject = std::make_unique<Subject>();

		void EraseComponent(const BaseComponent* component);
		std::vector<std::unique_ptr<GameObject>> m_pChildren{};
		std::vector<std::unique_ptr<BaseComponent>> m_pComponents{};
		std::vector<BaseComponent*> m_pDestroyComponents{};
	};
}
