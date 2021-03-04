#include "Instrument.h"

namespace Instrument {

	void I_Instrument::addSoundToNotes(std::string fileName)
	{
		soundParameters = Parser::SoundGenData::parseFile(fileName);
		for (int i = 0; i < notes.size(); i++) {
			notes[i].lock()->generateAudioSample(i);
		}
	}

	void I_Instrument::registerNote(std::shared_ptr<cInstrumentNote> note)
	{
		notes.push_back(note);
	}

	std::thread cInstrumentNote::thread_Sample(unsigned int notePlacement, unsigned int thread, std::vector<sf::Int16>* container)
	{
		return std::thread([this, thread, container, notePlacement] {
			unsigned int threadCount = std::thread::hardware_concurrency();
			int steps = (SAMPLING / threadCount);
			int divisionLoss = (thread + 1) % threadCount == 0
				? divisionLoss = SAMPLING - (steps * threadCount)
				: divisionLoss = 0;
			for (unsigned int i = steps * thread; i < steps * (thread + 1) + divisionLoss; i++) {
				container->push_back(WaveSynth::waveSample(notePlacement, i, pParentInstrument.lock()->soundParameters));
			}
		});
	}

	void cInstrumentNote::generateAudioSample(unsigned int notePlacement)
	{
		std::vector<sf::Int16> samples;
		std::vector<std::thread> threads;
		unsigned int threadCount = std::thread::hardware_concurrency();
		std::vector<std::vector<sf::Int16>*> sampleChunks;
		for (unsigned int i = 0; i < threadCount; i++) {
			std::vector<sf::Int16>* chunk = new std::vector<sf::Int16>{};
			sampleChunks.push_back(chunk);
			threads.push_back(thread_Sample(notePlacement, i, chunk));
		}
		for (unsigned int i = 0; i < threadCount; i++) {
			threads[i].join();
		}
		for (unsigned int i = 0; i < threadCount; i++) {
			samples.insert(samples.end(), sampleChunks[i]->begin(), sampleChunks[i]->end());
		}
		for (auto chunk : sampleChunks) {
			delete(chunk);
		}
		sampleChunks.clear();

		audioBuffer.loadFromSamples(&samples[0], samples.size(), 1, SAMPLING);
		sound.setBuffer(audioBuffer);
		sound.setLoop(true);
		sound.setVolume(0);
	}

	void cInstrumentNote::audioPlay()
	{
		if (sound.getStatus() != sf::Sound::Status::Playing) {
			sound.play();
		}
	}

	void cInstrumentNote::audioStop()
	{
		sound.setVolume(0);
		sound.stop();
	}

	void cInstrumentNote::gainIncrease(float deltaTime)
	{
		float volumeIncrease = sound.getVolume() + (deltaTime * pParentInstrument.lock()->soundParameters.gainIncrease);
		if (volumeIncrease >= VOLUME_MAX) {
			sound.setVolume(VOLUME_MAX);
		}
		else {
			sound.setVolume(volumeIncrease);
		}
	}

	bool cInstrumentNote::gainDecrease(float deltaTime)
	{
		float volumeDecrease = sound.getVolume() - (deltaTime * pParentInstrument.lock()->soundParameters.gainDecrease);
		if (volumeDecrease <= 0) {
			audioStop();
			return true;
		}
		else {
			sound.setVolume(volumeDecrease);
		}
		return false;
	}
}