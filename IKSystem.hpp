#pragma once
#include "Arm.hpp"
#include "Point.hpp"

class IKSystem
{

	Point *_p;
	std::vector<Arm *> _arms = {};
	Arm *_last_arm = 0;

	float _x;
	float _y;

public:

	IKSystem(Point *p);

	void add_arm(Point *p);

	void add_arm(float x, float y);

	void drag(float x, float y);

	void reach(float x, float y);

	void update();

	void render(sf::RenderWindow *window);

private:

};