#pragma once

#include "ResourceManager.h"
#include "World.h"

/*
*===============================================================
*						STATE CLASS
*===============================================================
*/


class StateStack;

enum class StateID
{
	Title,
	MainMenu,
	Game,
	Pause,
	NullID
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

public:
	State(StateStack& stack, Context context);
	virtual ~State() = default;

	// processEvents and update returns a bool. If it is false, 
	// state stops the states before it to see states under it 
	// from calling their own processEvents and update functions.
	virtual bool processEvents(const std::optional<sf::Event> event) = 0;
	virtual bool update(sf::Time dt) = 0;
	
	virtual void draw() = 0;

protected:
	void requestStackPush(StateID stateID);
	void requestStackPop();
	void requestStackClear();

	Context getContext() const;

private:

/*==================================================================
*							MEMBER DATA
*=================================================================*/

	StateStack* mStack;
	Context mContext;
};

/*
=====================================
	TITLE STATE
=====================================


class TitleState : public State
{

};


=====================================
	MAIN MENU STATE
=====================================


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
*/

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