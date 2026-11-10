#include "Application.h"

int main()
{
	try
	{
		// App currently pushes the "Game State".
		// Current "World" in game state is temperory until Mehmet finishes the world<-level<-room hierarchy.

		Application app;
		app.run();
	}
	catch (std::exception& e)
	{
		std::cerr << "EXCEPTION: " << e.what();
	}
}
