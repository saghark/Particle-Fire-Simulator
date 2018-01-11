/*
 * Swarm.h
 *
 *  Created on: Jan 10, 2018
 *      Author: ksaghari
 */

#ifndef SWARM_H_
#define SWARM_H_

#include "Particle.h"

namespace std {

class Swarm {
private:
	int lastTime;
	Particle * particles;
public:
	const static int NUM_PARTICLES = 2000;
	Swarm();
	const Particle * const getParticles();
	void update(int timeElapsed);
	virtual ~Swarm();
};

} /* namespace std */

#endif /* SWARM_H_ */
