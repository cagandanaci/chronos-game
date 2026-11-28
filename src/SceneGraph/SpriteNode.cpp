#include "SpriteNode.h"

SpriteNode::SpriteNode(const sf::Texture& texture, bool collisionEnabled)
	: mSprite(texture),
	mCollisionEnabled(collisionEnabled)
{
}

SpriteNode::SpriteNode(const sf::Texture& texture, const sf::IntRect& textureRect, bool collisionEnabled)
	: mSprite(texture, textureRect),
	mCollisionEnabled(collisionEnabled)
{
}

void SpriteNode::setTextureRect(const sf::IntRect& textureRect)
{
	mSprite.setTextureRect(textureRect);
}

void SpriteNode::setCollisionEnabled(bool enabled) noexcept
{
	mCollisionEnabled = enabled;
}

bool SpriteNode::isCollisionEnabled() const noexcept
{
	return mCollisionEnabled;
}

sf::FloatRect SpriteNode::getCollisionBounds() const
{
	return getWorldTransform().transformRect(mSprite.getGlobalBounds());
}

std::optional<sf::FloatRect> SpriteNode::getOverlap(const SpriteNode& other) const
{
	if (!mCollisionEnabled || !other.mCollisionEnabled)
		return std::nullopt;

	return getCollisionBounds().findIntersection(other.getCollisionBounds());
}

bool SpriteNode::collidesWith(const SpriteNode& other) const
{
	return getOverlap(other).has_value();
}

void SpriteNode::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(mSprite, states);
}
