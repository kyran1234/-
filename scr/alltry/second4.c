#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<SDL2/SDL.h>
#include<SDL2/SDL_image.h>
#include<time.h>
#include<math.h>
#include<conio.h>
#include "second4.h"


static int Rank = 0;
int N = 16;
//static int man_x=2,man_y=2;//???
int man_x=3,man_y=3,ch1=0,ch2=0; 

SDL_Window *w = NULL;//窗口
SDL_Renderer *r  = NULL;//
SDL_Surface* s=NULL;
SDL_Texture* t=NULL;

SDL_Rect MAP[25];
SDL_Rect PATH[25];
SDL_Rect player;
SDL_Rect exIT;
SDL_Rect trap[2];




int main(int argc,char *argv[]) 
{
    SDL_Init(SDL_INIT_EVERYTHING);
	srand((unsigned)time(NULL));
	int **map_way=(int**)malloc(N*sizeof(int *));
	for (int i=0;i<N;i++) 
		map_way[i]=(int*)calloc(N,sizeof(int));

	map_make(map_way);
    init_player_3();
	//map_draw(map_way);//放在event_lop中
    create_window(WINDOW_WIDTH,WINDOW_HEIGHT);
    event_loop_5(map_way);
    //init_map(MAP);放在map_draw中
    //init_path(PATH,map_way);放在map_draw中
    SDL_DestroyRenderer(r);
    SDL_DestroyWindow(w);
	//move(map_way);
	//getchar();
    
	return 0;
}

void init_player_3(){
    player.x=man_x*50;
    player.y=man_y*50;
    player.h=49;
    player.w=49;
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

void event_loop_5(int** map_way){
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
                if(INPUT==SDLK_UP){
                    if(map_way[man_x][man_y-1]==WALL){
                        break;
                    }
                        
                    else if(map_way[man_x][man_y-1]==WAY){
                        man_y--;
                        init_player_3();
                    }
                    else if(map_way[man_x][man_y-1]==TRAP){
                         break;//直接死or减生命
                    }
                    else if(map_way[man_x][man_y-1]==EXIT){
                          man_y--;
                        init_player_3();
                        exit(0);
                        //last=true;
                        
                    }
                }
                if(INPUT==SDLK_DOWN){
                    if(map_way[man_x][man_y+1]==WALL){
                        break;
                    }
                        
                    else if(map_way[man_x][man_y+1]==WAY){
                        man_y++;
                        init_player_3();
                    }
                    else if(map_way[man_x][man_y+1]==TRAP){
                         break;//直接死or减生命
                    }
                    else if(map_way[man_x][man_y+1]==EXIT){
                        man_y++;
                        init_player_3();
                        exit(0);
                       //last=true;
                        

                    }
                }
                if(INPUT==SDLK_LEFT){
                    if(map_way[man_x-1][man_y]==WALL){
                         break;
                    }
                        
                    else if(map_way[man_x-1][man_y]==WAY){
                        man_x--;
                        init_player_3();
                    }
                    else if(map_way[man_x-1][man_y]==TRAP){
                         break;//直接死or减生命
                    }
                    else if(map_way[man_x-1][man_y]==EXIT){
                        man_x--;
                        init_player_3();
                        exit(0);
                        //last=true;
                        
                    }
                }
                if(INPUT==SDLK_RIGHT){
                   if(map_way[man_x+1][man_y]==WALL){
                     break;
                   }
                        
                    else if(map_way[man_x+1][man_y]==WAY){
                        man_x++;
                        init_player_3();
                    }
                    else if(map_way[man_x+1][man_y]==TRAP){
                         break;//直接死or减生命
                    }
                    else if(map_way[man_x+1][man_y]==EXIT){
                        man_x++;
                        init_player_3();
                        exit(0);
                        //last=true;
                    }
                }   
                break;
            }
     map_draw(map_way); 
     SDL_RenderPresent(r);  
     
    /*SDL_SetRenderDrawColor(r,0,0,0,255);
    SDL_RenderClear(r);
    SDL_SetRenderDrawColor(r,25,255,25,255);
    SDL_RenderFillRects(r,MAP,256);
    
   
    SDL_SetRenderDrawColor(r,255,255,255,255);
    SDL_RenderFillRects(r,PATH,256);*/
    
    

    
    /*if(last){
        SDL_Delay(10);
        s=IMG_Load("25.png");
        t=SDL_CreateTextureFromSurface(r,s);
        SDL_FreeSurface(s);
        SDL_RenderComan_y(r,t,NULL,NULL);
        SDL_RenderPresent(r);
        SDL_DestroyTexture(t);
        SDL_Delay(3000000);
       这段应该会接下一个游戏
    }*/
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
            exIT.x=(N-j)*50;
            exIT.y=(N-i)*50;
            exIT.h=49;
            exIT.w=49;
			break;
		}
	}
}


  



//��ͼ�Ĵ�ӡ
void map_draw(int **map_way) 
{
	int i,j;
	
	 
	//把全图涂黑
	for(int i=0;i<N;i++) 
	{
		for(int j=0;j<N;j++)
		{
			SDL_SetRenderDrawColor(r,0,0,0,255);
            SDL_RenderClear(r);
		}
		
	}

	i=man_x-2;
	j=man_y-2;
//范围内上色	
for(j=man_y-2;j<man_y+3;j++) 
	{
		
		for(i=man_x-2;i<man_x+3;i++)
		{
			if(map_way[i][j]==WAY){
                (PATH+i+5*j)->w=49;
                (PATH+i+5*j)->h=49;
                (PATH+i+5*j)->x=i*50;
                (PATH+i+5*j)->y=j*50;
				s=IMG_Load("29.png");
                t=SDL_CreateTextureFromSurface(r,s);
                SDL_FreeSurface(s);
                SDL_RenderCopy(r,t,NULL,PATH+i+5*j);
                SDL_DestroyTexture(t);
			}
			else if(map_way[i][j]==EXIT)
			{
                s=IMG_Load("23.jpg");
                t=SDL_CreateTextureFromSurface(r,s);
                SDL_FreeSurface(s);
                SDL_RenderCopy(r,t,NULL,&exIT);
                SDL_DestroyTexture(t);
                SDL_RenderPresent(r);	
			} 

			else if(map_way[i][j]==WALL)
			{	
				(MAP+i+5*j)->w=49;
                (MAP+i+5*j)->h=49;
                (MAP+i+5*j)->x=i*50;
                (MAP+i+5*j)->y=j*50;
				s=IMG_Load("27.png");
                t=SDL_CreateTextureFromSurface(r,s);
                SDL_FreeSurface(s);
                SDL_RenderCopy(r,t,NULL,MAP+i+5*j);
                SDL_DestroyTexture(t);
			}
			
			if(i==man_x&&j==man_y)
			{
                player.x=i*50;
                player.y=j*50;
                player.h=49;
                player.w=49;
				s=IMG_Load("31.png");
                t=SDL_CreateTextureFromSurface(r,s);
                SDL_FreeSurface(s);
                SDL_RenderCopy(r,t,NULL,&player);
                SDL_DestroyTexture(t);
			}
		}		
	}
}






