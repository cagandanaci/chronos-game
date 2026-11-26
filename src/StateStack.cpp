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

// Functions

void StateStack::requestAction(StackAction action, StateID id)
{
	mPendingList.emplace_back(action, id);
}

void StateStack::requestPush(StateID id)
{
	requestAction(StackAction::Push, id);
}

void StateStack::requestPop()
{
	requestAction(StackAction::Pop);
}

void StateStack::requestClear()
{
	requestAction(StackAction::Clear);
}

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
	for (const PendingAction change : mPendingList)
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
