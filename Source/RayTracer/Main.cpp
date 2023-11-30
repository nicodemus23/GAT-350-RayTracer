#include <iostream>
#include "Renderer.h"
#include "Random.h"
#include "MathUtils.h"
#include "Canvas.h"

int main(int, char**)
{
	std::cout << "'ello Vorld!\n";

	Random::seedRandom((unsigned int)time(nullptr));
	//Random::random01();
	//auto result = MathUtils::lerp(0.0f, 1.0f, .05f);

	// renderer instance
	Renderer renderer;

	renderer.Initialize();
	renderer.CreateWindow("Ray Tracer, bruh...", 400, 300);
	Canvas canvas(400, 300, renderer);

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

		canvas.Clear({ 0, 0, 0, 1 });						// random x				random y				random R			random G			random B		A
		for (int i = 0; i < 1000; i++) canvas.DrawPoint({Random::random(0, 399), Random::random(0,299)},{Random::random01(),Random::random01(), Random::random01(), 1});
		canvas.Update();

		canvas.PresentCanvas(canvas);
	}

	renderer.Shutdown();

	return 0;

}