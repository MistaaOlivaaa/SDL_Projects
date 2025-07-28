#ifndef BOUNCY_BALL_H
#define BOUNCY_BALL_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <math.h>

#define WIDTH 800
#define HEIGHT 600
#define GRAVITY 0.5f
#define BOUNCE_DAMPING 0.8f
#define FRICTION 0.99f
#define FPS 60
#define FRAME_DELAY (1000 / FPS)


typedef struct {
    float x;
    float y;
    int radius;
    float v_x;
    float v_y;
} Circle;

void DrawFilledCircle(SDL_Surface *surface, Circle circle, Uint32 color);
void UpdateBall(Circle *circle);

#endif 

