#include <SFML/Graphics.hpp>
#include "Point.hpp"
#include "Stick.hpp"
#include "Rope.hpp"
#include "Arm.hpp"
#include "VerletSolver.hpp"
#include "IKSystem.hpp"
#include "LegManager.hpp"
#include "PhotonBeam.hpp"
#include <iostream>

#define SOLVER_ITERS 100

int main()
{
    sf::RenderWindow window(sf::VideoMode(500, 500), "Blame!");

    window.setFramerateLimit(60);

    Point left_shoulder(245.f,400.f);
    Point right_shoulder(255.f,400.f);

    Point left_elbow(220.f,400.f);
    Point left_hand(195.f,400.f);

    Point right_elbow(280.f,400.f);
    Point right_hand(305.f,400.f);

    Point mid_top(250.f,400.f);
    Point head(250.f,390.f, false, false, false, false, 5);

    Point left_pelvis(245.f,440.f,false,false,true);
    Point right_pelvis(255.f,440.f,false,false,true);

    Point left_knee(245.f,465.f,false,false,true);
    Point right_knee(255.f,465.f,false,false,true);

    Point left_foot(245.f,490.f,false,false,true);
    Point right_foot(255.f,490.f,false,false,true);

    Stick left_thigh(&left_pelvis,&left_knee);
    Stick right_thigh(&right_pelvis,&right_knee);

    Stick left_calf(&left_knee,&left_foot);
    Stick right_calf(&right_knee,&right_foot);

    Stick neck(&mid_top, &head, -1, false, 2);

    Stick left_abdomen(&left_shoulder, &left_pelvis, -1, false, 2);
    Stick right_abdomen(&right_shoulder, &right_pelvis, -1, false, 2);

    Stick chest_stabilizer(&left_shoulder, &right_pelvis, -1, true);
    Stick chest_stabilizer2(&right_shoulder, &left_pelvis, -1, true);

    FlexStick left_wing(&left_shoulder, &head, 0.7,1.3,3);
    left_wing._hidden = true;
    FlexStick right_wing(&right_shoulder, &head, 0.7,1.3,3);
    right_wing._hidden = true;

    Stick bot(&left_pelvis, &right_pelvis, -1, false, 2);

    Stick left_top(&left_shoulder, &mid_top, -1, false, 2);
    Stick right_top(&mid_top, &right_shoulder, -1, false, 2);

    Stick left_arm1(&left_shoulder, &left_elbow, -1, false, 2);
    Stick right_arm1(&right_shoulder, &right_elbow, -1, false, 2);

    Stick right_arm2(&right_elbow, &right_hand, -1, false, 2);
    Stick left_arm2(&left_elbow, &right_hand, right_arm2._length, false, 2);

    Point gun_handle_top(305.f,395.f);
    Point gun_handle_bot(305.f,405.f);
    Point gun_front_top(340.f,395.f, false, false, false, true);
    Point gun_front_bot(340.f,405.f, false, false, false, true);

    Stick gun_handle_bot_part(&gun_handle_bot, &right_hand);
    Stick gun_handle_top_part(&right_hand, &gun_handle_top);
    Stick gun_barrel(&gun_handle_top, &gun_front_top);
    Stick gun_front(&gun_front_top, &gun_front_bot);
    Stick gun_bot(&gun_front_bot, &gun_handle_bot);
    Stick gun_stabilizer(&gun_front_top, &gun_handle_bot, -1, true);
    Stick gun_stabilizer2(&gun_front_bot, &gun_handle_top, -1, true);

    Point anchor(100.f,500.f, true);

    Rope decor_rope(&anchor,&left_shoulder, 0.2);
    Rope decor_rope2(&anchor,&left_pelvis, 0.2);
    Rope decor_rope3(&anchor,&right_shoulder, 0.2);

    VerletSolver solver(SOLVER_ITERS);

    solver.add_flex_stick(&left_wing);
    solver.add_flex_stick(&right_wing);
    solver.add_stick(&left_thigh);
    solver.add_stick(&right_thigh);
    solver.add_stick(&left_calf);
    solver.add_stick(&right_calf);
    solver.add_stick(&bot);
    solver.add_stick(&left_abdomen);
    solver.add_stick(&right_abdomen);
    solver.add_stick(&neck);
    solver.add_stick(&left_top);
    solver.add_stick(&right_top);
    solver.add_stick(&right_arm1);
    solver.add_stick(&right_arm2);
    solver.add_stick(&left_arm1);
    solver.add_stick(&left_arm2);
    solver.add_stick(&gun_barrel);
    solver.add_stick(&gun_front);
    solver.add_stick(&gun_bot);
    solver.add_stick(&gun_stabilizer);
    solver.add_stick(&gun_stabilizer2);
    solver.add_stick(&gun_handle_top_part);
    solver.add_stick(&gun_handle_bot_part);
    solver.add_stick(&chest_stabilizer);
    solver.add_stick(&chest_stabilizer2);
    //solver.add_rope(&decor_rope);
   // solver.add_rope(&decor_rope2);
   // solver.add_rope(&decor_rope3);

    solver.save_to_file("killy.map", &window);

    LegManager leg_manager(500.f, &left_pelvis,&left_knee,&left_foot,&right_pelvis,&right_knee,&right_foot);

    PhotonBeam photon_beam(&gun_handle_top,&gun_front_top);

    Point p0(0.f,0.f);

    // IKSystem iks(&p0);
    // for(int i = 10; i < 250; i+=10)
    //     iks.add_arm(i,i,log10(i));

    Point p1(100.f,100.f, true);
    Point p2(200.f,200.f, true);
    Rope r(&p1,&p2,0.2);
    solver.add_rope(&r);

    while (window.isOpen())
    {

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            if(event.type == sf::Event::KeyPressed)
            {
                if(event.key.code == sf::Keyboard::Q)
                {
                    solver._render_points = !solver._render_points;
                }
            }

        }

        window.clear();

        leg_manager.update(sf::Keyboard::isKeyPressed(sf::Keyboard::Left), sf::Keyboard::isKeyPressed(sf::Keyboard::Right));
        solver.update(&window);

        if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            photon_beam.charge();
        }
        else
            photon_beam.shoot();

        solver.render(&window);
        leg_manager.render(&window);
        photon_beam.render(&window);
        head.apply_force(0,-10);
        window.display();

    }

    return 0;
}