#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <math.h>
#include <vector>

using namespace sf;

int main()
{
	const int WIDTH = 1280;
	const int HEIGHT = 720;
	sf::Time ellapsedTime;
	sf::Clock clock;
	std::vector<Vector2f> points;

	int N = 1000;
	float residue = 0.9f;
	float R0 = 2.4f;
	float R = 4.f;
	float x0 = 0.5f;
	Color backgroundColor = Color(40, 44, 52);
	Color foreGroundColor = Color(202, 44, 146);

	for (float r = R0, inc = R / WIDTH, x = x0; r < R; r += inc)
	{
		int n = 0;
		while (n < N * residue) {
			x = r * x * (1.f - x);
			n++;
		}
		while (n < N) {
			float newx = r * x * (1 - x);
			points.push_back(Vector2f((r - R0) / (R - R0) * WIDTH, HEIGHT - newx * HEIGHT));
			if (std::abs(x - newx) < 0.001) {
				break;
			}
			x = newx;
			n++;
		}
	}

	sf::VertexArray DrawnPoints(sf::Points, points.size());
	int c = 0;

	printf("Plotting the logistic map. x[n+1]= rx[n](1-x[n]) ---> https://en.wikipedia.org/wiki/Logistic_map \n\n");
	printf("N: %i\n", N);
	printf("r: [%f,%f]\n", R0, R);
	printf("x0: %f\n", x0);
	printf("Ignoring %f %% of point residue\n", (double)residue * 100.f);
	printf("Plotting %i points\n", points.size());

	RenderWindow window(VideoMode(WIDTH, HEIGHT), "Logistic Map");
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}
		window.clear(backgroundColor);
		if (c < points.size()) {
			DrawnPoints[c] = points[c];
			DrawnPoints[c].color = foreGroundColor;
			c++;
		}
		window.draw(DrawnPoints);
		window.display();
		std::cout << "Fps: " << std::to_string(1 / clock.restart().asSeconds()) << '\r';
	}
}
