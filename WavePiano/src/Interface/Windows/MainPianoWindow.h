//////////////////////////////////////////////////////////////////////////////
//
//	Interface::cMainPianoWindow
//
//  Main application Window.
//	Stores piano board and general toolbar for application.
//	Closing this window causes application exit.
//

#pragma once
#include "MainPianoWindowButtons.h"
namespace Interface
{
	class cMainPianoWindow final : public IManagedWindow, public Instrument::I_Instrument, public std::enable_shared_from_this<IManagedWindow>
	{
		std::vector<sf::Text> texts;
	private:
		virtual bool updateFocused(bool delayedDisplay = false) override;
	public:
		cMainPianoWindow()
		{
			titleName = "My Piano";
			defaultSize = { 1300,250 };
		}
		virtual constexpr uint32_t getWindowID() override {
			return ID_WINDOW::mainPianoBoard;
		};
		virtual void deploy() override;
		virtual void openWindow(const std::string windowTitle) override;
		virtual void closeWindow() override;
	};
};

