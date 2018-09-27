//**************************************************************************
// Práctica 1 usando objetos
//**************************************************************************

#include <GL/glut.h>
#include <ctype.h>
#include <math.h>
#include <vector>
#include "objetos.h"


using namespace std;


// variables que definen la posicion de la camara en coordenadas polares
GLfloat Observer_distance;
GLfloat Observer_angle_x;
GLfloat Observer_angle_y;

// variables que controlan la ventana y la transformacion de perspectiva
GLfloat Size_x,Size_y,Front_plane,Back_plane;

// variables que determninan la posicion y tamaño de la ventana X
int Window_x=50,Window_y=50,Window_width=450,Window_high=450;

// objetos
/*----------------Variables practica1------------------------------*/
_cubo cubo;
_piramide tetraedro;

/*---------------------Variables practica2---------------------------------*/
_modeloply ply(10);
_modeloply ply3(true, 4);
_modeloply ply1(true);

// Variable global para controlar el tipo de PLY a usar (leer ply completo, ply con revolución o parte opcional de la practica 2)
char tecla_ply=' ';
/*-----------------------Variables practica3-----------------------------------*/
_grua grua;

int al=10, an=6;
float alfa=0;
float beta=0;
float gama=0;
float gama2=al-1.5;

float velocidad1=0, velocidad2=0, velocidad3=0;
bool tope_carro1=true, tope_carro2=false;
bool tope_gancho1=true, tope_gancho2=false;
/*-------------------------------------------------------------------*/

char practica;
// Variable que controla visualizar el cubo o el tetraedro, si true->cubo si false->tetraedro
bool objeto;
// Variable global que almacena la tecla pulsada para poder pintar los distintos modelos
char tecla_pulsada=' ';

//**************************************************************************
//
//***************************************************************************

void clean_window()
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

// formato(x_minimo,x_maximo, y_minimo, y_maximo,plano_delantero, plano_traser)
//  plano_delantero>0  plano_trasero>PlanoDelantero)
glFrustum(-Size_x,Size_x,-Size_y,Size_y,Front_plane,Back_plane);
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
	
glDisable(GL_LIGHTING);
glLineWidth(2);
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
// Evaluando el modelo elegido (cubo o tetraedro) mediante la variable modelo podemos 
// aprovechar la misma tecla para los distintos escenarios
void draw_objects()
{
	if(practica=='1'){
		if(objeto){
			switch(tecla_pulsada){
				case 'P': cubo.draw_puntos(0,0,0,10); break;
				case 'L': cubo.draw_aristas(0,0,0,10); break;
				case 'S': cubo.draw_solido(1,0.83,0); break;
				case 'A': cubo.draw_solido_ajedrez(0,0,0,1,0.97,0.93); break;
			}
		}
		else {
			switch(tecla_pulsada){
				case 'P': tetraedro.draw_puntos(0,0,0,10); break;
				case 'L': tetraedro.draw_aristas(0,0,0,10); break;
				case 'S': tetraedro.draw_solido(1,0.83,0); break;
				case 'A': tetraedro.draw_solido_ajedrez(0,0,0,0.5,0.5,0.5); break;
			}
		}
	}
	if(practica=='2'){
		if(tecla_ply=='N'){
			switch(tecla_pulsada){
				case 'P': ply.draw_puntos(0,0,0,10); break;
				case 'L': ply.draw_aristas(0,0,0,10); break;
				case 'S': ply.draw_solido(1,0.83,0); break;
				case 'A': ply.draw_solido_ajedrez(0,0,0,0.5,0.5,0.5); break;
			}
		}
		else if(tecla_ply=='O'){
			switch(tecla_pulsada){
				case 'P': ply3.draw_puntos(0,0,0,10); break;
				case 'L': ply3.draw_aristas(0,0,0,10); break;
				case 'S': ply3.draw_solido(1,0.83,0); break;
				case 'A': ply3.draw_solido_ajedrez(0,0,0,0.5,0.5,0.5); break;
			}
		}
		else if(tecla_ply=='I'){
			switch(tecla_pulsada){
				case 'P': ply1.draw_puntos(0,0,0,10); break;
				case 'L': ply1.draw_aristas(0,0,0,10); break;
				case 'S': ply1.draw_solido(1,0.83,0); break;
				case 'A': ply1.draw_solido_ajedrez(0,0,0,0.5,0.5,0.5); break;
			}
		}
	}
	if(practica=='3'){
		grua.draw(alfa,beta,gama,al, an);
	}
}


//**************************************************************************
//
//***************************************************************************

void draw(void)
{
clean_window();
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
float Aspect_ratio;

Aspect_ratio=(float) Alto1/(float )Ancho1;
Size_y=Size_x*Aspect_ratio;
change_projection();
glViewport(0,0,Ancho1,Alto1);
glutPostRedisplay();
}


//***************************************************************************
// Funcion llamada cuando se aprieta una tecla normal
//
// el evento manda a la funcion:
// codigo de la tecla
// posicion x del raton
// posicion y del raton
//***************************************************************************

