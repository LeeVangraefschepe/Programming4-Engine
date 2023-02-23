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

		const glm::vec3& GetPosition() const { return m_position; }
		void SetPosition(float x, float y, float z = 0);

		//Component stuff
		~Transform() override = default;
		void Update() override{}
		void Render() const override{}

	private:
		glm::vec3 m_position{0,0,0};
	};
}
