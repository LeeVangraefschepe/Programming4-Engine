#pragma once
#include <string>
#include <thread>

#include "AudioSystem.h"
#include <unordered_map>

struct Mix_Chunk;
namespace dae
{
	class AudioSystemSDL2 final : public AudioSystem
	{
	public:
		AudioSystemSDL2();
		~AudioSystemSDL2() override;
		void LoadSound(SoundId id, const std::string& path) override;
		void Play(const SoundId id, const float volume) override;
	private:
		void Run();
		std::unordered_map<SoundId, Mix_Chunk*> m_sounds{};
		std::jthread m_thread;
	};
}