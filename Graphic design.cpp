//
//  Created by Omniah H. Nagoor on 06/03/1445 AH.
//  Copyright © 2023 Omniah H. Nagoor. All rights reserved.

#ifdef __APPLE__
/* Defined before OpenGL and GLUT includes to avoid deprecation messages */
#define GL_SILENCE_DEPRECATION
#include <OpenGL/gl.h>
#include <GLUT/glut.h>      // handle the window-managing operations
#else
#include <GL/glew.h>
#include <GL/freeglut.h>    // handle the window-managing operations
#endif
#include <stdlib.h>
#include <iostream>
#include <ctime>



int currentScene = 1;
using namespace std;

GLint win_width = 500,
win_hight = 500;
GLuint myTexture;
char image2Path[] = "D:\\the hunter art.bmp";
float transValue;
float scaleValue;
GLdouble PI = 3.14159265359;
float housePosition = 0.0f;
float treePositionX = 0.0f;
float PositionX = 0.0f;

void facecir(GLfloat x, GLfloat y, GLfloat radius) {
	int i;
	int triangleAmount = 20; //# of triangles used to draw circle
	GLfloat twicePi = 2.0f * PI;
	glBegin(GL_TRIANGLE_FAN);
	glVertex2f(x, y); // center of circle
	for (i = 0; i <= triangleAmount; i++) {
		glVertex2f(
			x + (radius * cos(i * twicePi / triangleAmount)),
			y + (radius * sin(i * twicePi / triangleAmount))
		);
	}
	glEnd();
}

void drawCircle(float radius, int segments) {
	glBegin(GL_POLYGON);
	for (int i = 0; i < segments; i++) {
		float theta = 2.0f * PI * float(i) / float(segments);
		float x = radius * cosf(theta);
		float y = radius * sinf(theta);
		glVertex2f(x, y);
	}
	glEnd();
}
void drawOval(float x_radius, float y_radius, int segments) {
	glBegin(GL_POLYGON);
	for (int i = 0; i < segments; i++) {
		float theta = 2.0f * PI * float(i) / float(segments);
		float x = x_radius * cosf(theta);
		float y = y_radius * sinf(theta);
		glVertex2f(x, y);
	}
	glEnd();
}
void drawHollowCircle(GLfloat x, GLfloat y, GLfloat radius) {
	int i;
	int lineAmount = 100; //# of triangles used to draw circle

	//GLfloat radius = 0.8f; //radius
	GLfloat twicePi = 2.0f * PI;

	glBegin(GL_LINE_LOOP);
	for (i = 0; i <= lineAmount; i++) {
		glVertex2f(
			x + (radius * cos(i * twicePi / lineAmount)),
			y + (radius * sin(i * twicePi / lineAmount))
		);
	}
	glEnd();
}



void drawFilledCircle(GLfloat x, GLfloat y, GLfloat radius) {
	int i;
	int triangleAmount = 20; //# of triangles used to draw circle

	//GLfloat radius = 0.8f; //radius
	GLfloat twicePi = 2.0f * PI;

	glBegin(GL_TRIANGLE_FAN);
	glVertex2f(x, y); // center of circle
	for (i = 0; i <= triangleAmount; i++) {
		glVertex2f(
			x + (radius * cos(i * twicePi / triangleAmount)),
			y + (radius * sin(i * twicePi / triangleAmount))
		);
	}
	glEnd();
}



void drawText(const char* text, int length, int x, int y) {
	glMatrixMode(GL_PROJECTION);
	double* matrix = new double[16];
	glGetDoublev(GL_PROJECTION_MATRIX, matrix);
	glLoadIdentity();
	glOrtho(0, 800, 0, 600, -5, 5);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glPushMatrix();
	glLoadIdentity();
	glRasterPos2i(x, y);
	for (int i = 0; i < length; i++) {

		glutBitmapCharacter(GLUT_BITMAP_9_BY_15, (int)text[i]);

	}
	glPopMatrix();
	glMatrixMode(GL_PROJECTION);
	glLoadMatrixd(matrix);
	glMatrixMode(GL_MODELVIEW);

}



void drawText(const char* text, int length, int x, int y, void* font) {
	glRasterPos2i(x, y);
	for (int i = 0; i < length; i++) {
		glutBitmapCharacter(font, (int)text[i]);
	}
}


GLuint LoadTexture(const char* filename, int width, int height)
{

	GLuint texture;

	unsigned char* data;

	FILE* file;

	//The following code will read in our RAW file


	fopen_s(&file, filename, "rb");

	if (file == NULL)
	{
		cout << "Unable to open the image file" << endl << "Program will exit :(" << endl;
		exit(0);
		return 0;
	}

	data = (unsigned char*)malloc(width * height * 3);

	fread(data, width * height * 3, 1, file);

	fclose(file);

	// reorder the image colors to RGB not BGR

	for (int i = 0; i < width * height; ++i)

	{

		int index = i * 3;

		unsigned char B, R;

		B = data[index];

		R = data[index + 2];

		data[index] = R;

		data[index + 2] = B;

	}

	/////////////////////////////////////////

	// All Exercises TODO: load another texture image

	//////

	glGenTextures(1, &texture);
	//generate the texture with the loaded data

	glBindTexture(GL_TEXTURE_2D, texture); //bind the texture to it's array

	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE); //set texture environment parameters

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	//glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);

	//glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);

	/////////////////////////////////////////

	free(data); //free the texture array

	if (glGetError() != GL_NO_ERROR)

		printf("GLError in genTexture()\n");

	return texture; //return whether it was successfull 
}


void home()
{
	glPointSize(200.0f);
	glBegin(GL_POINTS);
	glColor3f(1.0f, 0.9f, 0.5f);
	glVertex2f(-0.650, -0.02f);
	glEnd();

	glPointSize(60.0f);
	glBegin(GL_POINTS);
	glColor3f(0.7f, 0.3f, 0.1f);
	glVertex2f(-0.650, -0.30f);
	glVertex2f(-0.650, -0.25f);
	glEnd();

	glPointSize(30.0f);
	glBegin(GL_POINTS);
	glColor3f(0.6f, 0.3f, 0.0f);
	glVertex2f(-0.650, -0.24f);
	glVertex2f(-0.650, -0.36f);
	glEnd();

	glBegin(GL_TRIANGLES);
	glColor3f(1.0f, 0.9f, 0.5f);
	glVertex2f(-0.7f, 0.7f);
	glVertex2f(-0.999f, 0.37f);
	glVertex2f(-0.23f, 0.37f);
	glEnd();

	glLineWidth(14.0f);
	glBegin(GL_LINES);
	glColor3f(0.6f, 0.3f, 0.0f);
	glVertex2f(-0.999f, 0.37f);
	glVertex2f(-0.7f, 0.72f);
	glVertex2f(-0.7f, 0.72f);
	glVertex2f(-0.23f, 0.37f);
	glEnd();

	glLineWidth(27.0f);
	glBegin(GL_LINES);
	glColor3f(0.6f, 0.3f, 0.0f);
	glVertex2f(-0.34f, 0.49f);
	glVertex2f(-0.24f, 0.45f);
	glEnd();

	glPointSize(50.0f);
	glBegin(GL_POINTS);
	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex2f(-0.8, 0.12f);
	glVertex2f(-0.45, 0.12f);
	glColor3f(0.2f, 0.8f, 0.9f);
	glEnd();

	glPointSize(40.0f);
	glBegin(GL_POINTS);
	glVertex2f(-0.8, 0.12f);
	glVertex2f(-0.45, 0.12f);
	glEnd();

	glLineWidth(5.0f);
	glBegin(GL_LINES);
	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex2f(-0.45f, 0.20f);
	glVertex2f(-0.45f, 0.02f);

	glVertex2f(-0.8f, 0.20f);
	glVertex2f(-0.8f, 0.02f);

	glVertex2f(-0.35f, 0.12f);
	glVertex2f(-0.54f, 0.12f);

	glVertex2f(-0.9f, 0.12f);
	glVertex2f(-0.7f, 0.12f);

	glEnd();

	glColor3f(1.0f, 1.0f, 1.0f);
	facecir(-0.65, 0.4, 0.10);
	glColor3f(0.2f, 0.8f, 0.9f);
	facecir(-0.65, 0.4, 0.08);
	glColor3f(0.0f, 0.0f, 0.0f);
	facecir(-0.56, -0.3f, 0.02);

}


void TheRoom() {

	glEnable(GL_BLEND);
	glEnable(GL_DEPTH_TEST);
	// the window
	// 
	// frame 2
	glColor4f(0.807f, 0.693f, 0.636f, 0);
	glBegin(GL_LINES);
	glColor3f(0.294, 0.160, 0.2);
	glVertex2f(0.43, 0.92);
	glVertex2f(0.43, 0.44);
	glEnd();

	// frame 2
	glBegin(GL_LINES);
	glColor3f(0.294, 0.160, 0.2);
	glVertex2f(0.75, 0.68);
	glVertex2f(0.1, 0.68);
	glEnd();


	// square1 of the window
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glPushMatrix();
	glTranslatef(0.5, 0.2, 0.0);
	glScalef(0.8, 0.8, 1);
	glBegin(GL_QUADS);
	glColor4f(0.615f, 0.831f, 0.929f, 0.6f);
	glTexCoord2f(0, 1); glVertex2f(-0.5, 0.9);
	glTexCoord2f(0, 0); glVertex2f(-0.5, 0.6);
	glTexCoord2f(1, 0); glVertex2f(-0.1, 0.6);
	glTexCoord2f(1, 1); glVertex2f(-0.1, 0.9);
	glEnd();

	//square2 of the window
	glBegin(GL_QUADS);
	glColor4f(0.615f, 0.831f, 0.929f, 0.6f);
	glVertex2f(-0.5, 0.6);
	glVertex2f(-0.5, 0.3);
	glVertex2f(-0.1, 0.3);
	glVertex2f(-0.1, 0.6);
	glEnd();

	// square3 of the window
	glBegin(GL_QUADS);
	glColor4f(0.615f, 0.831f, 0.929f, 0.6f);
	glVertex2f(-0.1, 0.9);
	glVertex2f(-0.1, 0.6);
	glVertex2f(0.3, 0.6);
	glVertex2f(0.3, 0.9);
	glEnd();

	//square 4 of the window
	glBegin(GL_QUADS);
	glColor4f(0.615f, 0.831f, 0.929f, 0.6f);
	glVertex2f(-0.1, 0.6);
	glVertex2f(-0.1, 0.3);
	glVertex2f(0.3, 0.3);
	glVertex2f(0.3, 0.6);
	glEnd();

	// lining the shape 
	glLineWidth(7.0);
	glBegin(GL_LINE_LOOP);
	glColor3f(0.294, 0.160, 0.2);
	glVertex2f(-0.5, 0.9);
	glVertex2f(0.3, 0.9);
	glVertex2f(0.3, 0.3);
	glVertex2f(-0.5, 0.3);
	glEnd();
	glPopMatrix();

	//----------------------------------------

		// the bed

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glPushMatrix();
	glTranslatef(0, -0.1, 0);
	glBegin(GL_QUADS);
	// frame
	glColor3f(0.376f, 0.211f, 0.258);
	glVertex2f(-0.2, 0.1);
	glVertex2f(0.7, 0.1);
	glVertex2f(0.7, -0.1);
	glVertex2f(-0.2, -0.1);
	glEnd();

	// frame (bed wall)
	glBegin(GL_QUADS);
	glColor3f(0.294, 0.160, 0.2);
	glVertex2f(0.7, 0.3);
	glVertex2f(0.9, 0.3);
	glVertex2f(0.9, -0.1);
	glVertex2f(0.7, -0.1);
	glEnd();

	//base 
	glBegin(GL_QUADS);
	glColor3f(0.294, 0.160, 0.2);
	glVertex2f(-0.2, -0.1);
	glVertex2f(-0.2, -0.3);
	glVertex2f(0.0, -0.1);
	glVertex2f(0.0, -0.1);
	glEnd();

	//pillow 

	glBegin(GL_QUADS);
	glColor3f(1.0, 1.0, 1.0);
	glVertex2f(0.7, 0.2);
	glVertex2f(0.7, 0.1);
	glVertex2f(0.5, 0.1);
	glVertex2f(0.5, 0.2);
	glEnd();

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glPushMatrix();
	glScalef(-1, 1, 1);
	glTranslatef(-0.5, -0.1, 0);
	glBegin(GL_QUADS);
	glScalef(1, -1, 1);
	glColor3f(0.294, 0.160, 0.2);
	glVertex2f(-0.2, -0.1);
	glVertex2f(-0.2, -0.3);
	glVertex2f(0.0, -0.1);
	glVertex2f(0.0, -0.1);
	glEnd();
	glPopMatrix();

	// glPopMatrix();

	 //-----------------------------------------
		 // the closet 

		 // door 1
	glColor3f(0.23, 0.23, 0.23);
	facecir(-0.5, 0.1, 0.03);

	glLineWidth(4.0);
	glBegin(GL_LINE_LOOP);
	glColor3f(0.294, 0.160, 0.2);
	glVertex2f(-0.8, 0.4);
	glVertex2f(-0.8, -0.2);
	glVertex2f(-0.6, -0.2);
	glVertex2f(-0.6, 0.4);
	glEnd();

	glBegin(GL_QUADS);
	glColor3f(0.407, 0.211, 0.286);
	glVertex2f(-0.8, 0.4);
	glVertex2f(-0.8, -0.2);
	glVertex2f(-0.6, -0.2);
	glVertex2f(-0.6, 0.4);
	glEnd();

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glPushMatrix();
	glScalef(-1, 1, 1);
	glTranslatef(1.1, 0, 0);
	glColor3f(0.23, 0.23, 0.23);
	facecir(-0.5, 0.1, 0.03);
	glLineWidth(4.0);
	glBegin(GL_LINE_LOOP);
	glColor3f(0.294, 0.160, 0.2);
	glVertex2f(-0.7, 0.4);
	glVertex2f(-0.7, -0.2);
	glVertex2f(-0.3, -0.2);
	glVertex2f(-0.3, 0.4);
	glEnd();
	glBegin(GL_QUADS);
	glColor3f(0.407, 0.211, 0.286);
	glVertex2f(-0.7, 0.4);
	glVertex2f(-0.7, -0.2);
	glVertex2f(-0.5, -0.2);
	glVertex2f(-0.5, 0.4);
	glEnd();
	glPopMatrix();

	// base 
  /*  glLineWidth(7.0);
	glBegin(GL_LINE_LOOP);
	glColor3f(1.3, 0.2, 0.3);
	glVertex2f(-0.8, 0.4);
	glVertex2f(-0.8, -0.2);
	glVertex2f(-0.6, -0.2);
	glVertex2f(-0.6, 0.4);
	glEnd();*/


	//--------------------------------------------
		// the small teable and the granma's belongings 

	glLineWidth(9.0);
	glBegin(GL_LINE_LOOP);
	glColor3f(0.294, 0.160, 0.2);
	glVertex2f(0.6, -0.4);
	glVertex2f(0.1, -0.4);

	glEnd();

	glLineWidth(9.0);
	glBegin(GL_LINE_LOOP);
	glColor3f(0.294, 0.160, 0.2);
	glVertex2f(0.13, -0.4);
	glVertex2f(0.13, -0.6);
	glEnd();

	glLineWidth(9.0);
	glBegin(GL_LINE_LOOP);
	glColor3f(0.294, 0.160, 0.2);
	glVertex2f(0.57, -0.4);
	glVertex2f(0.57, -0.6);
	glEnd();

	//granma's cap
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glPushMatrix();
	glTranslatef(0.07, 0, 0);
	glLineWidth(10.0);
	glBegin(GL_LINE_LOOP);
	glColor3f(0.250, 0.396, 0.588);
	glVertex2f(0.3, -0.37);
	glVertex2f(0.49, -0.37);
	glEnd();
	glColor3f(0.250, 0.396, 0.588);
	facecir(0.4, -0.34, 0.073);
	glPopMatrix();

	// granma's glasses
	glColor4f(0.615f, 0.831f, 0.929f, 0.6f);
	facecir(0.27, -0.35, 0.03);

	glLineWidth(2.0);
	glBegin(GL_LINE_LOOP);
	glColor3f(0.0, 0.0, 0.0);
	glVertex2f(0.24, -0.35);
	glVertex2f(0.2, -0.35);
	glEnd();

	glColor4f(0.615f, 0.831f, 0.929f, 0.6f);
	facecir(0.17, -0.35, 0.03);

	glLineWidth(2.0);
	glBegin(GL_LINE_LOOP);
	glColor3f(0.0, 0.0, 0.0);
	glVertex2f(0.29, -0.35);
	glVertex2f(0.34, -0.28);
	glEnd();


	glLineWidth(2.0);
	glBegin(GL_LINE_LOOP);
	glColor3f(0.0, 0.0, 0.0);
	glVertex2f(0.14, -0.35);
	glVertex2f(0.19, -0.28);
	glEnd();
	//--------------------------------------------
	 // the carrpet 
	glBegin(GL_QUADS);
	glColor3f(0.533, 0.290, 0.290);
	glVertex2f(-0.9, -0.11);
	glVertex2f(-0.9, -0.9);
	glVertex2f(0.9, -0.9);
	glVertex2f(0.9, -0.11);
	glEnd();

	//-----------------------------------------------
	glDisable(GL_DEPTH_TEST);
	glPopMatrix();


}

void BackgroundS1() {
	glPointSize(30000000000000000000000000000000000000.0f);
	glBegin(GL_POINTS);
	glColor3f(0.9f, 0.8f, 0.7f);
	glVertex2f(0.0f, 0.0f);
	glVertex2f(-0.5f, -0.5f);
	glVertex2f(0.5f, -0.5f);
	glVertex2f(-0.5f, 0.5f);
	glVertex2f(0.5f, 0.5f);
	glEnd();

	glPointSize(30000000000000000000000000000000000000.0f);
	glBegin(GL_POINTS);
	glColor3f(0.5f, 0.2f, 0.0f);
	glVertex2f(-0.5f, -0.8f);
	glVertex2f(0.5f, -0.8f);
	glEnd();
}
void door() {
	glPointSize(100.0f);
	glBegin(GL_POINTS);
	glColor3f(0.7f, 0.3f, 0.1f);
	glVertex2f(0.0f, -0.09f);
	glVertex2f(0.0f, 0.08f);
	glEnd();

	glPointSize(50.0f);
	glBegin(GL_POINTS);
	glColor3f(0.6f, 0.3f, 0.0f);
	glVertex2f(0.0f, -0.14f);
	glVertex2f(0.0f, 0.10f);
	glEnd();

}
void window() {
	glPointSize(80.0f);
	glBegin(GL_POINTS);
	glColor3f(0.7f, 0.3f, 0.1f);//////
	glVertex2f(-0.6, 0.2f);
	glEnd();

	glPointSize(70.0f);
	glBegin(GL_POINTS);
	glColor3f(0.2f, 0.8f, 0.9f);
	glVertex2f(-0.6, 0.2f);
	glEnd();

	glLineWidth(5.0f);
	glBegin(GL_LINES);
	glColor3f(0.7f, 0.3f, 0.1f);
	glVertex2f(-0.6f, 0.36f);
	glVertex2f(-0.6f, 0.04f);
	glVertex2f(-0.75f, 0.20f);
	glVertex2f(-0.45f, 0.20f);
	glEnd();
}

void panel() {
	glPointSize(80.0f);
	glBegin(GL_POINTS);
	glColor3f(0.8f, 0.4f, 0.0f);
	glVertex2f(0.6, 0.2f);
	glEnd();

	glPointSize(70.0f);
	glBegin(GL_POINTS);
	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex2f(0.6f, 0.2f);
	glEnd();

	glBegin(GL_TRIANGLES);
	glColor3f(0.8f, 0.6f, 0.4f);
	glVertex2f(0.004, 0.2);
	glColor3f(0.8f, 0.5f, 0.2f);
	glVertex2f(0.002, 0.2);
	glColor3f(0.7f, 0.5f, 0.3f);
	glVertex2f(0.006, 0.2);
	glEnd();
}
void draw() {
	//background 

	glBegin(GL_QUADS);

	glColor3f(0.71f, 0.81f, 0.88f);

	glVertex2f(1.0f, 1.f);

	glVertex2f(1.0f, -1.0f);

	glVertex2f(-1.0f, -1.0f);

	glVertex2f(-1.0f, 1.0f);

	glEnd();

	glFlush();

	// clouds in the right side up

	glColor3f(1.0f, 0.96f, 0.93f);

	facecir(0.25, 0.6, .15);

	facecir(0.48, 0.6, .15);

	facecir(0.48, 0.7, .15);

	facecir(0.70, 0.6, .15);

	// rainbow (red)

	glLineWidth(20.0f);

	glColor3f(1.0f, 0.0f, 0.0f);

	drawHollowCircle(0, -0.2, 0.8);

	// rainbow (orange)

	glLineWidth(20.0f);

	glColor3f(1.0f, 0.37f, 0.12f);

	drawHollowCircle(0, -0.2, 0.74); //radius -6

	// rainbow (yellow)

	glLineWidth(20.0f);

	glColor3f(1.0f, 0.91f, 0.0f);

	drawHollowCircle(0, -0.2, 0.68); //radius -6

	// rainbow (green)

	glLineWidth(20.0f);

	glColor3f(0.0f, 1.0f, 0.0f);

	drawHollowCircle(0, -0.2, 0.62); //radius -6

	// rainbow (bright blue)

	glLineWidth(20.0f);

	glColor3f(0.0f, 0.58f, 1.0f);

	drawHollowCircle(0, -0.2, 0.56); //radius -6

	// rainbow (blue)

	glLineWidth(20.0f);

	glColor3f(0.0f, 0.0f, 1.0f);

	drawHollowCircle(0, -0.2, 0.50); //radius -6

	// rainbow (purple)

	glLineWidth(20.0f);

	glColor3f(0.5f, 0.0f, 0.5f);

	drawHollowCircle(0, -0.2, 0.44); //radius -6

	// to cut the circules 

	glBegin(GL_QUADS);

	glColor3f(0.71f, 0.81f, 0.88f);

	glVertex2f(-1.0f, -0.2f);

	glVertex2f(1.0f, -0.2f);

	glVertex2f(1.0f, -1.0f);

	glVertex2f(-1.0f, -1.0f);

	glEnd();

	glFlush();

	// clouds in the left side down

	glColor3f(1.0f, 0.96f, 0.93f);

	facecir(-0.45, -0.2, .17);

	facecir(-0.68, -0.2, .17);

	facecir(-0.68, -0.1, .17);

	facecir(-0.95, -0.2, .17);

	// clouds in the right side down

	glColor3f(1.0f, 0.96f, 0.93f);

	facecir(0.45, -0.2, .17);

	facecir(0.68, -0.2, .17);

	facecir(0.68, -0.1, .17);

	facecir(0.95, -0.2, .17);

}
void flowerS1() {
	glPointSize(06.0f);
	glBegin(GL_POINTS);
	glColor3f(1.0f, 1.0f, 0.2f);
	glVertex2f(0.6, -0.15f);
	glEnd();

	glPointSize(08.0f);
	glBegin(GL_POINTS);
	glColor3f(1.0f, 0.5f, 0.6f);
	glVertex2f(0.63, -0.18f);
	glVertex2f(0.63, -0.15f);
	glVertex2f(0.63, -0.12f);
	glVertex2f(0.6, -0.12f);
	glVertex2f(0.57, -0.12f);
	glVertex2f(0.57, -0.15f);
	glVertex2f(0.57, -0.18f);
	glVertex2f(0.6, -0.18f);
	glEnd();

	glPointSize(06.0f);
	glBegin(GL_POINTS);
	glColor3f(0.5f, 0.7f, 0.1f);
	glVertex2f(0.6, -0.20f);
	glVertex2f(0.6, -0.22f);
	glVertex2f(0.62, -0.22f);
	glVertex2f(0.6, -0.24f);
	glEnd();

	glPointSize(30.0f);
	glBegin(GL_POINTS);
	glColor3f(0.9f, 0.8f, 0.5f);
	glVertex2f(0.6, -0.30f);
	glEnd();

}


void eyes()
{
	glPointSize(4.0f);
	glBegin(GL_TRIANGLES);
	glColor3f(0, 0, 0);
	//right eye
	glVertex2f(.750, 1.71);
	glVertex2f(.67, 1.71);
	glVertex2f(.59, 1.71);

	glVertex2f(.68, 1.63);
	glVertex2f(.68, 1.55);
	glVertex2f(.68, 1.47);
	//wh
	glColor3f(0.5, 0.5, 0.5);
	glVertex2f(.59, 1.63);

	glColor3f(0.9, 0.9, 0.9);
	glVertex2f(.59, 1.55);
	glVertex2f(.59, 1.47);

	//left eye
	glColor3f(0, 0, 0);

	glVertex2f(.019, 1.71);
	glVertex2f(-.09, 1.71);
	glVertex2f(.0, 1.71);

	glVertex2f(.1, 1.71);
	glVertex2f(.1, 1.63);
	glVertex2f(.1, 1.55);
	glVertex2f(.1, 1.47);

	glVertex2f(-.17, 1.63);
	glVertex2f(-.17, 1.55);
	///
	glColor4f(.7333, 0.5922, .4588, 0.5);
	glVertex2f(-.17, 1.47);

	//wh
	glColor3f(0.5, 0.5, 0.5);
	glVertex2f(.019, 1.63);
	glVertex2f(-.09, 1.63);

	glColor3f(0.9, 0.9, 0.9);
	glVertex2f(.019, 1.55);
	glVertex2f(.019, 1.47);
	glVertex2f(-.09, 1.55);
	glVertex2f(-.09, 1.47);

	glEnd();

}

void face()
{
	glPointSize(4.0f);
	glBegin(GL_POINTS);
	//light color
	glColor4f(.7333, 0.5922, .4588, 1);
	//nose
	glVertex2f(.59, 1.27);
	//mouth
	glVertex2f(.33, 1.1);
	glVertex2f(.25, 1.1);
	//shadow
	glVertex2f(.78, 1.37);
	glVertex2f(.78, 1.19);
	glVertex2f(.69, 1.1);
	glVertex2f(.055, 1.01);
	glVertex2f(.49, 1.01);
	glVertex2f(-.149, 1.19);

	glVertex2f(.48, 1.71);
	glVertex2f(.38, 1.71);
	glVertex2f(.27, 1.71);
	glVertex2f(.21, 1.71);
	glVertex2f(.12, 1.82);
	glVertex2f(.12, 1.91);
	glVertex2f(-.19, 1.71);
	glVertex2f(.68, 1.82);
	glVertex2f(.68, 1.91);
	//neck
	glVertex2f(.36, .83);
	glVertex2f(.27, .83);
	glVertex2f(.18, .83);
	//ear
	glVertex2f(-.419, 1.37);
	glVertex2f(-.419, 1.46);
	glVertex2f(-.419, 1.55);

	//out
	glColor4f(.4431, 0.2588, .2196, 1);
	glVertex2f(.77, 1.1);
	glVertex2f(-.419, 1.27);
	glVertex2f(.85, 1.18);
	glVertex2f(.85, 1.26);
	glVertex2f(.85, 1.34);
	glVertex2f(.67, 1.01);
	glVertex2f(.58, 1.01);

	glVertex2f(.49, .92);
	glVertex2f(.4, .92);
	glVertex2f(.31, .92);
	glVertex2f(.22, .92);
	glVertex2f(.13, .92);
	glVertex2f(.04, .92);
	glVertex2f(.067, .92);

	glVertex2f(-.059, 1.01);
	glVertex2f(-.149, 1.1);

	glVertex2f(.78, 1.44);
	glVertex2f(.78, 1.53);
	glVertex2f(.78, 1.62);

	glEnd();
}

void hand()
{
	glPointSize(4.0f);
	glBegin(GL_POINTS);
	//light color
	glColor4f(.4431, 0.2588, .2196, 1);
	//left hand
	glVertex2f(-0.57, .08);
	glVertex2f(-0.57, -.02);
	glVertex2f(-0.66, -.12);
	glVertex2f(-0.66, -.22);
	glVertex2f(-0.75, -.32);
	glVertex2f(-0.84, -.42);
	glVertex2f(-0.84, -.52);
	glVertex2f(-0.75, -.62);
	glVertex2f(-0.75, -.72);
	glVertex2f(-0.66, -.72);
	glVertex2f(-0.57, -.72);/////take shadow
	glVertex2f(-0.48, -.72);
	glVertex2f(-0.48, -.62);
	glVertex2f(-0.39, -.52);
	glVertex2f(-0.39, -.42);
	glVertex2f(-0.39, -.32);
	glVertex2f(-0.39, -.22);
	glVertex2f(-0.3, -.12);
	glVertex2f(-0.3, -.02);
	glVertex2f(-0.3, .08);
	glVertex2f(-0.3, -.02);

	//right hand
	glVertex2f(.915, -.25);
	glVertex2f(.915, -.15);
	glVertex2f(.915, -.04);
	glVertex2f(1.015, -.35);
	glVertex2f(1.105, -.45);
	glVertex2f(1.105, -.55);

	glVertex2f(1.03, -.65);
	glVertex2f(.93, -.55);
	glVertex2f(.84, -.45);
	glVertex2f(.84, -.35);
	glVertex2f(.71, -.25);
	glVertex2f(.71, -.15);
	glVertex2f(.71, -.04);
	glVertex2f(.827, .07);
	glVertex2f(.8, .07);

	//color
	glColor4f(.7333, 0.5922, .4588, 1);
	//right
	glVertex2f(.825, -.25);
	glVertex2f(.825, -.15);
	glVertex2f(.825, -.04);
	glVertex2f(.91, -.34);
	glVertex2f(.91, -.44);
	glVertex2f(1., -.44);
	glVertex2f(1., -.55);

	//left
	glVertex2f(-0.39, .08);
	glVertex2f(-0.39, -.02);
	glVertex2f(-0.39, -.12);
	glVertex2f(-0.48, .08);
	glVertex2f(-0.48, -.02);
	glVertex2f(-0.57, -.62);
	glVertex2f(-0.57, -.52);
	glVertex2f(-0.67, -.62);

	glColor4f(1, .8, .6, 1);
	glVertex2f(-0.48, -.12);
	glVertex2f(-0.48, -.22);
	glVertex2f(-0.48, -.32);
	glVertex2f(-0.48, -.42);
	glVertex2f(-0.48, -.52);

	glVertex2f(-0.57, -.12);
	glVertex2f(-0.57, -.22);
	glVertex2f(-0.57, -.32);
	glVertex2f(-0.57, -.42);
	glVertex2f(-0.66, -.52);
	glVertex2f(-0.5, -.32);
	glVertex2f(-0.57, -.42);
	glVertex2f(-0.73, -.52);
	glVertex2f(-0.73, -.42);
	glVertex2f(-0.64, -.42);
	glVertex2f(-0.64, -.32);
	glEnd;
}
void hairc() {
	glPointSize(4.0f);
	glBegin(GL_QUADS);
	glColor4f(.5569, .3490, .4275, 1);
	glVertex2f(.910, 2.47);
	glVertex2f(.910, 1.13);
	glVertex2f(.82, 1.13);
	glVertex2f(.82, 2.47);


	glVertex2f(1.13, 2.47);
	glVertex2f(1.13, 1.06);
	glVertex2f(.8, 1.06);
	glVertex2f(.8, 2.47);

	glVertex2f(1.03, 2.57);
	glVertex2f(1.03, 1.96);
	glVertex2f(-.39, 1.96);
	glVertex2f(-.39, 2.57);

	glVertex2f(1.13, 2.47);
	glVertex2f(1.13, 1.86);
	glVertex2f(-.48, 1.86);
	glVertex2f(-.48, 2.47);

	glVertex2f(-.19, 2.47);
	glVertex2f(-.19, .8);
	glVertex2f(-.38, .8);
	glVertex2f(-.38, 2.47);

	glVertex2f(.86, 2.67);
	glVertex2f(.86, 1.96);
	glVertex2f(-.22, 1.96);
	glVertex2f(-.22, 2.67);

	glVertex2f(-.12, 2.77);
	glVertex2f(-.12, 1.86);
	glVertex2f(.83, 1.86);
	glVertex2f(.83, 2.77);

	glVertex2f(.14, 2.87);
	glVertex2f(.14, 1.86);
	glVertex2f(.65, 1.86);
	glVertex2f(.65, 2.87);

	glVertex2f(-.76, 01.020);
	glVertex2f(-.76, 0.18);
	glVertex2f(-1.12, 0.18);
	glVertex2f(-1.12, 01.020);

	glVertex2f(-.67, 01.120);
	glVertex2f(-.67, -0.42);
	glVertex2f(-1., -0.42);
	glVertex2f(-1., 01.120);

	glVertex2f(-.41, 1.85);
	glVertex2f(-.41, .41);
	glVertex2f(-.68, .41);
	glVertex2f(-.68, 1.85);

	glVertex2f(-.56, .41);
	glVertex2f(-.56, -.09);
	glVertex2f(-.78, -.09);
	glVertex2f(-.78, .41);

	glEnd();
}

void hair()
{
	glPointSize(4.0f);
	glBegin(GL_POINTS);
	glColor4f(.3725, 0.2594, .2509, 1);

	//out line
	glVertex2f(-.67, 1.67);
	glVertex2f(-.67, 1.17);
	glVertex2f(-.67, 1.27);
	glVertex2f(-.67, 1.37);
	glVertex2f(-.67, 1.47);
	glVertex2f(-.67, 1.57);
	glVertex2f(-.67, 1.67);
	glVertex2f(-.67, 1.71);
	glVertex2f(.68, 2.22);
	glVertex2f(.68, 2.12);
	glVertex2f(.68, 2.02);
	glVertex2f(.78, 2.02);
	glVertex2f(.78, 1.92);
	glVertex2f(.78, 1.82);
	//
	glVertex2f(.87, 1.82);
	glVertex2f(.96, 1.82);
	glVertex2f(1.05, 1.82);
	glVertex2f(.58, 1.92);
	glVertex2f(.58, 1.82);
	glVertex2f(.48, 1.82);
	glVertex2f(.38, 1.82);
	glVertex2f(.38, 1.92);
	glVertex2f(.28, 1.82);
	glVertex2f(.18, 1.82);
	glVertex2f(.02, 1.82);
	glVertex2f(.02, 1.92);
	glVertex2f(.02, 2.02);
	glVertex2f(.12, 2.02);
	glVertex2f(.12, 2.12);
	glVertex2f(.12, 2.22);
	glVertex2f(.12, 2.32);
	glVertex2f(-.07, 1.82);
	glVertex2f(-.16, 1.82);
	glVertex2f(-.25, 1.82);
	glVertex2f(-.34, 1.82);
	glVertex2f(-.43, 1.82);
	glVertex2f(-.52, 1.82);
	glVertex2f(-.52, 1.92);
	glVertex2f(-.52, 2.02);
	glVertex2f(-.52, 2.12);
	glVertex2f(-.52, 2.22);
	glVertex2f(-.43, 2.32);
	glVertex2f(-.43, 2.42);
	glVertex2f(-.34, 2.52);
	glVertex2f(-.25, 2.62);
	glVertex2f(-.16, 2.72);
	glVertex2f(-.07, 2.72);
	glVertex2f(.02, 2.82);
	glVertex2f(.11, 2.82);
	glVertex2f(.2, 2.92);
	glVertex2f(.29, 2.92);
	glVertex2f(.38, 2.92);
	glVertex2f(.47, 2.92);
	glVertex2f(.56, 2.92);
	glVertex2f(.65, 2.82);
	glVertex2f(.74, 2.82);
	glVertex2f(.83, 2.72);
	glVertex2f(.92, 2.62);
	glVertex2f(1.02, 2.52);
	glVertex2f(1.11, 2.42);
	glVertex2f(1.11, 2.32);
	glVertex2f(-.419, 1.65);
	glVertex2f(-.419, 1.75);
	glVertex2f(-.419, 1.17);
	glVertex2f(-.419, 1.07);
	glVertex2f(-.419, .98);
	glVertex2f(-.419, .88);
	glVertex2f(-.419, .78);
	glVertex2f(-.50, .78);
	glVertex2f(-.5, .68);
	glVertex2f(-.5, .58);
	glVertex2f(-.32, .78);
	glVertex2f(-.32, .68);
	glVertex2f(-.41, .58);
	glVertex2f(-.41, .68);
	glVertex2f(-.41, .48);
	glVertex2f(-.32, .58);
	//
	glVertex2f(1.14, 1.82);
	glVertex2f(1.14, 1.91);
	glVertex2f(1.14, 2);
	glVertex2f(1.14, 2.09);
	glVertex2f(1.14, 2.18);

	glVertex2f(1.05, 1.73);
	glVertex2f(1.05, 1.64);
	glVertex2f(1.05, 1.55);
	glVertex2f(1.05, 1.46);
	glVertex2f(1.05, 1.37);
	glVertex2f(1.05, 1.28);
	glVertex2f(1.05, 1.19);

	glVertex2f(.95, 1.1);
	glVertex2f(.95, 1.);

	glVertex2f(.85, 1.);
	glVertex2f(.85, .9);

	glVertex2f(-1.03, 1.07);

	glVertex2f(-1.12, 0.98);
	glVertex2f(-1.12, 0.88);
	glVertex2f(-1.12, 0.78);
	glVertex2f(-1.12, 0.68);
	glVertex2f(-1.12, 0.58);
	glVertex2f(-1.12, 0.48);
	glVertex2f(-1.12, 0.38);
	glVertex2f(-1.12, 0.28);
	glVertex2f(-1.12, 0.18);
	glVertex2f(-1.03, 0.18);
	glVertex2f(-1.03, 0.08);
	glVertex2f(-1.03, -0.02);
	glVertex2f(-1.03, -0.12);
	glVertex2f(-1.03, -0.22);
	glVertex2f(-.940, -0.32);
	glVertex2f(-.94, -0.42);

	glVertex2f(.09, .87);
	glVertex2f(.0, .87);
	glVertex2f(-.09, .87);
	glVertex2f(-.15, .87);
	glVertex2f(-.15, .97);
	glVertex2f(-.15, 1.07);
	glVertex2f(-.06, .97);
	glEnd;
}

void foot() {
	glPointSize(4.0f);
	glBegin(GL_POINTS);
	glColor3f(0, 0, 0);
	glVertex2f(0.57, -1.32);
	glVertex2f(0.57, -1.42);
	glVertex2f(0.66, -1.52);
	glVertex2f(0.66, -1.62);
	glVertex2f(0.57, -1.62);
	glVertex2f(0.48, -1.62);
	glVertex2f(0.39, -1.62);
	glVertex2f(0.3, -1.62);
	glVertex2f(0.21, -1.62);
	glVertex2f(0.21, -1.52);
	glVertex2f(0.21, -1.42);
	glVertex2f(0.12, -1.42);
	glVertex2f(0.12, -1.32);
	glColor4f(0.2667, 0.2275, 0.2118, 1.0);

	glVertex2f(0.21, -1.42);
	glVertex2f(0.21, -1.32);
	glVertex2f(0.3, -1.42);
	glVertex2f(0.3, -1.32);
	glVertex2f(0.39, -1.42);
	glVertex2f(0.39, -1.32);
	glVertex2f(0.48, -1.42);
	glVertex2f(0.48, -1.32);

	glColor4f(0.3961, 0.3098, 0.3765, 1.0);

	glVertex2f(0.57, -1.52);
	glVertex2f(0.48, -1.52);
	glVertex2f(0.39, -1.52);
	glVertex2f(0.3, -1.52);
	glEnd();
}

void bodyt() {

	glBegin(GL_QUADS);
	glColor4f(214.0f / 255.0f, 197.0f / 255.0f, 153.0f / 255.0f, 1.0f);
	//l
	glVertex2f(.56, .83);
	glVertex2f(0.96, .13);
	glVertex2f(-.60, .13);
	glVertex2f(-.30, .83);

	glVertex2f(.96, .0);
	glVertex2f(01., -1.09);
	glVertex2f(-.890, -1.09);
	glVertex2f(-.30, .23);

	glVertex2f(.82, -.9);
	glVertex2f(0.82, -1.2);
	glVertex2f(-.60, -.9);
	glVertex2f(-.60, -1.2);

	glColor4f(0.467, 0.506, 0.603, 1.0);

	glVertex2f(.66, .33);
	glVertex2f(0.66, .03);
	glVertex2f(-.060, .03);
	glVertex2f(-.06, .33);
	glColor4f(0.302, 0.361, 0.482, 1.0);

	glVertex2f(.66, .03);
	glVertex2f(0.66, -.23);
	glVertex2f(-.060, -.23);
	glVertex2f(-.06, .03);

	//headacc
	glVertex2f(.14, 3.07);
	glVertex2f(.14, 1.77);
	glVertex2f(-.82, 1.77);
	glVertex2f(-.82, 3.07);

	glVertex2f(-.34, 2.7);
	glVertex2f(-.34, 1.17);
	glVertex2f(-1.09, 1.17);
	glVertex2f(-1.09, 2.7);


	glVertex2f(-.25, 2.83);
	glVertex2f(-.25, 1.17);
	glVertex2f(-1.0, 1.17);
	glVertex2f(-1.0, 2.83);


	glVertex2f(-.34, 2.6);
	glVertex2f(-.34, 1.27);
	glVertex2f(-1.18, 1.27);
	glVertex2f(-1.18, 2.6);


	glVertex2f(-.34, 2.5);
	glVertex2f(-.34, 1.37);
	glVertex2f(-1.27, 1.37);
	glVertex2f(-1.27, 2.5);

	glVertex2f(-.34, 2.3);
	glVertex2f(-.34, 1.37);
	glVertex2f(-1.36, 1.37);
	glVertex2f(-1.36, 2.3);

	glVertex2f(-.34, 2.2);
	glVertex2f(-.34, 1.47);
	glVertex2f(-1.45, 1.47);
	glVertex2f(-1.45, 2.2);

	glVertex2f(-.34, 2.);
	glVertex2f(-.34, 1.57);
	glVertex2f(-1.54, 1.57);
	glVertex2f(-1.54, 2.);
	glEnd;

}

void body() {
	glBegin(GL_POINTS);
	glColor3f(0, 0, 0);
	//right hand d
	glColor4f(0.2627, 0.1922, 0.1059, 1.0);

	glVertex2f(-0.75, -.82);
	glVertex2f(-0.84, -.92);//dreessleft
	glVertex2f(-0.84, -1.02);
	glVertex2f(-0.84, -1.12);
	glVertex2f(-0.75, -1.12);
	glVertex2f(-0.66, -1.12);

	glVertex2f(-0.57, -1.22);
	glVertex2f(-0.48, -1.22);
	glVertex2f(-0.39, -1.22);
	glVertex2f(-0.3, -1.22);
	glVertex2f(-0.21, -1.22);
	glVertex2f(-0.12, -1.22);
	glVertex2f(-0.03, -1.22);
	glVertex2f(0.06, -1.22);
	glVertex2f(0.12, -1.22);
	glVertex2f(0.21, -1.22);
	glVertex2f(0.3, -1.22);

	glVertex2f(0.39, -1.22);
	glVertex2f(0.48, -1.22);
	glVertex2f(0.57, -1.22);
	glVertex2f(0.66, -1.22);
	glVertex2f(0.75, -1.22);  //foot
	glVertex2f(0.84, -1.12);
	glVertex2f(0.93, -1.12);
	glVertex2f(1.03, -1.02);
	glVertex2f(1.03, -.95);
	glVertex2f(1.03, -.85);
	glVertex2f(1.03, -.75);

	glVertex2f(-0.12, .08);
	glVertex2f(-0.21, .08);
	glVertex2f(-0.30, .18);

	glVertex2f(-0.39, .18);
	glVertex2f(-0.48, .18);
	glVertex2f(-0.57, .18);
	glVertex2f(.827, .17);
	glVertex2f(.737, .17);
	glVertex2f(.917, .17);
	glVertex2f(.917, .27);
	glVertex2f(.827, .37);
	glVertex2f(.827, .47);
	glVertex2f(.737, .57);
	glVertex2f(.647, .67);
	//blue
	glVertex2f(.557, .77);
	glVertex2f(.38, .72);
	glVertex2f(.29, .72);
	glVertex2f(.2, .72);
	glVertex2f(.13, .72);
	glVertex2f(.11, .77);
	glVertex2f(.02, .77);

	glVertex2f(-.07, .77);
	glVertex2f(-.16, .77);
	glVertex2f(-.25, .77);
	glVertex2f(-.34, .67);
	glVertex2f(-.43, .57);
	glVertex2f(-.43, .47);
	glVertex2f(-.52, .37);
	glVertex2f(-.61, .27);
	glVertex2f(-.61, .17);

	glColor4f(0.1922f, 0.2549f, 0.3412f, 1.0f);
	glVertex2f(.08, .37);
	glVertex2f(.17, .37);
	glVertex2f(.26, .37);
	glVertex2f(.35, .37);
	glVertex2f(.44, .37);
	glVertex2f(.53, .37);
	glVertex2f(-00.03, .77);
	glVertex2f(-00.03, .67);
	glVertex2f(-00.03, .57);
	glVertex2f(-00.03, .47);
	glVertex2f(.08, .67);
	glVertex2f(.08, .57);
	glVertex2f(.08, .47);

	glVertex2f(-00.03, .37);
	glVertex2f(-00.03, .27);
	glVertex2f(-00.03, .17);
	glVertex2f(-00.03, .07);
	glVertex2f(0.06, .07);
	glVertex2f(0.69, .07);
	glVertex2f(0.51, .07);
	glVertex2f(0.6, .07);
	glVertex2f(0.69, .17);
	glVertex2f(0.69, .27);
	glVertex2f(0.6, -.02);
	glVertex2f(0.6, -.12);
	glVertex2f(0.51, -.22);
	glVertex2f(0.6, -.22);
	glVertex2f(0.42, -.22);
	glVertex2f(0.33, -.22);
	glVertex2f(0.24, -.22);
	glVertex2f(0.15, -.22);
	glVertex2f(0.06, -.22);
	glVertex2f(-0.03, -.22);
	glVertex2f(-0.12, -.22);
	glVertex2f(-0.12, -.12);
	glVertex2f(-0.12, -.02);

	//headacc            /////////////

	glColor4f(0.2627, 0.1922, 0.1059, 1.0);
	glVertex2f(-.76, 1.17);
	glVertex2f(-.85, 1.17);
	glVertex2f(-.94, 1.17);
	glVertex2f(-1.03, 1.17);
	glVertex2f(-1.03, 1.27);
	glVertex2f(-1.12, 1.27);
	glVertex2f(-1.21, 1.37);
	glVertex2f(-1.3, 1.37);
	glVertex2f(-1.39, 1.47);
	glVertex2f(-1.48, 1.57);
	glVertex2f(-1.57, 1.57);
	glVertex2f(-1.57, 1.67);
	glVertex2f(-1.57, 1.77);
	glVertex2f(-1.48, 1.87);
	glVertex2f(-1.48, 1.97);
	glVertex2f(-1.39, 2.07);
	glVertex2f(-1.39, 2.17);
	glVertex2f(-1.3, 2.27);
	glVertex2f(-1.21, 2.37);
	glVertex2f(-1.21, 2.47);
	glVertex2f(-1.12, 2.57);

	glVertex2f(-1.03, 2.67);
	glVertex2f(-.94, 2.77);
	glVertex2f(-.85, 2.87);
	glVertex2f(-.76, 2.97);
	glVertex2f(-.65, 2.97);
	glVertex2f(-.54, 3.07);
	glVertex2f(-.54, 3.07);
	glVertex2f(-.85, 2.87);

	glColor4f(0.1922f, 0.2549f, 0.3412f, 1.0f);

	glVertex2f(.47, .77);
	glVertex2f(.47, .67);
	glVertex2f(.557, .57);
	glVertex2f(.557, .47);
	glVertex2f(.647, .37);

	glColor4f(0.6745, 0.6392, 0.4902, 1.0);

	glVertex2f(-0.14, .19);
	glVertex2f(-0.21, .19);
	glVertex2f(-0.14, .29);
	glVertex2f(-0.21, .29);
	//
	glVertex2f(-0.21, -.01);
	glVertex2f(-0.21, -.11);
	glVertex2f(-0.21, -.21);
	glVertex2f(-0.3, -.21);
	glVertex2f(-0.3, -.31);
	glVertex2f(.81, .27);
	glVertex2f(.82, .17);
}

void mother() {
	bodyt();
	hairc();
	body();
	hair();
	foot();
	hand();
	eyes();
	face();
	glTranslatef(-0.60, -0.10, 0.0);
	foot();
}
void tree()
{

	glPointSize(20.0f);
	glBegin(GL_POINTS);
	glColor3f(0.1059f, 0.1451f, 0.1490f);
	glVertex2f(0.0031957349159, 0.8424513464816);
	glVertex2f(-0.0722499156368, 0.8424513464816);
	glVertex2f(-0.1507093743189, 0.8424513464816);

	glVertex2f(0.0763006618024, 0.7808893027877);

	glVertex2f(0.1291409702678, 0.7286507092189);
	glVertex2f(0.0763006618024, 0.7286507092189);
	glVertex2f(0.203770840375, 0.7852543747463);
	glVertex2f(0.2796250381809, 0.7852543747463);
	glVertex2f(0.3585753256932, 0.7852543747463);
	glVertex2f(0.4230343451221, 0.7243803124463);
	glVertex2f(0.4230343451221, 0.6724493072168);
	glVertex2f(0.4852085779266, 0.5968180855682);

	glVertex2f(0.4852085779266, 0.5155035287369);
	glVertex2f(0.4852085779266, 0.4441458564156);
	glVertex2f(0.5465821569684, 0.3647481438009);
	glVertex2f(0.5465821569684, 0.2873984706723);
	glVertex2f(0.5465821569684, 0.2132717005908);
	glVertex2f(0.4868709654128, 0.1440312183928);
	glVertex2f(0.4868709654128, 0.0934806725526);
	glVertex2f(0.4250244209523, 0.0299256436229);

	glVertex2f(0.2935078586573, -0.0300984145351);
	glVertex2f(0.2467658892981, -0.0300984145351);
	glVertex2f(0.1856417755207, -0.0300984145351);

	glVertex2f(0.1353042700569, -0.0912225283125);
	glVertex2f(0.1353042700569, -0.1469533379331);
	glVertex2f(0.1353042700569, -0.1972908433969);
	glVertex2f(0.2024669208655, -0.2743385105407);
	glVertex2f(0.2024669208655, -0.3279389643308);
	glVertex2f(0.2024669208655, -0.3834201357978);

	glVertex2f(0.1262978549532, -0.3834201357978);
	glVertex2f(0.0576516597483, -0.3834201357978);
	glVertex2f(-0.0015909470724, -0.3834201357978);
	glVertex2f(-0.056131759701, -0.3834201357978);
	glVertex2f(-0.0909250367226, -0.3834201357978);
	glVertex2f(0.0576516597483, -0.3834201357978);
	glVertex2f(-0.1230493904287, -0.3834201357978);

	glVertex2f(-0.1353042700569, -0.0912225283125);
	glVertex2f(-0.1353042700569, -0.1469533379331);
	glVertex2f(-0.1353042700569, -0.1972908433969);
	glVertex2f(-0.2024669208655, -0.2743385105407);

	glVertex2f(-0.2024669208655, -0.3279389643308);
	glVertex2f(-0.2024669208655, -0.3834201357978);

	glVertex2f(-0.203770840375, 0.7852543747463);
	glVertex2f(-0.2796250381809, 0.7852543747463);
	glVertex2f(-0.3585753256932, 0.7852543747463);
	glVertex2f(-0.4230343451221, 0.7243803124463);
	glVertex2f(-0.4230343451221, 0.6724493072168);
	glVertex2f(-0.4852085779266, 0.5968180855682);

	glVertex2f(-0.4852085779266, 0.5155035287369);
	glVertex2f(-0.4852085779266, 0.4441458564156);
	glVertex2f(-0.5465821569684, 0.3647481438009);
	glVertex2f(-0.5465821569684, 0.2873984706723);
	glVertex2f(-0.5465821569684, 0.2132717005908);
	glVertex2f(-0.4868709654128, 0.1440312183928);
	glVertex2f(-0.4868709654128, 0.0934806725526);
	glVertex2f(-0.4250244209523, 0.0299256436229);
	//A,Z,W
	glVertex2f(-0.2935078586573, -0.0300984145351);
	glVertex2f(-0.2467658892981, -0.0300984145351);
	glVertex2f(-0.1856417755207, -0.0300984145351);

	//الجذعbrown
	glColor3f(0.6275f, 0.4471f, 0.3176f);
	glVertex2f(0.056228435491, -0.0912225283125);
	glVertex2f(-0.056228435491, -0.0912225283125);
	glVertex2f(0.0171131392121, -0.0912225283125);
	glVertex2f(0.056228435491, -0.1469533379331);
	glVertex2f(-0.056228435491, -0.1469533379331);
	glVertex2f(0.0171131392121, -0.1469533379331);
	glVertex2f(0.056228435491, -0.1972908433969);
	glVertex2f(-0.056228435491, -0.1972908433969);
	glVertex2f(0.0171131392121, -0.1972908433969);
	glVertex2f(0.1262978549532, -0.2743385105407);
	glVertex2f(0.0576516597483, -0.2743385105407);
	glVertex2f(-0.0015909470724, -0.2743385105407);
	glVertex2f(-0.056131759701, -0.2743385105407);
	glVertex2f(-0.0909250367226, -0.2743385105407);
	glVertex2f(0.0576516597483, -0.2743385105407);
	glVertex2f(-0.1230493904287, -0.2743385105407);
	glVertex2f(0.1262978549532, -0.303);
	glVertex2f(0.0576516597483, -0.303);
	glVertex2f(-0.0015909470724, -0.303);
	glVertex2f(-0.056131759701, -0.303);
	glVertex2f(-0.0909250367226, -0.303);
	glVertex2f(0.0576516597483, -0.303);
	glVertex2f(-0.1230493904287, -0.303);
	//
	//q,r,s,t,u>1 tree fill in
	glColor3f(0.2824f, 0.4392f, 0.1961f);
	glVertex2f(0.1353042700569, -0.0300984145351);
	glVertex2f(0.056228435491, -0.0300984145351);
	glVertex2f(0.0171131392121, -0.0300984145351);
	glVertex2f(-0.0300949769865, -0.0300984145351);
	glVertex2f(-0.11, -0.0300984145351);
	glVertex2f(0.3427906028501, 0.0299256436229);
	glVertex2f(0.056228435491, 0.0299256436229);
	glVertex2f(0.0171131392121, 0.0299256436229);
	glVertex2f(0.1353042700569, 0.0299256436229);
	glVertex2f(-0.0300949769865, 0.0299256436229);
	glVertex2f(-0.11, 0.0299256436229);
	glVertex2f(-0.2935078586573, 0.0299256436229);
	glVertex2f(-0.2467658892981, 0.0299256436229);
	glVertex2f(-0.1856417755207, 0.0299256436229);
	glVertex2f(0.2935078586573, 0.0299256436229);
	glVertex2f(0.2467658892981, 0.0299256436229);
	glVertex2f(0.1856417755207, 0.0299256436229);
	glVertex2f(-0.3427906028501, 0.0299256436229);

	glVertex2f(0.3427906028501, 0.0934806725526);
	glVertex2f(0.056228435491, 0.0934806725526);
	glVertex2f(0.0171131392121, 0.0934806725526);
	glVertex2f(0.1353042700569, 0.0934806725526);
	glVertex2f(-0.0300949769865, 0.0934806725526);
	glVertex2f(-0.11, 0.0934806725526);
	glVertex2f(-0.2935078586573, 0.09348067255269);
	glVertex2f(-0.2467658892981, 0.0934806725526);
	glVertex2f(-0.1856417755207, 0.0934806725526);
	glVertex2f(0.2935078586573, 0.0934806725526);
	glVertex2f(0.2467658892981, 0.0934806725526);
	glVertex2f(0.1856417755207, 0.0934806725526);
	glVertex2f(-0.3427906028501, 0.0934806725526);
	glVertex2f(0.41, 0.0934806725526);
	glVertex2f(-0.41, 0.0934806725526);

	glVertex2f(0.3427906028501, 0.1440312183928);
	glVertex2f(0.056228435491, 0.1440312183928);
	glVertex2f(0.0171131392121, 0.1440312183928);
	glVertex2f(0.1353042700569, 0.1440312183928);
	glVertex2f(-0.0300949769865, 0.1440312183928);
	glVertex2f(-0.11, 0.1440312183928);
	glVertex2f(-0.2935078586573, 0.1440312183928);
	glVertex2f(-0.2467658892981, 0.1440312183928);
	glVertex2f(-0.1856417755207, 0.1440312183928);
	glVertex2f(0.2935078586573, 0.1440312183928);
	glVertex2f(0.2467658892981, 0.1440312183928);
	glVertex2f(0.1856417755207, 0.1440312183928);
	glVertex2f(-0.3427906028501, 0.1440312183928);
	glVertex2f(0.41, 0.1440312183928);
	glVertex2f(-0.41, 0.1440312183928);

	glVertex2f(0.3427906028501, 0.2132717005908);
	glVertex2f(0.056228435491, 0.2132717005908);
	glVertex2f(0.0171131392121, 0.2132717005908);
	glVertex2f(0.1353042700569, 0.2132717005908);
	glVertex2f(-0.0300949769865, 0.2132717005908);
	glVertex2f(-0.11, 0.2132717005908);
	glVertex2f(-0.2935078586573, 0.2132717005908);
	glVertex2f(-0.2467658892981, 0.2132717005908);
	glVertex2f(-0.1856417755207, 0.2132717005908);
	glVertex2f(0.2935078586573, 0.2132717005908);
	glVertex2f(0.2467658892981, 0.2132717005908);
	glVertex2f(0.1856417755207, 0.2132717005908);
	glVertex2f(-0.3427906028501, 0.2132717005908);
	glVertex2f(0.41, 0.2132717005908);
	glVertex2f(-0.41, 0.2132717005908);
	glVertex2f(0.47, 0.2132717005908);
	glVertex2f(-0.47, 0.2132717005908);


	glVertex2f(0.3427906028501, 0.2873984706723);
	glVertex2f(0.056228435491, 0.2873984706723);
	glVertex2f(0.0171131392121, 0.2873984706723);
	glVertex2f(0.1353042700569, 0.2873984706723);
	glVertex2f(-0.0300949769865, 0.2873984706723);
	glVertex2f(-0.11, 0.2873984706723);
	glVertex2f(-0.2935078586573, 0.2873984706723);
	glVertex2f(-0.2467658892981, 0.2873984706723);
	glVertex2f(-0.1856417755207, 0.2873984706723);
	glVertex2f(0.2935078586573, 0.2873984706723);
	glVertex2f(0.2467658892981, 0.2873984706723);
	glVertex2f(0.1856417755207, 0.2873984706723);
	glVertex2f(-0.3427906028501, 0.2873984706723);
	glVertex2f(0.41, 0.2873984706723);
	glVertex2f(-0.41, 0.2873984706723);
	glVertex2f(0.47, 0.2873984706723);
	glVertex2f(-0.47, 0.2873984706723);

	glVertex2f(0.3427906028501, 0.3647481438009);
	glVertex2f(0.056228435491, 0.3647481438009);
	glVertex2f(0.0171131392121, 0.3647481438009);
	glVertex2f(0.1353042700569, 0.3647481438009);
	glVertex2f(-0.0300949769865, 0.3647481438009);

	glVertex2f(-0.11, 0.4441458564156);
	glVertex2f(-0.2935078586573, 0.4441458564156);
	glVertex2f(-0.2467658892981, 0.4441458564156);
	glVertex2f(-0.1856417755207, 0.4441458564156);
	glVertex2f(0.2935078586573, 0.4441458564156);
	glVertex2f(0.2467658892981, 0.4441458564156);
	glVertex2f(0.1856417755207, 0.4441458564156);
	glVertex2f(-0.3427906028501, 0.4441458564156);
	glVertex2f(0.41, 0.4441458564156);
	glVertex2f(-0.41, 0.4441458564156);

	glVertex2f(0.3427906028501, 0.5155035287369);
	glVertex2f(0.056228435491, 0.5155035287369);
	glVertex2f(0.0171131392121, 0.5155035287369);
	glVertex2f(0.1353042700569, 0.5155035287369);
	glVertex2f(-0.0300949769865, 0.5155035287369);
	glVertex2f(-0.11, 0.5155035287369);
	glVertex2f(-0.2935078586573, 0.5155035287369);
	glVertex2f(-0.2467658892981, 0.5155035287369);
	glVertex2f(-0.1856417755207, 0.5155035287369);
	glVertex2f(0.2935078586573, 0.5155035287369);
	glVertex2f(0.2467658892981, 0.5155035287369);
	glVertex2f(0.1856417755207, 0.5155035287369);
	glVertex2f(-0.3427906028501, 0.5155035287369);
	glVertex2f(0.41, 0.5155035287369);
	glVertex2f(-0.41, 0.5155035287369);

	glVertex2f(0.3427906028501, 0.5968180855682);
	glVertex2f(0.056228435491, 0.5968180855682);
	glVertex2f(0.0171131392121, 0.5968180855682);
	glVertex2f(0.1353042700569, 0.5968180855682);
	glVertex2f(-0.0300949769865, 0.5968180855682);
	glVertex2f(-0.11, 0.5968180855682);
	glVertex2f(-0.2935078586573, 0.5968180855682);
	glVertex2f(-0.2467658892981, 0.5968180855682);
	glVertex2f(-0.1856417755207, 0.5968180855682);
	glVertex2f(0.2935078586573, 0.5968180855682);
	glVertex2f(0.2467658892981, 0.5968180855682);
	glVertex2f(0.1856417755207, 0.5968180855682);
	glVertex2f(-0.3427906028501, 0.5968180855682);
	glVertex2f(0.41, 0.5968180855682);
	glVertex2f(-0.41, 0.5968180855682);


	glVertex2f(0.3427906028501, 0.65);
	glVertex2f(0.056228435491, 0.65);
	glVertex2f(0.0171131392121, 0.65);
	glVertex2f(0.1353042700569, 0.65);
	glVertex2f(-0.0300949769865, 0.65);
	glVertex2f(-0.11, 0.65);
	glVertex2f(-0.2935078586573, 0.65);
	glVertex2f(-0.2467658892981, 0.65);
	glVertex2f(-0.11, 0.3647481438009);
	glVertex2f(-0.2935078586573, 0.3647481438009);
	glVertex2f(-0.2467658892981, 0.3647481438009);
	glVertex2f(-0.1856417755207, 0.3647481438009);
	glVertex2f(0.2935078586573, 0.3647481438009);
	glVertex2f(0.2467658892981, 0.3647481438009);
	glVertex2f(0.1856417755207, 0.3647481438009);
	glVertex2f(-0.3427906028501, 0.3647481438009);
	glVertex2f(0.41, 0.3647481438009);
	glVertex2f(-0.41, 0.3647481438009);
	glVertex2f(0.47, 0.3647481438009);
	glVertex2f(-0.47, 0.3647481438009);

	glVertex2f(0.3427906028501, 0.4441458564156);
	glVertex2f(0.056228435491, 0.4441458564156);
	glVertex2f(0.0171131392121, 0.4441458564156);
	glVertex2f(0.1353042700569, 0.4441458564156);
	glVertex2f(-0.0300949769865, 0.4441458564156);

	glVertex2f(-0.11, 0.65);
	glVertex2f(-0.2935078586573, 0.65);
	glVertex2f(-0.2467658892981, 0.65);
	glVertex2f(-0.1856417755207, 0.65);
	glVertex2f(0.2935078586573, 0.65);
	glVertex2f(0.2467658892981, 0.65);
	glVertex2f(0.1856417755207, 0.65);
	glVertex2f(-0.3427906028501, 0.65);


	glVertex2f(-0.3427906028501, 0.72);
	glVertex2f(-0.1856417755207, 0.72);
	glVertex2f(-0.2467658892981, 0.72);
	glVertex2f(-0.2935078586573, 0.72);
	glVertex2f(-0.1353042700569, 0.73);
	glColor3f(0.3922f, 0.5412f, 0.2392f);

	glVertex2f(0.35, 0.677);
	glVertex2f(0.2796250381809, 0.677);
	glVertex2f(0.203770840375, 0.677);
	glVertex2f(0.35, 0.703);
	glVertex2f(0.2796250381809, 0.703);
	glVertex2f(0.203770840375, 0.703);

	glVertex2f(-0.3427906028501, 0.72);
	glVertex2f(-0.1856417755207, 0.72);
	glVertex2f(-0.2467658892981, 0.72);
	glVertex2f(-0.2935078586573, 0.72);
	glVertex2f(-0.1353042700569, 0.73);
	glVertex2f(-0.0171131392121, 0.73);
	glVertex2f(-0.056228435491, 0.73);
	glVertex2f(-0.3427906028501, 0.72);
	glVertex2f(0.0001, 0.73);
	glVertex2f(-0.1353042700569, 0.77);
	glVertex2f(-0.00101131392121, 0.77);
	glVertex2f(-0.056228435491, 0.77);
	glVertex2f(-0.056228435491, 0.77);
	glEnd();
}
void bush()
{
	glPointSize(10.0f);
	glBegin(GL_POINTS);
	glColor3f(0.1059f, 0.1451f, 0.1490f);
	glVertex2f(-0.2620337741632, -0.2860608372172);
	glVertex2f(-0.3051764496952, -0.2860608372172);
	glVertex2f(-0.3383631231813, -0.3275441790748);
	glVertex2f(-0.3770481646636, -0.3642901286609);
	glVertex2f(-0.3396010043923, -0.4019958040929);
	glVertex2f(-0.301986999999, -0.4019958040929);
	glVertex2f(-0.26, -0.4019958040929);
	glColor3f(0.2824f, 0.4392f, 0.1961f);

	glVertex2f(-0.3383631231813, -0.3642901286609);
	glVertex2f(-0.3016368137994, -0.3642901286609);
	glVertex2f(-0.26, -0.3642901286609);
	glVertex2f(-0.3016368137994, -0.3275441790748);
	glVertex2f(-0.26, -0.3275441790748);

	glEnd();
}
void tree1()
{
	glPointSize(20.0f);
	glBegin(GL_POINTS);
	glColor3f(0.0f, 0.0f, .0f);
	//تحديد
	glVertex2f(0.1353042700569, -0.0912225283125);
	glVertex2f(0.1353042700569, -0.1469533379331);
	glVertex2f(0.1353042700569, -0.1972908433969);
	glVertex2f(0.2024669208655, -0.2743385105407);
	glVertex2f(0.2024669208655, -0.3279389643308);
	glVertex2f(0.2024669208655, -0.3834201357978);
	glVertex2f(0.1262978549532, -0.3834201357978);
	glVertex2f(0.0576516597483, -0.3834201357978);
	glVertex2f(-0.0015909470724, -0.3834201357978);
	glVertex2f(-0.056131759701, -0.3834201357978);
	glVertex2f(-0.0909250367226, -0.3834201357978);
	glVertex2f(0.0576516597483, -0.3834201357978);
	glVertex2f(-0.1230493904287, -0.3834201357978);
	glVertex2f(-0.1353042700569, -0.0912225283125);
	glVertex2f(-0.1353042700569, -0.1469533379331);
	glVertex2f(-0.1353042700569, -0.1972908433969);
	glVertex2f(-0.2024669208655, -0.2743385105407);
	glVertex2f(-0.2024669208655, -0.3279389643308);
	glVertex2f(-0.2024669208655, -0.3834201357978);



	//الجذع
	glColor3f(0.3f, 0.2f, .0f);
	glVertex2f(0.056228435491, -0.0912225283125);
	glVertex2f(-0.056228435491, -0.0912225283125);
	glVertex2f(0.0171131392121, -0.0912225283125);
	glVertex2f(0.056228435491, -0.1469533379331);
	glVertex2f(-0.056228435491, -0.1469533379331);
	glVertex2f(0.0171131392121, -0.1469533379331);
	glVertex2f(0.056228435491, -0.1972908433969);
	glVertex2f(-0.056228435491, -0.1972908433969);
	glVertex2f(0.0171131392121, -0.1972908433969);
	glVertex2f(0.1262978549532, -0.2743385105407);
	glVertex2f(0.0576516597483, -0.2743385105407);
	glVertex2f(-0.0015909470724, -0.2743385105407);
	glVertex2f(-0.056131759701, -0.2743385105407);
	glVertex2f(-0.0909250367226, -0.2743385105407);
	glVertex2f(0.0576516597483, -0.2743385105407);
	glVertex2f(-0.1230493904287, -0.2743385105407);
	glVertex2f(0.1262978549532, -0.303);
	glVertex2f(0.0576516597483, -0.303);
	glVertex2f(-0.0015909470724, -0.303);
	glVertex2f(-0.056131759701, -0.303);
	glVertex2f(-0.0909250367226, -0.303);
	glVertex2f(0.0576516597483, -0.303);
	glVertex2f(-0.1230493904287, -0.303);
	//leafs bottom line
	glColor3f(0.0f, 0.0f, .0f);
	glVertex2f(-0.3, -0.0101);
	glVertex2f(-0.2255815247019, -0.0101);
	glVertex2f(-0.15, -0.0101);
	glVertex2f(0.2284813704787, -0.0101);
	glVertex2f(0.1567438619528, -0.0101);
	glVertex2f(0.3, -0.0101);
	glVertex2f(0.3678151227693, -0.0101);
	glVertex2f(0.4302750806927, -0.0101);
	glVertex2f(0.5, -0.0101);
	glVertex2f(0.5660053738723, -0.0101);
	glVertex2f(0.6308676378696, -0.0101);
	glColor3f(0.0f, 0.4f, .0f);
	glVertex2f(0.079268232939, -0.0101);
	glVertex2f(0, -0.0101);
	glVertex2f(-0.0747741819204, -0.0101);
	//first layer of color
	glColor3f(0.0f, 0.4f, .0f);
	glVertex2f(-0.3, 0.0519113705434);
	glVertex2f(-0.2255815247019, 0.0519113705434);
	glVertex2f(-0.15, 0.0519113705434);
	glVertex2f(0.2284813704787, 0.0519113705434);
	glVertex2f(0.1567438619528, 0.0519113705434);
	glVertex2f(0.3, 0.0519113705434);
	glVertex2f(0.3678151227693, 0.0519113705434);
	glVertex2f(0.4302750806927, 0.0519113705434);
	glVertex2f(0.5, 0.0519113705434);
	glVertex2f(0.5660053738723, 0.0519113705434);
	glVertex2f(0.6308676378696, 0.0519113705434);
	glVertex2f(0.079268232939, 0.0519113705434);
	glVertex2f(0, 0.0519113705434);
	glVertex2f(-0.0747741819204, 0.0519113705434);
	//2nd layer of color
	glColor3f(0.0f, 0.4f, .0f);
	glVertex2f(-0.3, 0.129250475244);
	glVertex2f(-0.2255815247019, 0.129250475244);
	glVertex2f(-0.15, 0.129250475244);
	glVertex2f(0.2284813704787, 0.129250475244);
	glVertex2f(0.1567438619528, 0.129250475244);
	glVertex2f(0.3, 0.129250475244);
	glVertex2f(0.3678151227693, 0.129250475244);
	glVertex2f(0.4302750806927, 0.129250475244);
	glVertex2f(0.5, 0.129250475244);
	glVertex2f(0.5660053738723, 0.129250475244);
	glVertex2f(0.6308676378696, 0.129250475244);
	glVertex2f(0.079268232939, 0.129250475244);
	glVertex2f(0, 0.129250475244);
	glVertex2f(-0.0747741819204, 0.129250475244);
	glVertex2f(-0.3639154440927, 0.129250475244);
	glVertex2f(-0.4211342157906, 0.129250475244);
	glVertex2f(-0.4763094599278, 0.129250475244);
	//3d layer
	glColor3f(0.0f, 0.4f, .0f);
	glVertex2f(-0.3, 0.2049272094298);
	glVertex2f(-0.2255815247019, 0.2049272094298);
	glVertex2f(-0.15, 0.2049272094298);
	glVertex2f(0.2284813704787, 0.2049272094298);
	glVertex2f(0.1567438619528, 0.2049272094298);
	glVertex2f(0.3, 0.2049272094298);
	glVertex2f(0.3678151227693, 0.2049272094298);
	glVertex2f(0.4302750806927, 0.2049272094298);
	glVertex2f(0.5, 0.2049272094298);
	glVertex2f(0.5660053738723, 0.2049272094298);
	glVertex2f(0.4308676378696, 0.2049272094298);
	glVertex2f(0.079268232939, 0.2049272094298);
	glVertex2f(0, 0.2049272094298);
	glVertex2f(-0.0747741819204, 0.2049272094298);
	glVertex2f(-0.3639154440927, 0.2049272094298);
	glVertex2f(-0.4211342157906, 0.2049272094298);
	glVertex2f(-0.4763094599278, 0.2049272094298);
	//4th layer
	glColor3f(0.0f, 0.4f, .0f);
	glVertex2f(-0.3, 0.2469260364693);
	glVertex2f(-0.2255815247019, 0.2469260364693);
	glVertex2f(-0.15, 0.2469260364693);
	glVertex2f(0.2284813704787, 0.2469260364693);
	glVertex2f(0.1567438619528, 0.2469260364693);
	glVertex2f(0.3, 0.2469260364693);
	glVertex2f(0.3678151227693, 0.2469260364693);
	glVertex2f(0.4302750806927, 0.2469260364693);
	glVertex2f(0.5, 0.2469260364693);
	glVertex2f(0.5660053738723, 0.2469260364693);
	glVertex2f(0.4308676378696, 0.2469260364693);
	glVertex2f(0.079268232939, 0.2469260364693);
	glVertex2f(0, 0.2469260364693);
	glVertex2f(-0.0747741819204, 0.2469260364693);
	glVertex2f(-0.3639154440927, 0.2469260364693);
	glVertex2f(-0.4211342157906, 0.2469260364693);
	glVertex2f(-0.4763094599278, 0.2469260364693);
	//5th layer color
	glColor3f(0.0f, 0.4f, .0f);
	glVertex2f(-0.3, 0.3289083761095);
	glVertex2f(-0.2255815247019, 0.3289083761095);
	glVertex2f(-0.15, 0.3289083761095);
	glVertex2f(0.2284813704787, 0.3289083761095);
	glVertex2f(0.1567438619528, 0.3289083761095);
	glVertex2f(0.3, 0.3289083761095);
	glVertex2f(0.3678151227693, 0.3289083761095);
	glVertex2f(0.4302750806927, 0.3289083761095);
	glVertex2f(0.45, 0.3289083761095);
	//6th
	glColor3f(0.0f, 0.4f, .0f);
	glVertex2f(-0.29, 0.408);
	glVertex2f(-0.2255815247019, 0.34);
	glVertex2f(-0.15, 0.32);
	glVertex2f(0.2284813704787, 0.4099731349307);
	glVertex2f(0.1567438619528, 0.4099731349307);
	glVertex2f(0.3, 0.4099731349307);
	glVertex2f(0.3678151227693, 0.4099731349307);
	glVertex2f(0.4302750806927, 0.4099731349307);
	glVertex2f(-0.103, 0.4099731349307);
	glVertex2f(0.4308676378696, 0.4099731349307);
	glVertex2f(0.079268232939, 0.4099731349307);
	glVertex2f(0, 0.4099731349307);
	glVertex2f(-0.0747741819204, 0.4099731349307);
	glVertex2f(-0.3639154440927, 0.2469260364693);
	glVertex2f(-0.4211342157906, 0.2469260364693);
	glVertex2f(-0.4763094599278, 0.2469260364693);
	// glVertex2f(0.5660053738723, 0.3289083761095);
	glVertex2f(0.4308676378696, 0.3289083761095);
	glVertex2f(0.079268232939, 0.3289083761095);
	glVertex2f(0, 0.3289083761095);
	glVertex2f(-0.0747741819204, 0.3289083761095);
	glVertex2f(-0.3639154440927, 0.3289083761095);
	glVertex2f(-0.401, 0.31);
	glVertex2f(0.2735296266778, 0.484777729795);
	glVertex2f(0.2014326295041, 0.484777729795);
	glVertex2f(0.1475880366782, 0.484777729795);
	glVertex2f(0.1059910927791, 0.484777729795);

	//leafs other side
	glColor3f(0.0f, 0.0f, .0f);
	glVertex2f(-0.3639154440927, 0.0519113705434);
	glVertex2f(-0.4211342157906, 0.0519113705434);
	glVertex2f(-0.4763094599278, 0.0519113705434);
	glVertex2f(-0.5297835498475, 0.129250475244);
	glVertex2f(-0.5297835498475, 0.2049272094298);
	glVertex2f(-0.5297835498475, 0.2469260364693);
	glVertex2f(-0.4739272953739, 0.305424938262);

	glVertex2f(0.6866930407535, 0.0521185159194);
	glVertex2f(0.6866930407535, 0.1311937879271);
	glVertex2f(0.6284530967555, 0.1856656633027);
	glVertex2f(0.5667022350788, 0.2439859215529);
	glVertex2f(0.5169584853948, 0.3023061798031);
	glVertex2f(0.4517770202916, 0.3606264380533);
	glVertex2f(0.4517770202916, 0.4189466963035);
	glVertex2f(0.3919173999355, 0.4779121170047);
	glVertex2f(0.3357781773825, 0.4779121170047);
	glVertex2f(0.2735296266778, 0.5332520417348);
	glVertex2f(0.2014326295041, 0.5332520417348);
	glVertex2f(0.1475880366782, 0.5332520417348);
	glVertex2f(0.0537600894568, 0.484777729795);
	glVertex2f(0.1059910927791, 0.5332520417348);
	glVertex2f(-0.41776181063, 0.3590494289026);
	glVertex2f(-0.3641161184045, 0.3590494289026);

	glVertex2f(-0.2970590031226, 0.4180596903507);
	glVertex2f(-0.2434133108971, 0.4180596903507);
	glVertex2f(-0.1857441917547, 0.3590494289026);
	glVertex2f(-0.1039345111108, 0.4234242595732);
	glVertex2f(-0.066382526553, 0.4234242595732);
	glVertex2f(-0.0113956920219, 0.4234242595732);

	glEnd();
}
void tree2()
{
	glPointSize(20.0f);
	glBegin(GL_POINTS);
	glColor3f(0.0f, 0.0f, .0f);
	//تحديد
	glVertex2f(0.1353042700569, -0.0912225283125);
	glVertex2f(0.1353042700569, -0.1469533379331);
	glVertex2f(0.1353042700569, -0.1972908433969);
	glVertex2f(0.2024669208655, -0.2743385105407);
	glVertex2f(0.2024669208655, -0.3279389643308);
	glVertex2f(0.2024669208655, -0.3834201357978);
	glVertex2f(0.1262978549532, -0.3834201357978);
	glVertex2f(0.0576516597483, -0.3834201357978);
	glVertex2f(-0.0015909470724, -0.3834201357978);
	glVertex2f(-0.056131759701, -0.3834201357978);
	glVertex2f(-0.0909250367226, -0.3834201357978);
	glVertex2f(0.0576516597483, -0.3834201357978);
	glVertex2f(-0.1230493904287, -0.3834201357978);
	glVertex2f(-0.1353042700569, -0.0912225283125);
	glVertex2f(-0.1353042700569, -0.1469533379331);
	glVertex2f(-0.1353042700569, -0.1972908433969);
	glVertex2f(-0.2024669208655, -0.2743385105407);
	glVertex2f(-0.2024669208655, -0.3279389643308);
	glVertex2f(-0.2024669208655, -0.3834201357978);



	//الجذع
	glColor3f(0.3f, 0.2f, .0f);
	glVertex2f(0.056228435491, -0.0912225283125);
	glVertex2f(-0.056228435491, -0.0912225283125);
	glVertex2f(0.0171131392121, -0.0912225283125);
	glVertex2f(0.056228435491, -0.1469533379331);
	glVertex2f(-0.056228435491, -0.1469533379331);
	glVertex2f(0.0171131392121, -0.1469533379331);
	glVertex2f(0.056228435491, -0.1972908433969);
	glVertex2f(-0.056228435491, -0.1972908433969);
	glVertex2f(0.0171131392121, -0.1972908433969);
	glVertex2f(0.1262978549532, -0.2743385105407);
	glVertex2f(0.0576516597483, -0.2743385105407);
	glVertex2f(-0.0015909470724, -0.2743385105407);
	glVertex2f(-0.056131759701, -0.2743385105407);
	glVertex2f(-0.0909250367226, -0.2743385105407);
	glVertex2f(0.0576516597483, -0.2743385105407);
	glVertex2f(-0.1230493904287, -0.2743385105407);
	glVertex2f(0.1262978549532, -0.303);
	glVertex2f(0.0576516597483, -0.303);
	glVertex2f(-0.0015909470724, -0.303);
	glVertex2f(-0.056131759701, -0.303);
	glVertex2f(-0.0909250367226, -0.303);
	glVertex2f(0.0576516597483, -0.303);
	glVertex2f(-0.1230493904287, -0.303);
	//leafs bottom line
	glColor3f(0.0f, 0.0f, .0f);
	glVertex2f(-0.3, -0.0101);
	glVertex2f(-0.2255815247019, -0.0101);
	glVertex2f(-0.15, -0.0101);
	glVertex2f(0.2284813704787, -0.0101);
	glVertex2f(0.1567438619528, -0.0101);
	glVertex2f(0.3, -0.0101);
	glColor3f(0.0f, 0.4f, .0f);
	glVertex2f(0.079268232939, -0.0101);
	glVertex2f(0, -0.0101);
	glVertex2f(-0.0747741819204, -0.0101);

	//1st layer color
	glColor3f(0.0f, 0.4f, .0f);

	glColor3f(0.0f, 0.4f, .0f);
	glVertex2f(-0.3, 0.129250475244);
	glVertex2f(-0.2255815247019, 0.129250475244);
	glVertex2f(-0.15, 0.129250475244);
	glVertex2f(0.2284813704787, 0.129250475244);
	glVertex2f(0.1567438619528, 0.129250475244);
	glVertex2f(0.3, 0.129250475244);
	glVertex2f(0.079268232939, 0.129250475244);
	glVertex2f(0, 0.129250475244);
	glVertex2f(-0.0747741819204, 0.129250475244);
	//2nd
	glColor3f(0.0f, 0.4f, .0f);
	glVertex2f(-0.3, 0.0519113705434);
	glVertex2f(-0.2255815247019, 0.0519113705434);
	glVertex2f(-0.15, 0.0519113705434);
	glVertex2f(0.2284813704787, 0.0519113705434);
	glVertex2f(0.1567438619528, 0.0519113705434);
	glVertex2f(0.3, 0.0519113705434);
	glVertex2f(0.079268232939, 0.0519113705434);
	glVertex2f(0, 0.0519113705434);
	glVertex2f(-0.0747741819204, 0.0519113705434);
	glVertex2f(-0.3639154440927, 0.129250475244);
	glVertex2f(-0.4211342157906, 0.129250475244);
	glVertex2f(-0.4763094599278, 0.129250475244);
	glVertex2f(0.3639154440927, 0.129250475244);
	glVertex2f(0.4211342157906, 0.129250475244);
	glVertex2f(0.4763094599278, 0.129250475244);
	//3rd
	glColor3f(0.0f, 0.4f, .0f);
	glVertex2f(-0.3, 0.2049272094298);
	glVertex2f(-0.2255815247019, 0.2049272094298);
	glVertex2f(-0.15, 0.2049272094298);
	glVertex2f(0.2284813704787, 0.2049272094298);
	glVertex2f(0.1567438619528, 0.2049272094298);
	glVertex2f(0.3, 0.2049272094298);
	glVertex2f(0.079268232939, 0.2049272094298);
	glVertex2f(0, 0.2049272094298);
	glVertex2f(-0.0747741819204, 0.2049272094298);
	glVertex2f(-0.3639154440927, 0.2049272094298);
	glVertex2f(-0.4211342157906, 0.2049272094298);
	glVertex2f(-0.4763094599278, 0.2049272094298);
	glVertex2f(0.3639154440927, 0.2049272094298);
	glVertex2f(0.4211342157906, 0.2049272094298);
	glVertex2f(0.4763094599278, 0.2049272094298);
	//4th
	glColor3f(0.0f, 0.4f, .0f);
	glVertex2f(-0.3, 0.2469260364693);
	glVertex2f(-0.2255815247019, 0.2469260364693);
	glVertex2f(-0.15, 0.2469260364693);
	glVertex2f(0.2284813704787, 0.2469260364693);
	glVertex2f(0.1567438619528, 0.2469260364693);
	glVertex2f(0.3, 0.2469260364693);
	glVertex2f(0.079268232939, 0.2469260364693);
	glVertex2f(0, 0.2469260364693);
	glVertex2f(-0.0747741819204, 0.2469260364693);
	glVertex2f(-0.3639154440927, 0.2469260364693);
	glVertex2f(-0.4211342157906, 0.2469260364693);
	glVertex2f(-0.4763094599278, 0.2469260364693);
	glVertex2f(0.3639154440927, 0.2469260364693);
	glVertex2f(0.4211342157906, 0.2469260364693);
	glVertex2f(0.4763094599278, 0.2469260364693);
	//5th
	glColor3f(0.0f, 0.4f, .0f);
	glVertex2f(-0.3, 0.3289083761095);
	glVertex2f(-0.2255815247019, 0.3289083761095);
	glVertex2f(-0.15, 0.3289083761095);
	glVertex2f(0.2284813704787, 0.3289083761095);
	glVertex2f(0.1567438619528, 0.3289083761095);
	glVertex2f(0.3, 0.3289083761095);
	glVertex2f(0.079268232939, 0.3289083761095);
	glVertex2f(0, 0.3289083761095);
	glVertex2f(-0.0747741819204, 0.3289083761095);
	glVertex2f(-0.3639154440927, 0.3289083761095);
	glVertex2f(-0.4111342157906, 0.3289083761095);
	// glVertex2f(-0.4763094599278,0.3289083761095);
	glVertex2f(0.3639154440927, 0.3289083761095);
	glVertex2f(0.4211342157906, 0.3289083761095);
	glVertex2f(0.4463094599278, 0.3289083761095);
	//6th
	glColor3f(0.0f, 0.4f, .0f);
	glVertex2f(-0.3, 0.3590494289026);
	glVertex2f(-0.2255815247019, 0.3590494289026);
	glVertex2f(-0.15, 0.3590494289026);
	glVertex2f(0.2284813704787, 0.3590494289026);
	glVertex2f(0.1567438619528, 0.3590494289026);
	glVertex2f(0.3, 0.3590494289026);
	glVertex2f(0.079268232939, 0.3590494289026);
	glVertex2f(0, 0.3590494289026);
	glVertex2f(-0.0747741819204, 0.3590494289026);
	glVertex2f(-0.3639154440927, 0.3590494289026);
	glVertex2f(-0.4111342157906, 0.3590494289026);
	// glVertex2f(-0.4763094599278,0.3289083761095);
	glVertex2f(0.3639154440927, 0.3590494289026);
	glVertex2f(0.4211342157906, 0.3590494289026);
	glVertex2f(0.4463094599278, 0.3590494289026);
	//7th
	glColor3f(0.0f, 0.4f, .0f);
	glVertex2f(-0.3, 0.4180596903507);
	glVertex2f(-0.2255815247019, 0.4180596903507);
	glVertex2f(-0.15, 0.4180596903507);
	glVertex2f(0.2284813704787, 0.4180596903507);
	glVertex2f(0.1567438619528, 0.4180596903507);
	glVertex2f(0.3, 0.4180596903507);
	glVertex2f(0.079268232939, 0.4180596903507);
	glVertex2f(0, 0.4180596903507);
	//  glVertex2f(0.3678151227693, -0.0101);
	  //leafs other side
	glColor3f(0.0f, 0.0f, .0f);
	glVertex2f(-0.3639154440927, 0.0519113705434);
	glVertex2f(-0.4211342157906, 0.0519113705434);
	glVertex2f(-0.4763094599278, 0.0519113705434);
	glVertex2f(-0.5297835498475, 0.129250475244);
	glVertex2f(-0.5297835498475, 0.2049272094298);
	glVertex2f(-0.5297835498475, 0.2469260364693);
	glVertex2f(-0.4739272953739, 0.305424938262);
	glVertex2f(0.5297835498475, 0.3023061798031);
	glVertex2f(0.4517770202916, 0.3606264380533);

	glVertex2f(0.4517770202916, 0.4189466963035);
	glVertex2f(0.4117770202916, 0.4189466963035);


	glVertex2f(0.3639154440927, 0.0519113705434);
	glVertex2f(0.4211342157906, 0.0519113705434);
	glVertex2f(0.4763094599278, 0.0519113705434);
	glVertex2f(0.5297835498475, 0.129250475244);
	glVertex2f(0.5297835498475, 0.2049272094298);
	glVertex2f(0.5297835498475, 0.2469260364693);
	glVertex2f(-0.41776181063, 0.3590494289026);
	glVertex2f(-0.3641161184045, 0.3590494289026);

	glVertex2f(-0.2970590031226, 0.4180596903507);
	glVertex2f(-0.2434133108971, 0.4180596903507);
	glVertex2f(-0.1857441917547, 0.4770699517987);
	glVertex2f(-0.1039345111108, 0.4234242595732);
	glVertex2f(-0.066382526553, 0.4234242595732);
	glVertex2f(-0.0113956920219, 0.4234242595732);

	glVertex2f(0.2970590031226, 0.4770699517987);
	glVertex2f(0.2434133108971, 0.4770699517987);
	glVertex2f(0.1857441917547, 0.4770699517987);
	glVertex2f(0.1039345111108, 0.4770699517987);
	glVertex2f(0.066382526553, 0.4770699517987);
	glVertex2f(0.3639154440927, 0.4180596903507);
	glEnd();
}
///
void backgrounds() {

	glPointSize(4.0f);
	glBegin(GL_POINTS);
	glColor4f(0.6667, 1.0, 0.5098, 1.0);

	glVertex2f(.99, -.43);
	glVertex2f(.98, -.43);
	glVertex2f(.97, -.43);
	glVertex2f(.93, -.43);

	glVertex2f(.89, -.43);
	glVertex2f(.88, -.43);
	glVertex2f(.87, -.43);
	glVertex2f(.86, -.43);
	glVertex2f(.85, -.43);
	glVertex2f(.84, -.43);
	glVertex2f(.83, -.43);
	glVertex2f(.8, -.43);
	glVertex2f(.79, -.43);
	glVertex2f(.78, -.43);
	glVertex2f(.77, -.43);
	glVertex2f(.76, -.43);
	glVertex2f(.74, -.43);
	glVertex2f(.72, -.43);
	glVertex2f(.71, -.43);
	glVertex2f(.7, -.43);
	glVertex2f(.69, -.43);
	glVertex2f(.68, -.43);
	glVertex2f(.78, -.44);
	glVertex2f(.78, -.45);
	glVertex2f(.77, -.45);
	glVertex2f(.87, -.44);
	///


	//green
	glColor4f(0.4902, 0.9176, 0.2902, 1.0);
	glVertex2f(.96, -.52);
	glVertex2f(.96, -.505);
	glVertex2f(.97, -.505);
	glVertex2f(.78, -.505);
	glVertex2f(.78, -.52);
	glVertex2f(.78, -.535);
	glVertex2f(.75, -.505);
	glVertex2f(.735, -.505);
	glVertex2f(.885, -.505);
	glVertex2f(.87, -.505);
	glVertex2f(.84, -.505);
	////
	glColor4f(0.3529, 0.6353, 0.1529, 1.0); // #5aa227 color in RGB


	glVertex2f(.945, -.505);
	glVertex2f(.93, -.49);
	glVertex2f(.915, -.49);
	glVertex2f(.9, -.505);
	glVertex2f(.885, -.52);
	glVertex2f(.87, -.52);
	glVertex2f(.855, -.505);
	glVertex2f(.84, -.52);
	glVertex2f(.825, -.505);
	glVertex2f(.81, -.49);
	glVertex2f(.795, -.505);
	glVertex2f(.765, -.52);
	glVertex2f(.75, -.52);
	glVertex2f(.765, -.505);
	glVertex2f(.72, -.505);
	glVertex2f(.705, -.49);
	glVertex2f(.690, -.505);
	glVertex2f(.9, -.47);
	glVertex2f(.885, -.49);
	glVertex2f(.825, -.47);
	glVertex2f(.81, -.47);
	glVertex2f(.98, -.46);
	glVertex2f(.99, -.47);
	glVertex2f(.96, -.47);

	glVertex2f(.99, -.485);
	glVertex2f(.99, -.495);
	glVertex2f(.98, -.505);
	glVertex2f(.97, -.52);
	glVertex2f(.96, -.535);
	glEnd();
}
void backgr2() {
	glPointSize(4.0f);
	glBegin(GL_POINTS);
	//green
	glColor4f(0.3569, 0.2000, 0.0941, 1.0); // #5b3318 color in RGB

	glVertex2f(.96, -.52);
	glVertex2f(.96, -.505);
	glVertex2f(.97, -.505);
	glVertex2f(.78, -.505);
	glVertex2f(.78, -.52);
	glVertex2f(.78, -.535);
	glVertex2f(.75, -.505);
	glVertex2f(.735, -.505);
	glVertex2f(.885, -.505);
	glVertex2f(.87, -.505);
	glVertex2f(.84, -.505);
	////

	glVertex2f(.945, -.505);
	glVertex2f(.93, -.49);
	glVertex2f(.915, -.49);
	glVertex2f(.9, -.505);
	glVertex2f(.885, -.52);
	glVertex2f(.87, -.52);
	glVertex2f(.855, -.505);
	glVertex2f(.84, -.52);
	glVertex2f(.825, -.505);
	glVertex2f(.81, -.49);
	glVertex2f(.795, -.505);
	glVertex2f(.765, -.52);
	glVertex2f(.75, -.52);
	glVertex2f(.765, -.505);
	glVertex2f(.72, -.505);
	glVertex2f(.705, -.49);
	glVertex2f(.690, -.505);
	glVertex2f(.9, -.47);
	glVertex2f(.885, -.49);
	glVertex2f(.825, -.47);
	glVertex2f(.81, -.47);
	glVertex2f(.98, -.46);
	glVertex2f(.99, -.47);
	glVertex2f(.96, -.47);

	glVertex2f(.99, -.485);
	glVertex2f(.99, -.495);
	glVertex2f(.98, -.505);
	glVertex2f(.97, -.52);
	glVertex2f(.96, -.535);
	glEnd();
}
void gr2() {
	glBegin(GL_QUADS);
	glColor3f(0.4549f, 0.7922f, 0.8980f);
	glVertex2f(0.99990, 0.9999);
	glVertex2f(0.999990, -0.9999);
	glVertex2f(-0.99990, -0.9999);
	glVertex2f(-0.99990, 0.9999);
	glEnd();
}

void gr() {
	glBegin(GL_QUADS);
	glColor4f(0.4667, 0.2824, 0.2118, 1.0); // #774836 color in RGB

	glVertex2f(.9999, -.9999);
	glVertex2f(0.9999, -.42);
	glVertex2f(-.9999, -.42);
	glVertex2f(-.9999, -.9999);
	glColor4f(0.3569, 0.2000, 0.0941, 1.0);

	glVertex2f(.9999, -.52);
	glVertex2f(0.9999, -.42);
	glVertex2f(-.9999, -.42);
	glVertex2f(-.9999, -.52);

	glColor3f(0, 1, 0);

	glVertex2f(.9999, -.5);
	glVertex2f(0.9999, -.42);
	glVertex2f(-.9999, -.42);
	glVertex2f(-.9999, -.5);


	glEnd();
}

void background() {
	glBegin(GL_QUADS);
	glColor3f(0, 1, 0);

	glVertex2f(.99, -.13);
	glVertex2f(0.99, -.99);
	glVertex2f(-.990, -.99);
	glVertex2f(-.990, -.13);
	glColor3f(0, 1, 10);

	glVertex2f(0.990, 0.99);
	glVertex2f(0.990, -0.130);
	glVertex2f(-0.990, -0.130);
	glVertex2f(-0.990, 0.99);


	glEnd();
}



void BG() {
	backgrounds();
	glTranslatef(-0.3150, 0, 0.0);
	backgrounds();
	glTranslatef(-0.3150, 0, 0.0);
	backgrounds();
	glTranslatef(-0.3150, 0, 0.0);
	backgrounds();
	glTranslatef(-0.3150, 0, 0.0);
	backgrounds();
	glTranslatef(-0.3150, 0, 0.0);
	backgrounds();
	glTranslatef(-0.3150, 0, 0.0);
	backgrounds();
}
void BG2() {
	backgr2();
	glTranslatef(-0.3150, 0, 0.0);
	backgr2();
	glTranslatef(-0.3150, 0, 0.0);
	backgr2();
	glTranslatef(-0.3150, 0, 0.0);
	backgr2();
	glTranslatef(-0.3150, 0, 0.0);
	backgr2();
	glTranslatef(-0.3150, 0, 0.0);
	backgr2();
	glTranslatef(-0.3150, 0, 0.0);
	backgr2();
}

void tr() {


	glPointSize(20.0f);
	glBegin(GL_POINTS);
	//glColor3f(0.0f, 0.0f, 1.0f);
	glVertex2f(0.0031957349159, 0.8424513464816);
	glVertex2f(-0.0722499156368, 0.8424513464816);
	glVertex2f(-0.1507093743189, 0.8424513464816);

	glVertex2f(0.0763006618024, 0.7808893027877);

	glVertex2f(0.1291409702678, 0.7286507092189);
	glVertex2f(0.0763006618024, 0.7286507092189);
	glVertex2f(0.203770840375, 0.7852543747463);
	glVertex2f(0.2796250381809, 0.7852543747463);
	glVertex2f(0.3585753256932, 0.7852543747463);
	glVertex2f(0.4230343451221, 0.7243803124463);
	glVertex2f(0.4230343451221, 0.6724493072168);
	glVertex2f(0.4852085779266, 0.5968180855682);

	glVertex2f(0.4852085779266, 0.5155035287369);
	glVertex2f(0.4852085779266, 0.4441458564156);
	glVertex2f(0.5465821569684, 0.3647481438009);
	glVertex2f(0.5465821569684, 0.2873984706723);
	glVertex2f(0.5465821569684, 0.2132717005908);
	glVertex2f(0.4868709654128, 0.1440312183928);
	glVertex2f(0.4868709654128, 0.0934806725526);
	glVertex2f(0.4250244209523, 0.0299256436229);

	glVertex2f(0.2935078586573, -0.0300984145351);
	glVertex2f(0.2467658892981, -0.0300984145351);
	glVertex2f(0.1856417755207, -0.0300984145351);

	glVertex2f(0.1353042700569, -0.0912225283125);
	glVertex2f(0.1353042700569, -0.1469533379331);
	glVertex2f(0.1353042700569, -0.1972908433969);
	glVertex2f(0.2024669208655, -0.2743385105407);
	glVertex2f(0.2024669208655, -0.3279389643308);
	glVertex2f(0.2024669208655, -0.3834201357978);

	glVertex2f(0.1262978549532, -0.3834201357978);
	glVertex2f(0.0576516597483, -0.3834201357978);
	glVertex2f(-0.0015909470724, -0.3834201357978);
	glVertex2f(-0.056131759701, -0.3834201357978);
	glVertex2f(-0.0909250367226, -0.3834201357978);
	glVertex2f(0.0576516597483, -0.3834201357978);
	glVertex2f(-0.1230493904287, -0.3834201357978);

	glVertex2f(-0.1353042700569, -0.0912225283125);
	glVertex2f(-0.1353042700569, -0.1469533379331);
	glVertex2f(-0.1353042700569, -0.1972908433969);
	glVertex2f(-0.2024669208655, -0.2743385105407);

	glVertex2f(-0.2024669208655, -0.3279389643308);
	glVertex2f(-0.2024669208655, -0.3834201357978);

	glVertex2f(-0.203770840375, 0.7852543747463);
	glVertex2f(-0.2796250381809, 0.7852543747463);
	glVertex2f(-0.3585753256932, 0.7852543747463);
	glVertex2f(-0.4230343451221, 0.7243803124463);
	glVertex2f(-0.4230343451221, 0.6724493072168);
	glVertex2f(-0.4852085779266, 0.5968180855682);

	glVertex2f(-0.4852085779266, 0.5155035287369);
	glVertex2f(-0.4852085779266, 0.4441458564156);
	glVertex2f(-0.5465821569684, 0.3647481438009);
	glVertex2f(-0.5465821569684, 0.2873984706723);
	glVertex2f(-0.5465821569684, 0.2132717005908);
	glVertex2f(-0.4868709654128, 0.1440312183928);
	glVertex2f(-0.4868709654128, 0.0934806725526);
	glVertex2f(-0.4250244209523, 0.0299256436229);
	//A,Z,W
	glVertex2f(-0.2935078586573, -0.0300984145351);
	glVertex2f(-0.2467658892981, -0.0300984145351);
	glVertex2f(-0.1856417755207, -0.0300984145351);

	//الجذعbrown
	//glColor3f(0.3f, 0.2f, .0f);
	glVertex2f(0.056228435491, -0.0912225283125);
	glVertex2f(-0.056228435491, -0.0912225283125);
	glVertex2f(0.0171131392121, -0.0912225283125);
	glVertex2f(0.056228435491, -0.1469533379331);
	glVertex2f(-0.056228435491, -0.1469533379331);
	glVertex2f(0.0171131392121, -0.1469533379331);
	glVertex2f(0.056228435491, -0.1972908433969);
	glVertex2f(-0.056228435491, -0.1972908433969);
	glVertex2f(0.0171131392121, -0.1972908433969);
	glVertex2f(0.1262978549532, -0.2743385105407);
	glVertex2f(0.0576516597483, -0.2743385105407);
	glVertex2f(-0.0015909470724, -0.2743385105407);
	glVertex2f(-0.056131759701, -0.2743385105407);
	glVertex2f(-0.0909250367226, -0.2743385105407);
	glVertex2f(0.0576516597483, -0.2743385105407);
	glVertex2f(-0.1230493904287, -0.2743385105407);
	glVertex2f(0.1262978549532, -0.303);
	glVertex2f(0.0576516597483, -0.303);
	glVertex2f(-0.0015909470724, -0.303);
	glVertex2f(-0.056131759701, -0.303);
	glVertex2f(-0.0909250367226, -0.303);
	glVertex2f(0.0576516597483, -0.303);
	glVertex2f(-0.1230493904287, -0.303);
	//
	//q,r,s,t,u>1 tree fill in
	//glColor3f(0.0f, 0.5f, 0.0f);
	glVertex2f(0.1353042700569, -0.0300984145351);
	glVertex2f(0.056228435491, -0.0300984145351);
	glVertex2f(0.0171131392121, -0.0300984145351);
	glVertex2f(-0.0300949769865, -0.0300984145351);
	glVertex2f(-0.11, -0.0300984145351);
	glVertex2f(0.3427906028501, 0.0299256436229);
	glVertex2f(0.056228435491, 0.0299256436229);
	glVertex2f(0.0171131392121, 0.0299256436229);
	glVertex2f(0.1353042700569, 0.0299256436229);
	glVertex2f(-0.0300949769865, 0.0299256436229);
	glVertex2f(-0.11, 0.0299256436229);
	glVertex2f(-0.2935078586573, 0.0299256436229);
	glVertex2f(-0.2467658892981, 0.0299256436229);
	glVertex2f(-0.1856417755207, 0.0299256436229);
	glVertex2f(0.2935078586573, 0.0299256436229);
	glVertex2f(0.2467658892981, 0.0299256436229);
	glVertex2f(0.1856417755207, 0.0299256436229);
	glVertex2f(-0.3427906028501, 0.0299256436229);

	glVertex2f(0.3427906028501, 0.0934806725526);
	glVertex2f(0.056228435491, 0.0934806725526);
	glVertex2f(0.0171131392121, 0.0934806725526);
	glVertex2f(0.1353042700569, 0.0934806725526);
	glVertex2f(-0.0300949769865, 0.0934806725526);
	glVertex2f(-0.11, 0.0934806725526);
	glVertex2f(-0.2935078586573, 0.09348067255269);
	glVertex2f(-0.2467658892981, 0.0934806725526);
	glVertex2f(-0.1856417755207, 0.0934806725526);
	glVertex2f(0.2935078586573, 0.0934806725526);
	glVertex2f(0.2467658892981, 0.0934806725526);
	glVertex2f(0.1856417755207, 0.0934806725526);
	glVertex2f(-0.3427906028501, 0.0934806725526);
	glVertex2f(0.41, 0.0934806725526);
	glVertex2f(-0.41, 0.0934806725526);

	glVertex2f(0.3427906028501, 0.1440312183928);
	glVertex2f(0.056228435491, 0.1440312183928);
	glVertex2f(0.0171131392121, 0.1440312183928);
	glVertex2f(0.1353042700569, 0.1440312183928);
	glVertex2f(-0.0300949769865, 0.1440312183928);
	glVertex2f(-0.11, 0.1440312183928);
	glVertex2f(-0.2935078586573, 0.1440312183928);
	glVertex2f(-0.2467658892981, 0.1440312183928);
	glVertex2f(-0.1856417755207, 0.1440312183928);
	glVertex2f(0.2935078586573, 0.1440312183928);
	glVertex2f(0.2467658892981, 0.1440312183928);
	glVertex2f(0.1856417755207, 0.1440312183928);
	glVertex2f(-0.3427906028501, 0.1440312183928);
	glVertex2f(0.41, 0.1440312183928);
	glVertex2f(-0.41, 0.1440312183928);

	glVertex2f(0.3427906028501, 0.2132717005908);
	glVertex2f(0.056228435491, 0.2132717005908);
	glVertex2f(0.0171131392121, 0.2132717005908);
	glVertex2f(0.1353042700569, 0.2132717005908);
	glVertex2f(-0.0300949769865, 0.2132717005908);
	glVertex2f(-0.11, 0.2132717005908);
	glVertex2f(-0.2935078586573, 0.2132717005908);
	glVertex2f(-0.2467658892981, 0.2132717005908);
	glVertex2f(-0.1856417755207, 0.2132717005908);
	glVertex2f(0.2935078586573, 0.2132717005908);
	glVertex2f(0.2467658892981, 0.2132717005908);
	glVertex2f(0.1856417755207, 0.2132717005908);
	glVertex2f(-0.3427906028501, 0.2132717005908);
	glVertex2f(0.41, 0.2132717005908);
	glVertex2f(-0.41, 0.2132717005908);
	glVertex2f(0.47, 0.2132717005908);
	glVertex2f(-0.47, 0.2132717005908);


	glVertex2f(0.3427906028501, 0.2873984706723);
	glVertex2f(0.056228435491, 0.2873984706723);
	glVertex2f(0.0171131392121, 0.2873984706723);
	glVertex2f(0.1353042700569, 0.2873984706723);
	glVertex2f(-0.0300949769865, 0.2873984706723);
	glVertex2f(-0.11, 0.2873984706723);
	glVertex2f(-0.2935078586573, 0.2873984706723);
	glVertex2f(-0.2467658892981, 0.2873984706723);
	glVertex2f(-0.1856417755207, 0.2873984706723);
	glVertex2f(0.2935078586573, 0.2873984706723);
	glVertex2f(0.2467658892981, 0.2873984706723);
	glVertex2f(0.1856417755207, 0.2873984706723);
	glVertex2f(-0.3427906028501, 0.2873984706723);
	glVertex2f(0.41, 0.2873984706723);
	glVertex2f(-0.41, 0.2873984706723);
	glVertex2f(0.47, 0.2873984706723);
	glVertex2f(-0.47, 0.2873984706723);

	glVertex2f(0.3427906028501, 0.3647481438009);
	glVertex2f(0.056228435491, 0.3647481438009);
	glVertex2f(0.0171131392121, 0.3647481438009);
	glVertex2f(0.1353042700569, 0.3647481438009);
	glVertex2f(-0.0300949769865, 0.3647481438009);
	glVertex2f(-0.11, 0.3647481438009);
	glVertex2f(-0.2935078586573, 0.3647481438009);
	glVertex2f(-0.2467658892981, 0.3647481438009);
	glVertex2f(-0.1856417755207, 0.3647481438009);
	glVertex2f(0.2935078586573, 0.3647481438009);
	glVertex2f(0.2467658892981, 0.3647481438009);
	glVertex2f(0.1856417755207, 0.3647481438009);
	glVertex2f(-0.3427906028501, 0.3647481438009);
	glVertex2f(0.41, 0.3647481438009);
	glVertex2f(-0.41, 0.3647481438009);
	glVertex2f(0.47, 0.3647481438009);
	glVertex2f(-0.47, 0.3647481438009);

	glVertex2f(0.3427906028501, 0.4441458564156);
	glVertex2f(0.056228435491, 0.4441458564156);
	glVertex2f(0.0171131392121, 0.4441458564156);
	glVertex2f(0.1353042700569, 0.4441458564156);
	glVertex2f(-0.0300949769865, 0.4441458564156);
	glVertex2f(-0.11, 0.4441458564156);
	glVertex2f(-0.2935078586573, 0.4441458564156);
	glVertex2f(-0.2467658892981, 0.4441458564156);
	glVertex2f(-0.1856417755207, 0.4441458564156);
	glVertex2f(0.2935078586573, 0.4441458564156);
	glVertex2f(0.2467658892981, 0.4441458564156);
	glVertex2f(0.1856417755207, 0.4441458564156);
	glVertex2f(-0.3427906028501, 0.4441458564156);
	glVertex2f(0.41, 0.4441458564156);
	glVertex2f(-0.41, 0.4441458564156);

	glVertex2f(0.3427906028501, 0.5155035287369);
	glVertex2f(0.056228435491, 0.5155035287369);
	glVertex2f(0.0171131392121, 0.5155035287369);
	glVertex2f(0.1353042700569, 0.5155035287369);
	glVertex2f(-0.0300949769865, 0.5155035287369);
	glVertex2f(-0.11, 0.5155035287369);
	glVertex2f(-0.2935078586573, 0.5155035287369);
	glVertex2f(-0.2467658892981, 0.5155035287369);
	glVertex2f(-0.1856417755207, 0.5155035287369);
	glVertex2f(0.2935078586573, 0.5155035287369);
	glVertex2f(0.2467658892981, 0.5155035287369);
	glVertex2f(0.1856417755207, 0.5155035287369);
	glVertex2f(-0.3427906028501, 0.5155035287369);
	glVertex2f(0.41, 0.5155035287369);
	glVertex2f(-0.41, 0.5155035287369);

	glVertex2f(0.3427906028501, 0.5968180855682);
	glVertex2f(0.056228435491, 0.5968180855682);
	glVertex2f(0.0171131392121, 0.5968180855682);
	glVertex2f(0.1353042700569, 0.5968180855682);
	glVertex2f(-0.0300949769865, 0.5968180855682);
	glVertex2f(-0.11, 0.5968180855682);
	glVertex2f(-0.2935078586573, 0.5968180855682);
	glVertex2f(-0.2467658892981, 0.5968180855682);
	glVertex2f(-0.1856417755207, 0.5968180855682);
	glVertex2f(0.2935078586573, 0.5968180855682);
	glVertex2f(0.2467658892981, 0.5968180855682);
	glVertex2f(0.1856417755207, 0.5968180855682);
	glVertex2f(-0.3427906028501, 0.5968180855682);
	glVertex2f(0.41, 0.5968180855682);
	glVertex2f(-0.41, 0.5968180855682);

	glVertex2f(0.35, 0.677);
	glVertex2f(0.2796250381809, 0.677);
	glVertex2f(0.203770840375, 0.677);
	glVertex2f(0.35, 0.703);
	glVertex2f(0.2796250381809, 0.703);
	glVertex2f(0.203770840375, 0.703);


	glVertex2f(0.3427906028501, 0.65);
	glVertex2f(0.056228435491, 0.65);
	glVertex2f(0.0171131392121, 0.65);
	glVertex2f(0.1353042700569, 0.65);
	glVertex2f(-0.0300949769865, 0.65);
	glVertex2f(-0.11, 0.65);
	glVertex2f(-0.2935078586573, 0.65);
	glVertex2f(-0.2467658892981, 0.65);
	glVertex2f(-0.1856417755207, 0.65);
	glVertex2f(0.2935078586573, 0.65);
	glVertex2f(0.2467658892981, 0.65);
	glVertex2f(0.1856417755207, 0.65);
	glVertex2f(-0.3427906028501, 0.65);


	glVertex2f(-0.3427906028501, 0.72);
	glVertex2f(-0.1856417755207, 0.72);
	glVertex2f(-0.2467658892981, 0.72);
	glVertex2f(-0.2935078586573, 0.72);
	glVertex2f(-0.1353042700569, 0.73);
	glVertex2f(-0.0171131392121, 0.73);
	glVertex2f(-0.056228435491, 0.73);
	glVertex2f(-0.3427906028501, 0.72);
	glVertex2f(0.0001, 0.73);
	// glVertex2f(-0.0171131392121, 0.7335716097802);
	glVertex2f(-0.1353042700569, 0.77);
	glVertex2f(-0.00101131392121, 0.77);
	glVertex2f(-0.056228435491, 0.77);
	glVertex2f(-0.056228435491, 0.77);
	glEnd();

}

void cloud1()
{

	glPointSize(10.0f);
	glBegin(GL_POINTS);
	glColor3f(0.7f, 0.8f, 1.0f);
	//blue base 26 vertex
	glVertex2f(0.0f, 0.0f);//1
	glVertex2f(0.04f, 0.0f);//2
	glVertex2f(0.08f, 0.0f);//3
	glVertex2f(0.12f, 0.0f);//4
	glVertex2f(0.16f, 0.0f);//5
	glVertex2f(0.20f, 0.0f);//6
	glVertex2f(0.24f, 0.0f);//7
	glVertex2f(0.28f, 0.0f);//8
	glVertex2f(0.32f, 0.0f);//9
	glVertex2f(0.36f, 0.0f);//10
	glVertex2f(0.40f, 0.0f);//11
	glVertex2f(0.44f, 0.0f);//12
	glVertex2f(0.48f, 0.0f);//13
	glVertex2f(0.52f, 0.0f);//14
	glVertex2f(0.56f, 0.0f);//15
	glVertex2f(0.60f, 0.0f);//16
	glVertex2f(0.64f, 0.0f);//17
	glVertex2f(0.68f, 0.0f);//18
	glVertex2f(0.72f, 0.0f);//19
	glVertex2f(0.76f, 0.0f);//20
	glVertex2f(0.80f, 0.0f);//21
	glVertex2f(0.84f, 0.0f);//22
	glVertex2f(0.88f, 0.0f);//23
	glVertex2f(0.92f, 0.0f);//24
	glVertex2f(0.96f, 0.0f);//25
	glVertex2f(1.0f, 0.0f);//26

	glVertex2f(-0.04f, 0.04f);
	glVertex2f(-0.08f, 0.08f);
	glVertex2f(0.60f, 0.04f);//16
	glVertex2f(0.64f, 0.04f);//17
	glVertex2f(0.68f, 0.04f);//18
	glVertex2f(0.72f, 0.04f);//19
	glVertex2f(0.76f, 0.04f);//20
	glVertex2f(0.80f, 0.04f);//21
	glVertex2f(0.84f, 0.04f);//22
	glVertex2f(0.88f, 0.04f);//23
	glVertex2f(0.92f, 0.04f);//24
	glVertex2f(0.96f, 0.04f);//25

	glVertex2f(0.84f, 0.08f);//22
	glVertex2f(0.88f, 0.08f);//23

	glVertex2f(0.88f, 0.12f);//22


	glVertex2f(0.72f, 0.16f);//19
	glVertex2f(0.72f, 0.20f);//19
	glVertex2f(0.72f, 0.24f);//19
	glVertex2f(0.72f, 0.28f);//19

	glVertex2f(0.68f, 0.20f);//19
	glVertex2f(0.76f, 0.20f);//19

	glVertex2f(0.68f, 0.32f);//19
	glVertex2f(0.68f, 0.36f);//19
	glVertex2f(0.68f, 0.40f);//19
	glVertex2f(0.64f, 0.44f);//19

	glVertex2f(0.08f, 0.20f);//3
	glVertex2f(0.12f, 0.20f);//4
	glVertex2f(0.12f, 0.16f);//4


	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex2f(0.0f, 0.04f);//1
	glVertex2f(0.04f, 0.04f);//2
	glVertex2f(0.08f, 0.04f);//3
	glVertex2f(0.12f, 0.04f);//4
	glVertex2f(0.16f, 0.04f);//5
	glVertex2f(0.20f, 0.04f);//6
	glVertex2f(0.24f, 0.04f);//7
	glVertex2f(0.28f, 0.04f);//8
	glVertex2f(0.32f, 0.04f);//9
	glVertex2f(0.36f, 0.04f);//10
	glVertex2f(0.40f, 0.04f);//11
	glVertex2f(0.44f, 0.04f);//12
	glVertex2f(0.48f, 0.04f);//13
	glVertex2f(0.52f, 0.04f);//14
	glVertex2f(0.56f, 0.04f);//15


	glVertex2f(-0.04f, 0.08f);//1
	glVertex2f(0.0f, 0.08f);//1
	glVertex2f(0.04f, 0.08f);//2
	glVertex2f(0.08f, 0.08f);//3
	glVertex2f(0.12f, 0.08f);//4
	glVertex2f(0.16f, 0.08f);//5
	glVertex2f(0.20f, 0.08f);//6
	glVertex2f(0.24f, 0.08f);//7
	glVertex2f(0.28f, 0.08f);//8
	glVertex2f(0.32f, 0.08f);//9
	glVertex2f(0.36f, 0.08f);//10
	glVertex2f(0.40f, 0.08f);//11
	glVertex2f(0.44f, 0.08f);//12
	glVertex2f(0.48f, 0.08f);//13
	glVertex2f(0.52f, 0.08f);//14
	glVertex2f(0.56f, 0.08f);//15
	glVertex2f(0.60f, 0.08f);//16
	glVertex2f(0.64f, 0.08f);//17
	glVertex2f(0.68f, 0.08f);//18
	glVertex2f(0.72f, 0.08f);//19
	glVertex2f(0.76f, 0.08f);//20
	glVertex2f(0.80f, 0.08f);//21

	glVertex2f(-0.08f, 0.12f);
	glVertex2f(-0.04f, 0.12f);//1
	glVertex2f(0.0f, 0.12f);//1
	glVertex2f(0.04f, 0.12f);//2
	glVertex2f(0.08f, 0.12f);//3
	glVertex2f(0.12f, 0.12f);//4
	glVertex2f(0.16f, 0.12f);//5
	glVertex2f(0.20f, 0.12f);//6
	glVertex2f(0.24f, 0.12f);//7
	glVertex2f(0.28f, 0.12f);//8
	glVertex2f(0.32f, 0.12f);//9
	glVertex2f(0.36f, 0.12f);//10
	glVertex2f(0.40f, 0.12f);//11
	glVertex2f(0.44f, 0.12f);//12
	glVertex2f(0.48f, 0.12f);//13
	glVertex2f(0.52f, 0.12f);//14
	glVertex2f(0.56f, 0.12f);//15
	glVertex2f(0.60f, 0.12f);//16
	glVertex2f(0.64f, 0.12f);//17
	glVertex2f(0.68f, 0.12f);//18
	glVertex2f(0.72f, 0.12f);//19
	glVertex2f(0.76f, 0.12f);//20
	glVertex2f(0.80f, 0.12f);//21
	glVertex2f(0.84f, 0.12f);//22

	glVertex2f(-0.08f, 0.16f);
	glVertex2f(-0.04f, 0.16f);//1
	glVertex2f(0.0f, 0.16f);//1
	glVertex2f(0.04f, 0.16f);//2
	glVertex2f(0.08f, 0.16f);//3
	glVertex2f(0.16f, 0.16f);//5
	glVertex2f(0.20f, 0.16f);//6
	glVertex2f(0.24f, 0.16f);//7
	glVertex2f(0.28f, 0.16f);//8
	glVertex2f(0.32f, 0.16f);//9
	glVertex2f(0.36f, 0.16f);//10
	glVertex2f(0.40f, 0.16f);//11
	glVertex2f(0.44f, 0.16f);//12
	glVertex2f(0.48f, 0.16f);//13
	glVertex2f(0.52f, 0.16f);//14
	glVertex2f(0.56f, 0.16f);//15
	glVertex2f(0.60f, 0.16f);//16
	glVertex2f(0.64f, 0.16f);//17
	glVertex2f(0.68f, 0.16f);//18
	glVertex2f(0.76f, 0.16f);//20
	glVertex2f(0.80f, 0.16f);//21
	glVertex2f(0.84f, 0.16f);//22

	glVertex2f(-0.08f, 0.20f);
	glVertex2f(-0.04f, 0.20f);//1
	glVertex2f(0.0f, 0.20f);//1
	glVertex2f(0.04f, 0.20f);//2
	glVertex2f(0.16f, 0.20f);//5
	glVertex2f(0.20f, 0.20f);//6
	glVertex2f(0.24f, 0.20f);//7
	glVertex2f(0.28f, 0.20f);//8
	glVertex2f(0.32f, 0.20f);//9
	glVertex2f(0.36f, 0.20f);//10
	glVertex2f(0.40f, 0.20f);//11
	glVertex2f(0.44f, 0.20f);//12
	glVertex2f(0.48f, 0.20f);//13
	glVertex2f(0.52f, 0.20f);//14
	glVertex2f(0.56f, 0.20f);//15
	glVertex2f(0.60f, 0.20f);//16
	glVertex2f(0.64f, 0.20f);//17
	//glVertex2f(0.68f, 0.16f);//18
	//glVertex2f(0.76f, 0.20f);//20
	glVertex2f(0.80f, 0.20f);//21
	glVertex2f(0.84f, 0.20f);//22

	glVertex2f(-0.04f, 0.24f);//1
	glVertex2f(0.0f, 0.24f);//1
	glVertex2f(0.04f, 0.24f);//2
	glVertex2f(0.12f, 0.24f);//4
	glVertex2f(0.16f, 0.24f);//5
	glVertex2f(0.20f, 0.24f);//6
	glVertex2f(0.24f, 0.24f);//7
	glVertex2f(0.28f, 0.24f);//8
	glVertex2f(0.32f, 0.24f);//9
	glVertex2f(0.36f, 0.24f);//10
	glVertex2f(0.40f, 0.24f);//11
	glVertex2f(0.44f, 0.24f);//12
	glVertex2f(0.48f, 0.24f);//13
	glVertex2f(0.52f, 0.24f);//14
	glVertex2f(0.56f, 0.24f);//15
	glVertex2f(0.60f, 0.24f);//16
	glVertex2f(0.64f, 0.24f);//17
	glVertex2f(0.68f, 0.24f);//18


	//glVertex2f(0.12f, 0.28f);//4
	//glVertex2f(0.16f, 0.28f);//5
	//glVertex2f(0.20f, 0.28f);//6
	glVertex2f(0.24f, 0.28f);//7
	glVertex2f(0.28f, 0.28f);//8
	glVertex2f(0.32f, 0.28f);//9
	glVertex2f(0.36f, 0.28f);//10
	glVertex2f(0.40f, 0.28f);//11
	glVertex2f(0.44f, 0.28f);//12
	glVertex2f(0.48f, 0.28f);//13
	glVertex2f(0.52f, 0.28f);//14
	glVertex2f(0.56f, 0.28f);//15
	glVertex2f(0.60f, 0.28f);//16
	glVertex2f(0.64f, 0.28f);//17
	glVertex2f(0.68f, 0.28f);//18

	//glVertex2f(0.28f, 0.32f);//8
	glVertex2f(0.32f, 0.32f);//9
	glVertex2f(0.36f, 0.32f);//10
	glVertex2f(0.40f, 0.32f);//11
	glVertex2f(0.44f, 0.32f);//12
	glVertex2f(0.48f, 0.32f);//13
	glVertex2f(0.52f, 0.32f);//14
	glVertex2f(0.56f, 0.32f);//15
	glVertex2f(0.60f, 0.32f);//16
	glVertex2f(0.64f, 0.32f);//17

	//glVertex2f(0.28f, 0.36f);//8
	//glVertex2f(0.32f, 0.36f);//9
	glVertex2f(0.36f, 0.36f);//10
	glVertex2f(0.40f, 0.36f);//11
	glVertex2f(0.44f, 0.36f);//12
	glVertex2f(0.48f, 0.36f);//13
	glVertex2f(0.52f, 0.36f);//14
	glVertex2f(0.56f, 0.36f);//15
	glVertex2f(0.60f, 0.36f);//16
	glVertex2f(0.64f, 0.36f);//17
	//glVertex2f(0.68f, 0.36f);//18

	//glVertex2f(0.36f, 0.40f);//10
	glVertex2f(0.40f, 0.40f);//11
	glVertex2f(0.44f, 0.40f);//12
	glVertex2f(0.48f, 0.40f);//13
	glVertex2f(0.52f, 0.40f);//14
	glVertex2f(0.56f, 0.40f);//15
	glVertex2f(0.60f, 0.40f);//16
	glVertex2f(0.64f, 0.40f);//17

	glVertex2f(0.48f, 0.44f);//13
	glVertex2f(0.52f, 0.44f);//14
	glVertex2f(0.56f, 0.44f);//15
	glVertex2f(0.60f, 0.44f);//16
	//glVertex2f(0.64f, 0.44f);//17

	glEnd();
	glFlush();

}
void cloud2()
{
	glPointSize(10.0f);
	glBegin(GL_POINTS);
	glColor3f(0.7f, 0.8f, 1.0f);
	//blue base 

	//line 1 blue
	glVertex2f(0.0f, 0.0f);//1
	glVertex2f(0.04f, 0.0f);//2
	glVertex2f(0.08f, 0.0f);//3
	glVertex2f(0.12f, 0.0f);//4
	glVertex2f(0.16f, 0.0f);//5
	glVertex2f(0.16f, 0.0f);//6
	glVertex2f(0.36f, 0.0f);//5
	glVertex2f(0.40f, 0.0f);//6
	glVertex2f(0.44f, 0.0f);//5
	glVertex2f(0.48f, 0.0f);//6
	glVertex2f(0.0f, 0.04f);//1
	glVertex2f(0.04f, 0.04f);//2
	glVertex2f(0.08f, 0.04f);//3
	glVertex2f(0.12f, 0.04f);//4
	glVertex2f(0.16f, 0.04f);//5
	glVertex2f(0.16f, 0.04f);//6
	glVertex2f(0.36f, 0.04f);//5
	glVertex2f(0.40f, 0.04f);//6
	glVertex2f(0.44f, 0.04f);//5
	glVertex2f(0.48f, 0.04f);//6

	//line 2 blue
	glVertex2f(-0.16f, 0.08f);//5
	glVertex2f(-0.12f, 0.08f);//6
	glVertex2f(-0.08f, 0.08f);//5
	glVertex2f(-0.04f, 0.08f);//6
	glVertex2f(0.0f, 0.08f);//1
	glVertex2f(0.04f, 0.08f);//2
	glVertex2f(0.08f, 0.08f);//3
	glVertex2f(0.12f, 0.08f);//4
	glVertex2f(0.16f, 0.08f);//5
	glVertex2f(0.16f, 0.08f);//6
	glVertex2f(0.20f, 0.08f);//5
	glVertex2f(0.24f, 0.08f);//6
	glVertex2f(0.28f, 0.08f);//5
	glVertex2f(0.32f, 0.08f);//6
	glVertex2f(0.36f, 0.08f);//5
	glVertex2f(0.40f, 0.08f);//6
	glVertex2f(0.44f, 0.08f);//5
	glVertex2f(0.48f, 0.08f);//6
	glVertex2f(0.52f, 0.08f);//6
	glVertex2f(0.56f, 0.08f);//6

	glVertex2f(-0.16f, 0.12f);//5
	glVertex2f(-0.12f, 0.12f);//6
	glVertex2f(-0.08f, 0.12f);//5
	glVertex2f(-0.04f, 0.12f);//6
	glVertex2f(0.0f, 0.12f);//1
	glVertex2f(0.04f, 0.12f);//2
	glVertex2f(0.08f, 0.12f);//3
	glVertex2f(0.12f, 0.12f);//4
	glVertex2f(0.16f, 0.12f);//5
	glVertex2f(0.16f, 0.12f);//6
	glVertex2f(0.20f, 0.12f);//5
	glVertex2f(0.24f, 0.12f);//6
	glVertex2f(0.28f, 0.12f);//5
	glVertex2f(0.32f, 0.12f);//6
	glVertex2f(0.36f, 0.12f);//5
	glVertex2f(0.40f, 0.12f);//6
	glVertex2f(0.44f, 0.12f);//5
	glVertex2f(0.48f, 0.12f);//6
	glVertex2f(0.52f, 0.12f);//6
	glVertex2f(0.56f, 0.12f);//6

	//line 3 blue
	glVertex2f(-0.28f, 0.16f);//5
	glVertex2f(-0.24f, 0.16f);//6
	glVertex2f(-0.20f, 0.16f);//5
	glVertex2f(-0.16f, 0.16f);//6
	glVertex2f(-0.12f, 0.16f);//6

	glVertex2f(0.28f, 0.16f);//5
	glVertex2f(0.32f, 0.16f);//6
	glVertex2f(0.44f, 0.16f);//5
	glVertex2f(0.48f, 0.16f);//6
	glVertex2f(0.52f, 0.16f);//5
	glVertex2f(0.56f, 0.16f);//6
	glVertex2f(0.60f, 0.16f);//5
	glVertex2f(0.64f, 0.16f);//6
	glVertex2f(0.68f, 0.16f);//5
	glVertex2f(0.72f, 0.16f);//6
	glVertex2f(0.76f, 0.16f);//5
	glVertex2f(0.80f, 0.16f);//6
	glVertex2f(-0.28f, 0.16f);//5
	glVertex2f(-0.24f, 0.16f);//6
	glVertex2f(-0.20f, 0.16f);//5
	glVertex2f(-0.16f, 0.16f);//6
	glVertex2f(-0.12f, 0.16f);//6

	glVertex2f(-0.28f, 0.2f);//5
	glVertex2f(-0.24f, 0.2f);//6
	glVertex2f(-0.20f, 0.2f);//5
	glVertex2f(-0.16f, 0.2f);//6
	glVertex2f(-0.12f, 0.2f);//6
	glVertex2f(0.28f, 0.2f);//5
	glVertex2f(0.32f, 0.2f);//6
	glVertex2f(0.44f, 0.2f);//5
	glVertex2f(0.48f, 0.2f);//6
	glVertex2f(0.52f, 0.2f);//5
	glVertex2f(0.56f, 0.2f);//6
	glVertex2f(0.60f, 0.2f);//5
	glVertex2f(0.64f, 0.2f);//6
	glVertex2f(0.68f, 0.2f);//5
	glVertex2f(0.72f, 0.2f);//6
	glVertex2f(0.76f, 0.2f);//5
	glVertex2f(0.80f, 0.2f);//6
	glVertex2f(-0.28f, 0.2f);//5
	glVertex2f(-0.24f, 0.2f);//6
	glVertex2f(-0.20f, 0.2f);//5
	glVertex2f(-0.16f, 0.2f);//6
	glVertex2f(-0.12f, 0.2f);//6

	//line 4 blue
	glVertex2f(0.36f, 0.24f);//5
	glVertex2f(0.40f, 0.24f);//6
	glVertex2f(0.56f, 0.24f);//6
	glVertex2f(0.60f, 0.24f);//5
	glVertex2f(0.64f, 0.24f);//6
	glVertex2f(0.68f, 0.24f);//5
	glVertex2f(0.72f, 0.24f);//6
	glVertex2f(0.76f, 0.24f);//5
	glVertex2f(0.80f, 0.24f);//6

	glVertex2f(0.36f, 0.28f);//5
	glVertex2f(0.40f, 0.28f);//6
	glVertex2f(0.56f, 0.28f);//6
	glVertex2f(0.60f, 0.28f);//5
	glVertex2f(0.64f, 0.28f);//6
	glVertex2f(0.68f, 0.28f);//5
	glVertex2f(0.72f, 0.28f);//6
	glVertex2f(0.76f, 0.28f);//5
	glVertex2f(0.80f, 0.28f);//6


	//line 5 blue
	glVertex2f(0.76f, 0.32f);//5
	glVertex2f(0.80f, 0.32f);//6
	glVertex2f(0.84f, 0.32f);//5
	glVertex2f(0.88f, 0.32f);//6
	glVertex2f(0.76f, 0.32f);//5
	glVertex2f(0.80f, 0.32f);//6
	glVertex2f(0.84f, 0.32f);//5
	glVertex2f(0.88f, 0.32f);//6

	glVertex2f(0.76f, 0.36f);//5
	glVertex2f(0.80f, 0.36f);//6
	glVertex2f(0.84f, 0.36f);//5
	glVertex2f(0.88f, 0.36f);//6
	glVertex2f(0.76f, 0.36f);//5
	glVertex2f(0.80f, 0.36f);//6
	glVertex2f(0.84f, 0.36f);//5
	glVertex2f(0.88f, 0.36f);//6

	//line 6 blue
	glVertex2f(0.76f, 0.4f);//5
	glVertex2f(0.80f, 0.4f);//6
	glVertex2f(0.84f, 0.4f);//5
	glVertex2f(0.88f, 0.4f);//6
	glVertex2f(0.76f, 0.4f);//5
	glVertex2f(0.80f, 0.4f);//6
	glVertex2f(0.84f, 0.4f);//5
	glVertex2f(0.88f, 0.4f);//6

	glVertex2f(0.76f, 0.44f);//5
	glVertex2f(0.80f, 0.44f);//6
	glVertex2f(0.84f, 0.44f);//5
	glVertex2f(0.88f, 0.44f);//6
	glVertex2f(0.76f, 0.44f);//5
	glVertex2f(0.80f, 0.44f);//6
	glVertex2f(0.84f, 0.44f);//5
	glVertex2f(0.88f, 0.44f);//6

	//line 7 blue 
	glVertex2f(0.0f, 0.48f);//3
	glVertex2f(0.04f, 0.48f);//4
	glVertex2f(0.08f, 0.48f);//5
	glVertex2f(0.12f, 0.48f);//6

	glVertex2f(0.0f, 0.52f);//3
	glVertex2f(0.04f, 0.52f);//4
	glVertex2f(0.08f, 0.52f);//5
	glVertex2f(0.12f, 0.52f);//6

	glVertex2f(0.76f, 0.52f);//5
	glVertex2f(0.80f, 0.52f);//6
	glVertex2f(0.84f, 0.52f);//5
	glVertex2f(0.88f, 0.52f);//6
	glVertex2f(0.76f, 0.52f);//5
	glVertex2f(0.80f, 0.52f);//6
	glVertex2f(0.84f, 0.52f);//5
	glVertex2f(0.88f, 0.52f);//6

	glVertex2f(0.76f, 0.48f);//5
	glVertex2f(0.80f, 0.48f);//6
	glVertex2f(0.84f, 0.48f);//5
	glVertex2f(0.88f, 0.48f);//6
	glVertex2f(0.76f, 0.48f);//5
	glVertex2f(0.80f, 0.48f);//6
	glVertex2f(0.84f, 0.48f);//5
	glVertex2f(0.88f, 0.48f);//6

	//line 8 blue
	glVertex2f(0.0f, 0.52f);//3
	glVertex2f(0.04f, 0.52f);//4

	glVertex2f(0.0f, 0.56f);//3
	glVertex2f(0.04f, 0.56f);//4

	glVertex2f(0.0f, 0.6f);//3
	glVertex2f(0.04f, 0.6f);//4

	glVertex2f(0.40f, 0.56f);//6
	glVertex2f(0.44f, 0.56f);//5
	glVertex2f(0.40f, 0.6f);//6
	glVertex2f(0.44f, 0.6f);//5



	glVertex2f(0.48f, 0.56f);//6
	glVertex2f(0.52f, 0.56f);//5
	glVertex2f(0.48f, 0.6f);//6
	glVertex2f(0.52f, 0.6f);//5


	glVertex2f(0.68f, 0.56f);//5
	glVertex2f(0.68f, 0.6f);//5



	glVertex2f(0.7f, 0.56f);//6
	glVertex2f(0.72f, 0.56f);//5
	glVertex2f(0.7f, 0.6f);//6
	glVertex2f(0.72f, 0.6f);//5


	glVertex2f(0.76f, 0.56f);//5
	glVertex2f(0.80f, 0.56f);//6




	glVertex2f(0.76f, 0.6f);//5
	glVertex2f(0.80f, 0.6f);//6





	//line 9 blue
	glVertex2f(0.40f, 0.64f);//6
	glVertex2f(0.44f, 0.64f);//5
	glVertex2f(0.40f, 0.68f);//6
	glVertex2f(0.44f, 0.68f);//5

	//line 10 blue

	glVertex2f(0.40f, 0.72f);//6
	glVertex2f(0.44f, 0.72f);//5
	glVertex2f(0.40f, 0.76f);//6
	glVertex2f(0.44f, 0.76f);//5


	//line 3 white
	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex2f(-0.08f, 0.16f);//1
	glVertex2f(-0.04f, 0.16f);//2
	glVertex2f(0.0f, 0.16f);//3
	glVertex2f(0.04f, 0.16f);//4
	glVertex2f(0.08f, 0.16f);//5
	glVertex2f(0.12f, 0.16f);//6
	glVertex2f(0.16f, 0.16f);//7
	glVertex2f(0.2f, 0.16f);//8
	glVertex2f(0.24f, 0.16f);//9
	glVertex2f(0.36f, 0.16f);//10
	glVertex2f(0.4f, 0.16f);//11


	glVertex2f(-0.08f, 0.2f);//1
	glVertex2f(-0.04f, 0.2f);//2
	glVertex2f(0.0f, 0.2f);//3
	glVertex2f(0.04f, 0.2f);//4
	glVertex2f(0.08f, 0.2f);//5
	glVertex2f(0.12f, 0.2f);//6
	glVertex2f(0.16f, 0.2f);//7
	glVertex2f(0.2f, 0.2f);//8
	glVertex2f(0.24f, 0.2f);//9
	glVertex2f(0.36f, 0.2f);//10
	glVertex2f(0.4f, 0.2f);//11

	//line 4 white

	glVertex2f(-0.36f, 0.24f);//1
	glVertex2f(-0.32f, 0.24f);//1
	glVertex2f(-0.28f, 0.24f);//2
	glVertex2f(-0.24f, 0.24f);//1
	glVertex2f(-0.2f, 0.24f);//2
	glVertex2f(-0.16f, 0.24f);//1
	glVertex2f(-0.12f, 0.24f);//2
	glVertex2f(-0.08f, 0.24f);//1
	glVertex2f(-0.04f, 0.24f);//2
	glVertex2f(0.0f, 0.24f);//3
	glVertex2f(0.04f, 0.24f);//4
	glVertex2f(0.08f, 0.24f);//5
	glVertex2f(0.12f, 0.24f);//6
	glVertex2f(0.16f, 0.24f);//7
	glVertex2f(0.2f, 0.24f);//8
	glVertex2f(0.24f, 0.24f);//9
	glVertex2f(0.28f, 0.24f);//10
	glVertex2f(0.32f, 0.24f);//11
	glVertex2f(0.36f, 0.24f);//10
	glVertex2f(0.4f, 0.24f);//11
	glVertex2f(0.44f, 0.24f);//10
	glVertex2f(0.48f, 0.24f);//11
	glVertex2f(0.52f, 0.24f);//10
	glVertex2f(0.56f, 0.24f);//11

	glVertex2f(-0.36f, 0.28f);//1
	glVertex2f(-0.32f, 0.28f);//1
	glVertex2f(-0.28f, 0.28f);//2
	glVertex2f(-0.24f, 0.28f);//1
	glVertex2f(-0.2f, 0.28f);//2
	glVertex2f(-0.16f, 0.28f);//1
	glVertex2f(-0.12f, 0.28f);//2
	glVertex2f(-0.08f, 0.28f);//1
	glVertex2f(-0.04f, 0.28f);//2
	glVertex2f(0.0f, 0.28f);//3
	glVertex2f(0.04f, 0.28f);//4
	glVertex2f(0.08f, 0.28f);//5
	glVertex2f(0.12f, 0.28f);//6
	glVertex2f(0.16f, 0.28f);//7
	glVertex2f(0.2f, 0.28f);//8
	glVertex2f(0.24f, 0.28f);//9
	glVertex2f(0.28f, 0.28f);//10
	glVertex2f(0.32f, 0.28f);//11
	glVertex2f(0.36f, 0.28f);//10
	glVertex2f(0.4f, 0.28f);//11
	glVertex2f(0.44f, 0.28f);//10
	glVertex2f(0.48f, 0.28f);//11
	glVertex2f(0.52f, 0.28f);//10
	glVertex2f(0.56f, 0.28f);//11

	//line 5 white
	glVertex2f(-0.36f, 0.32f);//1
	glVertex2f(-0.32f, 0.32f);//1
	glVertex2f(-0.28f, 0.32f);//2
	glVertex2f(-0.24f, 0.32f);//1
	glVertex2f(-0.2f, 0.32f);//2
	glVertex2f(-0.16f, 0.32f);//1
	glVertex2f(-0.12f, 0.32f);//2
	glVertex2f(-0.08f, 0.32f);//1
	glVertex2f(-0.04f, 0.32f);//2
	glVertex2f(0.0f, 0.32f);//3
	glVertex2f(0.04f, 0.32f);//4
	glVertex2f(0.08f, 0.32f);//5
	glVertex2f(0.12f, 0.32f);//6
	glVertex2f(0.16f, 0.32f);//7
	glVertex2f(0.2f, 0.32f);//8
	glVertex2f(0.24f, 0.32f);//9
	glVertex2f(0.28f, 0.32f);//10
	glVertex2f(0.32f, 0.32f);//11
	glVertex2f(0.36f, 0.32f);//10
	glVertex2f(0.4f, 0.32f);//11
	glVertex2f(0.44f, 0.32f);//10
	glVertex2f(0.48f, 0.32f);//11
	glVertex2f(0.52f, 0.32f);//10
	glVertex2f(0.56f, 0.32f);//11
	glVertex2f(0.6f, 0.32f);//10
	glVertex2f(0.64f, 0.32f);//11
	glVertex2f(0.68f, 0.32f);//10
	glVertex2f(0.72f, 0.32f);//11

	glVertex2f(-0.36f, 0.36f);//1
	glVertex2f(-0.32f, 0.36f);//1
	glVertex2f(-0.28f, 0.36f);//2
	glVertex2f(-0.24f, 0.36f);//1
	glVertex2f(-0.2f, 0.36f);//2
	glVertex2f(-0.16f, 0.36f);//1
	glVertex2f(-0.12f, 0.36f);//2
	glVertex2f(-0.08f, 0.36f);//1
	glVertex2f(-0.04f, 0.36f);//2
	glVertex2f(0.0f, 0.36f);//3
	glVertex2f(0.04f, 0.36f);//4
	glVertex2f(0.08f, 0.36f);//5
	glVertex2f(0.12f, 0.36f);//6
	glVertex2f(0.16f, 0.36f);//7
	glVertex2f(0.2f, 0.36f);//8
	glVertex2f(0.24f, 0.36f);//9
	glVertex2f(0.28f, 0.36f);//10
	glVertex2f(0.32f, 0.36f);//11
	glVertex2f(0.36f, 0.36f);//10
	glVertex2f(0.4f, 0.36f);//11
	glVertex2f(0.44f, 0.36f);//10
	glVertex2f(0.48f, 0.36f);//11
	glVertex2f(0.52f, 0.36f);//10
	glVertex2f(0.56f, 0.36f);//11
	glVertex2f(0.6f, 0.36f);//10
	glVertex2f(0.64f, 0.36f);//11
	glVertex2f(0.68f, 0.36f);//10
	glVertex2f(0.72f, 0.36f);//11

	//line 6 white

	glVertex2f(-0.28f, 0.4f);//2
	glVertex2f(-0.24f, 0.4f);//1
	glVertex2f(-0.2f, 0.4f);//2
	glVertex2f(-0.16f, 0.4f);//1
	glVertex2f(-0.12f, 0.4f);//2
	glVertex2f(-0.08f, 0.4f);//1
	glVertex2f(-0.04f, 0.4f);//2
	glVertex2f(0.0f, 0.4f);//3
	glVertex2f(0.04f, 0.4f);//4
	glVertex2f(0.08f, 0.4f);//5
	glVertex2f(0.12f, 0.4f);//6
	glVertex2f(0.16f, 0.4f);//7
	glVertex2f(0.2f, 0.4f);//8
	glVertex2f(0.24f, 0.4f);//9
	glVertex2f(0.28f, 0.4f);//10
	glVertex2f(0.32f, 0.4f);//11
	glVertex2f(0.36f, 0.4f);//10
	glVertex2f(0.4f, 0.4f);//11
	glVertex2f(0.44f, 0.4f);//10
	glVertex2f(0.48f, 0.4f);//11
	glVertex2f(0.52f, 0.4f);//10
	glVertex2f(0.56f, 0.4f);//11
	glVertex2f(0.6f, 0.4f);//10
	glVertex2f(0.64f, 0.4f);//11
	glVertex2f(0.68f, 0.4f);//10
	glVertex2f(0.72f, 0.4f);//11


	glVertex2f(-0.28f, 0.44f);//2
	glVertex2f(-0.24f, 0.44f);//1
	glVertex2f(-0.2f, 0.44f);//2
	glVertex2f(-0.16f, 0.44f);//1
	glVertex2f(-0.12f, 0.44f);//2
	glVertex2f(-0.08f, 0.44f);//1
	glVertex2f(-0.04f, 0.44f);//2
	glVertex2f(0.0f, 0.44f);//3
	glVertex2f(0.04f, 0.44f);//4
	glVertex2f(0.08f, 0.44f);//5
	glVertex2f(0.12f, 0.44f);//6
	glVertex2f(0.16f, 0.44f);//7
	glVertex2f(0.2f, 0.44f);//8
	glVertex2f(0.24f, 0.44f);//9
	glVertex2f(0.28f, 0.44f);//10
	glVertex2f(0.32f, 0.44f);//11
	glVertex2f(0.36f, 0.44f);//10
	glVertex2f(0.4f, 0.44f);//11
	glVertex2f(0.44f, 0.44f);//10
	glVertex2f(0.48f, 0.44f);//11
	glVertex2f(0.52f, 0.44f);//10
	glVertex2f(0.56f, 0.44f);//11
	glVertex2f(0.6f, 0.44f);//10
	glVertex2f(0.64f, 0.44f);//11
	glVertex2f(0.68f, 0.44f);//10
	glVertex2f(0.72f, 0.44f);//11


	//line 7 white
	glVertex2f(-0.28f, 0.48f);//2
	glVertex2f(-0.24f, 0.48f);//1
	glVertex2f(-0.2f, 0.48f);//2
	glVertex2f(-0.16f, 0.48f);//1
	glVertex2f(-0.12f, 0.48f);//2
	glVertex2f(-0.08f, 0.48f);//1
	glVertex2f(-0.04f, 0.48f);//2
	glVertex2f(0.16f, 0.48f);//7
	glVertex2f(0.2f, 0.48f);//8
	glVertex2f(0.24f, 0.48f);//9
	glVertex2f(0.28f, 0.48f);//10
	glVertex2f(0.32f, 0.48f);//11
	glVertex2f(0.36f, 0.48f);//10
	glVertex2f(0.4f, 0.48f);//11
	glVertex2f(0.44f, 0.48f);//10
	glVertex2f(0.48f, 0.48f);//11
	glVertex2f(0.52f, 0.48f);//10
	glVertex2f(0.56f, 0.48f);//11
	glVertex2f(0.6f, 0.48f);//10
	glVertex2f(0.64f, 0.48f);//11
	glVertex2f(0.68f, 0.48f);//10
	glVertex2f(0.72f, 0.48f);//11



	glVertex2f(-0.28f, 0.52f);//2
	glVertex2f(-0.24f, 0.52f);//1
	glVertex2f(-0.2f, 0.52f);//2
	glVertex2f(-0.16f, 0.52f);//1
	glVertex2f(-0.12f, 0.52f);//2
	glVertex2f(-0.08f, 0.52f);//1
	glVertex2f(-0.04f, 0.52f);//2
	glVertex2f(0.16f, 0.52f);//7
	glVertex2f(0.2f, 0.52f);//8
	glVertex2f(0.24f, 0.52f);//9
	glVertex2f(0.28f, 0.52f);//10
	glVertex2f(0.32f, 0.52f);//11
	glVertex2f(0.36f, 0.52f);//10
	glVertex2f(0.4f, 0.52f);//11
	glVertex2f(0.44f, 0.52f);//10
	glVertex2f(0.48f, 0.52f);//11
	glVertex2f(0.52f, 0.52f);//10
	glVertex2f(0.56f, 0.52f);//11
	glVertex2f(0.6f, 0.52f);//10
	glVertex2f(0.64f, 0.52f);//11
	glVertex2f(0.68f, 0.52f);//10
	glVertex2f(0.72f, 0.52f);//11

	//line 8 white
	glVertex2f(0.08f, 0.56f);//11
	glVertex2f(0.12f, 0.56f);//10
	glVertex2f(0.16f, 0.56f);//7
	glVertex2f(0.2f, 0.56f);//8
	glVertex2f(0.24f, 0.56f);//9
	glVertex2f(0.28f, 0.56f);//10
	glVertex2f(0.32f, 0.56f);//11
	glVertex2f(0.36f, 0.56f);//10
	glVertex2f(0.56f, 0.56f);//11
	glVertex2f(0.6f, 0.56f);//10
	glVertex2f(0.64f, 0.56f);//11


	glVertex2f(0.08f, 0.6f);//11
	glVertex2f(0.12f, 0.6f);//10
	glVertex2f(0.16f, 0.6f);//7
	glVertex2f(0.2f, 0.6f);//8
	glVertex2f(0.24f, 0.6f);//9
	glVertex2f(0.28f, 0.6f);//10
	glVertex2f(0.32f, 0.6f);//11
	glVertex2f(0.36f, 0.6f);//10
	glVertex2f(0.56f, 0.6f);//11
	glVertex2f(0.6f, 0.6f);//10
	glVertex2f(0.64f, 0.6f);//11

	//line 9 white

	glVertex2f(0.0f, 0.64f);//10
	glVertex2f(0.04f, 0.64f);//11
	glVertex2f(0.08f, 0.64f);//11
	glVertex2f(0.12f, 0.64f);//10
	glVertex2f(0.16f, 0.64f);//7
	glVertex2f(0.2f, 0.64f);//8
	glVertex2f(0.24f, 0.64f);//9
	glVertex2f(0.28f, 0.64f);//10
	glVertex2f(0.32f, 0.64f);//11
	glVertex2f(0.36f, 0.64f);//10

	glVertex2f(0.0f, 0.68f);//10
	glVertex2f(0.04f, 0.68f);//11
	glVertex2f(0.08f, 0.68f);//11
	glVertex2f(0.12f, 0.68f);//10
	glVertex2f(0.16f, 0.68f);//7
	glVertex2f(0.2f, 0.68f);//8
	glVertex2f(0.24f, 0.68f);//9
	glVertex2f(0.28f, 0.68f);//10
	glVertex2f(0.32f, 0.68f);//11
	glVertex2f(0.36f, 0.68f);//10

	//lone 11 white 
	glVertex2f(0.0f, 0.72f);//10
	glVertex2f(0.04f, 0.72f);//11
	glVertex2f(0.08f, 0.72f);//11
	glVertex2f(0.12f, 0.72f);//10
	glVertex2f(0.16f, 0.72f);//7
	glVertex2f(0.2f, 0.72f);//8
	glVertex2f(0.24f, 0.72f);//9
	glVertex2f(0.28f, 0.72f);//10
	glVertex2f(0.32f, 0.72f);//11
	glVertex2f(0.36f, 0.72f);//10

	glVertex2f(0.0f, 0.76f);
	glVertex2f(0.04f, 0.76f);
	glVertex2f(0.08f, 0.76f);
	glVertex2f(0.12f, 0.76f);
	glVertex2f(0.16f, 0.76f);
	glVertex2f(0.2f, 0.76f); \
		glVertex2f(0.24f, 0.76f);
	glVertex2f(0.28f, 0.76f);
	glVertex2f(0.32f, 0.76f);
	glVertex2f(0.36f, 0.76f);

	//line 12 white
	glVertex2f(0.08f, 0.8f);
	glVertex2f(0.12f, 0.8f);
	glVertex2f(0.16f, 0.8f);
	glVertex2f(0.2f, 0.8f);
	glVertex2f(0.24f, 0.8f);
	glVertex2f(0.28f, 0.8f);
	glVertex2f(0.32f, 0.8f);
	glVertex2f(0.36f, 0.8f);

	glVertex2f(0.08f, 0.84f);
	glVertex2f(0.12f, 0.84f);
	glVertex2f(0.16f, 0.84f);
	glVertex2f(0.2f, 0.84f);
	glVertex2f(0.24f, 0.84f);
	glVertex2f(0.28f, 0.84f);
	glVertex2f(0.32f, 0.84f);
	glVertex2f(0.36f, 0.84f);
	glEnd();
	glFlush();
}


void laila()
{
	glColor3f(0.9f, 0.7f, 0.3f);
	facecir(0.14, 0.47, 0.20);
	// drawing the face
	glColor3f(0.93f, 0.75f, 0.68f);
	facecir(0.14, 0.39, 0.15);

	glPointSize(4.0f);
	glBegin(GL_POINTS);
	glColor3f(0.82f, 0.58f, 0.5f);
	glVertex2f(0.28f, 0.38f);//
	glVertex2f(0.28f, 0.36f);//
	glVertex2f(0.28f, 0.34f);//
	glVertex2f(0.27f, 0.32f);//
	glVertex2f(0.25f, 0.30f);//
	glVertex2f(0.23f, 0.28f);//
	glVertex2f(0.20f, 0.26f);//
	glVertex2f(0.18f, 0.24f);//
	glVertex2f(0.16f, 0.24f);//
	glVertex2f(0.14f, 0.24f);//
	glVertex2f(0.12f, 0.24f);//
	glVertex2f(0.10f, 0.24f);//
	glVertex2f(0.08f, 0.26f);//
	glVertex2f(0.06f, 0.28f);//
	glVertex2f(0.04f, 0.30f);//
	glVertex2f(0.01f, 0.32f);//

	glEnd();
	glFlush();
	//head band
	glPointSize(7.0f);
	glBegin(GL_POINTS);
	glColor3f(1.0f, 0.1f, 0.3f);
	glVertex2f(-0.07, 0.42f);
	glVertex2f(-0.07, 0.45f);
	glVertex2f(-0.05, 0.48f);
	glVertex2f(-0.03, 0.51f);
	glVertex2f(-0.01, 0.54f);
	glVertex2f(0.02, 0.56f);
	glVertex2f(0.05, 0.58f);
	glVertex2f(0.085, 0.60f);
	glVertex2f(0.11, 0.62f);
	glVertex2f(0.13, 0.62f);
	glVertex2f(0.15, 0.62f);
	glVertex2f(0.18, 0.60f);
	glVertex2f(0.20, 0.60f);
	glVertex2f(0.22, 0.58f);
	glVertex2f(0.25, 0.58f);
	glVertex2f(0.27, 0.56f);
	glVertex2f(0.30, 0.54f);
	glVertex2f(0.32, 0.52f);
	glVertex2f(0.32, 0.54f);
	glVertex2f(0.30, 0.54f);
	glVertex2f(0.30, 0.56f);
	glVertex2f(0.32, 0.57f);
	glVertex2f(0.32, 0.59f);
	glVertex2f(0.30, 0.62f);
	glVertex2f(0.30, 0.59f);
	glVertex2f(0.28, 0.59f);
	glVertex2f(0.27, 0.64f);
	glVertex2f(0.27, 0.61f);
	glVertex2f(0.25, 0.66f);
	glVertex2f(0.24, 0.64f);
	glVertex2f(0.235, 0.61f);
	glVertex2f(0.22, 0.68f);
	glVertex2f(0.20, 0.68f);
	glVertex2f(0.18, 0.70f);
	glVertex2f(0.16, 0.70f);
	glVertex2f(0.14, 0.72f);
	glVertex2f(0.12, 0.72f);
	glVertex2f(0.10, 0.72f);
	glVertex2f(0.08, 0.72f);
	glVertex2f(0.06, 0.74f);
	glVertex2f(0.04, 0.74f);
	glVertex2f(0.02, 0.74f);
	glVertex2f(0.0, 0.74f);
	glVertex2f(-0.02, 0.72f);
	glVertex2f(-0.05, 0.70f);
	glVertex2f(-0.08, 0.68f);
	glVertex2f(-0.11, 0.66f);
	glVertex2f(-0.11, 0.64f);
	glVertex2f(-0.14, 0.62f);
	glVertex2f(-0.14, 0.60f);
	glVertex2f(-0.17, 0.58f);
	glVertex2f(-0.17, 0.56f);
	glVertex2f(-0.17, 0.54f);
	glVertex2f(-0.19, 0.52f);
	glVertex2f(-0.19, 0.50f);
	glVertex2f(-0.22, 0.48f);
	glVertex2f(-0.22, 0.46f);
	glVertex2f(-0.22, 0.44f);
	glVertex2f(-0.19, 0.42f);
	glVertex2f(-0.17, 0.40f);
	glVertex2f(-0.14, 0.38f);
	glVertex2f(-0.14, 0.36f);
	glVertex2f(-0.12, 0.35f);
	glVertex2f(-0.10, 0.35f);
	glVertex2f(-0.08, 0.35f);
	glVertex2f(-0.08, 0.39f);
	glVertex2f(-0.08, 0.37f);
	glVertex2f(-0.10, 0.37f);
	glVertex2f(-0.10, 0.39f);
	glVertex2f(-0.10, 0.41f);///////////
	glVertex2f(-0.10, 0.44f);
	glVertex2f(-0.10, 0.47f);
	glVertex2f(-0.10, 0.50f);
	glVertex2f(-0.10, 0.53f);
	glVertex2f(-0.10, 0.56f);
	glVertex2f(-0.10, 0.59f);
	glVertex2f(-0.10, 0.61f);
	glVertex2f(-0.10, 0.64f);
	glVertex2f(-0.10, 0.65f);//
	glVertex2f(-0.12, 0.37f);
	glVertex2f(-0.12, 0.39f);
	glVertex2f(-0.12, 0.41f);
	glVertex2f(-0.12, 0.44f);
	glVertex2f(-0.12, 0.47f);
	glVertex2f(-0.12, 0.50f);
	glVertex2f(-0.12, 0.53f);
	glVertex2f(-0.12, 0.56f);
	glVertex2f(-0.12, 0.59f);
	glVertex2f(-0.12, 0.61f);//
	glVertex2f(-0.15, 0.41f);
	glVertex2f(-0.15, 0.44f);
	glVertex2f(-0.15, 0.47f);
	glVertex2f(-0.15, 0.50f);
	glVertex2f(-0.15, 0.53f);
	glVertex2f(-0.15, 0.56f);
	glVertex2f(-0.15, 0.59f);
	glVertex2f(-0.15, 0.61f);//
	glVertex2f(-0.19, 0.45f);
	glVertex2f(-0.19, 0.47f);//
	glVertex2f(-0.17, 0.43f);
	glVertex2f(-0.17, 0.45f);
	glVertex2f(-0.17, 0.48f);
	glVertex2f(-0.17, 0.51f);
	glVertex2f(-0.07, 0.43f);//
	glVertex2f(-0.07, 0.45f);
	glVertex2f(-0.07, 0.48f);
	glVertex2f(-0.07, 0.51f);
	glVertex2f(-0.07, 0.53f);
	glVertex2f(-0.07, 0.56f);
	glVertex2f(-0.07, 0.59f);
	glVertex2f(-0.07, 0.61f);
	glVertex2f(-0.07, 0.64f);
	glVertex2f(-0.07, 0.67f);


	glVertex2f(-0.04, 0.53f);
	glVertex2f(-0.04, 0.56f);
	glVertex2f(-0.04, 0.59f);
	glVertex2f(-0.04, 0.61f);
	glVertex2f(-0.04, 0.64f);
	glVertex2f(-0.04, 0.67f);
	glVertex2f(-0.04, 0.70f);

	glVertex2f(-0.01, 0.56f);//
	glVertex2f(-0.01, 0.59f);
	glVertex2f(-0.01, 0.61f);
	glVertex2f(-0.01, 0.64f);
	glVertex2f(-0.01, 0.67f);
	glVertex2f(-0.01, 0.705f);

	glVertex2f(0.01, 0.56f);//
	glVertex2f(0.01, 0.59f);
	glVertex2f(0.01, 0.61f);
	glVertex2f(0.01, 0.64f);
	glVertex2f(0.01, 0.67f);
	glVertex2f(0.01, 0.705f);


	glVertex2f(0.04, 0.59f);//
	glVertex2f(0.04, 0.61f);
	glVertex2f(0.04, 0.64f);
	glVertex2f(0.04, 0.67f);
	glVertex2f(0.04, 0.705f);

	glVertex2f(0.06, 0.61f);//
	glVertex2f(0.06, 0.64f);
	glVertex2f(0.06, 0.67f);
	glVertex2f(0.06, 0.705f);

	glVertex2f(0.08, 0.63f);//
	glVertex2f(0.08, 0.65f);
	glVertex2f(0.08, 0.67f);
	glVertex2f(0.08, 0.69f);

	glVertex2f(0.10, 0.65f);//
	glVertex2f(0.10, 0.67f);
	glVertex2f(0.10, 0.69f);


	glVertex2f(0.13, 0.65f);//
	glVertex2f(0.13, 0.67f);
	glVertex2f(0.13, 0.69f);


	glVertex2f(0.15, 0.65f);//
	glVertex2f(0.15, 0.67f);
	glVertex2f(0.15, 0.69f);


	glVertex2f(0.18, 0.65f);//
	glVertex2f(0.18, 0.67f);
	glVertex2f(0.18, 0.69f);
	glVertex2f(0.18, 0.63f);//

	glVertex2f(0.22, 0.67f);
	glVertex2f(0.21, 0.69f);
	glVertex2f(0.21, 0.65f);//
	glVertex2f(0.21, 0.63f);
	glVertex2f(0.21, 0.60f);

	glEnd();
	glFlush();

	//head band
	glPointSize(5.0f);
	glBegin(GL_POINTS);
	glColor3f(0.7f, 0.0f, 0.0f);

	glVertex2f(0.33, 0.51f);
	glVertex2f(0.33, 0.53f);
	glVertex2f(0.33, 0.55f);
	glVertex2f(0.33, 0.57f);
	glVertex2f(0.33, 0.59f);
	glVertex2f(0.30, 0.60f);
	glVertex2f(0.30, 0.62f);

	glVertex2f(0.27, 0.64f);

	glVertex2f(0.25, 0.66f);

	glVertex2f(0.23, 0.68f);

	glVertex2f(0.21, 0.70f);
	glVertex2f(0.19, 0.70f);
	glVertex2f(0.17, 0.72f);
	glVertex2f(0.15, 0.72f);
	glVertex2f(0.13, 0.72f);
	glVertex2f(0.11, 0.72f);
	glVertex2f(0.09, 0.74f);
	glVertex2f(0.07, 0.74f);
	glVertex2f(0.05, 0.74f);
	glVertex2f(0.03, 0.74f);
	glVertex2f(0.0, 0.74f);
	glVertex2f(-0.02, 0.72f);
	glVertex2f(-0.05, 0.70f);
	glVertex2f(-0.08, 0.68f);
	glVertex2f(-0.11, 0.66f);
	glVertex2f(-0.11, 0.64f);
	glVertex2f(-0.15, 0.62f);
	glVertex2f(-0.15, 0.60f);
	glVertex2f(-0.17, 0.58f);
	glVertex2f(-0.17, 0.56f);
	glVertex2f(-0.17, 0.54f);
	glVertex2f(-0.19, 0.52f);
	glVertex2f(-0.19, 0.50f);
	glVertex2f(-0.22, 0.48f);
	glVertex2f(-0.22, 0.46f);
	glVertex2f(-0.22, 0.44f);
	glVertex2f(-0.19, 0.42f);
	glVertex2f(-0.17, 0.40f);
	glVertex2f(-0.15, 0.38f);
	glVertex2f(-0.15, 0.36f);
	glVertex2f(-0.13, 0.35f);
	glVertex2f(-0.11, 0.35f);
	glVertex2f(-0.09, 0.35f);
	glVertex2f(-0.07, 0.35f);
	glVertex2f(-0.05, 0.37f);
	glEnd();
	glFlush();

	//right Eye
	glPointSize(4.0f);
	glBegin(GL_POINTS);
	glColor3f(0.0f, 0.0f, 0.0f);
	glVertex2f(0.19f, 0.42f);//
	glVertex2f(0.20f, 0.42f);//
	glVertex2f(0.21f, 0.42f);//
	glVertex2f(0.22f, 0.42f);//
	glVertex2f(0.23f, 0.42f);//
	glVertex2f(0.22f, 0.41f);//
	glVertex2f(0.22f, 0.40f);//
	glVertex2f(0.21f, 0.40f);//
	glVertex2f(0.21f, 0.41f);//
	glVertex2f(0.22f, 0.39f);//
	glColor3f(0.5f, 0.5f, 0.5f);
	glVertex2f(0.20f, 0.41f);// grey shadow
	glColor3f(1.0f, 1.0f, 1.0f); //setting the color th white
	glVertex2f(0.20f, 0.40f);// white eye
	glVertex2f(0.20f, 0.39f);//
	glEnd();
	glFlush();
	//Left eye
	glPointSize(4.0f);
	glBegin(GL_POINTS);
	glColor3f(0.0f, 0.0f, 0.0f);
	glVertex2f(0.11f, 0.42f);
	glVertex2f(0.10f, 0.42f);
	glVertex2f(0.09f, 0.42f);
	glVertex2f(0.08f, 0.42f);
	glVertex2f(0.07f, 0.42f);
	glVertex2f(0.10f, 0.41f);//
	glVertex2f(0.10f, 0.40f);//
	glVertex2f(0.10f, 0.39f);//
	glVertex2f(0.09f, 0.40f);//
	glVertex2f(0.09f, 0.39f);//
	glColor3f(0.5f, 0.5f, 0.5f);
	glVertex2f(0.08f, 0.41f);// grey shadow
	glColor3f(1.0f, 1.0f, 1.0f); //setting the color to white
	glVertex2f(0.08f, 0.40f);// white eye
	glVertex2f(0.08f, 0.39f);//
	glEnd();
	glFlush();

	//لمعة العين
	glPointSize(1.0f);
	glBegin(GL_POINTS);
	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex2f(0.23f, 0.40f);//for right eye
	glVertex2f(0.11f, 0.40f);//for left eye
	glEnd();
	glFlush();




	//nose and lips
	glPointSize(2.0f);
	glBegin(GL_POINTS);
	glColor4f(0.8f, 0.6f, 0.4f, 0.4f);
	glVertex2f(0.18f, 0.34f); //nose
	glVertex2f(0.15f, 0.29f); //lips
	glVertex2f(0.16f, 0.29f); //lips
	glVertex2f(0.14f, 0.29f); //lips
	glEnd();
	glFlush();
	//checks
	glPointSize(4.0f);
	glBegin(GL_POINTS);
	glColor4f(0.9f, 0.5f, 0.6f, 0.0f);
	glVertex2f(0.22f, 0.36f);
	glVertex2f(0.23f, 0.35f);
	glVertex2f(0.24f, 0.37f);
	glVertex2f(0.25f, 0.38f);
	glVertex2f(0.25f, 0.36f);

	glVertex2f(0.10f, 0.36f);
	glVertex2f(0.08f, 0.36f);
	glVertex2f(0.07f, 0.37f);
	glVertex2f(0.06f, 0.38f);
	glVertex2f(0.06f, 0.36f);
	glVertex2f(0.07f, 0.35f);
	glEnd();
	glFlush();

	//ضل للوجه
	glPointSize(4.0f);
	glBegin(GL_POINTS);
	glColor4f(0.8f, 0.6f, 0.4f, 0.4f);
	glVertex2f(0.1f, 0.26f);
	glVertex2f(0.06f, 0.30f);
	glVertex2f(0.18f, 0.26f);
	glVertex2f(0.21f, 0.28f);
	glVertex2f(0.23f, 0.30f);
	glEnd();
	glFlush();


	glPointSize(8.0f);
	glBegin(GL_POINTS);
	glColor3f(0.9f, 0.7f, 0.3f);
	glVertex2f(-0.03, 0.48f);
	glVertex2f(-0.01, 0.47f);
	glVertex2f(-0.01, 0.45);
	glVertex2f(0.03, 0.47f);
	glVertex2f(0.06, 0.47f);
	glVertex2f(0.13, 0.47f);
	glVertex2f(0.17, 0.47f);
	glVertex2f(0.21, 0.47f);


	glVertex2f(0.03, 0.51f);
	glVertex2f(0.06, 0.51f);
	glVertex2f(0.09, 0.51f);
	glVertex2f(0.12, 0.51f);
	glVertex2f(0.15, 0.51f);
	glVertex2f(0.18, 0.51f);
	glVertex2f(0.21, 0.51f);

	glVertex2f(0.03, 0.54f);
	glVertex2f(0.06, 0.54f);
	glVertex2f(0.09, 0.54f);
	glVertex2f(0.12, 0.54f);
	glVertex2f(0.15, 0.54f);
	glVertex2f(0.18, 0.54f);
	glVertex2f(0.21, 0.54f);

	glVertex2f(0.03, 0.56f);
	glVertex2f(0.06, 0.58f);
	glVertex2f(0.09, 0.58f);
	glVertex2f(0.12, 0.58f);
	glVertex2f(0.15, 0.58f);
	glVertex2f(0.18, 0.58f);
	glVertex2f(0.21, 0.58f);




	glVertex2f(0.12, 0.61f);
	glVertex2f(0.15, 0.61f);
	glVertex2f(0.18, 0.61f);
	glVertex2f(0.2, 0.61f);

	glVertex2f(0.0, 0.51f);
	glVertex2f(0.0, 0.54f);
	glVertex2f(-0.02, 0.37f);
	glVertex2f(-0.02, 0.34f);
	glVertex2f(-0.02, 0.31f);
	glVertex2f(-0.02, 0.27f);

	glVertex2f(0.23, 0.51f);
	glVertex2f(0.23, 0.54f);
	glVertex2f(0.23, 0.57f);
	glVertex2f(0.23, 0.60f);

	glVertex2f(0.26, 0.48f);
	glVertex2f(0.26, 0.51f);
	glVertex2f(0.26, 0.54f);
	glVertex2f(0.26, 0.57f);

	glVertex2f(0.29, 0.43f);
	glVertex2f(0.30, 0.48f);
	glVertex2f(0.30, 0.51f);
	glVertex2f(0.30, 0.54f);
	// the end of filling the bangs


	glVertex2f(-0.07f, 0.34);
	glVertex2f(-0.07f, 0.30f);
	glVertex2f(-0.07f, 0.26);
	glVertex2f(-0.07f, 0.22f);
	glVertex2f(-0.07f, 0.18);
	glVertex2f(-0.07f, 0.14f);
	glVertex2f(-0.07f, 0.10);
	glVertex2f(-0.07f, 0.06f);
	glVertex2f(-0.07f, 0.04);
	glVertex2f(-0.05f, 0.03f);

	/////////////////////////////////////




	glVertex2f(-0.09f, 0.30f);
	glVertex2f(-0.09f, 0.26);
	glVertex2f(-0.09f, 0.22f);
	glVertex2f(-0.09f, 0.18);
	glVertex2f(-0.09f, 0.14f);
	glVertex2f(-0.09f, 0.10);
	glVertex2f(-0.09f, 0.06f);
	/////////////////////////////////////

	glVertex2f(-0.03f, 0.07f);
	glVertex2f(-0.03f, 0.10f);
	glVertex2f(-0.03f, 0.14f);
	glVertex2f(-0.03f, 0.17f);
	glVertex2f(-0.03f, 0.20f);
	glVertex2f(-0.03f, 0.23f);
	glVertex2f(-0.03f, 0.26f);

	glVertex2f(0.0f, 0.14f);
	glVertex2f(0.0f, 0.17f);
	glVertex2f(0.0f, 0.20f);
	glVertex2f(0.0f, 0.23f);
	//////////////////////////////////////
	glVertex2f(0.3f, 0.38f);
	glVertex2f(0.3f, 0.35f);
	glVertex2f(0.3f, 0.33f);
	glVertex2f(0.3f, 0.3f);
	glVertex2f(0.3f, 0.28f);
	/////////////////////////////////////


	glColor3f(0.7f, 0.5f, 0.3f);
	glVertex2f(0.02f, 0.20f);
	glVertex2f(0.02f, 0.22f);
	glVertex2f(0.02f, 0.25f);
	glVertex2f(0.02f, 0.27f);
	glVertex2f(0.01f, 0.285f);

	glVertex2f(0.04f, 0.22f);
	glVertex2f(0.04f, 0.25f);
	glVertex2f(0.04f, 0.27f);

	glVertex2f(0.07f, 0.22f);
	glVertex2f(0.07f, 0.25f);

	glVertex2f(-0.01f, 0.20f);
	glVertex2f(-0.01f, 0.23f);

	glVertex2f(-0.01f, 0.18f);








	glEnd();
	glFlush();
	//hair
	glPointSize(3.0);
	glBegin(GL_POINTS);
	glColor3f(0.7f, 0.5f, 0.3f);


	glVertex2f(0.0, 0.36f);
	glVertex2f(0.0, 0.34f);

	glVertex2f(0.0, 0.32f);
	glVertex2f(0.0, 0.30f);
	glVertex2f(0.0, 0.28f);
	glVertex2f(-0.01, 0.26f);
	glVertex2f(0.0, 0.42f);
	glVertex2f(0.0, 0.40f);
	glVertex2f(0.0, 0.38f);

	////////////////////////////////


	glVertex2f(-0.03, 0.25f);
	glVertex2f(-0.04, 0.27f);
	glVertex2f(-0.04, 0.29f);
	glVertex2f(-0.04, 0.31f);
	glVertex2f(-0.04, 0.33f);
	glVertex2f(-0.04, 0.35f);
	glVertex2f(-0.04, 0.37f);
	glVertex2f(-0.05, 0.39f);
	glVertex2f(-0.05, 0.41f);
	glVertex2f(-0.05, 0.43f);
	glVertex2f(-0.05, 0.45f);
	glVertex2f(-0.05, 0.47f);
	glVertex2f(-0.05, 0.49f);
	glVertex2f(-0.03, 0.51f);
	glVertex2f(-0.03, 0.53f);
	glVertex2f(-0.01, 0.55f);
	glVertex2f(0.01, 0.57f);
	glVertex2f(0.03, 0.59f);
	glVertex2f(0.05, 0.59f);
	glVertex2f(0.07, 0.61f);
	glVertex2f(0.09, 0.61f);
	glVertex2f(0.11, 0.63f);
	glVertex2f(0.13, 0.63f);
	glVertex2f(0.15, 0.63f);
	glVertex2f(0.17, 0.63f);
	glVertex2f(0.19, 0.63f);
	glVertex2f(0.21, 0.63f);

	glVertex2f(0.23, 0.61f);
	glVertex2f(0.25, 0.61f);

	glVertex2f(0.27, 0.59f);
	glVertex2f(0.29, 0.57f);
	glVertex2f(0.31, 0.55f);


	glVertex2f(0.33, 0.53f);
	glVertex2f(0.33, 0.51f);
	glVertex2f(0.33, 0.49f);








	////////// الغرة
	glVertex2f(0.02, 0.44f);
	glVertex2f(0.04, 0.44f);
	glVertex2f(0.06, 0.44f);
	glVertex2f(0.08, 0.44f);
	glVertex2f(0.12, 0.44f);
	glVertex2f(0.16, 0.46f);
	glVertex2f(0.08, 0.46f);
	glVertex2f(0.08, 0.48f);
	glVertex2f(0.10, 0.48f);
	glVertex2f(0.10, 0.50f);
	glVertex2f(0.10, 0.52f);
	glVertex2f(0.10, 0.54f);




	///////////

	glVertex2f(0.34, 0.47f);
	glVertex2f(0.34, 0.45f);
	glVertex2f(0.34, 0.43f);
	glVertex2f(0.32, 0.41f);
	glVertex2f(0.32f, 0.40f);
	glVertex2f(0.30f, 0.40f);
	glVertex2f(0.28f, 0.40f);
	glVertex2f(0.26f, 0.40f);
	glVertex2f(0.26f, 0.40f);
	glVertex2f(0.26f, 0.42f);
	glVertex2f(0.26f, 0.44f);
	glVertex2f(0.26f, 0.46f);
	glVertex2f(0.24f, 0.46f);
	glVertex2f(0.24f, 0.48f);
	glVertex2f(0.24f, 0.50f);
	glVertex2f(0.24f, 0.52f);

	glVertex2f(0.22f, 0.44f);
	glVertex2f(0.20f, 0.44f);
	glVertex2f(0.18f, 0.44f);
	glVertex2f(0.16f, 0.44f);
	glVertex2f(0.14f, 0.44f);

	//the rest of the the hair
	glVertex2f(-0.1f, 0.32f);
	glVertex2f(-0.1f, 0.30f);
	glVertex2f(-0.12f, 0.28f);
	glVertex2f(-0.12f, 0.26f);
	glVertex2f(-0.12f, 0.24f);
	glVertex2f(-0.12f, 0.22f);
	glVertex2f(-0.12f, 0.20f);
	glVertex2f(-0.12f, 0.18f);
	glVertex2f(-0.12f, 0.16f);
	glVertex2f(-0.12f, 0.14f);
	glVertex2f(-0.12f, 0.12f);
	glVertex2f(-0.12f, 0.10f);
	glVertex2f(-0.10f, 0.08f);
	glVertex2f(-0.10f, 0.06f);
	glVertex2f(-0.10f, 0.04f);
	glVertex2f(-0.08f, 0.02f);
	glVertex2f(-0.06f, 0.0f);
	glVertex2f(-0.04f, 0.0f);
	glVertex2f(-0.02f, 0.02f);
	////////////////////////////////////////
	glVertex2f(0.32f, 0.38f);
	glVertex2f(0.32f, 0.36f);
	glVertex2f(0.32f, 0.34f);
	glVertex2f(0.32f, 0.32f);
	glVertex2f(0.32f, 0.30f);
	glVertex2f(0.30f, 0.28f);
	glVertex2f(0.29f, 0.26f);


	glVertex2f(0.28f, 0.38f);
	glVertex2f(0.28f, 0.36f);
	glVertex2f(0.28f, 0.34f);
	glVertex2f(0.28f, 0.32f);
	glVertex2f(0.28f, 0.30f);
	glVertex2f(0.28f, 0.28f);
	glVertex2f(0.28f, 0.26f);

	glEnd();
	glFlush();



	//body

	glPointSize(6.0f);
	glBegin(GL_POINTS);
	//neck
	glColor3f(0.79f, 0.5f, 0.5f);
	glVertex2f(0.11f, 0.21f);
	glVertex2f(0.13f, 0.21f);
	glVertex2f(0.15f, 0.21f);
	glVertex2f(0.17f, 0.21f);



	glEnd();
	glFlush();

	//dress
	glPointSize(5.0f);
	glBegin(GL_POINTS);
	glColor3f(0.5f, 0.4f, 0.3f);
	glVertex2f(0.11f, 0.19f);
	glVertex2f(0.13f, 0.19f);
	glVertex2f(0.15f, 0.19f);
	glVertex2f(0.17f, 0.19f);
	glVertex2f(0.19f, 0.21f);
	glVertex2f(0.21f, 0.21f);
	glVertex2f(0.23f, 0.19f);

	glVertex2f(0.25f, 0.19f);
	glVertex2f(0.27f, 0.17f);
	glVertex2f(0.27f, 0.15f);
	glVertex2f(0.29f, 0.13f);
	glVertex2f(0.31f, 0.11f);
	glVertex2f(0.31f, 0.09f);
	glVertex2f(0.31f, 0.07f);
	//end of the right sholder

	glVertex2f(0.09f, 0.21f);
	glVertex2f(0.07f, 0.21f);
	glVertex2f(0.05f, 0.19f);
	glVertex2f(0.03f, 0.19f);
	glVertex2f(0.01f, 0.17f);
	glVertex2f(0.01f, 0.15f);
	glVertex2f(-0.01f, 0.13f);
	glVertex2f(-0.01f, 0.11f);
	glVertex2f(-0.03f, 0.09f);
	glVertex2f(-0.03f, 0.07f);

	glVertex2f(-0.03f, 0.05f);
	glVertex2f(-0.01f, 0.05f);
	glVertex2f(0.01f, 0.05f);
	glVertex2f(0.03f, 0.05f); //end of the left sholder
	glVertex2f(-0.05f, -0.15f);
	glVertex2f(-0.07f, -0.17f);
	glVertex2f(-0.07f, -0.19f);
	glVertex2f(-0.07f, -0.21f);
	glVertex2f(-0.05f, -0.21f);
	glVertex2f(-0.03f, -0.21f);
	glVertex2f(-0.01f, -0.21f);
	glVertex2f(0.01f, -0.23f);
	glVertex2f(0.03f, -0.23f);
	glVertex2f(0.05f, -0.23f);
	glVertex2f(0.07f, -0.23f);
	glVertex2f(0.09f, -0.23f);
	glVertex2f(0.11f, -0.23f);
	glVertex2f(0.13f, -0.23f);
	glVertex2f(0.15f, -0.23f);
	glVertex2f(0.17f, -0.23f);
	glVertex2f(0.19f, -0.23f);
	glVertex2f(0.21f, -0.23f);
	glVertex2f(0.23f, -0.23f);
	glVertex2f(0.25f, -0.23f);
	glVertex2f(0.27f, -0.23f);
	glVertex2f(0.29f, -0.21f);
	glVertex2f(0.31f, -0.21f);
	glVertex2f(0.33f, -0.19f);
	glVertex2f(0.33f, -0.17f);
	glVertex2f(0.33f, -0.15f);
	glVertex2f(0.33f, -0.13f);

	//تلوين الفستان

	glColor3f(0.5f, 0.0f, 0.0f);
	glVertex2f(0.06f, 0.20f);
	glVertex2f(0.06f, 0.18f);
	glVertex2f(0.06f, 0.16f);
	glVertex2f(0.06f, 0.14f);
	glVertex2f(0.06f, 0.12f);
	glVertex2f(0.06f, 0.10f);
	glVertex2f(0.06f, 0.08f);
	glVertex2f(0.06f, 0.06f);
	glVertex2f(0.06f, 0.04f);
	glVertex2f(0.06f, 0.02f);
	glVertex2f(0.08f, 0.02f);
	glVertex2f(0.10f, 0.02f);
	glVertex2f(0.12f, 0.02f);
	glVertex2f(0.14f, 0.02f);
	glVertex2f(0.16f, 0.02f);
	glVertex2f(0.18f, 0.02f);
	glVertex2f(0.20f, 0.02f);
	glVertex2f(0.22f, 0.02f);
	glVertex2f(0.24f, 0.02f);
	glVertex2f(0.24f, 0.04f);
	glVertex2f(0.24f, 0.06f);
	glVertex2f(0.22f, 0.06f);
	glVertex2f(0.20f, 0.06f);
	glVertex2f(0.26f, 0.08f);
	glVertex2f(0.26f, 0.10f);
	glVertex2f(0.26f, 0.12f);
	glVertex2f(0.22f, 0.14f);
	glVertex2f(0.20f, 0.14f);
	glVertex2f(0.18f, 0.14f);
	glVertex2f(0.16f, 0.14f);
	glVertex2f(0.14f, 0.14f);
	glVertex2f(0.12f, 0.14f);
	glVertex2f(0.10f, 0.14f);
	glVertex2f(0.08f, 0.14f);
	glVertex2f(0.07f, 0.14f);
	glVertex2f(0.07f, 0.16f);
	glVertex2f(0.07f, 0.18f);
	glVertex2f(0.24f, 0.14f);
	glVertex2f(0.19f, 0.16f);
	glVertex2f(0.19f, 0.18f);
	glVertex2f(0.20f, 0.18f);
	glVertex2f(0.19f, 0.20f);
	glVertex2f(0.20f, 0.16f);

	//filling the dress (chest)
	glColor3f(0.9f, 0.4f, 0.4f);
	glVertex2f(0.09f, 0.115f);
	glVertex2f(0.09f, 0.09f);
	glVertex2f(0.11f, 0.115f);
	glVertex2f(0.11f, 0.09f);
	glVertex2f(0.13f, 0.115f);
	glVertex2f(0.13f, 0.09f);
	glVertex2f(0.15f, 0.115f);
	glVertex2f(0.15f, 0.09f);
	glVertex2f(0.17f, 0.115f);
	glVertex2f(0.17f, 0.09f);
	glVertex2f(0.19f, 0.115f);
	glVertex2f(0.19f, 0.09f);
	glVertex2f(0.21f, 0.115f);
	glVertex2f(0.21f, 0.09f);
	glVertex2f(0.235f, 0.115f);
	glVertex2f(0.235f, 0.09f);

	glColor3f(0.9f, 0.3f, 0.3f);
	glVertex2f(0.09f, 0.06f);
	glVertex2f(0.09f, 0.04f);
	glVertex2f(0.11f, 0.06f);
	glVertex2f(0.11f, 0.04f);
	glVertex2f(0.13f, 0.06f);
	glVertex2f(0.13f, 0.04f);
	glVertex2f(0.15f, 0.06f);
	glVertex2f(0.15f, 0.04f);
	glVertex2f(0.17f, 0.06f);
	glVertex2f(0.17f, 0.04f);
	glVertex2f(0.19f, 0.06f);
	glVertex2f(0.19f, 0.04f);
	glVertex2f(0.21f, 0.06f);
	glVertex2f(0.21f, 0.04f);
	glVertex2f(0.235f, 0.04f);
	//filling the rest of the dress
	glColor3f(1.0f, 0.8f, 0.8f);

	glVertex2f(-0.045f, -0.18f);

	glVertex2f(-0.025f, -0.14f);
	glVertex2f(-0.025f, -0.16f);
	glVertex2f(-0.025f, -0.185f);


	glVertex2f(0.0f, -0.14f);
	glVertex2f(0.0f, -0.16f);
	glVertex2f(0.0f, -0.185f);


	glVertex2f(0.02f, -0.10f);
	glVertex2f(0.02f, -0.12f);
	glVertex2f(0.02f, -0.14f);
	glVertex2f(0.02f, -0.16f);
	glVertex2f(0.02f, -0.18f);
	glVertex2f(0.015f, -0.205f);

	glVertex2f(0.04f, -0.02f);
	glVertex2f(0.04f, -0.04f);
	glVertex2f(0.04f, -0.06f);
	glVertex2f(0.04f, -0.08f);
	glVertex2f(0.04f, -0.10f);
	glVertex2f(0.04f, -0.12f);
	glVertex2f(0.04f, -0.14f);
	glVertex2f(0.04f, -0.16f);
	glVertex2f(0.04f, -0.18f);
	glVertex2f(0.04f, -0.205f);




	glVertex2f(0.06f, 0.0f);
	glVertex2f(0.06f, -0.02f);
	glVertex2f(0.06f, -0.04f);
	glVertex2f(0.06f, -0.06f);
	glVertex2f(0.06f, -0.08f);
	glVertex2f(0.06f, -0.10f);
	glVertex2f(0.06f, -0.12f);
	glVertex2f(0.06f, -0.14f);
	glVertex2f(0.06f, -0.16f);
	glVertex2f(0.06f, -0.18f);
	glVertex2f(0.06f, -0.205f);

	glVertex2f(0.08f, 0.0f);
	glVertex2f(0.08f, -0.02f);
	glVertex2f(0.08f, -0.04f);
	glVertex2f(0.08f, -0.06f);
	glVertex2f(0.08f, -0.08f);
	glVertex2f(0.08f, -0.10f);
	glVertex2f(0.08f, -0.12f);
	glVertex2f(0.08f, -0.14f);
	glVertex2f(0.08f, -0.16f);
	glVertex2f(0.08f, -0.18f);
	glVertex2f(0.08f, -0.205f);

	glVertex2f(0.10f, 0.0f);
	glVertex2f(0.10f, -0.02f);
	glVertex2f(0.10f, -0.04f);
	glVertex2f(0.10f, -0.06f);
	glVertex2f(0.10f, -0.08f);
	glVertex2f(0.10f, -0.10f);
	glVertex2f(0.10f, -0.12f);
	glVertex2f(0.10f, -0.14f);
	glVertex2f(0.10f, -0.16f);
	glVertex2f(0.10f, -0.18f);
	glVertex2f(0.10f, -0.205f);

	glVertex2f(0.12f, 0.0f);
	glVertex2f(0.12f, -0.02f);
	glVertex2f(0.12f, -0.04f);
	glVertex2f(0.12f, -0.06f);
	glVertex2f(0.12f, -0.08f);
	glVertex2f(0.12f, -0.10f);
	glVertex2f(0.12f, -0.12f);
	glVertex2f(0.12f, -0.14f);
	glVertex2f(0.12f, -0.16f);
	glVertex2f(0.12f, -0.18f);
	glVertex2f(0.12f, -0.205f);

	glVertex2f(0.14f, 0.0f);
	glVertex2f(0.14f, -0.02f);
	glVertex2f(0.14f, -0.04f);
	glVertex2f(0.14f, -0.06f);
	glVertex2f(0.14f, -0.08f);
	glVertex2f(0.14f, -0.10f);
	glVertex2f(0.14f, -0.12f);
	glVertex2f(0.14f, -0.14f);
	glVertex2f(0.14f, -0.16f);
	glVertex2f(0.14f, -0.18f);
	glVertex2f(0.14f, -0.205f);

	glVertex2f(0.16f, 0.0f);
	glVertex2f(0.16f, -0.02f);
	glVertex2f(0.16f, -0.04f);
	glVertex2f(0.16f, -0.06f);
	glVertex2f(0.16f, -0.08f);
	glVertex2f(0.16f, -0.10f);
	glVertex2f(0.16f, -0.12f);
	glVertex2f(0.16f, -0.14f);
	glVertex2f(0.16f, -0.16f);
	glVertex2f(0.16f, -0.18f);
	glVertex2f(0.16f, -0.205f);

	glVertex2f(0.18f, 0.0f);
	glVertex2f(0.18f, -0.02f);
	glVertex2f(0.18f, -0.04f);
	glVertex2f(0.18f, -0.06f);
	glVertex2f(0.18f, -0.08f);
	glVertex2f(0.18f, -0.10f);
	glVertex2f(0.18f, -0.12f);
	glVertex2f(0.18f, -0.14f);
	glVertex2f(0.18f, -0.16f);
	glVertex2f(0.18f, -0.18f);
	glVertex2f(0.18f, -0.205f);

	glVertex2f(0.20f, 0.0f);
	glVertex2f(0.20f, -0.02f);
	glVertex2f(0.20f, -0.04f);
	glVertex2f(0.20f, -0.06f);
	glVertex2f(0.20f, -0.08f);
	glVertex2f(0.20f, -0.10f);
	glVertex2f(0.20f, -0.12f);
	glVertex2f(0.20f, -0.14f);
	glVertex2f(0.20f, -0.16f);
	glVertex2f(0.20f, -0.18f);
	glVertex2f(0.20f, -0.205f);

	glVertex2f(0.22f, 0.0f);
	glVertex2f(0.22f, -0.02f);
	glVertex2f(0.22f, -0.04f);
	glVertex2f(0.22f, -0.06f);
	glVertex2f(0.22f, -0.08f);
	glVertex2f(0.22f, -0.10f);
	glVertex2f(0.22f, -0.12f);
	glVertex2f(0.22f, -0.14f);
	glVertex2f(0.22f, -0.16f);
	glVertex2f(0.22f, -0.18f);
	glVertex2f(0.22f, -0.205f);

	glVertex2f(0.24f, 0.0f);
	glVertex2f(0.24f, -0.02f);
	glVertex2f(0.24f, -0.04f);
	glVertex2f(0.24f, -0.06f);
	glVertex2f(0.24f, -0.08f);
	glVertex2f(0.24f, -0.10f);
	glVertex2f(0.24f, -0.12f);
	glVertex2f(0.24f, -0.14f);
	glVertex2f(0.24f, -0.16f);
	glVertex2f(0.24f, -0.18f);
	glVertex2f(0.24f, -0.205f);

	glVertex2f(0.26f, -0.03f);
	glVertex2f(0.26f, -0.06f);
	glVertex2f(0.26f, -0.08f);
	glVertex2f(0.26f, -0.10f);
	glVertex2f(0.26f, -0.12f);
	glVertex2f(0.26f, -0.14f);
	glVertex2f(0.26f, -0.16f);
	glVertex2f(0.26f, -0.18f);
	glVertex2f(0.26f, -0.205f);

	glVertex2f(0.28f, -0.08f);
	glVertex2f(0.28f, -0.10f);
	glVertex2f(0.28f, -0.12f);
	glVertex2f(0.28f, -0.14f);
	glVertex2f(0.28f, -0.16f);
	glVertex2f(0.28f, -0.18f);

	glVertex2f(0.30f, -0.12f);
	glVertex2f(0.30f, -0.14f);
	glVertex2f(0.30f, -0.16f);
	glVertex2f(0.30f, -0.185f);


	//filling the left sholder
	glVertex2f(0.0f, 0.075f);
	glVertex2f(0.015f, 0.075f);
	glVertex2f(0.015f, 0.09f);
	glVertex2f(0.015f, 0.11f);
	glVertex2f(0.015f, 0.13f);
	glVertex2f(0.035f, 0.075f);
	glVertex2f(0.035f, 0.09f);
	glVertex2f(0.035f, 0.11f);
	glVertex2f(0.035f, 0.13f);
	glVertex2f(0.035f, 0.15f);
	glVertex2f(0.035f, 0.16f);

	//filing the neck
	glVertex2f(0.09f, 0.18f);
	glVertex2f(0.09f, 0.16f);
	glVertex2f(0.11f, 0.16f);
	glVertex2f(0.13f, 0.16f);
	glVertex2f(0.15f, 0.16f);
	glVertex2f(0.17f, 0.16f);
	glVertex2f(0.23f, 0.16f);
	glVertex2f(0.24f, 0.16f);
	//filling the right sholder
	glVertex2f(0.29f, 0.10f);
	glVertex2f(0.29f, 0.08f);

	glEnd();
	glFlush();

	//hands
	glPointSize(4.0f);
	glBegin(GL_POINTS);
	glColor3f(0.7f, 0.5f, 0.5f);
	glVertex2f(-0.02f, 0.03f);
	glVertex2f(-0.02f, 0.01f);
	glVertex2f(-0.04f, -0.01f);
	glVertex2f(-0.04f, -0.03f);
	glVertex2f(-0.06f, -0.05f);
	glVertex2f(-0.08f, -0.07f);
	glVertex2f(-0.08f, -0.09f);
	glVertex2f(-0.06f, -0.11f);
	glVertex2f(-0.06f, -0.13f);
	glVertex2f(-0.04f, -0.13f);
	glVertex2f(-0.02f, -0.13f);
	glVertex2f(0.0f, -0.13f);
	glVertex2f(0.0f, -0.11f);
	glVertex2f(0.02f, -0.09f);
	glVertex2f(0.02f, -0.03f);
	glVertex2f(0.02f, -0.05f);
	glVertex2f(0.02f, -0.07f);
	glVertex2f(0.04f, 0.03f);
	glVertex2f(0.04f, 0.01f);
	glVertex2f(0.04f, -0.01f);// end of the left hand
	glVertex2f(0.34f, -0.11f);
	glVertex2f(0.32f, -0.11f);
	glVertex2f(0.30f, -0.09f);
	glVertex2f(0.30f, -0.09f);
	glVertex2f(0.28f, -0.07f);
	glVertex2f(0.28f, -0.05f);
	glVertex2f(0.28f, -0.03f);
	glVertex2f(0.26f, -0.01f);
	glVertex2f(0.26f, 0.01f);
	glVertex2f(0.26f, 0.03f);
	glVertex2f(0.28f, 0.05f);
	glVertex2f(0.30f, 0.05f);
	glVertex2f(0.32f, 0.03f);
	glVertex2f(0.32f, 0.01f);
	glVertex2f(0.32f, -0.01f);
	glVertex2f(0.34f, -0.03f);
	glVertex2f(0.34f, -0.05f);
	glVertex2f(0.36f, -0.05f);
	glVertex2f(0.38f, -0.07f);
	glVertex2f(0.38f, -0.09f);
	glVertex2f(0.36f, -0.11f); //the end of the right hand

	//filling the hands
	glColor3f(0.85f, 0.67f, 0.6f);
	glVertex2f(0.28f, 0.03f);
	glVertex2f(0.28f, 0.01f);
	glVertex2f(0.28f, -0.01f);

	glVertex2f(0.3f, 0.03f);
	glVertex2f(0.3f, 0.01f);
	glVertex2f(0.3f, -0.01f);

	glVertex2f(0.3f, -0.03f);
	glVertex2f(0.3f, -0.05f);
	glVertex2f(0.3f, -0.07f);

	glVertex2f(0.32f, -0.03f);
	glVertex2f(0.32f, -0.05f);
	glVertex2f(0.32f, -0.07f);

	glVertex2f(0.32f, -0.09f);
	glVertex2f(0.34f, -0.07f);
	glVertex2f(0.34f, -0.09f);
	glVertex2f(0.36f, -0.07f);
	glVertex2f(0.36f, -0.09f);
	// end of filling the right hand



	glVertex2f(-0.04f, -0.11f);
	glVertex2f(-0.02f, -0.09f);
	glVertex2f(-0.02f, -0.11f);
	glColor3f(0.93f, 0.75f, 0.68f);
	glVertex2f(-0.06f, -0.09f);
	glVertex2f(-0.06f, -0.07f);
	glVertex2f(-0.04f, -0.09f);
	glVertex2f(-0.04f, -0.07f);
	glVertex2f(-0.04f, -0.05f);
	glVertex2f(-0.02f, -0.05f);
	glVertex2f(-0.02f, -0.07f);
	glVertex2f(-0.02f, -0.03f);
	glVertex2f(-0.02f, -0.01f);

	glVertex2f(0.0f, -0.09f);
	glVertex2f(0.0f, -0.05f);
	glVertex2f(0.0f, -0.07f);
	glVertex2f(0.0f, -0.03f);
	glVertex2f(0.0f, -0.01f);
	glVertex2f(0.0f, 0.01f);
	glVertex2f(0.0f, 0.03f);

	glVertex2f(0.02f, -0.01f);
	glVertex2f(0.02f, 0.01f);
	glVertex2f(0.02f, 0.03f);
	//end of filling left hand
	glEnd();
	glFlush();



	// legs
	glPointSize(5.0f);
	glBegin(GL_POINTS);
	glColor3f(0.7f, 0.5f, 0.5f);
	// the edges of the left leg
	glVertex2f(0.03f, -0.26f);
	glVertex2f(0.03f, -0.28f);
	glVertex2f(0.03f, -0.30f);
	glVertex2f(0.15f, -0.26f);
	glVertex2f(0.15f, -0.28f);
	glVertex2f(0.15f, -0.30f);
	// the edges of the right leg
	glVertex2f(0.15f, -0.26f);
	glVertex2f(0.15f, -0.28f);
	glVertex2f(0.15f, -0.30f);
	glVertex2f(0.25f, -0.26f);
	glVertex2f(0.25f, -0.28f);
	glVertex2f(0.25f, -0.30f);

	// filling the left leg
	glColor3f(0.85f, 0.67f, 0.6f);
	glVertex2f(0.05f, -0.26f);
	glVertex2f(0.05f, -0.28f);
	glVertex2f(0.05f, -0.30f);
	glVertex2f(0.07f, -0.26f);
	glVertex2f(0.07f, -0.28f);
	glVertex2f(0.07f, -0.30f);
	glVertex2f(0.09f, -0.26f);
	glVertex2f(0.09f, -0.28f);
	glVertex2f(0.09f, -0.30f);
	glVertex2f(0.11f, -0.26f);
	glVertex2f(0.11f, -0.28f);
	glVertex2f(0.11f, -0.30f);
	glVertex2f(0.13f, -0.26f);
	glVertex2f(0.13f, -0.28f);
	glVertex2f(0.13f, -0.30f);

	// filling the right leg

	glVertex2f(0.17f, -0.26f);
	glVertex2f(0.17f, -0.28f);
	glVertex2f(0.17f, -0.30f);
	glVertex2f(0.19f, -0.26f);
	glVertex2f(0.19f, -0.28f);
	glVertex2f(0.19f, -0.30f);
	glVertex2f(0.21f, -0.26f);
	glVertex2f(0.21f, -0.28f);
	glVertex2f(0.21f, -0.30f);
	glVertex2f(0.23f, -0.26f);
	glVertex2f(0.23f, -0.28f);
	glVertex2f(0.23f, -0.30f);


	//filling the shoes for the left pair
	glColor3f(0.7f, 0.2f, 0.2f);
	glVertex2f(0.05f, -0.32f);
	glVertex2f(0.07f, -0.32f);
	glVertex2f(0.09f, -0.32f);
	glVertex2f(0.11f, -0.32f);
	glVertex2f(0.13f, -0.32f);
	glVertex2f(0.15f, -0.32f);
	glVertex2f(0.17f, -0.32f);
	glVertex2f(0.05f, -0.34f);
	glVertex2f(0.07f, -0.34f);
	glVertex2f(0.09f, -0.34f);
	glVertex2f(0.11f, -0.34f);
	glVertex2f(0.13f, -0.34f);
	glVertex2f(0.15f, -0.34f);
	glVertex2f(0.17f, -0.34f);


	glColor3f(0.5f, 0.4f, 0.3f);
	//The edges of the left shoes
	glVertex2f(0.05f, -0.36f);
	glVertex2f(0.07f, -0.36f);
	glVertex2f(0.09f, -0.36f);
	glVertex2f(0.11f, -0.36f);
	glVertex2f(0.13f, -0.36f);
	glVertex2f(0.15f, -0.36f);
	glVertex2f(0.17f, -0.36f);
	glVertex2f(0.17f, -0.34f);
	glVertex2f(0.17f, -0.32f);
	//the edges of the right shoes
	glVertex2f(0.17f, -0.36f);
	glVertex2f(0.19f, -0.36f);
	glVertex2f(0.21f, -0.36f);
	glVertex2f(0.23f, -0.36f);
	glVertex2f(0.25f, -0.36f);
	glVertex2f(0.27f, -0.36f);
	glVertex2f(0.29f, -0.36f);
	glVertex2f(0.29f, -0.34f);
	glVertex2f(0.29f, -0.32f);

	//filling the shoes for the right pair
	glColor3f(0.7f, 0.2f, 0.2f);
	glVertex2f(0.195f, -0.32f);
	glVertex2f(0.21f, -0.32f);
	glVertex2f(0.23f, -0.32f);
	glVertex2f(0.25f, -0.32f);
	glVertex2f(0.27f, -0.32f);

	glVertex2f(0.195f, -0.34f);
	glVertex2f(0.21f, -0.34f);
	glVertex2f(0.23f, -0.34f);
	glVertex2f(0.25f, -0.34f);
	glVertex2f(0.27f, -0.34f);
	glEnd();
	glFlush();

	glColor3f(0.7, 0.5, 0.3); // Set color to light brown (RGB values)
	glBegin(GL_QUADS); // Begin drawing a quadrilateral
	glVertex2f(-0.06, -0.31); // Bottom-left vertex
	glVertex2f(0.04, -0.31);  // Bottom-right vertex
	glVertex2f(0.09, -0.2);  // Top-left vertex
	glVertex2f(-0.11, -0.2);   // Top-right vertex (shorter base)

	glEnd(); // End drawing the quadrilateral
	glFlush();


	glColor3f(0.7, 0.5, 0.3); // Set color to light brown (RGB values)
	glLineWidth(5);
	glBegin(GL_LINES); // Begin drawing a quadrilateral
	glVertex2f(-0.09, -0.2);
	glVertex2f(-0.09, -0.1);
	glVertex2f(-0.09, -0.1);
	glVertex2f(0.07, -0.1);
	glVertex2f(0.07, -0.1);
	glVertex2f(0.07, -0.2);
	glEnd();
	glFlush();


	glEnd();
	glFlush();
}
void grandma()
{
	// 0.8 f, 0.5f, 0.2f  
	glPointSize(5.0f);
	glBegin(GL_POINTS);
	glColor3f(0.9f, 0.7f, 0.5f);
	glVertex2f(0.0f, 0.0f);
	glVertex2f(0.02f, 0.0f);
	glVertex2f(0.04f, 0.0f);
	glVertex2f(0.0f, -0.02f);
	glVertex2f(0.02f, -0.02f);
	glVertex2f(0.04f, -0.02f);
	glVertex2f(0.0f, -0.04f);
	glVertex2f(0.0f, 0.02f);
	glVertex2f(0.02f, 0.02f);
	glVertex2f(0.04f, 0.02f);
	glVertex2f(0.0f, 0.04f);
	glVertex2f(0.02f, 0.04f);
	glVertex2f(0.04f, 0.04f);
	glVertex2f(0.04f, 0.04f);
	glVertex2f(0.06f, 0.04f);
	glVertex2f(0.0f, 0.06f);
	glVertex2f(0.02f, 0.06f);
	glVertex2f(0.04f, 0.06f);
	glVertex2f(0.06f, 0.06f);
	glVertex2f(0.08f, 0.06f);
	glVertex2f(0.0f, 0.08f);
	glVertex2f(0.02f, 0.08f);
	glVertex2f(0.04f, 0.08f);
	glVertex2f(0.06f, 0.08f);
	glVertex2f(0.08f, 0.08f);
	glVertex2f(0.0f, 0.10f);
	glVertex2f(0.02f, 0.10f);
	glVertex2f(0.04f, 0.10f);
	glVertex2f(0.06f, 0.10f);
	glVertex2f(0.08f, 0.10f);
	glVertex2f(0.10f, 0.10f);
	glVertex2f(0.12f, 0.10f);
	glVertex2f(0.0f, 0.12f);
	glVertex2f(0.02f, 0.12f);
	glVertex2f(0.04f, 0.12f);
	glVertex2f(0.06f, 0.12f);
	glVertex2f(0.13f, 0.11f);
	glVertex2f(0.0f, 0.13f);
	glVertex2f(0.02f, 0.13f);
	glVertex2f(0.04f, 0.13f);
	glVertex2f(0.06f, 0.13f);
	glVertex2f(0.08f, 0.13f);
	glVertex2f(0.13f, 0.13f);
	glVertex2f(0.0f, 0.15f);
	glVertex2f(0.02f, 0.15f);
	glVertex2f(0.04f, 0.15f);
	glVertex2f(0.06f, 0.15f);
	glVertex2f(0.08f, 0.15f);
	glVertex2f(0.11f, 0.15f);
	glVertex2f(0.11f, 0.15f);
	glVertex2f(0.0f, -0.04f);
	glVertex2f(-0.02f, -0.04f);
	glVertex2f(-0.04f, -0.04f);
	glVertex2f(-0.06f, -0.04f);
	glVertex2f(-0.08f, -0.04f);
	glVertex2f(-0.10f, -0.04f);
	glVertex2f(-0.12f, -0.04f);
	glVertex2f(-0.14f, -0.04f);
	glVertex2f(-0.22f, -0.03f);
	glVertex2f(-0.20f, -0.03f);
	glVertex2f(-0.16f, -0.03f);
	glVertex2f(-0.14f, -0.03f);
	glVertex2f(-0.12f, -0.03f);
	glVertex2f(-0.10f, -0.03f);
	glVertex2f(-0.08f, -0.03f);
	glVertex2f(-0.06f, -0.03f);
	glVertex2f(-0.04f, -0.03f);
	glVertex2f(-0.02f, -0.03f);
	glVertex2f(-0.22f, 0.02f);
	glVertex2f(-0.16f, -0.04f);
	glVertex2f(-0.18f, -0.04f);
	glVertex2f(-0.20f, -0.04f);
	glVertex2f(-0.22f, -0.02f);
	glVertex2f(-0.24f, -0.02f);
	glVertex2f(-0.24f, 0.0f);
	glVertex2f(-0.26f, 0.0f);
	glVertex2f(-0.26f, 0.02f);
	glVertex2f(-0.26f, 0.04f);
	glVertex2f(-0.26f, 0.06f);
	glVertex2f(-0.26f, 0.08f);
	glVertex2f(-0.26f, 0.10f);
	glVertex2f(-0.26f, 0.12f);
	glVertex2f(-0.10f, 0.28f);
	glVertex2f(-0.12f, 0.28f);
	glVertex2f(-0.14f, 0.28f);
	glVertex2f(-0.26f, 0.19f);
	glVertex2f(-0.28f, 0.19f);
	glVertex2f(-0.24f, 0.20f);
	glVertex2f(-0.26f, 0.20f);
	glVertex2f(-0.24f, 0.20f);
	glVertex2f(-0.24f, 0.26f);
	glVertex2f(-0.24f, 0.28f);
	glVertex2f(-0.22f, 0.24f);
	glVertex2f(-0.22f, 0.26f);
	glVertex2f(-0.22f, 0.28f);
	glVertex2f(-0.22f, 0.30f);
	glVertex2f(-0.20f, 0.30f);
	glVertex2f(-0.18f, 0.30f);
	glVertex2f(-0.16f, 0.30f);
	glVertex2f(-0.14f, 0.30f);
	glVertex2f(-0.12f, 0.30f);
	glVertex2f(-0.10f, 0.30f);
	glVertex2f(-0.12f, 0.28f);
	glVertex2f(-0.10f, 0.28f);
	glVertex2f(-0.12f, 0.28f);
	glVertex2f(-0.08f, 0.26f);
	glVertex2f(-0.06f, 0.26f);
	glVertex2f(-0.06f, 0.24f);
	glVertex2f(-0.04f, 0.24f);
	glVertex2f(-0.10f, 0.28f);
	glVertex2f(-0.12f, 0.28f);
	glVertex2f(-0.14f, 0.28f);
	glVertex2f(-0.16f, 0.28f);
	glVertex2f(-0.18f, 0.28f);
	glVertex2f(-0.20f, 0.28f);
	glVertex2f(-0.26f, 0.18f);
	glVertex2f(-0.26f, 0.16f);
	glVertex2f(-0.26f, 0.14f);
	glEnd();

	glPointSize(5.0f);
	glBegin(GL_POINTS);
	glColor3f(0.9f, 0.6f, 0.5f);
	glVertex2f(0.10f, 0.08f);
	glVertex2f(0.06f, 0.08f);
	glVertex2f(0.09f, 0.11f);
	glVertex2f(0.11f, 0.11f);
	glVertex2f(0.11f, 0.13f);
	glVertex2f(0.18f, -0.20f);
	glEnd();

	glPointSize(11.0f);
	glBegin(GL_POINTS);
	glColor3f(0.9f, 0.8f, 0.6f);
	glVertex2f(-0.22f, 0.02f);
	glVertex2f(-0.22f, 0.04f);
	glVertex2f(-0.22f, 0.08f);
	glVertex2f(-0.18f, 0.08f);
	glVertex2f(-0.18f, 0.06f);
	glVertex2f(-0.18f, 0.04f);
	glVertex2f(-0.16f, 0.04f);
	glVertex2f(-0.16f, 0.06f);
	glVertex2f(-0.16f, 0.08f);
	glVertex2f(-0.16f, 0.10f);
	glVertex2f(-0.18f, 0.10f);
	glVertex2f(-0.18f, 0.12f);
	glVertex2f(-0.20f, 0.14f);
	glVertex2f(-0.22f, 0.16f);
	glVertex2f(-0.20f, 0.16f);
	glVertex2f(-0.16f, 0.15f);
	glVertex2f(-0.16f, 0.16f);
	glVertex2f(-0.12f, 0.16f);
	glVertex2f(-0.12f, 0.14f);
	glVertex2f(-0.12f, 0.12f);
	glVertex2f(-0.12f, 0.10f);
	glVertex2f(-0.12f, 0.08f);
	glVertex2f(-0.12f, 0.06f);
	glVertex2f(-0.12f, 0.04f);
	glVertex2f(-0.10f, 0.01f);
	glVertex2f(-0.05f, 0.01f);
	glVertex2f(-0.04f, 0.01f);
	glVertex2f(-0.05f, 0.06f);
	glVertex2f(-0.04f, 0.06f);
	glVertex2f(-0.07f, 0.06f);
	glVertex2f(-0.04f, 0.1f);
	glVertex2f(-0.07f, 0.1f);
	glVertex2f(-0.22f, 0.16f);
	glVertex2f(-0.22f, 0.14f);
	glVertex2f(-0.14f, 0.0f);
	glVertex2f(-0.18f, 0.0f);
	glVertex2f(-0.04f, 0.15f);
	glVertex2f(-0.08f, 0.15f);
	glEnd();

	glPointSize(5.0f);
	glBegin(GL_POINTS);
	glColor3f(0.9f, 0.7f, 0.5f);
	glVertex2f(-0.04f, 0.12f);
	glVertex2f(-0.02f, 0.12f);
	glVertex2f(-0.22f, 0.12f);
	glVertex2f(-0.24f, 0.12f);
	glEnd();

	glPointSize(3.0f);
	glBegin(GL_POINTS);
	glColor3f(0.9f, 0.8f, 0.6f);
	glVertex2f(-0.02f, 0.18f);
	glVertex2f(-0.04f, 0.18f);
	glVertex2f(-0.06f, 0.18f);
	glVertex2f(-0.09f, 0.18f);
	glVertex2f(-0.08f, 0.18f);
	glEnd();

	glPointSize(5.0f);
	glBegin(GL_POINTS);
	glColor3f(0.9f, 0.8f, 0.6f);
	glVertex2f(-0.04f, 0.22f);
	glVertex2f(-0.06f, 0.22f);
	glVertex2f(-0.08f, 0.22f);
	glVertex2f(-0.10f, 0.22f);
	glVertex2f(-0.12f, 0.22f);
	glVertex2f(-0.14f, 0.22f);
	glVertex2f(-0.16f, 0.22f);
	glVertex2f(-0.18f, 0.22f);
	glVertex2f(-0.20f, 0.22f);
	glVertex2f(-0.22f, 0.22f);
	glVertex2f(-0.24f, 0.22f);
	glVertex2f(-0.26f, 0.22f);
	glVertex2f(-0.02f, 0.22f);
	glVertex2f(-0.02f, 0.20f);
	glVertex2f(0.0f, 0.20f);
	glVertex2f(0.0f, 0.16f);
	glVertex2f(0.0f, 0.18f);
	glVertex2f(-0.02f, 0.18f);
	glVertex2f(-0.16f, 0.26f);
	glVertex2f(-0.18f, 0.26f);
	glVertex2f(-0.20f, 0.26f);
	glVertex2f(-0.14f, 0.26f);
	glVertex2f(-0.12f, 0.26f);
	glVertex2f(-0.10f, 0.26f);
	glVertex2f(-0.07f, 0.20f);
	glVertex2f(-0.06f, 0.20f);
	glVertex2f(-0.04f, 0.20f);
	glVertex2f(0.0f, 0.20f);
	glVertex2f(-0.10f, 0.20f);
	glVertex2f(-0.12f, 0.20f);
	glVertex2f(-0.14f, 0.20f);
	glVertex2f(-0.16f, 0.20f);
	glVertex2f(-0.18f, 0.20f);
	glVertex2f(-0.20f, 0.20f);
	glVertex2f(-0.22f, 0.20f);
	glVertex2f(-0.22f, 0.19f);
	glEnd();

	glPointSize(4.0f); //lips
	glBegin(GL_POINTS);
	glColor3f(0.9f, 0.6f, 0.5f);
	glVertex2f(-0.14f, 0.03f);
	glVertex2f(-0.17f, 0.03f);
	glVertex2f(-0.15f, 0.03f);
	glVertex2f(-0.19f, 0.03f);
	glVertex2f(-0.12f, 0.03f);
	glVertex2f(-0.11f, 0.03f);
	glEnd();

	glPointSize(5.0);
	glBegin(GL_POINTS);
	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex2f(-0.02f, 0.14f);
	glVertex2f(-0.2f, 0.14f);
	glColor3f(0.0f, 0.0f, 0.0f);
	glVertex2f(-0.06f, 0.14f);
	glVertex2f(-0.24f, 0.14f);
	glEnd();

	glPointSize(6.0);
	glBegin(GL_POINTS);
	glColor3f(0.0f, 0.0f, 0.0f);
	glVertex2f(-0.06f, 0.14f);
	glVertex2f(-0.24f, 0.14f);
	glEnd();

	glPointSize(2.0f);
	glBegin(GL_POINTS);
	glColor3f(0.9f, 0.7f, 0.5f);
	glVertex2f(-0.20f, 0.24f);
	glVertex2f(-0.19f, 0.24f);
	glVertex2f(-0.18f, 0.24f);
	glVertex2f(-0.17f, 0.24f);
	glVertex2f(-0.16f, 0.24f);
	glVertex2f(-0.15f, 0.24f);
	glVertex2f(-0.14f, 0.24f);
	glVertex2f(-0.13f, 0.24f);
	glVertex2f(-0.12f, 0.24f);
	glVertex2f(-0.11f, 0.24f);
	glVertex2f(-0.10f, 0.24f);
	glVertex2f(-0.09f, 0.24f);
	glVertex2f(-0.08f, 0.24f);
	glEnd();

	glPointSize(4.0f);
	glBegin(GL_POINTS);
	glColor3f(0.6f, 0.6f, 0.6f);
	glVertex2f(0.0f, 0.18f);
	glVertex2f(-0.02f, 0.18f);
	glVertex2f(-0.04f, 0.18f);
	glVertex2f(-0.06f, 0.18f);
	glVertex2f(-0.08f, 0.18f);
	glVertex2f(-0.18f, 0.18f);
	glVertex2f(-0.2f, 0.18f);
	glVertex2f(-0.22f, 0.18f);
	glVertex2f(-0.24f, 0.18f);
	glVertex2f(-0.26f, 0.18f);
	glEnd();

	////////////////////////////////الشعر///////////////////////////////////
	glPointSize(5.0f);
	glBegin(GL_POINTS);
	glColor3f(0.5f, 0.5f, 0.5f);
	glVertex2f(-0.32f, 0.14f);
	glVertex2f(-0.32f, 0.12f);
	glVertex2f(-0.34f, 0.12f);
	glVertex2f(-0.36f, 0.12f);
	glVertex2f(-0.36f, 0.14f);
	glVertex2f(-0.38f, 0.16f);
	glVertex2f(-0.38f, 0.18f);
	glVertex2f(-0.36f, 0.18f);
	glVertex2f(-0.36f, 0.20f);
	glVertex2f(-0.34f, 0.20f);
	glVertex2f(-0.36f, 0.22f);
	glVertex2f(-0.36f, 0.24f);
	glVertex2f(-0.34f, 0.26f);
	glVertex2f(-0.32f, 0.28f);
	glVertex2f(-0.30f, 0.30f);
	glVertex2f(-0.30f, 0.32f);
	glVertex2f(-0.26f, 0.32f);
	glVertex2f(-0.24f, 0.32f);
	glVertex2f(-0.22f, 0.32f);
	glVertex2f(-0.20f, 0.32f);
	glVertex2f(-0.18f, 0.32f);
	glVertex2f(-0.16f, 0.32f);
	glVertex2f(-0.14f, 0.32f);
	glVertex2f(-0.12f, 0.32f);
	glVertex2f(-0.10f, 0.32f);
	glVertex2f(-0.08f, 0.32f);
	glVertex2f(-0.08f, 0.28f);
	glVertex2f(-0.06f, 0.28f);
	glVertex2f(-0.04f, 0.28f);
	glVertex2f(-0.04f, 0.26f);
	glVertex2f(-0.02f, 0.26f);
	glVertex2f(-0.02f, 0.24f);
	glVertex2f(0.0f, 0.24f);
	glVertex2f(0.0f, 0.22f);
	glVertex2f(0.02f, 0.22f);
	glVertex2f(0.02f, 0.20f);
	glVertex2f(0.02f, 0.20f);
	glVertex2f(0.02f, 0.18f);
	glVertex2f(0.04f, 0.17f);
	glVertex2f(0.06f, 0.17f);
	glVertex2f(0.08f, 0.17f);
	glVertex2f(0.10f, 0.17f);
	glVertex2f(0.12f, 0.17f);
	glVertex2f(0.13f, 0.14f);
	glVertex2f(0.15f, 0.14f);
	glVertex2f(0.15f, 0.12f);
	glVertex2f(0.15f, 0.10f);
	glVertex2f(0.15f, 0.08f);
	glVertex2f(0.17f, 0.06f);
	glVertex2f(0.19f, 0.04f);
	glVertex2f(0.21f, 0.02f);
	glVertex2f(0.23f, 0.02f);
	glVertex2f(0.25f, 0.02f);
	glVertex2f(0.27f, 0.04f);
	glVertex2f(0.29f, 0.06f);
	glVertex2f(0.31f, 0.08f);
	glVertex2f(0.31f, 0.10f);
	glVertex2f(0.27f, 0.04f);
	glVertex2f(0.29f, 0.06f);
	glVertex2f(0.31f, 0.08f);
	glVertex2f(0.31f, 0.10f);
	glVertex2f(0.31f, 0.12f);
	glVertex2f(0.31f, 0.14f);
	glVertex2f(0.29f, 0.16f);
	glVertex2f(0.26f, 0.18f);
	glVertex2f(0.24f, 0.18f);
	glVertex2f(0.22f, 0.18f);
	glVertex2f(0.20f, 0.16f);
	glVertex2f(0.17f, 0.16f);
	glVertex2f(0.20f, 0.20f);
	glVertex2f(0.18f, 0.22f);
	glVertex2f(0.18f, 0.24f);
	glVertex2f(0.16f, 0.26f);
	glVertex2f(0.14f, 0.28f);
	glVertex2f(0.14f, 0.30f);
	glVertex2f(0.12f, 0.32f);
	glVertex2f(0.10f, 0.34f);
	glVertex2f(0.10f, 0.36f);
	glVertex2f(0.08f, 0.38f);
	glVertex2f(0.10f, 0.34f);
	glVertex2f(0.10f, 0.36f);
	glVertex2f(0.08f, 0.38f);
	glVertex2f(0.06f, 0.38);
	glVertex2f(0.04f, 0.40f);
	glVertex2f(0.02f, 0.42f);
	glVertex2f(0.0f, 0.44f);
	glVertex2f(0.0f, 0.42f);
	glVertex2f(-0.02f, 0.46f);
	glVertex2f(-0.04f, 0.46f);
	glVertex2f(-0.06f, 0.46f);
	glVertex2f(-0.08f, 0.46f);
	glVertex2f(-0.08f, 0.46f);
	glVertex2f(-0.08f, 0.46f);
	glVertex2f(-0.10f, 0.46f);
	glVertex2f(-0.12f, 0.46f);
	glVertex2f(-0.16f, 0.46f);
	glVertex2f(-0.18f, 0.44f);
	glVertex2f(-0.18f, 0.46f);
	glVertex2f(-0.20f, 0.42f);
	glVertex2f(-0.22f, 0.40f);
	glVertex2f(-0.24f, 0.40f);
	glVertex2f(-0.24f, 0.38f);
	glVertex2f(-0.26f, 0.38f);
	glVertex2f(-0.28f, 0.36f);
	glVertex2f(-0.30f, 0.34f);
	glVertex2f(-0.30f, 0.18f);
	glVertex2f(-0.32f, 0.18f);
	glVertex2f(-0.30f, 0.20f);
	glVertex2f(-0.28f, 0.21f);
	glVertex2f(-0.28f, 0.22f);
	glVertex2f(-0.28f, 0.24f);
	glVertex2f(-0.26f, 0.24f);
	glVertex2f(-0.24f, 0.24f);
	glVertex2f(-0.26f, 0.26f);
	glVertex2f(-0.26f, 0.28f);
	glVertex2f(-0.26f, 0.30f);
	glVertex2f(-0.24f, 0.30f);
	glEnd();

	glPointSize(5.0f);
	glBegin(GL_POINTS);
	glColor3f(0.8f, 0.8f, 0.8f);
	glVertex2f(-0.30f, 0.28f);
	glVertex2f(-0.30f, 0.26f);
	glVertex2f(-0.30f, 0.24f);
	glVertex2f(-0.32f, 0.24f);
	glVertex2f(-0.32f, 0.26f);
	glVertex2f(-0.32f, 0.16f);
	glVertex2f(-0.28f, 0.32f);
	glVertex2f(-0.28f, 0.34f);
	glVertex2f(-0.34f, 0.24f);
	glVertex2f(-0.34f, 0.20f);
	glEnd();

	glPointSize(8.0f);
	glBegin(GL_POINTS);
	glColor3f(0.8f, 0.8f, 0.8f);
	glVertex2f(-0.25f, 0.34f);
	glVertex2f(-0.20f, 0.36f);
	glVertex2f(-0.20f, 0.38f);
	glVertex2f(-0.16f, 0.40f);
	glVertex2f(-0.20f, 0.36f);
	glVertex2f(-0.16f, 0.38f);
	glVertex2f(-0.20f, 0.35f);
	glVertex2f(-0.16f, 0.36f);
	glVertex2f(-0.14f, 0.42f);
	glVertex2f(-0.12f, 0.42f);
	glVertex2f(-0.10f, 0.42f);
	glVertex2f(-0.08f, 0.42f);
	glVertex2f(-0.06f, 0.42f);
	glVertex2f(-0.04f, 0.42f);
	glVertex2f(-0.12f, 0.40f);
	glVertex2f(-0.10f, 0.40f);
	glVertex2f(-0.08f, 0.40f);
	glVertex2f(-0.06f, 0.40f);
	glVertex2f(-0.04f, 0.40f);
	glVertex2f(-0.12f, 0.35f);
	glVertex2f(-0.10f, 0.35f);
	glVertex2f(-0.08f, 0.35f);
	glVertex2f(-0.04f, 0.35f);
	glVertex2f(-0.07f, 0.31f);
	glVertex2f(-0.06f, 0.31f);
	glVertex2f(-0.01f, 0.31f);
	glVertex2f(-0.01f, 0.35f);
	glVertex2f(0.0f, 0.39f);
	glVertex2f(0.02f, 0.37f);
	glVertex2f(0.02f, 0.32f);
	glVertex2f(0.00f, 0.30f);
	glVertex2f(0.02f, 0.27f);
	glVertex2f(0.02f, 0.26f);
	glVertex2f(0.07f, 0.31f);
	glVertex2f(0.06f, 0.35f);
	glVertex2f(0.07f, 0.26f);
	glVertex2f(0.12f, 0.26f);
	glVertex2f(0.12f, 0.31f);
	glVertex2f(0.10f, 0.28f);
	glVertex2f(0.06f, 0.21f);
	glEnd();

	glPointSize(11.0f);
	glBegin(GL_POINTS);
	glColor3f(0.8f, 0.8f, 0.8f);
	glVertex2f(0.10f, 0.22f);
	glVertex2f(0.15f, 0.21f);
	glVertex2f(0.15f, 0.18f);
	glVertex2f(0.20f, 0.14f);
	glVertex2f(0.20f, 0.10f);
	glVertex2f(0.22f, 0.06f);
	glVertex2f(0.22f, 0.13f);
	glVertex2f(0.26f, 0.13f);
	glVertex2f(0.26f, 0.09f);
	glEnd();

	// 0.5  / 0.6    / 0.6  حتاف يدامر
	glPointSize(5.0f);
	glBegin(GL_POINTS);
	glColor3f(0.8f, 0.8f, 0.8f);
	glVertex2f(-0.28f, 0.30f);
	glVertex2f(-0.28f, 0.28f);
	glVertex2f(-0.30f, 0.24f);
	glVertex2f(-0.30f, 0.22f);
	glVertex2f(-0.32f, 0.22f);
	glVertex2f(-0.34f, 0.22f);
	glVertex2f(-0.32f, 0.20f);
	glVertex2f(-0.35f, 0.16f);
	glVertex2f(-0.34f, 0.18f);
	glVertex2f(-0.34f, 0.16f);
	glVertex2f(-0.34f, 0.14f);
	glEnd();

	//////////الجسما//////////////////
	glPointSize(5.0f);
	glBegin(GL_POINTS);
	glColor3f(0.3f, 0.4f, 0.3f);
	glVertex2f(-0.20f, -0.06f);
	glVertex2f(-0.18f, -0.06f);
	glVertex2f(-0.16f, -0.06f);
	glVertex2f(-0.14f, -0.06f);
	glVertex2f(-0.12f, -0.06f);
	glVertex2f(-0.10f, -0.06f);
	glVertex2f(-0.08f, -0.06f);
	glVertex2f(-0.06f, -0.06f);
	glVertex2f(-0.04f, -0.06f);
	glColor3f(0.3f, 0.4f, 0.3f);
	glVertex2f(-0.02f, -0.06f);
	glVertex2f(0.0f, -0.06f);
	glVertex2f(0.02f, -0.04f);
	glVertex2f(0.04f, -0.04f);
	glVertex2f(0.06f, -0.04f);
	glVertex2f(0.06f, -0.06f);
	glVertex2f(0.06f, -0.08f);
	glVertex2f(0.06f, -0.10f);
	glVertex2f(0.04f, -0.12f);
	glVertex2f(0.02f, -0.14f);
	glVertex2f(0.0f, -0.14f);
	glVertex2f(-0.02f, -0.16f);
	glVertex2f(0.0f, -0.18f);
	glVertex2f(0.02f, -0.20f);
	glVertex2f(0.02f, -0.22f);
	glVertex2f(0.02f, -0.24f);
	glEnd();

	glPointSize(5.0f);
	glBegin(GL_POINTS);
	glColor3f(0.3f, 0.4f, 0.3f);
	glVertex2f(0.0f, -0.24f);
	glVertex2f(-0.02f, -0.24f);
	glVertex2f(-0.04f, -0.24f);
	glVertex2f(-0.06f, -0.24f);
	glVertex2f(-0.08f, -0.24f);
	glVertex2f(-0.08f, -0.22f);
	glVertex2f(-0.08f, -0.20f);
	glVertex2f(-0.06f, -0.18f);
	glVertex2f(-0.04f, -0.16f);
	glVertex2f(-0.08f, -0.18f);
	glVertex2f(-0.06f, -0.14f);
	glVertex2f(-0.08f, -0.14f);
	glVertex2f(-0.10f, -0.12f);
	glVertex2f(-0.12f, -0.12f);
	glVertex2f(-0.14f, -0.10f);
	glVertex2f(-0.16f, -0.10f);
	glVertex2f(-0.18f, -0.08f);
	glVertex2f(-0.20f, -0.08f);
	glEnd();

	glPointSize(5.0f);
	glBegin(GL_POINTS);
	glColor3f(0.3f, 0.3f, 0.1f);
	glVertex2f(-0.16f, -0.08f);
	glVertex2f(-0.18f, -0.08f);
	glVertex2f(-0.20f, -0.08f);
	glVertex2f(-0.14f, -0.10f);
	glVertex2f(-0.12f, -0.10f);
	glVertex2f(-0.08f, -0.12f);
	glVertex2f(0.04f, -0.06f);
	glVertex2f(0.04f, -0.08f);
	glVertex2f(0.02f, -0.06f);
	glEnd();

	glPointSize(5.0f);
	glBegin(GL_POINTS);
	glColor3f(0.3f, 0.3f, 0.1f);
	glVertex2f(0.04f, -0.08f);
	glVertex2f(0.02f, -0.06f);
	glEnd();

	glPointSize(7.0f);
	glBegin(GL_POINTS);
	glColor3f(0.3f, 0.5f, 0.3f);
	glVertex2f(0.01f, -0.11f);
	glVertex2f(-0.06f, -0.08f);
	glVertex2f(-0.09f, -0.08f);
	glEnd();

	glPointSize(5.0f);
	glBegin(GL_POINTS);
	glColor3f(0.3f, 0.5f, 0.3f);
	glVertex2f(0.04f, -0.10f);
	glVertex2f(0.02f, -0.08f);
	glVertex2f(0.0f, -0.08f);
	glVertex2f(-0.02f, -0.08f);
	glVertex2f(-0.04f, -0.08f);
	glEnd();


	glPointSize(3.0f);
	glBegin(GL_POINTS);
	glColor3f(0.3f, 0.5f, 0.3f);
	glVertex2f(-0.12f, -0.08f);
	glVertex2f(-0.14f, -0.08f);
	glVertex2f(-0.08f, -0.10f);
	glVertex2f(-0.10f, -0.10f);
	glVertex2f(-0.06f, -0.10f);
	glEnd();

	glPointSize(8.0f);
	glBegin(GL_POINTS);
	glColor3f(0.3f, 0.5f, 0.3f);
	glVertex2f(-0.02f, -0.1f);
	glVertex2f(-0.05f, -0.11f);
	glVertex2f(-0.02f, -0.11f);
	glEnd();

	glPointSize(6.0f);
	glBegin(GL_POINTS);
	glColor3f(0.3f, 0.5f, 0.3f);
	glVertex2f(-0.03f, -0.14f);
	glVertex2f(-0.03f, -0.19f);
	glEnd();

	glPointSize(8.0f);
	glBegin(GL_POINTS);
	glColor3f(0.3f, 0.5f, 0.3f);
	glVertex2f(-0.03f, -0.21f);
	glVertex2f(-0.01f, -0.21f);
	glVertex2f(-0.06f, -0.21f);
	glVertex2f(-0.19f, -0.11f);
	glVertex2f(-0.19f, -0.11f);
	glEnd();


	glPointSize(8.0f);
	glBegin(GL_POINTS);
	glColor3f(0.0f, 0.3f, 0.5f);
	glVertex2f(-0.19f, -0.15f);
	glVertex2f(-0.15f, -0.19f);
	glVertex2f(-0.15f, -0.23f);
	glVertex2f(-0.11f, -0.26f);
	glVertex2f(-0.11f, -0.30f);
	glVertex2f(-0.11f, -0.30f);
	glVertex2f(-0.08f, -0.34f);
	glVertex2f(-0.08f, -0.34f);
	glVertex2f(0.0f, -0.34f);
	glVertex2f(0.02f, -0.34f);
	glVertex2f(0.04f, -0.34f);
	glVertex2f(0.06f, -0.34f);
	glVertex2f(0.09f, -0.30f);
	glVertex2f(0.12f, -0.30f);
	glVertex2f(0.15f, -0.26f);
	glVertex2f(0.19f, -0.26f);
	glVertex2f(0.19f, -0.22f);
	glVertex2f(0.19f, -0.18f);
	glVertex2f(0.15f, -0.14f);
	glVertex2f(0.15f, -0.10f);
	glVertex2f(0.11f, -0.10f);
	glVertex2f(0.09f, -0.10f);
	glVertex2f(0.11f, -0.10f);
	glVertex2f(0.09f, -0.06f);
	glEnd();

	glPointSize(8.0f);
	glBegin(GL_POINTS);
	glColor3f(0.2f, 0.4f, 0.6f);
	glVertex2f(0.07f, -0.11f);
	glEnd();

	glPointSize(7.0f);
	glBegin(GL_POINTS);
	glColor3f(0.2f, 0.4f, 0.6f);
	glVertex2f(0.07f, -0.14f);
	glEnd();

	glPointSize(7.0f);
	glBegin(GL_POINTS);
	glColor3f(0.2f, 0.4f, 0.6f);
	glVertex2f(0.09f, -0.14f);
	glEnd();

	glPointSize(7.0f);
	glBegin(GL_POINTS);
	glColor3f(0.2f, 0.4f, 0.6f);
	glVertex2f(0.04f, -0.14f);
	glEnd();

	glPointSize(7.0f);
	glBegin(GL_POINTS);
	glColor3f(0.2f, 0.4f, 0.6f);
	glVertex2f(0.12f, -0.14f);
	glEnd();

	glPointSize(8.0f);
	glBegin(GL_POINTS);
	glColor3f(0.2f, 0.4f, 0.6f);
	glVertex2f(0.12f, -0.17f);
	glEnd();

	glPointSize(8.0f);
	glBegin(GL_POINTS);
	glColor3f(0.2f, 0.4f, 0.6f);
	glVertex2f(0.15f, -0.17f);
	glEnd();

	glPointSize(8.0f);
	glBegin(GL_POINTS);
	glColor3f(0.2f, 0.4f, 0.6f);
	glVertex2f(0.12f, -0.17f);
	glEnd();

	glPointSize(8.0f);
	glBegin(GL_POINTS);
	glColor3f(0.2f, 0.4f, 0.6f);
	glVertex2f(0.09f, -0.17f);
	glEnd();

	glPointSize(8.0f);
	glBegin(GL_POINTS);
	glColor3f(0.2f, 0.4f, 0.6f);
	glVertex2f(0.06f, -0.17f);
	glEnd();

	glPointSize(8.0f);
	glBegin(GL_POINTS);
	glColor3f(0.2f, 0.4f, 0.6f);
	glVertex2f(0.03f, -0.17f);
	glEnd();

	glPointSize(3.0f);
	glBegin(GL_POINTS);
	glColor3f(0.2f, 0.4f, 0.6f);
	glVertex2f(0.0f, -0.16f);
	glEnd();

	glPointSize(3.0f);
	glBegin(GL_POINTS);
	glColor3f(0.2f, 0.4f, 0.6f);
	glVertex2f(-0.06f, -0.16f);
	glEnd();

	glPointSize(3.0f);
	glBegin(GL_POINTS);
	glColor3f(0.2f, 0.4f, 0.6f);
	glVertex2f(-0.07f, -0.16f);
	glEnd();

	glPointSize(3.0f);
	glBegin(GL_POINTS);
	glColor3f(0.2f, 0.4f, 0.6f);
	glVertex2f(-0.08f, -0.16f);
	glEnd();

	glPointSize(3.0f);
	glBegin(GL_POINTS);
	glColor3f(0.2f, 0.4f, 0.6f);
	glVertex2f(-0.09f, -0.14f);
	glEnd();

	glPointSize(3.0f);
	glBegin(GL_POINTS);
	glColor3f(0.2f, 0.4f, 0.6f);
	glVertex2f(-0.11f, -0.14f);
	glEnd();

	glPointSize(3.0f);
	glBegin(GL_POINTS);
	glColor3f(0.2f, 0.4f, 0.6f);
	glVertex2f(-0.13f, -0.14f);
	glEnd();

	glPointSize(13.0f);
	glBegin(GL_POINTS);
	glColor3f(0.2f, 0.4f, 0.6f);
	glVertex2f(-0.14f, -0.14f);
	glEnd();

	glPointSize(8.0f);
	glBegin(GL_POINTS);
	glColor3f(0.2f, 0.4f, 0.6f);
	glVertex2f(-0.11f, -0.17f);
	glEnd();

	glPointSize(8.0f);
	glBegin(GL_POINTS);
	glColor3f(0.2f, 0.4f, 0.6f);
	glVertex2f(-0.07f, -0.30f);
	glEnd();

	glPointSize(8.0f);
	glBegin(GL_POINTS);
	glColor3f(0.2f, 0.4f, 0.6f);
	glVertex2f(0.04f, -0.30f);
	glEnd();

	glPointSize(8.0f);
	glBegin(GL_POINTS);
	glColor3f(0.2f, 0.4f, 0.6f);
	glVertex2f(0.06f, -0.30f);
	glEnd();

	glPointSize(8.0f);
	glBegin(GL_POINTS);
	glColor3f(0.2f, 0.4f, 0.6f);
	glVertex2f(0.11f, -0.26f);
	glEnd();

	glPointSize(8.0f);
	glBegin(GL_POINTS);
	glColor3f(0.2f, 0.4f, 0.6f);
	glVertex2f(0.16f, -0.22f);
	glEnd();

	glPointSize(13.0f);
	glBegin(GL_POINTS);
	glColor3f(0.0f, 0.4f, 0.5f);
	glVertex2f(0.16f, -0.19f);
	glVertex2f(0.11f, -0.22f);
	glVertex2f(0.06f, -0.22f);
	glVertex2f(0.06f, -0.26f);
	glVertex2f(0.11f, -0.22f);
	glVertex2f(-0.01f, -0.30f);
	glEnd();

	glPointSize(2.0f);
	glBegin(GL_POINTS);
	glColor3f(0.0f, 0.4f, 0.5f);
	glVertex2f(-0.05f, -0.32f);
	glVertex2f(-0.05f, -0.31f);
	glVertex2f(-0.05f, -0.30f);
	glEnd();

	glPointSize(6.0f);
	glBegin(GL_POINTS);
	glColor3f(0.0f, 0.4f, 0.5f);
	glVertex2f(-0.05f, -0.29f);
	glVertex2f(-0.05f, -0.26f);
	glVertex2f(0.04f, -0.27f);
	glVertex2f(0.0f, -0.27f);
	glVertex2f(0.02f, -0.27f);
	glVertex2f(0.04f, -0.27f);
	glVertex2f(0.06f, -0.27f);
	glVertex2f(-0.04f, -0.27f);
	glVertex2f(-0.06f, -0.27f);
	glVertex2f(-0.09f, -0.27f);
	glVertex2f(-0.11f, -0.22f);
	glVertex2f(-0.11f, -0.20f);
	glEnd();

	glPointSize(5.0f);
	glBegin(GL_POINTS);
	glColor3f(0.6f, 0.6f, 0.4f);
	glVertex2f(0.12f, -0.06f);
	glVertex2f(0.10f, -0.06f);
	glVertex2f(0.08f, -0.06f);
	glVertex2f(0.14f, -0.06f);
	glVertex2f(0.17f, -0.06f);
	glVertex2f(0.19f, -0.08f);
	glVertex2f(0.21f, -0.08f);
	glVertex2f(0.23f, -0.10f);
	glVertex2f(0.25f, -0.12f);
	glVertex2f(0.27f, -0.12f);
	glVertex2f(0.27f, -0.14f);
	glVertex2f(0.25f, -0.16f);
	glVertex2f(0.23f, -0.16f);
	glVertex2f(0.21f, -0.16f);
	glVertex2f(0.18f, -0.16f);
	glEnd();

	glPointSize(5.0f);
	glBegin(GL_POINTS);
	glColor3f(0.6f, 0.7f, 0.5f);
	glVertex2f(0.12f, -0.08f);
	glVertex2f(0.16f, -0.08f);
	glVertex2f(0.20f, -0.10f);
	glVertex2f(0.18f, -0.10f);
	glVertex2f(0.16f, -0.10f);
	glVertex2f(0.14f, -0.10f);
	glVertex2f(0.20f, -0.12f);
	glVertex2f(0.22f, -0.12f);
	glVertex2f(0.24f, -0.12f);
	glVertex2f(0.18f, -0.12f);
	glVertex2f(0.16f, -0.12f);
	glVertex2f(0.20f, -0.14f);
	glVertex2f(0.22f, -0.14f);
	glVertex2f(0.24f, -0.14f);
	glVertex2f(0.18f, -0.14f);
	glEnd();

	glPointSize(5.0f);
	glBegin(GL_POINTS);
	glColor3f(0.9f, 0.8f, 0.6f);
	glVertex2f(0.20f, -0.18f);
	glVertex2f(0.20f, -0.20f);
	glVertex2f(0.20f, -0.22f);
	glVertex2f(0.20f, -0.24f);
	glVertex2f(0.22f, -0.24f);
	glVertex2f(0.22f, -0.22f);
	glVertex2f(0.22f, -0.18f);
	glVertex2f(0.22f, -0.20f);
	glEnd();

	glPointSize(5.0f);
	glBegin(GL_POINTS);
	glColor3f(0.9f, 0.7f, 0.5f);
	glVertex2f(0.24f, -0.18f);
	glColor3f(0.9f, 0.7f, 0.5f);
	glVertex2f(0.26f, -0.18f);
	glVertex2f(0.24f, -0.20f);
	glVertex2f(0.26f, -0.20f);
	glVertex2f(0.24f, -0.22f);
	glEnd();

	glPointSize(9.0f);
	glBegin(GL_POINTS);
	glColor3f(0.3f, 0.3f, 0.1f);
	glVertex2f(-0.11f, -0.33f);
	glVertex2f(-0.11f, -0.36f);
	glVertex2f(-0.14f, -0.38f);
	glVertex2f(-0.14f, -0.40f);
	glVertex2f(-0.14f, -0.42f);
	glVertex2f(-0.14f, -0.44f);
	glVertex2f(-0.14f, -0.46f);
	glVertex2f(-0.14f, -0.48f);
	glVertex2f(0.20f, -0.28f);
	glVertex2f(0.20f, -0.30f);
	glVertex2f(0.20f, -0.32f);
	glVertex2f(0.20f, -0.34f);
	glVertex2f(0.22f, -0.36f);
	glVertex2f(0.22f, -0.38f);
	glVertex2f(0.22f, -0.40f);
	glVertex2f(0.22f, -0.42f);
	glVertex2f(0.24f, -0.44f);
	glVertex2f(0.24f, -0.46f);
	glEnd();

	glPointSize(9.0f);
	glBegin(GL_POINTS);
	glColor3f(0.3f, 0.4f, 0.3f);//التنوره
	glVertex2f(-0.13f, -0.36f);
	glVertex2f(-0.13f, -0.38f);
	glVertex2f(-0.13f, -0.40f);
	glVertex2f(-0.13f, -0.42f);
	glVertex2f(-0.13f, -0.44f);
	glVertex2f(-0.13f, -0.46f);
	glVertex2f(-0.113f, -0.48f);
	glVertex2f(-0.09f, -0.38f);
	glVertex2f(-0.09f, -0.40f);
	glVertex2f(-0.09f, -0.42f);
	glVertex2f(-0.09f, -0.44f);
	glVertex2f(-0.09f, -0.46f);
	glVertex2f(-0.09f, -0.48f);
	glVertex2f(-0.12f, -0.36f);
	glVertex2f(-0.11f, -0.36f);
	glVertex2f(-0.10f, -0.36f);
	glVertex2f(-0.09f, -0.36f);
	glVertex2f(-0.08f, -0.36f);
	glVertex2f(-0.06f, -0.36f);
	glVertex2f(-0.05f, -0.36f);
	glVertex2f(-0.12f, -0.38f);
	glVertex2f(-0.13f, -0.40f);
	glVertex2f(-0.13f, -0.42f);
	glVertex2f(-0.13f, -0.44f);
	glVertex2f(-0.13f, -0.46f);
	glVertex2f(-0.13f, -0.48f);
	glVertex2f(-0.11f, -0.38f);
	glVertex2f(-0.11f, -0.40f);
	glVertex2f(-0.11f, -0.42f);
	glVertex2f(-0.11f, -0.44f);
	glVertex2f(-0.11f, -0.46f);
	glVertex2f(-0.11f, -0.48f);
	glVertex2f(-0.09f, -0.38f);
	glVertex2f(-0.09f, -0.40f);
	glVertex2f(-0.09f, -0.42f);
	glVertex2f(-0.09f, -0.44f);
	glVertex2f(-0.09f, -0.46f);
	glVertex2f(-0.09f, -0.48f);
	glVertex2f(-0.07f, -0.38f);
	glVertex2f(-0.07f, -0.40f);
	glVertex2f(-0.07f, -0.42f);
	glVertex2f(-0.07f, -0.44f);
	glVertex2f(-0.07f, -0.46f);
	glVertex2f(-0.07f, -0.48f);
	glColor3f(0.3f, 0.5f, 0.3f);
	glVertex2f(-0.05f, -0.38f);
	glVertex2f(-0.05f, -0.40f);
	glVertex2f(-0.05f, -0.42f);
	glVertex2f(-0.05f, -0.44f);
	glVertex2f(-0.05f, -0.46f);
	glVertex2f(-0.05f, -0.48f);
	glVertex2f(-0.03f, -0.36f);
	glVertex2f(-0.03f, -0.38f);
	glVertex2f(-0.03f, -0.40f);
	glVertex2f(-0.03f, -0.42f);
	glVertex2f(-0.03f, -0.44f);
	glVertex2f(-0.03f, -0.46f);
	glVertex2f(-0.03f, -0.48f);
	glVertex2f(-0.01f, -0.36f);
	glVertex2f(-0.01f, -0.38f);
	glVertex2f(-0.01f, -0.40f);
	glVertex2f(-0.01f, -0.42f);
	glVertex2f(-0.01f, -0.44f);
	glVertex2f(-0.01f, -0.46f);
	glVertex2f(-0.01f, -0.48f);
	glVertex2f(0.01f, -0.36f);
	glVertex2f(0.01f, -0.38f);
	glVertex2f(0.01f, -0.40f);
	glVertex2f(0.01f, -0.42f);
	glVertex2f(0.01f, -0.44f);
	glVertex2f(0.01f, -0.46f);
	glVertex2f(0.01f, -0.48f);
	glVertex2f(0.03f, -0.36f);
	glVertex2f(0.03f, -0.38f);
	glVertex2f(0.03f, -0.40f);
	glVertex2f(0.03f, -0.42f);
	glVertex2f(0.03f, -0.44f);
	glVertex2f(0.03f, -0.46f);
	glVertex2f(0.03f, -0.48f);
	glVertex2f(0.05f, -0.36f);
	glVertex2f(0.05f, -0.38f);
	glVertex2f(0.05f, -0.40f);
	glVertex2f(0.05f, -0.42f);
	glVertex2f(0.05f, -0.44f);
	glVertex2f(0.05f, -0.46f);
	glVertex2f(0.05f, -0.48f);
	glVertex2f(0.06f, -0.36f);
	glVertex2f(0.06f, -0.38f);
	glVertex2f(0.06f, -0.40f);
	glVertex2f(0.06f, -0.42f);
	glVertex2f(0.06f, -0.44f);
	glVertex2f(0.06f, -0.46f);
	glVertex2f(0.06f, -0.48f);
	glVertex2f(0.08f, -0.33f);
	glVertex2f(0.08f, -0.34f);
	glVertex2f(0.08f, -0.36f);
	glVertex2f(0.08f, -0.38f);
	glVertex2f(0.08f, -0.40f);
	glVertex2f(0.08f, -0.42f);
	glVertex2f(0.08f, -0.44f);
	glVertex2f(0.08f, -0.46f);
	glVertex2f(0.08f, -0.48f);
	glVertex2f(0.10f, -0.33f);
	glVertex2f(0.10f, -0.34f);
	glVertex2f(0.10f, -0.36f);
	glVertex2f(0.10f, -0.38f);
	glVertex2f(0.10f, -0.40f);
	glVertex2f(0.10f, -0.42f);
	glVertex2f(0.10f, -0.44f);
	glVertex2f(0.10f, -0.46f);
	glVertex2f(0.10f, -0.48f);
	glVertex2f(0.12f, -0.36f);
	glVertex2f(0.12f, -0.38f);
	glVertex2f(0.12f, -0.40f);
	glVertex2f(0.12f, -0.42f);
	glVertex2f(0.12f, -0.44f);
	glVertex2f(0.12f, -0.46f);
	glVertex2f(0.12f, -0.48f);
	glVertex2f(0.14f, -0.40f);
	glVertex2f(0.14f, -0.42f);
	glVertex2f(0.14f, -0.44f);
	glVertex2f(0.14f, -0.46f);
	glVertex2f(0.14f, -0.48f);
	glColor3f(0.3f, 0.4f, 0.3f);
	glVertex2f(0.12f, -0.33f);
	glVertex2f(0.12f, -0.34f);
	glVertex2f(0.14f, -0.27f);
	glVertex2f(0.14f, -0.30f);
	glVertex2f(0.14f, -0.32f);
	glVertex2f(0.14f, -0.34f);
	glVertex2f(0.14f, -0.36f);
	glVertex2f(0.14f, -0.38f);
	glVertex2f(0.16f, -0.27f);
	glVertex2f(0.16f, -0.30f);
	glVertex2f(0.16f, -0.32f);
	glVertex2f(0.16f, -0.34f);
	glVertex2f(0.16f, -0.36f);
	glVertex2f(0.16f, -0.38f);
	glVertex2f(0.16f, -0.40f);
	glVertex2f(0.16f, -0.42f);
	glVertex2f(0.16f, -0.44f);
	glVertex2f(0.16f, -0.46f);
	glVertex2f(0.16f, -0.48f);
	glVertex2f(0.16f, -0.40f);
	glVertex2f(0.16f, -0.42f);
	glVertex2f(0.16f, -0.44f);
	glVertex2f(0.16f, -0.46f);
	glVertex2f(0.16f, -0.48f);
	glVertex2f(0.18f, -0.27f);
	glVertex2f(0.18f, -0.30f);
	glVertex2f(0.18f, -0.32f);
	glVertex2f(0.18f, -0.34f);
	glVertex2f(0.18f, -0.36f);
	glVertex2f(0.18f, -0.38f);
	glVertex2f(0.18f, -0.40f);
	glVertex2f(0.18f, -0.42f);
	glVertex2f(0.18f, -0.44f);
	glVertex2f(0.18f, -0.46f);
	glVertex2f(0.18f, -0.48f);
	glVertex2f(0.20f, -0.36f);
	glVertex2f(0.20f, -0.38f);
	glVertex2f(0.20f, -0.40f);
	glVertex2f(0.20f, -0.42f);
	glVertex2f(0.20f, -0.44f);
	glVertex2f(0.20f, -0.46f);
	glVertex2f(0.20f, -0.48f);
	glVertex2f(0.22f, -0.44f);
	glVertex2f(0.22f, -0.46f);
	glVertex2f(0.22f, -0.48f);
	glEnd();

	glPointSize(9.0f);//الجزمه
	glBegin(GL_POINTS);
	glColor3f(0.0f, 0.0f, 0.0f);
	glVertex2f(0.16f, -0.50f);
	glVertex2f(0.16f, -0.52f);
	glVertex2f(0.14f, -0.50f);
	glVertex2f(0.14f, -0.52f);
	glVertex2f(0.18f, -0.50f);
	glVertex2f(0.18f, -0.52f);
	glVertex2f(0.20f, -0.50f);
	glVertex2f(0.20f, -0.52f);
	glVertex2f(0.22f, -0.50f);
	glVertex2f(0.22f, -0.52f);
	glVertex2f(0.14f, -0.50f);
	glVertex2f(0.14f, -0.52f);
	glVertex2f(0.12f, -0.52f);

	glVertex2f(-0.02f, -0.50f);
	glVertex2f(-0.02f, -0.52f);
	glVertex2f(-0.04f, -0.50f);
	glVertex2f(-0.04f, -0.52f);
	glVertex2f(-0.06f, -0.50f);
	glVertex2f(-0.06f, -0.52f);
	glVertex2f(-0.08f, -0.50f);
	glVertex2f(-0.08f, -0.52f);
	glVertex2f(-0.10f, -0.50f);
	glVertex2f(-0.10f, -0.52f);
	glVertex2f(-0.12f, -0.52f);

	glEnd();
}
void grannysHair()
{
	///////////////////////////////////الشعر //////////////////////////////////
	glPointSize(5.0f);
	glBegin(GL_POINTS);
	glColor3f(0.5f, 0.5f, 0.5f);
	glVertex2f(-0.32f, 0.14f);
	glVertex2f(-0.32f, 0.12f);
	glVertex2f(-0.34f, 0.12f);
	glVertex2f(-0.36f, 0.12f);
	glVertex2f(-0.36f, 0.14f);
	glVertex2f(-0.38f, 0.16f);
	glVertex2f(-0.38f, 0.18f);
	glVertex2f(-0.36f, 0.18f);
	glVertex2f(-0.36f, 0.20f);
	glVertex2f(-0.34f, 0.20f);
	glVertex2f(-0.36f, 0.22f);
	glVertex2f(-0.36f, 0.24f);
	glVertex2f(-0.34f, 0.26f);
	glVertex2f(-0.32f, 0.28f);
	glVertex2f(-0.30f, 0.30f);
	glVertex2f(-0.30f, 0.32f);
	glVertex2f(-0.26f, 0.32f);
	glVertex2f(-0.24f, 0.32f);
	glVertex2f(-0.22f, 0.32f);
	glVertex2f(-0.20f, 0.32f);
	glVertex2f(-0.18f, 0.32f);
	glVertex2f(-0.16f, 0.32f);
	glVertex2f(-0.14f, 0.32f);
	glVertex2f(-0.12f, 0.32f);
	glVertex2f(-0.10f, 0.32f);
	glVertex2f(-0.08f, 0.32f);
	glVertex2f(-0.08f, 0.28f);
	glVertex2f(-0.06f, 0.28f);
	glVertex2f(-0.04f, 0.28f);
	glVertex2f(-0.04f, 0.26f);
	glVertex2f(-0.02f, 0.26f);
	glVertex2f(-0.02f, 0.24f);
	glVertex2f(0.0f, 0.24f);
	glVertex2f(0.0f, 0.22f);
	glVertex2f(0.02f, 0.22f);
	glVertex2f(0.02f, 0.20f);
	glVertex2f(0.02f, 0.20f);
	glVertex2f(0.02f, 0.18f);
	glVertex2f(0.04f, 0.17f);
	glVertex2f(0.06f, 0.17f);
	glVertex2f(0.08f, 0.17f);
	glVertex2f(0.10f, 0.17f);
	glVertex2f(0.12f, 0.17f);
	glVertex2f(0.13f, 0.14f);
	glVertex2f(0.15f, 0.14f);
	glVertex2f(0.15f, 0.12f);
	glVertex2f(0.15f, 0.10f);
	glVertex2f(0.15f, 0.08f);
	glVertex2f(0.17f, 0.06f);
	glVertex2f(0.19f, 0.04f);
	glVertex2f(0.21f, 0.02f);
	glVertex2f(0.23f, 0.02f);
	glVertex2f(0.25f, 0.02f);
	glVertex2f(0.27f, 0.04f);
	glVertex2f(0.29f, 0.06f);
	glVertex2f(0.31f, 0.08f);
	glVertex2f(0.31f, 0.10f);
	glVertex2f(0.27f, 0.04f);
	glVertex2f(0.29f, 0.06f);
	glVertex2f(0.31f, 0.08f);
	glVertex2f(0.31f, 0.10f);
	glVertex2f(0.31f, 0.12f);
	glVertex2f(0.31f, 0.14f);
	glVertex2f(0.29f, 0.16f);
	glVertex2f(0.26f, 0.18f);
	glVertex2f(0.24f, 0.18f);
	glVertex2f(0.22f, 0.18f);
	glVertex2f(0.20f, 0.16f);
	glVertex2f(0.17f, 0.16f);
	glVertex2f(0.20f, 0.20f);
	glVertex2f(0.18f, 0.22f);
	glVertex2f(0.18f, 0.24f);
	glVertex2f(0.16f, 0.26f);
	glVertex2f(0.14f, 0.28f);
	glVertex2f(0.14f, 0.30f);
	glVertex2f(0.12f, 0.32f);
	glVertex2f(0.10f, 0.34f);
	glVertex2f(0.10f, 0.36f);
	glVertex2f(0.08f, 0.38f);
	glVertex2f(0.10f, 0.34f);
	glVertex2f(0.10f, 0.36f);
	glVertex2f(0.08f, 0.38f);
	glVertex2f(0.06f, 0.38);
	glVertex2f(0.04f, 0.40f);
	glVertex2f(0.02f, 0.42f);
	glVertex2f(0.0f, 0.44f);
	glVertex2f(0.0f, 0.42f);
	glVertex2f(-0.02f, 0.46f);
	glVertex2f(-0.04f, 0.46f);
	glVertex2f(-0.06f, 0.46f);
	glVertex2f(-0.08f, 0.46f);
	glVertex2f(-0.08f, 0.46f);
	glVertex2f(-0.08f, 0.46f);
	glVertex2f(-0.10f, 0.46f);
	glVertex2f(-0.12f, 0.46f);
	glVertex2f(-0.16f, 0.46f);
	glVertex2f(-0.18f, 0.44f);
	glVertex2f(-0.18f, 0.46f);
	glVertex2f(-0.20f, 0.42f);
	glVertex2f(-0.22f, 0.40f);
	glVertex2f(-0.24f, 0.40f);
	glVertex2f(-0.24f, 0.38f);
	glVertex2f(-0.26f, 0.38f);
	glVertex2f(-0.28f, 0.36f);
	glVertex2f(-0.30f, 0.34f);
	glVertex2f(-0.30f, 0.18f);
	glVertex2f(-0.32f, 0.18f);
	glVertex2f(-0.30f, 0.20f);
	glVertex2f(-0.28f, 0.21f);
	glVertex2f(-0.28f, 0.22f);
	glVertex2f(-0.28f, 0.24f);
	glVertex2f(-0.26f, 0.24f);
	glVertex2f(-0.24f, 0.24f);
	glVertex2f(-0.26f, 0.26f);
	glVertex2f(-0.26f, 0.28f);
	glVertex2f(-0.26f, 0.30f);
	glVertex2f(-0.24f, 0.30f);
	glEnd();

	glPointSize(5.0f);
	glBegin(GL_POINTS);
	glColor3f(0.8f, 0.8f, 0.8f);
	glVertex2f(-0.30f, 0.28f);
	glVertex2f(-0.30f, 0.26f);
	glVertex2f(-0.30f, 0.24f);
	glVertex2f(-0.32f, 0.24f);
	glVertex2f(-0.32f, 0.26f);
	glVertex2f(-0.32f, 0.16f);
	glVertex2f(-0.28f, 0.32f);
	glVertex2f(-0.28f, 0.34f);
	glVertex2f(-0.34f, 0.24f);
	glVertex2f(-0.34f, 0.20f);
	glEnd();

	glPointSize(11.0f);
	glBegin(GL_POINTS);
	glColor3f(0.8f, 0.8f, 0.8f);
	glVertex2f(-0.25f, 0.34f);
	glVertex2f(-0.20f, 0.36f);
	glVertex2f(-0.20f, 0.38f);
	glVertex2f(-0.16f, 0.40f);
	glVertex2f(-0.20f, 0.36f);
	glVertex2f(-0.16f, 0.38f);
	glVertex2f(-0.20f, 0.35f);
	glVertex2f(-0.16f, 0.36f);
	glVertex2f(-0.14f, 0.42f);
	glVertex2f(-0.12f, 0.42f);
	glVertex2f(-0.10f, 0.42f);
	glVertex2f(-0.08f, 0.42f);
	glVertex2f(-0.06f, 0.42f);
	glVertex2f(-0.04f, 0.42f);
	glVertex2f(-0.12f, 0.40f);
	glVertex2f(-0.10f, 0.40f);
	glVertex2f(-0.08f, 0.40f);
	glVertex2f(-0.06f, 0.40f);
	glVertex2f(-0.04f, 0.40f);
	glVertex2f(-0.12f, 0.35f);
	glVertex2f(-0.10f, 0.35f);
	glVertex2f(-0.08f, 0.35f);
	glVertex2f(-0.04f, 0.35f);
	glVertex2f(-0.07f, 0.31f);
	glVertex2f(-0.06f, 0.31f);
	glVertex2f(-0.01f, 0.31f);
	glVertex2f(-0.01f, 0.35f);
	glVertex2f(0.0f, 0.39f);
	glVertex2f(0.02f, 0.37f);
	glVertex2f(0.02f, 0.32f);
	glVertex2f(0.00f, 0.30f);
	glVertex2f(0.02f, 0.27f);
	glVertex2f(0.02f, 0.26f);
	glVertex2f(0.07f, 0.31f);
	glVertex2f(0.06f, 0.35f);
	glVertex2f(0.07f, 0.26f);
	glVertex2f(0.12f, 0.26f);
	glVertex2f(0.12f, 0.31f);
	glVertex2f(0.10f, 0.28f);
	glVertex2f(0.06f, 0.21f);
	glEnd();

	glPointSize(17.0f);
	glBegin(GL_POINTS);
	glColor3f(0.8f, 0.8f, 0.8f);
	glVertex2f(0.10f, 0.22f);
	glVertex2f(0.15f, 0.21f);
	glVertex2f(0.15f, 0.18f);
	glVertex2f(0.20f, 0.14f);
	glVertex2f(0.20f, 0.10f);
	glVertex2f(0.22f, 0.06f);
	glVertex2f(0.22f, 0.13f);
	glVertex2f(0.26f, 0.13f);
	glVertex2f(0.26f, 0.09f);
	glEnd();

	// 0.5  / 0.6    / 0.6  حتاف يدامر
	glPointSize(5.0f);
	glBegin(GL_POINTS);
	glColor3f(0.8f, 0.8f, 0.8f);
	glVertex2f(-0.28f, 0.30f);
	glVertex2f(-0.28f, 0.28f);
	glVertex2f(-0.30f, 0.24f);
	glVertex2f(-0.30f, 0.22f);
	glVertex2f(-0.32f, 0.22f);
	glVertex2f(-0.34f, 0.22f);
	glVertex2f(-0.32f, 0.20f);
	glVertex2f(-0.35f, 0.16f);
	glVertex2f(-0.34f, 0.18f);
	glVertex2f(-0.34f, 0.16f);
	glVertex2f(-0.34f, 0.14f);
	glEnd();
}


void grandmaHouse() {
	// Roof
	glColor3f(0.6, 0.4, 0.2);
	glBegin(GL_POLYGON);
	glVertex2f(0.0, 0.5);
	glVertex2f(0.5, 0.5);
	glVertex2f(0.7, 0.35);
	glVertex2f(0.2, 0.35);
	glEnd();


	glColor3f(0.6f, 0.4f, 0.2f);
	glLineWidth(20);
	glBegin(GL_LINES);
	glVertex2f(0.0, 0.5);
	glVertex2f(-0.2, 0.35);
	glEnd();

	//// Top of Front Wall
	glColor3f(0.8, 0.7, 0.9);
	glBegin(GL_TRIANGLES);
	glVertex2f(0.0, 0.5);
	glVertex2f(-0.2, 0.35);
	glVertex2f(0.2, 0.35);
	glEnd();

	// Front Wall
	glColor3f(0.8, 0.7, 0.9);
	glBegin(GL_POLYGON);
	glVertex2f(-0.2, 0.35);
	glVertex2f(0.2, 0.35);
	glVertex2f(0.2, 0.1);
	glVertex2f(-0.2, 0.1);
	glEnd();

	// Front Door
	glColor3f(0.6, 0.4, 0.2);
	glBegin(GL_POLYGON);
	glVertex2f(-0.1, 0.3);
	glVertex2f(0.1, 0.3);
	glVertex2f(0.1, 0.1);
	glVertex2f(-0.1, 0.1);
	glEnd();

	// Front Door Lock
	glColor3f(0.7, 0.5, 0.0);
	glPointSize(8);
	glBegin(GL_POINTS);
	glVertex2f(0.06, 0.17);
	glEnd();

	// Side Wall
	glColor3f(0.9, 0.8, 1.0);
	glBegin(GL_POLYGON);
	glVertex2f(0.2, 0.35);
	glVertex2f(0.7, 0.35);
	glVertex2f(0.7, 0.1);
	glVertex2f(0.2, 0.1);
	glEnd();

	// Window one
	glColor3f(0.6, 0.8, 1.0);
	glBegin(GL_POLYGON);
	glVertex2f(0.23, 0.32);
	glVertex2f(0.35, 0.32);
	glVertex2f(0.35, 0.23);
	glVertex2f(0.23, 0.23);
	glEnd();

	// Lines of window one
	glColor3f(1.0, 1.0, 1.0);
	glLineWidth(5);
	glBegin(GL_LINES);
	glVertex2f(0.29, 0.32);
	glVertex2f(0.29, 0.23);
	glVertex2f(0.23, 0.275);
	glVertex2f(0.35, 0.275);
	glEnd();

	// Window two
	glColor3f(0.6, 0.8, 1.0);
	glBegin(GL_POLYGON);
	glVertex2f(0.43, 0.32);
	glVertex2f(0.55, 0.32);
	glVertex2f(0.55, 0.23);
	glVertex2f(0.43, 0.23);
	glEnd();
	// Lines of window two
	glColor3f(1.0, 1.0, 1.0);
	glLineWidth(5);
	glBegin(GL_LINES);
	glVertex2f(0.49, 0.32);
	glVertex2f(0.49, 0.23);
	glVertex2f(0.43, 0.275);
	glVertex2f(0.55, 0.275);
	glEnd();

	// Window three
	glColor3f(0.6, 0.8, 1.0);
	glBegin(GL_POLYGON);
	glVertex2f(-0.06, 0.2);
	glVertex2f(0.06, 0.2);
	glVertex2f(0.06, 0.28);
	glVertex2f(-0.06, 0.28);
	glEnd();
	// Lines of window three
	glColor3f(1.0, 1.0, 1.0);
	glLineWidth(5);
	glBegin(GL_LINES);
	glVertex2f(-0.06, 0.2);
	glVertex2f(0.06, 0.2);
	glVertex2f(0.06, 0.28);
	glVertex2f(-0.06, 0.28);
	glVertex2f(-0.06, 0.199);
	glVertex2f(-0.06, 0.284);
	glVertex2f(0.06, 0.199);
	glVertex2f(0.06, 0.284);

	glVertex2f(0.0, 0.2);
	glVertex2f(0.0, 0.284);

	glVertex2f(-0.06, 0.24);
	glVertex2f(0.06, 0.24);




	glEnd();









	// Process all OpenGL routines as quickly as possible
	glFlush();
}

void flowerR()
{
	glPointSize(4.0f);
	glBegin(GL_POINTS);
	glColor3f(0.0f, 0.0f, .0f);
	// glVertex2f(0.0466026924458, 0.4814061082885);
	 //center
	 //glColor3f(1.0f, 1.0f, .2f);
	glVertex2f(0.0001627077349, 0.2343185420988);
	glVertex2f(0, 0.2);

	glColor3f(0.2f, 0.4f, .1f);
	//trunk
	glVertex2f(0.0014529951961, -0.5016329978216);
	glVertex2f(0.0014529951961, -0.4294339831145);
	glVertex2f(0.0014529951961, -0.3637985151989);
	glVertex2f(0.0014529951961, -0.2915995004918);
	glVertex2f(0.0014529951961, -0.2915995004918);
	glVertex2f(0.0014529951961, -0.2369780361781);
	glVertex2f(0.0014529951961, -0.1822331207204);
	glVertex2f(0.0014529951961, -0.1297226916079);
	glVertex2f(0.0014529951961, -0.0772122624954); //ورق الجذع
	glColor3f(0.3f, 0.5f, .0f);
	glVertex2f(-0.0774584463015, -0.3);
	glVertex2f(-0.0774584463015, -0.3535582934665);
	glVertex2f(-0.0774584463015, -0.4113273823811);
	glVertex2f(-0.1394545417221, -0.3);
	glVertex2f(-0.1394545417221, -0.3535582934665);
	glVertex2f(-0.215802105348, -0.2638106460606);
	//other side
	glVertex2f(0.0774584463015, -0.3);
	glVertex2f(0.0774584463015, -0.3535582934665);
	glVertex2f(0.0774584463015, -0.4113273823811);
	glVertex2f(0.1394545417221, -0.3);
	glVertex2f(0.1394545417221, -0.3535582934665);
	glVertex2f(0.215802105348, -0.2638106460606);
	glEnd();
}

void flower1()
{
	glPointSize(10.0f);
	glBegin(GL_POINTS);
	//leafs
	// glColor3f(0.8f, 0.4f, .4f);
	glVertex2f(0.0268457046849, -0.022943698829);
	glVertex2f(0.1040633442151, -0.022943698829);
	glVertex2f(-0.0534606404265, -0.022943698829);

	glVertex2f(-0.1167791048412, -0.022943698829);
	glVertex2f(-0.1167791048412, 0.0542739407011);
	glVertex2f(-0.1167791048412, 0.1253141690689);

	glVertex2f(0.1167791048412, -0.022943698829);
	glVertex2f(0.1167791048412, 0.0542739407011);
	glVertex2f(0.1167791048412, 0.1253141690689);

	glVertex2f(0.0268457046849, 0.0542739407011);
	glVertex2f(0.1040633442151, 0.0542739407011);
	glVertex2f(-0.0534606404265, 0.0542739407011);
	glVertex2f(-0.1167791048412, 0.0542739407011);

	glVertex2f(0.0268457046849, 0.1253141690689);
	glVertex2f(0.1040633442151, 0.1253141690689);
	glVertex2f(-0.0534606404265, 0.1253141690689);
	glVertex2f(-0.1167791048412, 0.1253141690689);
	//up
	glVertex2f(0.0268457046849, 0.3091562710633);
	glVertex2f(0.1040633442151, 0.3091562710633);
	glVertex2f(-0.0534606404265, 0.3091562710633);
	glVertex2f(-0.1167791048412, 0.3091562710633);
	glVertex2f(-0.1167791048412, 0.3865156240461);
	glVertex2f(-0.1167791048412, 0.4544896592541);
	glVertex2f(0.1167791048412, 0.3091562710633);
	glVertex2f(0.1167791048412, 0.3865156240461);
	glVertex2f(0.1167791048412, 0.4544896592541);
	//fill
	glVertex2f(0.0268457046849, 0.3865156240461);
	glVertex2f(0.1040633442151, 0.3865156240461);
	glVertex2f(-0.0534606404265, 0.3865156240461);
	glVertex2f(-0.1167791048412, 0.3865156240461);

	glVertex2f(0.0268457046849, 0.4544896592541);
	glVertex2f(0.1040633442151, 0.4544896592541);
	glVertex2f(-0.0534606404265, 0.4544896592541);
	glVertex2f(-0.1167791048412, 0.4544896592541);
	//left
	glVertex2f(-0.0788985912566, 0.3605458593712);
	glVertex2f(-0.0788985912566, 0.3144875514146);
	glVertex2f(-0.0788985912566, 0.2676981592047);
	glVertex2f(-0.0788985912566, 0.2143290087153);
	glVertex2f(-0.0788985912566, 0.1602287739727);
	glVertex2f(-0.0788985912566, 0.1039352864701);
	glVertex2f(-0.125238358929, 0.1039352864701);
	glVertex2f(-0.1686261355347, 0.1039352864701);
	glVertex2f(-0.2165023028236, 0.1039352864701);
	glVertex2f(-0.25, 0.1039352864701);
	//left other side
	glVertex2f(-0.25, 0.3605458593712);
	glVertex2f(-0.25, 0.3144875514146);
	glVertex2f(-0.25, 0.2676981592047);
	glVertex2f(-0.25, 0.2143290087153);
	glVertex2f(-0.25, 0.1602287739727);
	glVertex2f(-0.25, 0.1039352864701);
	//left up
	glVertex2f(-0.125238358929, 0.3605458593712);
	glVertex2f(-0.1686261355347, 0.3605458593712);
	glVertex2f(-0.2165023028236, 0.3605458593712);
	glVertex2f(-0.25, 0.3605458593712);
	//left fill
	glVertex2f(-0.1582280304516, 0.3605458593712);
	glVertex2f(-0.1582280304516, 0.3144875514146);
	glVertex2f(-0.1582280304516, 0.2676981592047);
	glVertex2f(-0.1582280304516, 0.2143290087153);
	glVertex2f(-0.1582280304516, 0.1602287739727);
	glVertex2f(-0.1582280304516, 0.1039352864701);

	glVertex2f(-0.1796226927089, 0.3605458593712);
	glVertex2f(-0.1796226927089, 0.3144875514146);
	glVertex2f(-0.1796226927089, 0.2676981592047);
	glVertex2f(-0.1796226927089, 0.2143290087153);
	glVertex2f(-0.1796226927089, 0.1602287739727);
	glVertex2f(-0.1796226927089, 0.1039352864701);
	//right
	glVertex2f(0.0788985912566, 0.3605458593712);
	glVertex2f(0.0788985912566, 0.3144875514146);
	glVertex2f(0.0788985912566, 0.2676981592047);
	glVertex2f(0.0788985912566, 0.2143290087153);
	glVertex2f(0.0788985912566, 0.1602287739727);
	glVertex2f(0.0788985912566, 0.1039352864701);
	glVertex2f(0.125238358929, 0.1039352864701);
	glVertex2f(0.1686261355347, 0.1039352864701);
	glVertex2f(0.2165023028236, 0.1039352864701);
	glVertex2f(0.25, 0.1039352864701);
	//left other side
	glVertex2f(0.25, 0.3605458593712);
	glVertex2f(0.25, 0.3144875514146);
	glVertex2f(0.25, 0.2676981592047);
	glVertex2f(0.25, 0.2143290087153);
	glVertex2f(0.25, 0.1602287739727);
	glVertex2f(0.25, 0.1039352864701);
	//left up
	glVertex2f(0.125238358929, 0.3605458593712);
	glVertex2f(0.1686261355347, 0.3605458593712);
	glVertex2f(0.2165023028236, 0.3605458593712);
	glVertex2f(0.25, 0.3605458593712);
	//left fill
	glVertex2f(0.1582280304516, 0.3605458593712);
	glVertex2f(0.1582280304516, 0.3144875514146);
	glVertex2f(0.1582280304516, 0.2676981592047);
	glVertex2f(0.1582280304516, 0.2143290087153);
	glVertex2f(0.1582280304516, 0.1602287739727);
	glVertex2f(0.1582280304516, 0.1039352864701);

	glVertex2f(0.1796226927089, 0.3605458593712);
	glVertex2f(0.1796226927089, 0.3144875514146);
	glVertex2f(0.1796226927089, 0.2676981592047);
	glVertex2f(0.1796226927089, 0.2143290087153);
	glVertex2f(0.1796226927089, 0.1602287739727);
	glVertex2f(0.1796226927089, 0.1039352864701);
	glEnd();
}

void MyExtr3()
{
	glMatrixMode(GL_MODELVIEW);

	glPushMatrix();
	glTranslatef(0.12, -.33, 0.0);
	glScalef(.2f, .2f, .0f);
	flowerR();
	glColor3f(0.5f, 0.1f, .4f);
	flower1();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.7, -.33, 0.0);
	glScalef(.2f, .2f, .0f);
	flowerR();
	glColor3f(0.7f, 0.4f, .4f);
	flower1();
	glPopMatrix();
	glPushMatrix();
	glTranslatef(0.9, -.33, 0.0);
	glScalef(.2f, .2f, .0f);
	flowerR();
	glColor3f(0.7f, 0.5f, .8f);
	flower1();
	glPopMatrix();
	/*
	glPushMatrix();
	glTranslatef (0.33, -.3, 0.0);
	 glScalef( .2f, .2f, .0f );
	  flower();
	glPopMatrix();
	glPushMatrix();
	glTranslatef (0.33, -.3, 0.0);
	 glScalef( .2f, .2f, .0f );
	  flower();
	glPopMatrix();
	 */
	glPushMatrix();
	glTranslatef(-0.9, -.33, 0.0);
	glScalef(.2f, .2f, .0f);
	flowerR();
	glColor3f(0.8f, 0.3f, .6);
	flower1();
	glPopMatrix();
	glPushMatrix();
	glTranslatef(-0.7, -.33, 0.0);
	glScalef(.2f, .2f, .0f);
	flowerR();
	glColor3f(0.9f, 0.5f, 1.f);
	flower1();
	glPopMatrix();
	glPushMatrix();
	glTranslatef(-.5, -.33, 0.0);
	glScalef(.2f, .2f, .0f);
	flowerR();
	glColor3f(1.f, 0.5f, .5f);
	flower1();
	glPopMatrix();
	glPushMatrix();
	glTranslatef(-.31, -.33, 0.0);
	glScalef(.2f, .2f, .0f);
	flowerR();
	glColor3f(0.7f, .4f, 4.0f);
	flower1();
	glPopMatrix();
	glPushMatrix();
	glTranslatef(-.1, -.33, 0.0);
	glScalef(.2f, .2f, .0f);
	flowerR();
	glColor3f(0.8f, 0.33f, .4f);
	flower1();
	glPopMatrix();
	glPushMatrix();
	//glTranslatef (.12, -.3, 0.0);
  //glScalef( .2f, .2f, .0f );
	 // flower();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.9, -.33, 0.0);
	glScalef(.2f, .2f, .0f);
	flowerR();
	glColor3f(0.8f, 0.3f, .6);
	flower1();
	glPopMatrix();
	glPushMatrix();
	glTranslatef(0.7, -.33, 0.0);
	glScalef(.2f, .2f, .0f);
	flowerR();
	glColor3f(0.9f, 0.5f, 1.f);
	flower1();
	glPopMatrix();
	glPushMatrix();
	glTranslatef(.5, -.33, 0.0);
	glScalef(.2f, .2f, .0f);
	flowerR();
	glColor3f(1.f, 0.5f, .5f);
	flower1();
	glPopMatrix();
	glPushMatrix();
	glTranslatef(.31, -.33, 0.0);
	glScalef(.2f, .2f, .0f);
	flowerR();
	glColor3f(0.7f, .4f, 4.0f);
	flower1();
	glPopMatrix();

	glPushMatrix();
	//glTranslatef (.12, -.3, 0.0);
  //glScalef( .2f, .2f, .0f );
	 // flower();
	glPopMatrix();

	/*
	glPushMatrix();
  glTranslatef (0.2, -.3, 0.0);
   glScalef( .5f, .5f, .0f );
	flower();
	glPopMatrix();
	glPushMatrix();
	glTranslatef (0.7, -.3, 0.0);
	// glScalef( .5f, .5f, .0f );
	  flower();
	glPopMatrix();
	glPushMatrix();
	glTranslatef (0.72, -.3, 0.0);
	  flower();
	glPopMatrix();
	glPushMatrix();
	glTranslatef (-2.1, -.3, 0.0);
	  flower();
	glPopMatrix();
	glPushMatrix();
	glTranslatef (-1.4, -.3, 0.0);
	  flower();
	glPopMatrix();
	glPushMatrix();
	glTranslatef (.7, -.3, 0.0);
	  flower();



	glPopMatrix();
*/
}

void pick()
{
	glPushMatrix();
	glTranslatef(0.52, -.24, 0.0);
	glRotatef(-40.0f, 0.0f, 0.0f, 1.0f);
	glScalef(.2f, .1f, .0f);
	flowerR();
	glColor3f(0.8f, 0.0f, .3f);
	flower1();
	glPopMatrix();
}


void TheHunter() {
	glEnable(GL_BLEND);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, myTexture);
	glPushMatrix();
	glScalef(-0.9f, 0.9f, 1.0f);
	glColor3f(1.0f, 1.0f, 1.0f);
	// Set color to white for textur
	glBindTexture(GL_TEXTURE_2D, myTexture);
	glBegin(GL_QUADS);
	glColor3f(0.5, 0.5, 0.5);
	glTexCoord2f(0.0, 0.0); glVertex2f(0.3f, 0.6f);
	glTexCoord2f(1.0, 1.0); glVertex2f(-0.3f, 0.6f);
	glTexCoord2f(1.0, 0.0); glVertex2f(-0.3f, -0.5f);
	glTexCoord2f(0.0, 0.0); glVertex2f(0.3f, -0.5f);
	glEnd();
	glPopMatrix();
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_TEXTURE_2D);
}



void drawGlasses() {
	// Glasses (Black)
	glColor3f(0.0, 0.0, 0.0); // Black color for the glasses
	glPushMatrix();
	glTranslatef(-0.1, 0.11, 0.0); // Position for the left glass
	drawCircle(0.1, 360); // You can adjust the size and shape of the glasses as needed
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.1, 0.11, 0.0); // Position for the right glass
	drawCircle(0.1, 360); // You can adjust the size and shape of the glasses as needed
	glPopMatrix();

	// Glasses Frame Lines (Brown)
	glColor3f(0.647, 0.165, 0.165); // Brown color for the frame lines

	// Left Frame Line
	glPushMatrix();
	glTranslatef(-0.1, 0.11, 0.0); // Position for the left frame line
	glLineWidth(5.0); // تعيين عرض الخط
	glBegin(GL_LINES);
	glVertex2f(-0.1, 0.11); // Start point
	glVertex2f(-0.1, 0.06); // End point
	glEnd();
	glPopMatrix();

	// Right Frame Line
	glPushMatrix();
	glTranslatef(0.1, 0.11, 0.0); // Position for the right frame line
	glLineWidth(5.0); // تعيين عرض الخط
	glBegin(GL_LINES);
	glVertex2f(0.1, 0.11); // Start point
	glVertex2f(0.1, 0.06); // End point
	glEnd();
	glPopMatrix();

	// Reflection inside the left black glass
	glPushMatrix();
	glColor3f(1.0, 1.0, 1.0); // White color for the reflection
	glTranslatef(-0.1, 0.13, 0.0); // Offset for the reflection, matching the left black glass
	drawCircle(0.05, 360); // Adjust the size and shape of the reflection
	glPopMatrix();

	// Reflection inside the right black glass
	glPushMatrix();
	glColor3f(1.0, 1.0, 1.0); // White color for the reflection
	glTranslatef(0.1, 0.13, 0.0); // Offset for the reflection, matching the right black glass
	drawCircle(0.05, 360); // Adjust the size and shape of the reflection
	glPopMatrix();

	// Glasses (Silver)
	glPushMatrix();
	glColor3f(0.75, 0.75, 0.75); // Silver color for the glasses
	glTranslatef(-0.1, 0.11, 0.001); // Position for the left silver glass (slightly in front of black glass)
	drawCircle(0.110, 360); // Adjust the size and shape of the silver glasses as needed
	glPopMatrix();

	// Reflection inside the left silver glass
	glPushMatrix();
	glColor3f(1.0, 1.0, 1.0); // White color for the reflection
	glTranslatef(-0.1, 0.13, 0.001); // Offset for the reflection, matching the left silver glass
	drawCircle(0.015, 360); // Adjust the size and shape of the reflection
	glPopMatrix();

	// Reflection inside the right silver glass
	glPushMatrix();
	glColor3f(1.0, 1.0, 1.0); // White color for the reflection
	glTranslatef(0.1, 0.13, 0.001); // Offset for the reflection, matching the right silver glass
	drawCircle(0.015, 360); // Adjust the size and shape of the reflection
	glPopMatrix();

	// Glasses (Light Blue)
	glPushMatrix();
	glColor3f(0.678, 0.847, 0.902); // Light Blue color for the glasses
	glTranslatef(-0.1, 0.11, 0.002); // Position for the left light blue glass (slightly in front of silver glass)
	drawCircle(0.095, 360); // Adjust the size and shape of the light blue glasses as needed
	glPopMatrix();

	// Reflection inside the left light blue glass
	glPushMatrix();
	glColor3f(1.0, 1.0, 1.0); // White color for the reflection
	glTranslatef(-0.1, 0.11, 0.002); // Offset for the reflection, matching the left light blue glass
	drawCircle(0.030, 360); // Adjust the size and shape of the reflection
	glPopMatrix();

	// Right Light Blue Glass
	glPushMatrix();
	glColor3f(0.678, 0.847, 0.902); // Light Blue color for the right light blue glass
	glTranslatef(0.1, 0.11, 0.002); // Position for the right light blue glass (slightly in front of silver glass)
	drawCircle(0.11, 360); // Adjust the size and shape of the right light blue glass as needed
	glPopMatrix();

	// Reflection inside the right light blue glass
	glPushMatrix();
	glColor3f(1.0, 1.0, 1.0); // White color for the reflection
	glTranslatef(0.1, 0.13, 0.002); // Offset for the reflection, matching the right light blue glass
	drawCircle(0.035, 360); // Adjust the size and shape of the reflection
	glPopMatrix();
}


void drawHat() {
	// Hat (Brown)
	glColor3f(0.545, 0.271, 0.075); // Brown color for the hat
	glPushMatrix();
	glTranslatef(0.0, 0.2, 0.0); // Position for the hat on top of the head
	drawOval(0.35, 0.15, 360); // Adjust the size and shape of the hat as needed
	glPopMatrix();

	// Hat Band (Dark Brown)
	glColor3f(0.2, 0.1, 0.0); // Dark brown color for the hat band
	glPushMatrix();
	glTranslatef(0.0, 0.2, 0.0); // Position for the hat band
	drawOval(0.25, 0.05, 360); // Adjust the size and shape of the hat band as needed
	glPopMatrix();
}

void drawWolf() {

	glPushMatrix();
	glTranslatef(0.4, 0.3, 0.0); // نقل الذئب قليلاً للأعلى

	glScalef(0.4, 0.5, 0.5); // Scale down the entire wolf by half


	// Body
	glColor3f(0.5, 0.5, 0.5); // Gray color
	glPushMatrix();
	glTranslatef(0.0, -0.6, 0.0); // Move the body down
	drawOval(0.2, 0.7, 360);
	glPopMatrix();


	// Hands (dark grey, small oval-shaped)
	glColor3f(0.3, 0.3, 0.3); // Dark gray color for the hands
	glPushMatrix();
	glTranslatef(-0.20, -0.5, 0.4); // Left hand position inside the body
	drawOval(0.05, 0.3, 360);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.20, -0.5, 0.4); // Right hand position inside the body
	drawOval(0.05, 0.3, 360);
	glPopMatrix();

	// Long, slanted tail (dark gray, oval-shaped)
	glColor3f(0.3, 0.3, 0.3); // Dark gray color for the tail
	glPushMatrix();
	glTranslatef(-0.4, -0.6, 0.0); // Position the tail behind the body
	glRotatef(45.0, 0.0, 0.0, 1.0); // Rotate the tail to make it slanted
	glScalef(0.15, 0.7, 1.0); // Adjust dimensions to create a long tail
	drawOval(0.2, 0.4, 360);
	glPopMatrix();



	// Face
	glColor3f(0.3, 0.3, 0.3); // Dark gray color
	drawCircle(0.3, 360);



	// Eyes
	glColor3f(1.0, 1.0, 1.0); // White color for Eyes
	glPushMatrix();
	glTranslatef(-0.1, 0.1, 0.0); // Left eye position

	drawCircle(0.08, 360);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(0.1, 0.1, 0.0); // Right eye position
	drawCircle(0.08, 360);
	glPopMatrix();



	// Brown Irises
	glColor3f(0.0, 0.0, 0.0); // Black color
	glPushMatrix();
	glTranslatef(-0.1, 0.1, 0.0); // Left iris position (inside the left eye)
	drawCircle(0.03, 360);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(0.1, 0.1, 0.0); // Right iris position (inside the right eye)
	drawCircle(0.03, 360);
	glPopMatrix();

	// Nose
	glColor3f(0.0, 0.0, 0.0); // Black color
	glPushMatrix();
	glTranslatef(0.0, -0.05, 0.0);
	drawCircle(0.03, 360);
	glPopMatrix();

	// Legs (Oval-shaped)
	glColor3f(0.5, 0.5, 0.5); // Gray color for the legs
	glPushMatrix();
	glTranslatef(-0.15, -1.2, 0.0); // Position for the left leg (closer to the body)
	drawOval(0.05, 0.2, 360);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(0.15, -1.2, 0.0); // Position for the right leg (closer to the body)
	drawOval(0.05, 0.2, 360);
	glPopMatrix();


	// Mouth
	glPushMatrix();
	glTranslatef(0.0, -0.2, 0.0);
	glBegin(GL_LINES);
	glVertex2f(-0.05, -0.05);
	glVertex2f(0.05, -0.05);
	glEnd();
	glPopMatrix();

	// Mouth (Small Oval)
	glColor3f(0.0, 0.0, 0.0); // Black color for mouth
	glPushMatrix();
	glTranslatef(0.0, -0.15, 0.0);
	drawOval(0.1, 0.05, 360);
	glPopMatrix();

	// Teeth (White)
	glColor3f(1.0, 1.0, 1.0); // White color for teeth
	glPushMatrix();
	glTranslatef(-0.05, -0.15, 0.0); // Position for left teeth
	for (int i = 0; i < 3; i++) {
		glPushMatrix();
		glTranslatef(0.03 * i, 0.0, 0.0); // Adjust tooth position
		drawOval(0.015, 0.03, 360);
		glPopMatrix();
	}
	glPopMatrix();
	glPushMatrix();
	glTranslatef(0.05, -0.15, 0.0); // Position for right teeth
	for (int i = 0; i < 3; i++) {
		glPushMatrix();
		glTranslatef(-0.03 * i, 0.0, 0.0); // Adjust tooth position
		drawOval(0.015, 0.03, 360);
		glPopMatrix();
	}
	glPopMatrix();

	// Red Tongue
	glColor3f(1.0, 0.0, 0.0); // Red color for tongue
	glPushMatrix();
	glTranslatef(0.0, -0.2, 0.0);
	drawOval(0.05, 0.03, 360);
	glPopMatrix();
	drawHat();

	drawGlasses();
	glPopMatrix(); // End scaling transformation

}


void wolf() {

	glPushMatrix();
	glTranslatef(0.4, 0.3, 0.0); // نقل الذئب قليلاً للأعلى

	glScalef(0.4, 0.5, 0.5); // Scale down the entire wolf by half


	// Body
	glColor3f(0.5, 0.5, 0.5); // Gray color
	glPushMatrix();
	glTranslatef(0.0, -0.6, 0.0); // Move the body down
	drawOval(0.2, 0.7, 360);
	glPopMatrix();


	// Hands (dark grey, small oval-shaped)
	glColor3f(0.3, 0.3, 0.3); // Dark gray color for the hands
	glPushMatrix();
	glTranslatef(-0.20, -0.5, 0.4); // Left hand position inside the body
	drawOval(0.05, 0.3, 360);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.20, -0.5, 0.4); // Right hand position inside the body
	drawOval(0.05, 0.3, 360);
	glPopMatrix();

	// Long, slanted tail (dark gray, oval-shaped)
	glColor3f(0.3, 0.3, 0.3); // Dark gray color for the tail
	glPushMatrix();
	glTranslatef(-0.4, -0.6, 0.0); // Position the tail behind the body
	glRotatef(45.0, 0.0, 0.0, 1.0); // Rotate the tail to make it slanted
	glScalef(0.15, 0.7, 1.0); // Adjust dimensions to create a long tail
	drawOval(0.2, 0.4, 360);
	glPopMatrix();



	// Face
	glColor3f(0.3, 0.3, 0.3); // Dark gray color
	drawCircle(0.3, 360);



	// Ears
	glColor3f(0.3, 0.3, 0.3); // Dark gray color for the ears
	glPushMatrix();
	glTranslatef(-0.1, 0.4, 0.0); // Left ear position
	drawOval(0.1, 0.2, 360);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(0.1, 0.4, 0.0); // Right ear position
	drawOval(0.1, 0.2, 360);
	glPopMatrix();


	// Small lengthwise ovals for very light gray ear shadows
	glColor3f(0.9, 0.9, 0.9); // Very light gray color for the shadow
	glPushMatrix();
	glTranslatef(-0.1, 0.45, 0.0); // Position for left ear shadow
	drawOval(0.05, 0.12, 360);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(0.1, 0.45, 0.0); // Position for right ear shadow
	drawOval(0.05, 0.12, 360);
	glPopMatrix();



	// Eyes
	glColor3f(1.0, 1.0, 1.0); // White color for Eyes
	glPushMatrix();
	glTranslatef(-0.1, 0.1, 0.0); // Left eye position

	drawCircle(0.08, 360);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(0.1, 0.1, 0.0); // Right eye position
	drawCircle(0.08, 360);
	glPopMatrix();



	// Brown Irises
	glColor3f(0.0, 0.0, 0.0); // Black color
	glPushMatrix();
	glTranslatef(-0.1, 0.1, 0.0); // Left iris position (inside the left eye)
	drawCircle(0.03, 360);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(0.1, 0.1, 0.0); // Right iris position (inside the right eye)
	drawCircle(0.03, 360);
	glPopMatrix();

	// Nose
	glColor3f(0.0, 0.0, 0.0); // Black color
	glPushMatrix();
	glTranslatef(0.0, -0.05, 0.0);
	drawCircle(0.03, 360);
	glPopMatrix();

	// Legs (Oval-shaped)
	glColor3f(0.5, 0.5, 0.5); // Gray color for the legs
	glPushMatrix();
	glTranslatef(-0.15, -1.2, 0.0); // Position for the left leg (closer to the body)
	drawOval(0.05, 0.2, 360);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(0.15, -1.2, 0.0); // Position for the right leg (closer to the body)
	drawOval(0.05, 0.2, 360);
	glPopMatrix();


	// Mouth
	glPushMatrix();
	glTranslatef(0.0, -0.2, 0.0);
	glBegin(GL_LINES);
	glVertex2f(-0.05, -0.05);
	glVertex2f(0.05, -0.05);
	glEnd();
	glPopMatrix();

	// Mouth (Small Oval)
	glColor3f(0.0, 0.0, 0.0); // Black color for mouth
	glPushMatrix();
	glTranslatef(0.0, -0.15, 0.0);
	drawOval(0.1, 0.05, 360);
	glPopMatrix();

	// Teeth (White)
	glColor3f(1.0, 1.0, 1.0); // White color for teeth
	glPushMatrix();
	glTranslatef(-0.05, -0.15, 0.0); // Position for left teeth
	for (int i = 0; i < 3; i++) {
		glPushMatrix();
		glTranslatef(0.03 * i, 0.0, 0.0); // Adjust tooth position
		drawOval(0.015, 0.03, 360);
		glPopMatrix();
	}
	glPopMatrix();
	glPushMatrix();
	glTranslatef(0.05, -0.15, 0.0); // Position for right teeth
	for (int i = 0; i < 3; i++) {
		glPushMatrix();
		glTranslatef(-0.03 * i, 0.0, 0.0); // Adjust tooth position
		drawOval(0.015, 0.03, 360);
		glPopMatrix();
	}
	glPopMatrix();

	// Red Tongue
	glColor3f(1.0, 0.0, 0.0); // Red color for tongue
	glPushMatrix();
	glTranslatef(0.0, -0.2, 0.0);
	drawOval(0.05, 0.03, 360);
	glPopMatrix();
	glPopMatrix(); // End scaling transformation

}

void update(int value) {
	// Update the tree's position for animation
	treePositionX += 0.001f; // Adjust this value to control the speed of the animation
	housePosition += 0.004f;

	// Ensure the tree keeps moving by resetting its position

	if (treePositionX > 1.0f) {
		treePositionX = -1.0f;
	}

	if (housePosition > 1.0f) {
		housePosition = -1.0f;
	}



	glutPostRedisplay();
	glutTimerFunc(16, update, 0);  // 60 frames per second
}

void init() {

	glClearColor(1.0f, 1.0f, 1.0f, 1.0f); // Set background color to black and opaque
	// glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(-1, 1, -1, 1);
	glMatrixMode(GL_MODELVIEW);

	myTexture = LoadTexture(image2Path, 160, 267);

	if (myTexture == -1)

	{

		cout << "Error in loading the texture" << endl;

	}

	else

		cout << "The texture value is: " << myTexture
		<< endl;

}

void reshapeFunc(GLint new_width, GLint new_hight)
{
	glViewport(0, 0, new_width, new_hight);
	win_width = new_width;
	win_hight = new_hight;

}
void special(int key, int x, int y)
{
	//handle special keys
	switch (key) {
	case GLUT_KEY_HOME:

		break;
	case GLUT_KEY_LEFT:

		break;
	case GLUT_KEY_RIGHT:

		break;
	case GLUT_KEY_UP:

		break;
	case GLUT_KEY_DOWN:

		break;
	default:
		break;
	}
}


static void mouse(int button, int state, int x, int y)
{
	// Exercise 4
	if (button == GLUT_LEFT_BUTTON) {
		if (state == GLUT_UP) {
			scaleValue = 2;

		}
	}
	else if (button == GLUT_RIGHT_BUTTON) {
		if (state == GLUT_UP) {
			scaleValue = -2;
		}
	}
}


void keyboard(unsigned char key, int x, int y) {
	int sceneKey = -1; // Initialize sceneKey to an invalid value

	if (key >= '1' && key <= '9') {
		sceneKey = key - '1' + 1;  // Convert key to scene number for numeric keys (1 to 9)
	}
	else if (key >= 'a' && key <= 'e') {
		sceneKey = key - 'a' + 10; // Convert key to scene number for letters (10 to 14)
	}

	if (sceneKey >= 1 && sceneKey <= 14) {
		currentScene = sceneKey;
		glutPostRedisplay();  // Request a redraw to switch scenes
	}
}


void drawScene1() {
	glPushMatrix();


	glPushMatrix();
	BackgroundS1();
	door();
	window();
	panel();
	glScalef(0.13f, 0.13f, 0.12);
	glTranslatef(4.6f, 1.58f, 0.0);
	draw();
	glPopMatrix();

	glPushMatrix();
	flowerS1();
	glPopMatrix();

	glPushMatrix();
	(-treePositionX, -0.06, -0.0);
	glTranslatef(-transValue, -.2300, -0.1);
	glScalef(0.5, .5, 0.10);
	laila();
	reshapeFunc(500, 500);
	glPopMatrix();

	glPushMatrix();
	reshapeFunc(500, 500);
	glColor4f(1, .8, .6, 1);
	glScalef(0.160, 0.140, 1.0);
	glTranslatef(-2.1, -2.10, 0.0);
	facecir(0.1, 1.5, 0.6);
	glPopMatrix();

	glPushMatrix();
	glScalef(0.160, 0.140, 0.04);
	glTranslatef(-2.3, -2.06, 0.0);
	glScalef(1.0, 1.0, 0.0);
	mother();
	reshapeFunc(500, 500);
	glPopMatrix();

	glPushMatrix();


	std::string text;
	std::string text2;
	std::string text3;
	std::string text4;
	text = "Once upon a time, in a village near a dark forest, ";
	text2 = "lived Little Red Riding Hood.";
	text3 = "Her mother asked her to take food to her sick grandma";
	text4 = " She approved and took the basket with her.";

	glColor3f(1.0f, 1.0f, 1.0f);
	drawText(text4.data(), text4.size(), 10, 40);
	drawText(text3.data(), text3.size(), 10, 60);
	drawText(text2.data(), text2.size(), 10, 80);
	drawText(text.data(), text.size(), 10, 100);
	glPopMatrix();

	glEnd();

}

void drawScene2() {
	glPushMatrix();

	glPushMatrix();
	gr2();//لون السماء



	glPushMatrix();// كود للغيوم وتحريكها 
	glTranslatef(treePositionX, .0, 0.0);
	glTranslatef(-.7, .40, 0.0);
	glScalef(0.50, 0.40, 0.10);
	cloud2();
	reshapeFunc(500, 500);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(treePositionX, .0, 0.0);
	glTranslatef(.5, .40, 0.0);
	glScalef(0.6, 0.60, 0.10);
	cloud1();
	reshapeFunc(500, 500);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(treePositionX, .0, 0.0);
	glTranslatef(.999, .70, 0.0);
	glScalef(0.35, .350, 0.10);
	cloud2();
	reshapeFunc(500, 500);
	glPopMatrix();


	bush();

	glPushMatrix();
	gr();// الارض البني 
	reshapeFunc(500, 500);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(0.0, -.025, 0.0);
	BG2();// الزرع اللي لاصق بالارض 
	reshapeFunc(500, 500);
	glPopMatrix();
	glPushMatrix();
	BG();// الزرع اللي لاصق بالارض 
	reshapeFunc(500, 500);
	glPopMatrix();

	glPushMatrix();
	home();
	reshapeFunc(500, 500);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(treePositionX, -0.08, 0.0);
	glTranslatef(transValue, -.2300, 0.0);
	glScalef(0.5, .30, 0.10);
	laila();
	reshapeFunc(500, 500);
	glPopMatrix();

	glPushMatrix();
	//reshapeFunc(500, 500);
	glScalef(0.160, 0.140, 0.10);
	glTranslatef(-1., -1.4, 0.0);
	glTranslatef(-1.2, -0.6, 0.0);
	glColor4f(1, .8, .6, 1);
	glScalef(0.7, .50, 0.10);
	facecir(0.3, 1.5, 0.6);
	glPopMatrix();

	glPushMatrix();
	glScalef(0.160, 0.140, 0.04);
	glTranslatef(-2.3, -2.06, 0.0);
	glScalef(0.7, .50, 0.0);
	mother();
	reshapeFunc(500, 500);
	glPopMatrix();


	glPushMatrix();
	std::string text;
	std::string text1;
	text = " As she was leaving, her mother told her to be careful";
	text1 = " and not to talk to strangers.";
	glColor3f(1, 1, 1);
	drawText(text.data(), text.size(), 10, 60);
	drawText(text1.data(), text1.size(), 20, 40);
	glPopMatrix();
	glEnd();

}

void drawScene3() {
	glPushMatrix();
	gr2();
	glTranslatef(.0, -.27, 0.0);
	glScalef(0.40, 0.40, 0.10);
	glColor3f(0.3804f, 0.6941f, 0.8863f);
	tr();
	glTranslatef(-1., 0, 0.0);
	tr();
	glTranslatef(-1., 0, 0.0);
	tr();
	glTranslatef(4., 0, 0.0);
	tr();
	glTranslatef(5., 0, 0.0);
	tr();
	reshapeFunc(500, 500);
	glPopMatrix();
	//clouds

	glPushMatrix();
	glTranslatef(treePositionX, .0, 0.0);
	glTranslatef(-.2, .70, 0.0);
	glScalef(0.80, 0.80, 0.10);
	cloud1();
	reshapeFunc(500, 500);
	glPopMatrix();

	glPushMatrix();// كود للغيوم وتحريكها 
	glTranslatef(treePositionX, .0, 0.0);
	glTranslatef(-.7, .40, 0.0);
	glScalef(0.50, 0.40, 0.10);
	cloud2();
	reshapeFunc(500, 500);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(treePositionX, .0, 0.0);
	glTranslatef(.5, .40, 0.0);
	glScalef(0.6, 0.60, 0.10);
	cloud1();
	reshapeFunc(500, 500);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(treePositionX, .0, 0.0);
	glTranslatef(.999, .70, 0.0);
	glScalef(0.35, .350, 0.10);
	cloud2();
	reshapeFunc(500, 500);
	glPopMatrix();

	/////////1
	glPushMatrix();
	glScalef(0.8, 0.7, 0.10);
	glTranslatef(-0.4, -0.2, 0);
	wolf();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-.6, -.2, 0.0);
	glScalef(0.70, 0.70, 0.10);///في هذا الكود في الزرعه الصغيره معرف فين 
	tree();
	reshapeFunc(500, 500);// من 4333-4346
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.40, -.2, 0.0);
	glScalef(0.70, 0.70, 0.10);
	tree();
	bush();
	reshapeFunc(500, 500);
	glPopMatrix();

	glPushMatrix();
	gr();// الارض البني 
	reshapeFunc(500, 500);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.0, -.025, 0.0);
	BG2();// الزرع اللي لاصق بالارض 
	reshapeFunc(500, 500);
	glPopMatrix();

	glPushMatrix();
	BG();// الزرع اللي لاصق بالارض 
	reshapeFunc(500, 500);
	glPopMatrix();

	//glPushMatrix();
	//home();
	//reshapeFunc(500, 500);
	//glPopMatrix();

	//////////2
	/*glPushMatrix();
	glTranslatef(.40,.050, 0.0);
	glScalef(-0.70, 0.70, 0.10);
	drawWolf();
	glPopMatrix();*/

	glPushMatrix();
	glTranslatef(-0.5, -.2300, 0.0);
	glScalef(0.6, .6, 0.10);
	laila();
	reshapeFunc(500, 500);
	glPopMatrix();


	/*glPushMatrix();
	//reshapeFunc(500, 500);
	glScalef(0.160, 0.140, 0.10);
   glTranslatef(-1., -1.4, 0.0);

	glColor4f(1, .8, .6, 1);
	facecir(0.3, 1.5, 0.6);
	glPopMatrix();*/

	//glPushMatrix();
	//glScalef(0.160, 0.140, 1.0);
	//glTranslatef(-1, -1.4, 0.0);
	//mother();
	//reshapeFunc(500, 500);
	//glPopMatrix();

	glPushMatrix();
	std::string text3;
	std::string text4;
	text3 = "While she was walking through the forest";
	text4 = ",A wolf saw her and started chasing her. ";
	glColor3f(1.0f, 1.0f, 1.0f);
	drawText(text4.data(), text4.size(), 12, 60);
	drawText(text3.data(), text3.size(), 12, 80);
	glPopMatrix();



}
void drawScene4() {
	glPushMatrix();
	gr2();
	glTranslatef(.0, -.27, 0.0);
	glScalef(0.40, 0.40, 0.10);
	glColor3f(0.3804f, 0.6941f, 0.8863f);
	tr();
	glTranslatef(-1., 0, 0.0);
	tr();
	glTranslatef(-1., 0, 0.0);
	tr();
	glTranslatef(4., 0, 0.0);
	tr();
	glTranslatef(5., 0, 0.0);
	tr();
	reshapeFunc(500, 500);
	glPopMatrix();
	//clouds
	glPushMatrix();
	glTranslatef(treePositionX, .0, 0.0);
	glTranslatef(-.2, .70, 0.0);
	glScalef(0.80, 0.80, 0.10);
	cloud1();
	reshapeFunc(500, 500);
	glPopMatrix();

	glPushMatrix();// كود للغيوم وتحريكها 
	glTranslatef(treePositionX, .0, 0.0);
	glTranslatef(-.7, .40, 0.0);
	glScalef(0.50, 0.40, 0.10);
	cloud2();
	reshapeFunc(500, 500);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(treePositionX, .0, 0.0);
	glTranslatef(.5, .40, 0.0);
	glScalef(0.6, 0.60, 0.10);
	cloud1();
	reshapeFunc(500, 500);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(treePositionX, .0, 0.0);
	glTranslatef(.999, .70, 0.0);
	glScalef(0.35, .350, 0.10);
	cloud2();
	reshapeFunc(500, 500);
	glPopMatrix();

	/*glPushMatrix();
	glScalef(0.70, 0.70, 0.10);
	drawWolf();
	glPopMatrix();*/

	glPushMatrix();
	glTranslatef(-.6, -.2, 0.0);
	glScalef(0.70, 0.70, 0.10);///في هذا الكود في الزرعه الصغيره معرف فين 
	tree();
	reshapeFunc(500, 500);// من 4333-4346
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.40, -.2, 0.0);
	glScalef(0.70, 0.70, 0.10);
	tree();
	bush();
	reshapeFunc(500, 500);
	glPopMatrix();
	glPushMatrix();
	gr();// الارض البني 
	reshapeFunc(500, 500);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(0.0, -.025, 0.0);
	BG2();// الزرع اللي لاصق بالارض 
	reshapeFunc(500, 500);
	glPopMatrix();
	glPushMatrix();
	BG();// الزرع اللي لاصق بالارض 

	reshapeFunc(500, 500);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(-0.3, -0.1, 0.0);
	glScalef(-0.9, 0.9, 0.10);
	wolf();
	glPopMatrix();

	glPushMatrix();

	glTranslatef(transValue, -.2300, 0.0);
	glScalef(-0.6, .6, 0.10);
	laila();
	reshapeFunc(500, 500);
	glPopMatrix();


	/*glPushMatrix();
	//reshapeFunc(500, 500);
	glScalef(0.160, 0.140, 0.10);
   glTranslatef(-1., -1.4, 0.0);

	glColor4f(1, .8, .6, 1);
	facecir(0.3, 1.5, 0.6);
	glPopMatrix();*/

	//glPushMatrix();
	//glScalef(0.160, 0.140, 1.0);
	//glTranslatef(-1, -1.4, 0.0);
	//mother();
	//reshapeFunc(500, 500);
	//glPopMatrix();

	glPushMatrix();
	std::string text;
	std::string text2;
	std::string text3;
	std::string text4;
	std::string text5;
	std::string text6;
	//1
	/*text = "While she was walking through the forest,";
	text2 = "A wolf saw her and started chasing her. ";*/
	//2
	text3 = "Suddenly He came and talk to her and ";
	text4 = "suggested picking up flowers for her grandmother.";
	/*text5 = "the village celebrated their hero, the Hunter .";
	text6 = "THE END";*/

	glColor3f(1.0f, 1.0f, 1.0f);
	drawText(text6.data(), text4.size(), 12, 20);
	drawText(text5.data(), text4.size(), 12, 40);
	drawText(text4.data(), text4.size(), 12, 60);
	drawText(text3.data(), text3.size(), 12, 80);
	drawText(text2.data(), text2.size(), 12, 100);
	drawText(text.data(), text.size(), 12, 120);
	glPopMatrix();


}
void drawScene5() {

	glPushMatrix();
	gr2();

	glTranslatef(.0, -.27, 0.0);
	glScalef(0.40, 0.40, 0.10);
	//glColor4f(0.3882f, 0.6941f, 0.3647f,0.5f);
	glColor3f(0.3804f, 0.6941f, 0.8863f);
	tr();
	glTranslatef(-1., 0, 0.0);
	tr();
	glTranslatef(-1., 0, 0.0);
	tr();
	glTranslatef(4., 0, 0.0);
	tr();
	glTranslatef(5., 0, 0.0);
	tr();
	reshapeFunc(500, 500);
	glPopMatrix();
	//clouds

	glPushMatrix();
	glTranslatef(treePositionX, .0, 0.0);
	glTranslatef(-.2, .70, 0.0);
	glScalef(0.80, 0.80, 0.10);
	cloud1();
	reshapeFunc(500, 500);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(treePositionX, .0, 0.0);
	glTranslatef(-.7, .40, 0.0);
	glScalef(0.50, 0.40, 0.10);
	cloud2();
	reshapeFunc(500, 500);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(treePositionX, .0, 0.0);
	glTranslatef(.5, .40, 0.0);
	glScalef(0.6, 0.60, 0.10);
	cloud1();
	reshapeFunc(500, 500);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(treePositionX, .0, 0.0);
	glTranslatef(.999, .70, 0.0);
	glScalef(0.35, .350, 0.10);
	cloud2();
	reshapeFunc(500, 500);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-.6, -.2, 0.0);
	glScalef(0.70, .9, 0.10);
	tree1();
	bush();
	reshapeFunc(500, 500);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.60, -.2, 0.0);
	//glScalef(1.0, 1.0, 1.0);
	tree2();
	bush();
	reshapeFunc(500, 500);
	glPopMatrix();
	glPushMatrix();
	gr();
	reshapeFunc(500, 500);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(0.0, -.025, 0.0);
	BG2();
	reshapeFunc(500, 500);
	glPopMatrix();
	glPushMatrix();
	BG();
	reshapeFunc(500, 500);

	glPopMatrix();
	MyExtr3();
	glPushMatrix();

	//glTranslatef(treePositionX, .0, 0.0);
	glTranslatef(transValue, -.2680, 0.0);
	glScalef(0.5, .5, 0.10);
	laila();
	reshapeFunc(500, 500);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-0.06, -.32, 0.0);
	glScalef(0.1, .1, 0.10);
	pick();
	reshapeFunc(500, 500);
	glPopMatrix();

	glPushMatrix();
	std::string text;
	std::string text2;

	text = "Laila liked the idea and decided to pick some ";
	text2 = "flowers for her grandmother to make her feel better";

	glColor3f(1.0f, 1.0f, 1.0f);
	drawText(text2.data(), text2.size(), 12, 100);
	drawText(text.data(), text.size(), 12, 120);
	glPopMatrix();


	glEnd();

}

void drawScene6() {
	glPushMatrix();

	gr2();

	glTranslatef(.0, -.27, 0.0);
	glScalef(0.40, 0.40, 0.10);
	//glColor4f(0.3882f, 0.6941f, 0.3647f,0.5f);
	glColor3f(0.3804f, 0.6941f, 0.8863f);
	tr();
	glTranslatef(-1., 0, 0.0);
	tr();
	glTranslatef(-1., 0, 0.0);
	tr();
	glTranslatef(4., 0, 0.0);
	tr();
	glTranslatef(5., 0, 0.0);
	tr();
	reshapeFunc(500, 500);
	glPopMatrix();
	//clouds


	glPushMatrix();
	glTranslatef(treePositionX, .0, 0.0);
	glTranslatef(-.2, .70, 0.0);
	glScalef(0.80, 0.80, 0.10);
	cloud1();
	reshapeFunc(500, 500);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(treePositionX, .0, 0.0);
	glTranslatef(-.7, .40, 0.0);
	glScalef(0.50, 0.40, 0.10);
	cloud2();
	reshapeFunc(500, 500);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(treePositionX, .0, 0.0);
	glTranslatef(.5, .40, 0.0);
	glScalef(0.6, 0.60, 0.10);
	cloud1();
	reshapeFunc(500, 500);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(treePositionX, .0, 0.0);
	glTranslatef(.999, .70, 0.0);
	glScalef(0.35, .350, 0.10);
	cloud2();
	reshapeFunc(500, 500);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-.6, -.2, 0.0);
	glScalef(0.70, 0.70, 0.10);
	tree();
	reshapeFunc(500, 500);
	glPopMatrix();



	glPushMatrix();
	glTranslatef(0.40, -.2, 0.0);
	glScalef(0.70, 0.70, 0.10);
	tree();
	bush();
	reshapeFunc(500, 500);
	glPopMatrix();
	glPushMatrix();
	gr();
	reshapeFunc(500, 500);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(0.0, -.025, 0.0);
	BG2();
	reshapeFunc(500, 500);
	glPopMatrix();
	glPushMatrix();
	BG();
	reshapeFunc(500, 500);
	glPopMatrix();

	glPushMatrix();
	//glTranslatef(treePositionX, .0, 0.0);
	glTranslatef(0.5, -.8, 0.0);
	glScalef(1.5, 3.5, 0.10);
	grandmaHouse();
	reshapeFunc(500, 500);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(housePosition, .0, 0.0);
	glTranslatef(-0.5, -0.1, 1.0);
	glScalef(0.8, 0.8, 0.10);
	wolf();
	reshapeFunc(500, 500);
	glPopMatrix();


	glPushMatrix();
	std::string text;
	text = "While he rushed to the grandmother's house to eat her.";
	glColor3f(1.0f, 1.0f, 1.0f);
	drawText(text.data(), text.size(), 12, 120);
	glPopMatrix();


	glEnd;

}



void drawScene7() {
	TheRoom();

	glPushMatrix();
	//glTranslatef(treePositionX, .0, 0.0);
	glTranslatef(-0.1, -.1, 0.0);
	glScalef(0.6, .6, 1.0);
	grandma();
	reshapeFunc(500, 500);
	glPopMatrix();

	glPushMatrix();
	//glTranslatef(treePositionX, .0, 0.0);
	glTranslatef(-0.7, -0.1, 0.0);
	glScalef(0.8, .8, 1.0);
	wolf();
	reshapeFunc(500, 500);
	glPopMatrix();

	std::string text;
	std::string text1;
	glColor3f(1, 1, 1);
	text = "While he rushed to her grandmother's";
	text1 = "house to eat her.";
	drawText(text.data(), text.size(), 50, 100);
	drawText(text1.data(), text1.size(), 50, 80);


	glEnd();
}

void drawScene8() {
	glPushMatrix();

	gr2();

	glTranslatef(.0, -.27, 0.0);
	glScalef(0.40, 0.40, 0.10);
	glColor3f(0.3804f, 0.6941f, 0.8863f);
	tr();
	glTranslatef(-1., 0, 0.0);
	tr();
	glTranslatef(-1., 0, 0.0);
	tr();
	glTranslatef(4., 0, 0.0);
	tr();
	glTranslatef(5., 0, 0.0);
	tr();
	reshapeFunc(500, 500);
	glPopMatrix();
	//clouds
	glPushMatrix();
	glTranslatef(treePositionX, .0, 0.0);
	glTranslatef(-.2, .70, 0.0);
	glScalef(0.80, 0.80, 0.10);
	cloud1();
	reshapeFunc(500, 500);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(treePositionX, .0, 0.0);
	glTranslatef(-.7, .40, 0.0);
	glScalef(0.50, 0.40, 0.10);
	cloud2();
	reshapeFunc(500, 500);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(treePositionX, .0, 0.0);
	glTranslatef(.5, .40, 0.0);
	glScalef(0.6, 0.60, 0.10);
	cloud1();
	reshapeFunc(500, 500);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(treePositionX, .0, 0.0);
	glTranslatef(.999, .70, 0.0);
	glScalef(0.35, .350, 0.10);
	cloud2();
	reshapeFunc(500, 500);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-.6, -.2, 0.0);
	glScalef(0.70, 0.70, 0.10);
	tree();
	reshapeFunc(500, 500);
	glPopMatrix();



	glPushMatrix();
	glTranslatef(0.40, -.2, 0.0);
	glScalef(0.70, 0.70, 0.10);
	tree();
	bush();
	reshapeFunc(500, 500);
	glPopMatrix();
	glPushMatrix();
	gr();
	reshapeFunc(500, 500);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(0.0, -.025, 0.0);
	BG2();
	reshapeFunc(500, 500);
	glPopMatrix();
	glPushMatrix();
	BG();
	reshapeFunc(500, 500);
	glPopMatrix();

	glPushMatrix();
	//glTranslatef(treePositionX, .0, 0.0);
	glTranslatef(0.5, -.8, 0.0);
	glScalef(1.5, 3.5, 0.10);
	grandmaHouse();
	reshapeFunc(500, 500);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(housePosition, .0, 0.0);
	glTranslatef(-0.5, -.2280, 1.0);
	glScalef(0.60, 0.60, 0.10);
	laila();
	reshapeFunc(500, 500);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(housePosition, .0, 0.0);
	glTranslatef(-0.55, -.32, 0.0);
	glScalef(0.1, 0.1, 0.10);
	pick();
	reshapeFunc(500, 500);
	glPopMatrix();

	glPushMatrix();
	std::string text;
	std::string text2;
	std::string text3;
	text = "Laila journeyed to her grandmother's house with ";
	text2 = "a bouquet of freshly picked roses, unaware of  ";
	text3 = "the unexpected surprise that awaited her upon arrival.";
	glColor3f(1.0f, 1.0f, 1.0f);
	drawText(text3.data(), text3.size(), 12, 80);
	drawText(text2.data(), text2.size(), 12, 100);
	drawText(text.data(), text.size(), 12, 120);
	glPopMatrix();


	glEnd;
}

void drawScene9() {
	TheRoom();
	glPushMatrix();
	//glTranslatef(treePositionX, .0, 0.0);
	glTranslatef(0.1, .1, 0.0);
	glScalef(0.8, 0.8, 1.0);
	drawWolf();
	reshapeFunc(500, 500);
	glPopMatrix();

	glEnd();
}

void drawScene10() {

	glPushMatrix();

	gr2();

	glTranslatef(.0, -.27, 0.0);
	glScalef(0.40, 0.40, 0.10);
	//glColor4f(0.3882f, 0.6941f, 0.3647f,0.5f);
	glColor3f(0.3804f, 0.6941f, 0.8863f);
	tr();
	glTranslatef(-1., 0, 0.0);
	tr();
	glTranslatef(-1., 0, 0.0);
	tr();
	glTranslatef(4., 0, 0.0);
	tr();
	glTranslatef(5., 0, 0.0);
	tr();
	reshapeFunc(500, 500);
	glPopMatrix();
	//clouds


	glPushMatrix();
	glTranslatef(treePositionX, .0, 0.0);
	glTranslatef(-.2, .70, 0.0);
	glScalef(0.80, 0.80, 0.10);
	cloud1();
	reshapeFunc(500, 500);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(treePositionX, .0, 0.0);
	glTranslatef(-.7, .40, 0.0);
	glScalef(0.50, 0.40, 0.10);
	cloud2();
	reshapeFunc(500, 500);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(treePositionX, .0, 0.0);
	glTranslatef(.5, .40, 0.0);
	glScalef(0.6, 0.60, 0.10);
	cloud1();
	reshapeFunc(500, 500);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(treePositionX, .0, 0.0);
	glTranslatef(.999, .70, 0.0);
	glScalef(0.35, .350, 0.10);
	cloud2();
	reshapeFunc(500, 500);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-.6, -.2, 0.0);
	glScalef(0.70, 0.70, 0.10);
	tree();
	reshapeFunc(500, 500);
	glPopMatrix();



	glPushMatrix();
	glTranslatef(0.40, -.2, 0.0);
	glScalef(0.70, 0.70, 0.10);
	tree();
	bush();
	reshapeFunc(500, 500);
	glPopMatrix();
	glPushMatrix();
	gr();
	reshapeFunc(500, 500);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(0.0, -.025, 0.0);
	BG2();
	reshapeFunc(500, 500);
	glPopMatrix();
	glPushMatrix();
	BG();
	reshapeFunc(500, 500);
	glPopMatrix();



	//glPushMatrix();
	////glTranslatef(treePositionX, .0, 0.0);
	//glTranslatef(0.3, -.2280, 1.0);
	//glScalef(0.6, .6, 1.0);
	//laila();
	//reshapeFunc(500, 500);
	//glPopMatrix();


	glPushMatrix();
	//glTranslatef(treePositionX, .0, 0.0);
	glTranslatef(0.5, -.8, 0.0);
	glScalef(1.5, 3.5, 0.10);
	grandmaHouse();
	reshapeFunc(500, 500);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(housePosition, .0, 0.0);
	glTranslatef(-.4, .01, 0.0);
	TheHunter();
	glPopMatrix();


	/*glPushMatrix();
	glTranslatef(0.26, -0.1, 0.0);
	wolf();
	glPopMatrix();*/
	glPushMatrix();
	std::string text;
	std::string text2;
	std::string text3;
	text = "Fortunately, the hunter heard the noise ";
	text2 = "coming from Grandma's house and hurried to ";
	text3 = "save the girl and her grandmother.";
	glColor3f(1.0f, 1.0f, 1.0f);
	drawText(text3.data(), text3.size(), 12, 80);
	drawText(text2.data(), text2.size(), 12, 100);
	drawText(text.data(), text.size(), 12, 120);
	glPopMatrix();
	glEnd();


}

void drawScene11() {
	glPushMatrix();

	gr2();

	glTranslatef(.0, -.27, 0.0);
	glScalef(0.40, 0.40, 0.10);
	//glColor4f(0.3882f, 0.6941f, 0.3647f,0.5f);
	glColor3f(0.3804f, 0.6941f, 0.8863f);
	tr();
	glTranslatef(-1., 0, 0.0);
	tr();
	glTranslatef(-1., 0, 0.0);
	tr();
	glTranslatef(4., 0, 0.0);
	tr();
	glTranslatef(5., 0, 0.0);
	tr();
	reshapeFunc(500, 500);
	glPopMatrix();
	//clouds


	glPushMatrix();
	glTranslatef(treePositionX, .0, 0.0);
	glTranslatef(-.2, .70, 0.0);
	glScalef(0.80, 0.80, 0.10);
	cloud1();
	reshapeFunc(500, 500);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(treePositionX, .0, 0.0);
	glTranslatef(-.7, .40, 0.0);
	glScalef(0.50, 0.40, 0.10);
	cloud2();
	reshapeFunc(500, 500);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(treePositionX, .0, 0.0);
	glTranslatef(.5, .40, 0.0);
	glScalef(0.6, 0.60, 0.10);
	cloud1();
	reshapeFunc(500, 500);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(treePositionX, .0, 0.0);
	glTranslatef(.999, .70, 0.0);
	glScalef(0.35, .350, 0.10);
	cloud2();
	reshapeFunc(500, 500);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-.6, -.2, 0.0);
	glScalef(0.70, 0.70, 0.10);
	tree();
	reshapeFunc(500, 500);
	glPopMatrix();



	glPushMatrix();
	glTranslatef(0.40, -.2, 0.0);
	glScalef(0.70, 0.70, 0.10);
	tree();
	bush();
	reshapeFunc(500, 500);
	glPopMatrix();
	glPushMatrix();
	gr();
	reshapeFunc(500, 500);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(0.0, -.025, 0.0);
	BG2();
	reshapeFunc(500, 500);
	glPopMatrix();
	glPushMatrix();
	BG();
	reshapeFunc(500, 500);
	glPopMatrix();

	// Drawing code for scene 2
	glPushMatrix();
	//glTranslatef(treePositionX, .0, 0.0);
	glTranslatef(0.5, -.8, 0.0);
	glScalef(1.5, 3.5, 0.10);
	grandmaHouse();
	reshapeFunc(500, 500);
	glPopMatrix();

	glPushMatrix();
	//glTranslatef(treePositionX, .0, 0.0);
	glTranslatef(0.0, -.1, 0.0);
	glScalef(0.6, .6, 1.0);
	grandma();
	reshapeFunc(500, 500);
	glPopMatrix();


	glPushMatrix();
	//glTranslatef(treePositionX, .0, 0.0);
	glTranslatef(-0.5, -.2280, 1.0);
	glScalef(0.6, .6, 1.0);
	laila();
	reshapeFunc(500, 500);
	glPopMatrix();

	glPushMatrix();
	std::string text;
	std::string text2;
	std::string text3;
	std::string text4;
	std::string text5;
	std::string text6;
	text = "Finally They thanked the hunter for saving them.";
	text2 = "The story teaches us to be cautious, especially ";
	text3 = "in the woods. Little Red Riding Hood learned the";
	text4 = "importance of following her mother's advice, and";
	text5 = "the village celebrated their hero, the Hunter .";
	text6 = "THE END";

	glColor3f(1.0f, 1.0f, 1.0f);
	drawText(text6.data(), text4.size(), 12, 20);
	drawText(text5.data(), text4.size(), 12, 40);
	drawText(text4.data(), text4.size(), 12, 60);
	drawText(text3.data(), text3.size(), 12, 80);
	drawText(text2.data(), text2.size(), 12, 100);
	drawText(text.data(), text.size(), 12, 120);
	glPopMatrix();

	glEnd();


}

void drawScene12() {
	TheRoom();
	glPushMatrix();
	glTranslatef(-0.2, -0.1, 0.0);
	glScalef(-0.7, .8, 1.0);
	drawWolf();
	reshapeFunc(500, 500);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-0.1, -0.2, 0.0);
	glScalef(-0.5, 0.5, 1.0);
	laila();
	reshapeFunc(500, 500);
	glPopMatrix();

	glPushMatrix();
	std::string text;
	text = "Laila arrived to her grandmother's";
	glColor3f(1, 1, 1);
	drawText(text.data(), text.size(), 230, 100);

	std::string text1;
	text1 = "house and notice the wolf's strange.";
	glColor3f(1, 1, 1);
	drawText(text1.data(), text1.size(), 230, 82);

	std::string text2;
	text2 = "features.She ask about his";
	glColor3f(1, 1, 1);
	drawText(text2.data(), text2.size(), 230, 64);

	std::string text3;
	text3 = "features.Then the wolf reveale himself.";
	glColor3f(1, 1, 1);
	drawText(text3.data(), text3.size(), 210, 47);
	glPopMatrix();

	glEnd();
}




void renderBitmapString(float x, float y, void* font, std::string text) {
	glRasterPos2f(x, y);
	for (char c : text) {
		glutBitmapCharacter(font, c);
	}
}



void display() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	switch (currentScene) {
	case 1:
		drawScene1();
		break;
	case 2:
		drawScene2();
		break;
	case 3:
		drawScene3();
		break;
	case 4:
		drawScene4();
		break;
	case 5:
		drawScene5();
		break;
	case 6:
		drawScene6();
		break;
	case 7:
		drawScene7();
		break;
	case 8:
		drawScene8();
		break;
	case 9:
		drawScene9();
		break;
	case 10:
		drawScene12();
		break;
	case 11:
		drawScene10();
		break;
	case 12:
		drawScene11();
		break;
	}


	glutSwapBuffers();
}

int main(int argc, char** argv)
{

	glutInit(&argc, argv);               		  // Initialize GLUT
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);   //  Specify the display Mode ñ RGB, RGBA or color 				              //  Index, single or double Buffer
	glutInitWindowSize(500, 500);  		 // Set the window's initial width & height
	glutInitWindowPosition(50, 50); 		 // Position the window's initial top-left corner
	glutCreateWindow("little red riding hood");    // Create a window with the given title
	init();
	glutDisplayFunc(display);
	glutReshapeFunc(reshapeFunc);
	glutTimerFunc(0, update, 0);  // Start the animation timer
	glutMouseFunc(mouse);
	//glutMotionFunc(motion);
	glutKeyboardFunc(keyboard);
	glutMainLoop();           		// Enter the infinitely event-processing loop

	return 0;
}




