#include "alinit.h"
int main() {
    readConf();
    init();
    int i,wait,snakeSpeed=0,val,opt;
    char* strScore;
    while (state!=GSEXIT) {
        switch(state){
            case GSMENU:
                while(state==GSMENU){
                    clear_to_color(buff,makecol(0,0,0));
                    textout_ex(buff, font,"SNAKE", SCREENWIDTH/2-60, SCREENHEIGHT/2-40, makecol(255, 255, 255), -1);
                    textout_ex(buff, font,(mstate==MSPLAY)? "> NEW GAME": "NEW GAME", SCREENWIDTH/2-60, SCREENHEIGHT/2, makecol(255, 255, 255), -1);
                    textout_ex(buff, font, (mstate==MSOPTIONS)? "> OPTIONS" : "OPTIONS", SCREENWIDTH/2-60, SCREENHEIGHT/2+20, makecol(255, 255, 255), -1);
                    textout_ex(buff, font, (mstate==MSAUTHOR)? "> AUTHOR" : "AUTHOR", SCREENWIDTH/2-60, SCREENHEIGHT/2+40, makecol(255, 255, 255), -1);
                     textout_ex(buff, font, (mstate==MSEXIT)? "> EXIT" : "EXIT", SCREENWIDTH/2-60, SCREENHEIGHT/2+60, makecol(255, 255, 255), -1);
                    blit(buff,screen,0,0,0,0,buff->w,buff->h);
                    val=readkey();
                    switch(val>>8){
                        case KEY_DOWN:
                            mstate++;
                            if(mstate>MSEXIT) mstate=MSPLAY;
                            break;
                        case KEY_UP:
                            if(mstate==MSPLAY){ mstate=MSEXIT;}
                            else mstate--;
                            break;
                        case KEY_ENTER:
                            switch(mstate){
                                case MSPLAY:
                                    state=GSPLAY;
                                break;
                                case MSOPTIONS:
                                    opt=1; ostate=OSSPEED;
                                    while(opt){
                                        clear_to_color(buff,makecol(0,0,0));
                                        textout_ex(buff, font, (ostate==OSSPEED)? "< SNAKE SPEED >" : "SNAKE SPEED", SCREENWIDTH/2-60, SCREENHEIGHT/2+20, makecol(255, 255, 255), -1);
                                        char * sspeed = IntToStr(SNAKE_SPEED);
                                        textout_ex(buff, font, sspeed, SCREENWIDTH/2+70, SCREENHEIGHT/2+20, makecol(255, 255, 255), -1);
                                        free(sspeed);
                                        textout_ex(buff, font, (ostate==OSEXIT)? "> EXIT" : "EXIT", SCREENWIDTH/2-60, SCREENHEIGHT/2+60, makecol(255, 255, 255), -1);
                                        blit(buff,screen,0,0,0,0,buff->w,buff->h);
                                        val=readkey();
                                        switch(val>>8){
                                            case KEY_ENTER:
                                                switch(ostate){
                                                    case OSEXIT:
                                                        opt=0;
                                                        break;
                                                }
                                                break;

                                            case KEY_DOWN:
                                                ostate++;
                                                if(ostate>OSEXIT) ostate=OSSPEED;
                                                break;
                                            case KEY_UP:
                                                if(ostate==OSSPEED){ ostate=OSEXIT;}
                                                else ostate--;
                                                break;
                                            case KEY_RIGHT:
                                                if(ostate==OSSPEED)
                                                    SNAKE_SPEED+=10;
                                                install_int_ex( increment_speed,  MSEC_TO_TIMER( SNAKE_SPEED ) );

                                            break;
                                            case KEY_LEFT:
                                                if(ostate==OSSPEED)
                                                    SNAKE_SPEED-=10;
                                                if(SNAKE_SPEED<10) SNAKE_SPEED=10;
                                                install_int_ex( increment_speed,  MSEC_TO_TIMER( SNAKE_SPEED ) );
                                            break;
                                            case KEY_ESC:
                                                opt=0;
                                            break;
                                        }

                                        if(Close){ state=GSEXIT; break;}
                                    }
                                    break;
                                case MSAUTHOR:
                                    clear_to_color(buff,makecol(0,0,0));
                                    textout_ex(buff, font, "AUTHOR: MARCIN MRUGAS", SCREENWIDTH/2-60, SCREENHEIGHT/2, makecol(255, 255, 255), -1);
                                    blit(buff,screen,0,0,0,0,buff->w,buff->h);
                                    readkey();
                                break;
                                case MSEXIT:
                                    state=GSEXIT;
                                break;
                            }
                            break;
                        case KEY_ESC:
                            state=GSEXIT;
                            break;

                    }

                if(Close){ state=GSEXIT; break;}
                }
                break;
            case GSPLAY:
                newGame();
                while (state==GSPLAY) {
                    if((state=moveSnake()) == GSGAMEOVER){ break; }
                    if(s.seg->x==meat.x && s.seg->y==meat.y){
                            s.score++;
                            printf("Score: %d\n",s.score*POINTS_MULTIPLER);
                            addSegment();
                            randomizeMeat();
                    }
                    clear_to_color(buff,makecol(0,0,0));
                    drawSnake(s.seg);
                    drawMeat();
                    strScore=IntToStr(s.score*POINTS_MULTIPLER);
                    textout_ex(buff, font, "Score:", SCREENWIDTH-100, 10, makecol(255, 255, 255), -1);
                    textout_ex(buff, font, strScore, SCREENWIDTH-45, 10, makecol(255, 255, 255), -1);
                    free(strScore);
                    blit(buff,screen,0,0,0,0,buff->w,buff->h);
                    speed=0;
                    while(speed<1){
                        if((key[ KEY_A ] || key[KEY_LEFT]) && lastdir!=right) dir=left;
                        else if((key[ KEY_D ] || key[KEY_RIGHT]) && lastdir!=left) dir=right;
                        else if((key[ KEY_W ] || key[KEY_UP]) && lastdir!=down) dir=up;
                        else if((key[ KEY_S ] || key[KEY_DOWN]) && lastdir!=up) dir=down;
                        else if(key[KEY_ESC] || key[KEY_P]){ state=GSPAUSE; break; }
                    }
                    speed--;
                    if(state==GSPAUSE){ state=pause(); clear_keybuf(); rest(100); }
                    if(Close) break;
                }
                destroySnake();
                break;
            case GSGAMEOVER:
                clear_keybuf();
                destroySnake();
                state=gameover();
                break;

        }
    }
    clear_to_color(screen,makecol(0,0,0));
    textout_ex(screen, font, "Thanks for playing :>", SCREENWIDTH/2-60, SCREENHEIGHT/2, makecol(255, 255, 255), -1);
    textout_ex(screen, font, "VER 1.2", SCREENWIDTH/2-15, SCREENHEIGHT/2+30, makecol(255, 255, 255), -1);
    textout_ex(screen, font, "AUTHOR: MARCIN MRUGAS", SCREENWIDTH/2-60, SCREENHEIGHT/2+40, makecol(255, 255, 255), -1);
    //rest(1800);
    deinit();
	return 0;
}
END_OF_MAIN();
