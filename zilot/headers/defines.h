#ifndef DEFINES_H
#define DEFINES_H


#define WIDTH 800
#define HEIGHT 600

typedef int bool;
#define true 1
#define false 0


#define NB_ANIMATION_FRAME 6


// define philosophers value
#define STALLMAN 0
#define PLATO 1
#define TWILIGHT 2 // fuck you, love and friendship is philosphy too, just don't tell /lit/ about this, they'll spam garbage over the dev


//define battlegrounds value
#define HELL 0
#define MATRIX 1
#define EQUESTRIA 2


// define philosopher state
#define STANDING 0
#define MOVING_L 1
#define MOVING_R 2
#define JUMPING 3
#define JUMPING_L 4
#define JUMPING_R 5
#define DOWN 6
#define HIT1 7
#define HIT2 8
#define INJURED 9

#define LEFT 1
#define RIGHT 2


// placeholders ?
#define BACKGROUND_W 2382
#define BACKGROUND_H 1000

#define DEFAULT_P1_POS_X 150
#define DEFAULT_P1_POS_Y 400
#define DEFAULT_P1_WIDTH 100
#define DEFAULT_P1_HEIGHT 150


#define NB_PIXEL_MOVEMENT 3

#endif
