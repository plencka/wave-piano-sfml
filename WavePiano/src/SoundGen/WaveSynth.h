#pragma once
#define _USE_MATH_DEFINES
#include <SFML/Audio.hpp>
#include "../Parser/JsonParsers.h"
#include <map>


namespace WaveSynth
{
#define SAMPLING 44100
#define PI_2 (2.0 * M_PI)

	typedef double(*Periodic_MathFunction_t)(int, int, Parser::SoundGenData);

	sf::Int16 waveSample(int noteOffset, int sampleTime, Parser::SoundGenData soundData);

	class cWave {
	private:
		static std::map<uint32_t, Periodic_MathFunction_t> waveFunctions;
	public:
		static Periodic_MathFunction_t getWaveByID(uint32_t id);
#if _DEBUG
		static double test(int noteOffset, int sampleTime, Parser::SoundGenData soundData);
#endif
		static double pluck(int noteOffset, int sampleTime, Parser::SoundGenData soundData);
		static double square(int noteOffset, int sampleTime, Parser::SoundGenData soundData);
		static double alien(int noteOffset, int sampleTime, Parser::SoundGenData soundData);
		static double sine(int noteOffset, int sampleTime, Parser::SoundGenData soundData);
	};

	namespace WaveUtils {
		static double getCycle(double time, double tickFreq);
	}
}
