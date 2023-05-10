#include "VerletSolver.hpp"
#include <fstream>
#include <map>
#include <strstream>

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

	// move point according to mx and my

	// get global mouse position
    sf::Vector2i position = sf::Mouse::getPosition(*window);

    if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
    {
        if (!_currently_moving)
            _currently_moving = check_move_point(position.x, position.y);
    }
    else
    {
        _currently_moving = 0;
    }

    if(_currently_moving)
    {
        _currently_moving->_x = position.x;
        _currently_moving->_y = position.y;
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

void VerletSolver::save_to_file(std::string filename, sf::RenderWindow *window)
{

	std::map<Point *, uint32_t>pointer_to_sequence;

	uint32_t sequence_index = 0;
	float left_x = window->getSize().x;
	float top_y = window->getSize().y;
	for (Stick *s : _sticks)
    {

        if(!pointer_to_sequence.count(s->_p0))
        	pointer_to_sequence[s->_p0] = sequence_index++;
        if(!pointer_to_sequence.count(s->_p1))
        	pointer_to_sequence[s->_p1] = sequence_index++;

        if (s->_p0->_x < left_x)
        	left_x = s->_p0->_x;
        if (s->_p0->_y < top_y)
        	top_y = s->_p0->_y;

        if (s->_p1->_x < left_x)
        	left_x = s->_p1->_x;
        if (s->_p1->_y < top_y)
        	top_y = s->_p1->_y;

    }

    std::ofstream f(filename);

	// write points to file
	f << "P" << std::endl;
	for (auto element : pointer_to_sequence)
	{

		Point *p = element.first;
		uint32_t seq = element.second;

		f << seq << " " << p->_x-left_x << " " << p->_y-top_y << " " << p->_pinned << " " << p->_hidden << " " << p->_zero_grav << " " << p->_follow_mouse << " " << p->_radius << std::endl;

	}

	// write sticks to file
	f << "S" << std::endl;
	for (Stick *s : _sticks)
    {

        f << pointer_to_sequence[s->_p0] << " " << pointer_to_sequence[s->_p1] << " " << s->_length << " " << s->_hidden << std::endl;

    }

	f.close();

}

void VerletSolver::load_from_file(std::string filename, float left, float top)
{

	std::ifstream f(filename);

	std::map<uint32_t, Point *>sequence_to_pointer;

	while(f.peek() != EOF)
	{
		char line[128];
		f.getline(line,128);

		if (line[0] == 'P')
			continue;
		if (line[0] == 'S')
		{
			break;
		}

		std::strstream s;
		s << line;

		uint32_t index;
		float px;
		float py;
		bool is_pinned;
		bool hidden;
		bool zero_grav;
		bool follow_mouse;
		float radius;

		s >> index >> px >> py >> is_pinned >> hidden >> zero_grav >> follow_mouse >> radius;

		Point *p = new Point(px+left,py+top,is_pinned,hidden,zero_grav,follow_mouse,radius);

		sequence_to_pointer[index] = p;

	}

	while(f.peek() != EOF)
	{

		char line[128];
		f.getline(line,128);

		std::strstream s;
		s << line;

		uint32_t p0_index;
		uint32_t p1_index;
		float length;
		bool hidden;

		s >> p0_index >> p1_index >> length >> hidden;

		Stick *stick = new Stick(sequence_to_pointer[p0_index], sequence_to_pointer[p1_index],length,hidden);

		_sticks.push_back(stick);

	}

	f.close();

}