#include "stdlib.h"
#include "stdio.h"
#include <GL/glut.h>
#include <ctype.h>

#include <vector>
#include "vertex.h"

#include "objetos.h"
#include "figuras.h"

//--------------------------------------------------------------
// Metodos de la clase robot
//--------------------------------------------------------------

Robot::Robot(){
	//objetos

	altura_base = 1.5;
	altura_antebrazo = 1.5;
	altura_brazo = 1;
	angulo_base = 0.0;
	angulo_antebrazo = 0.0;
	altura_munieca = 0.3;
	angulo_munieca = 0.0;
	angulo_dedo=0.0;
	altura_dedo=0.5;
	angulo_dedo=0.0;

	//limites para los giros

	limite_giro_antebrazo=45;
	limite_giro_brazo=105;
	limite_giro_dedos=10;

	Dedo miDedo1();
	Dedo miDedo2();
	Munieca miMunieca();
	Brazo miBrazo();
	Antebrazo miAntebrazo();
	Base miBase();


}

void Robot::draw(Mode draw_mode, GLfloat color[3]){

	glPushMatrix();

	glMatrixMode(GL_MODELVIEW);

	glRotatef(angulo_base,0,1.0,0);
	glPushMatrix();

		glTranslatef(0.0,altura_base/2,0.0);
	miBase.draw(draw_mode,color);
	glPopMatrix();
		glPushMatrix();

		glTranslatef(0.0,altura_base,0.0);

		glRotatef(angulo_antebrazo,1.0,0.0,0.0);

		glTranslatef(0.0,-(altura_base),0.0);
		glPushMatrix();

			glTranslatef(0.0,altura_base+(altura_antebrazo/2),0.0);
		miAntebrazo.draw(draw_mode,color);
		glPopMatrix();
			glPushMatrix();

			glTranslatef(0.0,altura_base+altura_antebrazo,0.0);

			glRotatef(angulo_brazo,1.0,0.0,0.0);

			glTranslatef(0.0,-(altura_base+altura_antebrazo),0.0);

			glPushMatrix();

			glTranslatef(0.0,altura_base+altura_antebrazo+(altura_brazo/2),0.0);
			miBrazo.draw(draw_mode,color);
			glPopMatrix();

				glPushMatrix();


				glRotatef(angulo_munieca,0.0,1.0,0.0);

				glPushMatrix();
				glTranslatef(0.0,altura_base+altura_antebrazo+altura_brazo,0.0);

				miMunieca.draw(draw_mode,color);
				glPopMatrix();
					glPushMatrix();




					glPushMatrix();

					glTranslatef(0.0,(altura_base+altura_antebrazo+altura_brazo+altura_munieca-altura_dedo/2),0.0);

					glRotatef(angulo_dedo,0.0,0.0,1.0);

					glTranslatef(0.0,-(altura_base+altura_antebrazo+altura_brazo+altura_munieca-altura_dedo/2),0.0);

					//
					glTranslatef(0.0,(altura_base+altura_antebrazo+altura_brazo+altura_munieca-altura_dedo/2),0.0);

					glRotatef(-40,0.0,0.0,1.0);

					glTranslatef(0.0,-(altura_base+altura_antebrazo+altura_brazo+altura_munieca-altura_dedo/2),0.0);
					//
					miDedo1.draw(draw_mode,color);

					glPopMatrix();

							glPushMatrix();

							glTranslatef(0.0,(altura_base+altura_antebrazo+altura_brazo+altura_munieca-altura_dedo/2),0.0);

							glRotatef(-angulo_dedo,0.0,0.0,1.0);

							glTranslatef(0.0,-(altura_base+altura_antebrazo+altura_brazo+altura_munieca-altura_dedo/2),0.0);

							glRotatef(180,0.0,1.0,0.0);
							//
							glTranslatef(0.0,(altura_base+altura_antebrazo+altura_brazo+altura_munieca-altura_dedo/2),0.0);

							glRotatef(-40,0.0,0.0,1.0);

							glTranslatef(0.0,-(altura_base+altura_antebrazo+altura_brazo+altura_munieca-altura_dedo/2),0.0);
							//
							miDedo2.draw(draw_mode,color);

							glPopMatrix();

					glPopMatrix();

				glPopMatrix();

			glPopMatrix();

		glPopMatrix();

	glPopMatrix();
}

