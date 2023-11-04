#include "geometry/polygon.h"
#include "geometry/vector.h"

Polygon::Polygon() { }

sf::Vector3f Polygon::calculate_normal() {
	normal.x = (b->y - a->y) * (b->z - c->z) - (b->y - c->y) * (b->z - a->z);
	normal.y = (b->x - a->x) * (b->z - c->z) - (b->x - c->x) * (b->z - a->z);
	normal.z = (b->x - a->x) * (b->y - c->y) - (b->x - c->x) * (b->y - a->y);
	return normal;
}

Polygon Polygon::projection_on_camera_pol(sf::Vector3f origin, sf::Vector2f center, sf::Vector2f scale) {
	Polygon polygon;
	polygon.a = projection_on_camera(*a, origin, center, scale);	
	polygon.b = projection_on_camera(*b, origin, center, scale);	
	polygon.c = projection_on_camera(*c, origin, center, scale);	
	return polygon;
}
