#pragma once

/*
*===============================================================
*					SCENE NODE CLASS 
*===============================================================
*/

class SceneNode : public sf::Transformable, public sf::Drawable
{
public:
	using Ptr = std::unique_ptr<SceneNode>;

	SceneNode() = default;
	SceneNode(const SceneNode&) = delete;				// Scene nodes can't be copied.
	SceneNode& operator=(const SceneNode&) = delete;
	virtual ~SceneNode() = default;

	void attachChild(Ptr child);
	Ptr detachChild(const SceneNode& node);

	sf::Transform getWorldTransform() const;			// Returns the transform relative to the game world.

	void update(sf::Time dt);
private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override final;	
	virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;			// For derived classes to override if they will be drawn.

	virtual void updateCurrent(sf::Time dt);													// This function should be overridden to update the object.
	void updateChildren(sf::Time dt);

/*==================================================================
*							MEMBER DATA
*=================================================================*/

	std::vector<Ptr> mChildren;							// Container that keeps pointers to class' children.
	SceneNode* mParent = nullptr;						// Pointer to class' parent
};