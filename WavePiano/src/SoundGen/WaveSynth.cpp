#include "WaveSynth.h"

namespace WaveSynth
{
	namespace WaveUtils {
		double getCycle(double time, double tickFreq)
		{
			return time / tickFreq;
		}
	}
	sf::Int16 waveSample(int noteOffset, int sampleTime, Parser::SoundGenData soundData)
	{
		return static_cast<sf::Int16>((cWave::getWaveByID(soundData.waveNameHashed)(noteOffset, sampleTime, soundData)) * SHRT_MAX * soundData.amplitude);
	}

	std::map<uint32_t, Periodic_MathFunction_t> cWave::waveFunctions{
#if _DEBUG
			std::make_pair(HASH::compileFNVHash("Test"),  cWave::test),
#endif
			std::make_pair(HASH::compileFNVHash("Sine"),  cWave::sine),
			std::make_pair(HASH::compileFNVHash("Alien"),  cWave::alien),
			std::make_pair(HASH::compileFNVHash("Square"),  cWave::square),
			std::make_pair(HASH::compileFNVHash("Pluck"),  cWave::pluck),
	};

	Periodic_MathFunction_t cWave::getWaveByID(uint32_t id)
	{
		auto waveFunction = cWave::sine;
		auto it = cWave::waveFunctions.find(id);
		if (it != cWave::waveFunctions.end())
			waveFunction = it->second;
		return waveFunction;
	}

#if _DEBUG
	double cWave::test(int noteOffset, int sampleTime, Parser::SoundGenData soundData)
	{
		double rad = PI_2 * WaveUtils::getCycle(sampleTime,
			SAMPLING / (soundData.startFrequency + (noteOffset * soundData.noteIncrease)));
		return sin(sin(rad) + sin(rad - 25) - 25);
	}
#endif

	double cWave::pluck(int noteOffset, int sampleTime, Parser::SoundGenData soundData)
	{
		double rad = PI_2 * WaveUtils::getCycle(sampleTime, 
			SAMPLING / (soundData.startFrequency + (noteOffset * soundData.noteIncrease)));
		return sin(((PI_2 * sin(rad)) + (soundData.aParam * cos(PI_2 * WaveUtils::getCycle(sampleTime, SAMPLING)))) + (PI_2 * cos(rad)));
	}

	double cWave::square(int noteOffset, int sampleTime, Parser::SoundGenData soundData)
	{
		double rad = PI_2 * WaveUtils::getCycle(sampleTime,
			SAMPLING / (soundData.startFrequency + (noteOffset * soundData.noteIncrease)));
		return (sin(rad) >= 0)
			? soundData.aParam
			: -soundData.aParam;
	}

	double cWave::alien(int noteOffset, int sampleTime, Parser::SoundGenData soundData)
	{
		double rad = PI_2 * WaveUtils::getCycle(sampleTime,
			SAMPLING / (soundData.startFrequency + (noteOffset * soundData.noteIncrease)));
		return ((sin(rad) >= 0)
			? soundData.aParam
			: -soundData.aParam) * sin(PI_2 * WaveUtils::getCycle(sampleTime, SAMPLING));
	}

	double cWave::sine(int noteOffset, int sampleTime, Parser::SoundGenData soundData)
	{
		double rad = PI_2 * WaveUtils::getCycle(sampleTime,
			SAMPLING / (soundData.startFrequency + noteOffset * soundData.noteIncrease));
		return sin(rad);
	}

};
