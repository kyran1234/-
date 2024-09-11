#include  "afxres.h"
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include<stdbool.h>
#include<SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "intervaltwo.h"

SDL_Window *w = NULL;//窗口
SDL_Renderer *r  = NULL;//
SDL_Surface *s=NULL;


SDL_Texture* t=NULL;
int q=0,set=0;



void loading_2(){
                    static int degree=0;
                    s=IMG_Load("21.png");
                    int w=s->w;
                    int h=s->h;
                    SDL_Rect dstrect;
                    dstrect.x=100;
                    dstrect.y=600;
                    dstrect.w=w;
                    dstrect.h=h;
                    t=SDL_CreateTextureFromSurface(r,s);
                    SDL_FreeSurface(s);
                    for(degree=0;degree<720;){
                    SDL_RenderCopyEx(r,t,NULL,&dstrect,degree,NULL,SDL_FLIP_NONE);
                    SDL_Delay(10);
                    SDL_RenderPresent(r);
                    degree+=10;
                    }
                    exit(0);
}

bool on_timer(int duration){
    static int start=0;
    if(start==0){
        start=clock();
    }
    int end=clock();
    if(end-start>=duration){
        start=end;
        return true;
    }
    return false;
}






int create_window(int width,int height){
   w=SDL_CreateWindow(u8"打怪兽",100,100,width,height,SDL_WINDOW_SHOWN);
   if(!w)
   {
      fprintf(stderr,"cant create sdl windows,err is %s ",SDL_GetError);
      return -1;

   }
   r=SDL_CreateRenderer(w,-1,SDL_RENDERER_SOFTWARE);
   if(!r)
   {
      fprintf(stderr,"cant create sdl windows,err is %s ",SDL_GetError);
      return -1;

   }
  
}

void event_loop_4(){
   bool isRunning=true;//C语言的stdbool正常运行

   while(isRunning){
    SDL_Event msg;
    if(SDL_PollEvent(&msg)!=0){//获取消息成功
      SDL_KeyCode INPUT = msg.key.keysym.sym;
         switch(msg.type){
            case SDL_QUIT:
               isRunning=false;//退出了整个while循环
               break;//按叉关闭
            case SDL_KEYDOWN:
                if(INPUT==SDLK_SPACE){
                    s=IMG_Load("43.png");
                    t=SDL_CreateTextureFromSurface(r,s);
                    SDL_FreeSurface(s);
                    SDL_RenderCopy(r,t,NULL,NULL);
                    SDL_RenderPresent(r);
                    on_timer(5000);
                    SDL_DestroyTexture(t);
                    set=1;
                }
                break;

         }
    }
    if(q==0){
    s=IMG_Load("36.png");
    t=SDL_CreateTextureFromSurface(r,s);
    SDL_FreeSurface(s);
    SDL_RenderCopy(r,t,NULL,NULL);
     SDL_RenderPresent(r);
    SDL_Delay(3000);
    SDL_SetRenderDrawColor(r,255,255,255,50);
     SDL_RenderClear(r);
     SDL_RenderPresent(r);
     on_timer(1000);
    SDL_DestroyTexture(t);
    s=IMG_Load("37.png");
    t=SDL_CreateTextureFromSurface(r,s);
    SDL_FreeSurface(s);
    SDL_RenderCopy(r,t,NULL,NULL);
     SDL_RenderPresent(r);
     on_timer(3000);
    
    q++;
    }
    if(set==1)
    loading_2();

     
   }
}


int main(int argc,char *argv[]){
    int i=0;
    SDL_Init(SDL_INIT_EVERYTHING);
    create_window(WINDOW_WIDTH,WINDOW_HEIGHT);
    
    event_loop_4();
    
    SDL_DestroyRenderer(r);
    SDL_DestroyTexture(t);
    SDL_DestroyWindow(w);
    
    return 0;
}
