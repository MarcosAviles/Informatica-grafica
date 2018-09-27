//**************************************************************************
// Práctica 1 usando objetos
//**************************************************************************

#include <vector>
#include <GL/gl.h>
#include <GL/glut.h>
#include "vertex.h"
#include "jpg_imagen.hpp"
#include "jpg_jinclude.h"
#include <stdlib.h>

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
vector<_vertex3f> normal_vertices;
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
vector<_vertex3f> normal_caras;
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


class _grua: public _triangulos3D{
public:
	_cubo cubo;
	_piramide piramide;
	_grua();
	void draw(float a, float b, float g, int al, int an);
};

class _fuenteLuz{
private:
	GLenum id;

public:
	_fuenteLuz(GLenum id);
	void activar();
	void setambiental(const GLfloat x[]);
	void setdifusa(const GLfloat x[]);
	void setespecular(const GLfloat x[]);
	void setposicion(float a, float b, float angulo);
	void desactivar();

};

class _textura {
    private:
        jpg::Imagen * pimg;
        unsigned int tamx;
        unsigned int tamy;
        unsigned char * texels;
        unsigned int id;
    public:
        _textura(char *file_name);
        void automatica();
        void activar();
        void desactivar();
        void desactivar_auto();
};



//*************************************************************************
// clase modeloPly
//*************************************************************************

class _modeloply:public _triangulos3D
{
public:
	_modeloply(char * ruta);
	_modeloply(int num_perfiles); // Barrido sin el ultimo perfil
	_modeloply(bool opcional, int numero_barridos);
	_modeloply(int num_perfiles, char * ruta, bool otro); // Barrido duplicando el último perfil

	void calcularNormales();
	void calculoNormalcaras();
	void calculoNormalvertices();
	void calcularCoordenadas();

	void draw_suavizado_plano();
	void draw_suavizado_gouroud();
	void draw_textura(float r, float g, float b);
	void TieneTextura();

private:
	vector<_vertex2f>coordenadas_textura;
	bool textura;
	int numero_vertices;
	int numero_perfiles;
};

//*************************************************************************
// clase Camara
//*************************************************************************

class _camara{

public:
	_camara(GLfloat d, GLfloat x, GLfloat y);
	void setDistancia(GLfloat x);
	void setX(GLfloat x);
	void setY(GLfloat y);
	void seteye(_vertex3f x);
	void setcenter(_vertex3f x);
	void setup(_vertex3f y);
	void setalfa(float x);
	void setbeta(float y);
	GLfloat getDistancia();
	GLfloat getX();
	GLfloat getY();
	_vertex3f geteye();
	_vertex3f getcenter();
	_vertex3f getup();
	float getalfa();
	float getbeta();
private:
	GLfloat Observer_distance;
    GLfloat Observer_angle_x;
    GLfloat Observer_angle_y;
    _vertex3f eye, center, up;
    float alfa, beta;
};
