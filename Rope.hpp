#pragma once
#include "Point.hpp"
#include "FlexStick.hpp"

class Rope
{

public:

	std::vector<FlexStick> _sticks = {};
	float _length;
	float _resolution;

	float _flex_min_percent;
	float _flex_max_percent;

	float _max_stress_percent = 3;

	bool _allow_tear = true;
	float _min_stability = 1;

	Rope(Point *p0, Point *p1, float resolution, float flex_min_percent = -1, float flex_max_percent = -1);

	void update_points();

	void update_sticks();

	void check_for_stability();

	void de_update_sticks();

	void de_update_points();

	void constrain_points(sf::RenderWindow *window);

	Point *check_move_point(float mx, float my);

	void render(sf::RenderWindow *window, bool render_points);

private:


};