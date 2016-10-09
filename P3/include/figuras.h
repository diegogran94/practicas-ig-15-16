#ifndef FIGURAS
#define FIGURAS

#include "Objeto3d.h"

class Cilindro : public Objeto3d{

public:
	Cilindro(float radio,float altura, int revoluciones);
};

class Cubo : public Objeto3d{

public:
	Cubo(float tam);
};

class Cono : public Objeto3d{

public:
	Cono(float radio, float altura, int revoluciones);
};


#endif