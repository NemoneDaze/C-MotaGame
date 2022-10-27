#include"header.h"
#include<stdio.h>
#include<stdlib.h>

static sSceneCB* s_sceneCB;

typedef struct sMonster_
{
	sBase base;
	int Attack;
	int defense;
	int HP;
	int money;
}sMonster;

static int MonsterCollisionCB(sPlayer* player, sMonster* monster)
{
	if (player->floor == -1)
	{
		printf("\033[14;90H%s", monster->base.name1);
		printf("\033[15;90H%s", monster->base.name2);
		printf("\033[16;87H血量：%d", monster->HP);
		printf("\033[17;87H防御：%d", monster->defense);
		printf("\033[18;87H攻击：%d", monster->Attack);
		printf("\033[19;87H金钱：%d", monster->money);
		return 0;
	}
	if (player->Attack <= monster->defense)
	{
		printf("\033[30;50H你个菜B打不过啦！");
		return 0;
	}
	if (player->defense >= monster->Attack)
	{
		player->money += monster->money;
		free(monster);
		printf("\033[30;50H你击败了一个敌人!");
		return 1;
	}
	int round = monster->HP / (player->Attack - monster->defense);
	if (round < 1)
	{
		player->money += monster->money;
		free(monster);
		printf("\033[30;50H你击败了一个敌人!");
		return 1;
	}
	int lastHP = player->HP - (round - 1) * (monster->Attack - player->defense);
	if (lastHP > 0)
	{
		player->HP = lastHP;
		player->money += monster->money;
		free(monster);
		printf("\033[30;50H你击败了一个敌人!");
		return 1;
	}
	else
		printf("\033[30;50H你个菜B打不过啦！");
	return 0;
}

sBase* CreateSlime1CB(eBase type, int y, int x)
{
	sMonster* slime1 = malloc(sizeof(sMonster));
	slime1->base.type = type;
	slime1->base.y = y;
	slime1->base.x = x;
	slime1->base.name1 = "    ";
	slime1->base.name2 = "\033[92m ● \033[0m";
	slime1->base.collisionCB = MonsterCollisionCB;
	slime1->base.saveCB = NULL;
	slime1->Attack = 18;
	slime1->defense = 1;
	slime1->HP = 35;
	slime1->money = 1;
	return slime1;
}

sBase* CreateSlime2CB(eBase type, int y, int x)
{
	sMonster* slime2 = malloc(sizeof(sMonster));
	slime2->base.type = type;
	slime2->base.y = y;
	slime2->base.x = x;
	slime2->base.name1 = "    ";
	slime2->base.name2 = "\033[96m ● \033[0m";
	slime2->base.collisionCB = MonsterCollisionCB;
	slime2->base.saveCB = NULL;
	slime2->Attack = 20;
	slime2->defense = 2;
	slime2->HP = 45;
	slime2->money = 2;
	return slime2;
}

sBase* CreateSkeleton1CB(eBase type, int y, int x)
{
	sMonster* skeleton1 = malloc(sizeof(sMonster));
	skeleton1->base.type = type;
	skeleton1->base.y = y;
	skeleton1->base.x = x;
	skeleton1->base.name1 = "\033[37m ○ \033[0m";
	skeleton1->base.name2 = "\033[37m ╬ \033[0m";
	skeleton1->base.collisionCB = MonsterCollisionCB;
	skeleton1->base.saveCB = NULL;
	skeleton1->Attack = 42;
	skeleton1->defense = 6;
	skeleton1->HP = 50;
	skeleton1->money = 6;
	return skeleton1;
}

sBase* CreateSkeleton2CB(eBase type, int y, int x)
{
	sMonster* skeleton2 = malloc(sizeof(sMonster));
	skeleton2->base.type = type;
	skeleton2->base.y = y;
	skeleton2->base.x = x;
	skeleton2->base.name1 = "\033[37m ○ \033[0m";
	skeleton2->base.name2 = "\033[37m ╬ ▏\033[0m";
	skeleton2->base.collisionCB = MonsterCollisionCB;
	skeleton2->base.saveCB = NULL;
	skeleton2->Attack = 52;
	skeleton2->defense = 12;
	skeleton2->HP = 55;
	skeleton2->money = 8;
	return skeleton2;
}

