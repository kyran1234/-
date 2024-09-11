#include<stdio.h>
#include<Windows.h>
#include<time.h>
#include<math.h>
#include<conio.h>
#include<SDL2/SDL.h>
#include<stdlib.h>
#include<stdbool.h>
#include<SDL2/SDL_image.h>
#include "third.h"

SDL_Window *w = NULL;//窗口
SDL_Renderer *r  = NULL;//
SDL_Surface* s=NULL;
SDL_Texture* t=NULL;

static int Rank = 0;
int man_x=2,man_y=2;
static int px=2,py=2;
int N = 16;
bool last=false;
//int man_x=3,man_y=3,ch1=0,ch2=0;
SDL_Rect MAP[256];
SDL_Rect PATH[256];
SDL_Rect newmon[NUM];
SDL_Rect player;
SDL_Rect magicball;
SDL_Rect exIT;
bool die;





LINKLIST L1=NULL;










int main(int argc,char *argv[]) 
{
   
    SDL_Init(SDL_INIT_EVERYTHING);
	srand((unsigned)time(NULL));
	int **map_way=(int**)malloc(N*sizeof(int *));
    
	for (int i=0;i<N;i++) 
		map_way[i]=(int*)calloc(N,sizeof(int));
    map_make(map_way);
    init_player_4();
     linklist_init(&L1);
    createmon(newmon,map_way);
    turn_to_trap(newmon,map_way);
    linklistcreateh(L1,newmon,NUM);

	
    create_window(WINDOW_WIDTH,WINDOW_HEIGHT);
    //init_map(MAP);
    //init_path(PATH,map_way);
    event_loop_7(map_way);
	//map_draw(map_way);
	//move(map_way);
	//getchar();
    SDL_DestroyRenderer(r);
    SDL_DestroyWindow(w);
    //退出image库
    //IMG_Quit();
    //退出SDL
    SDL_Quit();
	return 0;
}


void linklist_init(LINKLIST* L){
    *L=(LNODE*)malloc(sizeof(LNODE));
    if(*L==NULL){
        printf("fail");
        exit;
    }
(*L)->next=NULL;
}//创建链表头

int linklistcreateh(LINKLIST L,SDL_Rect* MON,int n){//传链表的一级指针//传newmon
    int i;
    LNODE *p;//指向链表的指针
    if(L==NULL)linklist_init(&L);//若传入的链表没有初始化，则初始化
    for(i=0;i<n;i++){
        p=(LNODE*)malloc(sizeof(LNODE));//申请节点空间
        if(p==NULL){
            printf("fail");
            return  0;
        }
        p->mon=*(MON+i);
        p->next=L->next;//新节点的指针指向原来上个节点指向的位置
        L->next=p;//上一个节点指向p；一是把链表连起来，二是指向p，方便下次用
    }
    return 0;
}

LINKLIST Linklistdelete(LINKLIST L, int py, int px) {
    LNODE *pre, *p;
    p = L->next;
    if (p == NULL) {
        // 如果链表为空，直接返回
        return L;
    }
    if (p->mon.x == px * 50 && p->mon.y == py * 50) {
        // 如果头节点就是要删除的节点
        L->next = p->next;
        free(p);
        return L;
    }
    pre = p;
    p = p->next;
    while (p) {
        if (p->mon.x == px * 50 && p->mon.y == py * 50) {
            pre->next = p->next;
            free(p);
            break;
        }
        pre = p;
        p = p->next;
    }
    return L;
}


void init_magic_from_player(){
    magicball.x=player.x+10;
    magicball.y=player.y+10;
    magicball.h=30;
    magicball.w=30;
}


void init_player_4(){
    player.x=px*50;
    player.y=py*50;
    player.h=49;
    player.w=49;
}

void createmon(SDL_Rect* mon,int* map_way[]){
    int i;
    for(i=0;i<NUM;i++){
    time_t t;
    srand((unsigned) time(&t));
    //(mon+i)->x=((rand()%(N*50))+25)/50*50;
    //(mon+i)->y=(rand()%(N*50)+25)/50*50;
    (mon+i)->x = (rand() % 14+1) * 50; // 生成 0 到 15 之间的随机数，然后乘以 50
    (mon+i)->y = (rand() % 14+1) * 50; // 生成 0 到 15 之间的随机数，然后乘以 50
    (mon+i)->w=49;
    (mon+i)->h=49;
    SDL_Delay(1000);
    if(whereismon((mon+i),map_way)){//正好建在迷宫上了
        i--;
    }
    }
}

