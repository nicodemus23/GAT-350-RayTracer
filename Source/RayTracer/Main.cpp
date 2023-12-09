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
void InitScene03(Scene& scene, const Canvas& canvas);
void InitScene04(Scene& scene, const Canvas& canvas);

int main(int, char**)
{
	std::cout << "'ello Vorld!\n";

	const int width = 400;
	const int height = 300;
	const int samples = 1;
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

	// Cornell Box Cam:
																// position			// direction (target)    // up vector  // fov // aspect ratio
	//std::shared_ptr<Camera> camera = std::make_shared<Camera>(glm::vec3{ 0, 0, 4.5f }, glm::vec3{ 0, 0, 0 }, glm::vec3{ 0, 1, 0 },70.0f, aspectRatio);



	std::shared_ptr<Camera> camera = std::make_shared<Camera>(glm::vec3{ 0, 0, 4.5f }, glm::vec3{ 0, 0, 0 }, glm::vec3{ 0, 1, 0 }, 70.0f, aspectRatio);



	// create scene // sky color // ground color
	Scene scene; // (8, glm::vec3{ 0.1f }, glm::vec3{ 0.2f, 0.2f, 0.2f }); // sky color could be set with the top and bottom color
	scene.SetCamera(camera);

	InitScene04(scene, canvas);
	//InitScene02(scene, canvas);

	// render scene
	canvas.Clear({ 0, 0, 0, 1 });
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
	scene.SetCamera(camera);

	// create material
	auto lambertian = std::make_shared<Lambertian>(Color::color3_t{ 1, 1, 1 });
	auto metal = std::make_shared<Metal>(Color::color3_t{ 0.8f, 0.6f, 0.2f }, 0.3f);
	auto emissiveMaterial = std::make_shared<Emissive>(Color::color3_t{ 0.8f, 0.6f, 0.2f }, 0.3f);

	auto planeMaterial = std::make_shared<Lambertian>(Color::color3_t{ 0.2, 0.2, 0.2f });
	// normal			// position			// material
	auto plane = std::make_unique<Plane>(glm::vec3{ 0, 0, 0 }, glm::vec3{ 0, 2, 0 }, planeMaterial);

	//glm::vec3 trianglePosition = glm::vec3{ 0, 1, 0 };
	auto mesh = std::make_unique<Mesh>(std::make_shared<Emissive>(Color::color3_t{ 0.8f, 0.7f, 0.8f }));
	//glm::vec3 intendedPosition = glm::vec3{ 0, 0.5f, 0 };

	mesh->Load("Models/cube-1.obj", glm::vec3{ 0, 0.5f, 0 }, glm::vec3{ 0, 45, 0 });

	scene.AddObject(std::move(plane));
	scene.AddObject(std::move(mesh));
}


void InitScene02(Scene& scene, const Canvas& canvas)
{
	// create camera
	float aspectRatio = canvas.GetSize().x / (float)canvas.GetSize().y;
	// position			// direction (target)    // up vector  // fov // aspect ratio
	std::shared_ptr<Camera> camera = std::make_shared<Camera>(glm::vec3{ 0, 2, 3 }, glm::vec3{ 0, 1, 0 }, glm::vec3{ 0, 1, 0 }, 70.0f, aspectRatio);
	// create scene // sky color // ground color
	scene.SetCamera(camera);

	// create material
	auto lambertian = std::make_shared<Lambertian>(Color::color3_t{ 1, 1, 1 });
	auto metal = std::make_shared<Metal>(Color::color3_t{ 0.8f, 0.6f, 0.2f }, 0.3f);
	auto emissiveMaterial = std::make_shared<Emissive>(Color::color3_t{ 0.8f, 0.6f, 0.2f }, 0.3f);

	auto planeMaterial = std::make_shared<Lambertian>(Color::color3_t{ 0.2, 0.2, 0.2f });
	// normal			// position			// material
	auto plane = std::make_unique<Plane>(glm::vec3{ 0, 0, 0 }, glm::vec3{ 0, 2, 0 }, planeMaterial);
	scene.AddObject(std::move(plane));

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
}

