#ifndef OBJETOS
#define OBJETOS

#include "Objeto3d.h"

class Base{
public:

	float radio_base;

	Base();
	void draw(Mode draw_mode, GLfloat color[3]);
};

class Antebrazo{
public:
	float ancho_antebrazo;


	Antebrazo();
	void draw(Mode draw_mode, GLfloat color[3]);

};

class Brazo{
public:

	float ancho_brazo;


	Brazo();
	void draw(Mode draw_mode, GLfloat color[3]);

};

class Munieca{
public:

	float radio_munieca;

	Munieca();
	void draw(Mode draw_mode, GLfloat color[3]);
};

class Dedo{
public:

	float ancho_dedo;

	Dedo();
	void draw(Mode draw_mode, GLfloat color[3]);
};

class Robot : public Objeto3d{
public:

	Dedo miDedo1;
	Dedo miDedo2;
	Munieca miMunieca;
	Brazo miBrazo;
	Antebrazo miAntebrazo;
	Base miBase;


	float altura_base;
	float altura_antebrazo;
	float altura_brazo;
	float angulo_base;
	float angulo_antebrazo;
	float angulo_brazo;
	float altura_munieca;
	float angulo_munieca;
	float altura_dedo;
	float angulo_dedo;

	//limites para los giros

	float limite_giro_antebrazo;
	float limite_giro_brazo;
	float limite_giro_dedos;

	Robot();
	void draw(Mode draw_mode, GLfloat color[3]);
	void movimiento(unsigned char Tecla);
	void girar_base_derecha();
	void girar_base_izquierda();
	void girar_antebrazo_abajo();
	void girar_antebrazo_arriba();
	void girar_brazo_abajo();
	void girar_brazo_arriba();
	void girar_munieca_derecha();
	void girar_munieca_izquierda();
	void abrir_pinza();
	void cerrar_pinza();

};











#endif
