#include<stdio.h>
#include<Windows.h>
#include<time.h>
#include<math.h>
#include<conio.h>
#include<SDL2/SDL.h>
#include<stdlib.h>
#include<stdbool.h>
#include<SDL2/SDL_image.h>

#define WALL 0
#define WAY 1
#define TRAP 2
#define EXIT 3
#define WINDOW_WIDTH 1600
#define WINDOW_HEIGHT 800
#define NUM 4

typedef struct NODE{
    SDL_Rect mon;
    struct NODE *next;   
}LNODE,*LINKLIST;

void createmap(int **map_way,int x,int y);
void map_make(int **map_way);
void map_draw(int **map_way); 
void color(const unsigned short Color);
//int move(int **map_way);

void zhuangqiang();
int create_window(int width,int height);
void event_loop_7(int** map_way);
void init_path_3(SDL_Rect* path,int** map_way);
void init_map(SDL_Rect* map);
void drawmon(LINKLIST L);
void createmon(SDL_Rect* mon,int* map_way[]);
void linklist_init(LINKLIST* L);
int linklistcreateh(LINKLIST L,SDL_Rect* MON,int n);
bool whereismon(SDL_Rect* mon,int* map_way[]);
void init_player_4();
void turn_to_trap(SDL_Rect* mon,int** map_way);
void init_magic_from_player();
LINKLIST Linklistdelete(LINKLIST L,int py,int px);

