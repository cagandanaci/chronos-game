#pragma once

#include "SceneNode.h"
#include "ResourceManager.h"

/*
*===============================================================
*						WORLD CLASS
*===============================================================
*/

// TODO (Mehmet) : Create the composition hierarchy between world◆-level◆-room.	

class World
{
public:
	explicit World(sf::RenderWindow& window, const TextureManager& textureManager);

	// Deleted copy constructors.
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
	// Player pointer here, it will hold player during room transitions.
};