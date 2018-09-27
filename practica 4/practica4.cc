//**************************************************************************
// Práctica 4
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
_modeloply ply1((char*) "./beethoven.ply");

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
/*----------------------Variables practica4-------------------------*/
_modeloply peon1(10,(char*) "./perfil.ply", false);
_modeloply peon2(10,(char*) "./perfil.ply", false);
_modeloply peon3(10,(char*) "./perfil.ply", false);
_modeloply lata(10,(char*) "./lata-pcue.ply",true);
_modeloply lata_superior(10,(char*) "./lata-psup.ply",true);
_modeloply lata_inferior(10,(char*) "./lata-pinf.ply",true);

//luzq

GLfloat ambiental[]={0.3,0.3,0.3,0.3};
GLfloat difusa[]={1.0,1.0,1.0,1.0};

// Material negro
//GLfloat mambiental[]={0.01,0.01,0.01,1.0};
//GLfloat mdifusa[]={0.01,0.01,0.01,1.0};
//GLfloat mespecular[]={0.4,0.4,0.4,1.0};

//Peon Verde
GLfloat mambiental[]={0.2,1.0,0.2,1.0};
GLfloat mdifusa[]={0.4,1.0,0.4,1.0};
GLfloat mespecular[]={0.2,1.2,0.2,1.0};

//Material blanco
GLfloat m1ambiental[]={0.25,0.20725,0.20725,0.922};
GLfloat m1difusa[]={1.0,0.829,0.829,0.922};
GLfloat m1especular[]={0.296648,0.296648,0.296648,0.922};

//Material plata
GLfloat m2ambiental[]={0.20,0.20,0.20,1.0};
GLfloat m2difusa[]={0.51,0.51,0.51,1.0};
GLfloat m2especular[]={0.51,0.51,0.51,1.0};

//Material para texturas
GLfloat m3ambiental[]={0.24725,0.1995,0.0745,1.0};
GLfloat m3difusa[]={0.75164,0.60648,0.22648,1.0};
GLfloat m3especular[]={0.628281,0.555802,0.366065,1.0};

_fuenteLuz luz1(GL_LIGHT0);
char tecla_luz=' ';

_fuenteLuz luz2(GL_LIGHT1);
float angulo_alfa=0.0;
float angulo_beta=0.0;
GLfloat pos_luz[]={0,0,0,0};
float angulo=3.0;

_fuenteLuz luz3(GL_LIGHT2);
GLfloat luz_defensa1[]={1,0,1,0};
GLfloat luz_defensa2[]={1,0,1,0};
GLfloat luz_defensa3[]={1,0,1,0};
_textura cocacola((char *) "text-lata-1.jpg");
//peon2.calcularCoordenadas();
_textura madera((char*) "./text-madera.jpg");
//lata.setMaterial(_vertex4f(0.3,0.3,0.3,1),_vertex4f(0.8,0.8,0.8,1),_vertex4f(1,1,1,1),80);
//peon1.setMaterial(_vertex4f(0.3,0.3,0.3,1),_vertex4f(0.8,0.8,0.8,1),_vertex4f(1,1,1,1),80);
//peon2.setMaterial(_vertex4f(0.02,0.02,0.02,1),_vertex4f(0.01,0.01,0.01,1),_vertex4f(0.4,0.4,0.4,1),10);


/*-----------------------------------------------------------------*/
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
glClearDepth(1.0);
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
	if(practica=='4'){
		luz1.activar();
		luz3.setposicion(angulo_alfa,angulo_beta,angulo);
		if(tecla_luz=='l'){
			luz1.desactivar();
			luz3.setambiental(luz_defensa1);
			luz3.setdifusa(luz_defensa2);
			luz3.setespecular(luz_defensa3);
			luz3.setposicion(angulo_alfa,angulo_beta,angulo);
			luz3.activar();
			//luz2.activar();
			//luz2.setposicion(angulo_alfa,angulo_beta,angulo);
		}
		if(tecla_luz=='L'){
			luz3.desactivar();
			luz1.activar();
		}
		glPushMatrix();
			glTranslatef(0,1.2,0);
			glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT,m1ambiental);
			glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,m1especular);
			glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE,m1difusa);
			glMaterialf(GL_FRONT_AND_BACK,GL_SHININESS,11.264);
			peon2.draw_suavizado_gouroud();
		glPopMatrix();
		glPushMatrix();
			glTranslatef(+2.5,1.2,0);
			glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT,mambiental);
			glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,mespecular);
			glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE,mdifusa);
			glMaterialf(GL_FRONT_AND_BACK,GL_SHININESS,10);
			peon3.draw_suavizado_gouroud();
		glPopMatrix();
		glPushMatrix();
			glTranslatef(0,0,-2.5);
			glScalef(4,4,4);
			glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT,m2ambiental);
			glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,m2especular);
			glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE,m2difusa);
			glMaterialf(GL_FRONT_AND_BACK,GL_SHININESS,0.40);
			lata_inferior.draw_suavizado_gouroud();
			lata_superior.draw_suavizado_gouroud();
			glPushMatrix();
				luz1.desactivar();
				/*glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT,m3ambiental);
				glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,m3especular);
				glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE,m3difusa);
				glMaterialf(GL_FRONT_AND_BACK,GL_SHININESS,12);*/
				cocacola.activar();
				lata.draw_textura(1.0,1.0,1.0);	
				cocacola.desactivar();
				glPopMatrix();
		glPopMatrix();
		glPushMatrix();
			glTranslatef(-2.5,1.2,0);
			glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT,m3ambiental);
			glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,m3especular);
			glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE,m3difusa);
			glMaterialf(GL_FRONT_AND_BACK,GL_SHININESS,51.2);
			madera.automatica();
			//cocacola.automatica();
			peon1.draw_suavizado_gouroud();
			//cocacola.desactivar_auto();
			madera.desactivar_auto();
			//cocacola.activar();
		glPopMatrix();
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
	case '4': practica='4'; break;
	case 'T': objeto=false; break;
	case 'C': objeto=true; tecla_luz='C'; break;
	case 'P': tecla_pulsada='P';
			  velocidad1=0;
			  velocidad2=0;
			  velocidad3=0; break;
	case 'Q': exit(0); break;
	case 'L': tecla_pulsada='L'; break;
	case 'S': tecla_pulsada='S'; break;
	case 'A': tecla_pulsada='A'; tecla_luz='A'; break;
	case 'O': tecla_ply='O'; break;
	case 'I': tecla_ply='I'; break;
	case 'N': tecla_ply='N'; break;
	case 'Z': tecla_luz='Z'; break;
	case 'X': tecla_luz='X'; break;
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
	case 'L': tecla_luz='L'; break;
	case 'l': tecla_luz='l'; break;

}
	switch(tecla_luz){
		case 'A': if(angulo_beta>=0 && angulo_beta<355){
					angulo_beta+=5;
					}	break;
		case 'C': if(angulo_alfa>=5){
					angulo_alfa-=5;
					}
		case 'Z': if(angulo_beta>=5){
					angulo_beta-=5;
					}	break;
		case 'X': if(angulo_alfa>=0 && angulo_alfa<355){
					angulo_alfa+=5;
					}	break;
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

peon1.TieneTextura();
lata.TieneTextura();
luz1.setambiental(ambiental);
luz2.setdifusa(difusa);

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
glutCreateWindow("PRACTICA 4");

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
glCullFace(GL_BACK);
glEnable(GL_CULL_FACE);
// funcion de inicialización
initialize();

// inicio del bucle de eventos
glutMainLoop();

return 0;
}
