#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/time.h>
#include <time.h>

#define UP 65
#define DOWN 66
#define RIGHT 67
#define LEFT 68
#define A 15
#define B 75
#define C 35
#define MAX_LENGTH 200

struct element{
	int x;
	int y;
	int direction;
	int sign;
};
struct element Element[200],turn[200];
struct element *p_element,*p_turn; 

struct bait{
	int x;
	int y;
	int sign;

};
struct bait bait;
int length;
int count_length;
int count_turn;
int alive;
int score;
int score;
int special_food;
int count_time;
void draw_border(int a, int b, int c);
void generate_bait(int a, int b, int c);
void move();
void gotoxy(int x, int y);
void down();
void left();
void up();
void right();
void delay();
void is_death();
void Score();
void init();
int kbhit();
void turn_action();
void turn_up();
void turn_down();
void turn_right();
void turn_left();
int get_arrow(int a);
void eat_bait();
void draw();