void InitScene03(Scene& scene, const Canvas& canvas)
{
	// create camera
	float aspectRatio = canvas.GetSize().x / (float)canvas.GetSize().y;
																// position			// direction (target)    // up vector  // fov // aspect ratio
	std::shared_ptr<Camera> camera = std::make_shared<Camera>(glm::vec3{ 0, 2, 2}, glm::vec3{ 0, 1, 0 }, glm::vec3{ 0, 1, 0 }, 20.0f, aspectRatio);

	// create scene // sky color // ground color
	scene.SetCamera(camera);

	// create material
	auto dielectric = std::make_shared<Dielectric>(Color::color3_t{ 1.0f }, 1.5f);
	auto lambertian = std::make_shared<Lambertian>(Color::color3_t{ 1, 1, 1 });
	auto metal = std::make_shared<Metal>(Color::color3_t{ 0.8f, 0.6f, 0.2f }, 0.3f);
															// color				// intensity
	auto emissiveMaterial = std::make_shared<Emissive>(Color::color3_t{ 0.8f, 0.6f, 0.2f }, 1.0f);

	//auto planeMaterial = std::make_shared<Lambertian>(Color::color3_t{ 0.2, 0.2, 0.2f });
										// normal			// position			// material
	//auto plane = std::make_unique<Plane>(glm::vec3{ 0, 0, 0 }, glm::vec3{ 0, 2, 0 }, planeMaterial);
	//plane = std::make_unique<Plane>(glm::vec3{ 0, 0, 0 }, glm::vec3{ 0, 2, 0 }, planeMaterial);


	//auto planeMaterial = std::make_shared<Lambertian>(glm::rgbColor(glm::vec3{ Random::random(0, 360), 1.0f, 1.0f }));
	//glm::vec3 planePosition = glm::vec3{ 0, 0, 0 };

	

	auto cube = std::make_unique<Mesh>(std::make_shared<Lambertian>(Color::color3_t{ 1, 1, 1 }));
	//auto sphere = std::make_unique<Mesh>(std::make_shared<Lambertian>(Color::color3_t{ 1, 1, 1 }));

	auto backPlane = std::make_unique<Mesh>(std::make_shared<Lambertian>(Color::color3_t{ 1.0f, 1.0f, 1.0f }));
	auto topPlane = std::make_unique<Mesh>(std::make_shared<Lambertian>(Color::color3_t{ 1.0f, 1.0f, 1.0f }));
	auto floorPlane = std::make_unique<Mesh>(std::make_shared<Lambertian>(Color::color3_t{ 1.0f, 1.0f, 1.0f }));
	auto redPlane = std::make_unique<Mesh>(std::make_shared<Lambertian>(Color::color3_t{ 1.0f, 0.0f, 0.0f }));
	auto greenPlane = std::make_unique<Mesh>(std::make_shared<Lambertian>(Color::color3_t{ 0.0f, 1.0f, 0.0f }));

	auto lightPlane = std::make_unique<Mesh>(std::make_shared<Emissive>(Color::color3_t{ 0.95f, 0.95f, 0.95f }, 18.0f));
										
	cube->Load("Models/cube-1.obj", glm::vec3{ -0.65f, -1.2f, 1.0f }, glm::vec3{ 0, 55, 0 }, glm::vec3{0.75f, 0.75f , 0.75f });
	//sphere->Load("Models/sphere.obj", glm::vec3{ 0.5f, -1.0f, 1.5f }, glm::vec3{ 0, 0, 0 }, glm::vec3{ 0.5f, 0.5f , 0.5f });

	// create sphere using random radius and material
	float radius = 0.5f;
	auto sphere = std::make_unique<Sphere>(glm::vec3{ 0.5f, -1.0f, 1.5f }, radius, lambertian);
	//	// add sphere to the scene
	//	scene.AddObject(std::move(sphere));

	backPlane->Load("Models/quad-1.obj", glm::vec3{ 0, 0, 0 }, glm::vec3{ 0, 0, 0 }, glm::vec3{3, 3, 1});
	topPlane->Load("Models/quad-1.obj", glm::vec3{ 0, 1.5f, 1.5f }, glm::vec3{ 90, 0, 0 }, glm::vec3{ 3, 3, 1 });
	floorPlane->Load("Models/quad-1.obj", glm::vec3{ 0, -1.5f, 1.5f }, glm::vec3{ -90, 0, 0 }, glm::vec3{ 3, 3, 1 });
	redPlane->Load("Models/quad-1.obj", glm::vec3{ -1.5f, 0, 1.5f }, glm::vec3{ 0, 90, 0 }, glm::vec3{ 3, 3, 1 });
	greenPlane->Load("Models/quad-1.obj", glm::vec3{ 1.5f, 0, 1.5f }, glm::vec3{ 0, -90, 0 }, glm::vec3{ 3, 3, 1 });

	lightPlane->Load("Models/quad-1.obj", glm::vec3{ 0, 1.49f, 1.5f }, glm::vec3{ 90, 0, 0 }, glm::vec3{0.75f, 0.75f, 1});

	// add meshes to the scene
	// planes 
	scene.AddObject(std::move(backPlane));
	scene.AddObject(std::move(topPlane));
	scene.AddObject(std::move(floorPlane));
	scene.AddObject(std::move(redPlane));
	scene.AddObject(std::move(greenPlane));

	scene.AddObject(std::move(cube));
	scene.AddObject(std::move(sphere));

	scene.AddObject(std::move(lightPlane));

	// add meshes to the scene
	//scene.AddObject(std::move(plane));
	//scene03.AddObject(std::move(plane));
}

