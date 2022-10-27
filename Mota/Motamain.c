#include"header.h"
#include<stdio.h>
#include<stdlib.h>
#include<conio.h>

int main()
{
	printf("\033[?25l");
	INITRegCreateCB();
    InitMap();
	while (1)
	{
		PrintScene(GetNowScene());
		UpdateScene(GetNowScene());
	}
	return 0;
}

