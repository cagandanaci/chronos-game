#include "State.h"
#include "StateStack.h"

State::Context::Context(sf::RenderWindow& window, TextureManager& textureManager, FontManager& fontManager)
	: window(&window), textureManager(&textureManager), fontManager(&fontManager)
{}

State::State(StateStack& stack, Context context)
	: mStack(&stack), mContext(context)
{}

void State::requestStackPush(StateID stateID)
{
	mStack->pushState(stateID);
}

void State::requestStackPop()
{
	mStack->popState();
}

void State::requestStackClear()
{
	mStack->clearStates();
}

State::Context State::getContext() const
{
	return mContext;
}

// GAME STATE

GameState::GameState(StateStack& stack, Context context)
	: State(stack, context), mWorld(*context.window, *context.textureManager)
{}

bool GameState::processEvents(const std::optional<sf::Event> event)
{
	if(event->is<sf::Event::Closed>())
		getContext().window->close();

	else if (const auto keyPressed = event->getIf<sf::Event::KeyPressed>())
	{
		if (keyPressed->scancode == sf::Keyboard::Scan::Escape)
		{
			requestStackPush(StateID::Pause);
			return false;
		}
	}

	return false;
}

bool GameState::update(sf::Time dt)
{
	mWorld.update(dt);

	return false;
}

void GameState::draw()
{
	mWorld.render();
}

// PAUSE STATE

PauseState::PauseState(StateStack& stack, Context context)
	: State(stack, context), mText(getContext().fontManager->get(FontID::PixelOp))
{
	mFilter.setFillColor(sf::Color(0, 0, 0, 80));
	mFilter.setSize(BOUNDS_SIZE);

	mText.setCharacterSize(80);
	mText.setFillColor(sf::Color::Black);
	mText.setString("PAUSE");
	mText.setOrigin(mText.getLocalBounds().position + mText.getLocalBounds().size / 2.f);
	mText.setPosition(sf::Vector2f(context.window->getSize()) / 2.f);
}

bool PauseState::processEvents(const std::optional<sf::Event> event)
{
	if (event->is<sf::Event::Closed>())
		getContext().window->close();

	else if (const auto keyPressed = event->getIf<sf::Event::KeyPressed>())
	{
		if (keyPressed->scancode == sf::Keyboard::Scan::Escape)
		{
			requestStackPop();
			return false;
		}
	}

	return false;
}

bool PauseState::update(sf::Time dt)
{
	return false;
}

void PauseState::draw()
{
	sf::RenderWindow* window = getContext().window;

	window->setView(window->getDefaultView());
	window->draw(mFilter);
	window->draw(mText);

	// for debug
	/*
	sf::RectangleShape RECT(mText.getGlobalBounds().size);
	RECT.setOrigin(RECT.getSize() / 2.f);
	RECT.setPosition(mText.getPosition());
	window->draw(RECT);
	*/
}
