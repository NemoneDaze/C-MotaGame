#define _CRT_SECURE_NO_WARNINGS
#include"header.h"
#include<stdio.h>
#include<stdlib.h>
#include<windows.h>
#include<string.h>
#include<memory.h>

/*
* 注册创建魔塔中元素的回调函数
*/
static g_save[1024];//存档路径
static sSceneCB s_sceneCB;
static CreateCB s_createCB[1024] = {NULL};

//static int BaseSaveCB(_IN_OUT_ char* buff, _IN_OUT_ int* len, void* base)
//{
//	sBase* Base = (sBase*)base;
//	sprintf(buff, "%d %d %d", Base->type, Base->y, Base->x);
//	int size = strlen(buff);
//	*len = size;
//	return size;
//}
int BaseSaveCB(_IN_OUT_ char* data, _IN_ void* base)
{
	int len = sizeof(sSaveBase);
	if (data == NULL)
		return 0;
	memcpy(data, &len, 4);
	memcpy(data+4, base, len);
	return len + 4;
}

int GetDirectory(char* path, int len)
{
	unsigned long size = GetCurrentDirectoryA(0, NULL);
	if (GetCurrentDirectoryA(len, path) == 0)
		return -1;
	return size;
}

void RegCreateCB(eBase type, CreateCB cb)
{
	s_createCB[type] = cb;
};

