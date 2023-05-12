#pragma once
#include <SFML/Graphics.hpp>
#include "IKSystem.hpp"
#include "Stick.hpp"

class LegManager
{

public:
	float _left_leg_x;
    float _right_leg_x;
    bool _moving_left_leg = true;
    bool _walking_left = true;
    bool _is_midair = false;
    bool _is_crouching = false;
    float _jump_height = 500;
    float _stride = 40;
    float _crouch_stride = 20;
    float _leg_gap = 10;
    float _cooldown = 0;
    float _cooldown_seconds = 0.2;
    int _grnd_pixels = 8;
    IKSystem _right_leg;
    IKSystem _left_leg;

    Point *_left_knee;
    Point *_right_knee;
    Point *_left_foot;
    Point *_right_foot;
    Point *_left_pelvis;
    Point *_right_pelvis;
    Point *_center_of_mass;

    Stick *_left_thigh;
    Stick *_left_calf;
    Stick *_right_thigh;
    Stick *_right_calf;

	LegManager(Point *center_of_mass, Stick *left_thigh, Stick *left_calf, Stick *right_thigh, Stick *right_calf, Point *left_pelvis, Point *left_knee, Point *left_foot, Point *right_pelvis, Point *right_knee, Point *right_foot);

    LegManager() {};

	void update(bool is_left_pressed, bool is_right_pressed, bool is_up_pressed, bool is_down_pressed, float dt);

    void crouch_left();

    void crouch_right();

    float raycast_to_grnd(float x);

    void render(sf::RenderWindow *window);

private:


};