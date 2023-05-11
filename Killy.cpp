#include "Killy.hpp"

Killy::Killy(VerletSolver *solver, uint32_t solver_iters, sf::Clock *clock)
{

	_solver_iters = solver_iters;

	_clock = clock;

	Point *left_shoulder = new Point(245.f,400.f, false, false);
    Point *right_shoulder = new Point(255.f,400.f, false, false);

    Point *left_elbow = new Point(220.f,400.f, false, false);

    Point *right_elbow = new Point(280.f,400.f, false, false);
    Point *right_hand = new Point(305.f,400.f, false, false);

    Point *mid_top = new Point(250.f,400.f, false, false ,false, 0, -1, true);
    Point *head = new Point(250.f,390.f, false, false, false, -1, 5);

    Point *left_pelvis = new Point(245.f,440.f,false,false,false);
    Point *right_pelvis = new Point(255.f,440.f,false,false,false);

    Point *left_knee = new Point(245.f,465.f,false,false,false);
    Point *right_knee = new Point(255.f,465.f,false,false,false);

    Point *left_foot = new Point(245.f,490.f,false,false,false,0,-1,true);
    Point *right_foot = new Point(255.f,490.f,false,false,false,0,-1,true);

    Point *pelvis_bone = new Point(250.f, 430.f, false, true);

    Stick *pelvis_left_bone = new Stick(left_pelvis ,pelvis_bone, -1, true);
    Stick *pelvis_right_bone = new Stick(right_pelvis ,pelvis_bone, -1, true);

    Stick *left_thigh = new Stick(left_knee,left_pelvis, -1, false, 1, M_PI/2);
    Stick *right_thigh = new Stick(right_knee,right_pelvis, -1, false, 1, M_PI/2);

    Stick *left_calf = new Stick(left_foot,left_knee, -1, false, 1, M_PI/2);
    Stick *right_calf = new Stick(right_foot,right_knee, -1, false, 1, M_PI/2);

    Stick *neck = new Stick(mid_top, head, -1, false, 2);

    Stick *left_abdomen = new Stick(left_pelvis, left_shoulder, -1, false, 2);
    Stick *right_abdomen = new Stick(right_pelvis, right_shoulder, -1, false, 2);

    FlexStick *chest_stabilizer = new FlexStick(left_shoulder, right_pelvis, 0.99,1.01,3,true);
    FlexStick *chest_stabilizer2 = new FlexStick(right_shoulder, left_pelvis, 0.99,1.01,3,true);
    Stick *chest_stabilizer3 = new Stick(pelvis_bone, mid_top, -1, true, 2, M_PI/2);

    FlexStick *left_wing = new FlexStick(left_shoulder, head, 0.85,1.15,3,true);
    FlexStick *right_wing = new FlexStick(right_shoulder, head, 0.85,1.15,3,true);

    Stick *bot = new Stick(left_pelvis, right_pelvis, -1, false, 2);

    Stick *left_top = new Stick(left_shoulder, mid_top, -1, false, 2);
    Stick *right_top = new Stick(mid_top, right_shoulder, -1, false, 2);
    Stick *top = new Stick(left_shoulder, right_shoulder, -1, false, 2);

    Point *gun_shoot = new Point(340.f,400.f, false, false, true);

    FlexStick *left_leg_stabilizer = new FlexStick(left_pelvis,left_foot, 0.7,1.3,3,true);
    FlexStick *right_leg_stabilizer = new FlexStick(right_pelvis,right_foot, 0.7,1.3,3,true);

    _solver = solver;

    _solver->add_flex_stick(left_leg_stabilizer);
    _solver->add_flex_stick(right_leg_stabilizer);
    _solver->add_flex_stick(left_wing);
    _solver->add_flex_stick(right_wing);
    _solver->add_stick(left_thigh);
    _solver->add_stick(right_thigh);
    _solver->add_stick(left_calf);
    _solver->add_stick(right_calf);
    _solver->add_stick(bot);
    _solver->add_stick(left_abdomen);
    _solver->add_stick(right_abdomen);
    _solver->add_stick(neck);
    _solver->add_stick(left_top);
    _solver->add_stick(right_top);
    _solver->add_stick(top);
    _solver->add_stick(pelvis_left_bone);
    _solver->add_stick(pelvis_right_bone);
    _solver->add_flex_stick(chest_stabilizer);
    _solver->add_flex_stick(chest_stabilizer2);
    _solver->add_stick(chest_stabilizer3);

    _leg_manager = new LegManager(mid_top,left_pelvis,left_knee,left_foot,right_pelvis,right_knee,right_foot);

    _photon_beam = new PhotonBeam(right_hand,gun_shoot);

    _right_hand_iks = new IKSystem(right_shoulder);
    _right_hand_iks->add_arm(right_elbow,2);
    _right_hand_iks->add_arm(right_hand,2);
    _right_hand_iks->add_arm(gun_shoot,10);

    _left_hand_iks = new IKSystem(left_shoulder);
    _left_hand_iks->add_arm(left_elbow,2);
    Stick right_arm2(right_elbow, right_hand, -1, false, 2);
    _left_hand_iks->add_arm(right_hand,2,right_arm2._length);
    _left_hand_iks->add_arm(gun_shoot,10);

    _center_of_mass	= mid_top;

}

void Killy::update(sf::RenderWindow	*window)
{

	sf::Vector2i position = sf::Mouse::getPosition(*window);
    
    _leg_manager->update(sf::Keyboard::isKeyPressed(sf::Keyboard::Left), sf::Keyboard::isKeyPressed(sf::Keyboard::Right), sf::Keyboard::isKeyPressed(sf::Keyboard::Up), _clock->restart().asSeconds());
    _right_hand_iks->reach(position.x,position.y);
    _left_hand_iks->reach(position.x,position.y);

    if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
        _photon_beam->charge(_center_of_mass);
    }
    else
        _photon_beam->shoot(_center_of_mass);

}

void Killy::render(sf::RenderWindow	*window)
{

    _leg_manager->render(window);
    _photon_beam->render(window);
    _right_hand_iks->render(window);
    _left_hand_iks->render(window);

}