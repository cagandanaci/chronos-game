#include "Application.h"

int main()
{
	try
	{
		// App currently pushes the "Game State".
		// Current "World" in game state is temporary.

		Application app;
		app.run();
	}
	catch (std::exception& e)
	{
		std::cerr << "EXCEPTION: " << e.what();
	}
}
