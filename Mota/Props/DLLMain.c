#include<stdio.h>
#include<stdlib.h>
#include"header.h"

static sSceneCB* s_sceneCB;

typedef struct sProp_
{
	sBase base;
}sProp;

static int PropCollisionCB(sPlayer* player, sProp* prop)
{
	switch (prop->base.type)
	{
	case Ykey:
	{
		free(prop);
		player->ykey++;
		printf("\033[30;50H你得到了黄钥匙   ");
		return 1;
	}; break;
	case Bkey:
	{
		free(prop);
		player->bkey++;
		printf("\033[30;50H你得到了蓝钥匙   ");
		return 1;
	}; break;
	case HP1:
	{
		free(prop);
		player->HP += 70;
		printf("\033[30;50H血量回复了100点！");
		return 1;
	}; break;
	case HP2:
	{
		free(prop);
		player->HP += 200;
		printf("\033[30;50H血量回复了200点！");
		return 1;
	}; break;
	case AttUP:
	{
		free(prop);
		player->Attack += 1;
		printf("\033[30;50H攻击力提升了1点！");
		return 1;
	}; break;
	case DefUP:
	{
		free(prop);
		player->defense += 2;
		printf("\033[30;50H防御力提升了2点！");
		return 1;
	}; break;
	case TPstick:
	{
		free(prop);
		player->tpstick++;
		printf("\033[30;50H获得了传送法杖！ ");
		return 1;
	}; break;
	case IronSword:
	{
		free(prop);
		player->Attack += 7;
		printf("\033[30;48H得到铁剑攻击力上升!");
		return 1;
	}; break;
	case HandBook:
	{
		free(prop);
		player->handbook++;
		printf("\033[30;50H获得了记事本！！  ");
		return 1;
	}; break;
	}
}

sBase* CreateYkeyCB(eBase type, int y, int x)
{
	sProp* ykey = malloc(sizeof(sProp));
	ykey->base.type = type;
	ykey->base.y = y;
	ykey->base.x = x;
	ykey->base.name1 = "    ";
	ykey->base.name2 = "\033[93m  ╫ \033[0m";
	ykey->base.collisionCB = PropCollisionCB;
	ykey->base.saveCB = NULL;
	return ykey;
}

sBase* CreateBkeyCB(eBase type, int y, int x)
{
	sProp* bkey = malloc(sizeof(sProp));
	bkey->base.type = type;
	bkey->base.y = y;
	bkey->base.x = x;
	bkey->base.name1 = "    ";
	bkey->base.name2 = "\033[94m  ╫ \033[0m";
	bkey->base.collisionCB = PropCollisionCB;
	bkey->base.saveCB = NULL;
	return bkey;
}

sBase* CreateHP1CB(eBase type, int y, int x)
{
	sProp* HP1 = malloc(sizeof(sProp));
	HP1->base.type = type;
	HP1->base.y = y;
	HP1->base.x = x;
	HP1->base.name1 = "\033[91m  ┳\033[0m";
	HP1->base.name2 = "\033[91m  □\033[0m";
	HP1->base.collisionCB = PropCollisionCB;
	HP1->base.saveCB = NULL;
	return HP1;
}

sBase* CreateHP2CB(eBase type, int y, int x)
{
	sProp* HP2 = malloc(sizeof(sProp));
	HP2->base.type = type;
	HP2->base.y = y;
	HP2->base.x = x;
	HP2->base.name1 = "\033[94m  ┳\033[0m";
	HP2->base.name2 = "\033[94m  □\033[0m";
	HP2->base.collisionCB = PropCollisionCB;
	HP2->base.saveCB = NULL;
	return HP2;
}

sBase* CreateAttUPCB(eBase type, int y, int x)
{
	sProp* AttUP = malloc(sizeof(sProp));
	AttUP->base.type = type;
	AttUP->base.y = y;
	AttUP->base.x = x;
	AttUP->base.name1 = "\033[91m  ┍\033[0m";
	AttUP->base.name2 = "\033[91m  □\033[0m";
	AttUP->base.collisionCB = PropCollisionCB;
	AttUP->base.saveCB = NULL;
	return AttUP;
}

sBase* CreateDefUPCB(eBase type, int y, int x)
{
	sProp* defUP = malloc(sizeof(sProp));
	defUP->base.type = type;
	defUP->base.y = y;
	defUP->base.x = x;
	defUP->base.name1 = "\033[94m  ┍\033[0m";
	defUP->base.name2 = "\033[94m  □\033[0m";
	defUP->base.collisionCB = PropCollisionCB;
	defUP->base.saveCB = NULL;
	return defUP;
}

sBase* CreateTPstickCB(eBase type, int y, int x)
{
	sProp* TPstick = malloc(sizeof(sProp));
	TPstick->base.type = type;
	TPstick->base.y = y;
	TPstick->base.x = x;
	TPstick->base.name1 = "\033[97m  ╦ \033[0m";
	TPstick->base.name2 = "\033[97m  ║ \033[0m";
	TPstick->base.collisionCB = PropCollisionCB;
	TPstick->base.saveCB = NULL;
	return TPstick;
}

sBase* CreateIronSwordCB(eBase type, int y, int x)
{
	sProp* ironsword = malloc(sizeof(sProp));
	ironsword->base.type = type;
	ironsword->base.y = y;
	ironsword->base.x = x;
	ironsword->base.name1 = "\033[97m  ╀ \033[0m";
	ironsword->base.name2 = "\033[97m  │ \033[0m";
	ironsword->base.collisionCB = PropCollisionCB;
	ironsword->base.saveCB = NULL;
	return ironsword;
}

sBase* CreateHandBookCB(eBase type, int y, int x)
{
	sProp* handbook = malloc(sizeof(sProp));
	handbook->base.type = type;
	handbook->base.y = y;
	handbook->base.x = x;
	handbook->base.name1 = "\033[91m ▉▊\033[0m";
	handbook->base.name2 = "\033[91m ▉▊\033[0m";
	handbook->base.collisionCB = PropCollisionCB;
	handbook->base.saveCB = NULL;
	return handbook;
}

sBase* CreateTipsCB(eBase type, int y, int x)
{
	sProp* tips = malloc(sizeof(sProp));
	tips->base.type = type;
	tips->base.y = y;
	tips->base.x = x;
	tips->base.name1 = "\033[91m    \033[0m";
	tips->base.name2 = "\033[91m:-D\033[0m";
	tips->base.collisionCB = PropCollisionCB;
	tips->base.saveCB = NULL;
	return tips;
}

_declspec(dllexport) char* GetModuleName()
{
	return "Props";
}

_declspec(dllexport) void InitModule(sSceneCB* sceneCB)
{
	s_sceneCB = sceneCB;
	s_sceneCB->RegcreateCB(Ykey, CreateYkeyCB);
	s_sceneCB->RegcreateCB(Bkey, CreateBkeyCB);
	s_sceneCB->RegcreateCB(HP1, CreateHP1CB);
	s_sceneCB->RegcreateCB(HP2, CreateHP2CB);
	s_sceneCB->RegcreateCB(AttUP, CreateAttUPCB);
	s_sceneCB->RegcreateCB(DefUP, CreateDefUPCB);
	s_sceneCB->RegcreateCB(TPstick, CreateTPstickCB);
	s_sceneCB->RegcreateCB(IronSword, CreateIronSwordCB);
	s_sceneCB->RegcreateCB(HandBook, CreateHandBookCB);
	s_sceneCB->RegcreateCB(Tips, CreateTipsCB);
}