void InitScene04(Scene& scene, const Canvas& canvas)
{
	// create camera
	float aspectRatio = canvas.GetSize().x / (float)canvas.GetSize().y;
	// position			// direction (target)    // up vector  // fov // aspect ratio
	std::shared_ptr<Camera> camera = std::make_shared<Camera>(glm::vec3{ 0, 1.5f, 7 }, glm::vec3{ 0, -2.5f, 0 }, glm::vec3{ 0, 1, 0 }, 20.0f, aspectRatio);

	// create scene // sky color // ground color
	scene.SetCamera(camera);

	// create material										// color				// intensity
	auto dielectric = std::make_shared<Dielectric>(Color::color3_t{ 1.0f }, 1.5f);
	auto dielectricR = std::make_shared<Dielectric>(Color::color3_t{ 0.639f, 0.542f, 0.536f }, 1.5f);
	auto dielectricG = std::make_shared<Dielectric>(Color::color3_t{ 0.564f, 0.594f, 0.524f }, 1.5f);
	auto lambertian = std::make_shared<Lambertian>(Color::color3_t{ 1, 1, 1 });
	auto metal = std::make_shared<Metal>(Color::color3_t{ 0.8f, 0.6f, 0.2f }, 0.3f);
	// color				// intensity
	auto emissiveMaterial = std::make_shared<Emissive>(Color::color3_t{ 0.8f, 0.6f, 0.2f }, 1.0f);

	//auto planeMaterial = std::make_shared<Lambertian>(Color::color3_t{ 0.2, 0.2, 0.2f });
										// normal			// position			// material
	//auto plane = std::make_unique<Plane>(glm::vec3{ 0, 0, 0 }, glm::vec3{ 0, 2, 0 }, planeMaterial);
	//plane = std::make_unique<Plane>(glm::vec3{ 0, 0, 0 }, glm::vec3{ 0, 2, 0 }, planeMaterial);


	//auto planeMaterial = std::make_shared<Lambertian>(glm::rgbColor(glm::vec3{ Random::random(0, 360), 1.0f, 1.0f }));
	//glm::vec3 planePosition = glm::vec3{ 0, 0, 0 };



	auto cube = std::make_unique<Mesh>(std::make_shared<Lambertian>(Color::color3_t{ 1, 1, 1 }));
	auto diamond = std::make_unique<Mesh>(dielectric);
	auto diamondR = std::make_unique<Mesh>(dielectricR);
	auto diamondG = std::make_unique<Mesh>(dielectricG);
	//auto sphere = std::make_unique<Mesh>(std::make_shared<Lambertian>(Color::color3_t{ 1, 1, 1 }));

	auto backPlane = std::make_unique<Mesh>(std::make_shared<Lambertian>(Color::color3_t{ 1.0f, 1.0f, 1.0f }));
	auto topPlane = std::make_unique<Mesh>(std::make_shared<Lambertian>(Color::color3_t{ 1.0f, 1.0f, 1.0f }));
	auto floorPlane = std::make_unique<Mesh>(std::make_shared<Lambertian>(Color::color3_t{ 1.0f, 1.0f, 1.0f }));
	auto redPlane = std::make_unique<Mesh>(std::make_shared<Lambertian>(Color::color3_t{ 1.0f, 0.0f, 0.0f }));
	auto greenPlane = std::make_unique<Mesh>(std::make_shared<Lambertian>(Color::color3_t{ 0.0f, 1.0f, 0.0f }));

	auto lightPlane = std::make_unique<Mesh>(std::make_shared<Emissive>(Color::color3_t{ 0.95f, 0.95f, 0.95f }, 18.0f));

	cube->Load("Models/cube-1.obj", glm::vec3{ -0.65f, -1.2f, 1.0f }, glm::vec3{ 0, 55, 0 }, glm::vec3{ 0.75f, 0.75f , 0.75f });
													
	diamond->Load("Models/diamond_1.obj", glm::vec3{ -0.65f, -1.2f, 1.1f }, glm::vec3{ 0, 55, 0 }, glm::vec3{ 0.75f, 0.75f , 0.75f });
	diamondR->Load("Models/diamond_1.obj", glm::vec3{ 0.65f, -1.2f, 1.2f }, glm::vec3{ 0, 25, 0 }, glm::vec3{ 0.75f, 0.75f , 0.75f });
	diamondG->Load("Models/diamond_1.obj", glm::vec3{ 0.25f, -1.2f, 2.5f }, glm::vec3{ 0, 75, 0 }, glm::vec3{ 0.75f, 0.75f , 0.75f });
	//sphere->Load("Models/sphere.obj", glm::vec3{ 0.5f, -1.0f, 1.5f }, glm::vec3{ 0, 0, 0 }, glm::vec3{ 0.5f, 0.5f , 0.5f });

	// create sphere using random radius and material
	float radius = 0.5f;
	auto sphere = std::make_unique<Sphere>(glm::vec3{ 0.5f, -1.0f, 1.5f }, radius, dielectric);
	//	// add sphere to the scene
	//	scene.AddObject(std::move(sphere));

	//backPlane->Load("Models/quad-1.obj", glm::vec3{ 0, 0, 0 }, glm::vec3{ 0, 0, 0 }, glm::vec3{ 3, 3, 1 });
	//topPlane->Load("Models/quad-1.obj", glm::vec3{ 0, 1.5f, 1.5f }, glm::vec3{ 90, 0, 0 }, glm::vec3{ 3, 3, 1 });
	floorPlane->Load("Models/quad-1.obj", glm::vec3{ 0, -1.5f, 1.5f }, glm::vec3{ -90, 0, 0 }, glm::vec3{ 20, 20, 1 });
	//redPlane->Load("Models/quad-1.obj", glm::vec3{ -1.5f, 0, 1.5f }, glm::vec3{ 0, 90, 0 }, glm::vec3{ 3, 3, 1 });
	//greenPlane->Load("Models/quad-1.obj", glm::vec3{ 1.5f, 0, 1.5f }, glm::vec3{ 0, -90, 0 }, glm::vec3{ 3, 3, 1 });

	lightPlane->Load("Models/quad-1.obj", glm::vec3{ 0, 1.49f, 1.5f }, glm::vec3{ 90, 0, 0 }, glm::vec3{ 0.75f, 0.75f, 1 });

	// add meshes to the scene
	// planes 
	//scene.AddObject(std::move(backPlane));
	//scene.AddObject(std::move(topPlane));
	scene.AddObject(std::move(floorPlane));
	scene.AddObject(std::move(diamond));
	scene.AddObject(std::move(diamondR));
	scene.AddObject(std::move(diamondG));

	//scene.AddObject(std::move(redPlane));
	//scene.AddObject(std::move(greenPlane));

	//scene.AddObject(std::move(cube));
	//scene.AddObject(std::move(sphere));

	scene.AddObject(std::move(lightPlane));

	// add meshes to the scene
	//scene.AddObject(std::move(plane));
	//scene03.AddObject(std::move(plane));
}

// create one sphere with a fixed radius and material and add to scene
//auto sphere = std::make_unique<Sphere>(glm::vec3{ -5, -4, -7 }, radius, material);
//scene.AddObject(std::move(sphere));
