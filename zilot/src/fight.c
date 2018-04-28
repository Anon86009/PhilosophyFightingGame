#include "../headers/fight.h"


int fight(int p1, int p2, int battleground, SDL_Renderer *renderer)
{
	/** here I just want to get the shit done, so I don't bother creating a good function
	 * I'll clean the code later, one day. Like next month or so
	 * (expect never)
	 */

	
//we load the background into a SDL_Surface
	SDL_Surface *background = SDL_LoadBMP("background/test.bmp");
	if(background == NULL) {
		fprintf(stderr, "Error while loading the background : %s\n", SDL_GetError()); 
		exit(EXIT_FAILURE);
	}

//once the sprite sheet is loaded, we put it in a texture. 
	SDL_Texture *background_texture = SDL_CreateTextureFromSurface(renderer, background);
	if(background_texture == NULL) {
		fprintf(stderr, "Error while creating the texture of the background : %s\n", SDL_GetError());
		exit(EXIT_FAILURE);
	}
//we can free the surface
	SDL_FreeSurface(background);



	Player player1;

	load_philosopher(p1, &player1, renderer);


	SDL_Rect background_position, camera;
	background_position.x = 0;
	background_position.y = 0;
	background_position.w = WIDTH;
	background_position.h = HEIGHT;

	camera.x = 0;
	camera.y = 400;
	camera.w = WIDTH;
	camera.h = HEIGHT;

    	SDL_Event event;
	char run = 1; // boolean to know if he wants to quit or if game is over
	Uint32 start=0;
	Uint32 currentTime=0;
	int compteur=0;
	while(run){ 
		// get user input (wrap it in a function or some shit)
		if(SDL_PollEvent(&event)) {
			// alt+f4 or close
			if(event.type == SDL_QUIT) {
				run=0;
			}
		// !!!! const Uint8* keystates = SDL_GetKeyboardState(NULL); should be used instead (faster)
		// see SO : https://stackoverflow.com/questions/29373203/sdl-2-0-key-repeat-and-delay#29382114
			if(event.type == SDL_KEYDOWN) {
                		switch(event.key.keysym.sym){ //if space, we quit the program.
                    			case SDLK_ESCAPE :
						run=0;
						break;
					case SDLK_s :
						if(player1.can_move){
							player1.events.move_down = true;
							player1.current_state = DOWN;
							player1.can_move=false;
						}
						break;
					case SDLK_q :
						if(player1.can_move){
							player1.events.move_left = true;
							player1.current_state = MOVING_L;
							player1.can_move=true;
						}
						break;
					case SDLK_d:
						if(player1.can_move){
							player1.events.move_right = true;
							player1.current_state = MOVING_R;
							player1.can_move=true;
						}
						break;
					case SDLK_SPACE :
						if(player1.can_move){
							player1.events.move_jump = true;
							player1.can_move=false;
							player1.current_frame = 0;
							if(player1.current_state == MOVING_L)
								player1.current_state = JUMPING_L;
							else if(player1.current_state == MOVING_R)
								player1.current_state = JUMPING_R;
							else
								player1.current_state = JUMPING;
						}
						break;
					case SDLK_a:
						if(player1.can_move){
							player1.events.hit_1= true;
							player1.current_state = HIT1;
							player1.can_move=false;
							player1.current_frame = 0;
						}
						break;
					case SDLK_z:
						if(player1.can_move){
							player1.events.hit_2= true;
							player1.current_state = HIT2;
							player1.can_move=false;
							player1.current_frame = 0;
						}
						break;
					default :
						break;
				}
			}
			if(event.type == SDL_KEYUP) {
                		switch(event.key.keysym.sym){ //if space, we quit the program.
					case SDLK_SPACE :
						player1.events.move_jump = false;
						break;
					case SDLK_s :
						if(player1.current_state == DOWN) {
							player1.events.move_down = false;
							player1.current_state = STANDING;
							player1.can_move = true;
						}
						break;
					case SDLK_q :
						if(player1.current_state == MOVING_L) {
							player1.events.move_left = false;
							player1.current_state = STANDING;
						}
						break;
					case SDLK_d:
						if(player1.current_state == MOVING_R) {
							player1.events.move_right = false;
							player1.current_state = STANDING;
						}
						break;
					case SDLK_a:
						player1.events.hit_1= false;
						break;
					case SDLK_z:
						player1.events.hit_2= false;
						break;
					default :
						break;
				}
			}
		}
		

		// do AI shit here
		// play the actions of both players
		play_actions(&player1);

		// check if there's anyone hitting or some shit
		// nota bene : I completely forgot about possible projectiles. I'm a dumb fuck
		// set camera and shit



		// update textures and shit
		update_texture(&player1);

		SDL_RenderClear(renderer);
		SDL_RenderCopy(renderer, background_texture, &camera, &background_position);
		SDL_RenderCopy(renderer, player1.spritesheet , player1.current_clip, player1.position);
		SDL_RenderPresent(renderer);



		SDL_Delay(10);
		currentTime = SDL_GetTicks();
		if(currentTime - start > 1000) {
			start = SDL_GetTicks();
			//printf("FRAME RATE : %dfps\n", compteur);
			compteur = 0;
		}
		compteur++;
	}




	SDL_DestroyTexture(background_texture);
	return run;
}
