#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<SDL2/SDL.h>
#include<SDL2/SDL_image.h>
#include<time.h>
#include<math.h>
#include<conio.h>

#define WALL 0
#define WAY 1
#define TRAP 2
#define EXIT 3
#define WINDOW_WIDTH 1600
#define WINDOW_HEIGHT 800
#define N 16

struct Node
{
	int data;
	int flag;
};
 
struct Path
{
	int xpath;
	int ypath;
	int pox;    //在队列中的下标 
};

void createmap(int **map_way,int x,int y);
void map_make(int **map_way);
void map_draw(int **map_way) ; 
void init_player_2();
int create_window(int width,int height);
void event_loop_3(int** map_way);
void init_path_1(SDL_Rect* PATH_2,int** map_way);
void init_map_1(SDL_Rect* map);
void trap_make(int **map_way);
