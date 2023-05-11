#pragma once
#include "Stick.hpp"

class FlexStick : public Stick
{

public:
	float _min_length;
	float _max_length;
	float _max_stress;

	FlexStick(Point *p0, Point *p1, float min_length_percent, float max_length_percent, float max_stress_percent, bool hidden = false);

	float update() override;

private:

};