#include "Arm.hpp"
#include <tgmath.h>
#include <math.h>

Arm::Arm(Point *p0, Point *p1, float width)
{

	_p0 = p0;
	_p1 = p1;

	float dx = _p0->_x - _p1->_x;
	float dy = _p0->_y - _p1-> _y;

	_length = sqrt(dx*dx+dy*dy);

	_angle = atan2(dy,dx);

	_width = width;

}

float Arm::get_endx()
{

	return _p0->_x + cos(_angle) * _length;

}

float Arm::get_endy()
{

	return _p0->_y + sin(_angle) * _length;

}

void Arm::point_at(float x, float y)
{

	float dx = x - _p0->_x;

	float dy = y - _p0->_y;

	_angle = atan2(dy,dx);

	_p1->_x = get_endx();

	_p1->_y = get_endy();

}

void Arm::drag(float x, float y)
{

	point_at(x, y);

	_p0->_x = x - cos(_angle) * _length;

	_p0->_y = y - sin(_angle) * _length;

	if(_parent)
		_parent->drag(_p0->_x,_p0->_y);

}

void Arm::render(sf::RenderWindow *window)
{

	if (_width == 1)
	{
		sf::Vertex line[] =
	    {
	        sf::Vertex(sf::Vector2f(_p0->_x, _p0->_y)),
	        sf::Vertex(sf::Vector2f(_p1->_x, _p1->_y))
	    };
	    window->draw(line,2,sf::Lines);
	}
	else
	{

		sf::RectangleShape line(sf::Vector2f(_length, _width));
		line.setPosition(_p0->_x, _p0->_y);
		float angle = atan2(_p1->_y-_p0->_y,_p1->_x-_p0->_x);
		line.setRotation(angle*180/M_PI);
		window->draw(line);

	}
    //_p0->render(window);
    //_p1->render(window);

}