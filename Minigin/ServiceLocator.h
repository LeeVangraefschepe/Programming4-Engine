#pragma once
#include <memory>

#include "AudioSystem.h"
#include "GameState.h"

namespace dae
{
    class ServiceLocator final
    {
        inline static std::unique_ptr<AudioSystem> m_audioSystem = std::make_unique<DefaultAudioSystem>();
        inline static std::unique_ptr<GameState> m_gameState = std::make_unique<GameState>();
    public:
        ServiceLocator() = delete;
        static GameState* GetGameState() { return  m_gameState.get(); }

        static AudioSystem* GetAudioSystem() { return  m_audioSystem.get(); }
        static void RegisterAudioSystem(std::unique_ptr<AudioSystem> system)
        {
            if (system) { m_audioSystem = std::move(system); }
            else { m_audioSystem = std::make_unique<DefaultAudioSystem>(); }
        }
    };
}
