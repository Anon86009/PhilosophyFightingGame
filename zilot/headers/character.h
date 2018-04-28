#ifndef CHARACTER_H
#define CHARACTER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "defines.h"

typedef struct Input_Events Input_Events;
struct Input_Events {

    bool move_right;
    bool move_left;
    bool move_jump;
    bool move_down;
    
    bool hit_1;
    bool hit_2;
 
    // todo : determine all possible actions 
};


typedef struct Player Player;
struct Player{

	Input_Events events;	

	char philosopher_name[64];
	int life;
	int current_state; //ie : moving, jumping, hit_1, hit_2, injured...
	bool can_move;
	
	
	SDL_Rect *position;
	int nb_sprites[64];
	SDL_Rect spritesheet_clips[64][NB_ANIMATION_FRAME]; // I'm gonna code six animation for now. I'll add more later
	SDL_Rect *current_clip;
	SDL_Texture *spritesheet;

	int current_frame;
	int action_frame;

};

void load_philosopher(int philosopher, Player *p, SDL_Renderer *renderer);
void update_texture(Player *p);
void play_actions(Player *p);


#endif
