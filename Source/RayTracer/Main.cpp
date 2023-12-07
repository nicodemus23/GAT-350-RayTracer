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
	std::shared_ptr<Camera> camera = std::make_shared<Camera>(glm::vec3{ 0, 2, 3 }, glm::vec3{ 0, 1, 0 }, glm::vec3{ 0, 1, 0 }, 70.0f, aspectRatio);
	//std::shared_ptr<Camera> camera = std::make_shared<Camera>(glm::vec3{ 2, 3, 5}, glm::vec3{1, 0, 0 }, glm::vec3{ 0, 1, 0 }, 30.0f, aspectRatio);

	//std::shared_ptr<Camera> camera = std::make_shared<Camera>(glm::vec3{ 0, 1, 10 }, glm::vec3{ 0, 0, 0 }, glm::vec3{ 0, 1, 0 }, 20.0f, aspectRatio);

	// create scene // sky color // ground color
	Scene scene(8, glm::vec3{ 0.1f }, glm::vec3{ 0.0f, 0.0f, 0.0f }); // sky color could be set with the top and bottom color
	scene.SetCamera(camera);

	// create material
	auto lambertian = std::make_shared<Lambertian>(Color::color3_t{ 1, 1, 1 });
	auto metal = std::make_shared<Metal>(Color::color3_t{ 0.8f, 0.6f, 0.2f }, 0.3f);
	auto emissiveMaterial = std::make_shared<Emissive>(Color::color3_t{ 0.8f, 0.6f, 0.2f }, 0.3f);

	auto planeMaterial = std::make_shared<Lambertian>(Color::color3_t{ 0.2, 0.2, 0.2f });
	//glm::vec3 trianglePosition = glm::vec3{ 0, 1, 0 };
	                                       // normal			// position			// material
	auto plane = std::make_unique<Plane>(glm::vec3{ 0, 0, 0 }, glm::vec3{ 0, 2, 0 }, planeMaterial);
	scene.AddObject(std::move(plane));

	auto mesh = std::make_unique<Mesh>(std::make_shared<Emissive>(Color::color3_t{ 0.8f, 0.7f, 0.8f }));
	//glm::vec3 intendedPosition = glm::vec3{ 0, 0.5f, 0 };

	mesh->Load("Models/cube-1.obj", glm::vec3{ 0, 0.5f, 0 }, glm::vec3{ 0, 45, 0 });
	//{
	//
	//	
	//	std::cout << "Cube loaded successfully." << std::endl;

	//	// Get actual position from the mesh
	//	glm::vec3 actualPosition = mesh->GetPosition();
	//	//std::cout << "Intended cube position: (" << intendedPosition.x << ", " << intendedPosition.y << ", " << intendedPosition.z << ")" << std::endl;
	//	std::cout << "Cube position: (" << actualPosition.x << ", " << actualPosition.y << ", " << actualPosition.z << ")" << std::endl;

	//	scene.AddObject(std::move(mesh));
	//} 
	/*else 
	{
		std::cout << "Failed to load the cube." << std::endl;
	}*/
	scene.AddObject(std::move(mesh));


	/*auto triangleMaterial = std::make_shared<Metal>(Color::color3_t{ 1.0f, 0.0f, 0.0f }, 0.3f);
	std::cout << "Triangle created with vertices: "
		<< "V1(" << 0 << ", " << 2 << ", " << 0 << "), "
		<< "V2(" << 0 << ", " << 1 << ", " << 0 << "), "
		<< "V3(" << 0 << ", " << 3 << ", " << 0 << ")" << std::endl;*/

	//											// v1				// v2				// v3				// material
	//auto triangle = std::make_unique<Triangle>(glm::vec3{ 0.1f, 0, 0 }, glm::vec3{ 0, 1.0f, 0.7f }, glm::vec3{ 0.0f, 0, 0.9f }, triangleMaterial);
	// auto triangle = std::make_unique<Triangle>(glm::vec3{ -1, 0, -2 }, glm::vec3{ 1.5, 0, -2 }, glm::vec3{ 0.3, 2, -2 }, std::make_shared<Lambertian>(color3_t{ 1, 0, 0 }));



	// create objects -> add to scene
	/*int sphereGrid = 5;
	float gridSpacing = 1.1f;*/

	//for (int x = -sphereGrid; x <= sphereGrid; x++)
	//{			std::shared_ptr<Material> material;

	//
	//		for (int z = -sphereGrid; z <= sphereGrid; z++)
	//		{
	//			// create random material
	//			float r = Random::random01();
	//			if (r < 0.3f)		material = std::make_shared<Lambertian>(glm::rgbColor(glm::vec3{ Random::random(0, 360), 1.0f, 1.0f }));
	//			else if (r < 0.6f)	material = std::make_shared<Metal>(Color::color3_t{ Random::random(0.5f, 1.0f) }, Random::random(0, 0.5f));
	//			else if (r < 0.9f)	material = std::make_shared<Dielectric>(Color::color3_t{ 1.0f }, Random::random(1.1f, 2));
	//			else				material = std::make_shared<Emissive>(glm::rgbColor(glm::vec3{ Random::random(0, 360), 1.0f, 1.0f }), 5.0f);

	//			// set random sphere radius
	//			float radius = Random::random(0.3f, 0.5f);

	//			// create sphere using random radius and material
	//			auto sphere = std::make_unique<Sphere>(glm::vec3{ x * gridSpacing, radius, z * gridSpacing }, radius, material);
	//			// add sphere to the scene
	//			scene.AddObject(std::move(sphere));
	//		}
	//	
	//
	//}
	//for (int z = -10; z < 10; z++)
	//{

	//	std::shared_ptr<Material> material;

	//	// create random material
	//	float r = Random::random01();
	//	if (r < 0.3f)		material = std::make_shared<Lambertian>(glm::rgbColor(glm::vec3{ Random::random(0, 360), 1.0f, 1.0f }));
	//	else if (r < 0.6f)	material = std::make_shared<Metal>(Color::color3_t{ Random::random(0.5f, 1.0f) }, Random::random(0, 0.5f));
	//	else if (r < 0.9f)	material = std::make_shared<Dielectric>(Color::color3_t{ 1.0f }, Random::random(1.1f, 2));
	//	else				material = std::make_shared<Emissive>(glm::rgbColor(glm::vec3{ Random::random(0, 360), 1.0f, 1.0f }), 5.0f);

	//	// set random sphere radius
	//	float radius = Random::random(0.4f, 0.6f);

	//	auto sphereX = Random::random(-1.0f, 1.0f); // smaller range for x
	//	auto sphereY = radius; // keep it at the radius height
	//	auto sphereZ = z + Random::random(-0.5f, 0.5f); // smaller range for z
	//	auto sphere = std::make_unique<Sphere>(glm::vec3{ sphereX, sphereY, sphereZ }, radius, material);

	//	// create sphere using random radius and material
	//	//auto sphere = std::make_unique<Sphere>(glm::vec3{ x + Random::random(-0.5f, 0.8f), radius, z + Random::random(-0.5f, 0.8f) }, radius, material);
	//	// add sphere to the scene
	//	scene.AddObject(std::move(sphere));
	//}
	//auto sphere = std::make_unique<Sphere>(glm::vec3{ -5, -4, -7 }, radius, material);
		//scene.AddObject(std::move(sphere));
	//scene.AddObject(std::move(sphere));



	// render scene
	canvas.Clear({ 0, 0, 0, 20 });
	scene.Render(canvas, 300);
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