void Robot::movimiento(unsigned char Tecla){

	switch(Tecla){

		case 'P':
			girar_base_derecha();
			break;
		case 'p':
			girar_base_izquierda();
			break;

		case 'O':
			girar_antebrazo_abajo();
			break;
		case 'o':
			girar_antebrazo_arriba();
			break;

		case 'I':
			girar_brazo_abajo();
			break;
		case 'i':
			girar_brazo_arriba();
			break;

		case 'U':
			girar_munieca_derecha();
			break;
		case 'u':
			girar_munieca_izquierda();
			break;

		case 'Y':
			cerrar_pinza();
			break;
		case 'y':
			abrir_pinza();
			break;
	}


}

void Robot::girar_base_derecha(){
	angulo_base++;
}

void Robot::girar_base_izquierda(){
	angulo_base--;
}

void Robot::girar_antebrazo_abajo(){
	if(angulo_antebrazo <= limite_giro_antebrazo)
		angulo_antebrazo++;
}

void Robot::girar_antebrazo_arriba(){
	if(angulo_antebrazo >= -limite_giro_antebrazo)
		angulo_antebrazo--;
}

void Robot::girar_brazo_abajo(){
	if(angulo_brazo <= limite_giro_brazo)
		angulo_brazo++;
}

void Robot::girar_brazo_arriba(){
	if(angulo_brazo >= -limite_giro_brazo)
		angulo_brazo--;
}

void Robot::girar_munieca_derecha(){
	angulo_munieca++;
}

void Robot::girar_munieca_izquierda(){
	angulo_munieca--;
}

void Robot::abrir_pinza(){
	if(angulo_dedo >= -(limite_giro_dedos+10))
		angulo_dedo--;
}

void Robot::cerrar_pinza(){
	if(angulo_dedo <= limite_giro_dedos)
		angulo_dedo++;
}

//--------------------------------------------------------------
// Metodos de la clase base
//--------------------------------------------------------------

Base::Base(){

	radio_base = 0.7;
}

void Base::draw(Mode draw_mode, GLfloat color[3]){

	Cilindro cilindro(1,1,30);

	glMatrixMode(GL_MODELVIEW);

	glPushMatrix();



	glScalef(radio_base,1.5,radio_base);

	cilindro.draw(draw_mode,color);

	glPopMatrix();

}

//--------------------------------------------------------------
// Metodos de la clase antebrazo
//--------------------------------------------------------------

Antebrazo::Antebrazo(){
	ancho_antebrazo = 0.3;

}

void Antebrazo::draw(Mode draw_mode, GLfloat color[3]){

	Cubo cubo(1);

	glMatrixMode(GL_MODELVIEW);

	glPushMatrix();



	glScalef(ancho_antebrazo,1.5,ancho_antebrazo);

	cubo.draw(draw_mode,color);

	glPopMatrix();

}


//--------------------------------------------------------------
// Metodos de la clase brazo
//--------------------------------------------------------------

Brazo::Brazo(){
	ancho_brazo = 0.3;
}

void Brazo::draw(Mode draw_mode, GLfloat color[3]){

	Cubo cubo(1);

	glMatrixMode(GL_MODELVIEW);

	glPushMatrix();



	glScalef(ancho_brazo,1,ancho_brazo);

	cubo.draw(draw_mode,color);

	glPopMatrix();
}

//--------------------------------------------------------------
// Metodos de la clase munieca
//--------------------------------------------------------------

Munieca::Munieca(){
	radio_munieca = 0.2;
}

void Munieca::draw(Mode draw_mode, GLfloat color[3]){

	Cilindro cilindro(1,1,30);

	glMatrixMode(GL_MODELVIEW);

	glPushMatrix();



	glScalef(radio_munieca,0.3,radio_munieca);

	cilindro.draw(draw_mode,color);

	glPopMatrix();
}

//--------------------------------------------------------------
// Metodos de la clase Dedo
//--------------------------------------------------------------

Dedo::Dedo(){
	ancho_dedo = 0.08;
}

void Dedo::draw(Mode draw_mode, GLfloat color[3]){

	Cubo cubo_base(1);

	glMatrixMode(GL_MODELVIEW);

	glPushMatrix();



			glPushMatrix();

			glTranslatef(0.0,1.5+1.5+1+0.3,0.0);

			glScalef(ancho_dedo,0.5,ancho_dedo);

			cubo_base.draw(draw_mode,color);

			glPopMatrix();

			glPushMatrix();

			glTranslatef(0.0,1.5+1.5+1+0.3+0.5,0.0);

			glTranslatef(0.0, -(0.5/2),0.0);

			glRotatef(55,0.0,0.0,1.0);

			glTranslatef(0.0, 0.5/2,0.0);

			glScalef(ancho_dedo,0.5,ancho_dedo);

			cubo_base.draw(draw_mode,color);

			glPopMatrix();

	glPopMatrix();
}
