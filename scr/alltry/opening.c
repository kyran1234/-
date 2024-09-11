#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <windows.h>
#include<SDL2/SDL_image.h>
#include "opening.h"

SDL_Window *w = NULL;//窗口
SDL_Renderer *r  = NULL;//
SDL_Surface* s=NULL;
SDL_Texture* t=NULL;

//SDL_Rect MAP[49];
SDL_Rect player;
SDL_Rect PATH[49];//让显示为零的坐标变白//数值不确定，不行换栈
int maze[nn][nn];
bool begin;
int man_x=0,man_y=1;
SDL_Rect map;
 



void way_8(){
	
	maze[1][1]=8;
	maze[2][1]=8;
	maze[3][1]=8;
	maze[4][1]=8;
	maze[5][1]=8;
	maze[5][2]=8;
	maze[5][3]=8;
	maze[5][4]=8;
	maze[5][5]=8;
	maze[5][6]=8;
	
}

void init_path_0(SDL_Rect* path){
    int i,j;
    for(i=0;i<7;i++){
        for(j=0;j<7;j++){
            if(maze[i][j]==FALSE){
                (path+i+7*j)->w=49;
                (path+i+7*j)->h=49;
                (path+i+7*j)->x=i*50;
                (path+i+7*j)->y=j*50;
            }


        }
    }

}

void move(){
	int i;
	
	if(maze[man_y][man_x+1]==8){
		for(i=0;i<50;){
			player.y+=5;
			s=IMG_Load("26.png");
    		t=SDL_CreateTextureFromSurface(r,s);
    		SDL_FreeSurface(s);
    		SDL_RenderCopy(r,t,NULL,&player);
    		SDL_RenderPresent(r);
    		SDL_DestroyTexture(t);
			SDL_Delay(100);
			i+=5;
			
		}
		maze[man_y][man_x+1]=7;
		man_x++;
	  

	}
	else if(man_x-1>=0&&maze[man_y][man_x-1]==8){
		for(i=0;i<50;){
			player.y-=5;
			s=IMG_Load("26.png");
    		t=SDL_CreateTextureFromSurface(r,s);
    		SDL_FreeSurface(s);
    		SDL_RenderCopy(r,t,NULL,&player);
    		SDL_RenderPresent(r);
    		SDL_DestroyTexture(t);
			SDL_Delay(100);
			i+=5;
			
		}
		maze[man_y][man_x-1]=7;
		man_x--;


		
	}
	else if(maze[man_y+1][man_x]==8){
		for(i=0;i<50;){
			player.x+=5;
			s=IMG_Load("26.png");
    		t=SDL_CreateTextureFromSurface(r,s);
    		SDL_FreeSurface(s);
    		SDL_RenderCopy(r,t,NULL,&player);
    		SDL_RenderPresent(r);
    		SDL_DestroyTexture(t);
			SDL_Delay(100);
			i+=5;
			
		}
		maze[man_y+1][man_x]=7;
		man_y++;
	}

	else if(maze[man_y-1][man_x]==8){
		for(i=0;i<50;){
			player.x-=5;
			s=IMG_Load("26.png");
    		t=SDL_CreateTextureFromSurface(r,s);
    		SDL_FreeSurface(s);
    		SDL_RenderCopy(r,t,NULL,&player);
    		SDL_RenderPresent(r);
    		SDL_DestroyTexture(t);
			SDL_Delay(100);
	
			i+=5;
			
		}
		maze[man_y-1][man_x]=7;
		man_y--;
	}
	if(maze[5][5]==7){
		exit(0);
	}
	
}





