#include "geometry/vector.h"
#include "geometry/polygon.h"
#include "geometry/mesh.h"
#include <atomic>

#ifndef OBJECT_H
#define OBJECT_H

struct Object {
	Mesh mesh;
	sf::Vector3f origin;

	Object();
	Object(sf::Vector3f);
	void move(sf::Vector3f);
};

#endif //OBJECT_H
