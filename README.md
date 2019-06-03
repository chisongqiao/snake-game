# snake-game
this is a game about snake game by C
基本思路： 
蛇每吃一个食物蛇身子就增加一格，用WASD控制蛇头的运动，而蛇身子跟着蛇头走，每后一格蛇身子下一步走到上一格蛇身子的位置，以此类推。
程序主要变量如下：

#define M 20//整个图形界面的长和宽
#define N 60
    struct snake a[(M - 2)*(N - 2)];//蛇身数组
    int snake_x =4;//蛇身的XY坐标
    int snake_y =4;
    int X = 1;//控制蛇头的方向量
    int Y = 0;
    int food_x , food_y ;//食物的XY坐标
    int score = 0;//分数
食物的随机位置产生是通过两个随机数分别代表X,Y坐标实现的。
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
用WASD控制蛇头的运动是通过改变蛇头的X,Y坐标实现的。

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
1
2
3
4
5
6
7
8
9
10
11
12
13
14
15
16
17
18
19
20
21
22
23
24
25
26
27
28
29
30
31
32
33
34
35
36
37
用定义蛇身子的结构体储存身子的XY坐标，然后定义蛇身子结构体数组存储每一节蛇身子。

struct snake
{
    int number;
    int snake_x;
    int snake_y;
    //struct snake *next;
};

struct snake a[(M - 2)*(N - 2)];


void build_snake(struct snake *snake,int s,int *sx,int *sy)//sx,sy蛇头的位置
{
    for (int i = s; i >= 0; i--)
    {
        if (i == 0) {
            (snake + i)->number = i;
            (snake + i)->snake_x = *sx;
            (snake + i)->snake_y = *sy;
        }else{
            (snake + i)->number = i;
            (snake + i)->snake_x = (snake + i - 1)->snake_x;
            (snake + i)->snake_y = (snake + i - 1)->snake_y;
        }
    }
}
1
2
3
4
5
6
7
8
9
10
11
12
13
14
15
16
17
18
19
20
21
22
23
24
25
26
27
有了蛇身子和食物的坐标位置，将它们一起存储在一个表示整个界面的二位数组，然后循环打印整个数组形成动画效果！

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
