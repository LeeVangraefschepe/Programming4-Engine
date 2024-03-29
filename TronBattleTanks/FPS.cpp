#pragma once
#include "FPS.h"
#include <sstream>
#include "GameObject.h"
#include "ResourceManager.h"
#include "TextRenderer.h"
#include "Timer.h"

using namespace dae;

FPS::FPS(GameObject* pGameObject, float updateInterval): BaseComponent(pGameObject), m_timeInterval(updateInterval)
{
	m_pTextRenderer = GetGameObject()->GetComponent<TextRenderer>();
	if (m_pTextRenderer == nullptr)
	{
		m_pTextRenderer = GetGameObject()->AddComponent<TextRenderer>("FPS: ", ResourceManager::GetInstance().LoadFont("Lingua.otf", 12));
	}
	m_pTextRenderer->SetColor(247, 247, 0);
}

FPS::~FPS()
{
}

void FPS::Update()
{
	m_timeTillUpdate -= Time::GetDeltaTime();
	
	if (m_timeTillUpdate <= 0.f)
	{
		if (m_pTextRenderer)
		{
			std::stringstream ss{};
			ss << "FPS: " << static_cast<int>(1.f / Time::GetDeltaTime());
			m_pTextRenderer->SetText(ss.str());
		}
		m_timeTillUpdate = m_timeInterval;
	}
}
