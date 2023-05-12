#pragma once
#include "Point.hpp"
#include <tgmath.h>

float remap(float value, float low1, float high1, float low2, float high2);

class Stick
{

public:

	Point *_p0;
	Point *_p1;
	float _length;
	float _width;
	bool _updated;
	bool _hidden;
	float _requested_dx = -1;
	float _requested_dy = -1;
	float _steer_force = 7;
	float _min_steer_force = 3;
	float _rescue_force = 0.5;

	Stick() {}

	Stick(Point *p0, Point *p1, float length=-1, bool hidden = false, float _width = 1, float steer_angle = -1);

	~Stick();

	virtual float update();

	void update_points(sf::RenderWindow *window);

	void constrain_points(sf::RenderWindow *window);

	Point *move_point(float mx, float my);

	void set_steer_angle(float angle);
	
	void render_points(sf::RenderWindow *window);

	void render(sf::RenderWindow *window, bool _render_points);

	void render_intersect(Stick *s, sf::RenderWindow *window);


private:


};