#include <SDL2/SDL.h>
#include <stdbool.h>

typedef struct {
	unsigned int _x;
	unsigned int _y;
} Coord;

typedef struct {
	unsigned int _r;
	unsigned int _g;
	unsigned int _b;
	unsigned int _a;
} Col;

const unsigned int res[2] = {
	100,
	100
};

enum {
	X,
	Y
};

uint32_t rmask = 0xff000000;
uint32_t gmask = 0x00ff0000;
uint32_t bmask = 0x0000ff00;
uint32_t amask = 0x000000ff;

int prime(int n) {
	for (int i = 2; i <= n / 2; i++) {
		if (!(n % i)) {
			return false;
		}
	}

	return true;
}

int blitPix(unsigned char data[res[Y]][res[X]][3 + 1], Coord st, Col col) {
	if (!(st._x <= res[X] && st._y <= res[Y])) {
		printf("Error\n");

		return 1;
	}

	data[st._y][st._x][0] = col._r;
	data[st._y][st._x][1] = col._g;
	data[st._y][st._x][2] = col._b;
	data[st._y][st._x][3] = col._a;

	return 0;
}

int main() {
	SDL_Window* win = SDL_CreateWindow("asdf", 0, 0, res[X], res[Y], 0);
	SDL_Renderer* rend = SDL_CreateRenderer(win, -1, 0);

	SDL_Texture* tex = SDL_CreateTexture(rend, SDL_PIXELFORMAT_RGB888, SDL_TEXTUREACCESS_TARGET, res[X], res[Y]);

	SDL_Rect rect = {
		0,
		0,
		res[X],
		res[Y]
	};

	// clear
	unsigned char data[res[Y]][res[X]][3 + 1];
	for (int y = 0; y < res[Y]; y++) {
		for (int x = 0; x < res[X]; x++) {
			data[y][x][0] = 0;
			data[y][x][1] = 0;
			data[y][x][2] = 0;
			data[y][x][3] = 255;
		}
	}

	Col red = {
		255,
		0,
		0,
		255
	};

	for (int y = 0; y < res[1]; y++) {
		for (int x = 0; x < res[0]; x++) {
			Coord st = {
				x,
				y
			};

			if (prime((y * res[0]) + x)) {
				if (blitPix(data, st, red)) {
					printf("Error\n");
				}
			}
		}
	}

	SDL_Surface* surf = SDL_CreateRGBSurfaceFrom(data, res[X], res[Y], (3 + 1) * 8, (3 + 1) * res[X], rmask, gmask, bmask, amask);

	SDL_UpdateTexture(tex, &rect, surf->pixels, surf->pitch);

	bool open = true;
	SDL_Event e;
	while (open) {
		while (SDL_PollEvent(&e)) {
			if (e.type == SDL_QUIT) {
				open = false;
			}
		}

		SDL_RenderDrawRect(rend, &rect);

		SDL_RenderCopy(rend, tex, NULL, NULL);
		SDL_RenderPresent(rend);
	}

	return 0;
}
