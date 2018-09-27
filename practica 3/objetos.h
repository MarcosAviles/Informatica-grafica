//**************************************************************************
// Práctica 1 usando objetos
//**************************************************************************

#include <vector>
#include <GL/gl.h>
#include <GL/glut.h>
#include "vertex.h"
#include <stdlib.h>
#include <vector>

using namespace std;

const float AXIS_SIZE=5000;

//*************************************************************************
// clase punto
//*************************************************************************

class _puntos3D
{
public:

  
	_puntos3D();
void 	draw_puntos(float r, float g, float b, int grosor);

vector<_vertex3f> vertices;
};

//*************************************************************************
// clase triángulo
//*************************************************************************

class _triangulos3D: public _puntos3D
{
public:

	_triangulos3D();
void 	draw_aristas(float r, float g, float b, int grosor);
void    draw_solido(float r, float g, float b);
void 	draw_solido_ajedrez(float r1, float g1, float b1, float r2, float g2, float b2);

vector<_vertex3i> caras;
};


//*************************************************************************
// clase cubo
//*************************************************************************

class _cubo: public _triangulos3D
{
public:

	_cubo(float tam=1);
};


//*************************************************************************
// clase piramide
//*************************************************************************

class _piramide: public _triangulos3D
{
public:

	_piramide(float tam=1, float al=1.25);
};

//*************************************************************************
// clase modeloPly
//*************************************************************************

class _modeloply:public _triangulos3D
{
public:
	_modeloply(bool defecto);
	_modeloply(int num_perfiles);
	_modeloply(bool opcional, int numero_barridos);
};

class _grua: public _triangulos3D{
public:
	_cubo cubo;
	_piramide piramide;
	_grua();
	void draw(float a, float b, float g, int al, int an);
};
