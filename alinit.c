#include "alinit.h"
int nameToInt(char *name){
    char tab[4][50]={ "SCREENWIDTH","SCREENHEIGHT","SNAKESIZE","POINTSMULTIPLER"};
    int i=0,j=0,p=0;
    while(1){
      if(tab[i][j]=='\0' || name[j]=='\0') { break; }
      if(tab[i][j]!=name[j]){ i++; j=0;}
      if(i>=4){ p=1; break; }
        j++;
    }
    if(p) return 0;
    return i;


}
int pow(int a,int b){
    int i,w=1;
    for(i=0;i<b;i++){
        w*=a;
    }
    return w;
}
int strToInt(char * val){
    int i=0,j,v=0;
    while(val[i++]!='\0');
    i--;
    for(j=0;j<i;j++){

        v+=(val[j]-'0')*pow(10,i-j-1);

    }
    return v;
}
void readConf(){

    FILE *f = fopen("conf", "r");

    if(!f){
            printf("Can't open conf file :c");
            return;
    }
    char name[50],
         val[50],
         c;
    int i,v;
    do{
        i=0;
        while((c=fgetc(f)) != '=' && c!=EOF){
            name[i++]=c;
        }
        name[i]='\0';
        printf("%s = ",name);
        i=0;
        while((c=fgetc(f)) != '\n' && c != EOF){
            val[i++]=c;
        }
        val[i]='\0';
        printf(" %s \n",val);
        v=strToInt(val);
        printf("val %d\n",v);
        switch(nameToInt(name)){
            case 0: SCREENWIDTH=v; break;
            case 1: SCREENHEIGHT=v; break;
            case 2: SNAKE_SIZE=v; break;
            case 3: POINTS_MULTIPLER=v; break;
        }
    }while(c != EOF);
    SCREENWIDTH=SCREENWIDTH*SNAKE_SIZE;
    SCREENHEIGHT=SCREENHEIGHT*SNAKE_SIZE;
    if(!SCREENHEIGHT) SCREENHEIGHT = DEFAULT_SCREENHEIGHT;
    if(!SCREENWIDTH) SCREENWIDTH =DEFAULT_SCREENWIDTH;
    if(!SNAKE_SIZE) SNAKE_SIZE=DEFAULT_SNAKE_SIZE;
    if(!POINTS_MULTIPLER) POINTS_MULTIPLER=DEFAULT_POINTS_MULTIPLER;

    return;
}
void init(){
    allegro_init();
    SNAKE_SPEED=180;
    install_int_ex( increment_speed,  MSEC_TO_TIMER( SNAKE_SPEED ) );
    install_keyboard();
    set_color_depth(32);
    set_gfx_mode(GFX_AUTODETECT_WINDOWED, SCREENWIDTH, SCREENHEIGHT, 0,0);
    LOCK_FUNCTION(Handler);
    set_close_button_callback(Handler);
    buff=create_bitmap(SCREENWIDTH,SCREENHEIGHT);
    srand(time(NULL));
    state=GSMENU;
    mstate=MSPLAY;
    Close=0;
    return;
}
void Handler(){
    Close=1;
    return;
}
void deinit(){
	destroy_bitmap(buff);
    allegro_exit();
    return;
}
void increment_speed()
{
    speed++;
}

END_OF_FUNCTION( increment_speed );
LOCK_VARIABLE( speed );
LOCK_FUNCTION( increment_speed );
