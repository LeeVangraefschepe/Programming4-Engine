#pragma once
#include "FPS.h"
#include <sstream>
#include "GameObject.h"
#include "ResourceManager.h"
#include "TextRenderer.h"
#include "Time.h"

using namespace dae;

FPS::FPS(GameObject* pGameObject, float updateInterval): UpdateComponent(pGameObject), m_timeInterval(updateInterval)
{
	m_pTextRenderer = m_pGameObject->GetComponent<TextRenderer>();
	if (m_pTextRenderer.expired())
	{
		m_pTextRenderer = m_pGameObject->AddComponent<TextRenderer>("FPS: ", ResourceManager::GetInstance().LoadFont("Lingua.otf", 12));
	}
	m_pTextRenderer.lock()->SetColor(247, 247, 0);
}

FPS::~FPS()
{
}

void FPS::Update()
{
	m_timeTillUpdate -= Time::GetDeltaTime();
	
	if (m_timeTillUpdate <= 0.f)
	{
		if (m_pTextRenderer.expired() == false)
		{
			std::stringstream ss{};
			ss << "FPS: " << static_cast<int>(1.f / Time::GetDeltaTime());
			m_pTextRenderer.lock()->SetText(ss.str());
		}
		m_timeTillUpdate = m_timeInterval;
	}
}
