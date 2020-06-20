#include "DxLib.h"
#include "main.h"
#include "stage.h"
#include "math.h"
#include "keycheck.h"
#include "player.h"



#ifdef _DEBUG
#define AST() {\
	CHAR ast_mes[256];\
	wsprintf(ast_mes, "%s %d�s��\0", __FILE__, __LINE__);\
	MessageBox(0, ast_mes, "���ĕ\��", MB_OK);\
	}
#else
#define AST()
#endif		

int mapimage[1];
int BgImage;
int Stage1[CHIP_MAX_Y][CHIP_MAX_X];


XY mappos;
XY move;
XY playerpos;
//XY mapoffset;


//�}�b�v
int mapData[15][20] = {
{ 0,3, 3, 3, 3, 3, 3,  3, 3, 3, 3, 3, 3,  3, 3, 3, 3, 3, 3, 0},
{ 0,3, 3, 3, 3, 3, 3,  3, 3, 3, 3, 3, 3,  3, 3, 3, 3, 3, 3, 0},
{ 0,3, 3, 3, 3, 3, 3,  3, 3, 3, 3, 3, 3,  3, 3, 3, 3, 3, 3, 0},
{ 0,3, 3, 3, 3, 3, 3,  3, 3, 3, 3, 3, 3,  3, 3, 3, 3, 3, 3, 0},
{ 0,1, 1, 1, 1, 3, 3,  3, 3, 3, 3, 3, 3,  3, 3, 1, 1, 1, 1, 0},
{ 0,3, 3, 3, 3, 3, 3,  3, 3, 3, 3, 3, 3,  3, 3, 3, 3, 3, 3, 0},
{ 0,3, 3, 3, 3, 3, 3,  3, 3, 3, 3, 3, 3,  3, 1, 1, 1, 1, 3, 0},
{ 0,3, 3, 3, 3, 3, 3,  3, 1, 1, 1, 1, 3,  3, 3, 3, 3, 1, 3, 0},
{ 0,3, 3, 3, 3, 3, 3,  3, 3, 3, 3, 3, 3,  3, 3, 3, 3, 1, 3, 0},
{ 0,3, 3, 3, 3, 3, 3,  3, 3, 3, 3, 3, 3,  3, 3, 3, 3, 3, 3, 0},
{ 0,3, 3, 3, 3, 3, 3,  3, 3, 3, 3, 3, 3,  3, 3, 3, 3, 3, 3, 0},
{ 0,3, 3, 1, 1, 1, 1,  1, 3, 3, 3, 3, 1,  1, 1, 1, 1, 3, 3, 0},
{ 0,3, 3, 3, 3, 3, 3,  3, 3, 3, 3, 3, 3,  3, 3, 3, 3, 3, 3, 0},
{ 0,3, 3, 3, 3, 3, 3,  3, 3, 3, 3, 3, 3,  3, 3, 3, 3, 3, 3, 0},
{ 1, 1, 1, 1, 1, 1,  1, 1, 1, 1, 1, 1,  1, 1, 1, 1,1, 1, 1, 1},
};

void StageSystemInit(void)
{
	BgImage = LoadGraph("image/�w�i.jpg", true);

	LoadDivGraph("image/����.png", 2, 2, 1,MAP_CHIP_SIZE_X,MAP_CHIP_SIZE_Y,mapimage,true);
	move = { 6,4 };
}



void StageDraw(void)
{
	//DrawGraph(0, 0, BgImage, true);

	//DrawBox(0, 0, SCREEN_SIZE_X, SCREEN_SIZE_Y, 0xffffff, true);
	if (mappos.x <= 0)
	{
		mappos.x = 0;
	}
	if (mappos.x >= SCREEN_SIZE_X)
	{
		mappos.x = SCREEN_SIZE_X;
	}

	for (int x = 0; x < CHIP_MAX_X; x++)
	{
		for (int y = 0; y < CHIP_MAX_Y; y++)
		{
			//DrawLine(x * MAP_CHIP_SIZE_X, y * MAP_CHIP_SIZE_Y, x * MAP_CHIP_SIZE_X, 32 , 0xffff00);
			//DrawLine(x * MAP_CHIP_SIZE_X, y * MAP_CHIP_SIZE_Y, 32, y * MAP_CHIP_SIZE_Y, 0xffff00);
			DrawGraph(x * MAP_CHIP_SIZE_X - mappos.x, y * MAP_CHIP_SIZE_Y, mapimage[mapData[y][x]],true);
			
		}
	}

}

//�ȉ��Q�̓L�����̑������u���b�N�Ƀs�b�^�����邽�߂ɕK�v�ȃ��m
XY mapPosToIndex(XY pos)
{
	XY mapIndex;
	mapIndex = { pos.x / MAP_CHIP_SIZE_X,pos.y / MAP_CHIP_SIZE_Y };
	return mapIndex;
}

XY mapIndexToPos(XY index)
{
	XY mappos;
	mappos = { index.x  * MAP_CHIP_SIZE_X,index.y  * MAP_CHIP_SIZE_Y };

	return mappos;
}


XY mapPosToMoveIndex(XY pos, bool flag, XY_F velocity) {

	XY tmpIndex;
	XY tmpPos;
	tmpIndex = mapPosToIndex(pos);

	if (flag) {
		tmpIndex.y++;
	}
	if (velocity.x < 0) {			// ��
		tmpIndex.x++;
	}
	tmpPos = mapIndexToPos(tmpIndex);

	return tmpPos;
}


//XY mapPosToMoveIndexpos(XY pos, MOVE_DIR dir)
//{
//	XY mapIndex;
//	mapIndex = { pos.x / MAP_CHIP_SIZE_X,pos.y / MAP_CHIP_SIZE_Y };
//	if (dir == DIR_UP)
//	{
//
//	}
//	else if (dir == DIR_RIGHT)
//	{
//
//	}
//
//	else if (dir == DIR_LEFT)
//	{
//
//	}
//	return mapIndex;
//}

bool IsPass(XY pos)
{
	bool ret = true;
	int mapno;
	
	XY mapIndex;

	mapIndex = mapPosToIndex(pos);
	mapno = mapData[mapIndex.y][mapIndex.x];

	switch (mapno)
	{
	
	case 0:
	case 1:
	
			ret = false;
		break;
	}
	return ret;
}




//bool playerEXmove(XY pos)
//{
//	bool ret = false;
//	int mapno;
//	XY mapIndex;
//
//
//	mapIndex = mapPosToIndex(pos);
//	mapno = mapData[mapIndex.y][mapIndex.x];
//
//	
//		switch(mapno)
//		{
//			
//		case 24://�ŏ�
//		case 25:
//		case 26:
//		case 42:
//		case 43:
//		case 44:
//		case 51://�r
//		case 52:
//		case 53:
//		case 60:
//		case 61:
//		case 62:
//		case 69:
//		case 70:
//		case 71:
//			ret = true;
//		break;
//	}
//
//		return ret;
//}

