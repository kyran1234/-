#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <windows.h>
#include <SDL2/SDL_image.h>
#define IN_MAXSIZE 100
#define INCREASE 10
#define SElemType Point 
#define FALSE 0   
#define TURE 1

#define nn 7  //迷宫大小
#define k 3  // K = n/2
#define N 9 // N = K*K
#define a 0     //a表示路 
#define b 1	    //b表示墙

#define WINDOW_WIDTH 1600
#define WINDOW_HEIGHT 800

typedef struct 
{
	int x;    //行坐标 
	int y;	  //列坐标 
}Point;

typedef struct
{
	SElemType *base;
	SElemType *top;
	int stacksize;
}SqStack;




void way_8();
void init_path_0(SDL_Rect* path);
void move();
void init_player_1(int x,int y);
int create_window(int width,int height);
void event_loop_0();
int Init_Stack(SqStack *t);    //初始栈 
int Push(SqStack *t,SElemType e);
int Pop(SqStack *t,SElemType *e);
void DFSmaze(Point r[N],int maze[nn][nn],int smaze[k][k]);
