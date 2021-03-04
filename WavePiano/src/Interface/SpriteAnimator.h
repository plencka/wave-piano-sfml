//////////////////////////////////////////////////////////////////////////////
//
//	SpriteAnimator
//
//  Extends SFML Sprite class with functions related to sprite sheet animation.
//	Caches instances of animated sprite data to improve overall performance.
//

#pragma once
#include "../Parser/JsonParsers.h"
namespace SpriteAnimator
{
	struct cAnimatedSpriteInstance {
		unsigned int numReferences = 1;
		Parser::AnimatedSpriteData pAnimatedSpriteData;
		uint32_t id = 0;
		cAnimatedSpriteInstance(std::string aSpritePath);
	};

	class cAnimatedSprite : public sf::Sprite
	{
	protected:
		cAnimatedSpriteInstance* pOriginInstance = nullptr;
		float currentTick = 0;
		cAnimatedSprite(std::string aSpriteName);
	public:
		sf::Texture texture;
		sf::Vector2u tiles;
		int frameRate = 0;
		unsigned int frames = 2;
		void animate(float delta);
		void setFrame(unsigned int frame);
		void reset();
	};

	class cAnimationManager {
	private:
		static std::map<uint32_t, cAnimatedSpriteInstance*> pAnimatedSpriteCache_Map;

		/// Only call if specified asset isn't instanced.
		static cAnimatedSpriteInstance* createAnimationInstance(std::string aSpritePath);
	public:
		static bool verifyNoReferences();
		static void addAnimatedSpriteInstance(cAnimatedSpriteInstance* aSpriteInstance);
		static cAnimatedSpriteInstance* getAnimationInstance(std::string aSpritePath);
		static void removeReference(cAnimatedSpriteInstance* aSprite);
	};
};

