//////////////////////////////////////////////////////////////////////////////
//
//  Collection of names and identifiers.
//
//	Changes to names should match files used by the application.
//	Identifiers compile with application.
//	To create dynamic identifiers, use non-constexpr function.
//


#pragma once
#include "Utility.h"

#define ID_WINDOW WaverPiano::ID::Window
#define ID_BUTTON WaverPiano::ID::Button
#define ID_LOCALE WaverPiano::ID::Locale
#define NAME_EXTENSION WaverPiano::Names::Extension

namespace WaverPiano {
	namespace ID {
		namespace Window {
			constexpr uint32_t mainPianoBoard = HASH::compileFNVHash("MainWindow");
			constexpr uint32_t instrumentSelect = HASH::compileFNVHash("InstrumentSelectWindow");
		}

		namespace Button {
			constexpr uint32_t pianoKey = HASH::compileFNVHash("PianoKeyButton");
			constexpr uint32_t instrumentSelect = HASH::compileFNVHash("InstrumentSelectButton");
			constexpr uint32_t selectorUp = HASH::compileFNVHash("SelectorUpButton");
			constexpr uint32_t switcherLeft = HASH::compileFNVHash("SwitchLeftButton");
			constexpr uint32_t switcherRight = HASH::compileFNVHash("SwitchRightButton");
		}

		namespace Locale {
		}
	}

	namespace Names {
		namespace Extension {
			extern const char* soundGen;
			extern const char* animatedSprite;
		}
	}
}