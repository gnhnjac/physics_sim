#pragma once

#include "Stick.hpp"
#include "Point.hpp"
#include "FlexStick.hpp"
#include "Rope.hpp"
#include <string>

class VerletSolver
{

public:
	std::vector<Point *> _points = {};
	std::vector<Stick *> _sticks = {};
	std::vector<FlexStick *> _flex_sticks = {};
	std::vector<Rope *> _ropes = {};

	bool _render_points = true;
	Point *_currently_moving = 0;

	uint32_t _iters;

	VerletSolver(uint32_t iters) { _iters = iters; };

	void add_point(Point *p) { _points.push_back(p); };

	void add_stick(Stick *s) { _sticks.push_back(s); };

	void add_flex_stick(FlexStick *s) { _flex_sticks.push_back(s); };

	void add_rope(Rope *r) { _ropes.push_back(r); };

	void update(sf::RenderWindow *window);

	Point *check_move_point(float mx, float my);

	void render(sf::RenderWindow *window);

	void save_to_file(std::string filename, sf::RenderWindow *window);

	void load_from_file(std::string filename, float left, float top);

private:

};