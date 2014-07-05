//
// File:	wavefrontloader.h
// Author:      adam.lewis@athens.edu
// Purpose:
// Load the geometry information from a Wavefront OBJ 3-d model into an
// OpenGL program.  This code is based upon tutorial code from James Maples
// (http://http://www.tutorialized.com/tutorial/Write-a-WaveFront-OpenGL-3D-object-loader-in-C)
// and is licensed under a CC BY-NC-SA license.
//
#ifndef _WAVEFRONT_LOADER_H_
#define _WAVEFRONT_LOADER_H_
#define _CRT_SECURE_NO_WARNINGS


//
// Note that we using the C++ standard library vector classes in our loader.
#include <iostream>
#include <fstream>
#include <vector>
#include <cstring>
#include <GL/freeglut.h>
using namespace std;

typedef struct
{
	float x;
	float y;
	float z;
}
Vector;

typedef struct
{
	int v1, v2, v3;
	int vn1, vn2, vn3;
}
Face;

class WFObject
{
	private:
		// Dynamic variables to keep our object data in
		vector<Vector> vertices;
		vector<Vector> normals;
		vector<Face> faces;

		void parseLine(char *line);

		void parseVertex(char *line);
		void parseNormal(char *line);
		void parseFace(char *line);

	public:
		WFObject();
		~WFObject();

		bool load(char *filename);
		void draw();
};

#endif
