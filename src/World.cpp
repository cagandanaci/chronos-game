#include "World.h"

World::World(sf::RenderWindow& window, const TextureManager& textureManager)
	: mWindow(window),
	mWorldView(window.getDefaultView()),
	mTextureManager(textureManager),
	mBackground(mTextureManager.get(TextureID::Background)),

	// Temporary sprite initialization
	mTempSprite(mTextureManager.get(TextureID::Player))
{
}

void World::update(sf::Time dt)
{
	mTempSprite.update(dt);
}

void World::render()
{
	mWindow.draw(mBackground);
}

// Temporary sprite update function

void World::TempSprite::update(sf::Time dt)
{
}
