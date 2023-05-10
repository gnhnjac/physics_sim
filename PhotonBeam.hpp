#pragma once
#include "Point.hpp"

class PhotonBeam
{

public:
	Point *_handle;
	Point *_point;

	float _charging = -1;
	float _release_max = 10;
	float _max_radius = 40;
	float _charge_increment = 0.01;
	float _singularity_rate = 10;
	float _force_multiplier = 30;
	float _charging_force_multiplier = 0.1;

	PhotonBeam(Point *handle, Point *point);

	void charge();

	void shoot();

	void render(sf::RenderWindow *window);

private:

};