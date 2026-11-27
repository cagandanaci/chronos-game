#include "AnimationComponent.h"

void AnimationComponent::addClip(const AnimationClip& clip)
{
	mClips[clip.id] = clip;
	if (mCurrentClip == AnimationID::None)
	{
		play(clip.id, true);
	}
}

void AnimationComponent::play(AnimationID id, bool resetIfSame)
{
	if (mClips.find(id) == mClips.end())
		return;

	if (mCurrentClip == id && !resetIfSame)
		return;

	mCurrentClip = id;
	mCurrentFrame = 0;
	mElapsedTime = sf::Time::Zero;
	mFinished = false;
}

sf::IntRect AnimationComponent::update(sf::Time dt)
{
	auto it = mClips.find(mCurrentClip);
	if (it == mClips.end())
		return sf::IntRect();

	const AnimationClip& clip = it->second;
	if (clip.frameCount <= 1 || clip.duration <= sf::Time::Zero)
		return getCurrentFrameRect();

	mElapsedTime += dt;

	while (mElapsedTime >= clip.duration)
	{
		mElapsedTime -= clip.duration;

		if (mCurrentFrame + 1 < clip.frameCount)
		{
			++mCurrentFrame;
		}
		else if (clip.isLooping)
		{
			mCurrentFrame = 0; // Loop back to the first frame
		}
		else
		{
			mFinished = true;
			break;
		}
	}

	return getCurrentFrameRect();
}

sf::IntRect AnimationComponent::getCurrentFrameRect() const
{
	auto it = mClips.find(mCurrentClip);
	if (it == mClips.end())
		return sf::IntRect();

	const AnimationClip& clip = it->second;
	int left = clip.startPosition.x + (mCurrentFrame * clip.frameSize.x);
	int top = clip.startPosition.y;

	return sf::IntRect({ left, top }, { clip.frameSize.x, clip.frameSize.y });
}

bool AnimationComponent::isFinished() const
{
	return mFinished;
}

AnimationID AnimationComponent::getCurrentClipID() const
{
	return mCurrentClip;
}