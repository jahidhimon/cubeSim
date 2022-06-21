#include <GL/freeglut_std.h>
#include <GL/gl.h>
#include <GL/glut.h>

#include "main.h"

#include <stdio.h>



int main(int argc, char* argv[]) {
	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
	glutCreateWindow("cubeSim");

	glutDisplayFunc(display);

	glutMainLoop();
	return 0;
}

void display() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glFlush();
	glutSwapBuffers();
}
