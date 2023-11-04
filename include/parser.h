#include <cstring>
#include <iostream>
#include "object.h"
#include <SFML/Graphics.hpp>

#ifndef PARSER_H
#define PARSER_H

void preprocess(Object&);
int load_object(char*, Object&);

#endif //PARSER_H
