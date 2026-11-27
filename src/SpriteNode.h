#pragma once

#include "SceneNode.h"

#include <optional>

#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>

/*
*===============================================================
*					SPRITE NODE CLASS
*===============================================================
*/

// A scene node that draws a sprite.
// It is used for anything that is mostly displayed (backgrounds, platforms, decorations, etc.).
// The node does not own the texture, so the texture must outlive the node
// (the resource manager keeps it alive for the whole game).
// Collision is optional and off by default: enable it for solid objects like platforms.

class SpriteNode : public SceneNode
{
public:
	// Uses the whole texture.
	explicit SpriteNode(const sf::Texture& texture, bool collisionEnabled = false);

	// Uses only the selected rectangle of the texture (e.g. one frame of a sprite sheet).
	SpriteNode(const sf::Texture& texture, const sf::IntRect& textureRect, bool collisionEnabled = false);

	// Changes which part of the texture is displayed.
	// The animation component's frame rectangles can be passed to this function.
	void setTextureRect(const sf::IntRect& textureRect);

	// Enables or disables this node's participation in collision checks.
	void setCollisionEnabled(bool enabled) noexcept;
	[[nodiscard]] bool isCollisionEnabled() const noexcept;

	// Returns this sprite's axis-aligned bounding box (AABB) in world coordinates.
	[[nodiscard]] sf::FloatRect getCollisionBounds() const;

	// Returns the overlapping rectangle of the two nodes' bounds, or std::nullopt
	// if either node has collision disabled or the bounds do not overlap.
	// The size of the overlap tells how deep the nodes are inside each other.
	[[nodiscard]] std::optional<sf::FloatRect> getOverlap(const SpriteNode& other) const;

	// Returns true only when both nodes have collision enabled and their bounds overlap.
	[[nodiscard]] bool collidesWith(const SpriteNode& other) const;

private:
	// SceneNode calls this when it draws the scene graph.
	void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const override;

/*==================================================================
*							MEMBER DATA
*=================================================================*/

	sf::Sprite mSprite;
	bool mCollisionEnabled = false;
};
