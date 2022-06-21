#include <GL/freeglut_std.h>
#include <GL/gl.h>
#include <GL/glut.h>

#include "helper.h"

#include <stdio.h>

// variables to hold temporary values of the angles and given inputs from the
// keyboard
float aX = 30, aY = 1, aZ = 0, tY = 0;
int frame = 0, stop = 0;

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
struct ColorRGB _colors[6] = {{0.10, 0.07, 0.93}, {0.39, 0.07, 0.33},
                              {0.33, 0.36, 0.07}, {0.64, 0.33, 0.07},
                              {0.76, 0.40, 0.45}, {0.98, 0.23, 0.07}};

int main(int argc, char *argv[]) {
  glutInit(&argc, argv);

  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
  glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
  glutCreateWindow("cubeSim");
  glEnable(GL_DEPTH_TEST);
  glutDisplayFunc(display);
  glutIdleFunc(display);
	glutKeyboardFunc(handleKeyboard);
  display_init();
	
  glutMainLoop();
  return 0;
}

void display() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  // Push a new matrix in the stack copy the values from the current one
  glPushMatrix();
  // Do all the rotations for current values of angles with x,y and z axes
  glRotatef(aX, 1, 0, 0);
  glRotatef(aZ, 0, 0, 1);
  glRotatef(tY, 0, 1, 0);

  // Now draw cube over the rotated space
  drawCube(30);
  // Copy the values of the new matrix to current matrix and pop off the new one
  glPopMatrix();

  glColor4f(0.56, .22, 1, 1);              // COLOR of TITLE
  displayString(-16.0f, 45.0, 0.0, TITLE, 1); // DRAW TITLE

  glColor4f(.470, .56, .61, 1);
  displayString(-47, -47, 0.0, INSTRUCTION, 0);

  glFlush();
  glutSwapBuffers();

  if (!stop) {
    tY += aY;
    if (tY >= 360) {
      tY = 0;
    }
  }
}

void display_init() {
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(-50, 50, -50, 50, -50, 50);

  glMatrixMode(GL_MODELVIEW);
  glClearColor(0, 0, 0, 0);
}

void drawCube(GLint size) {
  int i;

  for (size_t i = 0; i < 6; i++) {
    drawQuad(size, _vertices[i], _colors[i]);
  }
}

void drawQuad(GLint size, struct Point3D points[], struct ColorRGB color) {
  GLint i;
  glPolygonMode(GL_FRONT_AND_BACK, frame? GL_LINE: GL_FILL);
  glColor4f(color.R, color.G, color.B, 1);
  glBegin(GL_QUADS);
  for (short i = 0; i < 4; i++) {
    glVertex3i(size * points[i].x, size * points[i].y, size * points[i].z);
  }
  glEnd();
}

void displayString(float x, float y, float z, char *string, int is_big) {
  glRasterPos3f(x, y, z);

  for (size_t i = 0; string[i] != 0; i++) {
    glutBitmapCharacter(
        is_big ? GLUT_BITMAP_HELVETICA_18 : GLUT_BITMAP_HELVETICA_12, string[i]);
  }
}


void handleKeyboard(unsigned char key, int x, int y) {
  switch (key) {
  // map 'W' to increment x-axis rotation angle
  case 'W':
    aX += ROTATION_ANGLE;
    if (aX >= 359) {
      aX = 0;
    }
    break;
  // map 'S' to decrement x-axis rotation angle
  case 's':
  case 'S':
    aX -= ROTATION_ANGLE;
    if (aX <= 0) {
      aX = 359;
    }
    break;
  // map 'A' to increment z-axis rotation angle
  case 'a':
  case 'A':
    aZ += ROTATION_ANGLE;
    if (aZ >= 359) {
      aZ = 0;
    }
    break;
  // map 'D' to decrement z-axis rotation angle
  case 'd':
  case 'D':
    aZ -= ROTATION_ANGLE;
    if (aZ <= 0) {
      aZ = 359;
    }
    break;
  // map '+' to increment y-axis rotation speed
  case '+':
    aY += 1;
    if (aY >= 360) {
      aY = 0;
    }
    break;
	// map '-' to decrement y-axis roation speed
	case '-':
		aY -= 1;
		if (aY <= 0) {
			aY = 360;
		}
		break;
  // map 'k' to toggle frame draw switch
  case 'k':
  case 'K':
    frame ^= 1;
    break;
  // map 'SPACE' to toggle stop y-axis rotation switch
  case 0x20:
    stop ^= 1;
    break;
  // map 'Q' to exit
  case 0x1B:
  case 'q':
  case 'Q':
    exit(0);
    break;
  }
}
