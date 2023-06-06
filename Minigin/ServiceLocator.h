#pragma once
#include <memory>
#include "AudioSystem.h"

namespace dae
{
    class ServiceLocator final
    {
        inline static std::unique_ptr<AudioSystem> m_audioSystem = std::make_unique<DefaultAudioSystem>();
    public:
        ServiceLocator() = delete;
        static AudioSystem* GetAudioSystem() { return  m_audioSystem.get(); }
        static void RegisterAudioSystem(std::unique_ptr<AudioSystem> system)
        {
            if (system) { m_audioSystem = std::move(system); }
            else { m_audioSystem = std::make_unique<DefaultAudioSystem>(); }
        }
    };
}
