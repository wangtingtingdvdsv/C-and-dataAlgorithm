/*屏幕坐标范围25(行)*80(列)，假设蛇的移动范围为23*80 */ 
#include <stdio.h>
#include <conio.h>
#include <bios.h>

#define UP 18432
#define RIGHT 19712
#define LEFT 19200
#define DOWN 20480
#define CENTER_X 40
#define CENTER_Y 20
#define END 7181
#define RANGE 100

typedef struct Point{
	int row;
	int col;
}Point;
typedef struct SnakeNode{
	Point point;
	int direct;
}SnakeNode;
typedef struct Snake{
	int head;
	int tail;
	int longth;
	SnakeNode arr[RANGE];
	Point food;  
}Snake;

void move(Snake* snake);
void dotStartUp(Snake* snake);
void circule(int* x, int* y, int* status);
void show(Snake snake);
void initSnake(Snake* snake);
void showBody(int x, int y, int direct);
void showHead(int x, int y, int direct);
void moveOnce(Snake* snake);
void increaseSnake(Snake* snake, int increaseLongth);
void Later(long delayTime);
void initFlagArr(Snake snake, char* flagArr);
int CreateNumberArr(char* flagArr, int* createNumArr);
void createFood(Snake* snake);
int isEat(Snake snake);
int isgameOver(Snake snake);
void border(int row);

void border(int row) {
	int i;
	gotoxy(1, row);
	for(i = 1; i <= 80; i++) {
		printf("~");	
	}
}

int isgameOver(Snake snake) {
	int row = snake.arr[snake.head].point.row;
	int col = snake.arr[snake.head].point.col;
	if(1<=row && row <=80 && 1<=col && col <= 22) {
		return 0;
	} 
	else {
		return 1;
	}
}

int isEat(Snake snake) {
	if(snake.arr[snake.head].point.row == snake.food.row && snake.arr[snake.head].point.col == snake.food.col) {
		return 1;
	} else {
		return 0;
	}
}

void createFood(Snake *snake) {
	int flagArr[1760] = {0};
	int createNumber[1760] = {0};
	int number;
	int row;
	int col;

	initFlagArr(*snake, flagArr);
	number = CreateNumberArr(flagArr, createNumber);
	row = (number%80) + 1;
	col = (number/80) + 1;
	snake->food.row = row;
	snake->food.col = col;
}
/* 
编写产生食物的函数
先申请两个数组，分别为char flagArr[ROW*COL]; int createNumArr[ROW*COL] ;
	遍历循环数组，将row和col所对应的下标转换成一纬数组的下标。然后对flag数组进行赋值；然后初始化creatNum数组；产生随机数。
	将随机数转换成二维下标，在二维下标所在处产生食物 
	*/
int CreateNumberArr(char* flagArr, int* createNumArr) {
	int i = 0;
	int j = 0; 
	int createNum;
	int row;
	int col;
	
	for(i; i < 1760; i++) {
		if(flagArr[i]==0){
			/*将i保存到 createNumArr数组。 */
			createNumArr[j++] = i;
		}
	}	
	srand((int)time(NULL));
	createNum = createNumArr[rand()%j];
	row = (createNum%80) + 1;
	col = (createNum/80) + 1;
	gotoxy(row, col);
	printf("@");
	return createNum;
}

void initFlagArr(Snake snake, char* flagArr) {
	int tail = snake.tail;
	int head = snake.head;
	int row;
	int col;
	for(tail; tail != (head + 1) % RANGE; tail = (tail + 1) % RANGE) {
		row = snake.arr[tail].point.row;
		col = snake.arr[tail].point.col;
		flagArr[(row-1) * 80 + col - 1] = 1; 
	}
}

void Later(long delayTime) {
	int i;
	for(i = 1; i < delayTime; i++) {		
	}
}

void increaseSnake(Snake* snake, int increaseLongth) {
	int i = 1;
	for(i = 1; i <= increaseLongth; i++) {
		snake->arr[((snake->tail)- i + RANGE)%RANGE].point.row = snake->arr[snake->tail].point.row;
		snake->arr[((snake->tail)- i + RANGE)%RANGE].point.col = snake->arr[snake->tail].point.col;
	}
	snake->tail = ((snake->tail) - i + RANGE) % RANGE;
}

void moveOnce(Snake* snake){
	 gotoxy(snake->arr[snake->tail].point.row, snake->arr[snake->tail].point.col);
	 printf(" ");
	 snake->tail = ((snake->tail)+1) % RANGE;
	 snake->head = ((snake->head)+1) % RANGE;
	 printf("\n\n\n");    /**这条语句必须要,为啥呢*/
	 move(snake);
	 show(*snake);
}

