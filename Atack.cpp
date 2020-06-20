#include "DxLib.h"
#include "main.h"
#include "stage.h"
#include "player.h"
#include "keycheck.h"
#include "Atack.h"
#include "math.h"

ATACK Atack[ATACK_MAX];
ATACK ExAtack[EXATACK_MAX];

int AtackImage;
int AtackImage2;
int ExSound;
int ExSound2;
int FireSound;

int ExAtackImage;
int ExAtack1Image;
int ExAtack2Image;
int ExAtack3Image;
int rotawait;
int rotawait2;

void AtackSysinit(void)
{
	AtackImage = LoadGraph("image/くちばし - コピー.PNG", true);
	AtackImage2 = LoadGraph("image/人間 近距離.PNG", true);
	
}

void AtackInit(void)
{
	for (int i = 0; i < ATACK_MAX; i++)
	{
		Atack[i].flag = false;
		Atack[i].pos = { 0,0 };
		Atack[i].size = { 48,48 };
		Atack[i].size2 = { 48,24 };
		Atack[i].life = 0;
		Atack[i].lifeMax = 40;
		Atack[i].angle = 0;
		Atack[i].angle2 = 0;
		Atack[i].defaltangle = 0;
		Atack[i].moveDir = DIR_RIGHT;
		Atack[i].type = 0;
		Atack[i].Cnt = 0;
	}
}

void Atackcontrol(void)
{
	
	for (int i = 0; i < ATACK_MAX; i++)
	{
		if (Atack[i].flag == false)
		{
			Atack[i].angle2 = 0;
		}
		//Atack.angle2++;
		if ((Atack[i].flag)&&(Atack[i].life !=0))
		{
			Atack[i].life--;

			if (Atack[i].life <= 0)
			{
				Atack[i].flag = false;
				if ((!Atack[i].flag) && (Atack[i].type == 0))
				{
					if (player[0].flag)
					{
						player[0].AtackFlag = false;
					}
					if (player[2].flag)
					{
						player[2].AtackFlag = false;
					}
				}
				if ((!Atack[i].flag) && (Atack[i].type == 1))
				{
					if (player[1].flag)
					{
						player[1].AtackFlag = false;
					}
					if (player[3].flag)
					{
						player[3].AtackFlag = false;
					}
				}
			}
		}
		

		if (Atack[i].type == 1)
		{
			switch (Atack[i].moveDir)
			{
			case DIR_LEFT:
				Atack[i].angle2 -= DX_PI_F / 40;
				break;
			case DIR_RIGHT:
				Atack[i].angle2 += DX_PI_F / 40;
				break;
			default:
				break;
			}
		}
	
	}

}

void AtackStartup(XY pPos, MOVE_DIR pDir , int type)
{
	for (int i = 0; i < ATACK_MAX; i++)
	{
		if (!Atack[i].flag)
		{
			Atack[i].life = Atack[i].lifeMax;
			Atack[i].moveDir = pDir;
			Atack[i].type = (type % 2);
			Atack[i].Cnt++;
			if ((Atack[i].moveDir == DIR_RIGHT) && (Atack[i].type == 0))
			{
				Atack[i].pos = { pPos.x + 48 ,pPos.y - 10 };
				
			}
			if ((Atack[i].moveDir == DIR_LEFT) && (Atack[i].type == 0))
			{
				Atack[i].pos = { pPos.x - 48 ,pPos.y - 10 };

			}

			if ((Atack[i].moveDir == DIR_RIGHT) && (Atack[i].type == 1))
			{
				Atack[i].pos = { pPos.x + 50,pPos.y };
				Atack[i].angle2 = 2;

				Atack[i].type = 1;
				
			}
			if ((Atack[i].moveDir == DIR_LEFT) && (Atack[i].type == 1))
			{
				
				Atack[i].pos = { pPos.x -48,pPos.y  };
				Atack[i].angle2 = 7.5;
				Atack[i].type = 1;

			}


			Atack[i].flag = true;
			break;
		}
		
	}
}


