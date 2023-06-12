#pragma once
#include <string>
#include <memory>
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
		virtual void Mute(bool) = 0;
	};

	class DefaultAudioSystem final : public AudioSystem
	{
	public:
		void Play(const SoundId, const float) override {}
		void LoadSound(const SoundId, const std::string&) override {}
		void StopAll() override {}
		void PauseAll() override {}
		void ResumeAll() override {}
		void Mute(bool) override {}
	};
	class AudioSystemLogger final : public AudioSystem
	{
		std::unique_ptr<AudioSystem> m_logger;
	public:
		AudioSystemLogger(std::unique_ptr<AudioSystem> logger) { m_logger = std::move(logger); }
		void Play(const SoundId id, const float volume) override { printf("Playing soud: %d with volume: %f\n", id, static_cast<double>(volume)); m_logger->Play(id, volume); }
		void LoadSound(const SoundId id, const std::string& path) override { printf("Loading sound: %d with path: %s\n", id, path.c_str()); m_logger->LoadSound(id, path); }
		void StopAll() override { printf("Stopping all sounds\n"); m_logger->StopAll(); }
		void PauseAll() override { printf("Pausing all sounds\n"); m_logger->PauseAll(); }
		void ResumeAll() override { printf("Resume all sounds\n"); m_logger->ResumeAll(); }
		void Mute(bool value) override { printf("Mute all sounds\n"); m_logger->Mute(value); }
	};
}