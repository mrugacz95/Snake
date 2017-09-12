#ifndef ALINIT_H_INCLUDED
#define ALINIT_H_INCLUDED
#define DEFAULT_SCREENWIDTH 800
#define DEFAULT_SCREENHEIGHT 400
#define DEFAULT_SNAKE_SIZE 20
#define DEFAULT_POINTS_MULTIPLER 150
//#define SNAKE_SPEED 180
#include <allegro.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "snake.h"
#include "game.h"
void readConf();
void init();
void deinit();
void Handler();
void increment_speed();
unsigned volatile int speed;
BITMAP * buff;
volatile int Close;
int SCREENHEIGHT, //sta³e
    SCREENWIDTH,
    SNAKE_SIZE,
    POINTS_MULTIPLER,
    SNAKE_SPEED;
#endif // ALINIT_H_INCLUDED