void AtackDraw(void)
{
	
	for (int i = 0; i < ATACK_MAX; i++)
	{
		if (Atack[i].flag)
		{
			if ((Atack[i].moveDir == DIR_RIGHT)&&(Atack[i].type == 0))
			{
				DrawGraph(Atack[i].pos.x, Atack[i].pos.y, AtackImage, true);

				
			}
			if ((Atack[i].moveDir == DIR_LEFT) && (Atack[i].type == 0))
			{
				DrawTurnGraph(Atack[i].pos.x, Atack[i].pos.y, AtackImage, true);
				
			}
			if ((Atack[i].moveDir == DIR_RIGHT) && (Atack[i].type == 1))
			{
				DrawTurnGraph(Atack[i].pos.x, Atack[i].pos.y, AtackImage2, true);

			}
			if ((Atack[i].moveDir == DIR_LEFT) && (Atack[i].type == 1))
			{
				DrawGraph(Atack[i].pos.x, Atack[i].pos.y, AtackImage2, true);

			}
		}
	}

}


//必殺技
void ExAtackSysinit(void)
{
	ExAtackImage = LoadGraph("image/Ex2.PNG", true);
	ExAtack1Image = LoadGraph("image/Ex1.png",true);
	ExAtack2Image = LoadGraph("image/赤玉.png", true);
	ExAtack3Image = LoadGraph("image/鉄パイプ.png", true);
	ExSound = LoadSoundMem("Sound/ドリル.mp3");
	ExSound2 = LoadSoundMem("Sound/ハンマー着弾.mp3");
	FireSound = LoadSoundMem("Sound/赤玉射出.mp3", true);

}


void ExAtackInit(void)
{

	rotawait2 = 0;
	for (int i = 0; i < EXATACK_MAX; i++)
	{
		ExAtack[i].flag = false;
		ExAtack[i].pos = { 0,0 };
		ExAtack[i].size = { 96,48 };
		ExAtack[i].size2 = { 48,69 };
		ExAtack[i].life = 0;
		ExAtack[i].lifeMax = 80;
		ExAtack[i].angle = 0;
		ExAtack[i].defaltangle = 0;
		ExAtack[i].type = 0;
		ExAtack[i].moveDir = DIR_RIGHT;
	}
}


void ExAtackcontrol(void)
{
	int Cnt5 = 0;
	int movey = 0;
	for (int i = 0; i < EXATACK_MAX; i++)
	{
		if (ExAtack[i].flag == false)
		{
			ExAtack[i].angle = 0;
			rotawait2 = 0;
		}

		if (ExAtack[i].flag == true)
		{
			ExAtack[i].life--;

			if (ExAtack[i].life <= 0)
			{
				ExAtack[i].flag = false;
			}
			if (ExAtack[i].type == 0)
			{
				if (ExAtack[i].moveDir == DIR_RIGHT)
				{
					ExAtack[i].pos.x +=1;

				}
				if (ExAtack[i].moveDir == DIR_LEFT)
				{
					ExAtack[i].pos.x -=1;

				}
				
				
			}
			if (ExAtack[i].type == 1)
			{

				movey = 5;
				ExAtack[i].pos.y = ExAtack[i].pos.y + movey;
				if (ExAtack[i].pos.y + 65 > player[1].pos.y + 96)
				{

					movey = 0;
					ExAtack[i].pos.y = player[1].pos.y + 31;
					
					if (Cnt5 == 0)
					{
						PlaySoundMem(ExSound2, DX_PLAYTYPE_BACK);
					}
					Cnt5++;
				}
			}
			if (ExAtack[i].type == 2)
			{
				switch (ExAtack[i].moveDir)
				{
				case DIR_LEFT:
					ExAtack[i].pos.x -= ExAtack[i].movespeed;
					break;
				case DIR_RIGHT:
					ExAtack[i].pos.x += ExAtack[i].movespeed;
					break;
				default:
					break;
				}

			}
			if (ExAtack[i].type == 3)
			{
				switch (ExAtack[i].moveDir)
				{
				case DIR_LEFT:
					ExAtack[i].pos.x -= ExAtack[i].movespeed;
					break;
				case DIR_RIGHT:
					ExAtack[i].pos.x += ExAtack[i].movespeed;
					break;
				default:
					break;
				}

			}
		}

		if (ExAtack[i].flag)
		{
			rotawait2++;
		}

	
	}

}


