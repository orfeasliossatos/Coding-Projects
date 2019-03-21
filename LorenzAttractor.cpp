#include "LorenzAttractor.h"

LorenzAttractor::LorenzAttractor()
{
	// Text
	font.loadFromFile("FUTRFW.ttf");
	text.setFont(font);
	text.setString(names[u]);
	text.setScale(0.1f, 0.1f);
	text.setPosition(sf::Vector2f(-85, -45));

	// Re-center view
	view.setCenter(sf::Vector2f(0.0f, 0.0f));
	view.setSize(sf::Vector2f(static_cast<float>(g_screenWidth / 10), static_cast<float>(g_screenHeight / 10)));

	// Set parameters
	params = 
	{
		{10.0f, 30.0f, 8 / 3},
		{1.24f, 1.1f, 4.4f, 3.21f},
		{0.95f, 0.7f, 0.6f, 3.5f, 0.25f, 0.1f},
		{0.3f, 1.0f},
		{5.0f, -10.0f, -0.38f},
		{1.4f},
		{0.001f, 0.2f, 1.1f},
		{0.4f, 0.175f},
		{1.5f},
		{0.2f}
	};

	colours =
	{
		sf::Color::Color(115, 62, 101, 42), // 42
		sf::Color::Color(255, 126, 210, 127),
		sf::Color::Color(109, 193, 202, 179),
		sf::Color::Color(135, 216, 10, 203),
		sf::Color::Color(125, 26, 133, 99),
		sf::Color::Color(8, 161, 163, 57),
		sf::Color::Color(134, 184, 38, 183),
		sf::Color::Color(132, 159, 149, 188),
		sf::Color::Color(100, 195, 167, 160),
		sf::Color::Color(190, 242, 126, 252),
	};

	trail_colours_params =
	{
		{61.3f, 62.1f, 33.9f},
		{-65.5125f, -27.8521f, -97.0907f},
		{-47.3382f, -49.5409f, -33.8347f},
		{-12.9346f, -76.7609f, 70.7356f},
		{-12.0673f, 51.6949f, 97.4566f},
		{93.4094f, -16.196f, 40.8949f},
		{-37.5288f, -31.3912f, -48.0061f},
		{-5.6245f, -49.0192f, 19.271f},
		{98.011f, -81.8857f, -80.084f},
		{44.3435f, -93.5679f, -52.0752f},

	};
	std::cout << "\n\n\n";
	for (unsigned c = 0; c < colours.size(); c++)
	{
		std::cout << static_cast<int>(colours[c].r) << " " <<
			static_cast<int>(colours[c].g) << " " <<
			static_cast<int>(colours[c].b) << " " <<
			static_cast<int>(colours[c].a) << std::endl;
		std::cout << trail_colours_params[c][0] << " " << trail_colours_params[c][1] << " " << trail_colours_params[c][2] << std::endl;

	}

	circle.resize(num_points);
	point.resize(num_points);
	trail.resize(num_points);



	// Create trial trackers
	for (unsigned i = 0; i < num_points; i++)
		j.push_back(0);

	for (unsigned i = 0; i < num_points; i++)
	{
		// Create balls
		circle[i].setRadius(0.5f);
		circle[i].setOrigin(circle[i].getRadius(), circle[i].getRadius());
		circle[i].setFillColor(colours[u]);
	
		// Set initial positions
		point[i] = { getRandomNumber(1.0f, 1.0f), getRandomNumber(1.0f, 1.0f), getRandomNumber(1.0f, 1.0f) };

		// Create trails
		trail[i].resize(trail_length);
		for (auto &pos : trail[i])
			pos = point[i];

	}

	// Prepare colours
	

	// Create lineStrip object with two vertices. The first line should start with a first point.
	line.setPrimitiveType(sf::LinesStrip);
	line.append(sf::Vector2f(point[0].x, point[0].y)); 
	line.append(sf::Vector2f(point[0].x, point[0].y)); 

	// Set Camera
	switch (u)
	{
	case 0: {cam_position = { 0, 0, -50 }; cam_angle = { 0, 0, 0 }; break; }
	case 1: {cam_position = { 1.07676f, 0.3f, -0.447995f }; cam_angle = { 0.1f, 4.84f, 0.0f }; break; }
	case 2: {cam_position = { 2.25, 0, 0.75 }; cam_angle = { 0, -pi / 2, 0 }; break; }
	case 3: {cam_position = { -7.5, 5, -15 }; cam_angle = { 0, pi / 6, 0 }; break; }
	case 4: {cam_position = { 51.310f, -4.8f, 25.151f }; cam_angle = { -0.16f, -2.1f, 0.0f }; break; }
	case 5: {cam_position = { -23.357f, -16.4f, -20.731f }; cam_angle = { -0.5f, -5.48f, 0.0f }; break; }
	case 6: {cam_position = { 1.0216f, -5.7f, 6.1861f }; cam_angle = { -0.16f, 3.34f, 0.0f }; break; }
	case 7: {cam_position = { 0, 0, -0.5 }; cam_angle = { 0, 0, -0.134f }; break; }
	case 8: {cam_position = { -0.14397f, -8.4f, -1.3497f }; cam_angle = { -1.66f, -2.94f, 0 }; break; }
	case 9: {cam_position = { 7.1565f, 4.2f, 2.6844f }; cam_angle = { 0.48f, -1.92f, 0 }; break; }
	}
}

