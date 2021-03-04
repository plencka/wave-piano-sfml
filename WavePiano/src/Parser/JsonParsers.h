//////////////////////////////////////////////////////////////////////////////
//
//	Defined data stored inside JSON structured files.
//	Additional parsing for data.
//

#pragma once
#include "../Common/Commons.h"
#include <iostream>
#include <fstream>
#include <rapidjson/document.h>
#include <rapidjson/stringbuffer.h>


namespace Parser {

	bool fileToString(std::string fileLocation, std::string *fileData);
	struct AnimatedSpriteData {
	public:
		std::string textureLocation = std::string(PATH_DEFAULTS::texture);
		sf::Vector2u tilingSize = { 2,1 };
		int frames = 2;
		int framerate = 1;

		static const AnimatedSpriteData parseFile(std::string fileName);
	};

	struct SoundGenData {
	public:
		uint32_t waveNameHashed = HASH::compileFNVHash("Sine");
		double startFrequency = 50;
		double amplitude = 1;
		float gainIncrease = 50;
		float gainDecrease = 25;
		double noteIncrease = 50;
		int aParam = 0;

		static const SoundGenData parseFile(std::string fileName);
	};

}