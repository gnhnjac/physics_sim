#include "IKSystem.hpp"

IKSystem::IKSystem(Point *p)
{

	_p = p;

	_x = _p->_x;
	_y = _p->_y;

}

void IKSystem::add_arm(Point *p, float width)
{

	Point *p0;

	if (_last_arm)
	{

		p0 = _last_arm->_p1;

	}
	else
	{

		p0 = _p;

	}

	Arm *r = new Arm(p0,p,width);

	r->_parent = _last_arm;

	_arms.push_back(r);
	_last_arm = r;

}

void IKSystem::add_arm(float x, float y, float width)
{

	Point *p0;

	if (_last_arm)
	{

		p0 = _last_arm->_p1;

	}
	else
	{

		p0 = _p;

	}

	Point *p = new Point(x,y);

	Arm *r = new Arm(p0,p,width);

	r->_parent = _last_arm;

	_arms.push_back(r);
	_last_arm = r;

}

void IKSystem::render(sf::RenderWindow *window)
{

	for (Arm *a : _arms)
		a->render(window);

}

void IKSystem::drag(float x, float y)
{
	_x = _arms[0]->_p0->_x;
	_y = _arms[0]->_p0->_y;
	_last_arm->drag(x, y);

}

void IKSystem::reach(float x, float y)
{

	drag(x, y);
	update();

}

void IKSystem::update()
{
	
	_arms[0]->_p0->_x = _x;
	_arms[0]->_p0->_y = _y;

}