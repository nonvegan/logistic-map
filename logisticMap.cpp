#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <math.h>
#include <vector>

using namespace sf;


int main()
{
	const int WIDTH = 1200;
	const int HEIGHT = 800;
	sf::Time ellapsedTime;
	sf::Clock clock;
	RenderWindow window(VideoMode(WIDTH, HEIGHT), "Logistic Map");
	std::vector<Vector2f> points;

	int N = 3000;
	float percent = 0.1f;
	float R0 = 1;
	float R = 4;
	float x0 = 0.5;


	for (float r = R0, inc = R / WIDTH, x = x0; r < R; r += inc)
	{
		int n = 0;
		while (n < N * (1.f - percent)) {
			x = r * x * (1.f - x);
			n++;
		}
		while (n < N) {
			float newx = r * x * (1 - x);
			points.push_back(Vector2f(r / R * WIDTH, HEIGHT - newx * HEIGHT));
			if (newx == x) {
				break;
			}
			x = newx;
			n++;
		}
	}

	sf::VertexArray DrawnPoints(sf::Points, points.size());
	for (size_t i = 0; i < points.size() - 1; i++) {
		DrawnPoints[i] = points[i];
	}
	printf("Plotting the logistic map. x[n+1]= rx[n](1-x[n]) ---> https://en.wikipedia.org/wiki/Logistic_map \n\n");
	printf("N: %i\n", N);
	printf("r: [%f-%f]\n", R0, R);
	printf("x0: %f\n", x0);
	printf("Ignoring %f of point residue\n", (1.f - percent) * 100.f);
	printf("Plotting %i points\n", points.size());

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}
		window.draw(DrawnPoints);
		window.display();
		ellapsedTime = clock.restart();
		std::cout << "Fps: " << std::to_string(1 / ellapsedTime.asSeconds()) << '\r';
	}

}