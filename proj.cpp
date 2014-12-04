/**
    Curso Computación Gráfica 20142
    Código Base para Laboratorio 3
    10 Nov 2014
*/

#include <stdio.h>
#include <math.h>
#include <GL/glut.h>
#define GL_PI 3.1416f
#define  BLANCO   0
#define  AZUL     1
#define  NARANJA  2
#define  ROJO     3
#define  AMARILLO 4
#define  VERDE    5
#define  NEGRO    6

#define  MODO_ROTACION	1
#define  MODO_JUEGO	2
#define  MODO_STANDBY	3

//static float width, height;
// ventana
static int ventanaX=500;
static int ventanaY=500;

// Ángulos de rotación de vista
float angX = -22.0, angY = 134.0, angZ = 0.0;

// numero de cubos
int numCubos = 8;
float ladoCubo = 2.0;
// estructura para inicializar las posiciones 
// y los colores de las caras de los cubos

typedef struct{
	float x, y, z;
//	giroX, giroY, giroZ
	float alfaX, alfaY, alfaZ;
	float AntX, AntY, AntZ;
	int colores[6];
}cubo;
cubo* modelo;

// ENFOCADO
float enfocar = 1.0;


// MODO DEL PROGRAMA
int modo = 0;


void generarDatosCubo();
void dibujaCubo(int i);
void ponColor(int color);

// vision
void reshape(int w, int h);

void init(void)
{
    glClearColor(0.0,0.0,0.0,0.0);
    glShadeModel(GL_FLAT);
}

void escena(void)
{
	GLfloat angulo, radio = 8.0f, x, y;
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	
	glScalef(enfocar,enfocar,enfocar);
	glRotatef(angX,1.0,0.0,0.0);
	glRotatef(angY,0.0,1.0,0.0);
	glRotatef(angZ,0.0,0.0,1.0);

	glLineWidth(1);

	for(int i=0; i<numCubos; i++){
	glPushMatrix();
		glTranslatef(modelo[i].x , modelo[i].y , modelo[i].z);
		glRotatef(modelo[i].alfaX, 1.0, 0.0, 0.0);
		glRotatef(modelo[i].alfaY, 0.0, 1.0, 0.0);
		glRotatef(modelo[i].alfaZ, 0.0, 0.0, 1.0);
		dibujaCubo(i);
	glPopMatrix();
	}
	
	glutSwapBuffers();
	glFlush();
//	glDisable(GL_DEPTH_TEST);
}

void generarDatosCubo(){
	int i,j;
	int x,y,z;
	modelo = (cubo*) malloc(numCubos*sizeof(cubo));

// todas las caras negras primero
	for (i = 0; i < numCubos; i++)
	for (j = 0; j < 6; j++)
	modelo[i].colores[j] = NEGRO;

// cambiamos los colores y escribimos las posiciones
	for (i = 0; i < numCubos; i++)
	{
		modelo[i].AntX = modelo[i].x = ladoCubo*(i % 2);
		modelo[i].AntY = modelo[i].y = ladoCubo*(i / (2*2));
		modelo[i].AntZ = modelo[i].z = ladoCubo*((i / 2) % 2);

		modelo[i].alfaX = 0;
		modelo[i].alfaY = 0;
		modelo[i].alfaZ = 0;

		modelo[i].colores[0] = (i > 3) ? VERDE : NEGRO;
		modelo[i].colores[1] = (((i / 2) % 2) == 1) ? ROJO : NEGRO;
		modelo[i].colores[2] = ((i % 2) == 1) ? AMARILLO : NEGRO;
		modelo[i].colores[3] = (((i / 2) % 2) == 0) ? NARANJA : NEGRO;
		modelo[i].colores[4] = ((i % 2) == 0) ? BLANCO : NEGRO;
		modelo[i].colores[5] = (i < 4) ? AZUL : NEGRO;
   }

}

