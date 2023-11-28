#include <iostream>
#include "Renderer.h"

int main(int, char**)
{
	std::cout << "'ello Vorld!\n";

	// renderer instance
	Renderer renderer;

	renderer.Initialize();
	renderer.CreateWindow("Ray Tracer, bruh...", 400, 300);

	bool quit = false;
	while (!quit)
	{
		SDL_Event event;
		SDL_PollEvent(&event);
		switch (event.type)
		{
		case SDL_QUIT:
			quit = true;
			break;
		}
	}

	renderer.Shutdown();

	return 0;

}