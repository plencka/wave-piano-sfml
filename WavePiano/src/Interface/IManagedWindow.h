//////////////////////////////////////////////////////////////////////////////
//
//	Interface::IManagedWindow
//
//  Abstract class for creating user interface window.
//
#pragma once

namespace Interface {

	class IManagedWindow : public sf::RenderWindow
	{
	public:
		enum windowStates {
			kNone = 0,
			kRequiresRedraw = 1,
			kIsFocused = 2,
			kLeftMousePressed = 4,
		};

	protected:
		sf::Vector2i defaultSize = { 1320,325 };
		std::vector<sf::RectangleShape> segments;
		std::map<uint32_t, std::shared_ptr<IManagedButton>> buttons;
	public:
		std::string titleName = "UnknownTitle";
		windowStates states = windowStates::kNone;
	protected:
		sf::RectangleShape createSegment(sf::Vector2f size);
	public:
		~IManagedWindow();
		virtual constexpr uint32_t getWindowID() {
			return 0;
		};
		virtual void deploy() {};
		std::map<uint32_t, std::shared_ptr<IManagedButton>> getButtons();
		virtual void openWindow(const std::string windowTitle);
		virtual void updateEvent(sf::Event windowEvent);
		virtual bool updateFocused(bool delayedDisplay = false);
		virtual void updateAlways();
		virtual void closeWindow();
		void updateWhenOpen();
		void requestRedraw();

		void registerButton(std::shared_ptr<IManagedButton> button);
		void enableButtons();
		void disableButtons();
	};
}