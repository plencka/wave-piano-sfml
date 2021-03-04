#include "JsonParsers.h"
namespace Parser {

	const AnimatedSpriteData AnimatedSpriteData::parseFile(std::string fileName)
	{
		using namespace rapidjson;
		AnimatedSpriteData data = AnimatedSpriteData();
		std::string stringFileData;
		std::string spriteLocation = std::string(PATH_ASSET::AnimatedSprite) + fileName + std::string(NAME_EXTENSION::animatedSprite);
		Document doc;
		if (!fileToString(spriteLocation, &stringFileData)) {
			debugPrintF("Couldn't access file @ %s\n", spriteLocation.c_str());
			return data;
		}
		if (doc.Parse(stringFileData.c_str()).HasParseError()) {
			debugPrintF("Couldn't parse json @ %s\n", spriteLocation.c_str());
			return data;
		};
		if(doc.HasMember("textureLocation")) {
			if (doc["textureLocation"].IsString()) {
				std::string textLoc = std::string(PATH_ASSET::AnimatedTexture) + doc["textureLocation"].GetString();
				std::ifstream ifs(textLoc.c_str());
				if (ifs.good()) {
					ifs.close();
					data.textureLocation = textLoc;
				}
				else {
					debugPrintF("Couldn't access texture @ %s\n", textLoc.c_str());
					return data;
				}
			}
		}
		if (doc.HasMember("tileSize")) {
			if (doc["tileSize"].IsArray()) {
				auto ar = doc["tileSize"].GetArray();
				if (ar.Size() == 2) {
					data.tilingSize.x = ar[0].GetInt();
					data.tilingSize.y = ar[1].GetInt();
				}
			}
		}
		if (doc.HasMember("frames")) {
			if (doc["frames"].IsInt()) {
				data.frames = doc["frames"].GetInt();
			}
		}
		if (doc.HasMember("framerate")) {
			if (doc["framerate"].IsInt()) {
				data.framerate = doc["framerate"].GetInt();
			}
		}
		return data;
	}

	const SoundGenData SoundGenData::parseFile(std::string fileName)
	{
		using namespace rapidjson;
		SoundGenData data = SoundGenData();
		std::string stringFileData;
		std::string soundPresetLocation = std::string(PATH_ASSET::SoundPresets) + fileName + std::string(NAME_EXTENSION::soundGen);
		Document doc;
		if (!fileToString(soundPresetLocation, &stringFileData)) {
			debugPrintF("Couldn't open file @ %s\n", soundPresetLocation.c_str());
			return data;
		}
		if (doc.Parse(stringFileData.c_str()).HasParseError()) {
			assert(false);
			debugPrintF("Couldn't parse json @ %s\n", soundPresetLocation.c_str());
			return data;
		};
		if (doc.HasMember("waveName")) {
			if (doc["waveName"].IsString()) {
				data.waveNameHashed = HASH::getFNVHash(doc["waveName"].GetString());
			}
		}
		if (doc.HasMember("startFrequency")) {
			if (doc["startFrequency"].IsString()) {
				data.startFrequency = doc["startFrequency"].GetInt();
			}
		}
		if (doc.HasMember("startFrequency")) {
			if (doc["startFrequency"].IsDouble()) {
				data.startFrequency = doc["startFrequency"].GetDouble();
			}
		}
		if (doc.HasMember("amplitude")) {
			if (doc["amplitude"].IsDouble()) {
				data.startFrequency = doc["amplitude"].GetDouble();
			}
		}
		if (doc.HasMember("gainIncrease")) {
			if (doc["gainIncrease"].IsFloat()) {
				data.startFrequency = doc["gainIncrease"].GetFloat();
			}
		}
		if (doc.HasMember("gainDecrease")) {
			if (doc["gainDecrease"].IsFloat()) {
				data.startFrequency = doc["gainDecrease"].GetFloat();
			}
		}
		if (doc.HasMember("noteIncrease")) {
			if (doc["noteIncrease"].IsDouble()) {
				data.noteIncrease = doc["noteIncrease"].GetDouble();
			}
		}
		if (doc.HasMember("additionalParameter")) {
			if (doc["additionalParameter"].IsInt()) {
				data.aParam = doc["additionalParameter"].GetInt();
			}
		}
		return data;
	}

	bool fileToString(std::string fileLocation, std::string* fileData)
	{
		std::ifstream ifs{ fileLocation.c_str() };
		if (!ifs.is_open())
		{
			return false;
		}
		std::string stringFileData((std::istreambuf_iterator<char>(ifs)),
			std::istreambuf_iterator<char>());
		*fileData = stringFileData;
		ifs.close();
		return true;
	}

}