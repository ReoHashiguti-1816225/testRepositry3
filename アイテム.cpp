#include "DxLib.h"

#include"main.h"
#include"アイテム.h"

CHARACTER ITEM;

int itemimage[ITEMMAX];
int RandCnt;
//int Typerand;
void iteminit()
{
	LoadDivGraph("image/アイテム.png",5,5,1,48,48,itemimage, true);

	ITEM.pos = {0,0};
	ITEM.flag = false;
	ITEM.tyep =  GetRand(5);
	RandCnt = 0;
	ITEM.Usetype = GetRand(4);
}

void itemUpdate()
{
	RandCnt++;




	if (ITEM.flag)
	{
		if (ITEM.tyep == 0)
		{
			ITEM.pos = { SCREEN_SIZE_X / 2,296};
		}

		if (ITEM.tyep == 1)
		{
			ITEM.pos = { 190 , 488 };
		}

		if (ITEM.tyep == 2)
		{
			ITEM.pos = { 100, 150 };
		}

		if (ITEM.tyep == 3)
		{
			ITEM.pos = { 330, 488 };
		}
		if (ITEM.tyep == 4)
		{
			ITEM.pos = { 596, 488 };
		}
		if (ITEM.tyep == 5)
		{
			ITEM.pos = { 500, 630 };
		}
	}
	
	if (RandCnt > 300)
	{
		ITEM.Usetype = GetRand(4);
		ITEM.tyep = GetRand(5);
		ITEM.flag = true;

		RandCnt = 0;
	}

}

void itemDraw()
{
	if (ITEM.flag)
	{
		DrawGraph(ITEM.pos.x, ITEM.pos.y, itemimage[ITEM.Usetype], true);


	}

}
