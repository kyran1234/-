#include  "afxres.h"
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include<stdbool.h>
#include<SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "intervalone.h"

SDL_Window *w = NULL;//窗口
SDL_Renderer *r  = NULL;//
SDL_Surface *s=NULL;
SDL_Texture* t=NULL;
int q=0,set=0;



void loading_1(){
                    static int degree=0;
                    s=IMG_Load("19.png");
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
                    //on_timer(5);
                    SDL_Delay(5);
                    degree+=5;
                    SDL_RenderPresent(r);
                    
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

void event_loop_1(){
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
                    s=IMG_Load("22.png");
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
    s=IMG_Load("1.png");
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
    s=IMG_Load("2_1.png");
    t=SDL_CreateTextureFromSurface(r,s);
    SDL_FreeSurface(s);
    SDL_RenderCopy(r,t,NULL,NULL);
     SDL_RenderPresent(r);
     SDL_Delay(3000);
     SDL_SetRenderDrawColor(r,0,0,0,50);
     SDL_RenderClear(r);
     SDL_RenderPresent(r);
     SDL_Delay(90);
    //on_timer(3000);
    SDL_DestroyTexture(t);
    s=IMG_Load("img//3.jpg");
    t=SDL_CreateTextureFromSurface(r,s);
    SDL_FreeSurface(s);
    SDL_RenderCopy(r,t,NULL,NULL);
     SDL_RenderPresent(r);
     SDL_Delay(100);
     SDL_DestroyTexture(t);
     s=IMG_Load("img//3.jpg");
    t=SDL_CreateTextureFromSurface(r,s);
    SDL_FreeSurface(s);
    SDL_RenderCopy(r,t,NULL,NULL);
     SDL_RenderPresent(r);
     SDL_Delay(100);
     SDL_DestroyTexture(t);
     s=IMG_Load("img//4.jpg");
    t=SDL_CreateTextureFromSurface(r,s);
    SDL_FreeSurface(s);
    SDL_RenderCopy(r,t,NULL,NULL);
     SDL_RenderPresent(r);
     SDL_Delay(100);
     SDL_DestroyTexture(t);
     s=IMG_Load("img//5.jpg");
    t=SDL_CreateTextureFromSurface(r,s);
    SDL_FreeSurface(s);
    SDL_RenderCopy(r,t,NULL,NULL);
     SDL_RenderPresent(r);
     SDL_Delay(100);
     SDL_DestroyTexture(t);
     s=IMG_Load("img//6.jpg");
    t=SDL_CreateTextureFromSurface(r,s);
    SDL_FreeSurface(s);
    SDL_RenderCopy(r,t,NULL,NULL);
     SDL_RenderPresent(r);
     SDL_Delay(100);
     SDL_DestroyTexture(t);
     s=IMG_Load("img//7.jpg");
    t=SDL_CreateTextureFromSurface(r,s);
    SDL_FreeSurface(s);
    SDL_RenderCopy(r,t,NULL,NULL);
     SDL_RenderPresent(r);
     SDL_Delay(100);
     SDL_DestroyTexture(t);
     s=IMG_Load("img//8.jpg");
    t=SDL_CreateTextureFromSurface(r,s);
    SDL_FreeSurface(s);
    SDL_RenderCopy(r,t,NULL,NULL);
     SDL_RenderPresent(r);
     SDL_Delay(100);
     SDL_DestroyTexture(t);
     s=IMG_Load("img//9.jpg");
    t=SDL_CreateTextureFromSurface(r,s);
    SDL_FreeSurface(s);
    SDL_RenderCopy(r,t,NULL,NULL);
     SDL_RenderPresent(r);
     SDL_Delay(100);
     SDL_DestroyTexture(t);
     s=IMG_Load("img//10.jpg");
    t=SDL_CreateTextureFromSurface(r,s);
    SDL_FreeSurface(s);
    SDL_RenderCopy(r,t,NULL,NULL);
     SDL_RenderPresent(r);
     SDL_Delay(100);
     SDL_DestroyTexture(t);
     s=IMG_Load("img//11.jpg");
    t=SDL_CreateTextureFromSurface(r,s);
    SDL_FreeSurface(s);
    SDL_RenderCopy(r,t,NULL,NULL);
     SDL_RenderPresent(r);
     SDL_Delay(100);
     SDL_DestroyTexture(t);
     s=IMG_Load("img//12.jpg");
    t=SDL_CreateTextureFromSurface(r,s);
    SDL_FreeSurface(s);
    SDL_RenderCopy(r,t,NULL,NULL);
     SDL_RenderPresent(r);
     SDL_Delay(100);
     SDL_DestroyTexture(t);
     s=IMG_Load("img//13.jpg");
    t=SDL_CreateTextureFromSurface(r,s);
    SDL_FreeSurface(s);
    SDL_RenderCopy(r,t,NULL,NULL);
     SDL_RenderPresent(r);
     SDL_Delay(100);
     SDL_DestroyTexture(t);
     s=IMG_Load("img//14.jpg");
    t=SDL_CreateTextureFromSurface(r,s);
    SDL_FreeSurface(s);
    SDL_RenderCopy(r,t,NULL,NULL);
     SDL_RenderPresent(r);
     SDL_Delay(100);
     SDL_DestroyTexture(t);
     s=IMG_Load("15.png");
    t=SDL_CreateTextureFromSurface(r,s);
    SDL_FreeSurface(s);
    SDL_RenderCopy(r,t,NULL,NULL);
     SDL_RenderPresent(r);
     SDL_Delay(2000);
     SDL_DestroyTexture(t);
     s=IMG_Load("17.png");
    t=SDL_CreateTextureFromSurface(r,s);
    SDL_FreeSurface(s);
    SDL_RenderCopy(r,t,NULL,NULL);
    SDL_RenderPresent(r);
    SDL_Delay(3000);
    SDL_DestroyTexture(t);
    s=IMG_Load("18.png");
    t=SDL_CreateTextureFromSurface(r,s);
    SDL_FreeSurface(s);
    SDL_RenderCopy(r,t,NULL,NULL);
    SDL_RenderPresent(r);
    on_timer(10000);
    SDL_DestroyTexture(t);


    q++;
    }
    if(set==1)
    loading_1();

     
   }
}


int main(int argc,char *argv[]){
    int i=0;
    SDL_Init(SDL_INIT_EVERYTHING);
    create_window(WINDOW_WIDTH,WINDOW_HEIGHT);
    
    event_loop_1();
    
    SDL_DestroyRenderer(r);
    SDL_DestroyTexture(t);
    SDL_DestroyWindow(w);
    
    return 0;
}
