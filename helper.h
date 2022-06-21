#ifndef HELPER_H
#define HELPER_H

#include <stddef.h>

#define WINDOW_WIDTH  600
#define WINDOW_HEIGHT 500

#define ROTATION_ANGLE 2

#define TITLE "THE ROTATING CUBE"
#define INSTRUCTION \
	"+/-: SPEED   w,a,s,d: ROTATE   space: PAUSE/RESUME   k: SKELETON   q: QUIT"

struct ColorRGB {
	float R;
	float G;
	float B;
};

struct Point3D {
	float x;
	float y;
	float z;
};

void display();
void display_init();
void drawCube(int size);
void drawQuad(int size, struct Point3D points[], struct ColorRGB color);
void displayString(float x, float y, float z, char *string, int is_big);
void handleKeyboard(unsigned char ch, int x, int y);
#endif // HELPER_H
