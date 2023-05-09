#pragma once
#include "Point.hpp"

class Arm
{

public:

	Point *_p0;
	Point *_p1;
	float _length;
	float _angle;
	Arm *_parent = 0;

	Arm(Point *p0, Point *p1);

	float get_endx();

	float get_endy();

	void point_at(float x, float y);

	void drag(float x, float y);

	void reach(float x, float y);

	void render(sf::RenderWindow *window);


private:


};