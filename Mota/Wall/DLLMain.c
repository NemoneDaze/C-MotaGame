#include<stdio.h>
#include<stdlib.h>
#include"header.h"

static sSceneCB* s_sceneCB;

typedef struct sArch_
{
	sBase base;
}sArch;

static int WallCollisionCB(void* Player, void* Base)
{
	printf("\033[30;50H你看到了一面墙   ");
	return 0;
}

static int PwallCollisionCB(void* Player, sArch* pwall)
{
	free(pwall);
	return 1;
}

static int AltarCollisionCB(void* Player, void* Base)
{
	printf("\033[30;50H祭坛! !可以升级哦!");
	return 0;
}

sBase* CreateWallCB(eBase type, int y, int x)
{
	sArch* wall = malloc(sizeof(sArch));
	wall->base.type = type;
	wall->base.y = y;
	wall->base.x = x;
	wall->base.name1 = "\033[33m■■\033[0m";
	wall->base.name2 = "\033[33m■■\033[0m";
	wall->base.collisionCB = WallCollisionCB;
	wall->base.saveCB = NULL;
	return wall;
}

sBase* CreateAltarCB(eBase type, int y, int x)
{
	sArch* altar = malloc(sizeof(sArch));
	altar->base.type = type;
	altar->base.y = y;
	altar->base.x = x;
	altar->base.name1 = "\033[97;101m║ ╦ ║\033[0m";
	altar->base.name2 = "\033[97;101m║ ╩ ║\033[0m";
	altar->base.collisionCB = AltarCollisionCB;
	altar->base.saveCB = NULL;
	return altar;
}

sBase* CreatePwallCB(eBase type, int y, int x)
{
	sArch* pwall = malloc(sizeof(sArch));
	pwall->base.type = type;
	pwall->base.y = y;
	pwall->base.x = x;
	pwall->base.name1 = "\033[93m■■\033[0m";
	pwall->base.name2 = "\033[93m■■\033[0m";
	pwall->base.collisionCB = PwallCollisionCB;
	pwall->base.saveCB = NULL;
	return pwall;
}

_declspec(dllexport) char* GetModuleName()
{
	return "Wall";
}

_declspec(dllexport) void InitModule(sSceneCB* sceneCB)
{
	s_sceneCB = sceneCB;
	s_sceneCB->RegcreateCB(Wall, CreateWallCB);
	s_sceneCB->RegcreateCB(Altar, CreateAltarCB);
	s_sceneCB->RegcreateCB(Pwall, CreatePwallCB);
	s_sceneCB->RegcreateCB(end, CreateWallCB);
}