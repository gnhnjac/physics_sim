#include "LegManager.hpp"
#include <tgmath.h>

LegManager::LegManager(Point *center_of_mass, Point *left_pelvis, Point *left_knee, Point *left_foot, Point *right_pelvis, Point *right_knee, Point *right_foot)
	: _right_leg(right_pelvis), _left_leg(left_pelvis)
{

	_left_leg_x = left_foot->_x;
	_right_leg_x = right_foot->_x;

    _right_leg.add_arm(right_knee,2);
    _right_leg.add_arm(right_foot,2);

    _left_leg.add_arm(left_knee,2);
    _left_leg.add_arm(left_foot,2);

	_left_knee = left_knee;
	_right_knee = right_knee;

    _left_foot = left_foot;
    _right_foot = right_foot;

    _center_of_mass = center_of_mass;

}
#include <iostream>
void LegManager::update(bool is_left_pressed, bool is_right_pressed, bool is_up_pressed, float dt)
{

    if (is_up_pressed && !_is_midair)
    {
        _is_midair = true;
        _left_foot->apply_force(0,-_left_foot->_gravity*_jump_height);
        _right_foot->apply_force(0,-_right_foot->_gravity*_jump_height);
    }


    if (500.f - _left_foot->_y > 4 && 500.f - _right_foot->_y > 4)
    {
        _is_midair = true;
        _left_foot->_is_detached_from_ground = true;
        _right_foot->_is_detached_from_ground = true;
        _center_of_mass->_is_detached_from_ground = true;
        _left_leg_x = _left_foot->_x;
        _right_leg_x = _right_foot->_x;
        return;
    }

    if (_is_midair)
    {
        _is_midair = false;
        _left_foot->_is_detached_from_ground = false;
        _right_foot->_is_detached_from_ground = false;
        _center_of_mass->_is_detached_from_ground = false;
        _moving_left_leg = _walking_left;
        _right_leg_x = _left_leg_x + _leg_gap;
    }

    if (is_left_pressed && _cooldown == 0)
    {

        if  (!_walking_left)
        {
            if (_moving_left_leg)
                _right_leg_x -= _stride;
            _moving_left_leg = true;
            _walking_left = true;
        }
        else
        {
            if (_moving_left_leg)
                _left_leg_x -= _stride;
            else
                _right_leg_x -= _stride;

            _moving_left_leg = !_moving_left_leg;
        }
        _cooldown = _cooldown_seconds;

    }
    else if(is_right_pressed && _cooldown == 0)
    {

        if  (_walking_left)
        {
            if (!_moving_left_leg)
            {
                _left_leg_x += _stride;
            }
            _moving_left_leg = false;
            _walking_left = false;
        }
        else
        {
            if (_moving_left_leg)
                _left_leg_x += _stride;
            else
                _right_leg_x += _stride;

            _moving_left_leg = !_moving_left_leg;
        }

        _cooldown = _cooldown_seconds;

    }
    
    _left_leg.drag(_left_leg_x,raycast_to_grnd(_left_leg_x));
    _right_leg.drag(_right_leg_x,raycast_to_grnd(_right_leg_x));
    

    _cooldown -= dt;
    if (_cooldown <= 0)
        _cooldown = 0;

}

float LegManager::raycast_to_grnd(float x)
{

    return 500.f;

}

void LegManager::render(sf::RenderWindow *window)
{

    _left_leg.render(window);
    _right_leg.render(window);

}