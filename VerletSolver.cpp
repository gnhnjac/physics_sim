#include "VerletSolver.hpp"

void VerletSolver::update(sf::RenderWindow *window)
{

	for (Point *p : _points)
		p->update(window);

	for (Rope *r : _ropes)
		r->update_points(window);

	for (Stick *s : _sticks)
		s->update_points(window);

	for (FlexStick *s : _flex_sticks)
		s->update_points(window);


    for (uint32_t i = 0; i < _iters; i++)
    {
    	for (Stick *s : _sticks)
        	s->update(window);

        for (FlexStick *s : _flex_sticks)
        	s->update(window);

        for (Rope *r : _ropes)
        	r->update_sticks(window);

        for (Point *p : _points)
        	p->constrain(window);

        for (Stick *s : _sticks)
        	s->constrain_points(window);

        for (FlexStick *s : _flex_sticks)
        	s->constrain_points(window);

        for (Rope *r : _ropes)
        	r->constrain_points(window);

        for (Stick *s : _sticks)
        	s->_updated = false;

        for (FlexStick *s : _flex_sticks)
        	s->_updated = false;

        for (Rope *r : _ropes)
        	r->de_update_sticks();

    }

    for (Point *p : _points)
		p->_updated = false;

	for (Rope *r : _ropes)
	{
		r->de_update_points();
		r->check_for_stability();
	}

	for (Stick *s : _sticks){
		s->_p0->_updated = false;
		s->_p1->_updated = false;
	}

	for (FlexStick *s : _flex_sticks){
		s->_p0->_updated = false;
		s->_p1->_updated = false;
	}
}

void VerletSolver::render(sf::RenderWindow *window)
{

	for (Rope *r : _ropes)
		r->render(window,_render_points);

	if (_render_points)
	{
		for (Point *p : _points)
			p->render(window);
	}
	for (Stick *s : _sticks)
		s->render(window,_render_points);

	for (FlexStick *s : _flex_sticks)
		s->render(window,_render_points);

}