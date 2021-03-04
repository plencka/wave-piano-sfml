//////////////////////////////////////////////////////////////////////////////
//
//	Button definitions for Interface::cMainPianoWindow
//

#pragma once
#include "../../SoundGen/Instrument.h"
namespace Interface
{
	class cMainPianoWindow;

	class cButtonPianoKey : public IManagedButton, public Instrument::cInstrumentNote {
	public:
		cButtonPianoKey(std::shared_ptr<IManagedWindow> pParentWindow, const KeyPair* key, const std::string& spriteFile)
			: IManagedButton(pParentWindow, key, spriteFile)
		{
			inputMod = inputModifier(ENUM::addFlag(inputMod, inputModifier::kLazyMousePress));
			pParentInstrument = std::dynamic_pointer_cast<Instrument::I_Instrument>(pParentWindow);
		};
	private:
		virtual bool actionPressed(bool isEventFromMouse = false) override;
		virtual bool actionActive(bool oneActionPerRelease = false) override;
		virtual bool actionDisabled() override;
	};

	class cButtonOpenSelector : public IManagedButton {
	private:
		virtual bool actionActive(bool oneActionPerRelease = false) override;
	public:
		cButtonOpenSelector(std::shared_ptr<IManagedWindow> pParentWindow, const KeyPair* key, const std::string& spriteFile)
			: IManagedButton(pParentWindow, key, spriteFile) {};
	};

}