/*
 * Particle.cpp
 *
 *  Created on: Jan 10, 2018
 *      Author: ksaghari
 */

#include "Particle.h"
#include <stdlib.h>
#include <math.h>

namespace std {

Particle::Particle() {
	init();
}

void Particle::init() {
	xPos = 0;
	yPos = 0;
	direction = (2 * M_PI * rand()) / RAND_MAX;
	velocity = (VELOCITY_SCALER * rand()) / RAND_MAX;
}

void Particle::updatePosition(int interval) {
	direction += interval * DIRECTION_SCALER;
	xPos += velocity * cos(direction) * interval;
	yPos += velocity * sin(direction) * interval;

	if (rand() < RAND_MAX / 100) {
		init();
	}
	if (xPos < -1 || xPos > 1 || yPos < -1 || yPos > 1) {
		init();
	}
}

double Particle::getXPos() {
	return xPos;
}
double Particle::getYPos() {
	return yPos;
}

Particle::~Particle() {
	// TODO Auto-generated destructor stub
}

} /* namespace std */
