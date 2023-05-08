#pragma once
#include "Point.hpp"
#include <tgmath.h>

class Stick
{

public:

	Point *_p0;
	Point *_p1;
	float _length;

	bool _updated;

	Stick() {}

	Stick(Point *p0, Point *p1);

	~Stick();

	virtual float update(sf::RenderWindow *window);

	void update_points(sf::RenderWindow *window);

	void constrain_points(sf::RenderWindow *window);

	void render_points(sf::RenderWindow *window);

	void render(sf::RenderWindow *window, bool _render_points);

private:


};