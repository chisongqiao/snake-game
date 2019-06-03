#ifndef INTERFACE_H
#define INTERFACE_H

#define M 20
#define N 60

void control(int *x, int *y, int *X, int *Y);
void snake(int x, int y);
void newinterface(struct snake *snake, int fx, int fy, int s);
void food(int *x, int *y, int *fx, int *fy, int *s, struct snake *snake);
void draw(void);
void death(int x, int y, int s);

#endif
