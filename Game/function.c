#include "header.h"

void init(){
  system("clear");
	draw_border(A,B,C);
	alive =1;
	length =4;
	count_turn=0;
	bait.x = 57;
	bait.y = 27;
	score=0;
	special_food=0;
	p_element=Element;
	p_turn=turn;
	p_element->x=25;
	p_element->y=25;
	p_turn->x=21;
	p_turn->y=25;
	p_element->sign='+';
  bait.sign='*';
  score=0;
  special_food=0;
	p_element->direction=RIGHT;
  p_turn->direction=RIGHT;
	
	gotoxy(10,10);


}
//create the coordinate for the bait 
void generate_bait(int a,int b,int c){
	time_t t;
  // get current time
  t=time(0);
  srand(t);
  if(special_food==5){
    count_time=50;
    bait.sign='F';
    special_food=0;
  }
  else{
    bait.sign='*';
  }
  bait.x=rand()%b;

  if(bait.x<=a){

    bait.x+=(a+1);
  }

  bait.y=rand()%c;

  if(bait.y<=a){
    bait.y+=(a+1);
  }

}
// check if first part of snake has the same coordinate with the bait
//if same coordinate, generate new coordinate of the bait
void eat_bait(){
    

	if(p_element->x==bait.x&&p_element->y==bait.y)
    {
      length++;
      special_food++;
      if(bait.sign=='F'){
        if(count_time>1){
        score+=count_time;
      }
      else{
        score++;
        
      }
      count_time=50;
      }
      else{
        score++;
      }
      generate_bait(A,B,C);
      

       
    }
    gotoxy(bait.x,bait.y);
    printf("%c",bait.sign);
    if(bait.sign=='F'){
      count_time--;
    }
    
    
   
    

}
// score = lenght -4 since the initial length is 4;
void Score(){
	gotoxy(B-10,10);
    printf("SCORE : %d",score);
    gotoxy(B+10,10);
}
// check if the coordinate of the first element meet border
void is_death(){
	if(p_element->x<=A||p_element->x>=B||p_element->y<=A||p_element->y>=C){
		alive =0;
	}
}
// in this fucntion, function kbhit is used to check if user presses any key or not, if not the snake continue to move on its direction
// if user presses the key, it will check if user pressed the arrow key 
// it also check the condition that if the snake is moving up or down, nothing will happen if user presses up or down key arrow
// similar with
//     
void move(){
  struct termios oldt;
  struct termios newt;
  //get current input terminal setting 
  tcgetattr(STDIN_FILENO, &oldt); 
  newt = oldt; 
  /* change setting 
  c_lflag member of the struct termios structure. These flags 
  generally control higher-level aspects of input processing
   c_flag is an 16 bit integer 
   ICANON and ECHO are two constant, which are located on the 16 bit integer c_flag
   for example if c_flag =0b100010
   ICANON bit position =1 -> ICANON value = 2^1=2 
  ICANON This bit, if set, enables canonical input processing mode. 
  Otherwise, input is processed in noncanonical mode.
  canonnical input processing mode terminal input is processed in lines terminated by newline it means
  that when user types anything in the terminal, he must press enter to commit ot to make it work.
  nocanonnical on the other hand does not require user to press enter to make it work 
  ECHO-If this bit is set, echoing of input characters back to the terminal is enabled.
  Bitwise operations in C | = or so  for exampel c_flag=11111111 ICANON value = 8=00001000 ECHO value =4=00000100 ICANON|ECHO =00001100
  and ~ mean not so ~(ICANON | ECHO) =11110011 &= means and so newt.c_lflag &= ~(ICANON | ECHO)= 11110011
  so basically this line of code will change the setting of terminal by changing it to noncanonnical means
  do not need to press enter and echoing of input characters back to the terminal is disable.*/

  newt.c_lflag &= ~(ICANON | ECHO);
  
  //apply new setting immediately TCSANOW
  tcsetattr(STDIN_FILENO, TCSANOW, &newt);
  while(!kbhit()){
   
    eat_bait();
    fflush(stdin);
    draw_border(A,B,C);

    
    count_length=1;
    switch (p_element->direction)
    {
       case UP:
       up();
      
       break;

       case DOWN:
       down();
      
       break;

       case RIGHT:
       right();
      
       break;

       case LEFT:
       left();
    
       break;

    }
   	Score();
    is_death();
    if(alive==0){
    	break;
    }
    
    
    delay();
    
   
  }
  int x = getchar();
  tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
  int arrow = get_arrow(x);
  if(arrow==UP&&(p_element->direction)!=UP&&(p_element->direction)!=DOWN){
    turn_up();
  }
  else if(arrow==DOWN&&(p_element->direction)!=UP&&(p_element->direction)!=DOWN){
    turn_down();
  }
  else if(arrow==RIGHT&&(p_element->direction)!=RIGHT&&(p_element->direction)!=LEFT){
    turn_right();
  }
  else if(arrow==LEFT&&(p_element->direction)!=RIGHT&&(p_element->direction)!=LEFT){
    turn_left();
  }



}
// used to check if user presses any key 
//http://cboard.cprogramming.com/c-programming/63166-kbhit-linux.html
int kbhit()
{
  struct timeval tv;
  // fd file descriptor set of fd
  // collection of files 
  fd_set rdfs;
 
  tv.tv_sec = 0;
  tv.tv_usec = 0;
 // clear collection

  FD_ZERO(&rdfs);
  //add standard input file to monitor
  FD_SET (STDIN_FILENO, &rdfs);
 //check if that file is ready to be read
  // select files that can be read into rdfs pointer
  select(STDIN_FILENO+1, &rdfs, NULL, NULL, &tv);
  //Returns a non-zero value if the bit for the file descriptor fd is set
  // in the file descriptor set pointed to by fdset, and 0 otherwise.
  //if user presses any key, it will check that file is ready to read or not
  return FD_ISSET(STDIN_FILENO, &rdfs);
 
}

