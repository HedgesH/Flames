//graphics.h
//uses display.c from sketch assignment with some updates
#include <stdio.h>
#include <time.h>
#include <SDL2/SDL.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <SDL2/SDL_ttf.h>
#define SDL_MAIN_HANDLED

//SDL_Window *window;
//SDL_Renderer *renderer;

typedef struct {
    SDL_Window *window;
    SDL_Renderer *renderer;
} display;

//input array of points, join the dots
void line(display *d, int x0, int y0, int x1, int y1);

//draws a circle
void circle(display *d, int x, int y, int r);

void clear(display *d);

static void fail();

static int I(int n);

static void *P(void *p);

void point(display *d, float x, float y );

void colour(display *d, int i, int pixel_size, int height);

void show(display *d);

display *newDisplay(char *title, int width, int height);

void pause(display *d, int ms);

void end(display *d);
