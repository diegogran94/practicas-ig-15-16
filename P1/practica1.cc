//**************************************************************************
// Práctica 1
//
// Domingo Martin Perandres 2013-2016
//
// GPL
//**************************************************************************

#include "stdlib.h"
#include "stdio.h"
#include <GL/glut.h>
#include <ctype.h>

#include <vector>
#include "vertex.h"

// tamaño de los ejes
const int AXIS_SIZE=5000;

// variables que definen la posicion de la camara en coordenadas polares
GLfloat Observer_distance;
GLfloat Observer_angle_x;
GLfloat Observer_angle_y;

// variables que controlan la ventana y la transformacion de perspectiva
GLfloat Window_width,Window_height,Front_plane,Back_plane;

// variables que determninan la posicion y tamaño de la ventana X
int UI_window_pos_x=50,UI_window_pos_y=50,UI_window_width=500,UI_window_height=500;

GLfloat color_principal[3] = {0,1,0};//Verde
GLfloat color_chess_0[3] = {1,1,0};
GLfloat color_chess_1[3] = {0,1,1};

enum Mode {
	PUNTOS, ALAMBRE, SOLIDO, AJEDREZ, TODO//Modificación: Pintar aristas+vertices+caras
};

//Modo en el que se pintaran los objetos
Mode modo_actual = PUNTOS;

//-------------------------------------------------------------------------------
//Cabeceras de las clases (TODO: Separar en archivos diferentes)

class Objeto3dSimple{
protected:
	vector<_vertex3f> vertices;
public:
	void init_vertices(vector<_vertex3f> v);
	void draw_vertices();
};

class Objeto3d : public Objeto3dSimple{
protected:
	vector<_vertex3i> caras;
public:
	void init_caras(vector<_vertex3i> c);
	void draw(GLenum draw_mode,GLfloat color[3]);
};
//----------------------------------------------------------------------------------
//Implementacion de las funciones de las clases

void Objeto3dSimple::init_vertices(vector<_vertex3f> v){
	vertices = v;
}

void Objeto3dSimple::draw_vertices(){
	int i;
	glColor3fv(&color_principal[0]);
	glPointSize(4);

	glBegin(GL_POINTS);
	for(i=0; i<vertices.size();i++)
		glVertex3f(vertices[i].x,vertices[i].y,vertices[i].z);
	glEnd();
}

void Objeto3d::init_caras(vector<_vertex3i> c){
	caras = c;
}

void Objeto3d::draw(GLenum draw_mode,GLfloat color[3]){
	int i;

	glColor3fv(&color[0]);
	glPointSize(4);
	
	glPolygonMode(GL_FRONT_AND_BACK,draw_mode);

	glBegin(GL_TRIANGLES);

	for(i=0;i<caras.size();i++){
		//En modo ajedrez intercambiar colores
		if(modo_actual == AJEDREZ){
			if(i % 2 == 0) 
				glColor3fv(&color_chess_0[0]);
			else
				glColor3fv(&color_chess_1[0]);
		}

		//Vertice 1 de la cara
		glVertex3f(vertices[caras[i]._0].x,
				   vertices[caras[i]._0].y,
		           vertices[caras[i]._0].z);

		//Vertice 2 de la cara
		glVertex3f(vertices[caras[i]._1].x,
				   vertices[caras[i]._1].y,
		           vertices[caras[i]._1].z);

		//Vertice 3 de la cara
		glVertex3f(vertices[caras[i]._2].x,
				   vertices[caras[i]._2].y,
		           vertices[caras[i]._2].z);
	}
	glEnd();
}


//----------------------------------------------------------------------------
//Objetos

vector<_vertex3f> vertices_tetraedro;
vector<_vertex3i> caras_tetraedro;
Objeto3d tetraedro;

vector<_vertex3f> vertices_cubo;
vector<_vertex3i> caras_cubo;
Objeto3d cubo;

//Objeto a pintar
Objeto3d objeto_actual;



//**************************************************************************
//
//***************************************************************************

void clear_window()
{

glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
}


//**************************************************************************
// Funcion para definir la transformación de proyeccion
//***************************************************************************

void change_projection()
{

glMatrixMode(GL_PROJECTION);
glLoadIdentity();

// formato(x_minimo,x_maximo, y_minimo, y_maximo,Front_plane, plano_traser)
//  Front_plane>0  Back_plane>PlanoDelantero)
glFrustum(-Window_width,Window_width,-Window_height,Window_height,Front_plane,Back_plane);
}

