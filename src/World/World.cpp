#include "World.h"

World::World(sf::RenderWindow& window, const TextureManager& textureManager)
	: mWindow(window),
	mWorldView(window.getDefaultView()),
	mTextureManager(textureManager),
	mBackground(mTextureManager.get(TextureID::Background)),

	// Temporary sprite initialization
	mTempSprite(mTextureManager.get(TextureID::Player))
{
	// Frame Width: 96, Frame Height: 64
	mTempSprite.mAnimComp.addClip({ AnimationID::Idle, { 96, 64 },{ 0, 64 * 0 }, 8, sf::seconds(0.1f),  true });
	mTempSprite.mAnimComp.addClip({ AnimationID::Running, { 96, 64 }, { 0, 64 * 1 }, 8, sf::seconds(0.08f), true });
	mTempSprite.mAnimComp.addClip({ AnimationID::Attack1, { 96, 64 },{ 0, 64 * 8 }, 7, sf::seconds(0.08f), true });

	// Test etmek istediğin animasyonu seç (Idle, Running veya Attack1)
	mTempSprite.mAnimComp.play(AnimationID::Running);

	mTempSprite.mSprite.setTextureRect(mTempSprite.mAnimComp.getCurrentFrameRect());
	mTempSprite.mSprite.setScale({ 3.f, 3.f }); // Ekranda rahat görmek için 3x büyütme
	mTempSprite.mSprite.setPosition({ 300.f, 300.f });
}

void World::update(sf::Time dt)
{
	mTempSprite.update(dt);
}

void World::render()
{
	mWindow.draw(mBackground);
	mWindow.draw(mTempSprite.mSprite);
}

// Temporary sprite update function
void World::TempSprite::update(sf::Time dt)
{
	mSprite.setTextureRect(mAnimComp.update(dt));
}