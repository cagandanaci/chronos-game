#pragma once

#include "SceneNode.h"
#include "ResourceManager.h"

/*
*===============================================================
*						WORLD CLASS
*===============================================================
*/

// TODO (Mehmet) : Create the composition hierarchy between world◆-level◆-room.	
// Levels should store every room the player will enter.
// Rooms will store the root of the scene graph, like World does in the book's example.
// The layer system will also be in the room.
// Rooms will also build scenes in their buildScene functions by creating layers,
// attaching child scene nodes to their parents, and providing access to the necessary resources for every scene node.
// The book has an example of the buildScene function as well.

// Load resources in Application.cpp and use the resource manager to access them.


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