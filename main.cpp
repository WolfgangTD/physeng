#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include "headers/Circle.h"

int main(int argc, char* argv[]){
	SDL_Window* window = NULL;
	SDL_Renderer* renderer = NULL;

	int result = SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS);
	if (result < 0) {
		SDL_Log("SDL_INIT error: %s", SDL_GetError());
		return -1;
	}

	window = SDL_CreateWindow("test", 640, 640, 0);
	if (window == NULL){
		SDL_Log("SDL_CreateWindow error: %s", SDL_GetError());
		return -2;
	}

	renderer = SDL_CreateRenderer(window, NULL);
	if (renderer == NULL){
		SDL_Log("SDL_CreateRenderer error: %s", SDL_GetError());
		return -3;
	}

	SDL_Event event;
	int quit = 0;
	while(!quit){
		while(SDL_PollEvent(&event)){
			switch(event.type){
				case SDL_EVENT_QUIT:
					SDL_Log("SDL Event Quit");
					quit = 1;
					break;
				case SDL_EVENT_KEY_DOWN:
					if (event.key.key == SDLK_ESCAPE){
						SDL_Log("SDL Event Quit");
						quit = 1;
						
					}
			}
		}
		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0);
		SDL_RenderClear(renderer);

		Circle ball;
		ball.point = {300, 300, 0};
		ball.radius = 100;
		SDL_SetRenderDrawColor(renderer, 0, 0, 255, 0);
		drawCircle(renderer, ball);
		
		Circle smallBall;
		smallBall.point = {300, 300, 0};
		smallBall.radius = 25;
		SDL_SetRenderDrawColor(renderer, 255, 0, 0, 0);
		drawCircleFilled(renderer, smallBall);

		SDL_FRect platform;
		platform.x = 10;
		platform.y = 500;
		platform.w = 600;
		platform.h = 10;
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
		SDL_RenderFillRect(renderer, &platform);
		

		SDL_RenderPresent(renderer);
	}

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
	return 0;
}