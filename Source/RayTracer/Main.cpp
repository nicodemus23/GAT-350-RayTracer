#include <iostream>
#include "Renderer.h"
#include "Random.h"
#include "MathUtils.h"
#include "Canvas.h"
#include "Scene.h"
#include "Material.h"
#include "Color.h"
#include <memory>
#include "Sphere.h"
#include "Object.h"




int main(int, char**)
{
	std::cout << "'ello Vorld!\n";

	//Random::seedRandom((unsigned int)time(nullptr));
	//Random::random01();
	//auto result = MathUtils::lerp(0.0f, 1.0f, .05f);

	// renderer instance
	Renderer renderer;

	renderer.Initialize();

	// create window
	renderer.CreateWindow("Ray Tracer, bruh...", 400, 300);

	// create canvas
	Canvas canvas(400, 300, renderer);

	// create camera
	float aspectRatio = canvas.GetSize().x / (float)canvas.GetSize().y;
	std::shared_ptr<Camera> camera = std::make_shared<Camera>(glm::vec3{ 0, 0, 1 }, glm::vec3{ 0, 0, 0 }, glm::vec3{ 0, 1, 0 }, 70.0f, aspectRatio);

	// create scene
	Scene scene; // sky color could be set with the top and bottom color
	scene.SetCamera(camera);

	
	bool quit = false;
	while (!quit)
	{	// event loop
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

		// create material 
		auto material = std::make_shared<Lambertian>(Color::color3_t{ 0, 0, 1 });

		// create objects -> add to scene
		auto sphere = std::make_unique<Sphere>(glm::vec3{ 0 }, glm::vec3{0}, material);
		scene.AddObject(std::unique_ptr<Object>(static_cast<Object*>(sphere.release())));
		canvas.Update();

		renderer.PresentCanvas(canvas);

		
	}
	
	renderer.Shutdown();

	return 0;
	


}