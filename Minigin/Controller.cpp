#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <Xinput.h>
#pragma comment(lib, "xinput.lib")

#include "Controller.h"
#include <cmath>
#include <algorithm>
#include <glm/vec2.hpp>

using namespace dae;

class Controller::ControllerImpl
{
	XINPUT_STATE previousState{};
	XINPUT_STATE currentState{};
	WORD buttonsPressedThisFrame;
	WORD buttonsReleasedThisFrame;
	int m_controllerIndex{};

public:
	ControllerImpl(int controllerIndex) : m_controllerIndex(controllerIndex)
	{
		ZeroMemory(&previousState, sizeof(XINPUT_STATE));
		ZeroMemory(&currentState, sizeof(XINPUT_STATE));
	}
	~ControllerImpl()
	{
		
	}
	void Update()
	{
		CopyMemory(&previousState, &currentState, sizeof(XINPUT_STATE));
		ZeroMemory(&currentState, sizeof(XINPUT_STATE));
		XInputGetState(m_controllerIndex, &currentState);

		auto buttonChanges { currentState.Gamepad.wButtons ^ previousState.Gamepad.wButtons };
		buttonsPressedThisFrame = buttonChanges & currentState.Gamepad.wButtons;
		buttonsReleasedThisFrame = buttonChanges & (~currentState.Gamepad.wButtons);
	}
	bool IsDownThisFrame(unsigned int button) const { return buttonsPressedThisFrame & button; }
	bool IsReleasedThisFrame(unsigned int button) const { return buttonsReleasedThisFrame & button; }
	bool IsPressed(unsigned int button) const { return currentState.Gamepad.wButtons & button; }
	glm::vec2 GetAxis(bool left) const
	{
		return 
	{
			(left ? currentState.Gamepad.sThumbLX : currentState.Gamepad.sThumbRX),
			(left ? currentState.Gamepad.sThumbLY : currentState.Gamepad.sThumbRY)
		};
	}
	unsigned char GetTrigger(bool left) const
	{
		return
		{
			left ? currentState.Gamepad.bLeftTrigger : currentState.Gamepad.bRightTrigger
		};
	}
};

float Controller::ClampAxisValue(float value) const
{
	constexpr float deadZoneValue{ 0.25f * MAXSHORT };
	constexpr float maxValue{ 0.9f * MAXSHORT };
	const float absValue = abs(value);

	if (absValue <= deadZoneValue)
	{
		return 0.f;
	}
	if (absValue >= maxValue)
	{
		if (std::signbit(value))
		{
			return -1.f;
		}
		return 1.f;
	}

	return value / maxValue;
}

float Controller::ClampTrigger(unsigned char value) const
{
	constexpr char deadZoneValue{ static_cast<char>(0.1f * static_cast<float>(MAXCHAR)) };
	constexpr char maxValue{ static_cast<char>(0.9f * static_cast<float>(MAXCHAR)) };

	if (value <= deadZoneValue)
	{
		return 0.f;
	}
	if (value >= maxValue)
	{
		return 1.f;
	}
	return static_cast<float>(value) / static_cast<float>(maxValue);
}

void dae::Controller::Update()
{
	m_pImpl->Update();
}

bool dae::Controller::IsDown(ControllerButton button) const
{
	return m_pImpl->IsDownThisFrame(static_cast<unsigned int>(button));
}

bool dae::Controller::IsUp(ControllerButton button) const
{
	return m_pImpl->IsReleasedThisFrame(static_cast<unsigned int>(button));
}

bool dae::Controller::IsPressed(ControllerButton button) const
{
	return m_pImpl->IsPressed(static_cast<unsigned int>(button));
}

glm::vec2 dae::Controller::GetAxis(ControllerButton button) const
{
	//TODO: Look into warning
	glm::vec2 input = m_pImpl->GetAxis(static_cast<int>(button) & static_cast<int>(ControllerButton::LeftThumb));
	input.x = ClampAxisValue(input.x);
	input.y = ClampAxisValue(input.y);
	return input;
}

float Controller::GetTrigger(ControllerButton button) const
{
	//TODO: Look into warning
	const unsigned char input = m_pImpl->GetTrigger(static_cast<int>(button) & static_cast<int>(ControllerButton::LeftShoulder));
	return ClampTrigger(input);
}

dae::Controller::Controller(int controllerIndex) : m_pImpl{ std::make_unique<ControllerImpl>(controllerIndex) }
{
	
}

Controller::~Controller()
{

}
