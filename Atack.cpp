#include "DxLib.h"
#include "main.h"
#include "stage.h"
#include "player.h"
#include "keycheck.h"
#include "Atack.h"
#include "math.h"

ATACK Atack/*[PLAYER_TYPE]*/;
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

//通常攻撃
void AtackSysinit(void)
{
	AtackImage = LoadGraph("image/くちばし - コピー.PNG", true);
	AtackImage2 = LoadGraph("image/人間 近距離.PNG", true);
	
}

void AtackInit(void)
{
	for (int i = 0; i < PLAYER_TYPE; i++)
	{
		Atack.flag = false;
		Atack.pos = { 0,0 };
		Atack.size = { 48,48 };
		Atack.size2 = { 48,24 };
		Atack.life = 0;
		Atack.lifeMax = 40;
		Atack.angle = 0;
		Atack.angle2 = 0;
		Atack.defaltangle = 0;
		Atack.moveDir = DIR_RIGHT;
		Atack.type = 0;
		Atack.Cnt = 0;
	}
}

void Atackcontrol(void)
{
	
	for (int i = 0; i < PLAYER_TYPE; i++)
	{
		if (Atack.flag == false)
		{
			Atack.angle2 = 0;
		}
		//Atack.angle2++;
		if ((Atack.flag == true)&&(Atack.life !=0))
		{
			Atack.life--;

			if (Atack.life <= 0)
			{
				Atack.flag = false;
			}
		}
		/*if (Atack.type == 0)
		{
		
			if (Atack.moveDir == DIR_RIGHT)
			{
				i = i % 2;
				Atack.pos.x = Atack.pos.x + 2;
				if (Atack.pos.x > player[i].pos.x + 48)
				{
					Atack.pos.x = player[i].pos.x + 48;
				}
			}
			if (Atack.moveDir == DIR_LEFT)
			{
				i = i % 2;
				Atack.pos.x = Atack.pos.x - 2;

				if (Atack.pos.x <= player[i].pos.x)
				{
					Atack.pos.x = player[i].pos.x ;
				}
			}
		}*/

		if (Atack.type == 1)
		{
			switch (Atack.moveDir)
			{
			case DIR_LEFT:
				Atack.angle2 -= DX_PI_F / 40;
				break;
			case DIR_RIGHT:
				Atack.angle2 += DX_PI_F / 40;
				break;
			default:
				break;
			}
		}
	}
}

void AtackStartup(XY pPos, MOVE_DIR pDir , int type)
{
	for (int i = 0; i < PLAYER_TYPE; i++)
	{
		if (!Atack.flag)
		{
			Atack.life = Atack.lifeMax;
			Atack.moveDir = pDir;
			Atack.type = (type % 2);
			//ExAtack.movespeed = 5;
			Atack.Cnt++;
			if ((Atack.moveDir == DIR_RIGHT) && (Atack.type == 0))
			{
				Atack.pos = { pPos.x + 48 ,pPos.y - 10 };
				
			}
			if ((Atack.moveDir == DIR_LEFT) && (Atack.type == 0))
			{
				Atack.pos = { pPos.x - 48 ,pPos.y - 10 };

			}

			if ((Atack.moveDir == DIR_RIGHT) && (Atack.type == 1))
			{
				Atack.pos = { pPos.x + 50,pPos.y };
				Atack.angle2 = 2;

				Atack.type = 1;
				
			}
			if ((Atack.moveDir == DIR_LEFT) && (Atack.type == 1))
			{
				
				Atack.pos = { pPos.x -48,pPos.y  };
				Atack.angle2 = 7.5;
				Atack.type = 1;

			}


			Atack.flag = true;

		}
	}
}


