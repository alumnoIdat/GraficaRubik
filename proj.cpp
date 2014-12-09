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

#define  MOV_EJEX	1
#define  MOV_EJEY	2
#define  MOV_EJEZ	3

#define	HORARIO		-1
#define ANTIHORARIO	1
//static float width, height;
// ventana
static int ventanaX=500;
static int ventanaY=500;

// Ángulos de rotación de vista
//float angX = -22.0, angY = 134.0, angZ = 0.0;
float angX = 0.0, angY = 0.0, angZ = 0.0;

// numero de cubos
int numCubos = 8;
float ladoCubo = 2.0;

// rubik logico
int rubikLogico[2][2][2];

bool ratonPresionado = false;

int seleccionado = -2;
int direccion = 0;
int sentido = 0;

float antX, antY, antZ;
int giroAntX, giroAntY, giroAntZ;

// estructura para inicializar las posiciones 
// y los colores de las caras de los cubos

typedef struct{
	float x, y, z;
	int alfaX, alfaY, alfaZ;
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
	glEnable(GL_DEPTH_TEST);
	glClearColor(0.0,0.0,0.0,0.0);
	glShadeModel(GL_FLAT);
}

void escena(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//	glEnable(GL_DEPTH_TEST);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	
	glScalef(enfocar,enfocar,enfocar);
	glRotatef(angX,1.0,0.0,0.0);
	glRotatef(angY,0.0,1.0,0.0);
	glRotatef(angZ,0.0,0.0,1.0);

	glLineWidth(1);
	
	for(int i=0; i<numCubos; i++){
	glLoadName(i);
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
/*	for (i = 0; i < numCubos; i++)
	for (j = 0; j < 6; j++)
	modelo[i].colores[j] = NEGRO;
*/
// cambiamos los colores y escribimos las posiciones
	for (i = 0; i < numCubos; i++)
	{
		modelo[i].AntX = modelo[i].x = ladoCubo*(i % 2);
		modelo[i].AntY = modelo[i].y = ladoCubo*(i/(2*2));
		modelo[i].AntZ = modelo[i].z = ladoCubo*((i/2)%2);

		modelo[i].alfaX = 0;
		modelo[i].alfaY = 0;
		modelo[i].alfaZ = 0;

		modelo[i].colores[0] = (i > 3) ? VERDE : NEGRO;
		modelo[i].colores[1] = (((i / 2) % 2) == 1) ? ROJO : NEGRO;
		modelo[i].colores[2] = ((i % 2) == 1) ? AMARILLO : NEGRO;
		modelo[i].colores[3] = (((i / 2) % 2) == 0) ? NARANJA : NEGRO;
		modelo[i].colores[4] = ((i % 2) == 0) ? BLANCO : NEGRO;
		modelo[i].colores[5] = (i < 4) ? AZUL : NEGRO;
		
		rubikLogico[i%2][i/(2*2)][(i/2)%2]=i;
	}

}

bool verificar_solucion(){
		if((rubikLogico[0][0][0]+rubikLogico[1][1][1])!=7 || (rubikLogico[1][0][0]+rubikLogico[0][1][1])!=7)	return false;
		if(abs(rubikLogico[0][0][0]-rubikLogico[1][0][0])*abs(rubikLogico[0][0][0]-rubikLogico[0][0][1])*abs(rubikLogico[0][0][0]-rubikLogico[0][1][0]) != 8)	return false;
	return true;
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

int cuboElejido(int x, int y){
	GLuint buffer[256];
	GLint sel;
	GLint viewport[4];

	glSelectBuffer (256, buffer);
	glRenderMode (GL_SELECT);
	glInitNames();
	glPushName(-1);

	glMatrixMode(GL_PROJECTION);
	glPushMatrix();

	glLoadIdentity();
	glGetIntegerv (GL_VIEWPORT, viewport);
	gluPickMatrix (x, viewport[3] - y, 5, 5, viewport);
	
	escena();
	
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	
	sel = glRenderMode (GL_RENDER);
	
	printf("hits %d\n",sel);
	
	GLuint* ptr = (GLuint *) buffer;
	GLuint  minZ = 0xffffffff;
	int nombre, n_nombres;
	
	for (int i = 0; i < sel; i++) {
		n_nombres = *ptr;
		ptr++;
		if ((*ptr) < minZ) {
			minZ = *ptr;
			nombre = *(ptr+2);
		}
		ptr += (n_nombres+2);
	}
	
	printf("cubo %d\n",nombre);
	
	if (sel > 0)	return nombre;
	else return (-1);
}

void coordenadaCubo (int * a, int * b, int * c) {
	for (int i = 0; i < 2; i++)
	for (int j = 0; j < 2; j++)
	for (int k = 0; k < 2; k++)
		if (rubikLogico[i][j][k] == seleccionado){
			*a = i;
			*b = j;
			*c = k;
	}
}

void giraCubo (int cuboAux, int ang){
	float auxH, auxV;
	
	switch (direccion) {
		case MOV_EJEX:
			auxH=modelo[cuboAux].y;
			auxV=modelo[cuboAux].z;
			modelo[cuboAux].y = (auxH - 2*ladoCubo/2.0)*cos(ang*GL_PI/180.0) - (auxV - 2*ladoCubo/2.0)*sin(ang*GL_PI/180.0) + 2*ladoCubo/2.0;
			modelo[cuboAux].z = (auxH - 2*ladoCubo/2.0)*sin(ang*GL_PI/180.0) + (auxV - 2*ladoCubo/2.0)*cos(ang*GL_PI/180.0) + 2*ladoCubo/2.0;
		break;
		case MOV_EJEY:
			auxH=modelo[cuboAux].z;
			auxV=modelo[cuboAux].x;
			modelo[cuboAux].z = (auxH - 2*ladoCubo/2.0)*cos(ang*GL_PI/180.0) - (auxV - 2*ladoCubo/2.0)*sin(ang*GL_PI/180.0) + 2*ladoCubo/2.0;
			modelo[cuboAux].x = (auxH - 2*ladoCubo/2.0)*sin(ang*GL_PI/180.0) + (auxV - 2*ladoCubo/2.0)*cos(ang*GL_PI/180.0) + 2*ladoCubo/2.0;
		break;
		case MOV_EJEZ:
			auxH=modelo[cuboAux].x;
			auxV=modelo[cuboAux].y;
			modelo[cuboAux].x = (auxH - 2*ladoCubo/2.0)*cos(ang*GL_PI/180.0) - (auxV - 2*ladoCubo/2.0)*sin(ang*GL_PI/180.0) + 2*ladoCubo/2.0;
			modelo[cuboAux].y = (auxH - 2*ladoCubo/2.0)*sin(ang*GL_PI/180.0) + (auxV - 2*ladoCubo/2.0)*cos(ang*GL_PI/180.0) + 2*ladoCubo/2.0;
		break;
	}
}

void animacionCubo(){
	int x, y, z;
	int auxCubo;
	int i,j;
//printf("animacion\n");
	coordenadaCubo(&x, &y, &z);
	switch (direccion) {
		case MOV_EJEX:
			for (i = 0; i < 2; i++)
				for (j = 0; j < 2; j++){
					auxCubo = rubikLogico[x][i][j];
					giraCubo (auxCubo, sentido*3);
					modelo[auxCubo].alfaX += sentido*3;
				}
		break;
		case MOV_EJEY:
			for (i = 0; i < 2; i++)
				for (j = 0; j < 2; j++){
					auxCubo = rubikLogico[i][y][j];
					giraCubo (auxCubo, sentido*3);
					modelo[auxCubo].alfaY += sentido*3;
				}
		break;
		case MOV_EJEZ:
			for (i = 0; i < 2; i++)
				for (j = 0; j < 2; j++){
					auxCubo = rubikLogico[i][j][z];
					giraCubo (auxCubo, sentido*3);
					modelo[auxCubo].alfaZ += sentido*3;
				}
		break;
	}
}

int giros(){
	int giros, dif;
	
	switch (direccion) {
		case MOV_EJEX:
			while (modelo[seleccionado].alfaX < 0) modelo[seleccionado].alfaX += 360;
			dif = modelo[seleccionado].alfaX - giroAntX;
			if (dif < 0) dif += 360;
			giros = (dif + 45)/90;
		break;
		
		case MOV_EJEY:
			while (modelo[seleccionado].alfaY < 0) modelo[seleccionado].alfaY += 360;
			dif = modelo[seleccionado].alfaY - giroAntY;
			if (dif < 0) dif += 360;
			giros = (dif + 45)/90;
		break;
			
		case MOV_EJEZ:
			while (modelo[seleccionado].alfaY < 0) modelo[seleccionado].alfaZ += 360;
			dif = modelo[seleccionado].alfaZ - giroAntZ;
			if (dif < 0) dif += 360;
			giros = (dif + 45)/90;
		break;
	}
	
	return giros;
}

void soltarRubik(){
	int x, y, z;
	int i, j;
	int posAux[4];
	int dif;
	int numRot, cuboAux;

	switch (direccion) {
		case MOV_EJEX:
			numRot = giros();
			coordenadaCubo(&x, &y, &z);
			for (i = 0; i < 2; i++)	for (j = 0; j < 2; j++){
				cuboAux = rubikLogico[x][i][j];
				modelo[cuboAux].y = modelo[cuboAux].AntY;
				modelo[cuboAux].z = modelo[cuboAux].AntZ;
				giraCubo(cuboAux, (numRot*90));
				modelo[cuboAux].AntY = modelo[cuboAux].y;
				modelo[cuboAux].AntZ = modelo[cuboAux].z;
				modelo[cuboAux].alfaX = (90*numRot+giroAntX) % 360;
			}
			posAux[0]=rubikLogico[x][0][0];
			posAux[1]=rubikLogico[x][1][0];
			posAux[2]=rubikLogico[x][1][1];
			posAux[3]=rubikLogico[x][0][1];
			
			rubikLogico[x][0][0]=posAux[(numRot)%4];
			rubikLogico[x][1][0]=posAux[(numRot+1)%4];
			rubikLogico[x][1][1]=posAux[(numRot+2)%4];
			rubikLogico[x][0][1]=posAux[(numRot+3)%4];
		break;
			
		case MOV_EJEY:
			numRot = giros();
			coordenadaCubo(&x, &y, &z);
			for (i = 0; i < 2; i++)	for (j = 0; j < 2; j++){
				cuboAux = rubikLogico[i][y][j];
				modelo[cuboAux].x = modelo[cuboAux].AntX;
				modelo[cuboAux].z = modelo[cuboAux].AntZ;
				giraCubo(cuboAux, (numRot*90));
				modelo[cuboAux].AntX = modelo[cuboAux].x;
				modelo[cuboAux].AntZ = modelo[cuboAux].z;
				modelo[cuboAux].alfaY = (90*numRot+giroAntY) % 360;
			}
			posAux[0]=rubikLogico[0][y][0];
			posAux[1]=rubikLogico[0][y][1];
			posAux[2]=rubikLogico[1][y][1];
			posAux[3]=rubikLogico[1][y][0];
			
			rubikLogico[0][y][0]=posAux[(numRot)%4];
			rubikLogico[0][y][1]=posAux[(numRot+1)%4];
			rubikLogico[1][y][1]=posAux[(numRot+2)%4];
			rubikLogico[1][y][0]=posAux[(numRot+3)%4];
		break;
			
		case MOV_EJEZ:
			numRot = giros();
			coordenadaCubo(&x, &y, &z);
			for (i = 0; i < 2; i++)	for (j = 0; j < 2; j++){
				cuboAux = rubikLogico[i][j][z];
				modelo[cuboAux].x = modelo[cuboAux].AntX;
				modelo[cuboAux].y = modelo[cuboAux].AntY;
				giraCubo(cuboAux, (numRot*90));
				modelo[cuboAux].AntX = modelo[cuboAux].x;
				modelo[cuboAux].AntY = modelo[cuboAux].y;
				modelo[cuboAux].alfaZ = (90*numRot+giroAntZ) % 360;
			}
			posAux[0]=rubikLogico[0][0][z];
			posAux[1]=rubikLogico[1][0][z];
			posAux[2]=rubikLogico[1][1][z];
			posAux[3]=rubikLogico[0][1][z];
			
			rubikLogico[0][0][z]=posAux[(numRot)%4];
			rubikLogico[1][0][z]=posAux[(numRot+1)%4];
			rubikLogico[1][1][z]=posAux[(numRot+2)%4];
			rubikLogico[0][1][z]=posAux[(numRot+3)%4];
		break;
	}
}

void desordenarRubik(){
	float  aleat = (float)rand()/RAND_MAX;//0y1
	int numero = int(aleat*5);
	int giros;
	
	for(int i=0; i<numero; i++){
		aleat = (float)rand()/RAND_MAX;
		seleccionado = int(aleat*numCubos);
		printf("%d\n",seleccionado);
		aleat = (float)rand()/RAND_MAX;
		giros = int( aleat*4);
		printf("%d\n",giros);
		aleat = (float)rand()/RAND_MAX;
		direccion = int( aleat*3)+1;
		printf("%d\n",direccion);
		aleat = (float)rand()/RAND_MAX;
		sentido = 2*( int( aleat*2))-1;
		printf("%d\n",sentido);
		for(int ang=0; ang<(giros*90);ang=ang+3){
			animacionCubo();
			escena();
		}
		soltarRubik();
		escena();
	}
	seleccionado=-1;
	direccion = 0;
	sentido = 0;
}

void transformar (){
	if(modo==MODO_STANDBY){		angY+=1;
		if(angY > 360)	angY-=360;
		escena();}
}

void tecladoS(int tecla, int x, int y)
{
	if(modo==MODO_ROTACION){
	
		if(tecla == GLUT_KEY_UP ){
			enfocar+=0.02;
	//printf("%.2f\n",angX);
			reshape(ventanaX, ventanaY);
			escena();
		}else if(tecla == GLUT_KEY_DOWN ){
			if(enfocar > 0.02)	enfocar-=0.02;
			else enfocar = 0.01;
	//printf("%.2f\n",angX);
			reshape(ventanaX, ventanaY);
			escena();
		}
	
	}
}

void teclado(unsigned char tecla, int x,int y)
{
	switch(tecla){
		case 27:
			exit(0) ;
			break;
	}
}

void mouse(int boton,int estado,int x,int y )
{
	if(boton == GLUT_LEFT_BUTTON){
		switch (estado) {
			case GLUT_DOWN:
				switch (modo) {
					case MODO_ROTACION:
						ratonPresionado = true;
						antX = x;
						antY = y;
					break;
				
					case MODO_JUEGO:
						seleccionado = cuboElejido(x,y);
						if (seleccionado >= 0){
							ratonPresionado = true;
							antX = x;
							antY = y;
							giroAntX = modelo[seleccionado].alfaX;
							giroAntY = modelo[seleccionado].alfaY;
							giroAntZ = modelo[seleccionado].alfaZ;}
					break;
				}
			break;
			
			case GLUT_UP:
				switch (modo) {
					case MODO_ROTACION:
						ratonPresionado = false;
						direccion = -1;
					break;
				
					case MODO_JUEGO:
						if (seleccionado >= 0){
							soltarRubik();
							ratonPresionado = false;
							if (verificar_solucion())	//cuboResuelto();
							printf("cubo resuelto\n");
						}
						escena();
						direccion = -1;
						sentido = 0;
					break;
				}
			break;
		}
	}
}

void rotarRaton(int x, int y){
	switch (modo) {
		case MODO_ROTACION:
		
			switch (ratonPresionado) {
				case true:
					if(direccion == -1){
						if (abs(x-antX) > abs(y-antY))
						{
							direccion = MOV_EJEY;
						}else{
							direccion = MOV_EJEX;
						}
					}
					
					if (direccion == MOV_EJEY) {
						if (x > antX)	angY +=2;
						else		angY -=2;
//						antX = x;
					}else if (direccion == MOV_EJEX) {
						if (y > antY)	angX +=2;
						else		angX -=2;
					}
					antX = x;
					antY = y;
				break;
				case false:
//					direccion = -1;
				break;
			}
		break;
			
		case MODO_JUEGO:
		
			switch (ratonPresionado) {
				case true:
					if(direccion == -1){
						if (abs(x-antX) > abs(y-antY))
						{
							direccion = MOV_EJEY;
							if (x > antX) sentido = ANTIHORARIO;
							else sentido = HORARIO;
						}else{
							direccion = MOV_EJEX;
							if (y > antY) sentido = HORARIO;
							else sentido = ANTIHORARIO;
						}
					}
					
					animacionCubo();
					
					if (direccion == MOV_EJEY) {
						if (x > antX) sentido = ANTIHORARIO;
						else sentido = HORARIO;
						antX = x;
					}else if (direccion == MOV_EJEX) {
						if (y > antY) sentido = HORARIO;
						else sentido = ANTIHORARIO;
						antY = y;
					}
//					antX = x;
//					antY = y;
				break;
				case false:
//					direccion = -1;
//					sentido = 0;
				break;
			}
		break;
		
	}
	glutPostRedisplay();
}

void reshape(int w, int h)
{
	GLfloat size = 10.0f, redimension =(GLfloat)w / (GLfloat)h;
	glViewport(0,0,(GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if (w <= h)
	glOrtho (-size, size, -size / redimension, size/ redimension, 7.0f*enfocar, -7.0f*enfocar);
	else
	glOrtho (-size* redimension, size* redimension, -size, size, 7.0f*enfocar, -7.0f*enfocar);
//	glMatrixMode(GL_MODELVIEW);
}

void submen(int value){
	switch(value){
		case 1 :
			modo=MODO_JUEGO;
			break;
		case 2 :
			desordenarRubik();
			break;
	}
}

void principal(int value){
	switch(value){
		case 1 :
			modo=MODO_ROTACION;
			break;
/*		case 2 :
			modo=MODO_JUEGO;
			break;*/
		case 3 :
			modo=MODO_STANDBY;
			break;
	}
}

int main(int argc, char** argv){
	generarDatosCubo();
	
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(ventanaX,ventanaY);
	glutInitWindowPosition(200,200);
	glutCreateWindow("Proyecto");
	
	init();
	glutIdleFunc(transformar);
	glutDisplayFunc(escena);
	glutReshapeFunc(reshape);
	glutMouseFunc(mouse);
	glutMotionFunc(rotarRaton);
	glutSpecialFunc(tecladoS);
	glutKeyboardFunc(teclado);
	
	
	int submenu = glutCreateMenu(submen);
	glutAddMenuEntry("Empezar",1);
	glutAddMenuEntry("Desordenar Rubik",2);
	
	glutCreateMenu(principal);
	glutAddMenuEntry("Modo Rotacion",1);
	glutAddSubMenu("Modo Juego",submenu);
	glutAddMenuEntry("Modo Stand By",3);
	
	glutAttachMenu(GLUT_RIGHT_BUTTON);
	
	glutMainLoop();
	return 0;
}
