#include "../headers/character.h"




void load_philosopher(int philosopher, Player *p, SDL_Renderer *renderer)
{
	SDL_Surface *surface;
	FILE *clipsData;
	
	switch(philosopher) {
		case STALLMAN :
			strcat(p->philosopher_name, "RMS");
			surface = SDL_LoadBMP("./character/rms.bmp");
			break;
		case PLATO :
			strcat(p->philosopher_name, "PLATO");
			surface = SDL_LoadBMP("./character/plato.bmp");
			
			break;
		case TWILIGHT :
			//strcat(p->philosopher_name, "TWILIGHT");
			surface = SDL_LoadBMP("./character/test.bmp");
			clipsData = fopen("./character/test.spr", "r");
			break;
		default :
			break;
	}
	if(clipsData == NULL) {
		fprintf(stderr, "Error while opening the file character/test.bmp\n");
		exit(EXIT_FAILURE);
	}
	if(surface == NULL) {
		fprintf(stderr, "Error while loading p1 : %s\n", SDL_GetError()); 
		exit(EXIT_FAILURE);
	}
	//remove background of the sprites
	SDL_SetColorKey( surface, SDL_TRUE, SDL_MapRGB( surface->format, 0, 40, 99 ) );

	p->spritesheet = SDL_CreateTextureFromSurface(renderer, surface);
	

	if(p->spritesheet == NULL) {
		fprintf(stderr, "Error while creating the texture of p1 : %s\n", SDL_GetError());
		exit(EXIT_FAILURE);
	}
	SDL_FreeSurface(surface);

	int i;
	bool data = true;
	int movement;
	while(data) {
		if(fscanf(clipsData, "%d", &movement) == 1) {
			fscanf(clipsData, "%d", &(p->nb_sprites[movement]));
			for(i=0 ; i<(p->nb_sprites[movement]) ; i++) {
				fscanf(clipsData, "%d", &(p->spritesheet_clips[movement][i].x));
				fscanf(clipsData, "%d", &(p->spritesheet_clips[movement][i].y));
				fscanf(clipsData, "%d", &(p->spritesheet_clips[movement][i].h));
				fscanf(clipsData, "%d", &(p->spritesheet_clips[movement][i].w));
			}
		}
		else {
			data = false;
		}

	}
	fclose(clipsData);
	//create spriteclips
	/*
	for(i=0 ; i<NB_ANIMATION_FRAME; i++) {
		p->spritesheet_clips[0][i].x = i * (300 / NB_ANIMATION_FRAME);
		p->spritesheet_clips[0][i].y = 0;
		p->spritesheet_clips[0][i].w = 300 / NB_ANIMATION_FRAME;
		p->spritesheet_clips[0][i].h = 118;
	}
	*/

	p->life = 100;
	p->current_state = STANDING;
	p->can_move = true;
	p->current_frame = 10;
	p->action_frame = 6;

	p->events.move_right = false;
	p->events.move_left = false;
	p->events.move_jump = false;
	p->events.move_down = false;
	p->events.hit_1 = false;
	p->events.hit_2 = false;

	p->position = malloc(sizeof *(p->position)); 

	p->position->x = DEFAULT_P1_POS_X;
	p->position->y = DEFAULT_P1_POS_Y;
	p->position->w = 300/ NB_ANIMATION_FRAME;
	p->position->h = 118;


	p->current_clip = &(p->spritesheet_clips[0][0]);
}





