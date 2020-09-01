/*
	Solar System, Federico Favia, Summer 2019, Computer Graphics project
*/

#include <stdio.h>
#include <stdlib.h>
#include <iostream>

#define _USE_MATH_DEFINES
#include <math.h>

//GLEW
#define GLEW_STATIC
#include <GL/glew.h>

// GLFW
#include <GLFW/glfw3.h>

#include <GL/glut.h> //Utilities e.g: setting camera view and projection


using namespace std;

#include "planet.h"
#include "texture.h"

//variables and structures

struct _eye {
	float x = 0.f, y = 0.f, z = 0.f;
};

_eye eye;

planet *sun, *mercury, *venus, *earth, *mars, *jupiter, *saturn, *uranus, *neptune;
float zoom = 80.f;
float eye_theta = M_PI / 20, eye_phi = 0.f;


//functions

void light_setup(void) {

	GLfloat ambient[] = { 0.0, 0.0, 0.0, 1.0 };
	GLfloat diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat position[] = { 0.0, 5.0, -5.0, 25.0 };
	glEnable(GL_LIGHTING);

	glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
	glLightfv(GL_LIGHT0, GL_POSITION, position);
	glEnable(GL_LIGHT0);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_DEPTH_TEST);
}

void change_size(int w, int h)
{
	cout << "changeSize called" << endl;
	if (h == 0) {
		h = 1;
	} // Prevent a divide by zero, when window is too short
	float ratio = 1.0 * w / h;

	// Reset the coordinate system before modifying
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	
	// Set the viewport to be the entire window
	glViewport(0, 0, w, h);

	//frustum perspective
	glFrustum(-5.0, 5.0, -5.0, 5.0, 5.0, 750.0);
	glMatrixMode(GL_MODELVIEW);
}

void draw_solar_system() //drawing of the system
{ 
	glClear(GL_COLOR_BUFFER_BIT);
	glLoadIdentity();

	gluLookAt(0.0 + eye.x, 0.0 + eye.y, zoom, eye.x, eye.y, eye.z,	0.0, 1.0, 0.0);											

	glRotatef((eye_theta - M_PI) * (180.0f / M_PI), 1, 0, 0);
	glRotatef(eye_phi * (180.0f / M_PI), 0, 0, 1);

	sun->draw_planet(); //draw sun

	mercury->draw_planet(); //draw mercury, his orbit
	mercury->draw_orbit();

	venus->draw_planet(); //draw venus, his orbit
	venus->draw_orbit();

	earth->draw_planet(); //draw earth, his orbit
	earth->draw_orbit();

	mars->draw_planet(); //draw mars, his orbit
	mars->draw_orbit();
	
	jupiter->draw_planet(); //draw jupiter, his orbit
	jupiter->draw_orbit();
	
	saturn->draw_planet(); //draw saturn, his orbit, his rings, just 7 for simplify
	saturn->draw_orbit();
	saturn->draw_ring(1.1);
	saturn->draw_ring(1.38);
	saturn->draw_ring(1.74);
	saturn->draw_ring(2.15);
	saturn->draw_ring(2.33);
	saturn->draw_ring(2.82);
	saturn->draw_ring(5.48);

	uranus->draw_planet(); //draw uranus, his orbit, his rings, just one for simplify
	uranus->draw_orbit();
	uranus->draw_ring(1.57);

	neptune->draw_planet(); //draw neptune, his orbit
	neptune->draw_orbit();

}

