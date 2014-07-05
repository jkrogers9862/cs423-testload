//
// File:	main.cpp
// Author:      adam.lewis@athens.edu
// Purpose:
// Demo program that loads a model from a Wavefront OBJ 3-d model into an
// OpenGL program.  This code is based upon tutorial code from James Maples
// (http://http://www.tutorialized.com/tutorial/Write-a-WaveFront-OpenGL-3D-object-loader-in-C)
// and is licensed under a CC BY-NC-SA license.
//
#include "main.h"

void reshape(int w, int h)
{
  if(h == 0)
  {
    h = 1;
  }

  // Keep global variables up to date
  screenWidth = w;
  screenHeight = h;

  // delete the last display lists
  glDeleteLists(g_persp, 1);
  glDeleteLists(g_ortho, 1);

  // set the drawable region of the window
  glViewport(0, 0, w, h);

  // generate new display list ID's
  g_persp = glGenLists(1);
  g_ortho = glGenLists(1);

  // generate perspective display list
  glNewList(g_persp, GL_COMPILE);

  // set up the projection matrix
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();

  // just use a perspective projection
  gluPerspective(45, (float)w / h, 0.1, 100);

  // go back to modelview matrix so we can move the objects about
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  glEndList();

  // generate orthographic display list
  glNewList(g_ortho, GL_COMPILE);

  // set up the projection matrix
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();

  // just use a orthographic projection
  glOrtho(0, w, h, 0, -100, 100);

  // go back to modelview matrix so we can move the objects about
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  glEndList();
}

int init()
{
    reshape(screenWidth, screenHeight);

    // OpenGL init
    // Stuff
    glShadeModel(GL_SMOOTH);
    glClearColor(0.2f, 0.2f, 0.2f, 0.0f);
    glClearDepth(1.0f);
    glDepthFunc(GL_LEQUAL);
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_FASTEST);

    // Face culling (for textures)
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glEnable(GL_DEPTH_TEST);

    // Lighting
    GLfloat light_ambient[] = { 0.5, 0.5, 0.5, 1.0 };
    GLfloat light_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat light_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat light_position[] = { 1.0, 1.0, 1.0, 1.0 };

    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glShadeModel(GL_SMOOTH);

    // Object loader
    if(!model.load("C:/(0) Game Development/Codeblocks/TestLoad/myWheel.obj"))
    {
    cout << "Could not load model" << endl;
    return false;
    }

    return true;
}

void idle()
{

}

void draw()
{
    glPushMatrix();

    // clear the screen & depth buffer
    glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

    // set the perspective projection
    glCallList(g_persp);

    // set the camera position
    gluLookAt(myX, 0, 0,	// 	eye pos
        -1, 0, 0,	// 	aim point
        0, 1, 0);	// 	up direction

    // 3D stuff	*****************************************
    glTranslatef(0,myY,myZ);

    {glRotatef(angleX, 1.0, 0.0, 0.0);}
    {glRotatef(angleY, 0.0, 1.0, 0.0);}
    {glRotatef(angleZ, 1.0, 0.0, 0.0);}

    glColor4f(1.0, 0.0, 0.0, 1.0);

    model.draw();

    // set the orthographic projection
    glCallList(g_ortho);

    // 2D/text	*****************************************

    glPopMatrix();

  // Commented out because we call it in our idle() function - maintains framerate independance
  // SDL_GL_SwapBuffers();
}

void display()
{
	// Reset background
	glClear(GL_COLOR_BUFFER_BIT);

	//Drawing the wheel
	draw();

	// Flush buffer
	glFlush();

	// Swap buffers
	glutSwapBuffers();
}

void keyInput()
{
    //glLoadIdentity();
	if(keyState['1'])
    {
        angleX += 15;
	}

	if(keyState['2'])
    {
        angleY += 15;
	}

	if(keyState['3'])
    {
        angleZ += 15;
	}

	if(keyState['a'])
    {
        myZ += 0.01;
	}

	if(keyState['d'])
    {
        myZ -= 0.01;
	}

	if(keyState['w'])
    {
        myY += 0.01;
	}

	if(keyState['s'])
    {
        myY -= 0.01;
	}

	if(keyState['q'])
    {
        myX += 0.01;
	}

	if(keyState['e'])
    {
        myX -= 0.01;
	}

	if(keyState['x'])
        {exit(0);}

	if(angleX > 360.0)
		{angleX -= 360.0;}

    if(angleX < 0.0)
        {angleX += 360.0;}

    if(angleY > 360.0)
		{angleY -= 360.0;}

    if(angleY < 0.0)
        {angleY += 360.0;}

    if(angleZ > 360.0)
		{angleZ -= 360.0;}

    if(angleZ < 0.0)
        {angleZ += 360.0;}

    if(myX > 1.0)
        {myX = 1.0;}

    if(myX < 0.0)
        {myX = 0.0;}

    if(myY > .5)
        {myY = .5;}

    if(myY < -.5)
        {myY = -.5;}

    if(myZ > .5)
        {myZ = .5;}

    if(myZ < -.5)
        {myZ = -.5;}
}

void keyPressed(unsigned char key,int x, int y)
{
    keyState[key] = true;
    keyInput();
    glutPostRedisplay();
}

void keyUp(unsigned char key, int x, int y)
{
    keyState[key] = false;
}

int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitWindowSize(screenWidth, screenHeight);

    if(init())
    {
        glutCreateWindow("myWheel");

        idle();

        glutKeyboardFunc(keyPressed);
        glutKeyboardUpFunc(keyUp);

        glutDisplayFunc(display);

        glutMainLoop();
    }

    return EXIT_SUCCESS;;
}
