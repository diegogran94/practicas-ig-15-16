#include "stdlib.h"
#include "stdio.h"
#include <GL/glut.h>
#include <ctype.h>

#include <vector>
#include "vertex.h"

#include "Objeto3d.h"
#include "file_ply_stl.h"

void Objeto3dSimple::init_vertices(vector<_vertex3f> v){
	vertices = v;
}

void Objeto3dSimple::draw_vertices(GLfloat color[3]){
	int i;
	glColor3fv(&color[0]);
	glPointSize(4);

	glBegin(GL_POINTS);
	for(i=0; i<vertices.size();i++)
		glVertex3f(vertices[i].x,vertices[i].y,vertices[i].z);
	glEnd();
}

void Objeto3d::init_caras(vector<_vertex3i> c){
	caras = c;
}

void Objeto3d::draw(Mode draw_mode,GLfloat color[3]){
	int i;

	glColor3fv(&color[0]);
	glPointSize(4);
	
	GLenum mode;
	switch(draw_mode){
		case PUNTOS : mode = GL_POINTS; break;
		case ALAMBRE : mode = GL_LINE; break;
		case SOLIDO : 
		case AJEDREZ : mode = GL_FILL; break;
	}

	glPolygonMode(GL_FRONT_AND_BACK,mode);

	if(draw_mode == PUNTOS)
		glBegin(GL_POINTS);
	else
		glBegin(GL_TRIANGLES);

	for(i=0;i<caras.size();i++){
		
		//En modo ajedrez intercambiar colores
		if(draw_mode == AJEDREZ){
			if(i % 2 == 0) 
				glColor3fv(&color[0]);
			else
				glColor3f(1,1,0);
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


void Objeto3d::load_ply(char* filename){
	
	vector<float> vertices_ply;
	vector<int> caras_ply;

	_file_ply reader;

	reader.open(filename);

	reader.read(vertices_ply, caras_ply);

	//La funcion reader introduce en los vectores las coordenadas
	//de los puntos consecutivamente:
	// vertices[0] = v0.x
	// vertices[1] = v0.y
	// vertices[2] = v0.z
	// vertices[3] = v1.x
	// ...
	//Por lo que hace falta introducirlos ordenadamente en un vertex

	int i;
	for(i=0; i<vertices_ply.size(); i+=3){

		_vertex3f aux;
		aux.x = vertices_ply.at(i);
		aux.y = vertices_ply.at(i+1);
		aux.z = vertices_ply.at(i+2);

		vertices.push_back(aux);
	}

	for(i=0; i<caras_ply.size(); i+=3){

		_vertex3i aux;
		aux.x = caras_ply.at(i);
		aux.y = caras_ply.at(i+1);
		aux.z = caras_ply.at(i+2);

		caras.push_back(aux);
	}

	reader.close();
}

float Objeto3d::grados_a_radianes(float angulo){
	return angulo*(M_PI / 180);
}


// Devuelve 
_vertex3f Objeto3d::rotacionY(_vertex3f punto, double alfa){

	_vertex3f nuevo_punto;

	nuevo_punto.x = cos(alfa) * punto.x + sin(alfa) * punto.z;
	nuevo_punto.y = punto.y;
	nuevo_punto.z = sin(alfa) * punto.x + cos(alfa) * punto.z;

	return nuevo_punto;
}


void Objeto3d::revolucion(int veces, float angulo_f, bool tiene_tapas){

	//Numero de vertices del perfil original
	int tam_perfil = vertices.size();


	float angulo = grados_a_radianes(angulo_f) / veces;
	//float angulo = M_PI*2 / veces;

	caras.clear();

	//Generar puntos nuevos
	for (int i=1; i <= veces; i++){//Empezamos en 1 para no multiplicar por 0 el angulo
		
		vector<_vertex3f> nuevo_perfil(tam_perfil);

		for(int j=0; j<tam_perfil; j++){

			nuevo_perfil.at(j)= rotacionY(vertices.at(j),angulo*(i));
		}

		vertices.insert(vertices.end(), nuevo_perfil.begin(), 
			nuevo_perfil.end());

		//Generar caras
		
		int inicio_perfil = i*tam_perfil; //Primer vertice del perfil

		for(int k= inicio_perfil; k< inicio_perfil+tam_perfil-1; k++){

			_vertex3i nueva_cara_par, nueva_cara_impar;

			nueva_cara_impar.x = k%vertices.size();
			nueva_cara_impar.y = (k-tam_perfil)%vertices.size();
			nueva_cara_impar.z = (k-tam_perfil+1)%vertices.size();

			nueva_cara_par.x = (k-tam_perfil+1)%vertices.size();
			nueva_cara_par.y = (k+1)%vertices.size();
			nueva_cara_par.z = k%vertices.size();

			caras.push_back(nueva_cara_impar);
			caras.push_back(nueva_cara_par);
		
		}
		
	}

	//TAPAS

	//Tapa superior
	if(vertices.at(tam_perfil-1).x != 0.0 && tiene_tapas){

		_vertex3f pto_central;

		pto_central.x = 0;
		pto_central.y = vertices.at(tam_perfil-1).y;
		pto_central.z = 0;

		vertices.push_back(pto_central);

		for(int l = 0; l<veces; l++){

			_vertex3i nueva_cara;
		nueva_cara.x = (vertices.size()-1);        
        nueva_cara.y = ((l*tam_perfil)+tam_perfil-1%(vertices.size()-1));
		nueva_cara.z = (((l*tam_perfil)+tam_perfil)+tam_perfil-1%(vertices.size()-1));
		

			caras.push_back(nueva_cara);
		}

	}
	
	//Tapa inferior
	if(vertices.front().x != 0.0 && tiene_tapas){//Tiene tapa superior

		_vertex3f pto_central;

		pto_central.x = 0;
		pto_central.y = vertices.front().y;
		pto_central.z = 0;

		vertices.push_back(pto_central);

		for(int l = 0; l<veces; l++){

			_vertex3i nueva_cara;

				nueva_cara.x = (vertices.size()-1);        
        nueva_cara.y = ((l*tam_perfil)%(vertices.size()-2));//-2 para no incluir los puntos centrales
		nueva_cara.z = (((l*tam_perfil)+tam_perfil)%(vertices.size()-2));

		
			caras.push_back(nueva_cara);
		}

	}

	

}