void INITRegCreateCB()
{
	RegCreateCB(UPstairs, CreateUPstairsCB); 
	RegCreateCB(DOWNstairs, CreateDownstairsCB);
	RegCreateCB(Player, CreatePlayerCB);

	s_sceneCB.RegcreateCB = RegCreateCB;


	char pathDir[1024] = "";
	int len = GetDirectory(pathDir, 1024);
	HANDLE hfind;
	WIN32_FIND_DATAA findData;
	LARGE_INTEGER size;
	char path[4096];
	sprintf(path, "%s\\plugins\\%s", pathDir, "*.dll");
	hfind = FindFirstFileA(path, &findData);
	if (hfind == INVALID_HANDLE_VALUE)
	{
		printf("Faild to find first file!\n");
		return;
	}
	do
	{
		if (strcmp(findData.cFileName, ".") == 0 || strcmp(findData.cFileName, "..") == 0)
		continue;
		if (findData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
			continue;
		else
		{
			char Path[1024];
			sprintf(Path, "%s//plugins//%s", pathDir, findData.cFileName);
			/*size.LowPart = findData.nFileSizeLow;
			size.HighPart = findData.nFileSizeHigh;*/
			HMODULE module = LoadLibraryA(Path);
			FInitModule InitModule = (FInitModule)GetProcAddress(module, "InitModule");
			InitModule(&s_sceneCB);
		}
	} while (FindNextFileA(hfind, &findData));
	FindClose(hfind);
}


/*
* 场景管理器
*/
typedef struct sSceneMgr_
{
	sScene* Scenes[1024];
	int floor;
}sSceneMgr;

static sSceneMgr Mgr = { {0},0 };

void PushSceneMgr(sSceneMgr* SceneMgr, sScene* scene)
{
	SceneMgr->Scenes[SceneMgr->floor] = scene;
	SceneMgr->floor++;
}

sSceneMgr* GetSceneMgr()
{
	return &Mgr;
}


/*
* 场景相关
*/
void NewScene(char* path, HANDLE hfind, WIN32_FIND_DATAA findData);

void RloadScene(char* path, HANDLE hfind, WIN32_FIND_DATAA findData);

typedef struct sScene_
{
	sBase** Base;
	int index;
	int maxindex;
	int Floor;
}sScene;

sScene* CreateScene()
{
	sScene* Scene = malloc(sizeof(sScene));
	Scene->Base = malloc(sizeof(sBase*) * 13);
	Scene->index = -1;
	Scene->Floor = Mgr.floor + 1;
	Scene->maxindex = 12;
	return Scene;
}

//void SaveScene(sScene* Scene)
//{
//	char name[1024];
//	sprintf(name, "%s\\%d.mapdata", g_save, Scene->Floor);
//	FILE* pfile = fopen(name, "wb");
//	for (int i = 0; i <= Scene-> index; i++)
//	{
//		if (!Scene->Base[i]->saveCB)
//		{
//			sBase* base = Scene->Base[i];
//			char data[1024];
//			int len = 1024;
//			BaseSaveCB(data, &len, base);
//			fprintf(pfile, "%x\n", data);
//		}
//		else
//		{
//			sBase* base = Scene->Base[i];
//			char data[1024];
//			int len = 1024;
//			base->saveCB(data, &len, base);
//			fprintf(pfile, "%x\n", data);
//		}
//	}
//	//fprintf(pfile, "%s\n", "999");
//	fclose(pfile);
//}
void SaveScene(sScene* Scene)
{
	char name[1024];
	sprintf(name, "%s\\%d.mapdata", g_save, Scene->Floor);
	FILE* pfile = fopen(name, "wb");
	for (int i = 0; i <= Scene->index; i++)
	{
		if (!Scene->Base[i]->saveCB)
		{
			sBase* base = Scene->Base[i];
			char data[1024];
			int len = BaseSaveCB(data, base);
			fwrite(data, 1, len, pfile);
		}
		else
		{
			sBase* base = Scene->Base[i];
			char data[1024];
			int len = base->saveCB(data, base);
			fwrite(data, 1, len, pfile);
		}
	}
	fclose(pfile);
}

void SaveAllScene()
{
	printf("\033[30;46H选择存档位置1或2");
	char pos = '0';
	char path[100];
	GetDirectory(path, 100);
	while (pos != '1' && pos != '2')
	{
		pos = _getch();
		switch (pos)
		{
		case '1':sprintf(g_save, "%s\\savedata\\%s", path, "save1"); break;
		case '2':sprintf(g_save, "%s\\savedata\\%s", path, "save2"); break;
		default:break;
		}
	} 
	for (int i = 0; i < Mgr.floor; i++)
		SaveScene(Mgr.Scenes[i]);
}

void PushSceneBase(sScene* Scene, sBase* Base)
{
	if (Scene->index == Scene->maxindex)
	{
		Scene->maxindex += 13;
		sBase** temp = malloc(sizeof(sBase*) * (Scene->maxindex + 1));
		for (int i = 0; i <= Scene->index; i++)
			temp[i] = Scene->Base[i];
		free(Scene->Base);
		Scene->Base = temp;
	}
	Scene->index++;
	Scene->Base[Scene->index] = Base;
}

void InitScene(int map[][13])
{
	sScene* Scene = CreateScene();
	for (int x = 0; x < 13; x++)
	{
		for (int y = 0; y < 13; y++)
		{
			if (map[x][y] != 31)
			{
				eBase type = map[x][y];
				if (!s_createCB[type])
					continue;
				PushSceneBase(Scene, s_createCB[type](type, x, y));
			}
		}
	}
	PushSceneMgr(&Mgr, Scene);
}

void SortMap(char* mappath[], int maxfloor)
{
	char* temp = NULL;
	for (int i = 1; i < maxfloor; i++)
	{
		for (int j = 0; j < maxfloor - i; j++)
		{
			if (strlen(mappath[j + 1]) < strlen(mappath[j]))
			{
				temp = mappath[j];
				mappath[j] = mappath[j + 1];
				mappath[j + 1] = temp;
				continue;
			}
			else if (strlen(mappath[j + 1]) == strlen(mappath[j]))
			{
				if (strcmp(mappath[j], mappath[j + 1]) > 0)
				{
					temp = mappath[j];
					mappath[j] = mappath[j + 1];
					mappath[j + 1] = temp;
				}
			}
		}
	}
}

void InitMap()
{
	char path[100] = "";
	char Path[200];
	GetDirectory(path, 100);
	HANDLE hfind;
	WIN32_FIND_DATAA findData;
	switch (Menu())
	{
	case 0: 
	{
		sprintf(Path, "%s\\map\\%s", path, "*.map");
		hfind = FindFirstFileA(Path, &findData);
		if (hfind == INVALID_HANDLE_VALUE)
		{
			puts("Falied to find first file!");
			return;
		}
		system("cls");
		NewScene(path, hfind, findData);
	}; break;
	case 1:
	{
		sprintf(Path, "%s\\savedata\\save1\\*.mapdata", path);
		sprintf(g_save, "%s\\savedata\\save1", path);
		hfind = FindFirstFileA(Path, &findData);
		if (hfind == INVALID_HANDLE_VALUE)
		{
			system("cls");
			puts("\033[16;52H无可用存档！！");
			puts("\033[17;52H开始新游戏！！");
			Sleep(1500);
			system("cls");
			sprintf(Path, "%s\\map\\%s", path, "*.map");
			hfind = FindFirstFileA(Path, &findData);
			NewScene(path, hfind, findData);
		}
		else
			RloadScene(g_save, hfind, findData);
	}; break;
	case 2:
	{
		sprintf(Path, "%s\\savedata\\save2\\*.mapdata", path);
		sprintf(g_save, "%s\\savedata\\save2", path);
		hfind = FindFirstFileA(Path, &findData);
		if (hfind == INVALID_HANDLE_VALUE)
		{
			system("cls");
			puts("\033[16;52H无可用存档！！");
			puts("\033[17;52H开始新游戏！！");
			Sleep(1500);
			system("cls");
			sprintf(Path, "%s\\map\\%s", path, "*.map");
			hfind = FindFirstFileA(Path, &findData);
			NewScene(path, hfind, findData);

		}
		else
			RloadScene(g_save, hfind, findData);
	}; break;
	}
}

void DestoryScene(sScene* Scene)
{
	free(Scene->Base);
	free(Scene);
	Scene = NULL;
}

sBase* FindSceneNode(sScene* Scene, int y, int x)
{
	for (int i = 0; i <= Scene->index; i++)
	{
		if (Scene->Base[i]->x == x && Scene->Base[i]->y == y)
		{
			return Scene->Base[i];
		}
	}
	return NULL;
}

sBase* FindSceneNode2(sScene* Scene, eBase type)
{
	for (int i = 0; i <= Scene->index; i++)
	{
		if (Scene->Base[i]->type == type)
		{
			return Scene->Base[i];
		}
	}
	return NULL;
}

void FindNewPlayer(sScene* Scene, int pos[2])
{
	int dir[4][2] = { {0,1}, {1,0}, {0,-1}, {-1,0} };
	int Y;
	int X;
	for (int i = 0; i < 4; i++)
	{
		Y = pos[0]+ dir[i][0];
		X = pos[1]+ dir[i][1];
		if (FindSceneNode(Scene, Y, X) == NULL)
			break;
	}
	pos[0] = Y;
	pos[1] = X;
}

int FindSceneindex(sScene* Scene, int y, int x)
{
	int target;
	for (int i = 0; i <= Scene->index; i++)
	{
		if (Scene->Base[i]->x == x && Scene->Base[i]->y == y)
		{
			target = i;
			return target;
		}
	}
	return 0;
}

void DelSceneNode(sScene* Scene, int target)
{
	for (int i = target; i < Scene->index; i++)
	{
		Scene->Base[i] = Scene->Base[i + 1];
	}
	Scene->index--;
}

void ChangeFloor(sScene* Scene,sPlayer* player,int move)
{
	int floor;
	int playerindex = FindSceneindex(Scene, player->base.y, player->base.x);
	DelSceneNode(Scene, playerindex);
	sBase* base = NULL;
	if (move == 3)
	{
		floor = Scene->Floor;
		base = FindSceneNode2(Mgr.Scenes[floor], DOWNstairs);
	}
	else
	{
		floor = Scene->Floor - 2;
		base = FindSceneNode2(Mgr.Scenes[floor], UPstairs);
	}
	int pos[2] = { base->y,base->x };
	FindNewPlayer(Mgr.Scenes[floor], pos);
	player->base.y = pos[0];
	player->base.x = pos[1];
	player->floor = floor + 1;
	PushSceneBase(Mgr.Scenes[floor], player);
	return;
}

sScene* GetNowScene()
{
	int floor = Getplayer()->floor;
	return Mgr.Scenes[floor - 1];
}

void NewScene(char* path, HANDLE hfind, WIN32_FIND_DATAA findData)
{
	char* mappath[50];
	int len = 0;
	do
	{
		if (findData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
			continue;
		if (strcmp(findData.cFileName, ".") == 0 || strcmp(findData.cFileName, "..") == 0)
			continue;
		char* floorpath = malloc(sizeof(char) * 200);
		sprintf(floorpath, "%s\\map\\%s", path, findData.cFileName);
		mappath[len] = floorpath;
		len++;
	} while (FindNextFileA(hfind, &findData));
	FindClose(hfind);
	SortMap(mappath, len);
	for (int i = 0; i < len; i++)
	{
		FILE* pfile = fopen(mappath[i], "r");
		int map[13][13] = { 0 };
		for (int x = 0; x < 13; x++)
		{
			for (int y = 0; y < 13; y++)
			{
				fscanf(pfile, "%d", &map[x][y]);
			}
		}
		InitScene(map);
		fclose(pfile);
	}
}

/*void RloadScene(char* path, HANDLE hfind, WIN32_FIND_DATAA findData)
{
	char* mappath[50];
	int len = 0;
	do
	{
		if (findData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
			continue;
		if (strcmp(findData.cFileName, ".") == 0 || strcmp(findData.cFileName, "..") == 0)
			continue;
		char* floorpath = malloc(sizeof(char) * 200);
		sprintf(floorpath, "%s\\%s", path, findData.cFileName);
		mappath[len] = floorpath;
		len++;
	} while (FindNextFileA(hfind, &findData));
	FindClose(hfind);
	SortMap(mappath, len);
	for (int i = 0; i < len; i++)
	{
		FILE* pfile = fopen(mappath[i], "r");
		char next[1024];
		int Data[1024];
		int type = 31;
		int y, x;
		sScene* Scene = CreateScene();
		while (1)
		{
			//fgets(pfile, "%s", data);
			//if (feof(pfile))
				//break;
			//sscanf(data, "%d %d %d", &Data[0], &Data[1], &Data[2]);
			//sBase* base = s_createCB[type](Data[0], Data[1], Data[2]);
			fscanf(pfile, "%d %d %d", &type, &y, &x);
			if(feof(pfile))
				break;
			sBase* base = s_createCB[type](type, y, x);
			if (type == Elder2)
			{
				int* attri = &base->collisionCB;
				attri += 4;
				fscanf(pfile, "%d", attri);
			}
			if (type == Player)
			{
				sPlayer* player = (sPlayer*)base;
				fscanf(pfile, "%d %d %d %d %d %d %d %d %d %d %d",
					&player->floor, &player->maxfloor, &player->Attack,
					&player->defense, &player->HP, &player->money, &player->ykey,
					&player->bkey, &player->tpstick, &player->handbook, &player->tips);
			}
			PushSceneBase(Scene,base);
			fgets(next, 1024, pfile);
		}
		PushSceneMgr(&Mgr, Scene);
		fclose(pfile);	
	}
}*/
void RloadScene(char* path, HANDLE hfind, WIN32_FIND_DATAA findData)
{
	char* mappath[50];
	int len = 0;
	do
	{
		if (findData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
			continue;
		if (strcmp(findData.cFileName, ".") == 0 || strcmp(findData.cFileName, "..") == 0)
			continue;
		char* floorpath = malloc(sizeof(char) * 200);
		sprintf(floorpath, "%s\\%s", path, findData.cFileName);
		mappath[len] = floorpath;
		len++;
	} while (FindNextFileA(hfind, &findData));
	FindClose(hfind);
	SortMap(mappath, len);
	for (int i = 0; i < len; i++)
	{
		FILE* pfile = fopen(mappath[i], "rb");
		char Data[1024];
		sScene* Scene = CreateScene();
		int datalen = 0;
		sBase base;
		while (1)
		{
			fread(&datalen, 4, 1, pfile);
			if (feof(pfile))
				break;
			fread(Data, datalen, 1, pfile);
			memcpy(&base, Data, sizeof(sSaveBase));
			sBase* Base = s_createCB[base.type](base.type, base.y, base.x);
			char* pos = Base;
			if (datalen == 20)
			{
				memcpy(pos + sizeof(sBase), Data + sizeof(sSaveBase), 4);
			}
			if (datalen > 20)
			{
				memcpy(pos + sizeof(sBase), Data + sizeof(sSaveBase),
					   sizeof(sPlayer) - sizeof(sBase));
			}
			PushSceneBase(Scene, Base);
		}
		PushSceneMgr(&Mgr, Scene);
		fclose(pfile);
	}
}

void PrintScene(sScene* Scene)
{
	for (int i = 0; i <= Scene->index; i++)
	{
		sBase* Base = Scene->Base[i];
		int Y = Base->y*2 + 3;
		int X = Base->x * 4 + 30;
		printf("\033[%d;%dH%s", Y, X, Base->name1);
		printf("\033[%d;%dH%s", Y+1, X, Base->name2);
	}
	sPlayer* player = Getplayer();
	printf("\033[6;16H血  量:%5d", player->HP);
	printf("\033[8;16H攻击力:%5d", player->Attack);
	printf("\033[10;16H防御力:%5d", player->defense);
	printf("\033[12;16H金  钱:%5d", player->money);
	printf("\033[7;86H黄钥匙: % 3d", player->ykey);
	printf("\033[11;86H蓝钥匙:%3d", player->bkey);
	printf("\033[24;86H当前楼层:%2d层", player->floor);
	printf("\033[14;16H主动道具");
	if (player->tpstick > 0)
	{
		printf("\033[16;12H\033[97m  ╦ \033[0m");
		printf("\033[17;12H\033[97m  ║ \033[0m");
		printf("\033[16;18H传送法杖\033[17;16H楼梯口按j使用");
	}
	if (player->tips > 0)
	{
		printf("\033[19;14H\033[91m:-D\033[0m");
		printf("\033[19;18H怪物手册\033[20;18H按k使用");
	}
	if (player->handbook > 0)
	{
		printf("\033[22;14H\033[91m▉▊\033[0m");
		printf("\033[23;14H\033[91m▉▊\033[0m");
		printf("\033[22;18H记事本\033[23;18H害没做完呢");
	}		
}

void UpdateScene(sScene* Scene)
{
	sPlayer* player = Getplayer();
	char dir = _getch();
	printf("\033[30;45H                          ");
	int Y = player->base.y;
	int X = player->base.x;
	int move = 1;
	switch (dir)
	{
	case 'W':
	case 'w':Y -= 1; break;
	case 'A':
	case 'a':X -= 1; break;
	case 'S':
	case 's':Y += 1; break;
	case 'd':
	case 'D':X += 1; break;
	case 'j':
	case 'J':move = TP(); break;
	case 'k':
	case 'K':move = Illustrated(); break;
	case 'l':
	case 'L': 
	{
		SaveAllScene();
		printf("\033[30;46H      存档成功！");
	}; break;
	default:return;break;
	}
	sBase* Base = FindSceneNode(Scene, Y, X);
	int target = FindSceneindex(Scene, Y, X);
	if (move > 1)
		return;
	if (Base != NULL)
	{
		if (Base == player)
			return;
		else
			move = Base->collisionCB(player, Base);
	}
	if (move == 1)
	{
		int YY = player->base.y * 2 + 3;
		int XX = player->base.x * 4 + 30;
		printf("\033[%d;%dH    \033[%d;%dH    ", YY, XX, YY + 1, XX);
		player->base.y = Y;
		player->base.x = X;
		if (Base != NULL)
			DelSceneNode(Scene, target);	
	}
}


/*
* 演出
*/
static int firstsight = 1;
static int awake = 1;

void Firstsight()
{
	sPlayer* player = Getplayer();
	if (3 == player->floor && 9 == player->base.y && 6 == player->base.x)
	{

	}


}