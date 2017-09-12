#include "game.h"
void newGame(){
    godMod=collisions=0;
    dir=lastdir=left;
    struct POINT* tmp;
    s.seg=malloc(sizeof(struct POINT));
    if(s.seg){
    s.seg->x=SCREENWIDTH/SNAKE_SIZE/2*SNAKE_SIZE;
    s.seg->y=SCREENHEIGHT/SNAKE_SIZE/2*SNAKE_SIZE;
    s.seg->prev=s.seg;
    s.seg->next= s.seg;
    s.score=0;
    s.seg->id=0;
    s.seg->next->id=1;
    s.size=2;
    addSegment();
    addSegment();
    addSegment();
    addSegment();
    }
    else return;
    randomizeMeat();
}

int pause(){
    textout_ex(screen, font, "PAUSE", 10, 10, makecol(255, 255, 255), -1);
    textout_ex(screen, font, "AUTHOR: MARCIN MRUGAS", 10, 40, makecol(255, 255, 255), -1);
    textout_ex(screen, font, "PRESS P TO RESUME", 10, 50, makecol(255, 255, 255), -1);
    textout_ex(screen, font, "PRESS ESC TO EXIT", 10, 60, makecol(255, 255, 255), -1);
    clear_keybuf();
    rest(200);
    while(1){
        if(key[KEY_P]) break;
        else if(key[KEY_ESC]) return GSMENU;
        if(Close) return GSEXIT;
        rest(1);
    }
    rest(200);
    if(Close) return GSEXIT;
    blit(buff,screen,0,0,0,0,buff->w,buff->h);
    return GSPLAY;
}
enum STATE gameover(){
    rest(200);
    textout_ex(buff, font, "PRESS ESC TO EXIT", SCREENWIDTH/2-80, SCREENHEIGHT/2+30, makecol(255, 255, 255), -1);
    textout_ex(buff, font, "PRESS ANY KEY TO RESTART", SCREENWIDTH/2-100, SCREENHEIGHT/2+50, makecol(255, 255, 255), -1);
    blit(buff,screen,0,0,0,0,buff->w,buff->h);
    textout_ex(screen, font, "GAME OVER", SCREENWIDTH/2-40, SCREENHEIGHT/2, makecol(255, 255, 255), -1);
    rest(400);
    int frame=0,val;
    clear_keybuf();
    while (!keypressed()) {

        if(Close) return GSEXIT;
        if(frame==1) textout_ex(screen, font, "GAME OVER", SCREENWIDTH/2-40, SCREENHEIGHT/2, makecol(255, 255, 255), -1);
        else if(frame==500) blit(buff,screen,0,0,0,0,buff->w,buff->h);
        else if(frame>=1000) frame=0;
        frame++;
        rest(1);
    }
    val=readkey();
    if((val>>8)==KEY_ESC) return GSMENU;
    if((val>>8)==KEY_A){ rest(500); return GSPLAY; }
    if(godMod) return GSPLAY;
    destroySnake();
    newGame();
    return GSPLAY;

}
char * IntToStr(int num){
    char* str;
    int b=num, len=0;
    if(num==0) len=1;
    while(b){ b/=10; len++; }
    len++;
    char * strNum = malloc((len)*sizeof(char));
    int i;
    for(i=len-2;i>=0;i--){
        strNum[i]=(char)(num%10+48);
        num/=10;
    }
    strNum[len-1]='\0';
    return strNum;
    char *strScroe;
    str=malloc((len+2)*sizeof(char));
    strcat(str,strNum);
    str[len+1]='\0';
    free(strNum);
    return str;
}
