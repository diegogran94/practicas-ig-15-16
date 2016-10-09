#include "stdlib.h"
#include "stdio.h"
#include <GL/glut.h>
#include <ctype.h>

#include <vector>
#include "vertex.h"

#include "Objeto3d.h"
#include "figuras.h"
#include "file_ply_stl.h"

Cilindro::Cilindro(float radio, float altura, int revoluciones){
	vertices.push_back(_vertex3f(0.0, -altura/2, 0));
	vertices.push_back(_vertex3f(radio, -altura/2, 0));
	vertices.push_back(_vertex3f(radio, altura/2, 0));
	vertices.push_back(_vertex3f(0.0, altura/2, 0));
	revolucion(revoluciones, 360, true);
}

Cubo::Cubo(float tam){
	vertices.push_back(_vertex3f(tam/2, -tam/2, -tam/2));
	vertices.push_back(_vertex3f(tam/2, tam/2, -tam/2));
	vertices.push_back(_vertex3f(tam/2, tam/2, tam/2));
	vertices.push_back(_vertex3f(tam/2, -tam/2, tam/2));

	vertices.push_back(_vertex3f(-tam/2, -tam/2, -tam/2));
	vertices.push_back(_vertex3f(-tam/2, tam/2, -tam/2));
	vertices.push_back(_vertex3f(-tam/2, tam/2, tam/2));
	vertices.push_back(_vertex3f(-tam/2, -tam/2, tam/2));

	caras.push_back(_vertex3i(0,1,2));
	caras.push_back(_vertex3i(0,3,2));
	caras.push_back(_vertex3i(3,2,6));
	caras.push_back(_vertex3i(3,7,6));
	caras.push_back(_vertex3i(7,6,5));
	caras.push_back(_vertex3i(7,4,5));
	caras.push_back(_vertex3i(4,5,1));
	caras.push_back(_vertex3i(4,0,1));
	caras.push_back(_vertex3i(1,5,6));
	caras.push_back(_vertex3i(1,2,6));
	caras.push_back(_vertex3i(4,0,3));
	caras.push_back(_vertex3i(4,7,3));
}

Cono::Cono(float radio, float altura, int revoluciones){
	vertices.push_back(_vertex3f(0.0, -altura/2, 0));
	vertices.push_back(_vertex3f(radio, -altura/2, 0));
	vertices.push_back(_vertex3f(0.0, altura/2, 0));
	revolucion(revoluciones, 360, false);
}