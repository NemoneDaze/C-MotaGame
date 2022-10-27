#include<stdio.h>
#include"header.h"
#include<conio.h>
#include<stdlib.h>



int TP()
{
	if (Getplayer()->tpstick == 0)
		return 0;
	int Pos[4][2] = { {0,1}, {1,0}, {0,-1}, {-1,0} };
	int Y = Getplayer()->base.y;
	int X = Getplayer()->base.x;
	int YY = 0;
	int XX = 0;
	int Existstairs = 0;
	for (int i = 0; i < 4; i++)
	{
		YY = Y + Pos[i][0];
		XX = X + Pos[i][1];
		sBase* base = FindSceneNode(GetNowScene(), YY, XX);
		if (base == NULL)
			continue;
		if (base->type == UPstairs || base->type == DOWNstairs)
		{
			Existstairs = 1;
			break;
		}
	}
	if (0 == Existstairs)
		return 0;
	int change;
	int prevfloor = Getplayer()->floor;
	int floor = Getplayer()->floor;
	char dir = '0';
	while (dir != ' ')
	{
		system("cls");
		PrintScene(GetNowScene());
		printf("\033[29;36H当前为%d层，按w、d切换想前往的楼层,空格确认",floor);
		dir = _getch();
		change = 0;
		switch (dir)
		{
		case 'w':
		case 'W':change = 1; break;
		case 's':
		case 'S':change = -1; break;
		default:break;
		}
		floor += change;
		if (floor <= 0)
			floor = 1;
		if (floor > Getplayer()->maxfloor)
			floor = Getplayer()->maxfloor;
		Getplayer()->floor = floor;
	}
	int move;
	int times = floor - prevfloor;
	Getplayer()->floor = prevfloor;
	if (times < 0)
	{
		times = -times;
		move = 4;
	}
	else if (times > 0)
		move = 3;
	else if (times == 0)
		return 0;
	while (times)
	{
		ChangeFloor(GetNowScene(), Getplayer(), move);
		times--;
	}
	system("cls");
	return 5;
}

int Illustrated()
{
	if (Getplayer()->tips == 0)
		return 0;
	sBase* base = NULL;
	sPlayer* empty = malloc(sizeof(sPlayer));
	empty->floor = -1;
	int arr[10] = { 0 };
	int kind = 0;
	int check;
	for (int i = 0; i < 13; i++)
	{
		for (int j = 0; j < 13; j++)
		{
			check = 1;
			base = FindSceneNode(GetNowScene(), i, j);
			if (!base)
				continue;
			for (int k = 0; k <= kind; k++)
			{
				if (base->type == arr[k])
				{
					check = 0;
					break;
				}
			}
			if (base->type <= 23 && base->type >= 16 && check)
			{
				arr[kind] = base->type;
				kind++;
				base->collisionCB(empty, base);
				printf("\033[20;84H请按任意键查询");
				printf("\033[21;84H下一个怪物属性");
				_getch();
			}
		}
	}
	system("cls");
	return 0;
}