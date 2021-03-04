#include "ManagedGUI.h"
namespace Interface {

	sf::Text createText(std::string text, sf::Vector2f position,
		unsigned int charSize, sf::Color textColor, sf::Text::Style textStyle)
	{
		sf::Text textContainer(text.c_str(), GUI_FONT::generic);
		textContainer.setPosition(position.x, position.y);
		textContainer.setCharacterSize(charSize);
		textContainer.setFillColor(textColor);
		textContainer.setStyle(textStyle);
		return textContainer;
	}

	IManagedButton::~IManagedButton()
	{
		pressKey = nullptr;
		SpriteAnimator::cAnimationManager::removeReference(pOriginInstance);
	}

	bool IManagedButton::contains(int x, int y)
	{
		auto buttonArea = getArea();
		auto buttonPosition = getPosition();
		if (x <= buttonPosition.x || x > buttonArea.x + buttonPosition.x) {
			actionUnHovered();
			return false;
		}
		if (y <= buttonPosition.y || y > buttonArea.y + buttonPosition.y) {
			actionUnHovered();
			return false;
		}
		actionHovered();
		return true;
	}

	sf::Vector2f IManagedButton::getArea()
	{
		if (tiles.x == 0) {
			tiles.x = 1;
			debugPrintF("X tile texture size was 0.");
		}
		if (tiles.y == 0) {
			tiles.y = 1;
			debugPrintF("Y tile texture size was 0.");
		}
		return sf::Vector2f((getTexture()->getSize().x * getScale().x) / tiles.x, (getTexture()->getSize().y * getScale().y) / tiles.y);
	}

	void IManagedButton::enableSelf()
	{
		setButtonState(buttonState::kIdle);
	}

	IManagedButton::buttonState IManagedButton::getButtonState()
	{
		return state;
	}

	void IManagedButton::setButtonState(buttonState bState)
	{
		state = bState;
		setFrame((unsigned int)bState);
		pParentWindow.lock()->requestRedraw();
	}

	IManagedButton::IManagedButton(std::weak_ptr<IManagedWindow> parentWindowArg, const KeyPair* key, const std::string& spriteFile) : cAnimatedSprite(spriteFile)
	{
		pParentWindow = parentWindowArg;
		pressKey = key;
		actionDisabled();
	}

	bool IManagedButton::actionIdle()
	{
		if (getButtonState() == buttonState::kDisabled || getButtonState() == buttonState::kIdle)
			return false;

		setButtonState(buttonState::kIdle);
		return true;
	}

	bool IManagedButton::actionHovered()
	{
		if (getButtonState() == buttonState::kDisabled)
			return false;
		setColor(GUI_COLOR::hover);
		pParentWindow.lock()->requestRedraw();
		inputMod = inputModifier(ENUM::addFlag(inputMod, inputModifier::kHovered));
		return true;
	}

	bool IManagedButton::actionUnHovered()
	{
		if (!ENUM::hasFlag(inputMod, inputModifier::kHovered)) {
			return false;
		}
		setColor(sf::Color::White);
		pParentWindow.lock()->requestRedraw();
		inputMod = inputModifier(ENUM::removeFlag(inputMod, inputModifier::kHovered));
		return true;
	}

	bool IManagedButton::actionPressed(bool isEventFromMouse)
	{
		if (getButtonState() == buttonState::kDisabled)
			return false;

		if (isEventFromMouse) {
			sourceStates = pressSource(ENUM::addFlag(sourceStates, pressSource::kMouse));
		}
		else {
			sourceStates = pressSource(ENUM::addFlag(sourceStates, pressSource::kKeyboard));
		}

		setButtonState(buttonState::kPressed);
		return true;
	}

	bool IManagedButton::actionReleased(bool isEventFromMouse)
	{
		if (getButtonState() != buttonState::kPressed)
			return false;

		if (isEventFromMouse) {
			sourceStates = pressSource(ENUM::removeFlag(sourceStates, pressSource::kMouse));
		}
		else {
			sourceStates = pressSource(ENUM::removeFlag(sourceStates, pressSource::kKeyboard));
		}

		if (sourceStates != pressSource::kNotPressed)
			return false;

		setButtonState(buttonState::kActive);
		return true;
	}

	bool IManagedButton::actionDisabled()
	{
		setButtonState(buttonState::kDisabled);
		return true;
	}

	bool IManagedButton::actionActive(bool oneActionPerRelease)
	{
		if (oneActionPerRelease) {
			return actionIdle();
		}
		return true;
	}

