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

	float _max_stress_percent = 2;

	bool _allow_tear = true;
	float _min_stability = 1;

	Rope(Point *p0, Point *p1, float resolution, float flex_min_percent = -1, float flex_max_percent = -1);

	void update_points(sf::RenderWindow *window);

	void update_sticks(sf::RenderWindow *window);

	void check_for_stability();

	void de_update_sticks();

	void de_update_points();

	void constrain_points(sf::RenderWindow *window);

	void render(sf::RenderWindow *window, bool render_points);

private:


};