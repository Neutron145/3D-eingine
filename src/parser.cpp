#include "parser.h"

//В будущем добавить вычисление нормалей к точке
void preprocess(Object &obj) { 
	//Вычисляем нормали полигонов и вершин
	for(size_t i = 0; i < obj.mesh.polygons.size(); i++) {
		obj.mesh.polygons[i].calculate_normal();
	}
}

//Считывание объекта из файла
int load_object(char* path, Object &obj) {
	FILE* fobj = fopen(path, "r");
	if(fobj == NULL) return -1;

	//Пропускаем все строки, пока не дойдем до вершин 
	char* data_type = new char;
	do { fscanf(fobj, "%s", data_type); } while(strcmp(data_type, "v") != 0);
	
	//Считываем вершины
	int points_count = 0;
	do {
		sf::Vector3f p(0, 0, 0);
		fscanf(fobj, "%e%e%e", &p.x, &p.y, &p.z);
		fgetc(fobj);
		obj.mesh.points.push_back(p);
		points_count++;
	} while(fscanf(fobj, "%s", data_type) && strcmp(data_type, "v") == 0);
	
	//Пропускаем vn
	if(strcmp(data_type, "vn") == 0) {
		char line[128];
		fgets(line, sizeof(line), fobj);
		do {
			fgets(line, sizeof(line), fobj);
			line[2] = 0;
		} while(fscanf(fobj,"%s", data_type)&& strcmp(data_type, "vn") == 0);
	}
	
	//Пропускаем vt
	if(strcmp(data_type, "vt") == 0) {
		char line[128];
		fgets(line, sizeof(line), fobj);
		do {
			fgets(line, sizeof(line), fobj);
			line[2] = 0;
		} while(strcmp(line, "vt") == 0);
		fscanf(fobj, "%s", data_type);
	}
	
	//Считываем f
	do {
		Polygon polygon;
		int a, b, c;
		fscanf(fobj, "%d", &a);
		fscanf(fobj, "%s", data_type);
		polygon.a = &obj.mesh.points[a-1];

		fscanf(fobj, "%d", &b);
		fscanf(fobj, "%s", data_type);
		polygon.b = &obj.mesh.points[b-1];

		fscanf(fobj, "%d", &c);
		fscanf(fobj, "%s", data_type);
		polygon.c = &obj.mesh.points[c-1];
		obj.mesh.polygons.push_back(polygon);
	} while(fscanf(fobj, "%s", data_type) && strcmp(data_type, "f") == 0);

	fclose(fobj);
	preprocess(obj);
	return 0;
}



