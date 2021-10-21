#include <iostream> 
#include <gl\freeglut.h> 
void display()
{
	glClearColor(0, 0, .3, 1);
	glClear(GL_COLOR_BUFFER_BIT);
	glFlush();
}
void reshape(GLint w, GLint h)
{
}
void main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(500, 400);
	glutInitWindowPosition(50, 600);
	glutCreateWindow("Primer programa en OpenGL");
	std::cout << "OpenGL runnings " << std::endl;
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutMainLoop();
}