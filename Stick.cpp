#include "Stick.hpp"


Stick::Stick(Point *p0, Point *p1)
{

    _p0 = p0;
    _p1 = p1;

    float dx = _p1->_x - _p0->_x;
    float dy = _p1->_y - _p0->_y;
    _length = sqrt(dx*dx + dy*dy);

}

Stick::~Stick()
{

    // delete _p0;
    // delete _p1;

}

float Stick::update(sf::RenderWindow *window)
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

}

void Stick::constrain_points(sf::RenderWindow *window)
{

    _p0->constrain(window);
    _p1->constrain(window);

}

void Stick::render_points(sf::RenderWindow *window)
{

    _p0->render(window);
    _p1->render(window);

}

void Stick::render(sf::RenderWindow *window, bool _render_points)
{

    sf::Vertex line[] =
    {
        sf::Vertex(sf::Vector2f(_p0->_x, _p0->_y)),
        sf::Vertex(sf::Vector2f(_p1->_x, _p1->_y))
    };
    window->draw(line,2,sf::Lines);

    if (_render_points)
        render_points(window);

}