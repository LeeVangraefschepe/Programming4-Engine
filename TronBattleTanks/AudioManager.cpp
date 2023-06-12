#include "AudioManager.h"

#include <SDL_keycode.h>

#include "AudioSystemSDL2.h"
#include "Commands.h"
#include "InputManager.h"
#include "ServiceLocator.h"

void dae::AudioManager::SetService(std::unique_ptr<dae::AudioSystem> system) const
{
	ServiceLocator::RegisterAudioSystem(std::move(system));
	LoadSounds();
}

void dae::AudioManager::LoadSounds() const
{
	const auto audioSystem = ServiceLocator::GetAudioSystem();
	audioSystem->LoadSound(Sounds::Fire, "Sounds/Shoot.mp3");
	audioSystem->LoadSound(Sounds::Teleport, "Sounds/Teleport.mp3");

	audioSystem->LoadSound(Music::MainMenu, "Sounds/MainMenuMusic.mp3");
	audioSystem->LoadSound(Music::HighscoreMenu, "Sounds/FailMusic.mp3");
	audioSystem->LoadSound(Music::GameMenu, "Sounds/Background.mp3");
}

dae::AudioManager::AudioManager()
{
	const auto continueAction = [this]()
	{
		m_muted = !m_muted;
		ServiceLocator::GetAudioSystem()->Mute(m_muted);
	};
	m_command = new LambdaCommand{ continueAction };
	InputManager::GetInstance().BindCommand<LambdaCommand>(m_command, SDLK_m, InputManager::InputType::OnButtonDown);
}
