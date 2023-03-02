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

		const glm::vec3& GetPosition() const { return m_localPosition; }
		const glm::vec3& GetWorldPosition();

		void SetPosition(float x, float y, float z = 0);
		void SetLocalPosition(float x, float y, float z = 0);
		void SetPosition(const glm::vec3& pos) { m_localPosition = pos; SetPositionDirty(); };
		void SetLocalPosition(const glm::vec3& pos) { m_localPosition = pos; SetPositionDirty(); };

		void SetPositionDirty();

		//Component stuff
		~Transform() override = default;

	private:

		void UpdateWorldPosition();

		glm::vec3 m_worldPosition{0,0,0};
		glm::vec3 m_localPosition{0,0,0};

		//Dirty flag
		bool m_isPositionDirty{true};
	};
}