//**************************************************************************
// Funcion para definir la transformación de vista (posicionar la camara)
//***************************************************************************

void change_observer()
{

// posicion del observador
glMatrixMode(GL_MODELVIEW);
glLoadIdentity();
glTranslatef(0,0,-Observer_distance);
glRotatef(Observer_angle_x,1,0,0);
glRotatef(Observer_angle_y,0,1,0);
}

//**************************************************************************
// Funcion que dibuja los ejes utilizando la primitiva grafica de lineas
//***************************************************************************

void draw_axis()
{
glBegin(GL_LINES);
// eje X, color rojo
glColor3f(1,0,0);
glVertex3f(-AXIS_SIZE,0,0);
glVertex3f(AXIS_SIZE,0,0);
// eje Y, color verde
glColor3f(0,1,0);
glVertex3f(0,-AXIS_SIZE,0);
glVertex3f(0,AXIS_SIZE,0);
// eje Z, color azul
glColor3f(0,0,1);
glVertex3f(0,0,-AXIS_SIZE);
glVertex3f(0,0,AXIS_SIZE);
glEnd();
}


//**************************************************************************
// Funcion que dibuja los objetos
//***************************************************************************

void draw_objects()
{

	switch(modo_actual){

		case PUNTOS: objeto_actual.draw_vertices(); 
			break;

		case ALAMBRE: objeto_actual.draw(GL_LINE,color_principal);
			break;

		case SOLIDO:
		case AJEDREZ: objeto_actual.draw(GL_FILL,color_principal);
			break;
		case TODO://Modificación
			objeto_actual.draw_vertices();
			objeto_actual.draw(GL_LINE,color_chess_1);
			objeto_actual.draw(GL_FILL,color_chess_0);
	}

}

//**************************************************************************
//
//***************************************************************************

void draw_scene(void)
{

clear_window();
change_observer();
draw_axis();
draw_objects();
glutSwapBuffers();
}



//***************************************************************************
// Funcion llamada cuando se produce un cambio en el tamaño de la ventana
//
// el evento manda a la funcion:
// nuevo ancho
// nuevo alto
//***************************************************************************

void change_window_size(int Ancho1,int Alto1)
{
change_projection();
glViewport(0,0,Ancho1,Alto1);
glutPostRedisplay();
}


//***************************************************************************
// Funcion llamada cuando se produce aprieta una tecla normal
//
// el evento manda a la funcion:
// codigo de la tecla
// posicion x del raton
// posicion y del raton
//***************************************************************************

void normal_keys(unsigned char Tecla1,int x,int y)
{

	if (toupper(Tecla1)=='Q') exit(0);

	else if(Tecla1 == '1') modo_actual = PUNTOS;
	else if(Tecla1 == '2') modo_actual = ALAMBRE;
	else if(Tecla1 == '3') modo_actual = SOLIDO;
	else if(Tecla1 == '4') modo_actual = AJEDREZ;
	else if(toupper(Tecla1) == 'T') modo_actual = TODO;//Modificación 

	else if(toupper(Tecla1) == 'C') objeto_actual = cubo;
	else if(toupper(Tecla1) == 'V') objeto_actual = tetraedro;

	glutPostRedisplay(); //Redibujamos con el nuevo modo
}

//***************************************************************************
// Funcion llamada cuando se produce aprieta una tecla especial
//
// el evento manda a la funcion:
// codigo de la tecla
// posicion x del raton
// posicion y del raton

//***************************************************************************

void special_keys(int Tecla1,int x,int y)
{

switch (Tecla1){
	case GLUT_KEY_LEFT:Observer_angle_y--;break;
	case GLUT_KEY_RIGHT:Observer_angle_y++;break;
	case GLUT_KEY_UP:Observer_angle_x--;break;
	case GLUT_KEY_DOWN:Observer_angle_x++;break;
	case GLUT_KEY_PAGE_UP:Observer_distance*=1.2;break;
	case GLUT_KEY_PAGE_DOWN:Observer_distance/=1.2;break;
	}
glutPostRedisplay();
}



//***************************************************************************
// Funcion de incializacion
//***************************************************************************

void initialize(void)
{
// se inicalizan la ventana y los planos de corte
//Window_width=5;
//Window_height=5;
//Front_plane=10;
Window_width=0.5;
Window_height=0.5;
Front_plane=1;
Back_plane=1000;

// se inicia la posicion del observador, en el eje z
Observer_distance=2*Front_plane;
Observer_angle_x=0;
Observer_angle_y=0;

// se indica cual sera el color para limpiar la ventana	(r,v,a,al)
// blanco=(1,1,1,1) rojo=(1,0,0,1), ...
glClearColor(1,1,1,1);

// se habilita el z-bufer
glEnable(GL_DEPTH_TEST);
//
change_projection();
//
glViewport(0,0,UI_window_width,UI_window_height);
}


