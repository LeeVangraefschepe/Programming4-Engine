#pragma once
#include <vector>

namespace dae
{
	class GameObject;

	class BaseComponent
	{
	public:
		//BaseComponent(GameObject* pGameObject){}
		BaseComponent() = default;

		virtual ~BaseComponent() = default;
		BaseComponent(const BaseComponent& other) = delete;
		BaseComponent(BaseComponent&& other) = delete;
		BaseComponent& operator=(const BaseComponent& other) = delete;
		BaseComponent& operator=(BaseComponent&& other) = delete;

		virtual void Update() = 0;
		virtual void Render() = 0;
	protected:
		GameObject* m_pGameObject{nullptr};
	};
}
