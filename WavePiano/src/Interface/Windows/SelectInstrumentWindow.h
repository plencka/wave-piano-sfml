//////////////////////////////////////////////////////////////////////////////
//
//	Interface::cSelectorWindow
//
//  Side application Window.
//	Enabled whenever user has a need to choose Instrument.
//	Window looks up files for instrument presets and displays them.
//

#pragma once
#include <filesystem>
#include "SelectInstrumentWindowButtons.h"

namespace Interface
{
	class cSelectorWindow final : public IManagedWindow, public std::enable_shared_from_this<IManagedWindow>
	{
	private:
		int shownIndex = 0;
		sf::Text selectionNameText;
		std::vector<std::string> soundGenFileNames;
		std::vector<std::shared_ptr<cInstrumentSelectButton>> selectors;

	private:
		void readFiles();
		void registerSelector(std::shared_ptr<cInstrumentSelectButton> selector);
	public:
		cSelectorWindow() {
			titleName = "Select instrument";
			defaultSize = { 300, 370 };
		}
		virtual void deploy() override;
		virtual constexpr uint32_t getWindowID() override {
			return ID_WINDOW::instrumentSelect;
		};
		void swipeSelectors(SwipeDirection direction);
		void setHoveredText(const std::string& text);
		virtual void openWindow(const std::string name) override;
		virtual bool updateFocused(bool delayedDisplay = false) override;
		virtual void closeWindow() override;
	};
}
