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
	float _bounce = 0.5f;
	float _gravity = 0.098f;
	float _friction = 0.99f;
	bool _pinned;
	bool _updated;
	bool _hidden;
	bool _zero_grav;
	bool _follow_mouse;

	Point() {}

	Point(float x, float y, float oldx, float oldy, bool is_pinned = false, bool hidden = false, bool zero_grav = false, bool follow_mouse = false, float radius = -1);

	Point(float x, float y, bool is_pinned = false, bool hidden = false, bool zero_grav = false, bool follow_mouse = false, float radius = -1);

	void update(sf::RenderWindow *window);

	void constrain(sf::RenderWindow *window);

	void apply_force(float fx, float fy);

	Point *check_collision_point(float x, float y);

	bool check_collision_circle(float other_x, float other_y, float other_rad);

	void render(sf::RenderWindow *window, float radius=-1);

private:


};