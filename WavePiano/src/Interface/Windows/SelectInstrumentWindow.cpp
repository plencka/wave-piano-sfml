#include "ManagedWindows.h"

namespace Interface {

	void cSelectorWindow::deploy()
	{
		sf::RectangleShape toolSegment = createSegment({ 300, 300 });
		sf::RectangleShape midSegment = createSegment({ 300, 30 });
		sf::RectangleShape switcherSegment = createSegment({ 300, 40 });
		for (unsigned int i = 0; i < 9; i++) { // Create grid 3x3
			auto selectButton = std::make_shared<cInstrumentSelectButton>(shared_from_this(),
				&keyPairs[i + KeyRemap::getNumberOffset()], "InstrumentDefaultSelector");
			selectButton->setPosition((float(toolSegment.getPosition().x + i % 3 * (selectButton->getArea().x))),
				float(toolSegment.getPosition().y + selectButton->getArea().y * (i / 3)));
			registerButton(selectButton);
			registerSelector(selectButton);
		}
		selectionNameText = Interface::createText("", { midSegment.getPosition().x+2, midSegment.getPosition().y },
			26, sf::Color::Black, sf::Text::Style::Bold);

		auto leftSwitch = std::make_shared<cInstrumentDirectional>(shared_from_this(), &keyPairs[0], "SwitchButtonLeft", SwipeDirection::kLeft);
		leftSwitch->setPosition(switcherSegment.getPosition());
		registerButton(leftSwitch);

		auto rightSwitch = std::make_shared<cInstrumentDirectional>(shared_from_this(), &keyPairs[1], "SwitchButtonRight", SwipeDirection::kRight);
		rightSwitch->setPosition(float(switcherSegment.getPosition().x + leftSwitch->getArea().x), switcherSegment.getPosition().y);
		registerButton(rightSwitch);
	}

	void cSelectorWindow::swipeSelectors(SwipeDirection direction)
	{
		for (auto selector : selectors) {
			selector->actionDisabled();
		}

		if (direction == SwipeDirection::kRight) {
			shownIndex += int(selectors.size());
			shownIndex = (shownIndex >= soundGenFileNames.size())
				? 0
				: shownIndex;
		}

		if (direction == SwipeDirection::kLeft) {
			shownIndex -= int(selectors.size());
			shownIndex = (shownIndex < 0)
				? int(soundGenFileNames.size() - (soundGenFileNames.size() % selectors.size()))
				: shownIndex;
		}

		for (unsigned int i = 0; i < selectors.size(); i++) {
			shownIndex + i < int(soundGenFileNames.size())
				? selectors[i]->setFileName(soundGenFileNames[unsigned int(shownIndex + i)])
				: selectors[i]->setFileName("");
		}
		for (auto selector : selectors) {
			if (selector->getFileName() == "") {
				selector->texture.loadFromFile(std::string(PATH_DEFAULTS::texture));
			}
			selector->actionIdle();
		}
	}

	//cSelectorWindow* cSelectorWindow::instantiateSelectorWindow()
	//{
	//	return pSelectorInstance
	//		? pSelectorInstance
	//		: new cSelectorWindow(ID_WINDOW::instrumentSelect);
	//}

	void cSelectorWindow::openWindow(const std::string name)
	{
		shownIndex = 0;
		IManagedWindow::openWindow(name);
		readFiles();
		swipeSelectors(SwipeDirection::kNoMotion);
		enableButtons();
	}

	bool cSelectorWindow::updateFocused(bool delayedDisplay)
	{
		if (!IManagedWindow::updateFocused(true))
			return false;
		draw(selectionNameText);
		states = windowStates(ENUM::removeFlag(states, windowStates::kRequiresRedraw));
		display();
		return true;
	}

	void cSelectorWindow::closeWindow()
	{
		IManagedWindow::closeWindow();
		soundGenFileNames.clear();
		selectionNameText.setString("");
		for (auto const& [key, button] : buttons) {
			if (button && dynamic_pointer_cast<cInstrumentSelectButton>(button)) { // Only reset selectors, as they can dynamically change
				button->texture.loadFromFile(std::string(PATH_ASSET::AnimatedTexture) + "Instruments/instrumentDefault.png");
			}
		}
		cWindowManager::enableKeysByID(ID_WINDOW::mainPianoBoard);
	}

	void cSelectorWindow::setHoveredText(const std::string& text)
	{
		selectionNameText.setString(text);
	}

	void cSelectorWindow::readFiles()
	{
		soundGenFileNames.clear();
		std::string extension(NAME_EXTENSION::soundGen);
		for (auto& p : std::filesystem::recursive_directory_iterator(PATH_ASSET::SoundPresets))
		{
			if (p.path().extension() == extension)
				soundGenFileNames.push_back(p.path().stem().string());
		}
	}

	void cSelectorWindow::registerSelector(std::shared_ptr<cInstrumentSelectButton> selector)
	{
		selectors.push_back(selector);
	}


	bool cInstrumentSelectButton::actionIdle()
	{
		if (fileName == "") {
			actionDisabled();
			return false;
		}
		if (!IManagedButton::actionIdle()) return false;
		return true;
	}

	bool cInstrumentSelectButton::actionHovered()
	{
		if (IManagedButton::actionHovered()) {
			dynamic_pointer_cast<cSelectorWindow>(pParentWindow.lock())->setHoveredText(fileName);
			return true;
		}
		return false;
	}


	bool cInstrumentSelectButton::actionReleased(bool isEventFromMouse)
	{
		if (!IManagedButton::actionReleased(isEventFromMouse)) 
			return false;
		pParentWindow.lock()->close();
		assert(!pParentWindow.expired());
		dynamic_pointer_cast<Instrument::I_Instrument>(cWindowManager::getWindowByID(ID_WINDOW::mainPianoBoard).lock())->addSoundToNotes(fileName);
		cWindowManager::enableKeysByID(ID_WINDOW::mainPianoBoard);
		return true;
	}


	void cInstrumentSelectButton::setFileName(const std::string& name)
	{
		fileName = name;
		if (name != "") {
			if (!texture.loadFromFile(std::string(PATH_ASSET::AnimatedTexture) + "Instruments/" + name + ".png")) {
				texture.loadFromFile(std::string(PATH_ASSET::AnimatedTexture) + "Instruments/instrumentDefault.png");
			};
			setTexture(texture);
			setButtonState(IManagedButton::buttonState::kIdle);
		}
	}
	const std::string& cInstrumentSelectButton::getFileName()
	{
		return fileName;
	}

	bool cInstrumentDirectional::actionReleased(bool isEventFromMouse)
	{
		if (!IManagedButton::actionReleased(isEventFromMouse)) return false;
		dynamic_pointer_cast<cSelectorWindow>(pParentWindow.lock())->swipeSelectors(direction);
		return true;
	}
}