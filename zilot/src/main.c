/*******************************************************************************
    This free software was brought to you by /lit/ and /g/

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*******************************************************************************/


#include <stdio.h>
#include <stdlib.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "../headers/fight.h"


int main(int argc, char **argv)
{

	if(SDL_Init(SDL_INIT_VIDEO) <0) {
		fprintf(stderr, "Couldn't init SDL : %s\n", SDL_GetError());
		exit(EXIT_FAILURE);
	}

	SDL_Window *window;
	SDL_Renderer *renderer;
	

	// create the window for the program
	window = SDL_CreateWindow("Philosopunch", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, 0);
	// we check if it failed
	if(window == NULL) {
		fprintf(stderr, "Error while creating the window : %s\n", SDL_GetError());
		exit(EXIT_FAILURE);
	}

	// create the render, where we will draw stuff to display.
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	//renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	// check if it failed 
	if(renderer == NULL) {
		fprintf(stderr, "Error while creating the renderer : %s\n", SDL_GetError());
		exit(EXIT_FAILURE);
	}
	//SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF );




    	SDL_Event event;
	int run = 1; // code to know what to do in the menu
	while(run){ 
		if(SDL_WaitEvent(&event)) {
			// alt+f4 or close
			if(event.type == SDL_QUIT) {
				run=0;
			}
		}


		run = fight(TWILIGHT, TWILIGHT, HELL, renderer);

		//game code goes here
		
	}


	// quit the SDL
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
	return 0;
}
