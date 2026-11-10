#include "StateStack.h"

StateStack::StateStack(State::Context context)
	: mContext(context)
{}

void StateStack::processEvents(const std::optional<sf::Event> event)
{
	for (auto it = mStack.rbegin(); it != mStack.rend(); ++it)
	{
		if (!(*it)->processEvents(event))
			break;
	}

	applyPendingChanges();
}

void StateStack::update(sf::Time dt)
{
	for (auto it = mStack.rbegin(); it != mStack.rend(); ++it)
	{
		if (!(*it)->update(dt))
			break;
	}

	applyPendingChanges();
}

void StateStack::draw()
{
	for (auto it = mStack.begin(); it != mStack.end(); ++it)
	{
		(*it)->draw();
	}
}

// Action Requests

void StateStack::pushState(StateID stateID)
{
	mPendingList.emplace_back(Push, stateID);
}

void StateStack::popState()
{
	mPendingList.emplace_back(Pop);	
}

void StateStack::clearStates()
{
	mPendingList.emplace_back(Clear);
}

//

bool StateStack::isEmpty() const
{
	return mStack.empty();
}

State::Ptr StateStack::createState(StateID stateID)
{
	auto found = mFactories.find(stateID);
	assert(found != mFactories.end());

	return found->second();
}

void StateStack::applyPendingChanges()
{
	for (const PendingChange change : mPendingList)
	{
		switch (change.action)
		{
		case Push:
			mStack.push_back(createState(change.stateID));
			break;
		case Pop:
			mStack.pop_back();
			break;
		case Clear:
			mStack.clear();
			break;
		}
	}

	mPendingList.clear();
}
