//============================================================================
// Name        : Particle.cpp
// Author      : Koosha Saghari
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "Screen.h"
#include "Swarm.h"
using namespace std;

int main() {
	srand(time(NULL));

	Screen myScreen = Screen();
	if (!myScreen.init()) {
		printf("Something went wrong with screen initialization.");
		return 1;
	}

	Swarm swarm;
	int timeElapsed;
	unsigned char r, g, b;
	const Particle * const ptrParticles = swarm.getParticles();

	while (true) {
		timeElapsed = SDL_GetTicks();
		swarm.update(timeElapsed);

		r = (unsigned char) ((1 + sin(timeElapsed * 0.0000008)) * 127);
		g = (unsigned char) ((1 + cos(timeElapsed * 0.0009)) * 127);
		b = (unsigned char) ((1 + sin(timeElapsed * 0.0009)) * 127);

		for (int i = 0; i < Swarm::NUM_PARTICLES; ++i) {
			Particle particle = ptrParticles[i];
			int xPosScaled = (particle.getXPos() + 1) * Screen::SCREEN_WIDTH
					/ 2;
			int yPosScaled = Screen::SCREEN_HEIGHT / 2
					+ particle.getYPos() * Screen::SCREEN_WIDTH / 2;
			myScreen.setPixel(xPosScaled, yPosScaled, r, g, b);
		}

		myScreen.boxBlur();
		myScreen.update();

		if (myScreen.processEvents() == false) {
			myScreen.close();
			break;
		}

	}

	return 0;
}