void LorenzAttractor::input(sf::RenderWindow &window)
{
	while (window.pollEvent(event))
	{
		// Window
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
			endSubProgram = true;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::F))
		{
			isFullscreen = !isFullscreen;
			window.create(sf::VideoMode(static_cast<int>(g_screenWidth), static_cast<int>(g_screenHeight)), "Coding Projects", (isFullscreen ? sf::Style::Fullscreen : sf::Style::Default), sf::ContextSettings());
			window.setPosition(sf::Vector2i(0, 0));
			window.setVerticalSyncEnabled(true);
			window.setFramerateLimit(60);
		}
		if ((sf::Keyboard::isKeyPressed(sf::Keyboard::H) || sf::Keyboard::isKeyPressed(sf::Keyboard::G)) && input_timer >= 0.1)
		{
			input_timer = 0;

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::H))
			{
				u++;
				if (u == params.size())
					u--;
			}
			else
			{
				u--;
				if (u == -1)
					u++;
			}

			switch (u)
			{
			case 0: {cam_position = { 0, 0, -50 }; cam_angle = { 0, 0, 0 }; break; }
			case 1: {cam_position = { 1.07676f, 0.3f, -0.447995f }; cam_angle = { 0.1f, 4.84f, 0.0f }; break; }
			case 2: {cam_position = { 2.25, 0, 0.75 }; cam_angle = { 0, -pi / 2, 0 }; break; }
			case 3: {cam_position = { -7.5, 5, -15 }; cam_angle = { 0, pi / 6, 0 }; break; }
			case 4: {cam_position = { 51.310f, -4.8f, 25.151f }; cam_angle = { -0.16f, -2.1f, 0 }; break; }
			case 5: {cam_position = { -23.357f, -16.4f, -20.731f }; cam_angle = { -0.5f, -5.48f, 0.0f }; break; }
			case 6: {cam_position = { 1.0216f, -5.7f, 6.1861f }; cam_angle = { -0.16f, 3.34f, 0.0f }; break; }
			case 7: {cam_position = { 0, 0, -0.5 }; cam_angle = { 0, 0, 0 }; break; }
			case 8: {cam_position = { -0.1439f, -8.4f, -1.3497f }; cam_angle = { -1.66f, -2.94f, 0 }; break; }
			case 9: {cam_position = { 7.1565f, 4.2f, 2.6844f }; cam_angle = { 0.48f, -1.92f, 0 }; break; }
			}

			for (unsigned i = 0; i < num_points; i++)
			{
				circle[i].setFillColor(colours[u]);
				point[i] = { getRandomNumber(-0.001f, 0.001f), getRandomNumber(-0.001f, 0.001f), getRandomNumber(-0.001f, 0.001f) };
			}
			for (unsigned i = 0; i < num_points; i++)
			{
				for (auto &pos : trail[i])
					pos = point[i];
			}

			text.setString(names[u]);
		}
	}
}

