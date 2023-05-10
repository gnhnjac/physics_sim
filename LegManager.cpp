#include "LegManager.hpp"
#include <tgmath.h>

LegManager::LegManager(float base, Point *left_pelvis, Point *left_knee, Point *left_foot, Point *right_pelvis, Point *right_knee, Point *right_foot)
	: _right_leg(right_pelvis), _left_leg(left_pelvis)
{

	_base = base;

	_left_leg_x = left_foot->_x;
	_left_leg_y = _base;

	_right_leg_x = right_foot->_x;
	_right_leg_y = _base;

	_grnd_left = _left_leg_x;
	_grnd_right = _right_leg_x;

    _right_leg.add_arm(right_knee);
    _right_leg.add_arm(right_foot);

    _left_leg.add_arm(left_knee);
    _left_leg.add_arm(left_foot);

	_step_time = M_PI/_step_cycles;

	_left_knee = left_knee;
	_right_knee = right_knee;

}

void LegManager::update(bool is_left_pressed, bool is_right_pressed)
{

	if (is_left_pressed && !_walking_left)
        {

            _angle = 0;
            if (_moving_left_leg)
            {
                _left_leg_x = _grnd_left+_step_cycles*_stride;
                _left_leg_y = _base;
            }
            else
            {
                _right_leg_x = _grnd_right;
                _right_leg_y = _base;
            }
            _walking_left = true;
            _moving_left_leg = true;

        }
    else if (is_right_pressed && _walking_left)
    {

        _angle = 0;
        if (!_moving_left_leg)
        {
            _right_leg_x = _grnd_right-_step_cycles*_stride;
            _right_leg_y = _base;
        }
        else
        {
            _left_leg_x = _grnd_left;
            _left_leg_y = _base;
        }
        _walking_left = false;
        _moving_left_leg = false;

    }

    if (is_left_pressed || is_right_pressed)
    {
        _angle+=_step_time;
        if (_angle >= M_PI)
        {
            _angle = 0;
            if (_moving_left_leg)
                _grnd_left = _left_leg_x;
            else
                _grnd_right = _right_leg_x;
            _moving_left_leg = !_moving_left_leg;
        }

        if (_moving_left_leg)
        {
            _left_leg_x += _stride*(_walking_left ? -1 : 1);
            _left_leg_y = _base-sin(_angle)*_step_height;
        }
        else
        {
            _right_leg_x += _stride*(_walking_left ? -1 : 1);
            _right_leg_y = _base-sin(_angle)*_step_height;
        }

    }

    if (_walking_left)
    {
        _left_knee->apply_force(-2,0);
        _right_knee->apply_force(-2,0);
    }
    else
    {
        _left_knee->apply_force(2,0);
        _right_knee->apply_force(2,0);
    }

    _left_leg.drag(_left_leg_x,_left_leg_y);
    _right_leg.drag(_right_leg_x,_right_leg_y);

}