void pressKey(unsigned char key, int x, int y) //keyboard handling
{
	switch (key) 
	{
		case 27: //esc
			exit(0); break;							
		case '-': //zoom out
			if (zoom > 5) zoom++; break;				
		case '+': //zoom in
			if (zoom < 750) zoom--; break;			
		case 'w': //move up
			if (eye.y < 450) eye.y++; break;
		case 's': //move down
			if (eye.y > -450) eye.y--; break;
		case 'a': //move left
			if (eye.x > -450) eye.x--; break;
		case 'd': //move right
			if (eye.x < 450) eye.x++; break;
		case 'i': //rotate view from above 
			eye_theta += M_PI / 20; break;	
		case 'k': //rotate view from below 
			eye_theta -= M_PI / 20; break;	
		case 'j': //rotate view counterclockwise
			eye_phi += M_PI / 20; break;	
		case 'l': //rotate view clockwise 
			eye_phi -= M_PI / 20;  break;	
		case 'r': // reset view, zoom, rotation
			eye.x = 0.f; eye.y = 0.f; zoom = 80.f;	eye_theta = M_PI / 20;	eye_phi = 0.f; 	break;			
	}
}

void setup_planets()
{
	sun = new planet("img/sun.jpg", 4.5f);																	//sun
	mercury = new planet("img/mercury.jpg", 0.016f, 0.47f / 100.f, 5.8f, 0.f, 0.f, 1.f / 58.f);				//mercury
	venus = new planet("img/venus.jpg", 0.039f, 0.35f / 100.f, 10.8f, 0.f, 3.f, 1.f / 243.f);				//venus
	earth = new planet("img/earth.jpg", 0.041f, 0.3f / 100.f, 15.f, 0.f, 23.44f, 1.f);						//earth
	mars = new planet("img/mars.jpg", 0.022f, 0.24f / 100.f, 22.8f, 0.f, 25.f, 1.f);						//mars
	jupiter = new planet("img/jupiter.jpg", 0.46f, 0.13f / 100.f, 77.9f, 0.f, 3.f, 1.f / 0.038f);			//jupiter
	saturn = new planet("img/saturn.jpg", 0.39f, 0.097f / 100.f, 143.4f, 0.f, 27.f, 1.f / 0.41f);			//saturn
	uranus = new planet("img/uranus.jpg", 0.17f, 0.068f / 100.f, 287.3f, 0.f, 98.f, 1.f / 0.71f);			//uranus 
	neptune = new planet("img/neptune.jpg", 0.16f, 0.054f / 100.f, 449.5f, 0.f, 28.5f, 1.f / 0.67f);		//neptune
}

void move_planets() 
{
	mercury->move_planet();
	venus->move_planet();
	earth->move_planet();
	mars->move_planet(); 
	jupiter->move_planet();
	saturn->move_planet();
	uranus->move_planet();
	neptune->move_planet();
}

void clean_planets() //delete from memory heap
{
	delete sun;
	delete mercury;
	delete venus;
	delete earth;
	delete mars;
	delete jupiter;
	delete saturn;
	delete uranus;
	delete neptune;
}

void renderScene(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.0, 0.0, 0.0, 0.0);

	draw_solar_system();
	move_planets();

	glutSwapBuffers();
}

void commands_guide() 
{
	cout << "Commands guide:" << endl;
	cout << "Move view: up W, left A, down S, right D" << endl;
	cout << "Rotate view: view from below I, counterclockwise J, view from above K, clockwise L" << endl;
	cout << "Zoom in: + | Zoom out: -" << endl;
	cout << "Reset view, zoom and rotation: press R" << endl;
}

void initGL(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA); //The mode parameter is a Boolean combination
	glutInitWindowPosition(-1, 1);
	glutInitWindowSize(950, 800);
	glutCreateWindow("Solar System");

	setup_planets(); //cretion of planets

	glutDisplayFunc(renderScene);
	glutIdleFunc(renderScene);
	glutReshapeFunc(change_size);

	glutKeyboardFunc(pressKey);   //keyboard functions
	glEnable(GL_DEPTH_TEST);
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glEnable(GL_CULL_FACE);

	glewInit();

	if (glewIsSupported("GL_VERSION_2_0"))
		printf("Ready for OpenGL 2.0\n");
	else {
		printf("OpenGL 2.0 not supported\n");
		exit(1);
	}
}

int main(int argc, char **argv)
{
	initGL(argc, argv); //initGL

	light_setup(); //light environment

	commands_guide(); //commands guide

	glutMainLoop(); //event processing loop

	clean_planets(); //delete the planets

	return 0;
}