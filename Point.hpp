#pragma once
#include <SFML/Graphics.hpp>

class Point
{

public:

	float _x;
	float _y;
	float _oldx;
	float _oldy;
	float _radius = 2.f;
	float _bounce = 0.6f;
	float _gravity = 0.01f;
	float _friction = 0.999f;
	bool _pinned;
	bool _updated;
	bool _hidden;

	Point() {}

	Point(float x, float y, float oldx, float oldy, bool is_pinned = false, bool hidden = false);

	Point(float x, float y, bool is_pinned = false, bool hidden = false);

	void update(sf::RenderWindow *window);

	void constrain(sf::RenderWindow *window);

	void apply_force(float fx, float fy);

	void render(sf::RenderWindow *window);

private:


};