/*
 * Particle.h
 *
 *  Created on: Jan 10, 2018
 *      Author: ksaghari
 */

#ifndef PARTICLE_H_
#define PARTICLE_H_

namespace std {

class Particle {
private:
	const double VELOCITY_SCALER = 0.00025;
	const double DIRECTION_SCALER = 0.00015;

private:
	double xPos, yPos, direction, velocity;

private:
	void init();

public:
	Particle();
	void updatePosition(int interval);
	double getXPos(), getYPos();
	virtual ~Particle();
};

} /* namespace std */

#endif /* PARTICLE_H_ */
