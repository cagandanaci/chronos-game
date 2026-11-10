#pragma once

#include "State.h"

/*
*===============================================================
*						STATE STACK CLASS
*===============================================================
*/

class StateStack
{
public:
	enum Action
	{
		Push,
		Pop,
		Clear
	};

	explicit StateStack(State::Context context);
	
	// Non-Copyable
	StateStack(const StateStack&) = delete;
	StateStack operator=(const StateStack&) = delete;
	// Non-Movable
	StateStack(StateStack&&) = delete;
	StateStack operator=(StateStack&&) = delete;

	template <typename T>
	void registerState(StateID stateID);

	void processEvents(const std::optional<sf::Event> event);
	void update(sf::Time dt);
	void draw();

	void pushState(StateID stateID);
	void popState();
	void clearStates();

	bool isEmpty() const;

private:
	State::Ptr createState(StateID stateID);

	void applyPendingChanges();

private:
	struct PendingChange
	{
		PendingChange(Action action, StateID stateID = StateID::NullID) : action(action), stateID(stateID) {}

		Action action;
		StateID stateID;
	};

/*==================================================================
*							MEMBER DATA
*=================================================================*/

	std::vector<State::Ptr> mStack;
	std::vector<PendingChange> mPendingList;
	State::Context mContext;
	std::map<StateID, std::function<State::Ptr()>> mFactories;
};

template<typename T>
void StateStack::registerState(StateID stateID)
{
	assert(mFactories.end() == mFactories.find(stateID));

	mFactories[stateID] = [this]()
	{
		return std::make_unique<T>(*this, mContext);
	};
}