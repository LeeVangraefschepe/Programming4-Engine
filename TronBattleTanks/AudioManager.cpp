#include "AudioManager.h"
#include "AudioSystemSDL2.h"
#include "ServiceLocator.h"

void dae::AudioManager::SetService(std::unique_ptr<dae::AudioSystem> system) const
{
	ServiceLocator::RegisterAudioSystem(std::move(system));
	LoadSounds();
}

void dae::AudioManager::LoadSounds() const
{
	ServiceLocator::GetAudioSystem()->LoadSound(Sounds::Fire, "Fart.mp3");
	ServiceLocator::GetAudioSystem()->LoadSound(Music::MainMenu, "AH.wav");
}