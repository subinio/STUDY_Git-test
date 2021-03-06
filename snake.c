#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <windows.h>

HANDLE Console;

int GameLoop();


//==============================================//
//==============================================//

char play = 0;
char pause = 0;
char direction;

int snake[500]; //Snake piece locations. [0] is head.
int pieces;

int newpieces;
int pointtoadd;
int pointtoerase;
int food = 0;

void FreshDraw();
void DrawFood();



void GameOver(int Type)
{
	switch(Type)
	{
		case HITSELF:
			PrintCenteredText("Game Over! You hit yourself!");
			break;
		
		case HITWALL:
			PrintCenteredText("Game Over! You hit a wall!");
	}
	
	food = 0;
	play = 0;
	memset(snake, 0, sizeof(int) * 500);
}

void zGameOver(int Type)
{
	
	food = 0;
	play = 0;
	memset(snake, 0, sizeof(int) * 500);
}

int UpdateSnake()
{
	int x, y;

	memcpy(snake + 1, snake, sizeof(int)*pieces);
	if(!newpieces)
	{
		pointtoerase = snake[pieces];
		snake[pieces] = 0;
	}
		
	else
	{
		pieces++;
		newpieces--;
	}
	
	x = GETX(snake[0]);
	y = GETY(snake[0]);
	
	switch(direction)
	{
		case UP:
			y -= 1;
			snake[0] = POINT(x,y);
			break;
			
		case DOWN:
			y += 1;
			snake[0] = POINT(x,y);
			break;
			
		case LEFT:
			x -= 1;
			snake[0] = POINT(x,y);
			break;
		
		case RIGHT:
			x += 1;
			snake[0] = POINT(x,y);
			break;
	}
	
	pointtoadd = snake[0];
	
	if(x > 79 || x < 0 ||
	   y > 24 || y < 0 )
	{
		GameOver(HITWALL);
		return 1;
	}
	
	int i;
	for(i = 1; i < pieces; i++)
		if(snake[0] == snake[i])
		{
			GameOver(HITSELF);
			return 1;
		}
		
	if(snake[0] == food)
	{
		while(1) //Find a location for the food not within the snake
		{
			food = (rand() % (80 * 25)) + 1;
			for(i = 0; snake[i]; i++)
				if(food == snake[i])
					food = 0;
					
			if(food)
				break;
		}
		DrawFood();
		newpieces = (rand() % 6) + 1;
	}
	
	return 0;
}

void DrawFood()
{
	SetPos(GETX(food),GETY(food));
	printf("O");
}

void FreshDraw()
{
	system("cls");
	int i;
	for(i = 0; snake[i]; i++)
	{
		SetPos(GETX(snake[i]),GETY(snake[i]));
		printf("#");
	}
	
	DrawFood();
}

void UpdateScreen()
{		
	if(pointtoerase)
	{
		SetPos(GETX(pointtoerase), GETY(pointtoerase));
		printf(" ");
	}
	
	if(pointtoadd)
	{
		SetPos(GETX(pointtoadd), GETY(pointtoadd));
		printf("#");
	}
	
	pointtoadd = pointtoerase = 0;
}

int GameLoop()
{
	int KeyPress;
	
	Sleep(50);
	
	if(kbhit())
	{
		KeyPress = getch();
		
		if(KeyPress == 0 || KeyPress == 0xE0) // 00 or E0 precedes scan code read
		{
			KeyPress = getch();
			
			switch(KeyPress)
			{
				case UP_KEY:
					if(direction != DOWN) //Can't reverse
						direction = UP;
					break;
				
				case DOWN_KEY:
					if(direction != UP)
						direction = DOWN;
					break;
					
				case LEFT_KEY:
					if(direction != RIGHT)
						direction = LEFT;
					break;
					
				case RIGHT_KEY:
					if(direction != LEFT)
						direction = RIGHT;
					break;
			}
		}
		
		if(KeyPress == '\r') //enter
		{
			if(!play)
			{
				play = 1;
				if(pause)
				{
					FreshDraw();
					pause = 0;
				}
			}
				
			else
			{
				PrintCenteredText("Game paused");
				play = 0;
				pause = 1;
			}
		}
		
		else if(KeyPress == 0x1B) //escape
			return 0;
	}
	
	
	return 1;
}

testtest
