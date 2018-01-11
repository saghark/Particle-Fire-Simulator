/*
 * Screen.cpp
 *
 *  Created on: Jan 10, 2018
 *      Author: ksaghari
 */

#include "Screen.h"

Screen::Screen() :
		window(NULL), renderer(NULL), texture(NULL), displayBuffer1(NULL), displayBuffer2(
		NULL) {

}

Screen::~Screen() {

}

bool Screen::printErrorMessageAndClose(string msg) {
	SDL_Quit();
	cout << msg << "\t" << SDL_GetError() << endl;
	return false;
}

bool Screen::init() {
	//	Check SDL Initialization and print results.
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		return printErrorMessageAndClose("SDL Initialization Failed.");
	}
	printf("SDL Initialization Success.\n");

	//	Initialize the window.
	window = SDL_CreateWindow("Particle Fire Explosion",
	SDL_WINDOWPOS_CENTERED,
	SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	if (window == NULL) {
		return printErrorMessageAndClose("Window Initialization Failed.");
	}
	printf("Window Initialization Success. \n");

	// Initialize Renderer
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC);
	if (renderer == NULL) {
		return printErrorMessageAndClose("Could not initialize renderer.");
	}

	// Initialize Texture
	texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888,
			SDL_TEXTUREACCESS_STATIC, SCREEN_WIDTH, SCREEN_HEIGHT);
	if (texture == NULL) {
		return printErrorMessageAndClose("Texture Initialization Failed.");
	}
	printf("Texture Initialization Success. \n");
	displayBuffer1 = new Uint32[SCREEN_HEIGHT * SCREEN_WIDTH];
	displayBuffer2 = new Uint32[SCREEN_HEIGHT * SCREEN_WIDTH];
	memset(displayBuffer1, DEFAULT_SCREEN_COLOR,
			SCREEN_HEIGHT * SCREEN_WIDTH * sizeof(Uint32));
	memset(displayBuffer2, DEFAULT_SCREEN_COLOR,
			SCREEN_HEIGHT * SCREEN_WIDTH * sizeof(Uint32));
	return true;
}

void Screen::update() {
	SDL_UpdateTexture(texture,
	NULL, displayBuffer1, SCREEN_WIDTH * sizeof(Uint32));
	SDL_RenderClear(renderer);
	SDL_RenderCopy(renderer, texture, NULL, NULL);
	SDL_RenderPresent(renderer);
}

void Screen::clearScreen() {
	memset(displayBuffer1, DEFAULT_SCREEN_COLOR,
			SCREEN_HEIGHT * SCREEN_WIDTH * sizeof(Uint32));
	memset(displayBuffer2, DEFAULT_SCREEN_COLOR,
			SCREEN_HEIGHT * SCREEN_WIDTH * sizeof(Uint32));
}

void Screen::boxBlur() {
	Uint32 * tempPtr = displayBuffer1;
	displayBuffer1 = displayBuffer2;
	displayBuffer2 = tempPtr;

	for (int y = 0; y < SCREEN_HEIGHT; ++y) {
		for (int x = 0; x < SCREEN_WIDTH; ++x) {
			int totalRed = 0;
			int totalBlu = 0;
			int totalGrn = 0;
			for (int localRow = -1; localRow <= 1; ++localRow) {
				for (int localCol = -1; localCol <= 1; ++localCol) {
					int currentPixelX = x + localCol;
					int currentPixelY = y + localRow;
					if (currentPixelX >= 0 && currentPixelX < SCREEN_WIDTH
							&& currentPixelY >= 0
							&& currentPixelY < SCREEN_HEIGHT) {
						Uint32 color = displayBuffer2[currentPixelY
								* SCREEN_WIDTH + currentPixelX];
						Uint8 red = color >> 24;
						Uint8 blu = color >> 16;
						Uint8 grn = color >> 8;
						totalRed += red;
						totalBlu += blu;
						totalGrn += grn;
					}
				}
			} /* End inner */
			Uint8 red = totalRed / 9;
			Uint8 blu = totalBlu / 9;
			Uint8 grn = totalGrn / 9;
			setPixel(x, y, red, blu, grn);
		}
	} /* End Outer */
}

void Screen::setPixel(int x, int y, Uint8 r, Uint8 b, Uint8 g) {
	if (x < 0 || x >= SCREEN_WIDTH || y < 0 || y >= SCREEN_HEIGHT)
		return;

	Uint32 color = 0;
	color += r;
	color <<= 8;
	color += b;
	color <<= 8;
	color += g;
	color <<= 8;
	color += 0xFF;

	displayBuffer1[(y * SCREEN_WIDTH) + x] = color;
}

bool Screen::processEvents() {
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		if (event.type == SDL_QUIT) {
			return false;
		}
	}
	return true;
}

void Screen::close() {
	printf("Closing...");
	delete[] displayBuffer1;
	delete[] displayBuffer2;
	SDL_DestroyTexture(texture);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
	printf("Closed.");
}

