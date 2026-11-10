#pragma once
#include "StateStack.h"

/*
*=============================================================== 
*						APPLICATION CLASS
*===============================================================
*/

class Application
{
public:
	Application();

	void loadTextures();
	void loadFonts();
	void registerStates();
	
	void run();

	void processEvents();
	void update(sf::Time dt);
	void draw();

private:

/*==================================================================
*							MEMBER DATA
*=================================================================*/

	sf::RenderWindow mWindow;
	TextureManager mTextureManager;
	FontManager mFontManager;

	StateStack mStateStack;
};