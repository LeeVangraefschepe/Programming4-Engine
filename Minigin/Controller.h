#pragma once
#include <memory>
#include <glm/vec2.hpp>

namespace dae
{
	class Controller
	{
		class ControllerImpl;
		std::unique_ptr<ControllerImpl> m_pImpl;
		float ClampAxisValue(float value) const;
		float ClampTrigger(unsigned char value) const;
	public:
		enum class ControllerButton
		{
			DPadUp = 0x0001,
			DPadDown = 0x0002,
			DPadLeft = 0x0004,
			DPadRight = 0x0008,
			Start = 0x0010,
			Back = 0x0020,
			LeftThumb = 0x0040,
			RightThumb = 0x0080,
			LeftShoulder = 0x0100,
			RightShoulder = 0x0200,
			ButtonA = 0x1000,
			ButtonB = 0x2000,
			ButtonX = 0x4000,
			ButtonY = 0x8000,
		};

		void Update();

		bool IsDown(ControllerButton button) const;
		bool IsUp(ControllerButton button) const;
		bool IsPressed(ControllerButton button) const;
		glm::vec2 GetAxis(ControllerButton button) const;
		float GetTrigger(ControllerButton button) const;

		explicit Controller(int controllerIndex);
		~Controller();

		Controller(const Controller& other) = delete;
		Controller(Controller&& other) = delete;
		Controller& operator=(const Controller& other) = delete;
		Controller& operator=(Controller&& other) = delete;
	};
}
