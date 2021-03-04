//////////////////////////////////////////////////////////////////////////////
//
//  Extended definitions for Interface creation.
//
//	Custom colors, paddings etc. are defined here.
//	To Do: Deprecate and use more customizable solution.
//


#pragma once
#include <SFML/Graphics.hpp>

#define GUI_COLOR WaverPiano::Interface::Color
#define GUI_PADDING WaverPiano::Interface::Padding
#define GUI_FONT WaverPiano::Interface::Font

namespace WaverPiano {
	namespace Interface {
		namespace Font {
			extern sf::Font generic;
		}
		namespace Color {
			extern const sf::Color hover;
			extern const sf::Color background;
			extern const sf::Color segment;
			extern const sf::Color segmentShade;
			extern const sf::Color warning;
			extern const sf::Color critical;
			extern const sf::Color visibleColor;
		}

		namespace Padding {
			constexpr float defaultTop = 0;
			constexpr float defaultLeft = 0;
			constexpr float toolboxTop = 0.0;
			constexpr float toolboxLeft = 0.0;
		}
	}
}