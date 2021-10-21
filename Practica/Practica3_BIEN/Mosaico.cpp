#include <iostream> 
#include <gl\freeglut.h>
#include <cmath>

static GLuint estrella;
static GLuint estrella_chikito;
static GLuint estrella_mega;

void display()
{
	glClearColor(1, 1, 1, 1);
	glClear(GL_COLOR_BUFFER_BIT);
	// Colores poligono
	glColor3f(0, 0, .3);
	glMatrixMode(GL_MODELVIEW); //Seleccionamos la matriz modelview
	glLoadIdentity();
	

	//Estrella superior izq.
	glPushMatrix();
	glTranslatef(-0.5, 0.5, 0);
	glScalef(0.5, 0.5, 0.5);
	glCallList(estrella_mega);
	glPopMatrix();

	//Estrella superior derecha
	glPushMatrix();
	glTranslatef(0.5, 0.5, 0);
	glScalef(0.5, 0.5, 0.5);
	glRotatef(90, 0, 0, 1);
	glCallList(estrella_mega);
	glPopMatrix();
	
	//Estrella inferior izq.
	glPushMatrix();
	glTranslatef(-0.5, -0.5, 0);
	glScalef(0.5, 0.5, 0.5);
	glRotatef(90, 0, 0, 1);
	glCallList(estrella_mega);
	glPopMatrix();

	//Estrella inferior der.
	glPushMatrix();
	glTranslatef(0.5, -0.5, 0);
	glScalef(0.5, 0.5, 0.5);
	glCallList(estrella_mega);
	glPopMatrix();

	glFlush(); // Cierra lista
}
void reshape(GLint w, GLint h)
{
}

void dibujarPentagono() {
	/* Dibuja las estrellas de David creando 3 listas. La primera de ellas contiene a la estrella de David Base
	La segunda contiene la estrella pequeña que esta inscrita dentro de la grande
	La última contiene a ambos polígonos y hace la rotación de 15 grados*/
	//Creamos las listas
	estrella = glGenLists(1);
	estrella_chikito = glGenLists(2);
	estrella_mega = glGenLists(3);

	//Variable para los ángulos
	double angle;
	//Abrimos la lista
	glNewList(estrella, GL_COMPILE);
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

		// Para el triangulo de abajo igual e1,i1,e3,i3...,e5,i5,e1,i1
		for (int i = 1; i < 8; i += 2) {
			angle = (float)(i * ((2.0 * pi) / 6.0) + pi / 2.0);
			glVertex3f(1 * cos(angle), 1 * sin(angle), 0); //exterior
			glVertex3f(0.7 * cos(angle), 0.7 * sin(angle), 0); //interior
		}

		glEnd();
	glEndList();

	//Nueva lista estrella_chikito
	glNewList(estrella_chikito, GL_COMPILE);
		//Pusheamos la matriz
		glPushMatrix();
		//Rotamos y escalamos (en ese orden)
		glScalef(0.4, 0.4, 0.4);
		glRotatef(30, 0, 0, 1);
		glCallList(estrella);
		//Hacemos pop
		glPopMatrix();
	glEndList();

	//Estrella de David que contiene a las dos, rotación de 15 grados para ambas
	glNewList(estrella_mega, GL_COMPILE);
	glPushMatrix();
		glRotatef(15, 0, 0, 1);	
		glCallList(estrella);
		glCallList(estrella_chikito);
		glPopMatrix();
	glEndList();

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