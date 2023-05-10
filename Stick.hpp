#pragma once
#include "Point.hpp"
#include <tgmath.h>

class Stick
{

public:

	Point *_p0;
	Point *_p1;
	float _length;
	float _width;
	bool _updated;
	bool _hidden;

	Stick() {}

	Stick(Point *p0, Point *p1, float length=-1, bool hidden = false, float _width = 1);

	~Stick();

	virtual float update();

	void update_points(sf::RenderWindow *window);

	void constrain_points(sf::RenderWindow *window);

	Point *move_point(float mx, float my);
	
	void render_points(sf::RenderWindow *window);

	void render(sf::RenderWindow *window, bool _render_points);

	void render_intersect(Stick *s, sf::RenderWindow *window);


private:


};