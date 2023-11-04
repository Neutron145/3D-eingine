#include "geometry/vector.h"
#include "geometry/polygon.h"

#ifndef MESH_H
#define MESH_H

//Меш хранит все данные о точках и полигонах объекта для отрисовки
struct Mesh {
	std::vector<sf::Vector3f> points;
	std::vector<Polygon> polygons;
	Mesh();
};

#endif //MESH_H
