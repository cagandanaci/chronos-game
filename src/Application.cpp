#include "Application.h"

Application::Application()
	: mWindow(sf::VideoMode({ 800, 600 }), "Window"),
	mStateStack(State::Context(mWindow, mTextureManager, mFontManager))
{
	loadTextures();
	loadFonts();
	registerStates();
	mStateStack.pushState(StateID::Game);
}

// Loading resources

void Application::loadTextures()
{
	// Textures loaded here are temporary.

	mTextureManager.load(TextureID::MenuBackground, "assets/textures/menu-background.png");

	mTextureManager.load(TextureID::Background, "assets/textures/background.png");
	mTextureManager.get(TextureID::Background).setRepeated(true);

	mTextureManager.load(TextureID::Player, "assets/textures/soldier.png");
}

void Application::loadFonts()
{
	mFontManager.load(FontID::PixelOp, "assets/fonts/pixel-operator.ttf");
}

void Application::registerStates()
{
	// Register every newly added state here.

	//mStateStack.registerState<TitleState>(StateID::Title);
	//mStateStack.registerState<MenuState>(StateID::MainMenu);
	mStateStack.registerState<GameState>(StateID::Game);
	mStateStack.registerState<PauseState>(StateID::Pause);
}

void Application::run()
{
	sf::Clock clock;
	auto timeSinceLastUpdate = sf::Time::Zero;

	while (mWindow.isOpen())
	{
		processEvents();

		timeSinceLastUpdate += clock.restart();

		while (timeSinceLastUpdate > TIME_PER_FRAME)
		{
			timeSinceLastUpdate -= TIME_PER_FRAME;
			processEvents();
			update(TIME_PER_FRAME);
		}

		draw();
	}
}

void Application::processEvents()
{
	while (const std::optional event = mWindow.pollEvent())
	{
		mStateStack.processEvents(event);
	}
}

void Application::update(sf::Time dt)
{
	mStateStack.update(dt);
}

void Application::draw()
{
	mWindow.clear(sf::Color::Black);

	mStateStack.draw();

	mWindow.display();
}
