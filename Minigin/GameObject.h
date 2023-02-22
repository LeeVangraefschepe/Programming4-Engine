#pragma once
#include <memory>
#include <vector>

#include "Transform.h"
#include "BaseComponent.h"
#include "RenderComponent.h"
#include "TextRenderer.h"

namespace dae
{
	class Texture2D;

	// todo: this should become final.
	class GameObject 
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
		T* AddComponentTest(T* component)
		{
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


		void SetTexture(const std::string& filename);
		virtual void SetPosition(float x, float y);

		GameObject() = default;
		virtual ~GameObject();
		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;

	private:
		Transform m_transform{};
		// todo: mmm, every gameobject has a texture? Is that correct?
		std::vector<BaseComponent*> m_pComponents{};
		std::shared_ptr<Texture2D> m_texture{};
	};
}