void LorenzAttractor::update()
{
	/// Calculate timestep
	timestep = clock.getElapsedTime().asSeconds();
	input_timer += timestep;
	clock.restart();

	timestep *= speed; // Slow down or speed up time.

	// Update position according to chosen equation u
	std::vector<float> &m = params[u];
	switch (u)
	{
	case 0: 
	{	
		for (unsigned i = 0; i < num_points; i++)
		{
			point[i].x += static_cast<float>(m[0] * (point[i].y - point[i].x) * timestep);
			point[i].y += static_cast<float>((point[i].x * (m[1] - point[i].z) - point[i].y) * timestep);
			point[i].z += static_cast<float>((point[i].x * point[i].y - m[2] * point[i].z) * timestep);
		}
		break;
	}
	case 1:
	{
		for (unsigned i = 0; i < num_points; i++)
		{
			float h1 = 0.5f * (abs(point[i].x + 1) - abs(point[i].x - 1));
			float h2 = 0.5f * (abs(point[i].y + 1) - abs(point[i].y - 1));
			float h3 = 0.5f * (abs(point[i].z + 1) - abs(point[i].z - 1));

			point[i].x += static_cast<float>((-point[i].x + m[0] * h1 - m[3] * h2 - m[3] * h3) * timestep);
			point[i].y += static_cast<float>((-point[i].y - m[3] * h1 + m[1] * h2 - m[2] * h3) * timestep);
			point[i].z += static_cast<float>((-point[i].z - m[3] * h1 + m[2] * h2 + h3) * timestep);
		}
		break;
	}
	case 2: 
	{
		for (unsigned i = 0; i < num_points; i++)
		{
			point[i].x += static_cast<float>(((point[i].z - m[1]) * point[i].x  - m[3] * point[i].y) * timestep);
			point[i].y += static_cast<float>((m[3] * point[i].x + (point[i].z - m[1]) * point[i].y) * timestep);
			point[i].z += static_cast<float>((m[2] + m[0] * point[i].z - (point[i].z * point[i].z * point[i].z) / 3 - (point[i].x * point[i].x + point[i].y * point[i].y) * (1 + m[4] * point[i].z) + m[5] * point[i].z * point[i].x * point[i].x * point[i].x) * timestep);
		}
		break;
	}
	case 3:
	{
		for (unsigned i = 0; i < num_points; i++)
		{
			point[i].x += static_cast<float>((point[i].x * (4 - point[i].y) + m[0] * point[i].z) * timestep);
			point[i].y += static_cast<float>((-point[i].y * (1 - point[i].x * point[i].x)) * timestep);
			point[i].z += static_cast<float>((-point[i].x * (1.5 - point[i].z * m[1]) - 0.05 * point[i].z) * timestep);
		}
		break;
	}
	case 4:
	{
		for (unsigned i = 0; i < num_points; i++)
		{
			point[i].x += static_cast<float>((m[0] * point[i].x - point[i].y * point[i].z) * timestep * 0.25f);
			point[i].y += static_cast<float>((m[1] * point[i].y + point[i].x * point[i].z) * timestep * 0.25f);
			point[i].z += static_cast<float>((m[2] * point[i].z + point[i].x * point[i].y / 3) * timestep * 0.25f);
		}
		break;
	}
	case 5:
	{
		for (unsigned i = 0; i < num_points; i++)
		{
			point[i].x += static_cast<float>((-m[0] * point[i].x - 4 * point[i].y - 4 * point[i].z - point[i].y * point[i].y) * timestep);
			point[i].y += static_cast<float>((-m[0] * point[i].y - 4 * point[i].z - 4 * point[i].x - point[i].z * point[i].z) * timestep);
			point[i].z += static_cast<float>((-m[0] * point[i].z - 4 * point[i].x - 4 * point[i].y - point[i].x * point[i].x) * timestep);
		}
		break;
	}
	case 6:
	{
		for (unsigned i = 0; i < num_points; i++)
		{
			point[i].x += static_cast<float>(((1 / m[1] - m[0]) * point[i].x + point[i].z + point[i].x * point[i].y) * timestep);
			point[i].y += static_cast<float>((-m[1] * point[i].y - point[i].x * point[i].x) * timestep);
			point[i].z += static_cast<float>((-point[i].x - m[2] * point[i].z) * timestep);
		}
		break;
	}
	case 7:
	{
		for (unsigned i = 0; i < num_points; i++)
		{
			point[i].x += static_cast<float>((-m[0] * point[i].x + point[i].y + 10.0f * point[i].y * point[i].z) * timestep);
			point[i].y += static_cast<float>((-point[i].x - 0.4 * point[i].y + 5.0f * point[i].x * point[i].z) * timestep);
			point[i].z += static_cast<float>((m[1] * point[i].z - 5.0f * point[i].x * point[i].y) * timestep);
		}
		break;
	}
	case 8:
	{
		for (unsigned i = 0; i < num_points; i++)
		{
			point[i].x += static_cast<float>((point[i].y) * timestep);
			point[i].y += static_cast<float>((-point[i].x + point[i].y * point[i].z) * timestep);
			point[i].z += static_cast<float>((m[0] - point[i].y * point[i].y) * timestep);
		}
		break;
	}
	case 9:
	{
		for (unsigned i = 0; i < num_points; i++)
		{
			point[i].x += static_cast<float>((-m[0] * point[i].x + sin(point[i].y)) * timestep);
			point[i].y += static_cast<float>((-m[0] * point[i].y + sin(point[i].z)) * timestep);
			point[i].z += static_cast<float>((-m[0] * point[i].z + sin(point[i].x)) * timestep);
		}
		break;
	}
	}

	/// Update Camera Position

	// Move Left and Right
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		cam_position.x -= sin(cam_angle[1] + pi / 2.0f) * 0.25f;
		cam_position.z -= cos(cam_angle[1] + pi / 2.0f) * 0.25f;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		cam_position.x += sin(cam_angle[1] + pi / 2.0f) * 0.25f;
		cam_position.z += cos(cam_angle[1] + pi / 2.0f) * 0.25f;
	}

	// Move Forwards and Backwards
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		cam_position.z -= cos(cam_angle[1]) * 0.25f;
		cam_position.x -= sin(cam_angle[1]) * 0.25f;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		cam_position.z += cos(cam_angle[1]) * 0.25f;
		cam_position.x += sin(cam_angle[1]) * 0.25f;
	}

	// Move Up and Down
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
		cam_position.y += 0.1f;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
		cam_position.y -= 0.1f;

	/// Update Camera Angle

	// Look Left and Right
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		cam_angle[1] -= 0.003f;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		cam_angle[1] += 0.003f;


	// Look Up and Down 
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		cam_angle[0] += 0.003f;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		cam_angle[0] -= 0.003f;

	/// Compute Rotation Matrixes

	rotMatrixX = 
	{
		{1, 0, 0},
		{0, cos(cam_angle[0]), sin(cam_angle[0])},
		{0, -sin(cam_angle[0]), cos(cam_angle[0])}
	};
	rotMatrixY = 
	{
		{cos(cam_angle[1]), 0, -sin(cam_angle[1])},
		{0, 1, 0},
		{sin(cam_angle[1]), 0, cos(cam_angle[1])}
	};
	rotMatrixZ =
	{
		{cos(cam_angle[2]), sin(cam_angle[2]), 0},
		{-sin(cam_angle[2]), cos(cam_angle[2]), 0},
		{0, 0, 1}
	};


	// Change speed
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::PageUp))
		speed += 0.025f;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::PageDown))
		speed -= 0.025f;
}