bool whereismon(SDL_Rect* mon,int* map_way[]){//防止mon生成在墙上
    int X,Y;
    X=mon->y/50;
    Y=mon->x/50;
    if(map_way[X][Y]==WAY||(X==2&&Y==2)){
        return false;
    }
    else return true;
}

void turn_to_trap(SDL_Rect* newmon,int** map_way){
    int X,Y,i;
    for(i=0;i<NUM;i++){
    X=(newmon+i)->y/50;
    Y=(newmon+i)->x/50;
    map_way[X][Y]=TRAP;
    }

}//删除节点后记得转回way！！！！！！！！

//void createmon(SDL_Rect* mon){//一级指针



void drawmon(LINKLIST L){
    LINKLIST p;
    for(p=L->next;p!=NULL;p=p->next){
        s=IMG_Load("mon.png");
        t=SDL_CreateTextureFromSurface(r,s);
        SDL_FreeSurface(s);
        SDL_RenderCopy(r,t,NULL,&(p->mon));
        SDL_DestroyTexture(t);
    }
   // SDL_RenderPresent(r);
}


void init_path_3(SDL_Rect* path,int** map_way){
    int i,j;
    for(i=0;i<16;i++){
        for(j=0;j<16;j++){
            if(map_way[i][j]==WAY||map_way[i][j]==TRAP){
                (path+i+16*j)->w=49;
                (path+i+16*j)->h=49;
                (path+i+16*j)->x=j*50;
                (path+i+16*j)->y=i*50;//坐标可能出错！！
                s=IMG_Load("32.png");
                t=SDL_CreateTextureFromSurface(r,s);
                SDL_FreeSurface(s);
                SDL_RenderCopy(r,t,NULL,(path+i+16*j));
                SDL_DestroyTexture(t);
            }


        }
    }

}



