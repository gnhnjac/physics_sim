#include <SFML/Graphics.hpp>
#include "Point.hpp"
#include "Stick.hpp"
#include "Rope.hpp"
#include "VerletSolver.hpp"
#include <iostream>

#define SOLVER_ITERS 500

int main()
{
    sf::RenderWindow window(sf::VideoMode(500, 500), "Blame!");

    Point left_foot(230.f,500.f);
    Point right_foot(280.f,500.f);

    Point left_knee(230.f,470.f);
    Point right_knee(280.f,470.f);

    Point left_pelvis(230.f,440.f, true);
    Point right_pelvis(280.f,440.f, true);

    Point left_shoulder(230.f,400.f);
    Point right_shoulder(280.f,400.f);

    Point left_elbow(210.f,400.f);
    Point left_hand(190.f,400.f);

    Point right_elbow(300.f,400.f);
    Point right_hand(320.f,400.f);

    Stick left_leg(&left_foot, &left_knee);
    Stick right_leg(&right_foot, &right_knee);

    Stick left_thigh(&left_knee, &left_pelvis);
    Stick right_thigh(&right_knee, &right_pelvis);

    Stick pelvis(&left_pelvis, &right_pelvis);

    Stick left_abdomen(&left_pelvis, &left_shoulder);
    Stick right_abdomen(&right_pelvis, &right_shoulder);

    Stick top(&left_shoulder, &right_shoulder);

    Stick left_arm1(&left_shoulder, &left_elbow);
    Stick right_arm1(&right_shoulder, &right_elbow);

    Stick left_arm2(&left_elbow, &left_hand);
    Stick right_arm2(&right_elbow, &right_hand);

    Stick chest_stabilizer(&left_shoulder, &right_pelvis);

    Point p0(10.f,250.f,true);
    Point p1(200.f,200.f,true);

    Rope r(&p0,&p1, 0.15);

    Point p2(10.f,100.f,true);
    Point p3(490.f,100.f,true);

    Rope r2(&p2,&p3, 0.15);

    VerletSolver solver(SOLVER_ITERS);

    solver.add_rope(&r);
    solver.add_rope(&r2);

    solver.add_stick(&left_leg);
    solver.add_stick(&right_leg);
    solver.add_stick(&left_thigh);
    solver.add_stick(&right_thigh);
    solver.add_stick(&pelvis);
    solver.add_stick(&left_abdomen);
    solver.add_stick(&right_abdomen);
    solver.add_stick(&top);
    solver.add_stick(&chest_stabilizer);
    solver.add_stick(&left_arm1);
    solver.add_stick(&right_arm1);
    solver.add_stick(&left_arm2);
    solver.add_stick(&right_arm2);

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
                    std::cout << "horray" << std::endl;
                }
            }

        }

        window.clear();
        
        solver.update(&window);
        solver.render(&window);
        left_hand.apply_force(-0.1,0);
        right_hand.apply_force(0.1,0);
        if (p1._x < 400)
            p1._x += 0.1;
        window.display();

    }

    return 0;
}