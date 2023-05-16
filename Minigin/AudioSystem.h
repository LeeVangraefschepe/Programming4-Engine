#pragma once
#include <string>
namespace dae
{
	using SoundId = unsigned short;
	class AudioSystem
	{
	public:
		virtual ~AudioSystem() = default;
		virtual void Play(const SoundId id, const float volume) = 0;
		virtual void LoadSound(const SoundId id, const std::string& path) = 0;
		virtual void StopAll() = 0;
		virtual void PauseAll() = 0;
		virtual void ResumeAll() = 0;
	protected:
		enum Action
		{
			load,
			play,
			pause,
			resume,
			stop,
		};
		struct Event
		{
			Action action;
			SoundId id{};
			std::string path{};
			float volume{};
		};
	};

	class DefaultAudioSystem final : public AudioSystem
	{
	public:
		void Play(const SoundId, const float) override {}
		void LoadSound(const SoundId, const std::string&) override {}
		void StopAll() override {}
		void PauseAll() override {}
		void ResumeAll() override {}
	};
}