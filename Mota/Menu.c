#include<stdio.h>
#include"header.h"

static int g_Menu[2][3] = { {0,1,0},
					        {3,2,3} };

static void PrintMenu1()
{
	system("cls");
	int Y = 15;
	for (int i = 0; i < 2; i++)
	{
		printf("\033[%d;51H ", Y);
		for (int j = 0; j < 3; j++)
		{
			switch (g_Menu[i][j])
			{
			case 0:printf("◆"); break;
			case 1:printf("开始新游戏"); break;
			case 2:printf("  载入存档"); break;
			case 3:printf("   "); break;
			}
		}
		Y++;
		printf("\n");
	}
}

static int start()
{
	if (g_Menu[0][0] == 0)//newgame
		return 0;
	if (g_Menu[1][0] == 0)//loadinggame
	{
		system("cls");
		printf("\033[16;48H请按1或2选择存档位置");
		while (1)
		{
			char pos = _getch();
			system("cls");
			if (pos == '1' || pos == '2')
				return((int)pos - 48);
		}
	}
}

int Menu()
{
	int pos = 0;
	PrintMenu1();
	while (1)
	{
		char dir = _getch();
		switch (dir)
		{
		case 'W':
		case 'w':dir = -1; break;
		case 'S':
		case 's':dir = +1; break;
		case ' ':return start(); break;
		default:break;
		}
		pos += dir;
		if (pos < 0 || pos>1)
			pos -= dir;
		g_Menu[pos][0] = 0;
		g_Menu[pos][2] = 0;
		g_Menu[1 - pos][0] = 3;
		g_Menu[1 - pos][2] = 3;
		PrintMenu1();
	}
}