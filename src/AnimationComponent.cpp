#include "stdafx.h"
#include "AnimationComponent.h"

void AnimationComponent::addClip(const std::string& name, const AnimationClip& clip)
{
	mClips[name] = clip;
	if (mCurrentClip.empty())
	{
		play(name, true);
	}
}

void AnimationComponent::play(const std::string& name, bool resetIfSame)
{
	if (mClips.find(name) == mClips.end())
		return;

	if (mCurrentClip == name && !resetIfSame)
		return;

	mCurrentClip = name;
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
			mCurrentFrame = 0; // Sona ulaşınca ilk kareye döner
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

const std::string& AnimationComponent::getCurrentClipName() const
{
	return mCurrentClip;
}