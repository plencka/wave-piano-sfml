#include "Commons.h"

namespace WaverPiano {
	namespace Interface {
		namespace Font {
			sf::Font generic;
		}

		namespace Color {
			const sf::Color hover = sf::Color(255, 255, 200, 255);
			const sf::Color background = sf::Color(149, 149, 149, 255);
			const sf::Color segment = sf::Color(222, 222, 222, 255);
			const sf::Color segmentShade = sf::Color(55, 55, 55, 255);
			const sf::Color warning = sf::Color::Yellow;
			const sf::Color critical = sf::Color::Red;
			const sf::Color visibleColor = sf::Color::Magenta;
		}
	}
	namespace Names {
		namespace Extension {
			const char* soundGen = ".sGen";
			const char* animatedSprite = ".aSprite";
		}
	}
	namespace Path {
		namespace AssetFolder {
			const char* AnimatedTexture = "Assets/Textures/SpriteSheet/";
			const char* AnimatedSprite = "Assets/Sprites/";
			const char* SoundPresets = "Assets/SoundPresets/";
		}
		namespace DefaultAsset {
			const char* texture = "Assets/Default/Missing.png";
			const char* font = "Assets/Default/FontDefault.otf";
			const char* soundWave = "sine";
		}
	}

	namespace App {
		bool exitApp = false;
		namespace Hash {
			uint32_t getFNVHash(const char* textToHash) {
				uint32_t newHash = 0x811c9dc5;
				const char* pData = &textToHash[0];
				while (*pData != '\0') {
					uint8_t data = *pData;
					newHash = newHash * 0x01000193;
					newHash = newHash xor data;
					*++pData;
				}
				return newHash;
			}
		}
		namespace Time {
			float frameDelta;
		}
		namespace Enum {
			bool hasFlag(uint32_t flags, uint32_t value) {
				if (flags & value) {
					return true;
				}
				return false;
			}
			uint32_t addFlag(uint32_t flags, uint32_t value) {
				return flags | value;
			}
			uint32_t removeFlag(uint32_t flags, uint32_t value) {
				return flags & ~value;
			}
		}
	}
}