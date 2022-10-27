#define _CRT_SECURE_NO_WARNINGS
#include"header.h"
#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<windows.h>
#include<string.h>

static sSceneCB* s_sceneCB;

typedef struct sElder_
{
	sBase base;
	int ins;
}sElder;

static int EmptyCollisionCB(sPlayer* player, sBase* base)
{
	return 0;
}

static int Elder2CollisionCB(sPlayer* player, sBase* base)
{
	sElder* elder = (sElder*)base;
	if (elder->ins == 2)
	{
		printf("\033[10;65H                   \n"\
			   "\033[11;65H你好,我是大木博士\n"\
			   "\033[12;65H                   ");
		_getch();
		printf("\033[30;48H从怪人手上获得手册");
		player->tips++;
		Sleep(1200);
		printf("\033[10;65H                   \n"\
			   "\033[11;65H去成为宝可梦大师吧\n"\
			   "\033[12;65H                   ");
		_getch();
		elder->ins--;
		system("cls");
		return 0;
	}
	if (elder->ins == 1)
	{
		printf("\033[10;65H                   \n"\
			"\033[11;65H什么?你说我挡路了?\n"\
			"\033[12;65H                   ");
		printf("\033[30;46H  怪人消失了！！！");
		Sleep(1200);
		elder->ins--;
		system("cls");
		free(elder);
		return 1;
	}
	return 0;
}

//static int Elder2SaveCB(_IN_OUT_ char* buff, _IN_OUT_ int* len, sBase* base)
//{
//	sElder* elder = (sElder*)base;
//	sprintf(buff, "%d %d %d %d", elder->base.type, elder->base.y, elder->base.x, elder->ins);
//	int size = strlen(buff);
//	*len = size;
//	return size;
//}
static int Elder2SaveCB(_IN_OUT_ char* data, _IN_ sBase* base)
{
	sElder* elder = (sElder*)base;
	int len = sizeof(sElder) - sizeof(sBase) + sizeof(sSaveBase);
	if (data == NULL)
		return 0;
	memcpy(data, &len, 4);
	memcpy(data+4, elder, sizeof(sSaveBase));
	memcpy(data + sizeof(sSaveBase) + 4, &elder->ins, sizeof(elder->ins));
	return len + 4;
}

typedef struct sTraders1_
{
	sBase base;
}sTraders1;

sBase* CreateTraders1CB(eBase type, int y, int x)
{
	sTraders1* traders1 = malloc(sizeof(sTraders1));
	traders1->base.type = type;
	traders1->base.y = y;
	traders1->base.x = x;
	traders1->base.name1 = "\033[94m ◆ \033[0m";
	traders1->base.name2 = "\033[94m ■ \033[0m";
	traders1->base.collisionCB = EmptyCollisionCB;
	traders1->base.saveCB = NULL;
	return traders1;
}

sBase* CreateElder1CB(eBase type, int y, int x)
{
	sElder* elder1 = malloc(sizeof(sElder));
	elder1->base.type = type;
	elder1->base.y = y;
	elder1->base.x = x;
	elder1->base.name1 = "\033[94m ▼\033[0m";
	elder1->base.name2 = "\033[94m ■ \033[0m";
	elder1->base.collisionCB = EmptyCollisionCB;
	elder1->base.saveCB = NULL;
	elder1->ins = 0;
	return elder1;
}

sBase* CreateElder2CB(eBase type, int y, int x)
{
	sElder* elder2 = malloc(sizeof(sElder));
	elder2->base.type = type;
	elder2->base.y = y;
	elder2->base.x = x;
	elder2->base.name1 = "\033[94m ▼\033[0m";
	elder2->base.name2 = "\033[94m ■ \033[0m";
	elder2->base.collisionCB = Elder2CollisionCB;
	elder2->base.saveCB = Elder2SaveCB;
	elder2->ins = 2;
	return elder2;
}

typedef struct sThief_
{
	sBase base;
}sThief;

sBase* CreateThiefCB(eBase type, int y, int x)
{
	sThief* thief = malloc(sizeof(sThief));
	thief->base.type = type;
	thief->base.y = y;
	thief->base.x = x;
	thief->base.name1 = "\033[94m ▲ \033[0m";
	thief->base.name2 = "\033[94m ■ \033[0m";
	thief->base.collisionCB = EmptyCollisionCB;
	thief->base.saveCB = NULL;
	return thief;
}

_declspec(dllexport) char* GetModuleName()
{
	return "NPC";
}

_declspec(dllexport) void InitModule(sSceneCB* sceneCB)
{
	s_sceneCB = sceneCB;
	s_sceneCB->RegcreateCB(Traders1, CreateTraders1CB);
	s_sceneCB->RegcreateCB(Elder1, CreateElder1CB);
	s_sceneCB->RegcreateCB(Elder2, CreateElder2CB);
	s_sceneCB->RegcreateCB(Thief, CreateThiefCB);
}