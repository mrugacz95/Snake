#include "snake.h"
enum STATE moveSnake(){
    struct POINT tmp=*s.seg;
    switch(dir){
        case up:
            tmp.y-=SNAKE_SIZE;
            break;
        case down:
            tmp.y+=SNAKE_SIZE;
            break;
        case right:
            tmp.x+=SNAKE_SIZE;
            break;
        case left:
            tmp.x-=SNAKE_SIZE;
            break;
    }
    tmp.x%=SCREENWIDTH;
    tmp.y%=SCREENHEIGHT;
    if(tmp.x<0) tmp.x=SCREENWIDTH-SNAKE_SIZE;
    if(tmp.y<0) tmp.y=SCREENHEIGHT-SNAKE_SIZE;
    int i;
    if(collision(tmp.x,tmp.y)) return GSGAMEOVER;
    lastdir=dir;
    s.seg=s.seg->prev;
    s.seg->x=tmp.x;
    s.seg->y=tmp.y;
    return GSPLAY;
}
void drawSnake(struct POINT* P){
        struct POINT * tmp=s.seg;
         rect(buff,P->x,P->y,P->x+SNAKE_SIZE,P->y+SNAKE_SIZE,makecol(0,255,0));
         if(P->next!=s.seg)drawSnake(P->next);
    return;

}
void destroySnake(){
    struct POINT * tmp = s.seg;
    int i;
    while(tmp->next != tmp){
        tmp->prev=tmp->next;
        tmp->next=tmp->next->next;
        free(tmp->prev);
    }
        free(tmp);
}
void delTail(){
    s.seg->prev=s.seg->prev->prev;
    printf("deell %d %d\n",s.seg->prev->next->x,s.seg->prev->next->y);
    free(s.seg->prev->next);
    s.seg->prev->next=s.seg;
}
void randomizeMeat(){
    do{
        meat.x=rand()%(SCREENWIDTH/SNAKE_SIZE)*SNAKE_SIZE;
        meat.y=rand()%(SCREENHEIGHT/SNAKE_SIZE)*SNAKE_SIZE;

    }while(collision(meat.x,meat.y));
}
void drawMeat(){
    rectfill(buff,meat.x,meat.y,meat.x+SNAKE_SIZE,meat.y+SNAKE_SIZE,makecol(0,255,0));
}
void addSegment(){
    struct POINT * t;
    if(t=malloc(sizeof(struct POINT))){

        t->prev=s.seg->prev;
        t->next=s.seg;
        s.seg->prev=t;
        t->prev->next=t;
        t->x=s.seg->x;
        t->y=s.seg->y;
        s.seg=t;
        t->id=s.size++;
    }
    else printf("Cant allocate segment\n");
    return;
}
int collision(int x, int y){
    if(!collisions){
        struct POINT * tmp2=s.seg;
        while((tmp2=tmp2->next) != s.seg)
            if(tmp2->x==x && tmp2->y==y) return 1;
    }
    return 0;
}
