#include "Stick.hpp"
#include <tgmath.h>

float remap(float value, float low1, float high1, float low2, float high2)
{

    return low2 + (value - low1) * (high2 - low2) / (high1 - low1);

}

Stick::Stick(Point *p0, Point *p1, float length, bool hidden, float width, float steer_angle)
{

    _p0 = p0;
    _p1 = p1;

    float dx = _p1->_x - _p0->_x;
    float dy = _p1->_y - _p0->_y;
    if (length == -1)
        _length = sqrt(dx*dx + dy*dy);
    else
        _length = length;

    _hidden = hidden;
    _width = width;

    if (steer_angle != -1)
    {
        _requested_dx = cos(steer_angle)*_length;
        _requested_dy = -sin(steer_angle)*_length;
    }

}

Stick::~Stick()
{

    // delete _p0;
    // delete _p1;

}

Point *Stick::move_point(float mx, float my)
{

    if (_p0->check_collision_point(mx, my))
        return _p0;
    else if(_p1->check_collision_point(mx, my))
        return _p1;

    return 0;

}

float Stick::update()
{

    if (_updated)
        return 1;

    float dx = _p1->_x - _p0->_x;
    float dy = _p1->_y - _p0->_y;
    float dist = sqrt(dx*dx + dy*dy);
    float diff = _length - dist;
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

    _updated = true;

    return 1;

}

void Stick::update_points(sf::RenderWindow *window)
{

    _p0->update(window);
    _p1->update(window);

    // try to steer towards requested angle
    if (_requested_dx != -1)
    {

        if ((_p0->_is_ground_dependant && _p0->_is_detached_from_ground) || (_p1->_is_ground_dependant && _p1->_is_detached_from_ground))
            return;

        float curr_dx = _p1->_x - _p0->_x;
        float curr_dy = _p1->_y - _p0->_y;

        float delta_dx = _requested_dx-curr_dx;
        float delta_dy = _requested_dy-curr_dy;

        delta_dx /= _length;
        delta_dy /= _length;

        float steer_force_x = remap(fabs(delta_dx), 0, 1, _steer_force,_min_steer_force);
        float steer_force_y = remap(fabs(delta_dy), 0, 1, _steer_force,_min_steer_force);

        if (fabs(delta_dy*steer_force_y) > _p0->_gravity*20)
        {

            if (delta_dy < 0)
                delta_dy = -_p0->_gravity*20/steer_force_y;
            else
                delta_dy = _p0->_gravity*20/steer_force_y;
        }

        if (fabs(delta_dy) > 0.5)
        {
            if (delta_dx > 0)
                delta_dx = -_rescue_force;
            else
                delta_dx = _rescue_force;
        }

        _p1->apply_force(delta_dx*steer_force_x,delta_dy*steer_force_y);

    }

}

void Stick::constrain_points(sf::RenderWindow *window)
{

    _p0->constrain(window);
    _p1->constrain(window);

}

void Stick::set_steer_angle(float angle)
{

    _requested_dx = cos(angle)*_length;
    _requested_dy = -sin(angle)*_length;

}

void Stick::render_points(sf::RenderWindow *window)
{

    _p0->render(window);
    _p1->render(window);

}

void Stick::render(sf::RenderWindow *window, bool _render_points)
{

    if (!_hidden)
    {
        if (_width == 1)
        {
            sf::Vertex line[] =
            {
                sf::Vertex(sf::Vector2f(_p0->_x, _p0->_y)),
                sf::Vertex(sf::Vector2f(_p1->_x, _p1->_y))
            };
            window->draw(line,2,sf::Lines);
        }
        else
        {
            float dx = _p1->_x - _p0->_x;
            float dy = _p1->_y - _p0->_y;
            sf::RectangleShape line(sf::Vector2f(sqrt(dx*dx+dy*dy), _width));
            line.setPosition(_p0->_x, _p0->_y);
            float angle = atan2(_p1->_y-_p0->_y,_p1->_x-_p0->_x);
            line.setRotation(angle*180/M_PI);
            window->draw(line);

        }
    }
    if (_render_points)
        render_points(window);

}

void Stick::render_intersect(Stick *s, sf::RenderWindow *window)
{

    float a0 = _p1->_y - _p0->_y;
    float b0 = _p0->_x - _p1->_x;
    float c0 = a0 * _p0->_x + b0 * _p0->_y;

    float a1 = s->_p1->_y - s->_p0->_y;
    float b1 = s->_p0->_x - s->_p1->_x;
    float c1 = a1 * s->_p0->_x + b1 * s->_p0->_y;


    float d = a0 * b1 - a1 * b0;

    if (d == 0) // if lines are parallel
        return;

    float intersect_x = ( b1 * c0 - b0 * c1 ) / d;
    float intersect_y = ( a0 * c1 - a1 * c0 ) / d;


    float rx0 = (intersect_x - s->_p0->_x) / (s->_p1->_x - s->_p0->_x);
    float ry0 = (intersect_y - s->_p0->_y) / (s->_p1->_y - s->_p0->_y);

    float rx1 = (intersect_x - s->_p0->_x) / (s->_p1->_x - s->_p0->_x);
    float ry1 = (intersect_y - s->_p0->_y) / (s->_p1->_y - s->_p0->_y);

    if (((rx0 >= 0 && rx0 <= 1) || (ry0 >= 0 && ry0 <= 1)) && ((rx1 >= 0 && rx1 <= 1) || (ry1 >= 0 && ry1 <= 1)))
    {
        Point inter(intersect_x, intersect_y, true);

        inter.render(window, 5.f);
    }

}