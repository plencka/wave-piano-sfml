#include "SpriteAnimator.h"

namespace SpriteAnimator {
	std::map<uint32_t, cAnimatedSpriteInstance*> cAnimationManager::pAnimatedSpriteCache_Map;
	cAnimatedSpriteInstance::cAnimatedSpriteInstance(std::string aSpritePath)
	{
		id = HASH::getFNVHash(aSpritePath.c_str());
		pAnimatedSpriteData = Parser::AnimatedSpriteData::parseFile(aSpritePath);
	}

	cAnimatedSprite::cAnimatedSprite(std::string aSpriteName)
	{
		pOriginInstance = cAnimationManager::getAnimationInstance(aSpriteName);
		const auto sprite = pOriginInstance->pAnimatedSpriteData;
		tiles.x = sprite.tilingSize.x;
		tiles.y = sprite.tilingSize.y;
		frameRate = sprite.framerate;
		frames = sprite.frames;
		texture.loadFromFile(pOriginInstance->pAnimatedSpriteData.textureLocation);
		setTexture(texture);
		if (tiles.x == 0) {
			debugPrintF("Tiling data wrong for %s on X.", aSpriteName.c_str());
			tiles.x = 1;
		}
		if (tiles.y == 0) {
			debugPrintF("Tiling data wrong for %s on Y.", aSpriteName.c_str());
			tiles.y = 1;
		}
		setTextureRect(sf::IntRect(0, 0, texture.getSize().x / tiles.x, texture.getSize().y / tiles.y));
	}

	void cAnimatedSprite::animate(float delta)
	{
		if (frameRate == 0) { // No change required
			return;
		}
		currentTick += frameRate * delta;
		unsigned int displayed = unsigned int(abs(floor(currentTick)));
		if (displayed >= frames) {
			displayed = 0;
			currentTick = 0;
		}
		if (frameRate < 0) {
			displayed = frames + displayed;
		}
		setFrame(displayed);
	}

	void cAnimatedSprite::setFrame(unsigned int frame)
	{
		if (tiles.x == 0) {
			assert(tiles.x > 0);
			debugPrintF("Tiling data wrong on X.");
			tiles.x = 1;
		}
		if (tiles.y == 0) {
			assert(tiles.y > 0);
			debugPrintF("Tiling data wrong on Y.");
			tiles.y = 1;
		}
		sf::Vector2u size = getTexture()->getSize();
		unsigned int x = (frame % tiles.x) * (size.x / tiles.x);
		unsigned int y = (frame / tiles.x) * (size.y / tiles.y);
		setTextureRect(sf::IntRect(x, y, size.x / tiles.x, size.y / tiles.y));
	}

	void cAnimatedSprite::reset()
	{
		currentTick = 0;
		const auto sprite = pOriginInstance->pAnimatedSpriteData;
		tiles.x = sprite.tilingSize.x;
		tiles.y = sprite.tilingSize.y;
		frameRate = sprite.framerate;
		frames = sprite.frames;
	}

	cAnimatedSpriteInstance* cAnimationManager::createAnimationInstance(std::string aSpritePath)
	{
		auto aSpriteInstance = new cAnimatedSpriteInstance(aSpritePath);
		addAnimatedSpriteInstance(aSpriteInstance);
		return aSpriteInstance;
	}

	bool cAnimationManager::verifyNoReferences()
	{
		if (pAnimatedSpriteCache_Map.size() == 0) {
			return true;
		}
		return false;
	}

	void cAnimationManager::addAnimatedSpriteInstance(cAnimatedSpriteInstance* aSpriteInstance)
	{
		pAnimatedSpriteCache_Map.insert(std::pair<uint32_t, cAnimatedSpriteInstance*>(aSpriteInstance->id, aSpriteInstance));
	}

	cAnimatedSpriteInstance* cAnimationManager::getAnimationInstance(std::string aSpritePath)
	{
		uint32_t elementID = HASH::getFNVHash(aSpritePath.c_str());
		auto element = pAnimatedSpriteCache_Map.find(elementID);
		if (element == pAnimatedSpriteCache_Map.end()) {
			return createAnimationInstance(aSpritePath);
		}
		else {
			element->second->numReferences++;
			return element->second;
		}
	}

	void cAnimationManager::removeReference(cAnimatedSpriteInstance* aSprite)
	{
		if (--aSprite->numReferences <= 0) {
			pAnimatedSpriteCache_Map.erase(aSprite->id);
			delete(aSprite);
		}
	}
}