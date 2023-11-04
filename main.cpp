#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>
#include <vector>
#include "parser.h"
#include "object.h"
#include "render/render.h"

#include "settings.h"

const int X_SIZE = 1024;
const int Y_SIZE = 1024;

using namespace std;

std::vector<Object> objects;

void init() {
	objects.push_back(Object(sf::Vector3f(0, 0, 10)));
	load_object("obj/sphere.obj", objects[0]);	

	objects.push_back(Object(sf::Vector3f(0, 0, 10)));
	load_object("obj/cube.obj", objects[1]);
}

int main() {
	init();
	sf::RenderWindow window(sf::VideoMode(X_SIZE, Y_SIZE), "Demo");
	
	window.setActive(false);

	sf::Thread render(&_render, &window);
	render.launch();

	while(window.isOpen()) {
		sf::Event event;
		while(window.pollEvent(event)) {
			if(event.type == sf::Event::Closed) 
				window.close();
		}
	}

	return 0;
}