sBase* CreateBat1CB(eBase type, int y, int x)
{
	sMonster* Bat1 = malloc(sizeof(sMonster));
	Bat1->base.type = type;
	Bat1->base.y = y;
	Bat1->base.x = x;
	Bat1->base.name1 = "\033[92m>○<\033[0m";
	Bat1->base.name2 = "    ";
	Bat1->base.collisionCB = MonsterCollisionCB;
	Bat1->base.saveCB = NULL;
	Bat1->Attack = 38;
	Bat1->defense = 3;
	Bat1->HP = 35;
	Bat1->money = 2;
	return Bat1;
}

sBase* CreateBat2CB(eBase type, int y, int x)
{
	sMonster* Bat2 = malloc(sizeof(sMonster));
	Bat2->base.type = type;
	Bat2->base.y = y;
	Bat2->base.x = x;
	Bat2->base.name1 = "\033[96m>○<\033[0m";
	Bat2->base.name2 = "    ";
	Bat2->base.collisionCB = MonsterCollisionCB;
	Bat2->base.saveCB = NULL;
	Bat2->Attack = 62;
	Bat2->defense = 6;
	Bat2->HP = 45;
	Bat2->money = 10;
	return Bat2;
}

sBase* CreateMage1CB(eBase type, int y, int x)
{
	sMonster* Mage1 = malloc(sizeof(sMonster));
	Mage1->base.type = type;
	Mage1->base.y = y;
	Mage1->base.x = x;
	Mage1->base.name1 = "\033[92m ● \033[0m";
	Mage1->base.name2 = "\033[92m ■ \033[0m";
	Mage1->base.collisionCB = MonsterCollisionCB;
	Mage1->base.saveCB = NULL;
	Mage1->Attack = 32;
	Mage1->defense = 8;
	Mage1->HP = 60;
	Mage1->money = 5;
	return Mage1;
}

sBase* CreateMage2CB(eBase type, int y, int x)
{
	sMonster* Mage2 = malloc(sizeof(sMonster));
	Mage2->base.type = type;
	Mage2->base.y = y;
	Mage2->base.x = x;
	Mage2->base.name1 = "\033[96m ● \033[0m";
	Mage2->base.name2 = "\033[96m ■ \033[0m";
	Mage2->base.collisionCB = MonsterCollisionCB;
	Mage2->base.saveCB = NULL;
	Mage2->Attack = 68;
	Mage2->defense = 16;
	Mage2->HP = 89;
	Mage2->money = 20;
	return Mage2;
}

sBase* CreateIronmanCB(eBase type, int y, int x)
{
	sMonster* ironman = malloc(sizeof(sMonster));
	ironman->base.type = type;
	ironman->base.y = y;
	ironman->base.x = x;
	ironman->base.collisionCB = MonsterCollisionCB;
	ironman->base.saveCB = NULL;
	ironman->base.name1 = "\033[91m ● \033[0m";
	ironman->base.name2 = "\033[91m ▓ \033[0m";
	ironman->Attack = 180;
	ironman->defense = 110;
	ironman->HP = 100;
	ironman->money = 101;
	return ironman;
}

_declspec(dllexport) char* GetModuleName()
{
	return "Enemy";
}

_declspec(dllexport) void InitModule(sSceneCB* sceneCB)
{
	s_sceneCB = sceneCB;
	s_sceneCB->RegcreateCB(Slime1, CreateSlime1CB);
	s_sceneCB->RegcreateCB(Slime2, CreateSlime2CB);
	s_sceneCB->RegcreateCB(Skeleton1, CreateSkeleton1CB);
	s_sceneCB->RegcreateCB(Skeleton2, CreateSkeleton2CB);
	s_sceneCB->RegcreateCB(Bat1, CreateBat1CB);
	s_sceneCB->RegcreateCB(Bat2, CreateBat2CB);
	s_sceneCB->RegcreateCB(Mage1, CreateMage1CB);
	s_sceneCB->RegcreateCB(Mage2, CreateMage2CB);
	s_sceneCB->RegcreateCB(Ironman, CreateIronmanCB);
}