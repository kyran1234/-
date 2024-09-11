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

void createmap(int **map_way,int x,int y);
void map_make(int **map_way);
void map_draw(int **map_way); 
void init_player_3();
int create_window(int width,int height);
void event_loop_5(int** map_way);


