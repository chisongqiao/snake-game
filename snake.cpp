#include <stdio.h>
#include <stdlib.h>
#include "snake.h"

void build_snake(struct snake *snake,int s,int *sx,int *sy)
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
