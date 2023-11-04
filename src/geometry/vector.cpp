#include "geometry/vector.h"

float operator*(const sf::Vector3f &lhs, const sf::Vector3f &rhs) {
	return lhs.x * rhs.x + lhs.y * rhs.y + lhs.z * rhs.z;
}

sf::Vector3f operator-(sf::Vector3f lhs, const sf::Vector3f &rhs) {
	lhs.x -= rhs.x;
	lhs.y -= rhs.y;
	lhs.z -= rhs.z;
	return lhs;
}

sf::Vector3f operator+(sf::Vector3f lhs, const sf::Vector3f &rhs) {
	lhs.x += rhs.x;
	lhs.y += rhs.y;
	lhs.z += rhs.z;
	return lhs;
}

sf::Vector3f operator*(const sf::Vector3f &lhs, const float rhs) {
	return sf::Vector3f (lhs.x * rhs, lhs.y * rhs, lhs.z * rhs);
}

sf::Vector3f operator-(const sf::Vector3f &lhs) {
	float t = -1;
	return lhs * t;
}

sf::Vector3f operator-(sf::Vector3f lhs, const float &rhs) {
	lhs.x -= rhs;
	lhs.y -= rhs;
	lhs.z -= rhs;
	return lhs;
}

sf::Vector3f operator+(sf::Vector3f lhs, const float &rhs) {
	lhs.x += rhs;
	lhs.y += rhs;
	lhs.z += rhs;
	return lhs;	
}

std::ostream& operator<<(std::ostream& out, const sf::Vector3f &v) {
	out << v.x << ' ' << v.y << ' ' << v.z << '\n';
	return out;
}

//Норма вектора
float norm(const sf::Vector3f &v) { return sqrt(v.x*v.x + v.y*v.y + v.z*v.z); };

//Нормализация вектора
sf::Vector3f normalize(sf::Vector3f &v) { return sf::Vector3f(v.x, v.y, v.z) * (1/norm(v)); }

//Скалярное произведение
float scalar(const sf::Vector3f &v1, const sf::Vector3f &v2) { return (v1 * v2) / (norm(v1) * norm(v2)); }

sf::Vector3f* projection_on_camera(sf::Vector3f v, sf::Vector3f origin, sf::Vector2f center, sf::Vector2f scale) {
	sf::Vector3f* p = new sf::Vector3f(0, 0, 1);
	p->x = center.x * (v.x + origin.x) / (v.z + origin.z) + scale.x;
	p->y = center.y * (v.y + origin.y) / (v.z + origin.z) + scale.y;
	return p;
}

sf::Vector3f to_barycentric(sf::Vector3f point, Polygon polygon) {
	sf::Vector3f lambda;
	point.x = (int)point.x;
	point.y = (int)point.y;
	lambda.x = ((polygon.b->x - polygon.c->x) * (point.y - polygon.c->y) -	(polygon.b->y - polygon.c->y) * (point.x - polygon.c->x)) /
		((polygon.b->x - polygon.c->x) * (polygon.a->y - polygon.c->y) - (polygon.b->y - polygon.c->y) * (polygon.a->x - polygon.c->x));

	lambda.y = ((polygon.c->x - polygon.a->x) * (point.y - polygon.a->y) -	(polygon.c->y - polygon.a->y) * (point.x - polygon.a->x)) /
		((polygon.c->x - polygon.a->x) * (polygon.b->y - polygon.a->y) - (polygon.c->y - polygon.a->y) * (polygon.b->x - polygon.a->x));
	
	lambda.z = ((polygon.a->x - polygon.b->x) * (point.y - polygon.b->y) -	(polygon.a->y - polygon.b->y) * (point.x - polygon.b->x)) /
		((polygon.a->x - polygon.b->x) * (polygon.c->y - polygon.b->y) - (polygon.a->y - polygon.b->y) * (polygon.c->x - polygon.b->x));
	return lambda;
}
