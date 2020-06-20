#include "DxLib.h"
#include "main.h"
#include "stage.h"
#include "player.h"
#include "keycheck.h"
#include "Shot.h"

#define SHOT_LIFE_MAX  33

SHOT shot[SHOT_MAX];
int shotimage;
int shotimage2;

void ShotSysinit(void)
{
	shotimage = LoadGraph("image/óë.PNG", true);
	shotimage2 = LoadGraph("image/êlÇÃíeä€.png", true);
}
void ShotInit(void)
{
	for (int i = 0; i < SHOT_MAX; i++)
	{
		shot[i].flag = false;
		shot[i].pos = {0,0};
		shot[i].size = {24,24};
		shot[i].offsetSize = { shot[i].size.x / 2 , shot[i].size.y / 2 };
		shot[i].moveDir = DIR_RIGHT;
		shot[i].lifeMax = SHOT_LIFE_MAX;
		shot[i].type = 0;
		
	}
}

void Shotcontrol(void)
{

	for (int i = 0; i < SHOT_MAX; i++)
	{
		if (shot[i].flag == true)
		{
			shot[i].life--;
			if (shot[i].life <= 0)
			{
				shot[i].flag = false;
			}
			if (!IsPass(shot[i].pos))
			{
				shot[i].flag = false;
			}
			switch (shot[i].moveDir)
			{
			case DIR_LEFT:
				shot[i].pos.x -= shot[i].movespeed;
				break;
			case DIR_RIGHT:
				shot[i].pos.x += shot[i].movespeed;
				break;
			default:
				break;
			}

		}
	}
}

void BulletFire(XY pPos, MOVE_DIR pDir, int type)
{
	
	for (int i = 0; i < SHOT_MAX; i++)
	{
		if (!shot[i].flag)
		{
			shot[i].life = shot[i].lifeMax;
			shot[i].pos = { pPos.x,pPos.y };
			shot[i].moveDir = pDir;
			shot[i].movespeed = 5;
			shot[i].type = (type %2);
			shot[i].flag = true;

			break;
		}
				
	}
}
void ShotDraw(void)
{
	for (int i = 0; i < SHOT_MAX; i++)
	{
		if ((shot[i].flag == true)&&(shot[i].type == 0))
		{
			DrawGraph(shot[i].pos.x- shot[i].offsetSize.x,
				shot[i].pos.y -  shot[i].offsetSize.y,
				shotimage, true);
		}
		if((shot[i].flag == true) && (shot[i].type == 1))
		{
			DrawGraph(shot[i].pos.x - shot[i].offsetSize.x,
				shot[i].pos.y - shot[i].offsetSize.y,
				shotimage2, true);
		}
	}
	
}
SHOT Getshot(int i) {
	return shot[i];
}

void DeleteShot(int i) {
	shot[i].flag = false;
}

