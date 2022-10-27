#define _CRT_SECURE_NO_WARNINGS
#include"header.h"
#include<stdio.h>
#include<stdlib.h>
#include<memory.h>

static sPlayer* s_Player;

static int PlayerSaveCB(_IN_OUT_ char* data, _IN_ sPlayer* player)
{
	int len = sizeof(sSaveBase) + sizeof(sPlayer) - sizeof(sBase);
	printf("%d", sizeof(sPlayer));
	if (data == NULL)
		return 0;
	BaseSaveCB(data, player);
	memcpy(data, &len, sizeof(int));
	memcpy(data + sizeof(sSaveBase)+4, &player->floor, 
		   sizeof(sPlayer) - sizeof(sBase));
	return len + 4;
}

sBase* CreatePlayerCB(eBase type, int y, int x)
{
	sPlayer* player = malloc(sizeof(sPlayer));
	s_Player = player;
	s_Player->base.type = type;
	s_Player->base.y = y;
	s_Player->base.x = x;
	s_Player->base.name1 = "\033[96m ¡ñ \033[0m";
	s_Player->base.name2 = "\033[96m©¦©ï¨d \033[0m";
	s_Player->base.collisionCB = NULL;
	s_Player->base.saveCB = PlayerSaveCB;
	player->floor = 1;
	player->maxfloor = 1;
	s_Player->Attack = 100;
	s_Player->defense = 100;
	s_Player->HP = 1000;
	s_Player->money = 0;
	s_Player->ykey = 0;
	s_Player->bkey = 0;
	s_Player->tpstick = 0;
	s_Player->handbook = 0;
	s_Player->tips = 0;
	return player;
}

sPlayer* Getplayer()
{
	return s_Player;
}