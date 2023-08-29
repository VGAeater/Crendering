#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <chrono>

using namespace std;

int x = 0;
int z = 0;

// declare width
int y = 0;
int width;
int height;

SDL_Event e;
const Uint8* keyState = SDL_GetKeyboardState(nullptr);
auto prevTime = chrono::high_resolution_clock::now();

float running = true;

void handleEvents() {
	while (SDL_PollEvent(&e)) {
		if (e.type == SDL_QUIT) {
			running = false;
			break;
		}
	}
}

int main(int argc, char* argv[]) {
	// set width and height
	width = 511;//stoi(argv[1]);
	height = 511;//stoi(argv[2]);

	SDL_Window* window = nullptr;
	SDL_Renderer* renderer = nullptr;

	SDL_Init(SDL_INIT_VIDEO);
	SDL_CreateWindowAndRenderer(width, height, 0, &window, &renderer);
	//SDL_RenderSetScale(renderer, resolution, resolution);

	//SDL_SetRelativeMouseMode(SDL_TRUE);

	while (running) {
		handleEvents();

		x = 0;
		while (x < 256) {
			y = 0;
			while (y < 256) {
				SDL_SetRenderDrawColor(renderer, x, y, z, 255);
				SDL_RenderDrawPoint(renderer, x+z, y+z);
				y++;
			}
			x++;
		}
		SDL_RenderPresent(renderer);
		z++;
		if (z > 255) {
			z = 0;
		}
		cout << "\r" << 1000/chrono::duration<double, milli>(chrono::high_resolution_clock::now() - prevTime).count();
		prevTime = chrono::high_resolution_clock::now();
	}

	cout << endl;
	return 0;
}
