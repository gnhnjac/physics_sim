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
	float _charge_increment = 0.02;
	float _singularity_rate = 10;
	float _force_multiplier = 10;
	float _charging_force_multiplier = 0.5;

	PhotonBeam(Point *handle, Point *point);

	PhotonBeam() {};

	void charge(Point *center_of_mass);

	void shoot(Point *center_of_mass);

	void render(sf::RenderWindow *window);

private:

};