void init_player_1(int x,int y){
	player.x=y*50+10;
	player.y=x*50+10;
	player.w=30;
	player.h=30;

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

void event_loop_0(){
    bool isRunning=true;//C语言的stdbool正常运行
    while(isRunning){

    SDL_Event msg;
    printf("按\n");
    if(SDL_PollEvent(&msg)!=0){
        SDL_KeyCode INPUT = msg.key.keysym.sym;//获取消息成功
		
         switch(msg.type){
            case SDL_QUIT:
               isRunning=false;//退出了整个while循环
               break;//按叉关闭
           /* case SDL_KEYDOWN:
                if(INPUT==SDLK_SPACE){
                    if(begin);
                    else begin=true;
                     
            
                }
*/
         
         
    }
	static bool one=0;
	if(one==0){
	s=IMG_Load("45.jpg");
    t=SDL_CreateTextureFromSurface(r,s);
    SDL_FreeSurface(s);
    SDL_RenderCopy(r,t,NULL,NULL);
    SDL_RenderPresent(r);
    SDL_DestroyTexture(t);
	SDL_Delay(3000);
	one++;
	}
	s=IMG_Load("44.png");
    t=SDL_CreateTextureFromSurface(r,s);
    SDL_FreeSurface(s);
    SDL_RenderCopy(r,t,NULL,&map);
    SDL_RenderPresent(r);
    SDL_DestroyTexture(t);
   
    

    
    if(one==1){
        SDL_SetRenderDrawColor(r,255,255,255,255);
        SDL_RenderFillRects(r,PATH,49);
        SDL_RenderPresent(r);
		way_8();
		

    
	s=IMG_Load("26.png");
    t=SDL_CreateTextureFromSurface(r,s);
    SDL_FreeSurface(s);
    SDL_RenderCopy(r,t,NULL,&player);
    SDL_RenderPresent(r);
    SDL_DestroyTexture(t);
	one++;
	}
	move();
	SDL_RenderPresent(r);
    
  
    }
}
}
  


int main(int argc,char *argv[])
{
    SDL_Init(SDL_INIT_EVERYTHING);
    create_window(WINDOW_WIDTH,WINDOW_HEIGHT);
	map.h=7*50;
	map.w=7*50;
	map.x=0;
	map.y=0;

	int i,j;
    int index;
	//int man_x=0,man_y=1;
    srand(time(0));
    index=(rand()%4)+1;
	int Init_Stack(SqStack *);     
	int Push(SqStack *,SElemType);         
	int Pop(SqStack *,SElemType *);  
	void DFSmaze(Point [],int [][nn],int [][k]) ; 
	
	//int maze[n][n]; //maze[7][7]
	int smaze[k][k]; //smaze[3][3]
	Point r[(k)*(k)];   //结构体数组 r[9]
	
	for(i=0;i<nn;i++)
		for(j=0;j<nn;j++)
		{
			maze[i][j] = b;//b=1
		}
	for(i=1;i<nn-1;i=i+2)
		for(j=1;j<nn-1;j=j+2)
		{
			maze[i][j] = a;//a=0
		}
	maze[1][0]=maze[nn-2][nn-1]=a;	//n=7
	
	for(i=0;i<k;i++)
		for(j=0;j<k;j++)
		{
			smaze[i][j] = FALSE;  //0 
		} 
	
	
	
	
	for(i=0;i<k*k;i++)   //结构体数组赋初值 
	{
		r[i].x = i/k;
		r[i].y = i%k;
	}
	

	for(i=0;i<k;i++)     //smaze数组赋值 
		for(j=0;j<k;j++)
			smaze[i][j] = FALSE;


	smaze[0][0] = TURE;  //初始节点 
	
	DFSmaze(r,maze,smaze);
    init_path_0(PATH);
	init_player_1(man_x,man_y);
	event_loop_0();
	/*for(i=0;i<n;i++)     //打印生成迷宫 
	{	
		for(j=0;j<n;j++)
		{
			printf("%d ",maze[i][j]);
		}
		printf("\n");
	}*/
	
	
	
    
    //SDL_DestroyRenderer(r);
    SDL_DestroyWindow(w);
    
    //退出image库
    //IMG_Quit();
    //退出SDL
    SDL_Quit();
    return 0;

}



int Init_Stack(SqStack *t)     //初始栈 
{
	t->base = (SElemType *)malloc(IN_MAXSIZE*sizeof(SElemType));
	if(!(t->base))
		return 0;
	t->top = t->base;
	t->stacksize = IN_MAXSIZE;//100
	return 1;   
}

int Push(SqStack *t,SElemType e)   //入栈 
{
	if(t->top-t->base>=t->stacksize)    //>=判断
	{
		t->base = (SElemType *)realloc(t->base,(t->stacksize+INCREASE)*sizeof(SElemType));
		if(!t->base)
			return 0;
		t->top = t->base + t->stacksize;	
		t->stacksize += INCREASE; //10
	}
	*(t->top++) = e;
	return 1;  
} 

int Pop(SqStack *t,SElemType *e)     //出栈 
{

	if(t->top==t->base)
		return 0;
	*e = *(--t->top);
	return 1;
}

void DFSmaze(Point r[N],int maze[nn][nn],int smaze[k][k])          //深度优先算法 
{
	SElemType e;		     //结构体变量e
	SqStack s; 
	if(Init_Stack(&s)==1)      //初始栈 
		printf("OK\n"); 
	else
		printf("Fail\n");      
	Push(&s,r[0]);  //压栈r[0]
	while(Pop(&s,&e))  //栈不空时，进行循环 
	{
		if(e.x-1>=0 && smaze[e.x-1][e.y]!=TURE)  //上 
		{
			smaze[e.x-1][e.y] = TURE;
			maze[2*e.x][2*e.y+1] = a; 			//打墙 
			Push(&s,r[(e.x-1)*k+e.y]);	
		} 
		if(e.y+1<k  && smaze[e.x][e.y+1]!=TURE) //右 
		{
			smaze[e.x][e.y+1] = TURE;      //1
			maze[2*e.x+1][2*(e.y+1)] = a;    
			Push(&s,r[(e.x)*k+e.y+1]);	
		}
		if(e.x+1<k && smaze[e.x+1][e.y]!=TURE)  //下 
		{
			smaze[e.x+1][e.y] = TURE;
			maze[2*(e.x+1)][2*e.y+1] = a; //0
			Push(&s,r[(e.x+1)*k+e.y]);	
		}
		if(e.y-1>=0 && smaze[e.x][e.y-1]!=TURE)   //左 
		{
			smaze[e.x][e.y-1] = TURE;
			maze[2*e.x+1][2*e.y] = a;
			Push(&s,r[(e.x)*k+e.y-1]);	
		}
	} 
} 



 



