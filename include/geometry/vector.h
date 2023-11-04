#include <cmath>
#include <SFML/Graphics.hpp>
#include <geometry/polygon.h>

#ifndef VECTOR_H
#define VECTOR_H
float operator*(const sf::Vector3f &lhs, const sf::Vector3f &rhs);

sf::Vector3f operator-(sf::Vector3f lhs, const sf::Vector3f &rhs); 

sf::Vector3f operator+(sf::Vector3f lhs, const sf::Vector3f &rhs); 

sf::Vector3f operator*(const sf::Vector3f &lhs, const float rhs); 

sf::Vector3f operator-(const sf::Vector3f &lhs);

sf::Vector3f operator-(sf::Vector3f lhs, const float& rhs);

sf::Vector3f operator+(sf::Vector3f lhs, const float& rhs);

std::ostream& operator<<(std::ostream& out, const sf::Vector3f &v); 

//Норма вектора
float norm(const sf::Vector3f &v); 

//Нормализация вектора
sf::Vector3f normalize(sf::Vector3f &v); 

//Скалярное произведение
float scalar(const sf::Vector3f &v1, const sf::Vector3f &v2); 

sf::Vector3f* projection_on_camera(sf::Vector3f, sf::Vector3f, sf::Vector2f, sf::Vector2f); 
sf::Vector3f to_barycentric(sf::Vector3f, Polygon);

#endif //VECTOR_H
