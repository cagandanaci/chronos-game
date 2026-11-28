#pragma once

#include "ResourceManager.h"
#include "World.h"

// TODO(Bedirhan): Implement the title state. For now use the temp menu background, 
// this will be changed later with its own background. Create the title with sf::Text,
// this will also be changed later as its own background will include a title.
// Create another text that fades in and out with a timer and reads "Press any key to continue...", 
// and when any keyboard key is pressed, TitleState must request a push for the MenuState.
//
// Don't forget to push TitleState in application start from Application.cpp.

/*
*===============================================================
*						STATE CLASS
*===============================================================
*/


class StateStack;

enum StackAction
{
	Push,
	Pop,
	Clear
};

enum class StateID
{
	Title,
	MainMenu,
	Game,
	Pause,
	Null
};

class State 
{
public:
	using Ptr = std::unique_ptr<State>;
	struct Context
	{
		Context(sf::RenderWindow& window,
				TextureManager& textureManager,
				FontManager& fontManager);

		// Context Data
		sf::RenderWindow* window;
		TextureManager* textureManager;
		FontManager* fontManager;
	};

	State(StateStack& stack, Context context);
	virtual ~State() = default;

	// processEvents and update return a bool. If it is false,
	// the state prevents the states below it from calling their own
	// processEvents and update functions.
	virtual bool processEvents(const std::optional<sf::Event> event) = 0;
	virtual bool update(sf::Time dt) = 0;
	virtual void draw() = 0;

	void requestStackAction(StackAction action, StateID id = StateID::Null);

	void requestStackPush(StateID id);
	void requestStackPop();
	void requestStackClear();

	Context getContext() const;

private:

/*==================================================================
*							MEMBER DATA
*=================================================================*/

	StateStack& mStack;
	Context mContext;
};

/*
=====================================
	TITLE STATE
=====================================


class TitleState : public State
{

};*/

/*
=====================================
	MAIN MENU STATE
=====================================
*/

class MenuState : public State
{
public:
	MenuState(StateStack& stack, Context context);

	virtual bool processEvents(const std::optional<sf::Event> event) override;
	virtual bool update(sf::Time dt) override;
	virtual void draw() override;

private:
	sf::Sprite mBackground;
	sf::Text mTitle;
	sf::Text mStartText;
	sf::Text mExitText;
};

/*
=====================================
	GAME STATE
=====================================
*/

class GameState : public State
{
public:
	GameState(StateStack& stack, Context context);

	virtual bool processEvents(const std::optional<sf::Event> event) override;
	virtual bool update(sf::Time dt) override;
	virtual void draw() override;

private:
	World mWorld;
};

/*
=====================================
	PAUSE STATE
=====================================
*/

class PauseState : public State
{
public:
	PauseState(StateStack& stack, Context context);

	virtual bool processEvents(const std::optional<sf::Event> event) override;
	virtual bool update(sf::Time dt) override;
	virtual void draw() override;

private:
	sf::RectangleShape mFilter;
	sf::Text mText;
};