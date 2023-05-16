#pragma once
#include "AudioSystem.h"
#include "EventQueue.h"
#include <condition_variable>
#include <string>
#include <thread>
#include <unordered_map>

struct Mix_Chunk;
namespace dae
{
	class AudioSystemSDL2 final : public AudioSystem
	{
	public:
		AudioSystemSDL2();
		~AudioSystemSDL2() override;
		void LoadSound(const SoundId id, const std::string& path) override;
		void Play(const SoundId id, const float volume) override;
		void StopAll() override;
		void PauseAll() override;
		void ResumeAll() override;
	private:
		void Run(const std::stop_token& stopToken);

		std::unordered_map<SoundId, Mix_Chunk*> m_sounds{};
		EventQueue<Event> m_Queue;

		std::jthread m_thread;
		std::stop_source m_Stop{};
		std::mutex m_Mutex;
		std::condition_variable m_ConditionVariable;
	};
}