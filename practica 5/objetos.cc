//**************************************************************************
// Práctica 1 usando objetos
//**************************************************************************

#include "objetos.h"
#include "file_ply_stl.h"
#include <vector>
#include <GL/gl.h>
#include <GL/glut.h>
#include "vertex.h"
#include <stdlib.h>


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

_modeloply::_modeloply(char * ruta)
{
	_file_ply fichero;
	char * nom_fichero=ruta;
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

_modeloply::_modeloply(int num_perfiles, char * ruta, bool otro)
{
	_file_ply fichero;
	char * nom_fichero=ruta;
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
	for(int i=0; i<num_perfiles; i++){
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
	if(!otro){
		// Vertices de las tapas
		vertices.push_back(_vertex3f(0,vertices[0].y,0));
		vertices.push_back(_vertex3f(0,vertices[num_vertices-1].y+0.07,0));
		//Caras de la tapa inferior
		for(int i=0;i<num_perfiles; i++){
			caras.push_back(_vertex3i(i*num_vertices+0, (i+1)*num_vertices+0, (num_perfiles*num_vertices)+num_vertices));
		}

		//Caras de la tapa superior
		for(int i=0;i<num_perfiles; i++){
			caras.push_back(_vertex3i(i*num_vertices+num_vertices-1, (num_perfiles*num_vertices)+num_vertices+1, (i+1)*num_vertices+num_vertices-1));
		}
	}
	this->numero_perfiles=num_perfiles;
	this->numero_vertices=num_vertices;
	this->textura=false;
	this->calcularNormales();
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

void _modeloply::calculoNormalcaras(){
	for(int i=0; i<caras.size(); i++){
		_vertex3f v1;
		v1.x=vertices[caras[i][1]].x-vertices[caras[i][0]].x;
		v1.y=vertices[caras[i][1]].y-vertices[caras[i][0]].y;
		v1.z=vertices[caras[i][1]].z-vertices[caras[i][0]].z;
		_vertex3f v2;
		v2.x=vertices[caras[i][2]].x-vertices[caras[i][0]].x;
		v2.y=vertices[caras[i][2]].y-vertices[caras[i][0]].y;
		v2.z=vertices[caras[i][2]].z-vertices[caras[i][0]].z;
		_vertex3f aux=v1.cross_product(v2);
		aux.normalize();
		normal_caras.push_back(_vertex3f(aux.x,aux.y,aux.z));
	}
}

void _modeloply::calculoNormalvertices(){
	for(int i=0; i<vertices.size(); i++){
		normal_vertices.push_back(_vertex3f(0.0,0.0,0.0));
	}
	for(int i=0; i<caras.size();i++){
		
		normal_vertices[caras[i][0]]+=normal_caras[i];
		normal_vertices[caras[i][1]]+=normal_caras[i];
		normal_vertices[caras[i][2]]+=normal_caras[i];

	}

	for(int i=0; i<normal_vertices.size(); i++){
		normal_vertices[i].normalize();
		//normal_vertices[i].show_values();
	}
}

void _modeloply::calcularNormales(){
	this->calculoNormalcaras();
	this->calculoNormalvertices();
}

void _modeloply::TieneTextura(){
	textura=true;
	this->calcularCoordenadas();
}


void _modeloply::draw_suavizado_plano(){
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glShadeModel(GL_FLAT);
	glBegin(GL_TRIANGLES);
		for(int i=0; i<normal_caras.size(); i++){
			glNormal3f(normal_vertices[caras[i].x].x,normal_vertices[caras[i].x].y,normal_vertices[caras[i].x].z);
			for(int x=0; x<3; x++){
				if(textura){
					glTexCoord2f(coordenadas_textura[caras[i][x]].s,coordenadas_textura[caras[i][x]].t);
				}
				glVertex3f(vertices[caras[i][x]].x, vertices[caras[i][x]].y, vertices[caras[i][x]].z);
			}
		}
	glEnd();

}

void _modeloply::draw_textura(float r, float g, float b){
	if(textura){
		glColor3f(r,g,b);
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		glBegin(GL_TRIANGLES);
		for(int i=0; i<caras.size(); i++){
			for(int j=0; j<3; j++){
				glTexCoord2f(coordenadas_textura[caras[i][j]].s,coordenadas_textura[caras[i][j]].t);
				glVertex3f(vertices[caras[i][j]].x, vertices[caras[i][j]].y, vertices[caras[i][j]].z);
			}
		}
		glEnd();
	}
	
}


void _modeloply::draw_suavizado_gouroud(){
	glShadeModel(GL_SMOOTH);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glBegin(GL_TRIANGLES);
		for(int i=0; i<normal_caras.size(); i++){
			for(int x=0; x<3; x++){
				glNormal3f(normal_vertices[caras[i][x]].x,normal_vertices[caras[i][x]].y,normal_vertices[caras[i][x]].z);
				glVertex3f(vertices[caras[i][x]].x, vertices[caras[i][x]].y, vertices[caras[i][x]].z);
			}
		}
	glEnd();

}


void _modeloply::calcularCoordenadas(){
	for(int i=0; i<vertices.size(); i++){
		coordenadas_textura.push_back(_vertex2f(0.0,0.0));
	}/*
	float aux;
	for(int i=0; i<numero_perfiles; i++){
		aux=i/(numero_perfiles-1);
		for(int j=0; j<numero_vertices; j++){
			coordenadas_textura[j+i].s=aux;
			coordenadas_textura[j+i].t=j/(numero_vertices-1);
			
		}
	}*/
    float var = 1.0/numero_perfiles;
    vector<float> distancia(numero_vertices);
    float suma = 0.0;
    distancia[0] = suma;
    for(int i=1; i<numero_vertices; i++) {
        suma += sqrt(pow(vertices[i].x-vertices[i-1].x,2)+pow(vertices[i].y-vertices[i-1].y,2));
        distancia[i] = suma;
    }
    for(int i=0; i<numero_vertices; i++) {
        distancia[i] /= suma;
    }
    for(unsigned int i=0; i<numero_perfiles+1; i++) {
        for(unsigned int j=0; j<numero_vertices; j++) {
            coordenadas_textura[i*numero_vertices+j].s = 1-i*var;           
            coordenadas_textura[i*numero_vertices+j].t = 1-distancia[j];   
        }
    }
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

//*************************************************************************
// clase fuente de luz
//*************************************************************************

_fuenteLuz::_fuenteLuz(GLenum ide){
	id=ide;
}

void _fuenteLuz::activar(){
	glEnable(GL_LIGHTING);
	glEnable(id);
}

void _fuenteLuz::setambiental(const GLfloat x[]){
	glLightfv(id,GL_AMBIENT,x);
}

void _fuenteLuz::setespecular(const GLfloat x[]){
	glLightfv(id,GL_SPECULAR,x);
}
void _fuenteLuz::setdifusa(const GLfloat x[]){
	glLightfv(id,GL_DIFFUSE,x);
}
void _fuenteLuz::setposicion(float a, float b,float angulo){
	glPushMatrix();
	//glRotatef(a,0,1,0);
    //glRotatef(b,1,0,0);
    GLfloat x[]={0,0,0,0};
    /*x[0]=angulo*sin(b*M_PI/180)*cos(a*M_PI/180);
	x[1]=angulo*sin(b*M_PI/180)*sin(a*M_PI/180);
	x[2]=angulo*cos(a*M_PI/180);*/

	x[0]=angulo*cos(b*M_PI/180)*sin(a*M_PI/180);
	x[1]=angulo*sin(b*M_PI/180);
	x[2]=angulo*cos(b*M_PI/180)*cos(a*M_PI/180);
	glLightfv(id,GL_POSITION,x);
	glPopMatrix();
}

void _fuenteLuz::desactivar(){
	glDisable(id);
	glDisable(GL_LIGHTING);
	
}


//*************************************************************************
// clase Textura
//*************************************************************************

_textura::_textura(char *file_name){
	pimg = new jpg::Imagen(file_name);
    tamx = pimg->tamX();
    tamy = pimg->tamY();
    texels = pimg->leerPixels();
    glGenTextures(1,&id);
	glBindTexture(GL_TEXTURE_2D,id);
	glTexImage2D(GL_TEXTURE_2D,0,3,tamx,tamy,0,GL_RGB,GL_UNSIGNED_BYTE,texels);
    
}
void _textura::automatica(){
	glEnable(GL_TEXTURE_GEN_S);
    glEnable(GL_TEXTURE_GEN_T);
    glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D,id);
	glTexImage2D(GL_TEXTURE_2D,0,3,tamx,tamy,0,GL_RGB,GL_UNSIGNED_BYTE,texels);
	glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
	//glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);

	/*glTexGeni(GL_S,GL_TEXTURE_GEN_MODE,GL_OBJECT_LINEAR);
    glTexGeni(GL_T,GL_TEXTURE_GEN_MODE,GL_OBJECT_LINEAR);
    glTexGenf(GL_S,GL_TEXTURE_GEN_MODE,GL_OBJECT_LINEAR);
    glTexGenf(GL_T,GL_TEXTURE_GEN_MODE,GL_OBJECT_LINEAR);*/
    
    
}

void _textura::desactivar_auto(){
	glDisable(GL_TEXTURE_2D);
	glDisable(GL_TEXTURE_GEN_S);
    glDisable(GL_TEXTURE_GEN_T);
}
void _textura::activar(){
	//glEnable(GL_DEPTH_TEST);
	glDisable(GL_TEXTURE_GEN_S);
    glDisable(GL_TEXTURE_GEN_T);
    glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D,0,3,tamx,tamy,0,GL_RGB,GL_UNSIGNED_BYTE,texels);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D,id);
	
	
}

void _textura::desactivar(){
	glDisable(GL_TEXTURE_2D);
}

//*************************************************************************
// clase Cámara
//*************************************************************************

_camara::_camara(GLfloat d, GLfloat x, GLfloat y){
	Observer_distance=d;
    Observer_angle_x=x;
    Observer_angle_y=y;
    alfa=0;
    beta=0;
}

void _camara::setDistancia(GLfloat d){
	Observer_distance=d;
}

void _camara::setX(GLfloat x){
	Observer_angle_x=x;
}

void _camara::setY(GLfloat y){
	Observer_angle_y=y;
}

GLfloat _camara::getDistancia(){
	return Observer_distance;
}

GLfloat _camara::getX(){
	return Observer_angle_x;
}

GLfloat _camara::getY(){
	return Observer_angle_y;
}

void _camara::seteye(_vertex3f x){
	eye=x;
}

void _camara::setcenter(_vertex3f x){
	center=x;
}

void _camara::setup(_vertex3f x){
	up=x;
}

_vertex3f _camara::geteye(){
	return eye;
}

_vertex3f _camara::getcenter(){
	return center;
}

_vertex3f _camara::getup(){
	return up;
}

void _camara::setalfa(float x){
	alfa=x;
}

void _camara::setbeta(float x){
	beta=x;
}

float _camara::getalfa(){
	return alfa;
}

float _camara::getbeta(){
	return beta;
}
