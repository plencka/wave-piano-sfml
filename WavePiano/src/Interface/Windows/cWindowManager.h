//////////////////////////////////////////////////////////////////////////////
//
//	Interface::cWindowManager
//
//  Class stores and manages created Windows.
//	Basic functions for registering, looking up and enabling/disabling windows.
//
#pragma once


namespace Interface{

	class cWindowManager {
	private:
		static std::map<uint32_t, std::shared_ptr<IManagedWindow>> pManagedWindow_Map;

	public:
		static void registerWindow(std::shared_ptr<IManagedWindow> window);
		static void disposeWindows();
		static void updateWindows();
		static std::weak_ptr<IManagedWindow> getWindowByID(uint32_t id);
		static std::weak_ptr<IManagedWindow> openWindowByID(uint32_t id);
		static void disableKeysByID(uint32_t id);
		static void enableKeysByID(uint32_t id);
	};

}