	std::map<sf::Event::EventType, InputEvent_t> cInputEventHandler::inputEvents_Map{
			std::make_pair(sf::Event::MouseMoved,  cInputEventHandler::userMouseMoved),
			std::make_pair(sf::Event::MouseButtonPressed,  cInputEventHandler::userMouseButtonPressed),
			std::make_pair(sf::Event::MouseButtonReleased,  cInputEventHandler::userMouseButtonReleased),
			std::make_pair(sf::Event::KeyPressed,  cInputEventHandler::userKeyPressed),
			std::make_pair(sf::Event::KeyReleased,  cInputEventHandler::userKeyReleased),
	};

	InputEvent_t cInputEventHandler::getEventFunction(sf::Event::EventType inputEvent)
	{
		auto it = inputEvents_Map.find(inputEvent);
		return it != inputEvents_Map.end()
			? it->second : nullptr;
	}

	void cInputEventHandler::userMouseMoved(IManagedWindow* window, sf::Event windowEvent)
	{
		for (auto const& [key, button] : window->getButtons())
		{
			button->contains(sf::Mouse::getPosition(*window).x, sf::Mouse::getPosition(*window).y);
		}
	}

	void cInputEventHandler::userMouseButtonPressed(IManagedWindow* window, sf::Event windowEvent)
	{
		if (windowEvent.mouseButton.button == sf::Mouse::Left) {
			window->states = IManagedWindow::windowStates(ENUM::addFlag(window->states, IManagedWindow::windowStates::kLeftMousePressed));
			for (auto const& [key, button] : window->getButtons()) {
				if (button->inputMod & IManagedButton::inputModifier::kLazyMousePress) {
					continue;
				}
				if (button->contains(sf::Mouse::getPosition(*window).x, sf::Mouse::getPosition(*window).y)) {
					button->actionPressed(true);
				}
			}
		}
	}

	void cInputEventHandler::userMouseButtonReleased(IManagedWindow* window, sf::Event windowEvent)
	{
		if (windowEvent.mouseButton.button == sf::Mouse::Left) {
			window->states = IManagedWindow::windowStates(ENUM::removeFlag(window->states, IManagedWindow::windowStates::kLeftMousePressed));
			for (auto const& [key, button] : window->getButtons()) {
				if(!ENUM::hasFlag(button->inputMod, IManagedButton::inputModifier::kLazyMousePress))
					button->actionReleased(true);
			}
		}
	}

	void cInputEventHandler::userKeyPressed(IManagedWindow* window, sf::Event windowEvent)
	{
		for (auto const& [key, button] : window->getButtons()) {
			if (windowEvent.key.code == button->pressKey->keyID) {
				if (ENUM::hasFlag(button->inputMod, IManagedButton::inputModifier::kLazyMousePress)) {
					button->inputMod = IManagedButton::inputModifier(ENUM::addFlag(button->inputMod, IManagedButton::inputModifier::kKeyHeld));
				}
				else {
					button->actionPressed(false);
				}
			}
		}
	}

	void cInputEventHandler::userKeyReleased(IManagedWindow* window, sf::Event windowEvent)
	{
		for (auto const& [key, button] : window->getButtons()) {
			if (windowEvent.key.code == button->pressKey->keyID) {
				if (ENUM::hasFlag(button->inputMod, IManagedButton::inputModifier::kLazyMousePress)) {
					button->inputMod = IManagedButton::inputModifier(ENUM::removeFlag(button->inputMod, IManagedButton::inputModifier::kKeyHeld));
				}
				else {
					button->actionReleased(false);
				}
			}
		}
	}

	IManagedWindow::~IManagedWindow()
	{
		buttons.empty();
		buttons.clear();
	}

	//std::shared_ptr<IManagedWindow> IManagedWindow::instantiate(std::shared_ptr<IManagedWindow> instance)
	//{
	//	return std::shared_ptr<IManagedWindow>();
	//}

