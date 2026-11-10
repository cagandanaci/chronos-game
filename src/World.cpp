#include "World.h"

World::World(sf::RenderWindow& window, const TextureManager& textureManager)
	: mWindow(window),
	mWorldView(window.getDefaultView()),
	mTextureManager(textureManager),
	mBackground(mTextureManager.get(TextureID::Background))
{
}

void World::update(sf::Time dt)
{
}

void World::render()
{
	mWindow.draw(mBackground);
}