void dibujaCubo(int i){
	glPushMatrix();
	glBegin(GL_QUADS);
	ponColor(modelo[i].colores[0]);
      glVertex3f(0, ladoCubo, 0);
      glVertex3f(0, ladoCubo, ladoCubo);
      glVertex3f(ladoCubo, ladoCubo, ladoCubo);
      glVertex3f(ladoCubo, ladoCubo, 0);

      ponColor(modelo[i].colores[1]);
      glVertex3f(0, ladoCubo, ladoCubo);
      glVertex3f(0, 0, ladoCubo);
      glVertex3f(ladoCubo, 0, ladoCubo);
      glVertex3f(ladoCubo, ladoCubo, ladoCubo);

      ponColor(modelo[i].colores[2]);
      glVertex3f(ladoCubo, ladoCubo, ladoCubo);
      glVertex3f(ladoCubo, 0, ladoCubo);
      glVertex3f(ladoCubo, 0, 0);
      glVertex3f(ladoCubo, ladoCubo, 0);

      ponColor(modelo[i].colores[3]);
      glVertex3f(0, ladoCubo, 0);
      glVertex3f(0, 0, 0);
      glVertex3f(ladoCubo, 0, 0);
      glVertex3f(ladoCubo, ladoCubo, 0);

      ponColor(modelo[i].colores[4]);
      glVertex3f(0, ladoCubo, ladoCubo);
      glVertex3f(0, 0, ladoCubo);
      glVertex3f(0, 0, 0);
      glVertex3f(0, ladoCubo, 0);

      ponColor(modelo[i].colores[5]);
      glVertex3f(0, 0, 0);
      glVertex3f(0, 0, ladoCubo);
      glVertex3f(ladoCubo, 0, ladoCubo);
      glVertex3f(ladoCubo, 0, 0);

   glEnd();

   glLineWidth(3);
   glColor3f(0.0, 0.0, 0.0);

   glBegin(GL_LINE_LOOP);
      glVertex3f(0.0, 0.0, 0.0);
      glVertex3f(0.0, 0.0, ladoCubo);
      glVertex3f(ladoCubo, 0.0, ladoCubo);
      glVertex3f(ladoCubo, 0.0, 0.0);
   glEnd();

   glBegin(GL_LINE_LOOP);
      glVertex3f(0, ladoCubo, 0);
      glVertex3f(0, ladoCubo, ladoCubo);
      glVertex3f(ladoCubo, ladoCubo, ladoCubo);
      glVertex3f(ladoCubo, ladoCubo, 0);
   glEnd();

   glBegin(GL_LINES);
      glVertex3f(0, 0, 0);
      glVertex3f(0, ladoCubo, 0);

      glVertex3f(ladoCubo, 0, 0);
      glVertex3f(ladoCubo, ladoCubo, 0);

      glVertex3f(ladoCubo, 0, ladoCubo);
      glVertex3f(ladoCubo, ladoCubo, ladoCubo);

      glVertex3f(0, 0, ladoCubo);
      glVertex3f(0, ladoCubo, ladoCubo);
   glEnd();

   glPopMatrix();
   glFlush();
}

void ponColor (int color) {
   switch(color) {
      case  BLANCO:     glColor3f(1.0, 1.0, 1.0);
                        break;

      case  AZUL:       glColor3f(0.0, 0.0, 1.0);
                        break;

      case  NARANJA:    glColor3f(1.0, 0.5, 0.2);
                        break;

      case  ROJO:       glColor3f(1.0, 0.0, 0.0);
                        break;

      case  AMARILLO:   glColor3f(1.0, 1.0, 0.0);
                        break;

      case  VERDE:      glColor3f(0.0, 1.0, 0.0);
                        break;

      case  NEGRO:      glColor3f(0.2, 0.2, 0.2);
                        break;
   }
}

void transformar (){
	if(modo==MODO_STANDBY)	angY+=0.7;
	escena();
}

void tecladoS(int tecla, int x, int y)
{
    if(tecla == GLUT_KEY_UP && modo==MODO_ROTACION){
		enfocar+=0.02;
//printf("%.2f\n",angX);
		reshape(ventanaX, ventanaY);
		escena();
	}

    if(tecla == GLUT_KEY_DOWN && modo==MODO_ROTACION){
		enfocar-=0.02;
//printf("%.2f\n",angX);
		reshape(ventanaX, ventanaY);
		escena();
	}

	if(tecla == GLUT_KEY_LEFT){
		angY+=2.0;
//printf("%.2f\n",angY);
		escena();	
	}

	if(tecla == GLUT_KEY_RIGHT){
		angY-=2.0;
//printf("%.2f\n",angY);
		escena();
	}

}

void teclado(unsigned char tecla, int x,int y)
{
    switch(tecla){
        case 27:
        {
            exit(0) ;
            break;
        }
    }
}

void mouse(int boton,int estado,int x,int y )
{
 /*    if (boton==GLUT_LEFT_BUTTON && estado==GLUT_DOWN && modo==MODO_JUEGO ) {
	enfocar+=0.2;
	escena();
     }
     if (boton==GLUT_RIGHT_BUTTON && estado==GLUT_DOWN && modo==MODO_JUEGO) {
	enfocar-=0.2;
	escena();
     }*/
}

void reshape(int w, int h)
{
   GLfloat size = 10.0f, redimension =(GLfloat)w / (GLfloat)h;
   glViewport(0,0,(GLsizei)w, (GLsizei)h);
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
//glFrustum(-5, 5, -5, 5, 5, 1000);
    if (w <= h)
        glOrtho (-size, size, -size / redimension, size/ redimension, 10.0f*enfocar, -7.00f*enfocar);
    else
        glOrtho (-size* redimension, size* redimension, -size, size, 7.0f*enfocar, -7.0f*enfocar);

	glMatrixMode(GL_MODELVIEW);
}

void principal(int value){
	switch(value){
		case 1 :
		{
			modo=MODO_ROTACION;
			break;
		}
		case 2 :
                {
                        modo=MODO_JUEGO;
                        break;
                }
		case 3 :
                {
                        modo=MODO_STANDBY;
                        break;
                }
	}
}

int main(int argc, char** argv)
{
	generarDatosCubo();
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(ventanaX,ventanaY);
    glutInitWindowPosition(100,100);
    glutCreateWindow("Proyecto");

    init();
    glutIdleFunc(transformar);
    glutDisplayFunc(escena);
    glutReshapeFunc(reshape);
    glutMouseFunc(mouse);
    glutSpecialFunc(tecladoS);
    glutKeyboardFunc(teclado);

	glutCreateMenu(principal);
	glutAddMenuEntry("Modo Rotacion",1);
	glutAddMenuEntry("Modo Juego",2);
	glutAddMenuEntry("Modo Stand By",3);
	
	glutAttachMenu(GLUT_RIGHT_BUTTON);

    glutMainLoop();
    return 0;
}



