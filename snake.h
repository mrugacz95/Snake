#ifndef SNAKE_H_INCLUDED
#define SNAKE_H_INCLUDED
#include "game.h"
typedef struct POINT{
    int x,
        y;
    int id;
    struct POINT *next,*prev;
}; //poedynczy segment weza listy dwukierunkowej
typedef struct{
    struct POINT * seg; //wskaznik na pierwszy element listy
    int size,
        score;
} SNAKE; //struktura wê¿a

enum DIRECTION {left,right,up,down} dir, lastdir;
SNAKE s;
struct POINT meat;
void addSegment();
void drawMeat();
void drawSnake(struct POINT* P);
#endif // SNAKE_H_INCLUDED
