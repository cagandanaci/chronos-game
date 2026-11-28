#pragma once

// TODO(name): The current AnimationClip constructor is hard to use because the 
// code that plays a clip has to know the sheet's pixel layout, such as the 
// starting y position.
//
// Idea: describe the sheet once (frame size), define each clip as {row, frames,
// seconds per frame}, and let everything else call play(id) with an enum value.
// The component works out the rectangle from the row and the current frame.
// Each entity type can have its own animation enum, so the shared AnimationID
// list (with player-only names and None) goes away.
//
// After you are done test it with maybe a second TempSprite.

enum class AnimationID
{
	None,
	Idle,
	Running,
	Jumping,
	Falling,
	WallSliding,
	SlideStart,
	Slide,
	SlideEnd,
	Attack1,
	Attack2,
	Attack3,
	DamageTaken,
	Died
};

struct AnimationClip
{
	AnimationClip() = default;

	AnimationClip(AnimationID id, 
		sf::Vector2i size, 
		sf::Vector2i startPos = { 0, 0 },
		int frames = 1,
		sf::Time frameDuration = sf::Time::Zero, 
		bool loop = true
	)
		: id(id)
		, frameSize(size)
		, startPosition(startPos)
		, frameCount(frames)
		, duration(frameDuration)
		, isLooping(loop)
	{}

	AnimationID id = AnimationID::None;
	sf::Vector2i frameSize{ 0, 0 };     // Width and height of a single frame
	sf::Vector2i startPosition{ 0, 0 }; // Starting (x, y) pixel on the sprite sheet
	int frameCount = 1;                 // Total number of frames in the clip
	sf::Time duration = sf::Time::Zero; // Duration per frame
	bool isLooping = true;              // Should the animation loop when finished?
};

class AnimationComponent
{
public:
	AnimationComponent() = default;

	// Adds a new animation clip using its internal AnimationID
	void addClip(const AnimationClip& clip);

	// Plays the specified clip (does not restart if already playing unless resetIfSame is true)
	void play(AnimationID id, bool resetIfSame = false);

	// Advances elapsed time, updates the current frame, and returns the active sf::IntRect
	sf::IntRect update(sf::Time dt);

	// Returns the current frame rectangle without advancing time
	sf::IntRect getCurrentFrameRect() const;

	bool isFinished() const;
	AnimationID getCurrentClipID() const;

private:
	/*==================================================================
	*							MEMBER DATA
	*=================================================================*/
	std::unordered_map<AnimationID, AnimationClip> mClips;

	AnimationID mCurrentClip = AnimationID::None;
	int mCurrentFrame = 0;

	sf::Time mElapsedTime = sf::Time::Zero;
	bool mFinished = false;
};