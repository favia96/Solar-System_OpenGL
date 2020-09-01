#include "planet.h"

planet::planet(const std::string& _texture_path, float _radius, float _speed, float _orbit_distance, float _revolution_angle , float _axial_tilt , float _rotation_motion_angle) //class constructor
{
	radius = _radius;
	speed = _speed;
	orbit_distance = _orbit_distance;
	revolution_angle = _revolution_angle;
	axial_tilt = _axial_tilt;
	rotation_motion_angle = _rotation_motion_angle;
	my_textureFilePath = _texture_path;
	_texture = new texture(_texture_path);

	if (rotation_motion_angle != 0) {
		rotation_motion = true;
		rotation_motion_speed = _rotation_motion_angle;
	}
} 

planet::~planet() //class destructor
{
	delete _texture;
	//cout << "Destructed" << endl;
}

void planet::draw_planet() //drawing the planet shape
{
	GLUquadric *quadric; //quadric object
	quadric = gluNewQuadric();

	glPushMatrix();
	glRotatef(revolution_angle, 0.0, 1.0, 0.0); 
	glTranslatef(orbit_distance, 0.0, 0.0); 
	glPushMatrix();

	glRotatef(axial_tilt, 1.0, 0.0, 0.0);
	glRotatef(rotation_motion_angle, 0.0, 1.0, 0.0);
	glRotatef(90.0, 1.0, 0.0, 0.0);
	
	glColorMaterial(GL_FRONT, GL_DIFFUSE);
	glEnable(GL_TEXTURE_2D);
	_texture->bind();
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	gluQuadricTexture(quadric, 1);
	gluSphere(quadric, radius, 55.0, 55.0); //planet as sphere object
	glDisable(GL_TEXTURE_2D);
	
	glPopMatrix();
	glPopMatrix();

	if (rotation_motion == true) 
	{
		rotation_motion_angle += rotation_motion_speed;
		if (rotation_motion_angle > 360)
		{
			rotation_motion_angle -= 360;
		}
	}
}

void planet::move_planet() //revolution motion around sun
{
	revolution_angle = revolution_angle + speed;
	if (revolution_angle > 360.0) 
	{
		revolution_angle = 0;
	}
}

void planet::draw_orbit()  //orbit line drawing
{
	glPushMatrix();
	glRotatef(90.0, 1.0, 0.0, 0.0);
	glutWireTorus(0.001, orbit_distance, 20.0, 20.0); //in this function the first parameter is the inner radius of the torus, very little to approximate to a line
													 
	glPopMatrix();
}

void planet::draw_ring(float _ring_distance_prop) //draw rings if there are
{
	glPushMatrix();
	glRotatef(revolution_angle, 0.0, 1.0, 0.0);
	glTranslatef(orbit_distance, 0.0, 0.0);
	glRotatef(90.0 + axial_tilt, 1.0, 0.0, 0.0);
	glutWireTorus(0.01, _ring_distance_prop * radius, 20.0, 20.0); //the inner radius of the thorus is fatter than the orbit to enhance the visual effect
																   // the radius of the ring is defined as the radius of the planet multiplied by a scalar
	glPopMatrix();
}
