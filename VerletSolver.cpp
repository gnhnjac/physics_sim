#include "VerletSolver.hpp"

void VerletSolver::update(sf::RenderWindow *window)
{

	for (Point *p : _points)
		p->update();

	for (Rope *r : _ropes)
		r->update_points();

	for (Stick *s : _sticks)
		s->update_points();

	for (FlexStick *s : _flex_sticks)
		s->update_points();


    for (uint32_t i = 0; i < _iters; i++)
    {
    	for (Stick *s : _sticks)
        	s->update();

        for (FlexStick *s : _flex_sticks)
        	s->update();

        for (Rope *r : _ropes)
        	r->update_sticks();

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

Point *VerletSolver::check_move_point(float mx, float my)
{

	for (Point *p : _points)
	{

		Point *p_tmp = p->check_collision_point(mx, my);

		if (p_tmp)
			return p_tmp;
	}

	for (Rope *r : _ropes)
	{
		Point *p_tmp = r->check_move_point(mx, my);

		if (p_tmp)
			return p_tmp;
	}

	for (Stick *s : _sticks){

		Point *p_tmp = s->move_point(mx, my);

		if (p_tmp)
			return p_tmp;
	}

	for (FlexStick *s : _flex_sticks){

		Point *p_tmp = s->move_point(mx, my);

		if (p_tmp)
			return p_tmp;
	}

	return 0;

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