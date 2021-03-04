//////////////////////////////////////////////////////////////////////////////
//
//	Interface::cInputEventHandler
//
//  Class maps used user-caused events.
//	Creates identifier look-up to dissolve if-tree.

#pragma once

namespace Interface {
	typedef void(*InputEvent_t)(IManagedWindow*, sf::Event);

	class cInputEventHandler {
	public:
		static InputEvent_t getEventFunction(sf::Event::EventType inputEvent);
	private:
		static std::map<sf::Event::EventType, InputEvent_t> inputEvents_Map;

		static void userMouseMoved(IManagedWindow* window, sf::Event windowEvent);
		static void userMouseButtonPressed(IManagedWindow* window, sf::Event windowEvent);
		static void userMouseButtonReleased(IManagedWindow* window, sf::Event windowEvent);
		static void userKeyPressed(IManagedWindow* window, sf::Event windowEvent);
		static void userKeyReleased(IManagedWindow* window, sf::Event windowEvent);
	};
}