void init_map(SDL_Rect* map){
    int q,A,B;
    A = q/16;
	B = q%16;
    for(q=0;q<256;q++){
        A = q/16;
	    B = q%16;
        (map+q)->w=49;
        (map+q)->h=49;
        (map+q)->x=(A)*50;
        (map+q)->y=(B)*50;

        s=IMG_Load("33.png");
        t=SDL_CreateTextureFromSurface(r,s);
        SDL_FreeSurface(s);
        SDL_RenderCopy(r,t,NULL,(map+q));
        SDL_DestroyTexture(t);
        
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

void event_loop_7(int** map_way){
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
                    if(map_way[py-1][px]==WALL){
                        break;
                    }
                        
                    else if(map_way[py-1][px]==WAY){
                        py--;
                        init_player_4();
                    }
                    else if(map_way[py-1][px]==TRAP){
                        die=true;//直接死or减生命
                    }
                    else if(map_way[py-1][px]==EXIT){
                          py--;
                        init_player_4();
                        last=true;
                        
                    }
                }
                if(INPUT==SDLK_DOWN){
                    if(map_way[py+1][px]==WALL){
                        break;
                    }
                        
                    else if(map_way[py+1][px]==WAY){
                        py++;
                        init_player_4();
                    }
                    else if(map_way[py+1][px]==TRAP){
                         die=true;//直接死or减生命
                    }
                    else if(map_way[py+1][px]==EXIT){
                        py++;
                        init_player_4();
                        last=true;
                        

                    }
                }
                if(INPUT==SDLK_LEFT){
                    if(map_way[py][px-1]==WALL){
                         break;
                    }
                        
                    else if(map_way[py][px-1]==WAY){
                        px--;
                        init_player_4();
                    }
                    else if(map_way[py][px-1]==TRAP){
                         die=true;//直接死or减生命
                    }
                    else if(map_way[py][px-1]==EXIT){
                        px--;
                        init_player_4();
                        last=true;
                        
                    }
                }
                if(INPUT==SDLK_RIGHT){
                   if(map_way[py][px+1]==WALL){
                     break;
                   }
                        
                    else if(map_way[py][px+1]==WAY){
                        px++;
                        init_player_4();
                    }
                    else if(map_way[py][px+1]==TRAP){
                         die=true;
                    }
                    else if(map_way[py][px+1]==EXIT){
                        px++;
                        init_player_4();
                        last=true;
                    }
                }   
            
                if(INPUT==SDLK_w){
                    init_magic_from_player();
                    int i;
                    for(i=0;i<14;i++){
                        SDL_SetRenderDrawColor(r,243,255,92,255);
                        SDL_RenderFillRect(r,&magicball);
                        SDL_RenderPresent(r);
                        magicball.y-=4;
                        magicball.h++;
                        magicball.w++;
                         SDL_Delay(30);
                    }
                         if(map_way[py-1][px]==TRAP){
                            //SDL_Delay(250);
                            Linklistdelete(L1,py-1,px);
                            map_way[py-1][px]=WAY;

                        }
                     //向上发射火球
                }
                if(INPUT==SDLK_s){
                    init_magic_from_player();
                    int i;
                    for(i=0;i<12;i++){
                        SDL_SetRenderDrawColor(r,243,255,92,255);
                        SDL_RenderFillRect(r,&magicball);
                        SDL_RenderPresent(r);
                        magicball.y+=4;
                        magicball.h++;
                        magicball.w++;
                         SDL_Delay(30);
                    }
                         if(map_way[py+1][px]==TRAP){
                            // SDL_Delay(250);
                            Linklistdelete(L1,py+1,px);
                            map_way[py+1][px]=WAY;

                        }
                    //向下发射火球

                }
                if(INPUT==SDLK_a){
                    init_magic_from_player();
                    int i;
                    for(i=0;i<14;i++){
                        SDL_SetRenderDrawColor(r,243,255,92,255);
                        SDL_RenderFillRect(r,&magicball);
                        SDL_RenderPresent(r);
                        magicball.x-=4;
                        magicball.h++;
                        magicball.w++;
                         SDL_Delay(30);
                    }
                        if(map_way[py][px-1]==TRAP){
                            //SDL_Delay(250);
                            Linklistdelete(L1,py,px-1);
                            map_way[py][px-1]=WAY;

                        }
                    
                      //向左发射火球
                }
                if(INPUT==SDLK_d){
                    init_magic_from_player();
                    int i;
                    for(i=0;i<12;i++){
                        SDL_SetRenderDrawColor(r,243,255,92,255);
                        SDL_RenderFillRect(r,&magicball);
                        SDL_RenderPresent(r);
                        magicball.x+=4;
                        magicball.h++;
                        magicball.w++;
                        SDL_Delay(30);
                    }
                        if(map_way[py][px+1]==TRAP){
                            // SDL_Delay(250);
                            Linklistdelete(L1,py,px+1);
                            map_way[py][px+1]=WAY;

                        }
                    
                    
                     //向右发射火球
                }
                break;
            }
        
            
    
    SDL_SetRenderDrawColor(r,23,21,56,255);
    SDL_RenderClear(r);
   // SDL_SetRenderDrawColor(r,25,255,25,255);
    //SDL_RenderFillRects(r,MAP,256);
    init_map(MAP);
   
    //SDL_SetRenderDrawColor(r,255,255,255,255);
    //SDL_RenderFillRects(r,PATH,256);
    init_path_3(PATH,map_way);
    drawmon(L1);
    //SDL_SetRenderDrawColor(r,255,23,34,255);
    //SDL_RenderFillRect(r,&player);
    s=IMG_Load("26.png");
    t=SDL_CreateTextureFromSurface(r,s);
    SDL_FreeSurface(s);
    SDL_RenderCopy(r,t,NULL,&player);
    SDL_RenderPresent(r);
    SDL_DestroyTexture(t);

    s=IMG_Load("23.jpg");
    t=SDL_CreateTextureFromSurface(r,s);
    SDL_FreeSurface(s);
    SDL_RenderCopy(r,t,NULL,&exIT);
    SDL_DestroyTexture(t);

    //SDL_DestroyTexture(t);
    
    SDL_RenderPresent(r);
    if(last){
        SDL_Delay(10);
        s=IMG_Load("42.png");
        t=SDL_CreateTextureFromSurface(r,s);
        SDL_FreeSurface(s);
        SDL_RenderCopy(r,t,NULL,NULL);
        SDL_RenderPresent(r);
        SDL_DestroyTexture(t);
        SDL_Delay(3000000);

    }
    if(die){
        SDL_Delay(10);
        s=IMG_Load("47.png");
        t=SDL_CreateTextureFromSurface(r,s);
        SDL_FreeSurface(s);
        SDL_RenderCopy(r,t,NULL,NULL);
        SDL_RenderPresent(r);
        SDL_DestroyTexture(t);
        SDL_Delay(3000);
    }
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
            exIT.x=(N-i)*50;
            exIT.y=(N-j)*50;
            exIT.h=49;
            exIT.w=49;
			break;
		}
	}
    
}

