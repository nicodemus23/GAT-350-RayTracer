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
#include "Plane.h"
#include "Triangle.h"
#include "Mesh.h"



void InitScene01(Scene& scene, const Canvas& canvas);
void InitScene02(Scene& scene, const Canvas& canvas);

int main(int, char**)
{
	std::cout << "'ello Vorld!\n";

	const int width = 400;
	const int height = 300;
	const int samples = 20;
	const int depth = 5;

	// renderer instance
	Renderer renderer;

	renderer.Initialize();

	// create window
	renderer.CreateWindow("Ray Tracer, bruh...", width, height);

	// create canvas
	Canvas canvas(width, height, renderer);

	// create camera
	float aspectRatio = canvas.GetSize().x / (float)canvas.GetSize().y;
	// position			// direction (target)    // up vector  // fov // aspect ratio
	std::shared_ptr<Camera> camera = std::make_shared<Camera>(glm::vec3{ 0, 2, 3 }, glm::vec3{ 0, 1, 0 }, glm::vec3{ 0, 1, 0 }, 70.0f, aspectRatio);


	// create scene // sky color // ground color
	Scene scene; // (8, glm::vec3{ 0.1f }, glm::vec3{ 0.2f, 0.2f, 0.2f }); // sky color could be set with the top and bottom color
	scene.SetCamera(camera);

	InitScene01(scene, canvas);
	//InitScene02(scene, canvas);

	// render scene
	canvas.Clear({ 0, 0, 0, 20 });
	scene.Render(canvas, samples, depth);
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

void InitScene01(Scene& scene, const Canvas& canvas)
{
	// create camera
	float aspectRatio = canvas.GetSize().x / (float)canvas.GetSize().y;
	// position			// direction (target)    // up vector  // fov // aspect ratio
	std::shared_ptr<Camera> camera = std::make_shared<Camera>(glm::vec3{ 0, 2, 3 }, glm::vec3{ 0, 1, 0 }, glm::vec3{ 0, 1, 0 }, 70.0f, aspectRatio);

	// create scene // sky color // ground color
	Scene scene01(8, glm::vec3{ 0.1f }, glm::vec3{ 0.0f, 0.0f, 0.0f }); // sky color could be set with the top and bottom color
	scene01.SetCamera(camera);

	// create material
	auto lambertian = std::make_shared<Lambertian>(Color::color3_t{ 1, 1, 1 });
	auto metal = std::make_shared<Metal>(Color::color3_t{ 0.8f, 0.6f, 0.2f }, 0.3f);
	auto emissiveMaterial = std::make_shared<Emissive>(Color::color3_t{ 0.8f, 0.6f, 0.2f }, 0.3f);

	auto planeMaterial = std::make_shared<Lambertian>(Color::color3_t{ 0.2, 0.2, 0.2f });
	// normal			// position			// material
	auto plane = std::make_unique<Plane>(glm::vec3{ 0, 0, 0 }, glm::vec3{ 0, 2, 0 }, planeMaterial);
	scene01.AddObject(std::move(plane));

	//glm::vec3 trianglePosition = glm::vec3{ 0, 1, 0 };
	auto mesh = std::make_unique<Mesh>(std::make_shared<Emissive>(Color::color3_t{ 0.8f, 0.7f, 0.8f }));
	//glm::vec3 intendedPosition = glm::vec3{ 0, 0.5f, 0 };

	mesh->Load("Models/cube-1.obj", glm::vec3{ 0, 0.5f, 0 }, glm::vec3{ 0, 45, 0 });

	scene.AddObject(std::move(mesh));
}


void InitScene02(Scene& scene, const Canvas& canvas)
{
	// create camera
	float aspectRatio = canvas.GetSize().x / (float)canvas.GetSize().y;
	// position			// direction (target)    // up vector  // fov // aspect ratio
	std::shared_ptr<Camera> camera = std::make_shared<Camera>(glm::vec3{ 0, 2, 3 }, glm::vec3{ 0, 1, 0 }, glm::vec3{ 0, 1, 0 }, 70.0f, aspectRatio);

	// create scene // sky color // ground color
	Scene scene01(8, glm::vec3{ 0.1f }, glm::vec3{ 0.0f, 0.0f, 0.0f }); // sky color could be set with the top and bottom color
	scene01.SetCamera(camera);

	// create material
	auto lambertian = std::make_shared<Lambertian>(Color::color3_t{ 1, 1, 1 });
	auto metal = std::make_shared<Metal>(Color::color3_t{ 0.8f, 0.6f, 0.2f }, 0.3f);
	auto emissiveMaterial = std::make_shared<Emissive>(Color::color3_t{ 0.8f, 0.6f, 0.2f }, 0.3f);

	auto planeMaterial = std::make_shared<Lambertian>(Color::color3_t{ 0.2, 0.2, 0.2f });
	// normal			// position			// material
	auto plane = std::make_unique<Plane>(glm::vec3{ 0, 0, 0 }, glm::vec3{ 0, 2, 0 }, planeMaterial);
	scene01.AddObject(std::move(plane));

	//create objects -> add to scene
	int sphereGrid = 5;
	float gridSpacing = 1.1f;

	for (int x = -sphereGrid; x <= sphereGrid; x++)
	{
		std::shared_ptr<Material> material;


		for (int z = -sphereGrid; z <= sphereGrid; z++)
		{
			// create random material
			float r = Random::random01();
			if (r < 0.3f)		material = std::make_shared<Lambertian>(glm::rgbColor(glm::vec3{ Random::random(0, 360), 1.0f, 1.0f }));
			else if (r < 0.6f)	material = std::make_shared<Metal>(Color::color3_t{ Random::random(0.5f, 1.0f) }, Random::random(0, 0.5f));
			else if (r < 0.9f)	material = std::make_shared<Dielectric>(Color::color3_t{ 1.0f }, Random::random(1.1f, 2));
			else				material = std::make_shared<Emissive>(glm::rgbColor(glm::vec3{ Random::random(0, 360), 1.0f, 1.0f }), 5.0f);

			// set random sphere radius
			float radius = Random::random(0.3f, 0.5f);

			// create sphere using random radius and material
			auto sphere = std::make_unique<Sphere>(glm::vec3{ x * gridSpacing, radius, z * gridSpacing }, radius, material);
			// add sphere to the scene
			scene.AddObject(std::move(sphere));
		}


	}

	// create sphere using random radius and material and add to scene
	for (int z = -10; z < 10; z++)
	{

		std::shared_ptr<Material> material;

		// create random material
		float r = Random::random01();
		if (r < 0.3f)		material = std::make_shared<Lambertian>(glm::rgbColor(glm::vec3{ Random::random(0, 360), 1.0f, 1.0f }));
		else if (r < 0.6f)	material = std::make_shared<Metal>(Color::color3_t{ Random::random(0.5f, 1.0f) }, Random::random(0, 0.5f));
		else if (r < 0.9f)	material = std::make_shared<Dielectric>(Color::color3_t{ 1.0f }, Random::random(1.1f, 2));
		else				material = std::make_shared<Emissive>(glm::rgbColor(glm::vec3{ Random::random(0, 360), 1.0f, 1.0f }), 5.0f);

		// set random sphere radius
		float radius = Random::random(0.4f, 0.6f);

		auto sphereX = Random::random(-1.0f, 1.0f); // smaller range for x
		auto sphereY = radius; // keep it at the radius height
		auto sphereZ = z + Random::random(-0.5f, 0.5f); // smaller range for z
		auto sphere = std::make_unique<Sphere>(glm::vec3{ sphereX, sphereY, sphereZ }, radius, material);

		// create sphere using random radius and material
		//auto sphere = std::make_unique<Sphere>(glm::vec3{ x + Random::random(-0.5f, 0.8f), radius, z + Random::random(-0.5f, 0.8f) }, radius, material);
		// add sphere to the scene
		scene.AddObject(std::move(sphere));
	}

	// create one sphere with a fixed radius and material and add to scene
	//auto sphere = std::make_unique<Sphere>(glm::vec3{ -5, -4, -7 }, radius, material);
	//scene.AddObject(std::move(sphere));
}