#pragma once
#include <SFML/Graphics.hpp>
#include "IKSystem.hpp"

class LegManager
{

	float _left_leg_x;
    float _left_leg_y;
    float _right_leg_x;
    float _right_leg_y;
    float _grnd_left;
    float _grnd_right;
    bool _moving_left_leg = true;
    bool _walking_left = true;
    float _angle = 0;
    float _stride = 3;
    float _step_height = 15;
    float _step_cycles = 20;
    float _step_time;
    float _base;
    IKSystem _right_leg;
    IKSystem _left_leg;

    Point *_left_knee;
    Point *_right_knee;

public:

	LegManager(float base, Point *left_pelvis, Point *left_knee, Point *left_foot, Point *right_pelvis, Point *right_knee, Point *right_foot);

	void update(bool is_left_pressed, bool is_right_pressed);

    void render(sf::RenderWindow *window);

private:


};