void ExAtackStartup(XY pPos, MOVE_DIR pDir, int type)
{
	for (int i = 0; i < EXATACK_MAX; i++)
	{
		if (!ExAtack[i].flag)
		{
			ExAtack[i].moveDir = pDir;
			ExAtack[i].type = type;
			ExAtack[i].life = ExAtack[i].lifeMax;

			if (ExAtack[i].type == 0)
			{
				if (pDir == DIR_LEFT)
				{
					ExAtack[i].pos = { pPos.x - 48 ,pPos.y };
				}
				if (pDir == DIR_RIGHT)
				{
					ExAtack[i].pos = { pPos.x ,pPos.y };

				}
				PlaySoundMem(ExSound, DX_PLAYTYPE_BACK);
				
			}


			if (ExAtack[i].type == 1)
			{
				if (pDir == DIR_RIGHT)
				{
					ExAtack[i].pos = { pPos.x + 125,pPos.y - 100 };
				}
				if (pDir == DIR_LEFT)
				{
					ExAtack[i].pos = { pPos.x - 72,pPos.y - 100 };
				}
			}

			if (ExAtack[i].type == 2)
			{
				ExAtack[i].pos = { pPos.x,pPos.y };
				ExAtack[i].movespeed = 10;
				PlaySoundMem(FireSound, DX_PLAYTYPE_BACK);
			}
			if (ExAtack[i].type == 3)
			{
				ExAtack[i].pos = { pPos.x,pPos.y+36 };
				ExAtack[i].movespeed = 10;
			}

			ExAtack[i].flag = true;
			break;
		}
		
	}

}



void ExAtackDraw(void)
{
	int Exx = 0;
	for (int i = 0; i < EXATACK_MAX; i++)
	{

		if (ExAtack[i].flag == true)
		{
			if (ExAtack[i].moveDir == DIR_RIGHT)
			{
				Exx = -30;
			}
			if (ExAtack[i].moveDir == DIR_LEFT)
			{
				Exx = 20;
			}
			if ((ExAtack[i].moveDir == DIR_RIGHT) && (ExAtack[i].type == 0))
			{
				DrawGraph(ExAtack[i].pos.x, ExAtack[i].pos.y, ExAtackImage, true);

			}
			if ((ExAtack[i].moveDir == DIR_LEFT) && (ExAtack[i].type == 0))
			{
				DrawTurnGraph(ExAtack[i].pos.x/*-48*/, ExAtack[i].pos.y, ExAtackImage, true);

			}

			if (ExAtack[i].type == 1)
			{

				DrawRotaGraph(
					ExAtack[i].pos.x/* + Exx*/, ExAtack[i].pos.y/* - 30*/,
					2.0, 91.11, ExAtack1Image, true);


			}
			if (ExAtack[i].type == 2)
			{
				if (ExAtack[i].flag == true)
				{
					DrawGraph(ExAtack[i].pos.x - ExAtack[i].offsetSize.x,
						ExAtack[i].pos.y - ExAtack[i].offsetSize.y,
						ExAtack2Image, true);
				}
			}
			if ((ExAtack[i].moveDir == DIR_LEFT) && (ExAtack[i].type == 3))
			{
				DrawGraph(ExAtack[i].pos.x, ExAtack[i].pos.y, ExAtack3Image, true);
			}
			if ((ExAtack[i].moveDir == DIR_RIGHT) && (ExAtack[i].type == 3))
			{
				DrawTurnGraph(ExAtack[i].pos.x, ExAtack[i].pos.y, ExAtack3Image, true);
			}
		}

	}
}