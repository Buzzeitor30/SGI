#define PROYECTO "Estrella 3D"
#define PI 3.141592653589793238463
#define POSICIONX 5
#define POSICIONY 4
#define POSICIONZ 5

#include <iostream> 
#include <gl\freeglut.h>
#include <cmath>
#include <math.h>

static GLuint estrella;

void display()
{
	glClearColor(1, 1, 1, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	// Colores poligono
	glColor3f(0, 0, .3);
	glMatrixMode(GL_MODELVIEW); //Seleccionamos la matriz modelview
	glLoadIdentity(); //Identidad
	GLfloat rojos[6] = { 1, 1, 1, 0, 0, 0 };
	GLfloat green[6] = { 0, 0.5, 1, 1, 1, 0};
	GLfloat blue[6] = { 0, 0, 0, 0, 1, 1 };
		//Situamos la cámara
	gluLookAt(POSICIONX, POSICIONY, POSICIONZ, 0, 0, 0, 0, 1, 0);
	glEnable(GL_DEPTH_TEST);
	for (int i = 0; i <= 360; i += 60) {
		glPushMatrix();
		glColor3f(rojos[i/60], green[i/60], blue[i/60]);
		glRotatef((float)i, 0, 1, 0);
		glCallList(estrella);
		glPopMatrix();
	}
	glColor3f(0, 0, 0);
	glutWireSphere(1, 20, 20);
	glFlush(); // Cierra lista
}

double get_fovy(double camx, double camy, double camz) {
	//Distancia al origen, que de acuerdo al profesor es (0,0,0)
	double dis = (camx) * (camx) + (camy) * (camy) + (camz) * (camz);
	dis = sqrt(dis);
	//Seno(fovy/2) = 1/d => arcsin(fovy/2) = 1/d => 2*arcsin(fovy)
	double radians = asin(1/dis);
	return 2 * (180 / PI) * radians;
}
void reshape(GLint w, GLint h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	
	float razon = (float)w / h;
	double fovy = get_fovy(POSICIONX, POSICIONY, POSICIONZ);
	gluPerspective(fovy, razon, 1, 30);
	//gluPerspective(45, razon, 1, 50);
}



void dibujarPentagono() {
	/* Dibuja las estrellas de David creando 3 listas. La primera de ellas contiene a la estrella de David Base
	La segunda contiene la estrella pequeña que esta inscrita dentro de la grande
	La última contiene a ambos polígonos y hace la rotación de 15 grados*/
	//Creamos las listas
	estrella = glGenLists(1);
	//Variable para los ángulos
	double angle;
	//Abrimos la lista
	glNewList(estrella, GL_COMPILE);
		//Primera lista, dibuja el triangulo de arriba
	glBegin(GL_TRIANGLE_STRIP);

	// Si el orden buscado es e0,i0,e2,i2,...,e4,i4,e0,i0
	// incrementamos de 2 en 2 en el bucle y empezamos en 0
	for (int i = 0; i < 7; i += 2) {
		// sumamos 90 grados de offset
		angle = (float)(i * ((2.0 * PI) / 6.0) + PI / 2.0);
		glVertex3f(1 * cos(angle), 1 * sin(angle), 0); //exterior
		glVertex3f(0.7 * cos(angle), 0.7 * sin(angle), 0); //interior
	}
	glEnd();

	// Segunda lista, dibuja el triangulo de abajo
	glBegin(GL_TRIANGLE_STRIP);

	// Para el triangulo de abajo igual e1,i1,e3,i3...,e5,i5,e1,i1
	for (int i = 1; i < 8; i += 2) {
		angle = (float)(i * ((2.0 * PI) / 6.0) + PI / 2.0);
		glVertex3f(1 * cos(angle), 1 * sin(angle), 0); //exterior
		glVertex3f(0.7 * cos(angle), 0.7 * sin(angle), 0); //interior
	}

	glEnd();
	glEndList();

}

void main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH); //buffers a usar, añadimos profunidad
	glutInitWindowSize(400, 400);
	glutInitWindowPosition(50, 600);
	glutCreateWindow(PROYECTO);
	dibujarPentagono();
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutMainLoop();
}