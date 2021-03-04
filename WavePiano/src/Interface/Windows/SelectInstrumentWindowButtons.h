//////////////////////////////////////////////////////////////////////////////
//
//	Button definitions for Interface::cSelectorWindow
//

#pragma once

namespace Interface {
	enum class SwipeDirection {
		kNoMotion = 0,
		kRight = 1,
		kLeft = 2,
	};

	class cInstrumentSelectButton : public IManagedButton {
		std::string fileName;

	public:
		cInstrumentSelectButton(std::shared_ptr<IManagedWindow> pParentWindow, const KeyPair* key, const std::string& spriteFile)
			: IManagedButton(pParentWindow, key, spriteFile) {};
		void setFileName(const std::string& name);
		const std::string& getFileName();
		bool actionIdle() override;
		bool actionHovered() override;
		bool actionReleased(bool isEventFromMouse = false) override;
	};

	class cInstrumentDirectional : public IManagedButton {
	private:
		SwipeDirection direction = SwipeDirection::kNoMotion;
	public:
		cInstrumentDirectional(std::shared_ptr<IManagedWindow> pParentWindow, const KeyPair* key, const std::string& spriteFile, SwipeDirection swipeDir)
			: IManagedButton(pParentWindow, key, spriteFile) {
			direction = swipeDir;
		};
		bool actionReleased(bool isEventFromMouse = false) override;
	};

}