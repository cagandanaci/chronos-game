#pragma once

#include "SceneNode.h"
#include "ResourceManager.h"

/*
	Represents the game world and stores the view
*/

class World
{
public:
	explicit World(sf::RenderWindow& window, const TextureManager& textureManager);

	// Deleted
	World(const World&) = delete;
	World& operator=(const World&) = delete;

	void update(sf::Time dt);
	void render();

private:
	enum Layer
	{
		Background,
		Objects,
		LayerCount
	};

/*==================================================================
*							MEMBER DATA
*=================================================================*/

	sf::RenderWindow& mWindow;				
	sf::View mWorldView;					// Camera
	const TextureManager& mTextureManager;

	sf::Sprite mBackground;
	// Player pointer here
};