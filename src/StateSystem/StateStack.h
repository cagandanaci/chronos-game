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

	void requestAction(StackAction action, StateID id = StateID::Null);
	void requestPush(StateID id);
	void requestPop();
	void requestClear();

	bool isEmpty() const;

private:
	State::Ptr createState(StateID stateID);
	void applyPendingChanges();

	struct PendingAction
	{
		PendingAction(StackAction action, StateID stateID = StateID::Null) : action(action), stateID(stateID) {}

		StackAction action;
		StateID stateID;
	};

/*==================================================================
*							MEMBER DATA
*=================================================================*/

	State::Context mContext;
	std::vector<State::Ptr> mStack;
	std::vector<PendingAction> mPendingList;
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