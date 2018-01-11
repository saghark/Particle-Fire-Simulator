/*
 * Screen.h
 *
 *  Created on: Jan 10, 2018
 *      Author: ksaghari
 */

#ifndef SCREEN_H_
#define SCREEN_H_

#include "SDL.h"
#include <stdio.h>
#include <stdlib.h>
#include <iostream>

using namespace std;

class Screen {
private:
	const static int DEFAULT_SCREEN_COLOR = 0x00000000;
	SDL_Window * window;
	SDL_Renderer * renderer;
	SDL_Texture * texture;
	Uint32 * displayBuffer1, * displayBuffer2;
	bool printErrorMessageAndClose(string msg);

public:
	const static int SCREEN_WIDTH = 1024;
	const static int SCREEN_HEIGHT = 720;
	Screen();
	virtual ~Screen();
	bool init();
	bool processEvents();
	void setPixel(int x, int y, Uint8 r, Uint8 b, Uint8 g);
	void boxBlur();
	void clearScreen();
	void update();
	void close();

};

#endif /* SCREEN_H_ */
