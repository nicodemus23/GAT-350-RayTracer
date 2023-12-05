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
																	// position			// direction (target)    // up vector  // fov // aspect ratio
	std::shared_ptr<Camera> camera = std::make_shared<Camera>(glm::vec3{ 0, 0, 1 }, glm::vec3{ 1, 0, 0 }, glm::vec3{ 0, 1, 0 }, 70.0f, aspectRatio);

	Scene scene(20); // sky color could be set with the top and bottom color
	scene.SetCamera(camera);

	// create material
	auto lambertian = std::make_shared<Lambertian>(Color::color3_t{ 1, 1, 1 });
	auto metal = std::make_shared<Metal>(Color::color3_t{ 0.8f, 0.6f, 0.2f }, 0.3f);


	// create objects -> add to scene
	for (int i = 0; i < 20; i++)
	{	// add multiple spheres to the scene at random positions and radii

		float radius = Random::random(0.1f, 0.5f);
		glm::vec3 position = Random::random(glm::vec3{ -1, -1, 0 }, glm::vec3{ 4, 1, -2 });
		std::shared_ptr<Material> material = (std::rand() % 2 == 0) ? std::dynamic_pointer_cast<Material>(lambertian) : std::dynamic_pointer_cast<Material>(metal);

		std::cout << "Sphere " << i << ": Radius = " << radius
			<< ", Position = (" << position.x << ", " << position.y << ", " << position.z << ")" << std::endl;

		auto sphere = std::make_unique<Sphere>(position, radius, material);

		scene.AddObject(std::move(sphere));
	}
	//auto sphere = std::make_unique<Sphere>(glm::vec3{ -5, -4, -7 }, radius, material);
		//scene.AddObject(std::move(sphere));
	//scene.AddObject(std::move(sphere));



	// render scene
	canvas.Clear({ 0, 0, 0, 1 });
	scene.Render(canvas, 10);
	canvas.Update();

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


		renderer.PresentCanvas(canvas);
	}

	renderer.Shutdown();

	return 0;

}