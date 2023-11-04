#include "object.h"

Object::Object() {
	
}

Object::Object(sf::Vector3f o) {
	origin = o;
}

void Object::move(sf::Vector3f o) {
	origin = origin + o;
}


