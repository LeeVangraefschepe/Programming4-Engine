#pragma once
#include <glm/glm.hpp>
#include "BaseComponent.h"

namespace dae
{
	class Transform final : public BaseComponent
	{
	public:
		Transform(GameObject* pGameObject)
			: BaseComponent(pGameObject)
		{
		}

		const glm::vec2& GetLocalPosition() const;
		const glm::vec2& GetWorldPosition();
		float GetRotation() const;

		void SetPosition(float x, float y);
		void SetLocalPosition(float x, float y);
		void SetPosition(const glm::vec2& pos) { m_localPosition = pos; SetPositionDirty(); };
		void SetLocalPosition(const glm::vec2& pos) { m_localPosition = pos; SetPositionDirty(); };
		void SetRotation(float rotation);

		void SetPositionDirty();

		//Component stuff
		~Transform() override = default;

	private:

		void UpdateWorldPosition();

		glm::vec2 m_worldPosition{0,0};
		glm::vec2 m_localPosition{0,0};
		float m_rotation{0.f};

		//Dirty flag
		bool m_isPositionDirty{true};
	};
}
