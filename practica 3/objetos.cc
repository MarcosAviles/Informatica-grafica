//**************************************************************************
// Práctica 1 usando objetos
//**************************************************************************

#include "objetos.h"
#include "file_ply_stl.h"
#include <GL/glut.h>
#include <GL/gl.h>


//*************************************************************************
// _puntos3D
//*************************************************************************

_puntos3D::_puntos3D()
{
    
}

//*************************************************************************
// dibujar puntos
//*************************************************************************

void _puntos3D::draw_puntos(float r, float g, float b, int grosor)
{
	glColor3f(r,g,b);
	glPointSize(grosor);
	glBegin(GL_POINTS);
		for(int i=0; i<vertices.size(); i++){
			glVertex3f(vertices[i].x, vertices[i].y, vertices[i].z);
		}
	glEnd();
}


//*************************************************************************
// _triangulos3D
//*************************************************************************

_triangulos3D::_triangulos3D()
{

}


//*************************************************************************
// dibujar en modo arista
//*************************************************************************

void _triangulos3D::draw_aristas(float r, float g, float b, int grosor)
{
	glLineWidth(grosor);
	glColor3f(r,g,b);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glBegin(GL_TRIANGLES);
		for(int i=0; i<caras.size(); i++){
			for(int x=0; x<3; x++){
				glVertex3f(vertices[caras[i][x]].x, vertices[caras[i][x]].y, vertices[caras[i][x]].z);
			}
		}
	glEnd();
}

//*************************************************************************
// dibujar en modo sólido
//*************************************************************************

void _triangulos3D::draw_solido(float r, float g, float b)
{
	glColor3f(r,g,b);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glBegin(GL_TRIANGLES);
		for(int i=0; i<caras.size(); i++){
			for(int x=0; x<3; x++){
				glVertex3f(vertices[caras[i][x]].x, vertices[caras[i][x]].y, vertices[caras[i][x]].z);
			}
		}
	glEnd();
}

//*************************************************************************
// dibujar en modo sólido con apariencia de ajedrez
//*************************************************************************

void _triangulos3D::draw_solido_ajedrez(float r1, float g1, float b1, float r2, float g2, float b2)
{
	glEnable(GL_CULL_FACE);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glBegin(GL_TRIANGLES);
		for(int i=0; i<caras.size(); i++){
			if(i%2==0){
				glColor3f(r1,g1,b1);
			}
			else{
				glColor3f(r2,g2,b2);
			}
			for(int x=0; x<3; x++){
				glVertex3f(vertices[caras[i][x]].x, vertices[caras[i][x]].y, vertices[caras[i][x]].z);
			}
		}
	glEnd();
}





//*************************************************************************
// clase cubo
//*************************************************************************

_cubo::_cubo(float tam)
{
	// Inicializo los valores de las coordenadas de todos los vertices del cubo (8 vertices)
	// V0
	vertices.push_back(_vertex3f(0.0,0.0,0.0));	
	// V1
	vertices.push_back(_vertex3f(tam,0.0,0.0));	
	// V2
	vertices.push_back(_vertex3f(0.0,tam,0.0));	
	// V3
	vertices.push_back(_vertex3f(tam,tam,0.0));	
	// V4
	vertices.push_back(_vertex3f(0.0,tam,-tam));	
	// V5
	vertices.push_back(_vertex3f(0.0,0.0,-tam));	
	// V6
	vertices.push_back(_vertex3f(tam,tam,-tam));	
	// V7
	vertices.push_back(_vertex3f(tam,0.0,-tam));

	// Emparejo los vertices correspondientes a las caras planas
	// C0	
	caras.push_back(_vertex3i(0,1,2));
	caras.push_back(_vertex3i(2,1,3));
	// C1
	caras.push_back(_vertex3i(1,7,3));
	caras.push_back(_vertex3i(3,7,6));
	// C2
	caras.push_back(_vertex3i(4,2,3));
	caras.push_back(_vertex3i(4,3,6));
	// C3
	caras.push_back(_vertex3i(4,5,0));
	caras.push_back(_vertex3i(4,0,2));
	// C4
	caras.push_back(_vertex3i(0,5,7));
	caras.push_back(_vertex3i(0,7,1));
	// C5
	caras.push_back(_vertex3i(5,4,6));
	caras.push_back(_vertex3i(5,6,7));
}


//*************************************************************************
// clase piramide
//*************************************************************************

