#include <SFML/Graphics.hpp>

#ifndef POLYGON_H
#define POLYGON_H

struct Polygon {
	sf::Vector3f* a;
	sf::Vector3f* b;
	sf::Vector3f* c;
	sf::Vector3f normal;
	Polygon();	
	sf::Vector3f calculate_normal();
	Polygon projection_on_camera_pol(sf::Vector3f, sf::Vector2f, sf::Vector2f);
};

#endif //POLYGON_H
