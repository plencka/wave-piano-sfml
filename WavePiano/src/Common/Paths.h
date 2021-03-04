//////////////////////////////////////////////////////////////////////////////
//
//  Relative paths used by application during runtime.
//

#pragma once

#define PATH_ASSET WaverPiano::Path::AssetFolder
#define PATH_DEFAULTS WaverPiano::Path::DefaultAsset
namespace WaverPiano {
	namespace Path {
		namespace AssetFolder {
			extern const char* AnimatedTexture;
			extern const char* AnimatedSprite;
			extern const char* SoundPresets;
		}
		namespace DefaultAsset {
			extern const char* texture;
			extern const char* font;
			extern const char* soundWave;
		}
	}
}