// draw the border for the game
void draw_border(int a, int b, int c){
  system("clear");
	for (int i=a;i<=b;i++){
		gotoxy(i,a);
		printf("0");
		gotoxy(i,c);
		printf("0");
	}
	for(int i =a;i<=c;i++){
		gotoxy(a,i);
		printf("0");
		gotoxy(b,i);
		printf("0");
	}
}
// move cursor to coordinate(x,y)
//http://cboard.cprogramming.com/linux-programming/33291-gotoxy-int-x-int-y-linux.html
// use fflush(stdout) because if I dont use it will not print entire the rectangle and I find out
// the reason and solution https://www.quora.com/Why-do-we-use-the-functions-fflush-stdin-and-fflush-stdout-in-c

//ESC (0x1B, ^[) starts an escape sequence and as far as I know it is a console command
void gotoxy(int x, int y){
  fflush(stdout);
  printf("%c[%d;%df",0x1B,y,x);
}
//http://falsinsoft.blogspot.fi/2014/05/detect-arrow-keys-pressure-under-linux.html
// get the key arrow since it is not easy like others
int get_arrow(int a){

  int b;
  int c;
  
  
  if (a == 27)
  {
  b = getchar();
  c = getchar();
  }
 

  if (a == 27 && b == 91)
  {
   return c;
  }
  else{
  	return 1;
  }

}
// four functions beneath 
// handle the change when user presses arrow key, it change the direction, and also this is the place that stores the coordinate 
// of first element when it turns

void turn_right(){
  count_turn++;
  (p_turn+count_turn)->x=p_element->x;
  (p_turn+count_turn)->y=p_element->y;
  (p_turn+count_turn)->direction=p_element->direction;
  p_element->direction=RIGHT;
  p_element->x++;
}
void turn_left(){
  count_turn++;
  (p_turn+count_turn)->x=p_element->x;
  (p_turn+count_turn)->y=p_element->y;
  (p_turn+count_turn)->direction=p_element->direction;
  p_element->direction=LEFT;
  p_element->x--;
}
void turn_up(){
  count_turn++;
  (p_turn+count_turn)->x=p_element->x;
  (p_turn+count_turn)->y=p_element->y;
  (p_turn+count_turn)->direction=p_element->direction;
  p_element->direction=UP;
  p_element->y--;
}
void turn_down(){
  count_turn++;
  (p_turn+count_turn)->x=p_element->x;
  (p_turn+count_turn)->y=p_element->y;
  (p_turn+count_turn)->direction=p_element->direction;
  p_element->direction=DOWN;
  p_element->y++;
}
//to delay the movement of the snake, and it also make that the higher the score is, the faster the snake moves
//and maximum score is 200;
void delay()
{
    
    float x = (float)(MAX_LENGTH+4-length)/MAX_LENGTH;
    long double i;
    for(i=0; i<=50000000*x; i++);
    

    
    
}
// four functions below
// program how the snake move
// for example when snake direction is right, right function will run, first it covers the part that is moving right
//then the turn_action function willhandle the left over part if for example the snake was moving up and turn right
//basically, each time it will reassign the coordinate of each element of the snake and after that I use draw function 
// to create the effect that the snake is moving  
void right(){
  	
    for(int i=1;i<=(p_element->x-(p_turn+count_turn)->x);i++){
    	
      if(count_length<length){
        (p_element+i)->x=p_element->x-i;
        (p_element+i)->y=p_element->y;
        (p_element+i)->sign='*';
        count_length++;
      }
    }
    turn_action();
    draw();
    p_element->x++;
   
}

