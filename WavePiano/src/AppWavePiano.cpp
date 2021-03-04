#include "AppWavePiano.h"

namespace App {
	sf::Clock cWavePiano::frameTime;

	int cWavePiano::run()
	{
		initialize();
		while (!WaverPiano::App::exitApp) {
			update();
		};
		return exit();
	}
	int cWavePiano::initialize()
	{
		frameTime.restart(); // Ensure clock starts with correct values to avoid value spikes.
		WaverPiano::Interface::Font::generic.loadFromFile(PATH_DEFAULTS::font);
		Interface::cWindowManager::registerWindow(std::make_shared<Interface::cMainPianoWindow>());
		Interface::cWindowManager::registerWindow(std::make_shared<Interface::cSelectorWindow>());
		return 0;
	}
	bool cWavePiano::update()
	{
		Interface::cWindowManager::updateWindows();
		WaverPiano::App::Time::frameDelta = frameTime.restart().asSeconds();
		return true;
	}
	int cWavePiano::exit()
	{
		Interface::cWindowManager::disposeWindows();
		assert(SpriteAnimator::cAnimationManager::verifyNoReferences());
		return 0;
	}
}