//////////////////////////////////////////////////////////////////////////////
//
//  Remapped SFML keybinds.
//
//	SFML A-Z Key class isn't defined in order.
//	Above prevented implementation of iterated piano creation.
//

#pragma once
#include <array>
#include <SFML/Graphics.hpp>

//Issues with std::array within namespace
	struct KeyPair {
		const char* keyName;
		const sf::Keyboard::Key keyID;
		constexpr KeyPair(const char* keyPrintName, const sf::Keyboard::Key keyIdentifier) :
			keyName(keyPrintName),
			keyID(keyIdentifier) {};
	};

	constexpr std::array<KeyPair, 36> keyPairs{
			KeyPair("Q", sf::Keyboard::Q), //0
			KeyPair("W", sf::Keyboard::W),
			KeyPair("E", sf::Keyboard::E), //2
			KeyPair("R", sf::Keyboard::R),
			KeyPair("T", sf::Keyboard::T), //4
			KeyPair("Y", sf::Keyboard::Y),
			KeyPair("U", sf::Keyboard::U), //6
			KeyPair("I", sf::Keyboard::I),
			KeyPair("O", sf::Keyboard::O), //8
			KeyPair("P", sf::Keyboard::P),
			KeyPair("A", sf::Keyboard::A), //10
			KeyPair("S", sf::Keyboard::S),
			KeyPair("D", sf::Keyboard::D), //12
			KeyPair("F", sf::Keyboard::F),
			KeyPair("G", sf::Keyboard::G), //14
			KeyPair("H", sf::Keyboard::H),
			KeyPair("J", sf::Keyboard::J), //16
			KeyPair("K", sf::Keyboard::K),
			KeyPair("L", sf::Keyboard::L), //18
			KeyPair("Z", sf::Keyboard::Z),
			KeyPair("X", sf::Keyboard::X), //20
			KeyPair("C", sf::Keyboard::C),
			KeyPair("V", sf::Keyboard::V), //22
			KeyPair("B", sf::Keyboard::B),
			KeyPair("N", sf::Keyboard::N), //24
			KeyPair("M", sf::Keyboard::M),
			KeyPair("ESC", sf::Keyboard::Escape), //26
			KeyPair("Num1", sf::Keyboard::Num1),
			KeyPair("Num2", sf::Keyboard::Num2),
			KeyPair("Num3", sf::Keyboard::Num3),
			KeyPair("Num4", sf::Keyboard::Num4),
			KeyPair("Num5", sf::Keyboard::Num5),
			KeyPair("Num6", sf::Keyboard::Num6),
			KeyPair("Num7", sf::Keyboard::Num7),
			KeyPair("Num8", sf::Keyboard::Num8),
			KeyPair("Num9", sf::Keyboard::Num9),
	};

	namespace KeyRemap {
	constexpr unsigned int getNumberOffset() {
		for (int i = 0; i < keyPairs.size(); i++) {
			if (keyPairs[i].keyID == sf::Keyboard::Num1) {
				return i;
			}
		}
		return 0;
	}
}
