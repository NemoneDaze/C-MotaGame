#include"header.h"
#include<stdio.h>
#include<stdlib.h>

static sSceneCB* s_sceneCB;

typedef struct sDoor_
{
	sBase base;
}sDoor;

static int YdoorCollisionCB(sPlayer* player, sDoor* ydoor)
{
	if (player->ykey > 0)
	{
		player->ykey--;
		free(ydoor);
		printf("\033[30;50H你打开了一扇门   ");
		return 1;
	}
	printf("\033[30;50H你没有对应的钥匙 ");
	return 0;
}

sBase* CreateYdoorCB(eBase type, int y, int x)
{
	sDoor* Ydoor = malloc(sizeof(sDoor));
	Ydoor->base.type = type;
	Ydoor->base.y = y;
	Ydoor->base.x = x;
	Ydoor->base.name1 = "\033[93m┍━━┑\033[0m";
	Ydoor->base.name2 = "\033[93m┝  ┥\033[0m";
	Ydoor->base.collisionCB = YdoorCollisionCB;
	Ydoor->base.saveCB = NULL;
	return Ydoor;
}

static int BdoorCollisionCB(sPlayer* player, sDoor* bdoor)
{
	if (player->bkey > 0)
	{
		player->bkey--;
		free(bdoor);
		printf("\033[30;50H你打开了一扇门   ");
		return 1;
	}
	printf("\033[30;50H你没有对应的钥匙 ");
	return 0;
}

sBase* CreateBdoorCB(eBase type, int y, int x)
{
	sDoor* Bdoor = malloc(sizeof(sDoor));
	Bdoor->base.type = type;
	Bdoor->base.y = y;
	Bdoor->base.x = x;
	Bdoor->base.name1 = "\033[94m┍━━┑\033[0m";
	Bdoor->base.name2 = "\033[94m┝  ┥\033[0m";
	Bdoor->base.collisionCB = BdoorCollisionCB;
	Bdoor->base.saveCB = NULL;
	return Bdoor;
}

static int GateCollisionCB(sPlayer* player, sDoor* gate)
{
	printf("\033[30;50H铁门！！无法打开 ");
	return 0;
}

sBase* CreateGateCB(eBase type, int y, int x)
{
	sDoor* gate = malloc(sizeof(sDoor));
	gate->base.type = Gate;
	gate->base.y = y;
	gate->base.x = x;
	gate->base.name1 = "\033[90m▓▓\033[0m";
	gate->base.name2 = "\033[90m▓▓\033[0m";
	gate->base.collisionCB = GateCollisionCB;
	gate->base.saveCB = NULL;
	return gate;
}

_declspec(dllexport) char* GetModuleName()
{
	return "Door";
}

_declspec(dllexport) void InitModule(sSceneCB* sceneCB)
{
	s_sceneCB = sceneCB;
	s_sceneCB->RegcreateCB(Ydoor, CreateYdoorCB);
	s_sceneCB->RegcreateCB(Bdoor, CreateBdoorCB);
	s_sceneCB->RegcreateCB(Gate, CreateGateCB);
}