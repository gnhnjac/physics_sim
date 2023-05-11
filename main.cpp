#include <SFML/Graphics.hpp>
#include "Point.hpp"
#include "Stick.hpp"
#include "Rope.hpp"
#include "Arm.hpp"
#include "VerletSolver.hpp"
#include "IKSystem.hpp"
#include "LegManager.hpp"
#include "PhotonBeam.hpp"
#include "Killy.hpp"
#include <iostream>
#include <tgmath.h>

#define SOLVER_ITERS 100

int main()
{
    sf::RenderWindow window(sf::VideoMode(500, 500), "Game");

    window.setFramerateLimit(60);

    VerletSolver solver(SOLVER_ITERS);

    sf::Clock clock;

    Killy killy(&solver, SOLVER_ITERS, &clock);

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

        killy.update(&window);
        solver.update(&window);
        solver.render(&window);
        killy.render(&window);
        
        window.display();

    }

    return 0;
}