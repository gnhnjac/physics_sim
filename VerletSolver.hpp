#pragma once

#include "Stick.hpp"
#include "Point.hpp"
#include "FlexStick.hpp"
#include "Rope.hpp"

class VerletSolver
{

public:
	std::vector<Point *> _points = {};
	std::vector<Stick *> _sticks = {};
	std::vector<FlexStick *> _flex_sticks = {};
	std::vector<Rope *> _ropes = {};

	bool _render_points = true;

	uint32_t _iters;

	VerletSolver(uint32_t iters) { _iters = iters; };

	void add_point(Point *p) { _points.push_back(p); };

	void add_stick(Stick *s) { _sticks.push_back(s); };

	void add_flex_stick(FlexStick *s) { _flex_sticks.push_back(s); };

	void add_rope(Rope *r) { _ropes.push_back(r); };

	void update(sf::RenderWindow *window);

	void render(sf::RenderWindow *window);

private:

};