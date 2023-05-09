#include "FlexStick.hpp"

float remap(float value, float low1, float high1, float low2, float high2)
{

	return low2 + (value - low1) * (high2 - low2) / (high1 - low1);

}

FlexStick::FlexStick(Point *p0, Point *p1, float min_length_percent, float max_length_percent, float max_stress_percent)
{

	_p0 = p0;
    _p1 = p1;

    float dx = _p1->_x - _p0->_x;
    float dy = _p1->_y - _p0->_y;
    float length = sqrt(dx*dx + dy*dy);

    _min_length = length * min_length_percent;
    _max_length = length * max_length_percent;
    _max_stress = length*max_stress_percent;

}

float FlexStick::update()
{

	float dx = _p1->_x - _p0->_x;
    float dy = _p1->_y - _p0->_y;
    float dist = sqrt(dx*dx + dy*dy);

    float length;

    if (dist > _max_length)
    	length = _max_length;
    else if (dist < _min_length)
    	length = _min_length;
    else
    	return 1;

    float diff = length - dist;
    // divide each point's moving distance / 2 so each point would move equally towards / outwards of each other.
    float percent = diff / dist / 2;
    float offx = dx * percent;
    float offy = dy * percent;

    if (_p0->_pinned || _p1->_pinned)
    {
        offx*=2;
        offy*=2;
    }

    if (!_p0->_pinned)
    {
        _p0->_x -= offx;
        _p0->_y -= offy;
    }
    if (!_p1->_pinned)
    {
        _p1->_x += offx;
        _p1->_y += offy;
    }

    return remap(dist, _min_length, _max_stress, 1, 0);

}