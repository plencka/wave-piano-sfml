#include "ManagedWindows.h"

namespace Interface {

	std::map<uint32_t, std::shared_ptr<IManagedWindow>> cWindowManager::pManagedWindow_Map;

	void cWindowManager::registerWindow(std::shared_ptr<IManagedWindow> window)
	{
		assert(pManagedWindow_Map.insert(std::make_pair(window->getWindowID(), window)).second);
		window->deploy();
	}

	void cWindowManager::disposeWindows()
	{
		pManagedWindow_Map.empty();
		pManagedWindow_Map.clear();
	}

	void cWindowManager::updateWindows()
	{
		for (auto& window : pManagedWindow_Map) {
			window.second->updateWhenOpen();
		}
	}

	std::weak_ptr<IManagedWindow> cWindowManager::getWindowByID(uint32_t id)
	{
		auto it = pManagedWindow_Map.find(id);
		if (it != pManagedWindow_Map.end()) {
			return it->second;
		}
		else {
			return std::weak_ptr<IManagedWindow>();
		}
	}

	std::weak_ptr<IManagedWindow> cWindowManager::openWindowByID(uint32_t id)
	{
		if (auto window = getWindowByID(id).lock()) {
			window->openWindow(window->titleName);
			return window;
		}
		return std::weak_ptr<IManagedWindow>();
	}

	void cWindowManager::disableKeysByID(uint32_t id)
	{
		if (auto window = getWindowByID(id).lock()) {
			window->disableButtons();
			window->updateFocused();
		}
	}
	void cWindowManager::enableKeysByID(uint32_t id)
	{
		if (auto window = getWindowByID(id).lock()) {
			window->enableButtons();
			window->updateFocused();
		}
	}
}