void AtackDraw(void)
{
	
	for (int i = 0; i < PLAYER_TYPE; i++)
	{
		if (Atack.flag)
		{
			if ((Atack.moveDir == DIR_RIGHT)&&(Atack.type == 0))
			{
				DrawGraph(Atack.pos.x, Atack.pos.y, AtackImage, true);

				////以下デバッグ
				//DrawBox(Atack.pos.x,
				//	Atack.pos.y,
				//	Atack.pos.x +5,
				//	Atack.pos.y + Atack.size.y ,
				//	0xffffff, true);

				//DrawBox(Atack.pos.x + 5,
				//	Atack.pos.y+2,
				//	Atack.pos.x + 10,
				//	Atack.pos.y +47,
				//	0x00ffff, true);

				//DrawBox(Atack.pos.x + 10,
				//	Atack.pos.y + 5,
				//	Atack.pos.x + 15,
				//	Atack.pos.y + 45,
				//	0xff00ff, true);
				//DrawBox(Atack.pos.x + 15,
				//	Atack.pos.y + 8,
				//	Atack.pos.x + 20,
				//	Atack.pos.y + 43,
				//	0xff00ff, true);
				//DrawBox(Atack.pos.x + 20,
				//	Atack.pos.y + 11,
				//	Atack.pos.x + 25,
				//	Atack.pos.y + 39,
				//	0xff00ff, true);
				//DrawBox(Atack.pos.x + 25,
				//	Atack.pos.y + 14,
				//	Atack.pos.x + 30,
				//	Atack.pos.y + 36,
				//	0xff00ff, true);
				//DrawBox(Atack.pos.x + 30,
				//	Atack.pos.y + 17,
				//	Atack.pos.x + 35,
				//	Atack.pos.y + 33,
				//	0xff00ff, true);
				//DrawBox(Atack.pos.x + 35,
				//	Atack.pos.y + 20,
				//	Atack.pos.x + 40,
				//	Atack.pos.y + 30,
				//	0xff00ff, true);
				//DrawBox(Atack.pos.x + 40,
				//	Atack.pos.y + 23,
				//	Atack.pos.x + 45,
				//	Atack.pos.y + 27,
				//	0xff00ff, true);
				
			}
			if ((Atack.moveDir == DIR_LEFT) && (Atack.type == 0))
			{
				DrawTurnGraph(Atack.pos.x, Atack.pos.y, AtackImage, true);

				//以下デバッグ
			/*	DrawBox(Atack.pos.x,
					Atack.pos.y+23,
					Atack.pos.x + 5,
					Atack.pos.y +27,
					0xffffff, true);
				DrawBox(Atack.pos.x + 5,
					Atack.pos.y+20,
					Atack.pos.x + 10,
					Atack.pos.y +30,
					0x00ffff, true);

				DrawBox(Atack.pos.x + 10,
					Atack.pos.y + 17,
					Atack.pos.x + 15,
					Atack.pos.y + 33,
					0xff00ff, true);
				DrawBox(Atack.pos.x + 15,
					Atack.pos.y + 14,
					Atack.pos.x + 20,
					Atack.pos.y + 36,
					0xff00ff, true);
				DrawBox(Atack.pos.x + 20,
					Atack.pos.y + 11,
					Atack.pos.x + 25,
					Atack.pos.y + 39,
					0xff00ff, true);
				DrawBox(Atack.pos.x + 25,
					Atack.pos.y + 8,
					Atack.pos.x + 30,
					Atack.pos.y + 42,
					0xff00ff, true);
				DrawBox(Atack.pos.x + 30,
					Atack.pos.y +  5,
					Atack.pos.x + 35,
					Atack.pos.y + 45,
					0xff00ff, true);

				DrawBox(Atack.pos.x + 35,
					Atack.pos.y + 2,
					Atack.pos.x + 40,
					Atack.pos.y + 47,
					0xff00ff, true);
				DrawBox(Atack.pos.x + 40,
					Atack.pos.y,
					Atack.pos.x + 45,
					Atack.pos.y + Atack.size.y,
					0xff00ff, true);*/
				
			}
			if ((Atack.moveDir == DIR_RIGHT) && (Atack.type == 1))
			{
				DrawTurnGraph(Atack.pos.x, Atack.pos.y, AtackImage2, true);

			/*	DrawBox(Atack.pos.x,
					Atack.pos.y +15,
					Atack.pos.x +12,
					Atack.pos.y + Atack.size2.y,
					0xff00ff, true);	
				DrawBox(Atack.pos.x + 12,
					Atack.pos.y + 15,
					Atack.pos.x + 20,
					Atack.pos.y + Atack.size2.y,
					0xff0000, true);
				DrawBox(Atack.pos.x + 20,
					Atack.pos.y + 15,
					Atack.pos.x + 28,
					Atack.pos.y + Atack.size2.y,
					0x000000, true);
				DrawBox(Atack.pos.x + 28,
					Atack.pos.y + 15,
					Atack.pos.x + 36,
					Atack.pos.y + Atack.size2.y,
					0x0000ff, true);
				DrawBox(Atack.pos.x + 36,
					Atack.pos.y + 4,
					Atack.pos.x + 44,
					Atack.pos.y + Atack.size2.y,
					0x0000ff, true);
				DrawBox(Atack.pos.x + 37,
					Atack.pos.y + 15,
					Atack.pos.x + 45,
					Atack.pos.y + Atack.size2.y,
					0x0000ff, true);*/
				
				
				//枝振る
				/*DrawRotaGraph2(Atack.pos.x, Atack.pos.y,
					48,12,1.0, Atack.angle2, AtackImage2, true);

				DrawBox(Atack.pos.x,
					Atack.pos.y - 15,
					Atack.pos.x + Atack.size2.x,
					Atack.pos.y + Atack.size2.y+5 ,
					0xffffff, true);*/
			}
			if ((Atack.moveDir == DIR_LEFT) && (Atack.type == 1))
			{
				DrawGraph(Atack.pos.x, Atack.pos.y, AtackImage2, true);

	/*			DrawBox(Atack.pos.x +44,
					Atack.pos.y + 15,
					Atack.pos.x + 52,
					Atack.pos.y + Atack.size2.y,
					0xff00ff, true);

			DrawBox(Atack.pos.x + 36,
					Atack.pos.y + 15,
					Atack.pos.x + 44,
					Atack.pos.y + Atack.size2.y,
					0xff0000, true);

	
				DrawBox(Atack.pos.x + 28,
					Atack.pos.y + 15,
					Atack.pos.x + 36,
					Atack.pos.y + Atack.size2.y,
					0x000000, true);
				DrawBox(Atack.pos.x + 20,
					Atack.pos.y + 15,
					Atack.pos.x + 28,
					Atack.pos.y + Atack.size2.y,
					0x0000ff, true);


				DrawBox(Atack.pos.x + 12,
					Atack.pos.y + 15,
					Atack.pos.x + 20,
					Atack.pos.y + Atack.size2.y,
					0x0000ff, true);

				DrawBox(Atack.pos.x + 10,
					Atack.pos.y + 4,
					Atack.pos.x + 16,
					Atack.pos.y + Atack.size2.y,
					0xffffff, true);
				DrawBox(Atack.pos.x + 4,
					Atack.pos.y + 4,
					Atack.pos.x + 10,
					Atack.pos.y + Atack.size2.y,
					0xffffff, true);

				DrawBox(Atack.pos.x,
					Atack.pos.y + 15,
					Atack.pos.x + 4,
					Atack.pos.y + Atack.size2.y,
					0x0000ff, true);*/



				//枝振る
				//DrawRotaGraph2(Atack.pos.x, Atack.pos.y,
				//	48,12,1.0, Atack.angle2, AtackImage2, true);
				//DrawBox(Atack.pos.x, Atack.pos.y,
				//	Atack.pos.x - Atack.size2.x, Atack.pos.y - Atack.size2.y ,
				//	0xffffff, true);
			}
		}
	}
	//DrawFormatString(0, 136, 0xffffff, "Atack.angle  = %d", Atack.angle2);
	//DrawFormatString(0, 400, 0xffffff, "Atack.Cnt  = %d", Atack.Cnt);

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
		//ExAtack.lifeMax = SHOT_LIFE_MAX;
		//shot[i].type = HIT_SHOT;	
		//ExAtack.offsetSize = { shot[i].size.x / 2 , shot[i].size.y / 2 };
		//break;
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
					ExAtack[i].pos.x = ExAtack[i].pos.x+1;
					if (ExAtack[i].pos.x > player[i].pos.x+48)
					{
						ExAtack[i].pos.x = player[i].pos.x + 48;
					}
				}
				if (ExAtack[i].moveDir == DIR_LEFT)
				{
					ExAtack[i].pos.x = ExAtack[i].pos.x - 1;
					if (ExAtack[i].pos.x <= player[i].pos.x - 96)
					{
						ExAtack[i].pos.x = player[i].pos.x - 96;
					}
				}
				
				
			}
			//ハンマー振る版
			/*if (rotawait2 > 50)
			{
				switch (ExAtack[i].moveDir)
				{
				case DIR_LEFT:
					ExAtack[i].angle -= DX_PI_F / 30;
					break;
				case DIR_RIGHT:
					ExAtack[i].angle += DX_PI_F / 30;
					break;
				default:
					break;
				}
			}*/
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
				/*if (ExAtack[i].moveDir == DIR_RIGHT)
				{
					ExAtack[i].pos.x = ExAtack[i].pos.x + 1;
					if (ExAtack[i].pos.x > player[i].pos.x + 48)
					{
						ExAtack[i].pos.x = player[i].pos.x + 48;
					}
				}
				if (ExAtack[i].moveDir == DIR_LEFT)
				{
					ExAtack[i].pos.x = ExAtack[i].pos.x - 1;
					if (ExAtack[i].pos.x <= player[i].pos.x - 96)
					{
						ExAtack[i].pos.x = player[i].pos.x - 96;
					}
				}*/
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



			//ハンマー振る版
		/*	if (ExAtack[i].type == 1)
			{
				if (pDir == DIR_RIGHT)
				{
					ExAtack[i].pos = { pPos.x + 70,pPos.y + 10 };
				}
				if (pDir == DIR_LEFT)
				{
					ExAtack[i].pos = { pPos.x - 7,pPos.y + 10 };
				}
			}*/

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
				//PlaySoundMem(FireSound, DX_PLAYTYPE_BACK);
			}
			//ExAtack.movespeed = 5;

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
			//DrawGraph(ExAtack.pos.x, ExAtack.pos.y, ExAtackImage, true);
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

				/*	DrawBox(ExAtack[i].pos.x,
						ExAtack[i].pos.y,
						ExAtack[i].pos.x + 10,
						ExAtack[i].pos.y + ExAtack[i].size.y,
						0xff00ff, false);

					DrawBox(ExAtack[i].pos.x + 10,
						ExAtack[i].pos.y + 2,
						ExAtack[i].pos.x + 20,
						ExAtack[i].pos.y + 47,
						0x00ffff, false);

					DrawBox(ExAtack[i].pos.x + 20,
						ExAtack[i].pos.y + 5,
						ExAtack[i].pos.x + 30,
						ExAtack[i].pos.y + 45,
						0xff00ff, false);
					DrawBox(ExAtack[i].pos.x + 30,
						ExAtack[i].pos.y + 8,
						ExAtack[i].pos.x + 40,
						ExAtack[i].pos.y + 43,
						0xff00ff, false);
					DrawBox(ExAtack[i].pos.x + 40,
						ExAtack[i].pos.y + 11,
						ExAtack[i].pos.x + 50,
						ExAtack[i].pos.y + 39,
						0xff00ff, false);
					DrawBox(ExAtack[i].pos.x + 50,
						ExAtack[i].pos.y + 14,
						ExAtack[i].pos.x + 60,
						ExAtack[i].pos.y + 36,
						0xff00ff, false);
					DrawBox(ExAtack[i].pos.x + 60,
						ExAtack[i].pos.y + 17,
						ExAtack[i].pos.x + 70,
						ExAtack[i].pos.y + 33,
						0xff00ff, false);
					DrawBox(ExAtack[i].pos.x + 70,
						ExAtack[i].pos.y + 20,
						ExAtack[i].pos.x + 80,
						ExAtack[i].pos.y + 30,
						0xff00ff, false);
					DrawBox(ExAtack[i].pos.x + 80,
						ExAtack[i].pos.y + 23,
						ExAtack[i].pos.x + 90,
						ExAtack[i].pos.y + 27,
						0xff00ff, false);*/
			}
			if ((ExAtack[i].moveDir == DIR_LEFT) && (ExAtack[i].type == 0))
			{
				DrawTurnGraph(ExAtack[i].pos.x/*-48*/, ExAtack[i].pos.y, ExAtackImage, true);

				/*	DrawBox(ExAtack[i].pos.x + 5,
						ExAtack[i].pos.y + 24,
						ExAtack[i].pos.x + 10,
						ExAtack[i].pos.y + 26,
						0x000000, true);

					DrawBox(ExAtack[i].pos.x + 10,
						ExAtack[i].pos.y + 23,
						ExAtack[i].pos.x + 20,
						ExAtack[i].pos.y + 27,
						0xffffff, false);
					DrawBox(ExAtack[i].pos.x + 20,
						ExAtack[i].pos.y + 20,
						ExAtack[i].pos.x + 30,
						ExAtack[i].pos.y + 30,
						0xff00ff, false);
					DrawBox(ExAtack[i].pos.x + 30,
						ExAtack[i].pos.y + 17,
						ExAtack[i].pos.x + 40,
						ExAtack[i].pos.y + 33,
						0xff00ff, false);

					DrawBox(ExAtack[i].pos.x + 40,
						ExAtack[i].pos.y + 14,
						ExAtack[i].pos.x + 50,
						ExAtack[i].pos.y + 36,
						0xff00ff, false);
					DrawBox(ExAtack[i].pos.x + 50,
						ExAtack[i].pos.y + 11,
						ExAtack[i].pos.x + 60,
						ExAtack[i].pos.y + 39,
						0xff00ff, false);

					DrawBox(ExAtack[i].pos.x + 60,
						ExAtack[i].pos.y + 8,
						ExAtack[i].pos.x + 70,
						ExAtack[i].pos.y + 43,
						0xff00ff, false);
					DrawBox(ExAtack[i].pos.x + 70,
						ExAtack[i].pos.y + 5,
						ExAtack[i].pos.x + 80,
						ExAtack[i].pos.y + 45,
						0xff00ff, false);
					DrawBox(ExAtack[i].pos.x + 80,
						ExAtack[i].pos.y + 2,
						ExAtack[i].pos.x + 95,
						ExAtack[i].pos.y + 47,
						0xff00ff, false);*/
			}

			if (ExAtack[i].type == 1)
			{

				//ハンマー振る版
				//DrawRotaGraph(ExAtack.pos.x+ Exx, ExAtack.pos.y-30, 2.0, ExAtack.angle, ExAtackImage, true);
				//DrawRotaGraph2(
				//	ExAtack[i].pos.x + Exx, ExAtack[i].pos.y - 30,
				//	24, 69,
				//	2.0, ExAtack[i].angle, ExAtack1Image, true);
				/*if (ExAtack[i].moveDir == DIR_LEFT)
				{*/
				DrawRotaGraph(
					ExAtack[i].pos.x/* + Exx*/, ExAtack[i].pos.y/* - 30*/,
					2.0, 91.11, ExAtack1Image, true);
				/*}*/
				/*if (ExAtack[i].moveDir == DIR_RIGHT)
				{
					DrawRotaGraph(
						ExAtack[i].pos.x + Exx, ExAtack[i].pos.y - 30,
						2.0, 91.11, ExAtack1Image, true);
				}*/


				if (ExAtack[i].moveDir == DIR_RIGHT)
				{



					//DrawBox(ExAtack[i].pos.x + 24, ExAtack[i].pos.y + 5/* + 34.5*/,
					//		ExAtack[i].pos.x + 45, ExAtack[i].pos.y + 21, 0xffffff, false);

					//DrawBox(ExAtack[i].pos.x + 24, ExAtack[i].pos.y + 21/* + 34.5*/,
					//		ExAtack[i].pos.x + 45, ExAtack[i].pos.y + 37, 0xffffff, false);

					//DrawBox(ExAtack[i].pos.x + 24, ExAtack[i].pos.y + 37/* + 34.5*/,
					//		ExAtack[i].pos.x + 45, ExAtack[i].pos.y + 53, 0xffffff, false);

					//DrawBox(ExAtack[i].pos.x + 24, ExAtack[i].pos.y + 53/* + 34.5*/,
					//		ExAtack[i].pos.x + 45, ExAtack[i].pos.y + 69, 0xffffff, false);



					//DrawBox(ExAtack[i].pos.x + 3, ExAtack[i].pos.y + 5/* + 34.5*/,
					//		ExAtack[i].pos.x + 24, ExAtack[i].pos.y + 21, 0xffffff, false);

					//DrawBox(ExAtack[i].pos.x + 3, ExAtack[i].pos.y + 21/* + 34.5*/,
					//		ExAtack[i].pos.x + 24, ExAtack[i].pos.y + 37, 0xffffff, false);

					//DrawBox(ExAtack[i].pos.x + 3, ExAtack[i].pos.y + 37/* + 34.5*/,
					//		ExAtack[i].pos.x + 24, ExAtack[i].pos.y + 53, 0xffffff, false);

					//DrawBox(ExAtack[i].pos.x + 3, ExAtack[i].pos.y + 53/* + 34.5*/,
					//		ExAtack[i].pos.x + 24, ExAtack[i].pos.y + 69, 0xffffff, false);


					//DrawBox(ExAtack[i].pos.x - 18, ExAtack[i].pos.y + 5/* + 34.5*/,
					//		ExAtack[i].pos.x + 3, ExAtack[i].pos.y + 21, 0xffffff, false);

					//DrawBox(ExAtack[i].pos.x - 18, ExAtack[i].pos.y + 21/* + 34.5*/,
					//		ExAtack[i].pos.x + 3, ExAtack[i].pos.y + 37, 0xffffff, false);

					//DrawBox(ExAtack[i].pos.x - 18, ExAtack[i].pos.y + 37/* + 34.5*/,
					//		ExAtack[i].pos.x + 3, ExAtack[i].pos.y + 53, 0xffffff, false);

					//DrawBox(ExAtack[i].pos.x - 18, ExAtack[i].pos.y + 53/* + 34.5*/,
					//		ExAtack[i].pos.x + 3, ExAtack[i].pos.y + 69, 0xffffff, false);


					//DrawBox(ExAtack[i].pos.x - 43, ExAtack[i].pos.y + 5/* + 34.5*/,
					//		ExAtack[i].pos.x - 18, ExAtack[i].pos.y + 21, 0xffffff, false);

					//DrawBox(ExAtack[i].pos.x - 43, ExAtack[i].pos.y + 21/* + 34.5*/,
					//		ExAtack[i].pos.x - 18, ExAtack[i].pos.y + 37, 0xffffff, false);

					//DrawBox(ExAtack[i].pos.x - 43, ExAtack[i].pos.y + 37/* + 34.5*/,
					//		ExAtack[i].pos.x - 18, ExAtack[i].pos.y + 53, 0xffffff, false);

					//DrawBox(ExAtack[i].pos.x - 43, ExAtack[i].pos.y + 53/* + 34.5*/,
					//		ExAtack[i].pos.x - 18, ExAtack[i].pos.y + 69, 0xffffff, false);

					//

					/*ハンマー振る版
					DrawBox(ExAtack[i].pos.x + 8,
						ExAtack[i].pos.y - 69,
						ExAtack[i].pos.x + 48 * 2,
						ExAtack[i].pos.y, 0xffffff, true);
					DrawBox(ExAtack.pos.x + 28,
						ExAtack.pos.y - 69,
						ExAtack.pos.x + 48 * 2,
						ExAtack.pos.y + 69, 0x00ffff, true);*/
				}
				if (ExAtack[i].moveDir == DIR_LEFT)
				{
					//DrawBox(ExAtack[i].pos.x - 44, ExAtack[i].pos.y + 5/* + 34.5*/,
					//	ExAtack[i].pos.x + 44, ExAtack[i].pos.y + 69, 0xffffff, false);

					//DrawBox(ExAtack[i].pos.x + 24, ExAtack[i].pos.y + 5/* + 34.5*/,
					//	ExAtack[i].pos.x + 45, ExAtack[i].pos.y + 21, 0xffffff, false);
					//DrawBox(ExAtack[i].pos.x + 24, ExAtack[i].pos.y + 21/* + 34.5*/,
					//	ExAtack[i].pos.x + 45, ExAtack[i].pos.y + 37, 0xffffff, false);
					//DrawBox(ExAtack[i].pos.x + 24, ExAtack[i].pos.y + 37/* + 34.5*/,
					//	ExAtack[i].pos.x + 45, ExAtack[i].pos.y + 53, 0xffffff, false);
					//DrawBox(ExAtack[i].pos.x + 24, ExAtack[i].pos.y + 53/* + 34.5*/,
					//	ExAtack[i].pos.x + 45, ExAtack[i].pos.y + 69, 0xffffff, false);

					//
					//DrawBox(ExAtack[i].pos.x + 3, ExAtack[i].pos.y + 5/* + 34.5*/,
					//	ExAtack[i].pos.x + 24, ExAtack[i].pos.y + 21, 0xffffff, false);
					//DrawBox(ExAtack[i].pos.x + 3, ExAtack[i].pos.y + 21/* + 34.5*/,
					//	ExAtack[i].pos.x + 24, ExAtack[i].pos.y + 37, 0xffffff, false);
					//DrawBox(ExAtack[i].pos.x + 3, ExAtack[i].pos.y + 37/* + 34.5*/,
					//	ExAtack[i].pos.x + 24, ExAtack[i].pos.y + 53, 0xffffff, false);
					//DrawBox(ExAtack[i].pos.x + 3, ExAtack[i].pos.y + 53/* + 34.5*/,
					//	ExAtack[i].pos.x + 24, ExAtack[i].pos.y + 69, 0xffffff, false);

					//DrawBox(ExAtack[i].pos.x - 18, ExAtack[i].pos.y + 5/* + 34.5*/,
					//	ExAtack[i].pos.x + 3, ExAtack[i].pos.y + 21, 0xffffff, false);
					//DrawBox(ExAtack[i].pos.x - 18, ExAtack[i].pos.y + 21/* + 34.5*/,
					//	ExAtack[i].pos.x + 3, ExAtack[i].pos.y + 37, 0xffffff, false);
					//DrawBox(ExAtack[i].pos.x - 18, ExAtack[i].pos.y + 37/* + 34.5*/,
					//	ExAtack[i].pos.x + 3, ExAtack[i].pos.y + 53, 0xffffff, false);
					//DrawBox(ExAtack[i].pos.x - 18, ExAtack[i].pos.y + 53/* + 34.5*/,
					//	ExAtack[i].pos.x + 3, ExAtack[i].pos.y + 69, 0xffffff, false);

					//DrawBox(ExAtack[i].pos.x - 43, ExAtack[i].pos.y + 5/* + 34.5*/,
					//	ExAtack[i].pos.x - 18, ExAtack[i].pos.y + 21, 0xffffff, false);
					//DrawBox(ExAtack[i].pos.x - 43, ExAtack[i].pos.y + 21/* + 34.5*/,
					//	ExAtack[i].pos.x - 18, ExAtack[i].pos.y + 37, 0xffffff, false);
					//DrawBox(ExAtack[i].pos.x - 43, ExAtack[i].pos.y + 37/* + 34.5*/,
					//	ExAtack[i].pos.x - 18, ExAtack[i].pos.y + 53, 0xffffff, false);
					//DrawBox(ExAtack[i].pos.x - 43, ExAtack[i].pos.y + 53/* + 34.5*/,
					//	ExAtack[i].pos.x - 18, ExAtack[i].pos.y + 69, 0xffffff, false);

					/*ハンマー振る版
					DrawBox(ExAtack[i].pos.x - 8,
						ExAtack[i].pos.y,
						ExAtack[i].pos.x - 48 * 2,
						ExAtack[i].pos.y - 69, 0xffffff, true);

					DrawBox(ExAtack[i].pos.x - 28,
						ExAtack[i].pos.y + 69,
						ExAtack[i].pos.x - 48 * 2,
						ExAtack[i].pos.y - 69, 0x00ffff, true);*/
				}
			}
			//DrawCircle(ExAtack[i].pos.x, ExAtack[i].pos.y+65, 5, 0xffffff, true);
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