	sf::RectangleShape IManagedWindow::createSegment(sf::Vector2f size)
	{
		sf::RectangleShape segmentShade(sf::Vector2f(size.x, size.y));
		segmentShade.setFillColor(GUI_COLOR::segmentShade);
		sf::RectangleShape segment(sf::Vector2f(size.x, size.y));
		segment.setFillColor(GUI_COLOR::segment);
		if (segments.size() > 0) {
			size_t index = segments.size() - 1;
			segment.setPosition(GUI_PADDING::defaultLeft, segments[index].getPosition().y
				+ segments[index].getSize().y + GUI_PADDING::defaultTop);
		}
		else {
			segment.setPosition(GUI_PADDING::defaultLeft, GUI_PADDING::defaultTop);
		}
		segmentShade.setPosition(segment.getPosition().x + GUI_PADDING::defaultLeft, segment.getPosition().y + GUI_PADDING::defaultLeft);
		segments.push_back(segmentShade);
		segments.push_back(segment);
		return segment;
	}

	std::map<uint32_t, std::shared_ptr<IManagedButton>> IManagedWindow::getButtons()
	{
		return std::map<uint32_t, std::shared_ptr<IManagedButton>>(buttons);
	}

	void IManagedWindow::openWindow(const std::string windowTitle)
	{
		create(sf::VideoMode(defaultSize.x, defaultSize.y), windowTitle, sf::Style::Titlebar | sf::Style::Close);
		states = windowStates(ENUM::addFlag(states, windowStates::kIsFocused));
		enableButtons();
	}


	void IManagedWindow::updateEvent(sf::Event windowEvent)
	{
		if (windowEvent.type == sf::Event::Closed) {
			closeWindow();
			return;
		}
		else if (windowEvent.type == sf::Event::GainedFocus)
			states = windowStates(ENUM::addFlag(states, windowStates::kIsFocused));
		else if (windowEvent.type == sf::Event::LostFocus)
			states = windowStates(ENUM::removeFlag(states, windowStates::kIsFocused));

		if (!ENUM::hasFlag(states, windowStates::kIsFocused))
			return;

		if (auto inputEvent = cInputEventHandler::getEventFunction(windowEvent.type)) {
			inputEvent(this, windowEvent);
		}

	}

	void IManagedWindow::closeWindow()
	{
		close();
	}

	void IManagedWindow::registerButton(std::shared_ptr<IManagedButton> button)
	{
		assert(buttons.insert(std::make_pair(HASH::getFNVHash(button->pressKey->keyName), button)).second);
	}

	void IManagedWindow::updateWhenOpen()
	{
		if (isOpen()) {
			sf::Event winEvent;
			while (pollEvent(winEvent)) {
				updateEvent(winEvent);
			}
			if (ENUM::hasFlag(states, windowStates::kIsFocused)) {
				updateFocused();
			}
			updateAlways();
		}
	}

	void IManagedWindow::enableButtons()
	{
		for (auto const& [key, button] : buttons)
		{
			button->enableSelf();
			button->actionIdle();
		}
	}

	void IManagedWindow::disableButtons()
	{
		for (auto const& [key, button] : buttons)
		{
			button->actionDisabled();
		}
	}

	void IManagedWindow::requestRedraw()
	{
		states = windowStates(ENUM::addFlag(states, windowStates::kRequiresRedraw));
	}

	bool IManagedWindow::updateFocused(bool delayedDisplay)
	{
		if (ENUM::hasFlag(states, windowStates::kRequiresRedraw)) {
			clear(GUI_COLOR::background);
			for (auto shape : segments) {
				draw(shape);
			}
			for (auto const& [key, button] : buttons) {
				if (!button)
					continue;

				draw(*button);
			}
			if (!delayedDisplay) {
				states = windowStates(ENUM::removeFlag(states, windowStates::kRequiresRedraw));
				display();
			}
			return true;
		}
		else {
			return false;
		}
	}

	void IManagedWindow::updateAlways()
	{
		for (auto const& [key, button] : buttons) {
			if (ENUM::hasFlag(button->inputMod, IManagedButton::inputModifier::kLazyMousePress))
				if (ENUM::hasFlag(states, windowStates::kLeftMousePressed)) {
					if (button->contains(sf::Mouse::getPosition(*this).x, sf::Mouse::getPosition(*this).y))
						button->actionPressed(true);
				}

			if (!button->contains(sf::Mouse::getPosition(*this).x, sf::Mouse::getPosition(*this).y) || !ENUM::hasFlag(states, windowStates::kLeftMousePressed))
				button->actionReleased(true);

			if (ENUM::hasFlag(button->inputMod, IManagedButton::inputModifier::kKeyHeld)) {
				button->actionPressed(false);
			}
			else {
				button->actionReleased(false);
			}
			if (button->getButtonState() == IManagedButton::buttonState::kActive) {
				button->actionActive();
			}
		}
	}
}