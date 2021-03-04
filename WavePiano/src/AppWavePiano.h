//////////////////////////////////////////////////////////////////////////////
//
//	App::cWavePiano
//
//  WavePiano application entry point.
//	Kept outside Main.cpp in case commandline options are introduced.

#pragma once
#include "Interface/Windows/ManagedWindows.h"

namespace App {
	class cWavePiano {
	private:
		static sf::Clock frameTime;
	public:
		static int run();
	private:
		static int initialize();
		static bool update();
		static int exit();
	};
}