void showHead(int x, int y, int direct) {
	if(direct == UP) {
		gotoxy(x, y);
		printf("^");
	} else if(direct == RIGHT) {
		gotoxy(x, y);
		printf(">");
	} else if(direct == LEFT) {
		gotoxy(x, y);
		printf("<");
	} else if(direct == DOWN) {
		gotoxy(x, y);
		printf("V");
	}
}

void showBody(int x, int y, int direct) {
	if(direct == RIGHT || direct == LEFT) {
		gotoxy(x, y);
		printf("-");
	} else if(direct == UP || direct == DOWN) {
		gotoxy(x, y);
		printf("|");
	}
}

void initSnake(Snake* snake) {
	snake->arr[3].point.row = CENTER_X;
	snake->arr[3].point.col = CENTER_Y;
	snake->arr[3].direct = RIGHT;
	snake->arr[2].point.row = CENTER_X-1;
	snake->arr[2].point.col = CENTER_Y;
	snake->arr[2].direct = RIGHT;
	snake->arr[1].point.row = CENTER_X-2;
	snake->arr[1].point.col = CENTER_Y;
	snake->arr[1].direct = RIGHT;
	snake->arr[0].point.row = CENTER_X-3;
	snake->arr[0].point.col = CENTER_Y;
	snake->arr[0].direct = RIGHT;
	snake->head = 3;
	snake->tail = 0;
	snake->longth = 4;
	snake->arr[snake->head].direct = RIGHT;
	show(*snake);
}
void show(Snake snake) {
	 int i;
	 for(i = snake.tail; i != snake.head; i = (i + 1) % RANGE) {
			gotoxy(snake.arr[i].point.row, snake.arr[i].point.col);
			showBody(snake.arr[i].point.row, snake.arr[i].point.col,snake.arr[i].direct);
      	 }
 	 gotoxy(snake.arr[snake.head].point.row, snake.arr[snake.head].point.col);

	showHead(snake.arr[snake.head].point.row, snake.arr[snake.head].point.col, snake.arr[snake.head].direct);
}

void dotStartUp(Snake* snake) {
	int key = END;
	key = bioskey(0);
	border(23);
	initSnake(snake);
	createFood(snake);
	while (key!= END){
		if(bioskey(1)) {
			key = bioskey(0);
			snake->arr[((snake->head)+1)%RANGE].direct = key; 
		}else {
			snake->arr[((snake->head)+1)%RANGE].direct = snake->arr[(snake->head)%RANGE].direct;
		}
		if(isEat(*snake) == 1) {
				increaseSnake(snake, 1);
				snake->arr[((snake->head)+1)%RANGE].direct = snake->arr[(snake->head)%RANGE].direct;
				createFood(snake);
		}
		if(isgameOver(*snake) == 1) {
			system("cls");
			printf("You are gameOver!!!!\n");
	 		return;
	 	}
			Later(30000);
			moveOnce(snake);	
	}
}
 
void move(Snake* snake) {
	if(snake->arr[snake->head].direct == UP) {
		snake->arr[snake->head].point.row = snake->arr[((snake->head)+(RANGE-1))%RANGE].point.row;
		snake->arr[snake->head].point.col = snake->arr[((snake->head)+(RANGE-1))%RANGE].point.col-1;
	} else if(snake->arr[snake->head].direct == DOWN) {
		snake->arr[snake->head].point.row = snake->arr[((snake->head)+(RANGE-1))%RANGE].point.row;
		snake->arr[snake->head].point.col = snake->arr[((snake->head)+(RANGE-1))%RANGE].point.col+1;
	} else if(snake->arr[snake->head].direct == LEFT) {
		snake->arr[snake->head].point.row = snake->arr[((snake->head)+(RANGE-1))%RANGE].point.row-1;
		snake->arr[snake->head].point.col = snake->arr[((snake->head)+(RANGE-1))%RANGE].point.col;
	} else if(snake->arr[snake->head].direct == RIGHT) {
		snake->arr[snake->head].point.row = snake->arr[((snake->head)+(RANGE-1))%RANGE].point.row + 1;
		snake->arr[snake->head].point.col = snake->arr[((snake->head)+(RANGE-1))%RANGE].point.col;
	}
}

void main(void) {
   int i;
   Snake snake = {0};
   system("cls");
	dotStartUp(&snake);
	printf("\n\n\n\n");
   system("pause");
}
