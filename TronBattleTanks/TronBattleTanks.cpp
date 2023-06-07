#include <SDL.h>

#if _DEBUG
// ReSharper disable once CppUnusedIncludeDirective
#if __has_include(<vld.h>)
#include <vld.h>
#endif
#endif

#include "AudioManager.h"
#include "AudioSystemSDL2.h"
#include "Minigin.h"
#include "GameScene.h"

int main(int, char* [])
{
    dae::Minigin engine("../Data/", 700, 720);
    dae::AudioManager::GetInstance().SetService(std::make_unique<dae::AudioSystemSDL2>());
    engine.Run(dae::GameScene::Load);
    return 0;
}
