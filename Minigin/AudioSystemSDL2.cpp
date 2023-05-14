#include "AudioSystemSDL2.h"
#include "SDL.h"
#include "SDL_mixer.h"
#include <iostream>
#include <ranges>
#include <sstream>
#include <thread>
#include <stop_token>

#include "ResourceManager.h"

dae::AudioSystemSDL2::AudioSystemSDL2()
{
	if (Mix_Init(MIX_INIT_MP3) < 0)
	{
		printf("Error initializing SDL sound: %s\n", Mix_GetError());
	}
	if (Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 4096) < 0)
	{
		printf("Error opening audio device: %s\n", Mix_GetError());
	}
	m_thread = std::jthread{ &AudioSystemSDL2::Run, this, m_Stop.get_token() };
}

dae::AudioSystemSDL2::~AudioSystemSDL2()
{
	m_Stop.request_stop();
	m_ConditionVariable.notify_one();
	for (const auto val : m_sounds | std::views::values)
	{
		Mix_FreeChunk(val);
	}
	Mix_CloseAudio();
	Mix_Quit();
}

void dae::AudioSystemSDL2::LoadSound(const SoundId id, const std::string& path)
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
	m_Queue.Enqueue(Event{ play, id });
	m_ConditionVariable.notify_one();
}
void dae::AudioSystemSDL2::StopAll()
{
	m_Queue.Enqueue(Event{ stop });
	m_ConditionVariable.notify_one();
}

void dae::AudioSystemSDL2::PauseAll()
{
	m_Queue.Enqueue(Event{ pause });
	m_ConditionVariable.notify_one();
}

void dae::AudioSystemSDL2::ResumeAll()
{
	m_Queue.Enqueue(Event{ resume });
	m_ConditionVariable.notify_one();
}

void dae::AudioSystemSDL2::Run(const std::stop_token& stopToken)
{
	std::unique_lock lock{m_Mutex};

	while (!stopToken.stop_requested())
	{
		m_ConditionVariable.wait(lock);
		
		while (!m_Queue.IsEmpty() && !stopToken.stop_requested())
		{
			auto event = m_Queue.Dequeue();
			switch (event.action)
			{
			case play:
			{
				if (!m_sounds.contains(event.id))
				{
					return;
				}
				const auto sound = m_sounds.at(event.id);
				if (const int channel = Mix_PlayChannel(-1, sound, 0); channel == -1)
				{
					printf("Error playing sound: %s\n", Mix_GetError());
				}
				std::cout << "Play sound " << event.id << "\n";
			}
			break;
			case stop:
			{
				Mix_HaltChannel(-1);
			}
			break;
			case pause:
			{
				Mix_Pause(-1);
			}
			break;
			case resume:
			{
				Mix_Resume(-1);
			}
			break;
			}
		}
	}
}

