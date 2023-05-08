#include "Point.hpp"

Point::Point(float x, float y, float oldx, float oldy, bool is_pinned, bool hidden)
{

	_x = x;
	_y = y;
	_oldx = oldx;
	_oldy = oldy;
	_pinned = is_pinned;
	_hidden = hidden;

}

Point::Point(float x, float y, bool is_pinned, bool hidden)
{

	_x = x;
	_y = y;
	_oldx = x;
	_oldy = y;
	_pinned = is_pinned;
	_hidden = hidden;

}

void Point::update(sf::RenderWindow *window)
{

	if(_pinned || _updated)
		return;

	float vx = (_x - _oldx)*_friction;
	float vy = (_y - _oldy)*_friction;

	_oldx = _x;
	_oldy = _y;

	_x += vx;
	_y += vy;
	_y += _gravity;

	_updated = true;

}

void Point::constrain(sf::RenderWindow *window)
{

	if(_pinned)
		return;

	float vx = (_x - _oldx)*_friction;
	float vy = (_y - _oldy)*_friction;

	float width = window->getSize().x;
	float height = window->getSize().y;

	if (_x > width)
	{
		_x = width;
		_oldx = _x + vx * _bounce;
	}
	else if (_x < 0)
	{
		_x = 0;
		_oldx = _x + vx * _bounce;
	}

	if (_y > height)
	{
		_y = height;
		_oldy = _y + vy * _bounce;
	}
	else if (_y < 0)
	{
		_y = 0;
		_oldy = _y + vy * _bounce;
	}

}

void Point::apply_force(float fx, float fy)
{

	_x += fx;
	_y += fy;

}

void Point::render(sf::RenderWindow *window)
{
	if (_hidden)
		return;
	sf::CircleShape shape(_radius);
    shape.setFillColor(sf::Color::Green);
    shape.setPosition(_x-_radius,_y-_radius);
    window->draw(shape);

}