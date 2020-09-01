#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <iostream>

#include <GL/glew.h>

// GLFW
#include <GLFW/glfw3.h>

#include <GL/glut.h>

#include "texture.h"

using namespace std;

class planet 
{
	private:
		float radius, speed, orbit_distance, revolution_angle, axial_tilt, rotation_motion_angle;
		float rotation_motion_speed = 0.f;
		bool rotation_motion = false;
		std::string my_textureFilePath;
		texture *_texture;
		
	public:
		planet(const std::string& _texture_path, float _radius = 1.f, float _speed = 0.f, float _orbit_distance = 0.f, float _revolution_angle = 0.f, float _axial_tilt = 0.f, float _rotation_motion_angle = 0.f); //constructor
		~planet(); //destructor
		void draw_planet(); //planet
		void move_planet(); //revolution 
		void draw_orbit(); //orbit
		void draw_ring(float _ring_distance_prop); //if it has rings
};

