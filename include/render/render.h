#include <SFML/Graphics.hpp>
#include "object.h"
#include <cstdint>
#include "settings.h"

#ifndef RENDER_H
#define RENDER_H

extern sf::Image frame;
extern float** z_buffer;
extern uint8_t* buffer;

void __init();
void __update();
float _min(sf::Vector3f);
float _max(sf::Vector3f);
void bounding_box(sf::Vector3f &);
void draw_polygon(Polygon, Object &);
void frame_render(std::vector<Object> &);
void _render(sf::RenderWindow *);

#endif //RENDER_H