void left(){
  
    for(int i=1;i<=((p_turn+count_turn)->x-p_element->x);i++){
      if(count_length<length){
        (p_element+i)->x=p_element->x+i;
        (p_element+i)->y=p_element->y;
        (p_element+i)->sign='*';
        count_length++;
      }
    }
    turn_action();
    draw();

    p_element->x--;
  
}
void up(){
  
    for(int i=1;i<=((p_turn+count_turn)->y-p_element->y);i++){
      if(count_length<length){
        (p_element+i)->x=p_element->x;
        (p_element+i)->y=p_element->y+i;
        (p_element+i)->sign='*';
        count_length++;
      }
    }
    turn_action();
    draw();
    p_element->y--;
  
}
void down(){
  
    for(int i=1;i<=(p_element->y-(p_turn+count_turn)->y);i++){
      if(count_length<length){
        (p_element+i)->x=p_element->x;
        (p_element+i)->y=p_element->y-i;
        (p_element+i)->sign='*';
        count_length++;
      }
    }
    turn_action();
    draw();
    p_element->y++;
}
// this function is used to handle how snake turns
// I save the coordinate of the first part when the snake turns and base on that I can change the coordinate of each part of the snake
//  notice that when snake moves up the y value is reduce;
void turn_action(){
  
  for(int j=count_turn;j>0;j--){
  	

  	
    
      if(((p_turn+j)->direction)==UP){
        int c=1;
        for(int i=0;i<((p_turn+j-1)->y-(p_turn+j)->y);i++){
          if(count_length<length){
          (p_element+count_length)->x=(p_turn+j)->x;
          (p_element+count_length)->y=(p_turn+j)->y+c;
          (p_element+count_length)->sign='*';
          c++;
          count_length++;
        }
      }
    }
      else if(((p_turn+j)->direction)==DOWN){
        int c=1;
        for(int i = 0;i<((p_turn+j)->y-(p_turn+j-1)->y);i++){
          if(count_length<length){
          
          (p_element+count_length)->x=(p_turn+j)->x;
          (p_element+count_length)->y=(p_turn+j)->y-c;
          c++;
          (p_element+count_length)->sign='*';
          count_length++;
        }
      }
    }
       else if(((p_turn+j)->direction)==RIGHT){
        int c=1;
        for(int i = 0;i<((p_turn+j)->x-(p_turn+j-1)->x);i++){
          
          if(count_length<length){
          (p_element+count_length)->x=(p_turn+j)->x-c;
          (p_element+count_length)->y=(p_turn+j)->y;
          c++;
          (p_element+count_length)->sign='*';
          count_length++;
        }
      }
    }
       else if(((p_turn+j)->direction)==LEFT){
        int c=1;
        for(int i = 0;i<((p_turn+j-1)->x-(p_turn+j)->x);i++){
          if(count_length<length){
          (p_element+count_length)->x=(p_turn+j)->x+c;
          (p_element+count_length)->y=(p_turn+j)->y;
          (p_element+count_length)->sign='*';
          c++;
          count_length++;
        }
      }
    }
    }
  

}
// to print the snake into the console
void draw(){
  
  for(int i=0;i<length;i++){
    gotoxy((p_element+i)->x,(p_element+i)->y);
    printf("%c",(p_element+i)->sign);
  }
}