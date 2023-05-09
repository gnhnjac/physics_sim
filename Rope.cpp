#include "Rope.hpp"

Rope::Rope(Point *p0, Point *p1, float resolution, float flex_min_percent, float flex_max_percent)
{

	_resolution = resolution;

	_flex_min_percent = flex_min_percent;
	_flex_max_percent = flex_max_percent;

	if (_flex_min_percent == -1 || _flex_max_percent == -1)
	{

		_flex_min_percent = 1-_resolution;
		_flex_max_percent = 1+_resolution;

	}

	float dx = p1->_x - p0->_x;
    float dy = p1->_y - p0->_y;
    _length = sqrt(dx*dx + dy*dy);

	uint32_t extra_points = (_resolution)*_length;

	Point * _tmp_p0 = p0;

	for(uint32_t i = 0; i < extra_points; i++)
	{

		float x = (p0->_x * (extra_points - i) + p1->_x * (i + 1)) / (extra_points + 1);
		float y = (p0->_y * (extra_points - i) + p1->_y * (i + 1)) / (extra_points + 1);

		Point *_tmp_p1 = new Point(x,y);

		_sticks.push_back(FlexStick(_tmp_p0,_tmp_p1,_flex_min_percent,_flex_max_percent,_max_stress_percent));

		_tmp_p0 = _tmp_p1;

	}

	_sticks.push_back(FlexStick(_tmp_p0,p1,_flex_min_percent,_flex_max_percent,_max_stress_percent));	
	
}

void Rope::update_points()
{

	for (FlexStick s : _sticks)
		s.update_points();

}

void Rope::constrain_points(sf::RenderWindow *window)
{

	for (FlexStick s : _sticks)
		s.constrain_points(window);

}

void Rope::de_update_sticks()
{

	for (Stick s : _sticks)
		s._updated = false;

}

void Rope::de_update_points()
{

	for (Stick s : _sticks)
	{
		s._p0->_updated = false;
		s._p1->_updated = false;
	}

}

Point *Rope::check_move_point(float mx, float my)
{

	for (Stick s : _sticks)
	{
		Point *p = s.move_point(mx, my);

		if (p)
			return p;

	}

	return 0;

}

void Rope::update_sticks()
{

	float min_stability = 1;

	for (auto it = _sticks.begin(); it != _sticks.end(); it++)
    {

    	float stability = it->update();

    	if (stability < 0 && min_stability >= 0)
		{

			// handle tearing
			if (_allow_tear)
			{
				Point *p0 = new Point(it->_p0->_x,it->_p0->_y,it->_p0->_oldx,it->_p0->_oldy);
				Point *p1 = new Point(it->_p1->_x,it->_p1->_y,it->_p1->_oldx,it->_p1->_oldy);

				_sticks.erase(it--);

				_sticks.push_back(FlexStick(p0,p1,_flex_min_percent,_flex_max_percent,_max_stress_percent));

				_allow_tear = false;

			}

		}

		if (stability < min_stability)
    		min_stability = stability;

    }

   	if (min_stability < _min_stability)
   		_min_stability = min_stability;

}

void Rope::check_for_stability()
{

	if (_min_stability > 0.5)
		_allow_tear = true;

	_min_stability = 1;

}

void Rope::render(sf::RenderWindow *window, bool render_points)
{

	for (FlexStick s : _sticks)
		s.render(window, render_points);

}