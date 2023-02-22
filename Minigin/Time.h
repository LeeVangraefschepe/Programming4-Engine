#pragma once
struct Time
{
	static void SetDeltaTime(float deltaTime) { m_deltaTime = deltaTime; }
	static float GetDeltaTime() { return m_deltaTime; }
private:
	static inline float m_deltaTime{};
};