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
		virtual void Update();
		virtual void Render() const;


		template<typename T, typename... Args>
		T* AddComponent(Args&&... args)
		{
			static_assert(std::is_base_of<BaseComponent, T>::value, "T must be derived from BaseComponent");
			T* component = new T(std::forward<Args>(args)...);
			m_pComponents.push_back(component);
			return component;
		}
		template<typename T>
		T* AddComponent(T* component)
		{
			m_pComponents.push_back(component);
			return component;
		}

		//TextRenderer* AddComponentCast(TextRenderer* component)
		//{
		//	m_pComponents.push_back(component);
		//	return component;
		//}

		template <typename T>
		T* GetComponent() const;

		template <typename T>
		void RemoveComponent() const;

		GameObject() = default;
		virtual ~GameObject();
		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;

	private:
		Transform m_transform{};
		std::vector<BaseComponent*> m_pComponents{};
	};
}