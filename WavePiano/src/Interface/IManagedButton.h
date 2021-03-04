//////////////////////////////////////////////////////////////////////////////
//
//	Interface::IManagedButton.
//
//  Abstract class for creating user interface buttons.
//

#pragma once

namespace Interface {
	class IManagedButton : public SpriteAnimator::cAnimatedSprite
	{
	public:
		enum class buttonState {
			kIdle = 0,
			kActive = 1,
			kPressed = 2,
			kDisabled = 3,
		};

		enum inputModifier {
			kNone = 0,
			kHovered = 1,
			kLazyMousePress = 2,
			kKeyHeld = 4,
		};

		enum pressSource {
			kNotPressed = 0,
			kMouse = 1,
			kKeyboard = 2,
		};

	private:
		buttonState state = buttonState::kDisabled;
	protected:
		std::weak_ptr<IManagedWindow> pParentWindow;
		pressSource sourceStates = pressSource::kNotPressed;
	public:
		uint32_t buttonID;
		const KeyPair* pressKey;
		inputModifier inputMod = inputModifier::kNone;

	protected:
		IManagedButton(std::weak_ptr<IManagedWindow> pParentWindow, const KeyPair* key, const std::string& spriteFile);
	public:
		~IManagedButton();
		bool contains(int x, int y);
		sf::Vector2f getArea();
		void enableSelf();
		buttonState getButtonState();
		void setButtonState(buttonState bState);
		virtual bool actionIdle();
		virtual bool actionHovered();
		virtual bool actionUnHovered();
		virtual bool actionPressed(bool isEventFromMouse = false);
		virtual bool actionReleased(bool isEventFromMouse = false);
		virtual bool actionDisabled();
		virtual bool actionActive(bool oneActionPerRelease = true);
	};
}