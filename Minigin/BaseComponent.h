#pragma once
#include <vector>

namespace dae
{
	class GameObject;

	class BaseComponent
	{
	public:
		BaseComponent(GameObject* pGameObject) : m_pGameObject(pGameObject){}

		virtual void Update(){}
		virtual void Render(){}

		virtual ~BaseComponent() = default;
		BaseComponent(const BaseComponent& other) = delete;
		BaseComponent(BaseComponent&& other) = delete;
		BaseComponent& operator=(const BaseComponent& other) = delete;
		BaseComponent& operator=(BaseComponent&& other) = delete;

	protected:
		virtual GameObject* GetGameObject() const { return m_pGameObject; }
	private:
		GameObject* m_pGameObject;
	};
}