//***************************************************************************
// Programa principal
//
// Se encarga de iniciar la ventana, asignar las funciones e comenzar el
// bucle de eventos
//***************************************************************************

int main(int argc, char **argv)
{

//Este valor se podría inicializar en el constructor de la clase
float tam = 0.5;//Arista/2

vertices_tetraedro.push_back(_vertex3f(-tam,-tam,-tam));
vertices_tetraedro.push_back(_vertex3f(tam,-tam,-tam));
vertices_tetraedro.push_back(_vertex3f(0,-tam,tam));
vertices_tetraedro.push_back(_vertex3f(0,tam,0));

caras_tetraedro.push_back(_vertex3i(0,1,1));
caras_tetraedro.push_back(_vertex3i(0,3,1));
caras_tetraedro.push_back(_vertex3i(1,3,2));
caras_tetraedro.push_back(_vertex3i(2,3,0));

tetraedro.init_vertices(vertices_tetraedro);
tetraedro.init_caras(caras_tetraedro);


vertices_cubo.push_back(_vertex3f(tam, -tam, -tam));
vertices_cubo.push_back(_vertex3f(tam, tam, -tam));
vertices_cubo.push_back(_vertex3f(tam, tam, tam));
vertices_cubo.push_back(_vertex3f(tam, -tam, tam));

vertices_cubo.push_back(_vertex3f(-tam, -tam, -tam));
vertices_cubo.push_back(_vertex3f(-tam, tam, -tam));
vertices_cubo.push_back(_vertex3f(-tam, tam, tam));
vertices_cubo.push_back(_vertex3f(-tam, -tam, tam));

caras_cubo.push_back(_vertex3i(0,1,2));
caras_cubo.push_back(_vertex3i(0,3,2));
caras_cubo.push_back(_vertex3i(3,2,6));
caras_cubo.push_back(_vertex3i(3,7,6));
caras_cubo.push_back(_vertex3i(7,6,5));
caras_cubo.push_back(_vertex3i(7,4,5));
caras_cubo.push_back(_vertex3i(4,5,1));
caras_cubo.push_back(_vertex3i(4,0,1));
caras_cubo.push_back(_vertex3i(1,5,6));
caras_cubo.push_back(_vertex3i(1,2,6));
caras_cubo.push_back(_vertex3i(4,0,3));
caras_cubo.push_back(_vertex3i(4,7,3));

cubo.init_vertices(vertices_cubo);
cubo.init_caras(caras_cubo);

objeto_actual = tetraedro;



// se llama a la inicialización de glut
glutInit(&argc, argv);

// se indica las caracteristicas que se desean para la visualización con OpenGL
// Las posibilidades son:
// GLUT_SIMPLE -> memoria de imagen simple
// GLUT_DOUBLE -> memoria de imagen doble
// GLUT_INDEX -> memoria de imagen con color indizado
// GLUT_RGB -> memoria de imagen con componentes rojo, verde y azul para cada pixel
// GLUT_RGBA -> memoria de imagen con componentes rojo, verde, azul y alfa para cada pixel
// GLUT_DEPTH -> memoria de profundidad o z-bufer
// GLUT_STENCIL -> memoria de estarcido
glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);

// posicion de la esquina inferior izquierdad de la ventana
glutInitWindowPosition(UI_window_pos_x,UI_window_pos_y);

// tamaño de la ventana (ancho y alto)
glutInitWindowSize(UI_window_width,UI_window_height);

// llamada para crear la ventana, indicando el titulo (no se visualiza hasta que se llama
// al bucle de eventos)
glutCreateWindow("Práctica 1");

// asignación de la funcion llamada "dibujar" al evento de dibujo
glutDisplayFunc(draw_scene);
// asignación de la funcion llamada "cambiar_tamanio_ventana" al evento correspondiente
glutReshapeFunc(change_window_size);
// asignación de la funcion llamada "tecla_normal" al evento correspondiente
glutKeyboardFunc(normal_keys);
// asignación de la funcion llamada "tecla_Especial" al evento correspondiente
glutSpecialFunc(special_keys);

// funcion de inicialización
initialize();

// inicio del bucle de eventos
glutMainLoop();
return 0;
}
