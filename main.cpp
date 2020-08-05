#include <stdlib.h>
#include <vector>
#include <string>

#include <string>
#include <sstream>
#include <fstream>
#include <iostream>

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

int
	wd = 800,
	ht = 600;

std::vector<SDL_Texture*> tex;
std::vector<SDL_Rect> rect;

std::vector<std::string> rd(std::string name) {
	std::ifstream f(name);
	std::string l;

	std::vector<std::string> word;

	while (std::getline(f, l)) {
		word.push_back(l);
	}

	return word;
}

void getTxtAndRect(SDL_Renderer* rend, int x, int y, char* txt, TTF_Font* font, SDL_Texture** tex, SDL_Rect* rect) {
	int
		wd,
		ht;

	SDL_Surface* surface;
	SDL_Color txtCol = {255, 255, 255, 0};

	surface = TTF_RenderText_Solid(font, txt, txtCol);
	*tex = SDL_CreateTextureFromSurface(rend, surface);

	wd = surface->w;
	ht = surface->h;

	SDL_FreeSurface(surface);

	rect->x = x;
	rect->y = y;
	rect->w = wd;
	rect->h = ht;
}

int main() {
	SDL_Renderer* rend;

	for (int i = 0; i < 3; i++) {
		SDL_Texture* tmpTex;
		tex.push_back(tmpTex);

		SDL_Rect tmpRect;
		rect.push_back(tmpRect);
	}

	// window
	SDL_Window* win;

	char* name = "terminus.bdf";

	SDL_Init(SDL_INIT_TIMER | SDL_INIT_VIDEO);
	SDL_CreateWindowAndRenderer(wd, ht, 0, &win, &rend);

	// text
	TTF_Init();
	TTF_Font* font = TTF_OpenFont(name, 24);

	std::vector<std::string> word = rd("intro");
	for (int i = 0; i < word.size(); i++) {
		getTxtAndRect(rend, 0, i * 32, (char*) word[i].c_str(), font, &tex[i], &rect[i]);
	}

	SDL_SetRenderDrawColor(rend, 0, 0, 0, 0);

	int open = true;
	SDL_Event e;
	while (open) {
		while (SDL_PollEvent(&e)) {
			if (e.type == SDL_QUIT) {
				open = false;
			}
		}

		SDL_RenderClear(rend);

		for (int i = 0; i < word.size(); i++) {
			SDL_RenderCopy(rend, tex[i], NULL, &rect[i]);
		}

		SDL_RenderPresent(rend);
	}

	return 0;
}