void LorenzAttractor::draw(sf::RenderWindow &window)
{
	// For every point
	for (unsigned g = 0; g < num_points; g++)
	{
		/// Draw circle

		// Projection maths
		sf::Vector3f d;
		d = point[g] - cam_position;
		d = rotMatrixX * (rotMatrixY * (rotMatrixZ * d));

		// Only if the point is infront of the camera
		if (d.z >= 0)
		{
			projected_point =
			{
				display_position.z * d.x / d.z + display_position.x,
				display_position.z * d.y / d.z + display_position.y
			};

			circle[g].setPosition(sf::Vector2f(projected_point.x, projected_point.y));
			window.draw(circle[g]);
		}

		/// Draw trail

		/* 
			The point of this algorithm is to use indexes in a clever manner in order to avoid shifting every
			previous position one across in "trail" every frame, which takes a lot of time. It flows like a 
			"shifting" >for< loop.
		*/

		trail[g][j[g]] = point[g];		 // Add most recent position to trail at index j[g]
		j[g]++;							 // j[g] incremented every frame, shifting the beginning of the for loop.
		if (j[g] == trail[g].size() - 1) // If j[g] gets to the final index, set it to 0
		{
			j[g] = 0;
			trail[g][trail[g].size() - 1] = trail[g][trail[g].size() - 2]; // This has to be done.
		}

		int k = 0; // Index that goes from 0 to num_points, used for colour 

		// Starting from the index i right after j[g], then from 0 all the way to j[g].
		int i = j[g] + 1;					
		while (i != j[g])
		{

			// Project the front end of the trail
			sf::Vector3f d1;
			d1 = trail[g][i] - cam_position;
			d1 = rotMatrixX * (rotMatrixY * (rotMatrixZ * d1));

			sf::Vector2f proj1;
			proj1 = { display_position.z * d1.x / d1.z + display_position.x,
				display_position.z * d1.y / d1.z + display_position.y };

			line[0].position = proj1;

			// Project the back end of the trail
			sf::Vector3f d2;
			if (i == 0)
				d2 = trail[g][trail[g].size() - 2] - cam_position;
			else
				d2 = trail[g][i - 1] - cam_position;
			d2 = rotMatrixX * (rotMatrixY * (rotMatrixZ * d2));

			sf::Vector2f proj2;
			proj2 = { display_position.z * d2.x / d2.z + display_position.x,
				display_position.z * d2.y / d2.z + display_position.y };

			line[1].position = proj2;

			// Calculate trail colours
			sf::Color fade;
			fade = sf::Color::Color(
				clamp(colours[u].r + trail_colours_params[u][0] * Magnitude(line[1].position - line[0].position)),
				clamp(colours[u].g + trail_colours_params[u][1] * Magnitude(line[1].position - line[0].position)),
				clamp(colours[u].b + trail_colours_params[u][2] * Magnitude(line[1].position - line[0].position)),
				0 + static_cast<sf::Uint8>((k * 255 / trail[g].size())));
			
			line[0].color = fade;
			line[1].color = fade;

			// Draw if both the front and end of the trail are infront of the camera
			if (d1.z >= 0 && d2.z >= 0)
				window.draw(line);

			// Increment counters
			i++;
			if (i == trail[g].size()) // Set i to 0 once it gets to the end of "trail"
				i = 0;

			k++;
		}
	}

	// Text
	text.setString(names[u]);
	text.setScale(0.1f, 0.1f);
	text.setPosition(sf::Vector2f(-85, -45));
	window.draw(text);

	/// UNCOMMENT FOR ON-SCREEN COORDINATES
	/*
	for (unsigned i = 0; i < num_points; i++)
	{
		std::string coordinate_string = "(" + std::to_string(static_cast<int>(point[i].x)) + ", " + std::to_string(static_cast<int>(point[i].y)) + ", " + std::to_string(static_cast<int>(point[i].z)) + ")";
		text.setString(coordinate_string);
		text.setPosition(circle[i].getPosition() + sf::Vector2f(1.0f, -5.0f));
		window.draw(text);
	}
	*/

	// Display then clear the screen
	window.display();
	window.clear(sf::Color::Color(0, 0, 0, 255));
}

void LorenzAttractor::run(sf::RenderWindow &window)
{
	window.setView(view);

	while (window.isOpen() && !endSubProgram)
	{
		this->input(window); // Get Input
		this->update();	     // Update Graphics
		this->draw(window);  // Draw Graphics
	}

	window.setView(sf::View(sf::Vector2f(static_cast<float>(g_screenWidth / 2), static_cast<float>(g_screenHeight / 2)), sf::Vector2f(static_cast<float>(g_screenWidth), static_cast<float>(g_screenHeight))));
}

LorenzAttractor::~LorenzAttractor()
{
}
