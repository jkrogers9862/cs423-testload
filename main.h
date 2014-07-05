//
// File:	main.h
// Author:      adam.lewis@athens.edu
// Purpose:
// Demo program for loading information from a Wavefront OBJ 3-d model into an
// OpenGL program.  This code is based upon tutorial code from James Maples
// (http://http://www.tutorialized.com/tutorial/Write-a-WaveFront-OpenGL-3D-object-loader-in-C)
// and is licensed under a CC BY-NC-SA license.
//


#ifndef _MAIN_H_
#define _MAIN_H_
#include <GL/glut.h>
#include <GL/GL.h>
#include <iostream>

using namespace std;

#include "wavefrontLoader.h"

bool keyState[256];
GLfloat angleX = 90;
GLfloat angleY = 90;
GLfloat angleZ = 90;
GLfloat myX = 0;
GLfloat myY = 0;
GLfloat myZ = 0;

// OpenGL variables
unsigned int g_persp = 1, g_ortho = 1;

// SDL stuff
int screenWidth = 800, screenHeight = 600, screenDepth;
bool screenFullScreen;

// Load models
WFObject model;

// Functions
void draw();

#endif