void update_texture(Player *p) 
{
	// do both left and right animation later.

	// action_frame : should define how many frame per animation so you can have it 'dynamic'
	// /10 : basically the number of frame a picture stay. Put it in a define. 
	// should stay the same so some animation will be longer cause of more sprites to animate ?
	// also, some won't be able to stop and will stope alone once last frame is reached (hit, jump...)
	switch(p->current_state) {
		case STANDING :
			p->current_frame++;
			if(p->current_frame/10 >= p->nb_sprites[STANDING]){
				p->current_frame = 0;
			}
			p->current_clip = &(p->spritesheet_clips[STANDING][(p->current_frame)/10]);
			break;
		case MOVING_L :
			p->current_frame++;
			if(p->current_frame/10 >= p->nb_sprites[MOVING_L]){
				p->current_frame = 0;
			}
			p->current_clip = &(p->spritesheet_clips[MOVING_L][(p->current_frame)/10]);
			break;
		case MOVING_R :
			p->current_frame++;
			if(p->current_frame/10 >= p->nb_sprites[MOVING_R]){
				p->current_frame = 0;
			}
			p->current_clip = &(p->spritesheet_clips[MOVING_R][(p->current_frame)/10]);
			break;
		case JUMPING :
			p->current_frame++;
			if(p->current_frame/10 >= p->nb_sprites[JUMPING]){
				p->current_frame = 0;
				p->current_state = STANDING;
				p->can_move=true;
			}
			p->current_clip = &(p->spritesheet_clips[JUMPING][(p->current_frame)/10]);
			break;
		case JUMPING_L :
			p->current_frame++;
			if(p->current_frame/10 >= p->nb_sprites[JUMPING_L]){
				p->current_frame = 0;
				p->current_state = STANDING;
				p->can_move=true;
			}
			p->current_clip = &(p->spritesheet_clips[JUMPING_L][(p->current_frame)/10]);
			break;
		case JUMPING_R :
			p->current_frame++;
			if(p->current_frame/10 >= p->nb_sprites[JUMPING_R]){
				p->current_frame = 0;
				p->current_state = STANDING;
				p->can_move=true;
			}
			p->current_clip = &(p->spritesheet_clips[JUMPING_R][(p->current_frame)/10]);
			break;
		case DOWN :
			p->current_frame++;
			if(p->current_frame/10 >= p->action_frame){
				p->current_frame = 0;
			}
			p->current_clip = &(p->spritesheet_clips[0][(p->current_frame)/10]);
			break;
		case HIT1 :
			p->current_frame++;
			if(p->current_frame/10 >= p->action_frame){
				p->current_frame = 0;
				p->current_state = STANDING;
				p->can_move=true;
			}
			p->current_clip = &(p->spritesheet_clips[0][(p->current_frame)/10]);
			break;
		case HIT2 :
			p->current_frame++;
			if(p->current_frame/10 >= p->action_frame){
				p->current_frame = 0;
				p->current_state = STANDING;
				p->can_move=true;
			}
			p->current_clip = &(p->spritesheet_clips[0][(p->current_frame)/10]);
			break;
		default :
			break;


	}

}



void play_actions(Player *p)
{
	switch(p->current_state) {
		case STANDING :
			break;
		case MOVING_L :
			p->position->x-=NB_PIXEL_MOVEMENT;
			break;
		case MOVING_R :
			p->position->x+=NB_PIXEL_MOVEMENT;
			break;
		case JUMPING :
			if(p->current_frame < p->nb_sprites[JUMPING]*10/2)
				p->position->y-=NB_PIXEL_MOVEMENT;
			else
				p->position->y+=NB_PIXEL_MOVEMENT;
			break;
		case JUMPING_L :
			if(p->current_frame < p->nb_sprites[JUMPING_L]/2) {
				p->position->y-=NB_PIXEL_MOVEMENT;
				p->position->x-=NB_PIXEL_MOVEMENT;
			}
			else {
				p->position->y+=NB_PIXEL_MOVEMENT;
				p->position->x-=NB_PIXEL_MOVEMENT;
			}
			break;
		case JUMPING_R :
			if(p->current_frame < p->nb_sprites[JUMPING_R]*10/2) {
				p->position->y-=NB_PIXEL_MOVEMENT;
				p->position->x+=NB_PIXEL_MOVEMENT;
			}
			else {
				p->position->y+=NB_PIXEL_MOVEMENT;
				p->position->x+=NB_PIXEL_MOVEMENT;
			}
			break;
		case HIT1 :
			break;
		case HIT2 :
			break;
		case INJURED :
			break;
		default :
			break;
	}
}
