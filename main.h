#ifndef MAIN_H
#define MAIN_H

#include <stddef.h>

#define WINDOW_WIDTH  500
#define WINDOW_HEIGHT 500

#define TITLE "THE ROTATING CUBE"

struct ColorRGB {
	double R;
	double G;
	double B;
};

struct Point3D {
	float x;
	float y;
	float z;
};

void display();
void display_init();
void drawCube(size_t size);
void drawQuad(size_t size, struct Point3D points[], struct ColorRGB color);
#endif // MAIN_H
