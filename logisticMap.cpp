#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <math.h>
#include <vector>

using namespace sf;

const int WIDTH = 1280;
const int HEIGHT = 720;
int N = 1000;
float transient = 0.9f;
float R0 = 2.4f;
float R = 4.f;
float x0 = 0.5f;
Color backgroundColor = Color(40, 44, 52);
Color foreGroundColor = Color(202, 44, 146);

int main()
{
	Time ellapsedTime;
	Clock clock;
	std::vector<Vector2f> points;
	for (float r = R0, inc = R / WIDTH, x = x0; r < R; r += inc)
	{
		int n = 0;
		while (n < N * transient) 
		{
			x = r * x * (1.f - x);
			n++;
		}
		while (n < N) 
		{
			float newx = r * x * (1 - x);
			points.push_back(Vector2f((r - R0) / (R - R0) * WIDTH, HEIGHT - newx * HEIGHT));
			if (std::abs(x - newx) < 0.001)
				break;
			x = newx;
			n++;
		}
	}

	printf("Plotting the logistic map. x[n+1]= rx[n](1-x[n]) ---> https://en.wikipedia.org/wiki/Logistic_map \n\n");
	printf("N: %i\n", N);
	printf("r: [%f,%f]\n", R0, R);
	printf("x0: %f\n", x0);
	printf("Ignoring %f %% of transient points\n", (double)transient * 100.f);
	printf("Plotting %i points\n", (int)points.size());

	RenderWindow window(VideoMode(WIDTH, HEIGHT), "Logistic Map");
	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
		}
		window.clear(backgroundColor);
		if (c < points.size()) 
		{
			DrawnPoints[c] = points[c];
			DrawnPoints[c].color = foreGroundColor;
			c++;
		}
		window.draw(DrawnPoints);
		window.display();
		std::cout << "Fps: " << std::to_string(1 / clock.restart().asSeconds()) << '\r';
	}
}
