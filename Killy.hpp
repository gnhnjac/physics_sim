#pragma once
#include "VerletSolver.hpp"
#include "LegManager.hpp"
#include "PhotonBeam.hpp"
#include "IKSystem.hpp"

class Killy
{

public:

	VerletSolver *_solver;
	LegManager *_leg_manager;
	PhotonBeam *_photon_beam;
	IKSystem *_right_hand_iks;
	IKSystem *_left_hand_iks;

	Point *_center_of_mass;

	uint32_t _solver_iters;

	sf::Clock *_clock;

	Killy(VerletSolver *solver, uint32_t solver_iters, sf::Clock *clock);

	void update(sf::RenderWindow *window);

	void render(sf::RenderWindow *window);

private:

};