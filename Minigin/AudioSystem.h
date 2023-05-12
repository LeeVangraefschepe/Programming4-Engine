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
		virtual void LoadSound(SoundId id, const std::string& path) = 0;
	};

	class DefaultAudioSystem final : public AudioSystem
	{
	public:
		void Play(const SoundId, const float) override {}
		void LoadSound(SoundId, const std::string&) override {}
	};
}