#include<stdio.h>
#include<stdlib.h>
#include"header.h"

typedef struct sStairs_
{
	sBase base;
}sStairs;

static int StairsCollisionCB(sPlayer* player, sStairs* stairs)
{
	int move;
	if (stairs->base.type == UPstairs)
		move = 3;
	else
		move = 4;
	ChangeFloor(GetNowScene(player), player, move);
	if (player->maxfloor < player->floor)
		player->maxfloor = player->floor;
	system("cls");
}

sBase* CreateUPstairsCB(eBase type, int y, int x)
{
	sStairs* Stairs = malloc(sizeof(sStairs));
	Stairs->base.type = type;
	Stairs->base.x = x;
	Stairs->base.y = y;
	Stairs->base.name1 = "\033[97m©Á©¥©É\033[0m";
	Stairs->base.name2 = "\033[97m©¦ ©¦\033[0m";
	Stairs->base.collisionCB = StairsCollisionCB;
	Stairs->base.saveCB = NULL;
	return Stairs;
}

sBase* CreateDownstairsCB(eBase type, int y, int x)
{
	sStairs* Stairs = malloc(sizeof(sStairs));
	Stairs->base.type = type;
	Stairs->base.x = x;
	Stairs->base.y = y;
	Stairs->base.name1 = "\033[97m©¦ ©¦\033[0m";
	Stairs->base.name2 = "\033[97m©Á©¥©É\033[0m";
	Stairs->base.collisionCB = StairsCollisionCB;
	Stairs->base.saveCB = NULL;
	return Stairs;
}
