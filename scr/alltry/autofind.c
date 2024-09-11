#include<stdio.h> 
#include<stdlib.h>
#include<time.h>
#include<conio.h>
 
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
 
//全局变量
int n, m;     //迷宫的行和列 
struct Node* maze;   //迷宫存放 
struct Path* que;
int top = -1;
int front = -1;
int rear = -1;
 
void create()
{
	int i, j;
	printf("输入迷宫(随机生成)的行和列：");
	scanf("%d%d", &n, &m);
    maze = (struct Node*)malloc(n * m * sizeof(struct Node));
	srand(time(NULL));
	for (i = 0; i < n; i++)
	{
		for (j = 0; j < m; j++)
		{
			int temp = rand() % 4;
			if (temp != 1) maze[i * m + j].data = 1;
			else maze[i * m + j].data = 0;
			maze[i * m + j].flag = 0;
		}
	}
	maze[0].data = 8;  //设置起点 
	maze[n * m - 1].data = 1;
	printf("生成迷宫：\n");
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			printf("%d", maze[i * m + j].data);
		}
		printf("\n");
	}
}
int judge_head()
{
	int k = 1;
	if (que[front].xpath == n - 1 && que[front].ypath == m - 1)
	{
		printf("找到迷宫的通路！\n");
		int x = que[front].xpath;
		int y = que[front].ypath;
		int t = que[front].pox;    //前一个坐标在队列的下标 
		while (x != 0 || y != 0)
		{
			maze[x * m + y].data = 8;
			x = que[t].xpath;
			y = que[t].ypath;
			t = que[t].pox;
			k++;
		}
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < m; j++)
			{
				printf("%d", maze[i * m + j].data);
			}
			printf("\n");
		}
		printf("路径长度为：%d\n", k);
		return 1;
	}
	return 0;
}
void push_road(int x, int y)
{
	if (maze[x * m + y].data == 1 && maze[x * m + y].flag == 0)
	{
		que[(++rear) % (n * m)].xpath = x;
		que[rear % (n * m)].ypath = y;
		que[rear % (n * m)].pox = front;   //设置上一个坐标在队列中的位置 
		maze[x * m + y].flag = 1;
	}
}
/*搜索路径*/
void seek_road()   /*先实现一个路径先*/
{
	//path = new Path[n*m];
	int x1, y1;

	que = (struct Path*)malloc(n * m * sizeof(struct Path));		     //利用广度优先实现最短路径
	que[0].xpath = 0;
	que[0].ypath = 0;
	que[0].pox = 0;
	maze[0].flag = 1;
	rear++;
	while (front != rear)
	{
		int x = que[(++front) % (n * m)].xpath;  //获取队头的坐标，然后将其四周的通路进队,知道操作完队尾元素 
		int y = que[front % (n * m)].ypath;
		//	path[++top] = que[front];
		if (judge_head()) return;
		if (y + 1 < m)
			push_road(x, y + 1);
		if (x + 1 < n)
			push_road(x + 1, y);
		if (y - 1 >= 0)
			push_road(x, y - 1);
		if (x - 1 >= 0)
			push_road(x - 1, y);
	}
	printf("没有通路！\n");
}
int main()
{
	create();
	seek_road();
	return 0;
}
