#include "render/render.h"
#include <iostream>
#include <thread>

//Изображения для загрузки текстуры
sf::Image frame;
//z-буффер
float** z_buffer;
//Массив пикселей
uint8_t* buffer;

//sf::Vector2f center(384, 384);
sf::Vector2f center(512, 512);
sf::Vector2f scale(1000, 1000);

sf::Vector3f light_dir(0, 0, 1);

void __init() {
	buffer = new uint8_t[X_SIZE * Y_SIZE * 4];
	z_buffer = new float* [X_SIZE];
	for(int i = 0; i < X_SIZE; i++) {
		z_buffer[i] = new float[Y_SIZE];
		for(int j = 0; j < Y_SIZE; j++) {
			z_buffer[i][j] = std::numeric_limits<float>::max();
		}
	}
	for(int k = 0; k < X_SIZE * Y_SIZE * 4; k++) {
		buffer[k++] = 0;
		buffer[k++] = 0;
		buffer[k++] = 0;
		buffer[k] = 255;
	}
}

void __update() {
	for(int i = 0; i < X_SIZE; i++) {
		for(int j = 0; j < Y_SIZE; j++) {
			buffer[(j*X_SIZE+i)*4 + 0] = 0;
			buffer[(j*X_SIZE+i)*4 + 1] = 0;
			buffer[(j*X_SIZE+i)*4 + 2] = 0;
			buffer[(j*X_SIZE+i)*4 + 3] = 255;
			z_buffer[i][j] = std::numeric_limits<float>::max();
		}
	}

}

void bounding_box(sf::Vector3f &v) {
	if(v.x < 0) v.x = 0; 
	else if(v.x > X_SIZE - 1) v.x = X_SIZE - 1; 
	if(v.y < 0) v.y = 0; 
	else if(v.y > X_SIZE - 1) v.y = X_SIZE - 1; 
}

void draw_polygon(Polygon polygon, Object& object) {
	Polygon p_polygon = polygon.projection_on_camera_pol(object.origin, scale, center);
	sf::Vector3f nw(std::min({p_polygon.a->x, p_polygon.b->x, p_polygon.c->x}), 
		std::min({p_polygon.a->y, p_polygon.b->y, p_polygon.c->y}), 0); 
	sf::Vector3f se(std::max({p_polygon.a->x, p_polygon.b->x, p_polygon.c->x}), 
		std::max({p_polygon.a->y, p_polygon.b->y, p_polygon.c->y}), 0); 

	bounding_box(nw);
	bounding_box(se);

	sf::Vector3f color(0, 0, 0);
	float colorf = 200 * scalar(light_dir, polygon.normal);
	if(colorf > 0) 
		color = color + 255 * scalar(light_dir, polygon.normal);

	for(int x = nw.x; x < se.x; x++) {
		for(int y = nw.y; y < se.y; y++) {
			sf::Vector3f lambda = to_barycentric(sf::Vector3f(x, y, 0), p_polygon);	
			if(lambda.x > 0 && lambda.y > 0 && lambda.z > 0) {
				float shift = object.origin.z;
				float z = lambda.x * (polygon.a->z+shift) + lambda.y * (polygon.b->z+shift) + lambda.z * (polygon.c->z+shift); 
				if(z < z_buffer[x][y]) {
					z_buffer[x][y] = z;

					buffer[(y*X_SIZE+x)*4 + 0] = color.x;
					buffer[(y*X_SIZE+x)*4 + 1] = color.y;
					buffer[(y*X_SIZE+x)*4 + 2] = color.z;
					buffer[(y*X_SIZE+x)*4 + 3] = 255;
				}
			}
		}
	}
}

void render_thread(int start, Object object) {	
	for(size_t i = start; i < object.mesh.polygons.size(); i += 2) {
		if(scalar(sf::Vector3f(0, 0, 1), object.mesh.polygons[i].normal)) {
			draw_polygon(object.mesh.polygons[i], object);
		}
	}
}

void frame_render(std::vector<Object> &_objects) {
	for(size_t i = 0; i < _objects.size(); i++) {
		std::thread t1(render_thread, 0, _objects[i]);
		std::thread t2(render_thread, 1, _objects[i]);
		t1.join();
		t2.join();
	}
}

void _render(sf::RenderWindow *window) {
	__init();
	std::cout << "Init complete\n";
	sf::Time elapsed_time;
	sf::Clock clock_frame;
	sf::Clock clock_fps;
	while(window->isOpen()) {
		sf::Time delta_time = clock_frame.restart();
		elapsed_time += delta_time;
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
			objects[0].move(sf::Vector3f(-0.3, 0, 0));
		}
		else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
			objects[0].move(sf::Vector3f(0.3, 0, 0));
		}
		else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
			objects[0].move(sf::Vector3f(0, 0.3, 0));
		}
		else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
			objects[0].move(sf::Vector3f(0, -0.3, 0));
		}
		else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) {
			objects[0].move(sf::Vector3f(0, 0, 0.3));
		}
		else if(sf::Keyboard::isKeyPressed(sf::Keyboard::E)) {
			objects[0].move(sf::Vector3f(0, 0, -0.3));
		}
		if(elapsed_time > sf::milliseconds(100)) {
			float fps = 1.f / clock_fps.restart().asSeconds();
			std::cout << "FPS: " << (int)fps << '\n';
			
			__update();
			frame_render(objects);
			frame.create(X_SIZE, Y_SIZE, buffer);
			frame.flipVertically();
			sf::Texture text;
			text.loadFromImage(frame);
				
		
			sf::Sprite sp(text);
			sp.setPosition(0, 0);

			window->draw(sp);
		}
		window->display();
	}
}
