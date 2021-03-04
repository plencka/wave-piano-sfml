#include "ManagedWindows.h"

namespace Interface
{

	void cMainPianoWindow::deploy()
	{
		sf::RectangleShape toolSegment = createSegment({ 1300, 50 });
		sf::RectangleShape midSegment = createSegment({ 1300, 200 });
		auto selectorButton = std::make_shared<cButtonOpenSelector>(shared_from_this(), &keyPairs[26], "SelectorButton");
		selectorButton->setPosition(toolSegment.getPosition());
		for (int i = 0; i < 26; i++) {
			auto pianoButton = std::make_shared<cButtonPianoKey>(shared_from_this(), &keyPairs[i], "PianoButton");
			pianoButton->setPosition((float(i * (pianoButton->getArea().x) + midSegment.getPosition().x)), float(midSegment.getPosition().y));

			sf::Vector2 position(float(pianoButton->getPosition().x + 7), float(pianoButton->getPosition().y));
			texts.push_back(Interface::createText(pianoButton->pressKey->keyName, position, 25, sf::Color::Black, sf::Text::Bold));

			registerButton(pianoButton);
			registerNote(pianoButton);
		}
		registerButton(selectorButton);
		addSoundToNotes("Sine");
		openWindow(titleName);
	}

	void cMainPianoWindow::openWindow(const std::string windowTitle)
	{
		IManagedWindow::openWindow(this->titleName);
		enableButtons();
	}

	bool cMainPianoWindow::updateFocused(bool delayedDisplay)
	{
		if (!IManagedWindow::updateFocused(true))
			return false;
		for (auto text : texts) {
			draw(text);
		}
		states = windowStates(ENUM::removeFlag(states, windowStates::kRequiresRedraw));
		display();
		return true;
	}

	void cMainPianoWindow::closeWindow()
	{
		IManagedWindow::closeWindow();
		WaverPiano::App::exitApp = true;
	}


	bool cButtonPianoKey::actionPressed(bool isEventFromMouse)
	{
		if (!IManagedButton::actionPressed(isEventFromMouse))
			return false;

		audioPlay();
		gainIncrease(WaverPiano::App::Time::frameDelta);
		return true;
	}
	bool cButtonPianoKey::actionActive(bool oneActionPerRelease)
	{
		if (!IManagedButton::actionActive(false))
			return false;

		if (gainDecrease(WaverPiano::App::Time::frameDelta)) actionIdle();
		return true;
	}
	bool cButtonPianoKey::actionDisabled()
	{
		IManagedButton::actionDisabled();
		audioStop();
		return true;
	}
	bool cButtonOpenSelector::actionActive(bool oneActionPerRelease)
	{
		if (!IManagedButton::actionActive(true))
			return false;
		cWindowManager::disableKeysByID(ID_WINDOW::mainPianoBoard);
		cWindowManager::openWindowByID(ID_WINDOW::instrumentSelect);
		return true;
	}
}