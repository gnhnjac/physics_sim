#include "Point.hpp"
#include <tgmath.h>

Point::Point(float x, float y, float oldx, float oldy, bool is_pinned, bool hidden, bool zero_grav, bool follow_mouse, float radius)
{

	_x = x;
	_y = y;
	_oldx = oldx;
	_oldy = oldy;
	_pinned = is_pinned;
	_hidden = hidden;
	_zero_grav = zero_grav;
	_follow_mouse = follow_mouse;

	if (radius != -1)
		_radius = radius;

}

Point::Point(float x, float y, bool is_pinned, bool hidden, bool zero_grav, bool follow_mouse, float radius)
{

	_x = x;
	_y = y;
	_oldx = x;
	_oldy = y;
	_pinned = is_pinned;
	_hidden = hidden;
	_zero_grav = zero_grav;
	_follow_mouse = follow_mouse;

	if (radius != -1)
		_radius = radius;

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
	if (!_zero_grav)
		_y += _gravity;

	if (_follow_mouse)
	{

		// get global mouse position
    	sf::Vector2i position = sf::Mouse::getPosition(*window);

		float dx = position.x - _x;
		float dy = position.y - _y;
		float dist = sqrt(dx*dx + dy*dy);

		// normalize to apply force
		dx /= dist;
		dy /= dist;

		dx /= 2;
		dy /= 2;

		apply_force(dx,dy);

	}

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

Point *Point::check_collision_point(float x, float y)
{

	float dx = x - _x;
	float dy = y - _y;

	if (sqrt(dx*dx + dy*dy) <= _radius)
		return this;

	return 0;

}

bool Point::check_collision_circle(float other_x, float other_y, float other_rad)
{

	float dx = other_x - _x;
	float dy = other_y - _y;

	if (sqrt(dx*dx + dy*dy) <= _radius+other_rad)
		return true;

	return false;

}

void Point::render(sf::RenderWindow *window, float radius)
{
	if (_hidden)
		return;

	if (radius == -1)
		radius = _radius;

	sf::CircleShape shape(radius);
    shape.setFillColor(sf::Color::Green);
    shape.setPosition(_x-radius,_y-radius);
    window->draw(shape);

}