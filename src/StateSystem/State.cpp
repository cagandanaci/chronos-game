#include "State.h"
#include "StateStack.h"

State::Context::Context(sf::RenderWindow& window, TextureManager& textureManager, FontManager& fontManager)
	: window(&window), textureManager(&textureManager), fontManager(&fontManager)
{}

State::State(StateStack& stack, Context context)
	: mStack(stack), mContext(context)
{}

void State::requestStackAction(StackAction action, StateID id)
{
	mStack.requestAction(action, id);
}

void State::requestStackPush(StateID id)
{
	mStack.requestPush(id);
}

void State::requestStackPop()
{
	mStack.requestPop();
}

void State::requestStackClear()
{
	mStack.requestClear();
}

State::Context State::getContext() const
{
	return mContext;
}

// MAIN MENU STATE

MenuState::MenuState(StateStack& stack, Context context)
	: State(stack, context),
	mBackground(getContext().textureManager->get(TextureID::MenuBackground)),
	mTitle(getContext().fontManager->get(FontID::PixelOp)),
	mStartText(getContext().fontManager->get(FontID::PixelOp)),
	mExitText(getContext().fontManager->get(FontID::PixelOp))
{
	mTitle.setCharacterSize(64);
	mTitle.setString("CHRONOS");
	mTitle.setFillColor(sf::Color(190,0,0));
	mTitle.setOutlineColor(sf::Color::Black);
	mTitle.setOutlineThickness(1.f);
	mTitle.setOrigin(mTitle.getLocalBounds().position + mTitle.getGlobalBounds().size / 2.f);
	mTitle.setPosition(sf::Vector2f(getContext().window->getSize().x / 2.f, getContext().window->getSize().y / 6.f));

	mStartText.setCharacterSize(36);
	mStartText.setString("START GAME");
	mStartText.setOutlineColor(sf::Color::Black);
	mStartText.setOutlineThickness(1.f);
	mStartText.setOrigin(mTitle.getLocalBounds().position + mTitle.getGlobalBounds().size / 2.f);
	mStartText.setPosition(sf::Vector2f(getContext().window->getSize().x * 6.5f / 8.f, getContext().window->getSize().y / 2.f));

	mExitText = mStartText;
	mExitText.setString("EXIT");

	mStartText.move({ 0.f, -20.f });
	mExitText.move({0.f, 20.f});
}

bool MenuState::processEvents(const std::optional<sf::Event> event)
{
	if (event->is<sf::Event::Closed>())
		getContext().window->close();

	if (auto mouseButton = event->getIf<sf::Event::MouseButtonPressed>())
	{
		if (mouseButton->button == sf::Mouse::Button::Left)
		{
			auto cursor = sf::FloatRect(sf::Vector2f(mouseButton->position), { 0.1f, 0.1f });
			if (cursor.findIntersection(mStartText.getGlobalBounds())) {
				requestStackPush(StateID::Game);
				return false;
			}
			else if (cursor.findIntersection(mExitText.getGlobalBounds())) {
				getContext().window->close();
				return false;
			}
		}
	}

	return false;
}

bool MenuState::update(sf::Time dt)
{
	return false;
}

void MenuState::draw()
{
	sf::RenderWindow& window = *getContext().window;

	window.draw(mBackground);
	window.draw(mTitle);
	window.draw(mStartText);
	window.draw(mExitText);
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
	sf::RenderWindow& window = *getContext().window;

	window.setView(window.getDefaultView());
	window.draw(mFilter);
	window.draw(mText);
}

