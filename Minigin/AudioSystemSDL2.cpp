#include "AudioSystemSDL2.h"
#include "SDL.h"
#include "SDL_mixer.h"
#include <iostream>
#include <ranges>
#include <sstream>

#include "ResourceManager.h"

dae::AudioSystemSDL2::AudioSystemSDL2()
{
	if (Mix_Init(MIX_INIT_MP3) < 0)
	{
		std::cout << "Failed initializing SDL mixer\n";
	}
	if (Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 4096) < 0)
	{
		std::cout << "Failed opening audio device in SDL mixer\n";
	}
	m_thread = std::jthread{ &AudioSystemSDL2::Run, this };
	m_thread.detach();
}

dae::AudioSystemSDL2::~AudioSystemSDL2()
{
	for (const auto val : m_sounds | std::views::values)
	{
		Mix_FreeChunk(val);
	}
}

void dae::AudioSystemSDL2::LoadSound(SoundId id, const std::string& path)
{
	std::stringstream ss{};
	ss << ResourceManager::GetInstance().GetPath() << path;
	auto sound = Mix_LoadWAV(ss.str().c_str());
	if (!sound)
	{
		printf("Error loading sound: %s\n", Mix_GetError());
		return;
	}

	m_sounds.emplace(std::pair{id, sound});
}

void dae::AudioSystemSDL2::Play(const SoundId id, const float)
{
	std::cout << "Play sound " << id << "\n";
	if (!m_sounds.contains(id))
	{
		return;
	}
	const auto sound = m_sounds.at(id);
	if (const int channel = Mix_PlayChannel(-1, sound, 0); channel == -1)
	{
		std::cout << "Failed to find open channel: " << channel <<"\n";
	}
}
void dae::AudioSystemSDL2::Run()
{
	
}

