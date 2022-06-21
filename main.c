#include <GL/freeglut_std.h>
#include <GL/gl.h>
#include <GL/glut.h>

#include "main.h"

#include <stdio.h>



// All faces and vertices of the cube, each row represents the four vertices of
// each face
struct Point3D _vertices[6][4] = {
    {{0.5, 0.5, 0.5}, {0.5, -0.5, 0.5}, {-0.5, -0.5, 0.5}, {-0.5, 0.5, 0.5}},
    {{-0.5, 0.5, 0.5},
     {-0.5, -0.5, 0.5},
     {-0.5, -0.5, -0.5},
     {-0.5, 0.5, -0.5}},
    {{-0.5, 0.5, -0.5},
     {-0.5, -0.5, -0.5},
     {0.5, -0.5, -0.5},
     {0.5, 0.5, -0.5}},
    {{0.5, 0.5, -0.5}, {0.5, -0.5, -0.5}, {0.5, -0.5, 0.5}, {0.5, 0.5, 0.5}},
    {{-0.5, 0.5, -0.5}, {0.5, 0.5, -0.5}, {0.5, 0.5, 0.5}, {-0.5, 0.5, 0.5}},
    {{-0.5, -0.5, -0.5},
     {0.5, -0.5, -0.5},
     {0.5, -0.5, 0.5},
     {-0.5, -0.5, 0.5}}};

// All the colors for each face of the cube
struct ColorRGB _colors[] = {
	{0.376, 0.007, 0.933}, {0.839, 0.007, 0.933},
	{0.933, 0.376, 0.007}, {0.564, 0.933, 0.007},
	{0.376, 0.490, 0.545}, {0.898, 0.223, 0.207}
};

int main(int argc, char* argv[]) {
	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
	glutCreateWindow("cubeSim");

	glutDisplayFunc(display);
	glutIdleFunc(display);

	display_init();

	glutMainLoop();
	return 0;
}

void display() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	drawCube(20);
	glFlush();
	glutSwapBuffers();
}

void display_init() {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-50, 50, -50, 50, -50, 50);

	glMatrixMode(GL_MODELVIEW);
	glClearColor(0, 0, 0, 0);
}

void drawCube(size_t size) {
	size_t i;
	
	for (size_t i = 0; i < 6; i++){
		drawQuad(size, _vertices[i], _colors[i]);
	}
}

void drawQuad(size_t size, struct Point3D points[], struct ColorRGB color) {
	GLint i;
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glColor4f(color.R, color.G, color.B, 1);
	glBegin(GL_QUADS);
	for(short i = 0; i < 4; i++) {
		glVertex3i(size * points[i].x, size * points[i].y, size * points[i].z);
	}
	glEnd();
}
