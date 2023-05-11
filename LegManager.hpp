#pragma once
#include <SFML/Graphics.hpp>
#include "IKSystem.hpp"

class LegManager
{

	float _left_leg_x;
    float _right_leg_x;
    bool _moving_left_leg = true;
    bool _walking_left = true;
    bool _is_jumping = false;
    float _jump_height = 50;
    float _stride = 40;
    float _cooldown = 0;
    float _cooldown_seconds = 0.2;
    IKSystem _right_leg;
    IKSystem _left_leg;

    Point *_left_knee;
    Point *_right_knee;
    Point *_left_foot;
    Point *_right_foot;

public:

	LegManager(Point *left_pelvis, Point *left_knee, Point *left_foot, Point *right_pelvis, Point *right_knee, Point *right_foot);

	void update(bool is_left_pressed, bool is_right_pressed, bool is_up_pressed, float dt);

    float raycast_to_grnd(float x);

    void render(sf::RenderWindow *window);

private:


};