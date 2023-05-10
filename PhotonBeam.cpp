#include "PhotonBeam.hpp"
#include <tgmath.h>

PhotonBeam::PhotonBeam(Point *handle, Point *point)
{

	_handle = handle;
	_point = point;

}

void PhotonBeam::charge()
{

	if (_charging == -1)
		_charging = 0;

	_charging += _charge_increment;

	if (_charging >= _release_max)
	{
		_charging = _release_max;
		shoot();
		return;
	}
	else
	{
		float dx = _point->_x - _handle->_x;
		float dy = _point->_y - _handle->_y;

		float length = sqrt(dx*dx + dy*dy);

		dx /= length;
		dy /= length;


		_handle->apply_force(-dx*_charging*_charging_force_multiplier,dy*_charging*_charging_force_multiplier);

	}
	
}

void PhotonBeam::shoot()
{

	if (_charging == -1)
		return;

	float dx = _point->_x - _handle->_x;
	float dy = _point->_y - _handle->_y;

	float length = sqrt(dx*dx + dy*dy);

	dx /= length;
	dy /= length;


	_handle->apply_force(-dx*_charging*_force_multiplier,dy*_charging*_force_multiplier);

	_charging = -1;

}

void PhotonBeam::render(sf::RenderWindow *window)
{

	if (_charging == -1)
		return;

	float scale_factor = (log(std::min(_charging+1,_release_max))/log(_release_max));

	if (_charging+1 > _release_max)
		scale_factor = pow(_release_max-_charging,_singularity_rate);
	
	float radius = scale_factor*_max_radius;

	sf::CircleShape shape(radius);
    shape.setFillColor(sf::Color(255,0,0,scale_factor*255));
    shape.setPosition(_point->_x-radius,_point->_y-radius);
    window->draw(shape);

    float outer_radius = radius+pow(_charging,3);
    if (_charging+1 > _release_max)
    	outer_radius = radius+scale_factor;
    for(int i = 0; i < _charging; i += _charge_increment*150)
    {

    	float length = static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/outer_radius));

    	float angle = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX/(2*M_PI)));

    	sf::RectangleShape point(sf::Vector2f(3, 3));
        point.setPosition(_point->_x+cos(angle)*length, _point->_y-sin(angle)*length);
        window->draw(point);

    }
	
}