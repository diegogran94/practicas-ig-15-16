#ifndef OBJETO3D
#define OBJETO3D

#include <math.h> //Para usar la costante PI

//Modos para pintar los objetos
enum Mode {
	PUNTOS, ALAMBRE, SOLIDO, AJEDREZ, TODO//Modificación: Pintar aristas+vertices+caras
};

class Objeto3dSimple{
protected:
	vector<_vertex3f> vertices;
public:
	void init_vertices(vector<_vertex3f> v);
	void draw_vertices(GLfloat color[3]);
};

class Objeto3d : public Objeto3dSimple{
protected:
	vector<_vertex3i> caras;
private:
	_vertex3f rotacionY(_vertex3f punto, double alfa);
	float grados_a_radianes(float angulo);
public:
	void init_caras(vector<_vertex3i> c);
	void draw(Mode draw_mode,GLfloat color[3]);
	void load_ply(char* filename);
	void revolucion(int veces, float angulo_i, bool tiene_tapas=true);
};


#endif