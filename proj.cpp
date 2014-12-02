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
	glClear(GL_COLOR_BUFFER_BIT);
	glPushMatrix();
	
	

	glPopMatrix();
	glFlush();
}
void transformar (){
    escena();
}

void reshape(int w, int h)
{
   GLfloat size = 10.0f, redimension =(GLfloat)w / (GLfloat)h;
   glViewport(0,0,(GLsizei)w, (GLsizei)h);
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();

    if (w <= h)
        glOrtho (-size, size, -size / redimension, size/ redimension, 1.0f, -1.0f);
    else
        glOrtho (-size* redimension, size* redimension, -size, size, 1.0f, -1.0f);
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
    glutInitWindowSize(250,250);
    glutInitWindowPosition(100,100);
    glutCreateWindow("Programa");
    init();
    //glutIdleFunc(transformar);
    glutDisplayFunc(escena);
    glutReshapeFunc(reshape);
    glutMainLoop();
    return 0;
}



