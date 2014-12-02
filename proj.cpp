/**
    Curso Computación Gráfica 20142
    Código Base para Laboratorio 3
    10 Nov 2014
*/

#include <math.h>
#include <GL/glut.h>
#define GL_PI 3.1416f
//static float width, height;

void init(void)
{
    glClearColor(0.0,0.0,0.0,0.0);
    glShadeModel(GL_FLAT);
}

void escena(void)
{
	GLfloat angulo, radio = 8.0f, x, y;
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);

	glPushMatrix();
	glRotatef(45.0,1.0,0.0,0.0);
//	glRotatef(45.0,0.0,1.0,0.0);
//	glRotatef(45.0,0.0,0.0,1.0);
//	glTranslatef(4.0,4.0,0.0);
	glPushMatrix();
//for(int i=-1;i<=1;i+=2){
//for(int j=-1;j<=1;j+=2){
for(int k=-1;k<=1;k+=2){	
	glPushMatrix();
		glTranslatef(2.0/**i*/,2.0/**j*/,2.0*k);
		glColor3f(/*(float)(i)/2.0+*/0.5,/*(float)(j)/2.0+*/0.5,(float)(k)/2.0+0.5);
		glutSolidCube(4);
	glPopMatrix();
}//}}
	glPopMatrix();
	glPopMatrix();
	
	glDisable(GL_DEPTH_TEST);
	glFlush();
	glutSwapBuffers();
//	glDisable(GL_DEPTH_TEST);
}
void transformar (){
    escena();
}

void tecladoS(int tecla, int x, int y)
{/*
    if(tecla == GLUT_KEY_UP)

    if(tecla == GLUT_KEY_DOWN)

    if(tecla == GLUT_KEY_LEFT)

    if(tecla == GLUT_KEY_RIGHT)//*/

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
{/*
     if (boton==GLUT_LEFT_BUTTON && estado==GLUT_DOWN) {

     }
     if (boton==GLUT_RIGHT_BUTTON && estado==GLUT_DOWN) {

     }//*/
}

void reshape(int w, int h)
{
   GLfloat size = 10.0f, redimension =(GLfloat)w / (GLfloat)h;
   glViewport(0,0,(GLsizei)w, (GLsizei)h);
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();

    if (w <= h)
        glOrtho (-size, size, -size / redimension, size/ redimension, 1.0f, -1.0f);
    else
        glOrtho (-size* redimension, size* redimension, -size, size, 1.0f, -1.0f);

	glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB|GLUT_DEPTH);
    glutInitWindowSize(500,500);
    glutInitWindowPosition(100,100);
    glutCreateWindow("Programa");
    init();
    //glutIdleFunc(transformar);
    glutDisplayFunc(escena);
    glutReshapeFunc(reshape);
    glutMouseFunc(mouse);
    glutSpecialFunc(tecladoS);
    glutKeyboardFunc(teclado);

    glutMainLoop();
    return 0;
}



