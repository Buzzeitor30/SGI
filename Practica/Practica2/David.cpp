#include <iostream> 
#include <gl\freeglut.h>
#include <cmath>

static GLuint pentagono;
void display()
{
	glClearColor(1, 1, 1, 1);
	glClear(GL_COLOR_BUFFER_BIT);
	// Colores poligono
	glColor3f(0, 0, .3);
	glCallList(pentagono);
	glFlush(); // Cierra lista
}
void reshape(GLint w, GLint h)
{
}

void dibujarPentagono() {
	pentagono = glGenLists(1); //id lista
	//Variable para los ángulos
	double angle;
	glMatrixMode(GL_MODELVIEW); //Seleccionamos la matriz modelview
	glLoadIdentity(); //Cargamos la matriz identidad, MV = I
	
	glPushMatrix(); //Apilamos la matriz modelview actual
	glRotatef(15, 0, 0, 0);
	glNewList(pentagono, GL_COMPILE); // abrir lista
		float pi = 3.14159; //Constante PI para los cálculos
		//Primera lista, dibuja el triangulo de arriba
		glBegin(GL_TRIANGLE_STRIP);
			// Si el orden buscado es e0,i0,e2,i2,...,e4,i4,e0,i0
			// incrementamos de 2 en 2 en el bucle y empezamos en 0
			for (int i = 0; i < 7; i += 2) {
				// sumamos 90 grados de offset
				angle = (float)(i * ((2.0 * pi) / 6.0) + pi / 2.0);
				glVertex3f(1 * cos(angle), 1 * sin(angle), 0); //exterior
				glVertex3f(0.7 * cos(angle), 0.7 * sin(angle), 0); //interior
			}
		glEnd();
		// Segunda lista, dibuja el triangulo de abajo
		glBegin(GL_TRIANGLE_STRIP);
			// Para el triangulo de abajo igual e1,i1,e3,i3...,e5,i5
			for (int i = 1; i < 7; i += 2) {
				angle = (float)(i * ((2.0 * pi) / 6.0) + pi / 2.0);
				glVertex3f(1 * cos(angle), 1 * sin(angle), 0); //exterior
				glVertex3f(0.7 * cos(angle), 0.7 * sin(angle), 0);
			}
			//Necesario para hacer e5,i5,e1,i1 y completar el círculo
			angle = (float)( 1.0 * ((2.0 * pi) / 6.0) + pi / 2.0);
			glVertex3f(1 * cos(angle), 1 * sin(angle), 0); //exterior
			glVertex3f(0.7 * cos(angle), 0.7 * sin(angle), 0);
		glEnd();
	glEndList();
	glPopMatrix();

}

void main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(400, 400);
	glutInitWindowPosition(50, 600);
	glutCreateWindow("Mosaico");
	dibujarPentagono();
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutMainLoop();
}