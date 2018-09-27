//**************************************************************************
// Práctica 1 usando objetos
//**************************************************************************

#include "objetos.h"
#include <GL/glut.h>


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
	glColor3f(r,g,b);
	glLineWidth(grosor);
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
	caras.push_back(_vertex3i(0,1,3));
	// C1
	caras.push_back(_vertex3i(1,2,3));
	// C2
	caras.push_back(_vertex3i(2,0,3));
	// C3
	caras.push_back(_vertex3i(0,1,2));

}
