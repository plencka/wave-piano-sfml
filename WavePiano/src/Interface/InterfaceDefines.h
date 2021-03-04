//////////////////////////////////////////////////////////////////////////////
//
//	Generic SFML functions and Interface definitions.
//
//	Concentrates most used relevant SFML functions.
//

#pragma once
#include "../Common/Commons.h"
namespace Interface {
	class IManagedButton;
	class IManagedWindow;

	sf::Text createText(std::string text, sf::Vector2f position,
		unsigned int charSize = 25, sf::Color textColor = sf::Color::Black, sf::Text::Style textStyle = sf::Text::Regular);

}