//////////////////////////////////////////////////////////////////////////////
//
//	SpriteAnimator
//
//  Extends SFML Sprite class with functions related to sprite sheet animation.
//	Caches instances of animated sprite data to improve overall performance.
//

#pragma once
#include <thread>
#include "WaveSynth.h"

namespace Instrument
{
#define VOLUME_MAX 50.0
#define VOLUME_MIN 0.0
	class cInstrumentNote;

	class I_Instrument {
	private:
		std::vector<std::weak_ptr<cInstrumentNote>> notes;
	public:
		Parser::SoundGenData soundParameters;

	protected:
		I_Instrument() {};
	public:
		void addSoundToNotes(std::string fileName);
		void registerNote(std::shared_ptr<cInstrumentNote> note);
	};

	class cInstrumentNote {
	private:
		sf::Sound sound;
		sf::SoundBuffer audioBuffer;
	protected:
		std::weak_ptr<I_Instrument> pParentInstrument;
	private:
		std::thread thread_Sample(unsigned int notePlacement, unsigned int thread, std::vector<sf::Int16>* container);
	protected:
		cInstrumentNote() {};
		void audioPlay();
		void audioStop();
		void gainIncrease(float deltaTime);
		bool gainDecrease(float deltaTime);
	public:
		void generateAudioSample(unsigned int notePlacement);
	};

};

