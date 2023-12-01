#include <iostream>
#include "Renderer.h"
#include "Random.h"
#include "MathUtils.h"
#include "Canvas.h"
#include "Scene.h"

// for debug:
#include "Color.h"



int main(int, char**)
{
	std::cout << "'ello Vorld!\n";

	//Random::seedRandom((unsigned int)time(nullptr));
	//Random::random01();
	//auto result = MathUtils::lerp(0.0f, 1.0f, .05f);

	// renderer instance
	Renderer renderer;

	renderer.Initialize();
	renderer.CreateWindow("Ray Tracer, bruh...", 400, 300);
	Canvas canvas(400, 300, renderer);

	float aspectRatio = canvas.GetSize().x / (float)canvas.GetSize().y;
	std::shared_ptr<Camera> camera = std::make_shared<Camera>(glm::vec3{ 0, 0, 1 }, glm::vec3{ 0, 0, 0 }, glm::vec3{ 0, 1, 0 }, 70.0f, aspectRatio);

	Scene scene; // sky color could be set with the top and bottom color
	scene.SetCamera(camera);


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
		//for (int i = 0; i < 1000; i++) canvas.DrawPoint({Random::random(0, 399), Random::random(0,299)},{Random::random01(),Random::random01(), Random::random01(), 1});
		scene.Render(canvas);
		canvas.Update();

		renderer.PresentCanvas(canvas);

		
	}

	renderer.Shutdown();

	return 0;
	


}