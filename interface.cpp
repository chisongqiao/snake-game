#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include "interface.h"
#include "snake.h"

char interf[M][N];

void newinterface(struct snake *snake,  int fx, int fy,int s)
{
    int x, y;
    for (int i = 0; i < M; i++)
    {
        for (int j = 0; j < N; j++)
        {
            if (i == 0 || i == M - 1)
                interf[i][j] = '-';
                //printf("-");
            else if (j == 0)
                interf[i][j] = '|';
                //printf("|");
            else if (j == N - 1)
                interf[i][j] = '|';
                //printf("|\n");
            else if (i == fy && j == fx)
                interf[i][j] = '$';
                //printf("$");
            else  
                interf[i][j] = ' ';
                //printf(" ");
        }
    }
    for (; s >= 0; s--)
    {
            x = (snake + s)->snake_x;
            y = (snake + s)->snake_y;
            interf[y][x] = '@';
    }   
}

void food(int *x, int *y,int *fx,int *fy,int *s, struct snake *snake)
{
    int ffx, ffy;//上一次食物的XY坐标
    ffx = *fx;
    ffy = *fy;

    if (*x == *fx && *y == *fy)//如果吃到了食物，产生下一个食物
    { 
        do {
            *fx = 1 + rand() % (N - 3);
            *fy = 1 + rand() % (M - 3);
        } while (ffx == *fx && ffy == *fy);//保证与上次食物位置不同

        for (int i= (*s); i >= 0; i--)
        {
            if ((snake + *s)->snake_x == *fx && (snake + *s)->snake_y == *fy) {
                *fx = 1 + rand() % (N - 3);
                *fy = 1 + rand() % (M - 3);
            }
        }//大概率保证食物与蛇身子的位置不同（不能完全保证）
        (*s)++ ;                          //分数加一!!!!!!!
    }
}


void control(int *x,int *y,int *X,int *Y)//xy是蛇头的坐标，XY是控制运动方向的量
{
    if (_kbhit())
    {
        switch (_getch())
        {
        case 'w' :
        case 'W' :
            if(interf[*y - 1][*x]!='@'){   //if语句保证蛇不能倒着走
                *X = 0; *Y = -1;
            }
            break;
        case 'd':
        case 'D':
            if(interf[*y][*x + 1] != '@'){
                *X = 1; *Y = 0;
            }
                break;
        case 's':
        case 'S':
            if (interf[*y + 1][*x] != '@') {
                *X = 0; *Y = 1;
            }
                break;
        case 'a':
        case 'A':
            if (interf[*y][*x - 1] != '@') {
                *X = -1; *Y = 0;
            }
                break;
        default:
            break;
        } 
    }
    *x = *x + *X;//改变一次位置
    *y = *y + *Y;
}


void draw(void)
{
    for (int i = 0; i < M; i++)
    {
        for (int j = 0; j < N; j++)
        {
            printf("%c", interf[i][j]);
        }
        printf("\n");
    }
}


void death(int x,int y,int s)
{
    if (x == 0 || x == N-1 || y  == 0 || y == M-1 || interf[y][x] == '@') {
        for (;;)
        {
            system("cls");
            printf("\n              游戏结束！\n");
            printf("              最终得分：%d \n", s);
            Sleep(140);
        //system("pause");
        }

    }
}