_piramide::_piramide(float tam, float al)
{
	// Inicializo los valores de las coordenadas de todos los vertices del tetraedro (4 vertices)
	// V0
	vertices.push_back(_vertex3f(tam,tam,0.0));	
	// V1
	vertices.push_back(_vertex3f(-tam,tam,0.0));	
	// V2
	vertices.push_back(_vertex3f(0.0,-tam,0.0));	
	// V3
	vertices.push_back(_vertex3f(0.0,0.0,-al));	

	// Emparejo los vertices correspondientes a las caras planas
	// C0
	caras.push_back(_vertex3i(1,2,0));
	// C1
	caras.push_back(_vertex3i(0,2,3));
	// C2
	caras.push_back(_vertex3i(3,2,1));
	// C3
	caras.push_back(_vertex3i(1,0,3));

}


//*************************************************************************
// clase modeloPly
//*************************************************************************

_modeloply::_modeloply(bool defecto)
{
	_file_ply fichero;
	char * nom_fichero=(char*)"./beethoven.ply";
	vector<float> v;
	vector<int> c;
	fichero.open(nom_fichero);
	fichero.read(v, c);
	fichero.close();
	for(int i=0; i<v.size(); i+=3){
		vertices.push_back(_vertex3f(v[i],v[i+1],v[i+2]));
	}
	for(int i=0; i<c.size(); i+=3){
		caras.push_back(_vertex3i(c[i],c[i+1],c[i+2]));
	}
}

_modeloply::_modeloply(int num_perfiles)
{
	_file_ply fichero;
	char * nom_fichero=(char*)"./perfil.ply";
	vector<float> v;
	vector<int> c;
	fichero.open(nom_fichero);
	fichero.read(v, c);
	fichero.close();
	for(int i=0; i<v.size(); i+=3){
		vertices.push_back(_vertex3f(v[i],v[i+1],v[i+2]));
	}
	int num_vertices=vertices.size();
	float const PI=3.141592;
	float angulo=(2*PI)/num_perfiles;
	float x,z;
	for(int i=0; i<num_perfiles-1; i++){
		for(int j=0; j<num_vertices; j++){
			x=(vertices[j].x*cos(angulo*(i+1)))+(vertices[j].z*sin(angulo*(i+1)));
			z=(vertices[j].x*sin(angulo*(i+1)))+(vertices[j].z*cos(angulo*(i+1)));
			vertices.push_back(_vertex3f(x,vertices[j].y,z));
		}

		for(int j=0; j<num_vertices-1; j++){
			caras.push_back(_vertex3i(((i+1)*num_vertices)+j+1, (i+1)*num_vertices+j, i*num_vertices+j ));
			caras.push_back(_vertex3i(i*num_vertices+j, (i*num_vertices)+j+1, ((i+1)*num_vertices)+j+1));
		}
	}
	// Caras del ultimo perfil
	num_perfiles=num_perfiles-1;
	for(int i=0; i<num_vertices-1; i++){
		caras.push_back(_vertex3i(0*num_vertices+i+1, 0*num_vertices+i, num_perfiles*num_vertices+i));
		caras.push_back(_vertex3i(num_perfiles*num_vertices+i, num_perfiles*num_vertices+i+1, 0*num_vertices+i+1));
	}
	// Vertices de las tapas
	vertices.push_back(_vertex3f(0,vertices[0].y,0));
	vertices.push_back(_vertex3f(0,vertices[num_vertices-1].y+0.07,0));
	//Caras de la tapa inferior
	for(int i=0;i<num_perfiles; i++){
		caras.push_back(_vertex3i(i*num_vertices+0, (i+1)*num_vertices+0, (num_perfiles*num_vertices)+num_vertices));
	}
	caras.push_back(_vertex3i(num_perfiles*num_vertices+0, 0*num_vertices+0, (num_perfiles*num_vertices)+num_vertices));
	//Caras de la tapa superior
	for(int i=0;i<num_perfiles; i++){
		caras.push_back(_vertex3i(i*num_vertices+num_vertices-1, (num_perfiles*num_vertices)+num_vertices+1, (i+1)*num_vertices+num_vertices-1));
	}
	caras.push_back(_vertex3i(num_perfiles*num_vertices+num_vertices-1, (num_perfiles*num_vertices)+num_vertices+1, 0*num_vertices+num_vertices-1));
}

