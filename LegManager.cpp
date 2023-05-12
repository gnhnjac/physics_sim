#include "LegManager.hpp"
#include <tgmath.h>

LegManager::LegManager(Point *center_of_mass, Stick *left_thigh, Stick *left_calf, Stick *right_thigh, Stick *right_calf, Point *left_pelvis, Point *left_knee, Point *left_foot, Point *right_pelvis, Point *right_knee, Point *right_foot)
	: _right_leg(right_pelvis), _left_leg(left_pelvis)
{

	_left_leg_x = left_foot->_x;
	_right_leg_x = right_foot->_x;

    _right_leg.add_arm(right_knee,2);
    _right_leg.add_arm(right_foot,2);

    _left_leg.add_arm(left_knee,2);
    _left_leg.add_arm(left_foot,2);

    _left_pelvis = left_pelvis;
    _right_pelvis = right_pelvis;

	_left_knee = left_knee;
	_right_knee = right_knee;

    _left_foot = left_foot;
    _right_foot = right_foot;

    _center_of_mass = center_of_mass;

    _left_thigh = left_thigh;
    _left_calf = left_calf;

    _right_thigh = right_thigh;
    _right_calf = right_calf;

}
#include <iostream>
void LegManager::update(bool is_left_pressed, bool is_right_pressed, bool is_up_pressed, bool is_down_pressed, float dt)
{

    if (is_up_pressed && !_is_midair && _cooldown == 0)
    {
        if (_is_crouching)
        {
            _is_crouching = false;
            _left_thigh->set_steer_angle(M_PI/2);
            _left_calf->set_steer_angle(M_PI/2);
            _right_thigh->set_steer_angle(M_PI/2);
            _right_calf->set_steer_angle(M_PI/2);
            _right_leg_x = _left_leg_x + _leg_gap;
        }
        else
        {
            _is_midair = true;
            _center_of_mass->apply_force(0,-_center_of_mass->_gravity*_jump_height);
        }

        _cooldown = _cooldown_seconds;
    }


    if ((500.f - _left_foot->_y > _grnd_pixels && 500.f - _right_foot->_y > _grnd_pixels) || (_is_midair && _cooldown > _cooldown_seconds-0.1))
    {
        _is_midair = true;
        _left_knee->_is_detached_from_ground = true;
        _right_knee->_is_detached_from_ground = true;
        _left_pelvis->_is_detached_from_ground = true;
        _right_pelvis->_is_detached_from_ground = true;
        _center_of_mass->_is_detached_from_ground = true;
        _left_leg_x = _left_foot->_x;
        _right_leg_x = _right_foot->_x;

        _cooldown -= dt;
        if (_cooldown <= 0)
            _cooldown = 0;

        return;
    }

    if (_is_midair)
    {
        _is_midair = false;
        _left_knee->_is_detached_from_ground = false;
        _right_knee->_is_detached_from_ground = false;
        _left_pelvis->_is_detached_from_ground = false;
        _right_pelvis->_is_detached_from_ground = false;
        _center_of_mass->_is_detached_from_ground = false;
        _moving_left_leg = _walking_left;
        _right_leg_x = _left_leg_x + _leg_gap;
    }

    if (!_is_crouching && is_down_pressed && _cooldown == 0)
    {
        _is_crouching = true;
        _cooldown = _cooldown_seconds;

        if (_walking_left)
            crouch_left();
        else
            crouch_right();
    }

    float stride = (_is_crouching) ? _crouch_stride : _stride;

    if (is_left_pressed && _cooldown == 0)
    {

        if  (!_walking_left)
        {
            if (_moving_left_leg)
                _right_leg_x -= stride;
            _moving_left_leg = true;
            _walking_left = true;

            if (_is_crouching)
            {
                crouch_left();
            }
        }
        else
        {
            if (_moving_left_leg)
                _left_leg_x -= stride;
            else
                _right_leg_x -= stride;

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
                _left_leg_x += stride;
            }
            _moving_left_leg = false;
            _walking_left = false;

            if (_is_crouching)
            {
                crouch_right();
            }
        }
        else
        {
            if (_moving_left_leg)
                _left_leg_x += stride;
            else
                _right_leg_x += stride;

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

void LegManager::crouch_left()
{

    _left_thigh->set_steer_angle(M_PI/6);
    _left_calf->set_steer_angle(M_PI-M_PI/6);
    _right_thigh->set_steer_angle(M_PI/6);
    _right_calf->set_steer_angle(M_PI-M_PI/6);

}

void LegManager::crouch_right()
{

    _left_thigh->set_steer_angle(M_PI-M_PI/6);
    _left_calf->set_steer_angle(M_PI/6);
    _right_thigh->set_steer_angle(M_PI-M_PI/6);
    _right_calf->set_steer_angle(M_PI/6);

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