#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<SDL2/SDL.h>
#include<SDL2/SDL_image.h>
#include<time.h>
#include<math.h>
#include<conio.h>
#include "one.h"

#ifdef __cplusplus
extern "C" {
#endif


static int Rank_1 = 0;


SDL_Window *w = NULL;//窗口
SDL_Renderer *r  = NULL;//
SDL_Surface* s=NULL;
SDL_Texture* t=NULL;

SDL_Rect MAP_1[N*N];
SDL_Rect PATH_2[N*N];
SDL_Rect player_1;
SDL_Rect exIT_1;
static int px_1=2,py_1=2;
bool fail;
SDL_Rect trAP[2];





int main(int argc,char *argv[]) 
{
    SDL_Init(SDL_INIT_EVERYTHING);
	srand((unsigned)time(NULL));
	int **map_way=(int**)malloc(N*sizeof(int *));
	for (int i=0;i<N;i++) 
		map_way[i]=(int*)calloc(N,sizeof(int));

	map_make(map_way);
    init_player_2();
    trap_make(map_way);
	create_window(WINDOW_WIDTH,WINDOW_HEIGHT);
    event_loop_3(map_way);
	SDL_DestroyRenderer(r);
    SDL_DestroyWindow(w);
	return 0;
}

void init_player_2(){
    player_1.x=py_1*50;
    player_1.y=px_1*50;
    player_1.h=49;
    player_1.w=49;
}

void init_map_1(SDL_Rect* map){
    int q,A,B;
    A = q/N;
	B = q%N;
    for(q=0;q<N*N;q++){
        A = q/N;
	    B = q%N;
        (map+q)->w=49;
        (map+q)->h=49;
        (map+q)->x=(A)*50;
        (map+q)->y=(B)*50;

        s=IMG_Load("34.png");
        t=SDL_CreateTextureFromSurface(r,s);
        SDL_FreeSurface(s);
        SDL_RenderCopy(r,t,NULL,(map+q));
        SDL_DestroyTexture(t);
        
    }
}

void init_path_1(SDL_Rect* PATH_2,int** map_way){
    int i,j;
    for(i=0;i<N;i++){
        for(j=0;j<N;j++){
            if(map_way[i][j]==WAY){
                (PATH_2+i+N*j)->w=49;
                (PATH_2+i+N*j)->h=49;
                (PATH_2+i+N*j)->x=j*50;
                (PATH_2+i+N*j)->y=i*50;//坐标可能出错！！
                s=IMG_Load("35.png");
                t=SDL_CreateTextureFromSurface(r,s);
                SDL_FreeSurface(s);
                SDL_RenderCopy(r,t,NULL,(PATH_2+i+16*j));
                SDL_DestroyTexture(t);
            }


        }
    }

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

void event_loop_3(int** map_way){
    bool isRunning=true;//C语言的stdbool正常运行
    while(isRunning){

    SDL_Event msg;
 
    if(SDL_PollEvent(&msg)!=0){
        SDL_KeyCode INPUT = msg.key.keysym.sym;//获取消息成功
		
         switch(msg.type){
            case SDL_QUIT:
               isRunning=false;//退出了整个while循环
               break;//按叉关闭
            case SDL_KEYDOWN:
                if(INPUT==SDLK_LEFT){
                    if(map_way[px_1][py_1-1]==WALL){
                        break;
                    }
                        
                    else if(map_way[px_1][py_1-1]==WAY){
                        py_1--;
                        init_player_2();
                    }
                    else if(map_way[px_1][py_1-1]==TRAP){
                        fail=true;
                    }
                    else if(map_way[px_1][py_1-1]==EXIT){
                          py_1--;
                        init_player_2();
                        exit(0);
                        //last=true;
                        
                    }
                }
                if(INPUT==SDLK_RIGHT){
                    if(map_way[px_1][py_1+1]==WALL){
                        break;
                    }
                        
                    else if(map_way[px_1][py_1+1]==WAY){
                        py_1++;
                        init_player_2();
                    }
                    else if(map_way[px_1][py_1+1]==TRAP){
                        fail=true;
                    }
                    else if(map_way[px_1][py_1+1]==EXIT){
                        py_1++;
                        init_player_2();
                        exit(0);
                       //last=true;
                        

                    }
                }
                if(INPUT==SDLK_UP){
                    if(map_way[px_1-1][py_1]==WALL){
                         break;
                    }
                        
                    else if(map_way[px_1-1][py_1]==WAY){
                        px_1--;
                        init_player_2();
                    }
                    else if(map_way[px_1-1][py_1]==TRAP){
                        fail=true;
                    }
                    else if(map_way[px_1-1][py_1]==EXIT){
                        px_1--;
                        init_player_2();
                        exit(0);
                        //last=true;
                        
                    }
                }
                if(INPUT==SDLK_DOWN){
                   if(map_way[px_1+1][py_1]==WALL){
                     break;
                   }
                        
                    else if(map_way[px_1+1][py_1]==WAY){
                        px_1++;
                        init_player_2();
                    }
                    else if(map_way[px_1+1][py_1]==TRAP){
                         fail=true;
                    }
                    else if(map_way[px_1+1][py_1]==EXIT){
                        px_1++;
                        init_player_2();
                        exit(0);
                        //last=true;
                    }
                }   
                break;
            }
    SDL_SetRenderDrawColor(r,23,21,56,255);
    SDL_RenderClear(r);
     init_map_1(MAP_1);
     init_path_1(PATH_2,map_way);
     s=IMG_Load("26.png");
    t=SDL_CreateTextureFromSurface(r,s);
    SDL_FreeSurface(s);
    SDL_RenderCopy(r,t,NULL,&player_1);
    SDL_RenderPresent(r);
    SDL_DestroyTexture(t);

    s=IMG_Load("23.jpg");
    t=SDL_CreateTextureFromSurface(r,s);
    SDL_FreeSurface(s);
    SDL_RenderCopy(r,t,NULL,&exIT_1);
    SDL_DestroyTexture(t);
     
     s=IMG_Load("21.png");
    t=SDL_CreateTextureFromSurface(r,s);
     SDL_FreeSurface(s);
    SDL_RenderCopy(r,t,NULL,trAP+1);
    
     SDL_RenderCopy(r,t,NULL,trAP);

     SDL_DestroyTexture(t);
      SDL_RenderPresent(r); 

    }
    if(fail){
        SDL_Delay(10);
        s=IMG_Load("47.png");
        t=SDL_CreateTextureFromSurface(r,s);
        SDL_FreeSurface(s);
        SDL_RenderCopy(r,t,NULL,NULL);
        SDL_RenderPresent(r);
        SDL_DestroyTexture(t);
        SDL_Delay(3000);
        //on_timer(30000);
       
    
    }
    }
}
//��ͼ
void createmap(int **map_way,int x,int y)
{
	//random_direction
	map_way[x][y] = WAY;

	int direction[4][2]={{1,0},{-1,0},{0,1},{0,-1}};
	for(int i=0;i < 4;i++)
	{	
		int r = rand()%4;
		int temp=direction[0][0];
		direction[0][0] = direction[r][0];
		direction[r][0] = temp;
		temp = direction[0][1];
		direction[0][1] = direction[r][1];
		direction[r][1] = temp;

	}
	//Maze_make
	for (int i=0;i < 4;i++)
	{
		int dx = x;
		int dy = y;

		int range = 1;
		while(range > 0)
		{
			dx += direction[i][0];
			dy += direction[i][1];

			if(map_way[dx][dy]==WAY)
				break;
	
			int count=0;
			for(int j = dx - 1;j < dx + 2;j++)
			{
				for(int k = dy - 1;k < dy + 2;k++)
				{
					if (abs(j - dx)+abs(k - dy)==1&&map_way[j][k] == WAY)
						count++;
				}
			}
			
			if (count > 1)
				break;

			--range;
			map_way[dx][dy]=WAY;	
		}
		if(range<=0)
			createmap(map_way,dx,dy);
	}
}
//exit_make
void map_make(int **map_way)
{
	for(int i=0;i < N;i++)
	{
		map_way[i][0]=WAY;
		map_way[0][i]=WAY;
		map_way[i][N-1]=WAY;
		map_way[N-1][i]=WAY;
	}
	createmap(map_way,2,2);
	while(1)
	{
		int i=rand()%(N/2);
		int j=rand()%(N/2);
		if(i > 1&&j > 1&&map_way[N-i][N-j]==WAY)
		{
			map_way[N - i][N - j] = EXIT;
            exIT_1.x=(N-j)*50;
            exIT_1.y=(N-i)*50;
            exIT_1.h=49;
            exIT_1.w=49;
			break;
		}
	}
}

void trap_make(int **map_way)
{
    for (int i = 0; i < 2;)
    {
        int x = rand()%(N/2);//��֤�������Թ������½�����;
        int y = rand()%(N/2);//ͬ��;
        if(y>1&&x>1&&map_way[N-x][N-y]!=WALL)
        {
            map_way[N-x][N-y]= 2;//change to trap
            (trAP+i)->x=(N-y)*50;
            (trAP+i)->y=(N-x)*50;
            (trAP+i)->h=49;
            (trAP+i)->w=49;
            i++;
        }

    }
    return ;
    
}

#ifdef __cplusplus
}
#endif