void normal_key(unsigned char Tecla1,int x,int y)
{

switch(toupper(Tecla1)){
	case '1': practica='1'; break;
	case '2': practica='2'; break;
	case '3': practica='3'; break;
	case 'T': objeto=false; break;
	case 'C': objeto=true; break;
	case 'P': tecla_pulsada='P';
			  velocidad1=0;
			  velocidad2=0;
			  velocidad3=0; break;
	case 'Q': exit(0); break;
	case 'L': tecla_pulsada='L'; break;
	case 'S': tecla_pulsada='S'; break;
	case 'A': tecla_pulsada='A'; break;
	case 'O': tecla_ply='O'; break;
	case 'I': tecla_ply='I'; break;
	case 'N': tecla_ply='N'; break;
}

switch((Tecla1)){
	case 'Z': alfa+=10; break;
	case 'z': alfa-=10; break;
	case 'x': if(beta<an-1){
					beta+=0.1;
				} break;
	case 'X': if(beta>0.1){
					beta-=0.1;
				} break;
	case 'C': if(gama>0.1){
				gama-=0.1;
				} break;
	case 'c': if(gama<al-1.5){
				gama+=0.1;
				} break;
	case 'b': if(velocidad1<2){
				velocidad1+=0.01;
				} break;
	case 'B': if(velocidad1>-2){
				velocidad1-=0.01;
				} break;
	case 'n': if(velocidad2<0.1){
				velocidad2+=0.01;
				} break;
	case 'N': if(velocidad2>-0.1){
				velocidad2-=0.01;
				} break;
	case 'M': if(velocidad3<0.1){
				velocidad3+=0.01;
				} break;
	case 'm': if(velocidad3>-0.1){
				velocidad3-=0.01;
				} break;

}
glutPostRedisplay();
}

//***************************************************************************
// Funcion llamada cuando se aprieta una tecla especial
//
// el evento manda a la funcion:
// codigo de la tecla
// posicion x del raton
// posicion y del raton

//***************************************************************************

void special_key(int Tecla1,int x,int y)
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
Size_x=0.5;
Size_y=0.5;
Front_plane=1;
Back_plane=1000;

// se incia la posicion del observador, en el eje z
Observer_distance=4*Front_plane;
Observer_angle_x=0;
Observer_angle_y=0;

// se indica cual sera el color para limpiar la ventana	(r,v,a,al)
// blanco=(1,1,1,1) rojo=(1,0,0,1), ...
glClearColor(1,1,1,1);

// se habilita el z-bufer
glEnable(GL_DEPTH_TEST);
change_projection();
glViewport(0,0,Window_width,Window_high);

}

//***************************************************************************
// Funcion idle
//***************************************************************************
void idle(){
	alfa+=velocidad1;
	if(velocidad2!=0){
		if(beta<0.1 && tope_carro1){
			tope_carro1=true;
			tope_carro2=false;
			if(velocidad2<0){
				velocidad2=velocidad2*(-1);
			}
		}
		if(beta<an-1 && !tope_carro2){
			beta+=velocidad2;
		}
		if(beta>=an-1){
			tope_carro2=true;
			tope_carro1=false;
		}

		if(tope_carro2 && !tope_carro1){
			if(beta<0.1){
				tope_carro1=true;
				tope_carro2=false;
			}
			beta-=velocidad2;
		}
	}
	
	if(velocidad3!=0){
		if(gama>=al-1.5){
			tope_gancho1=true;
			tope_gancho2=false;
			gama+=velocidad3;
		}
		
		if(tope_gancho1 && !tope_gancho2 && gama<al-1.5){
			if(gama<0.4){
				tope_gancho2=true;
				tope_gancho1=false;
			}
			gama+=velocidad3;
		}
		if(!tope_gancho1 && tope_gancho2){
			gama-=velocidad3;
		}

		
	}
	glutPostRedisplay();
}
//***************************************************************************
// Programa principal
//
// Se encarga de iniciar la ventana, asignar las funciones e comenzar el
// bucle de eventos
//***************************************************************************

int main(int argc, char **argv)
{

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
glutInitWindowPosition(Window_x,Window_y);

// tamaño de la ventana (ancho y alto)
glutInitWindowSize(Window_width,Window_high);

// llamada para crear la ventana, indicando el titulo (no se visualiza hasta que se llama
// al bucle de eventos)
glutCreateWindow("PRACTICA 3");

// asignación de la funcion llamada "dibujar" al evento de dibujo
glutDisplayFunc(draw);
// asignación de la funcion llamada "change_window_size" al evento correspondiente
glutReshapeFunc(change_window_size);
// asignación de la funcion llamada "normal_key" al evento correspondiente
glutKeyboardFunc(normal_key);
// asignación de la funcion llamada "tecla_Especial" al evento correspondiente
glutSpecialFunc(special_key);
// asignación de velocidades a los puntos de libertad
glutIdleFunc(idle);

// funcion de inicialización
initialize();

// inicio del bucle de eventos
glutMainLoop();
return 0;
}
