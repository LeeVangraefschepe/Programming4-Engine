#pragma once
#include "AudioSystem.h"
#include "Singleton.h"
#include "memory"

namespace dae
{
	class LambdaCommand;
	class AudioManager final : public dae::Singleton<AudioManager>
	{
	public:
		enum Sounds
		{
			Fire = 0,
			Teleport
		};
		enum Music
		{
			MainMenu = 100,
			GameMenu,
			HighscoreMenu
		};

		/**
		 * \brief Also loads the sounds for the new service
		 * \param system The new sound system
		 */
		void SetService(std::unique_ptr<dae::AudioSystem> system) const;
		void LoadSounds() const;
	private:
		friend class Singleton<AudioManager>;
		AudioManager();

		LambdaCommand* m_command;
		bool m_muted{};
	};
}