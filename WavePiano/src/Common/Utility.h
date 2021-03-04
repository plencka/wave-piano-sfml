//////////////////////////////////////////////////////////////////////////////
//
//	Application utilities.
//
//  Collection of general functionalities, that are not exclusive to the app.
//


#pragma once
#include <stdint.h>
#include <string>

#define HASH WaverPiano::App::Hash
#define ENUM WaverPiano::App::Enum
#ifdef _DEBUG
#define debugPrintF(...) std::printf(__VA_ARGS__)
#else
#define debugPrintF(...)
#endif

namespace WaverPiano {
	namespace App {
		extern bool exitApp;
		namespace Hash {
			constexpr uint32_t compileFNVHash(const char* textToHash) {
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
			uint32_t getFNVHash(const char* textToHash);
		}
		namespace Time {
			extern float frameDelta;
		}

		namespace Enum {
			bool hasFlag(uint32_t flags, uint32_t value);
			uint32_t addFlag(uint32_t flags, uint32_t value);
			uint32_t removeFlag(uint32_t flags, uint32_t value);
		}
	}
}