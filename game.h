#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED
#include <allegro.h>
#include "alinit.h"
enum STATE {GSPLAY,GSMENU,GSGAMEOVER,GSEXIT,GSPAUSE} state;
enum MENUSTATE {MSPLAY,MSOPTIONS, MSAUTHOR,MSEXIT} mstate;
enum OSTATE {OSSPEED,OSEXIT} ostate;
char * scoreToStr(int num);
enum STATE moveSnake();
int pause();
int collisions, godMod;
#endif // GAME_H_INCLUDED
