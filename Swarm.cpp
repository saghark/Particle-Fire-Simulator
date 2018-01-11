/*
 * Swarm.cpp
 *
 *  Created on: Jan 10, 2018
 *      Author: ksaghari
 */

#include "Swarm.h"

namespace std {

Swarm::Swarm() {
	lastTime = 0;
	particles = new Particle[NUM_PARTICLES];
}

const Particle * const Swarm::getParticles() {
	return particles;
}

void Swarm::update(int timeElapsed) {
	int interval = timeElapsed - lastTime;
	for (int i = 0; i < NUM_PARTICLES; ++i) {
		particles[i].updatePosition(interval);
	}

	lastTime = timeElapsed;
}

Swarm::~Swarm() {
	delete[] particles;
}

} /* namespace std */
