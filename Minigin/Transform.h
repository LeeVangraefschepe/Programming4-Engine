#pragma once
#include <glm/glm.hpp>
#include "BaseComponent.h"

namespace dae
{
	class Transform final : public BaseComponent
	{
	public:
		const glm::vec3& GetPosition() const { return m_position; }
		void SetPosition(float x, float y, float z);

		//Component stuff
		~Transform() override = default;
		void Update() override{}
		void Render() override{}

	private:
		glm::vec3 m_position{0,0,0};
	};
}
