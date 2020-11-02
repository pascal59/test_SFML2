#include <cstdlib>
#include <iostream>
#include <array>

#include <SFML/Graphics.hpp>


using namespace std;
using namespace sf;

class my_Rectangle /*: public sf::RectangleShape*/ {
public:
	//	my_Rectangle() : sf::RectangleShape(sf::Vector2f(1, 10)) {}
};

int main() {
	// Fenêtre

	std::array<sf::RectangleShape, 5> rectangles;

	float position_y = 10;
	for (auto& irec : rectangles) {
		irec.setSize(sf::Vector2f(1, 10));
		irec.setPosition(sf::Vector2f(10, position_y));
		position_y += 20;
	}

	int which_bar = 0;

	rectangles[which_bar].setOutlineThickness(1);
	rectangles[which_bar].setOutlineColor(sf::Color(250, 150, 100));

	const Vector2u WINDOW_SIZE(800, static_cast<unsigned>(position_y));

	const float window_width = static_cast<float>(WINDOW_SIZE.x - 20);

	RenderWindow app(VideoMode(WINDOW_SIZE.x, WINDOW_SIZE.y, 32), "My Camera");

	// Frames Per Second (FPS)
	app.setFramerateLimit(60); // limite la fenêtre à 60 images par seconde
	app.setKeyRepeatEnabled(false);

	while (app.isOpen()) // Boucle principale
	{
		Event event;
		while (app.pollEvent(event)) // Boucle des évènements de la partie pause
		{
			switch (event.type)
			{
				if ((event.type == Event::KeyPressed && event.key.code == sf::Keyboard::Escape) || event.type == Event::Closed)
				{
					app.close();
				}
				if (event.type == Event::KeyPressed) {
					switch (event.key.code) {
					case sf::Keyboard::Left: {
						auto size_rectangle = rectangles[which_bar].getSize();
						if (1 < size_rectangle.x) {
							rectangles[which_bar].setSize(sf::Vector2f(size_rectangle.x - 1, size_rectangle.y));
						}
						break;
					}

					case sf::Keyboard::Right: {
						auto size_rectangle = rectangles[which_bar].getSize();
						if (size_rectangle.x < window_width) {
							rectangles[which_bar].setSize(sf::Vector2f(size_rectangle.x + 1, size_rectangle.y));
						}
						break;
					}

					case sf::Keyboard::Up:
						rectangles[which_bar].setOutlineThickness(0);
						if (which_bar == 0) {
							which_bar = rectangles.size() - 1;
						}
						else {
							--which_bar;
						}
						rectangles[which_bar].setOutlineThickness(1);
						rectangles[which_bar].setOutlineColor(sf::Color(250, 150, 100));
						break;

					case sf::Keyboard::Down:
						rectangles[which_bar].setOutlineThickness(0);
						if (which_bar == rectangles.size() - 1) {
							which_bar = 0;
						}
						else {
							++which_bar;
						}
						rectangles[which_bar].setOutlineThickness(1);
						rectangles[which_bar].setOutlineColor(sf::Color(250, 150, 100));
						break;
					}
				}
			}
		}
		// Affichages
		app.clear();
		for (auto& irec : rectangles) {
			app.draw(irec);
		}
		app.display();
	}
		return EXIT_SUCCESS;
	}
