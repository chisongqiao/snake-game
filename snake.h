#ifndef SNAKE_H
#define SNAKE_H

struct snake
{
    int number;
    int snake_x;
    int snake_y;
    //struct snake *next;
};

void build_snake(struct snake *snake, int s, int *sx, int *sy);

#endif
