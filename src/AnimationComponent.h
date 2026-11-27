#pragma once

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
	AnimationClip(AnimationID id, sf::Vector2i startPos, sf::Vector2i size, int frames, sf::Time frameDuration, bool loop = true)
		: id(id)
		, startPosition(startPos)
		, frameSize(size)
		, frameCount(frames)
		, duration(frameDuration)
		, isLooping(loop)
	{
	}

	AnimationID id = AnimationID::None;
	sf::Vector2i startPosition{ 0, 0 }; // Starting (x, y) pixel on the sprite sheet
	sf::Vector2i frameSize{ 0, 0 };     // Width and height of a single frame
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