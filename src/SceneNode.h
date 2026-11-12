#pragma once

/*
*===============================================================
*					SCENE NODE CLASS 
*===============================================================
*/

// TODO(Türkalp): Inherit the "Entity" class from the scene node.
// Implement physics for it, giving it its own velocity and acceleration members.
// Its updateCurrent function should update entities.
// Every entity must move by mVelocity * dt during each update.
// Gravity will constantly accelerate it toward the ground (positive-y direction) while the entity is not grounded.
// Also add a bool mGravity.

// Resources will be given to particular scene nodes in Room.cpp's buildScene function.

// TODO(Bedirdhan): Inherit the "SpriteNode" class.
// Sprite nodes are scene nodes with sprites.
// An implementation can be found in the game development book we have been using.

// TODO(Mustafa): Create the animation component class. It will not be inherited from another class.
// It will store important information about an entity's sprite sheet.
// It will also have a function that returns the necessary frame rectangle (as an sf::IntRect object) for the entity class to set as its texture rectangle.
// That function would step to the next frame, and return the first frame when the clip being used reach its end.

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
	// Use updateCurrent for individual updates in inherited classes, not update.
	void updateChildren(sf::Time dt);											

/*==================================================================
*							MEMBER DATA
*=================================================================*/

	std::vector<Ptr> mChildren;							// Container that keeps pointers to class' children.
	SceneNode* mParent = nullptr;						// Pointer to class' parent
};