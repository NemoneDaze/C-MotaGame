#ifndef _HEADER_H_2022_4_11
#define _HEADER_H_2022_4_11
#include<stdio.h>
#define _IN_
#define _IN_OUT_
#define _OUT_


typedef enum eBase_
{
	Wall = 0,
	Pwall = 1,
	Ydoor = 2,
	Bdoor = 3,
	Rdoor = 4,
	UPstairs = 5,
	DOWNstairs = 6,
	Ykey = 7,
	Bkey = 8,
	HP1 = 9,
	HP2 = 10,
	AttUP = 11,
	DefUP = 12,
	TPstick = 13,
	HandBook = 14,
	Tips = 15,
	Slime1 = 16,
	Slime2 = 17,
	Skeleton1 = 18,
	Skeleton2 = 19,
	Bat1 = 20,
	Bat2 = 21,
	Mage1 = 22,
	Mage2 = 23,
	Player = 24,
	Traders1 = 25,
	Altar = 26,
	Thief = 27,
	Elder1 = 28,
	Gate = 29,
	Ironman = 30,
	Money = 32,
	Elder2 = 33,
	IronSword = 34,
	end = 99,
}eBase;

typedef int (*CollisionCB)(void* player, void* Base);

typedef int (*SaveCB)(_IN_OUT_ char* data,_IN_ void* Base);

int BaseSaveCB(_IN_OUT_ char* data, _IN_ void* base);

typedef struct sBase_
{
	eBase type;
	int y;
	int x;
	const char* name1;
	const char* name2;
	CollisionCB collisionCB;
	SaveCB saveCB;
}sBase;

typedef struct sSaveBase_
{
	eBase type;
	int y;
	int x;
}sSaveBase;

sBase* CreateWallCB(eBase type, int y, int x);

typedef struct sPlayer_
{
	sBase base;
	int floor;
	int maxfloor;
	int Attack;
	int defense;
	int HP;
	int money;
	int ykey;
	int bkey;
	int tpstick;
	int handbook;
	int tips;
}sPlayer;

sBase* CreatePlayerCB(eBase type, int y, int x);

sBase* CreateUPstairsCB(eBase type, int y, int x);

sBase* CreateDownstairsCB(eBase type, int y, int x);

sPlayer* Getplayer();

typedef sBase* (*CreateCB)(eBase type, int y, int x);

typedef void (*FRegCreateCB)(eBase type, CreateCB cb);

typedef struct sSceneCB_
{
	FRegCreateCB RegcreateCB;
}sSceneCB;

typedef char* (*FGetModuleName)();

typedef void (*FInitModule)(sSceneCB* sceneCB);

void INITRegCreateCB();

typedef struct sScene_ sScene;

typedef struct sSceneMgr_ sSceneMgr;

void InitMap();

sScene* GetNowScene();

sBase* FindSceneNode(sScene* Scene, int y, int x);

void ChangeFloor(sScene* Scene, sPlayer* player, int move);

void SaveScene(sScene* scene);

int TP();

void PrintScene(sScene* Scene);

void UpdateScene(sScene* Scene);

int Menu();

#endif