_modeloply::_modeloply(bool opcional, int numero_barridos){

	vertices.push_back(_vertex3f(-1,0,0));
	vertices.push_back(_vertex3f(-0.3,0.3,0));
	vertices.push_back(_vertex3f(0,1,0));
	vertices.push_back(_vertex3f(0.3,0.3,0));
	vertices.push_back(_vertex3f(1,0,0));
	vertices.push_back(_vertex3f(0.3,-0.3,0));
	vertices.push_back(_vertex3f(0,-1,0));
	vertices.push_back(_vertex3f(-0.3,-0.3,0));

	int num_vertices=vertices.size();
	float profundidad=-0.5;
	for(int i=0; i<numero_barridos; i++){
		for(int j=0; j<num_vertices; j++){
			vertices.push_back(_vertex3f(vertices[j].x, vertices[j].y, profundidad));
		}
		for(int j=0; j<num_vertices-1; j++){
			caras.push_back(_vertex3i(i*num_vertices+j, (i+1)*num_vertices+j, (i+1)*num_vertices+j+1));
			caras.push_back(_vertex3i(i*num_vertices+j, (i+1)*num_vertices+j+1, i*num_vertices+j+1));
		}
		//Ultimas caras del perfil
		caras.push_back(_vertex3i(i*num_vertices, (i+1)*num_vertices-1, (i+2)*num_vertices-1));
		caras.push_back(_vertex3i(i*num_vertices, (i+2)*num_vertices-1, (i+1)*num_vertices));
		profundidad-=0.5;
	}

	// Cara trasera
	for(int i=1; i<num_vertices-1; i+=2){
		caras.push_back(_vertex3i(i,i+1,i+2));
	}
	caras.push_back(_vertex3i(0,1,7));
	caras.push_back(_vertex3i(1,5,7));
	caras.push_back(_vertex3i(1,3,5));

	// Cara frontal
	for(int i=num_vertices*numero_barridos+1; i<numero_barridos*num_vertices+num_vertices-1; i+=2){
		caras.push_back(_vertex3i(i,i+2,i+1));
	}
	caras.push_back(_vertex3i(numero_barridos*num_vertices,numero_barridos*num_vertices+num_vertices-1,num_vertices*numero_barridos+1));
	caras.push_back(_vertex3i(numero_barridos*num_vertices+1,num_vertices*numero_barridos+num_vertices-1,num_vertices*numero_barridos+num_vertices-3));
	caras.push_back(_vertex3i(numero_barridos*num_vertices+1,num_vertices*numero_barridos+num_vertices-3,num_vertices*numero_barridos+num_vertices-5));
	
}

//*************************************************************************
// clase grua
//*************************************************************************
_grua::_grua(){

}

void _grua::draw(float a, float b, float g, int al, int an){
	int altura=al, anchura=an, cola=(anchura/2);
	glPushMatrix();
		glScalef(2,0.2,2);
		cubo.draw_solido(1,0,0); // Base Peana
	glPopMatrix();

/*-----------------Pie-------------------------------------------------*/

	for(int i=0; i<altura; i++){
		glPushMatrix();
			glTranslatef(0.5,0.2+i,-0.5);
			cubo.draw_aristas(0,0,1,10);
		glPopMatrix();
	}
/*------------------------Cabeza--------------------------------------------*/
	glPushMatrix(); // Primer grado de libertad
		glTranslatef(1,0.2+altura,-1);
		glRotatef(a,0,1,0);
		glTranslatef(-1,-altura-0.2,+1);
	for(int i=0; i<anchura; i++){
		glPushMatrix();
			glTranslatef(1.5+i,0.2+altura,-0.5);
			cubo.draw_aristas(0,0,1,10);
		glPopMatrix();
	}

	for(int i=0; i<=cola; i++){ //Cola
		glPushMatrix();
			glTranslatef(0.5-i,0.2+altura,-0.5);
			glScalef(1,0.2,1);
			cubo.draw_aristas(0,0,1,10);
		glPopMatrix();
	}


	float aux=0;
	for(int i=0; i<cola; i++){ //Contrapeso
		glPushMatrix();
			glTranslatef(0.5-cola,altura-aux,-0.5);
			glScalef(1,0.2,1);
			cubo.draw_solido(0,0,0);
		glPopMatrix();
		aux+=0.2;
	}
	

/*-------------------------------Carro----------------------------------------*/
	glPushMatrix(); // Segundo grado de libertad
		glTranslatef(b,0,0);
		glPushMatrix();
			glTranslatef(1.5,altura,-0.5);
			glScalef(1,0.2,1);
			cubo.draw_solido(1,0,0);
		glPopMatrix(); 

/*--------------------------Gancho----------------------------------------------*/
							 // Tercer grado de libertad
		glPushMatrix();
			glTranslatef(2,altura,-1);
			glRotatef(180,1,0,0); // Lo roto porque el cubo esta posicionado en el eje x e y positivos, 
									// como se trata de bajar el gancho, la altura de deber negativa, por tanto si no lo
									// roto pasaria por el 0,0 por lo que el gancho se haria cada vez mas pequeño inlcuso desaparecerá
									// hasta que la altura de bajada sea superior a 1
			glScalef(0.1,1+g,0.1);
			cubo.draw_solido(0,0,0);
		glPopMatrix();

		glPushMatrix();
			glTranslatef(2,altura-1.2-g,-1);
			glScalef(0.2,0.2,0.2);
			cubo.draw_solido(0,0,0);
		glPopMatrix();
			 			// Tercer grado de libertad
	glPopMatrix(); // Segundo grado de libertad

glPopMatrix(); // Primer grado de libertad


}