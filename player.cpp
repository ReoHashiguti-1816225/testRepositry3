#include "DxLib.h"
#include "main.h"
#include "player.h"
#include "keycheck.h"
#include "stage.h"
#include "shot.h"
#include "Atack.h"
#include "�A�C�e��.h"

CHARACTER player[PLAYER_MAX];
int playerimage[PLAYER_MAX][PLAYER_IMAGE_MAX];
int p1Lifeimage;
int p1Winimage;

int p1Nameimage;
int p2Nameimage;
int p3Nameimage;
int p4Nameimage;
int WIN;
int HitSound;
int ExHitSound;
int Aupimage;
int GetSound;
int ExpSound;
int jumpCnt[PLAYER_MAX];
int jumpFrame[PLAYER_MAX];
int exCnt = 0;
int AupCnt = 300;
int WaitCnt;
XY movedpos;



void playerInit(void)
{
	WaitCnt = 0;
	for (int i = 0; i < PLAYER_MAX; i++)
	{
		player[i].pos = { 48,SCREEN_SIZE_Y-96 };
		player[i].defaltpos = player[i].pos;
		
		player[i].velocity = { 0,0 };
		player[i].moveDir = DIR_RIGHT;
		player[i].hitPosS = { 0,  0 };									// �{�̍���
		player[i].hitPosE = { 48,  40 };									// �̉E��
		if(i % 2 == 1)
		{
			player[i].pos = { SCREEN_SIZE_X - 96,SCREEN_SIZE_Y - 144 };
			player[i].defaltpos = player[i].pos;
			player[i].moveDir = DIR_LEFT;
			player[i].hitPosS = { 0,  0 };									// �l�Ԃ̍���
			player[i].hitPosE = { 48,  96 };								// �l�Ԃ̉E��

		}
		player[0].Life = 300;
		player[0].LifeLimit = 300;
		player[1].Life = 400;
		player[1].LifeLimit = 400;

		player[2].Life = 200;
		player[2].LifeLimit = 200;
		player[3].Life = 300;
		player[3].LifeLimit = 300;
		//player[i].Damage = 10;

		player[i].WinCnt = 0;

		player[i].keyConfig[PLAYER_KEY_CONFIG_UP] = KEY_INPUT_W;
		player[i].keyConfig[PLAYER_KEY_CONFIG_DOWN] = KEY_INPUT_S;
		player[i].keyConfig[PLAYER_KEY_CONFIG_LEFT] = KEY_INPUT_A;
		player[i].keyConfig[PLAYER_KEY_CONFIG_RIGHT] = KEY_INPUT_D;
		player[i].keyConfig[PLAYER_KEY_CONFIG_FIRE] = KEY_INPUT_SPACE;
		player[i].keyConfig[PLAYER_KEY_CONFIG_ATACK] = KEY_INPUT_B;
		player[i].keyConfig[PLAYER_KEY_CONFIG_EXATACK] = KEY_INPUT_G;

		if (i % 2 == 1)
		{
			player[i].keyConfig[PLAYER_KEY_CONFIG_UP] = KEY_INPUT_UP;
			player[i].keyConfig[PLAYER_KEY_CONFIG_DOWN] = KEY_INPUT_DOWN;
			player[i].keyConfig[PLAYER_KEY_CONFIG_LEFT] = KEY_INPUT_LEFT;
			player[i].keyConfig[PLAYER_KEY_CONFIG_RIGHT] = KEY_INPUT_RIGHT;
			player[i].keyConfig[PLAYER_KEY_CONFIG_FIRE] = KEY_INPUT_NUMPAD0;
			player[i].keyConfig[PLAYER_KEY_CONFIG_ATACK] = KEY_INPUT_RSHIFT;
			player[i].keyConfig[PLAYER_KEY_CONFIG_EXATACK] = KEY_INPUT_NUMPAD5;
		}

		


		player[i].Ex = 0;
		player[i].ExLimit = 100;
		
		p1Winimage = LoadGraph("image/��.png", true);
		jumpFrame[i] = 15;
		jumpCnt[i] = 0;
	}
	LoadDivGraph("image/tori.png", 4, 4, 1, 48, 48, playerimage[0]);
	LoadDivGraph("image/�В�.png", 4, 4, 1, 48, 96, playerimage[1]);
	LoadDivGraph("image/�ψَ�.png", 4, 4, 1, 48, 48, playerimage[2]);
	LoadDivGraph("image/��ƈ� �p.png", 4, 4, 1, 48, 96, playerimage[3]);

	p1Nameimage = LoadGraph("image/�j���g��.png", true);
	p2Nameimage = LoadGraph("image/���Ⴟ��[.png", true);
	p3Nameimage = LoadGraph("image/�j���g����.png", true);
	p4Nameimage = LoadGraph("image/��ƈ�.png", true);
	Aupimage = LoadGraph("image/���.png", true);
	WIN = LoadGraph("image/Win.png", true);

	HitSound = LoadSoundMem("Sound/�q�b�g��.mp3", true);
	GetSound = LoadSoundMem("Sound/�Q�b�g.mp3",true);
	ExpSound = LoadSoundMem("Sound/���e.mp3", true);
	ExHitSound = LoadSoundMem("Sound/�K�E�Z���ʉ�.mp3");

}


void playerUpdate(void)
{
	int hposy = 0;
	for (int i = 0; i < PLAYER_MAX; i++)
	{
		XY tmpPos;

		XY movedPos = player[i].pos;


		// offset�͍�����ڲ԰��1Ͻ���Ƃ̍��W
		XY movedOffset = movedPos;
		XY movedOffset2 = movedPos;
		XY movedOffset3 = movedPos;
		XY tmpindex;

		for (int j = 0; j < PLAYER_KEY_CONFIG_MAX; j++)
		{
			player[i].keyLastPressed[j] = player[i].keyPressed[j];

			player[i].keyPressed[j] = CheckHitKey(player[i].keyConfig[j]);
			player[i].keyDown[j] = (!player[i].keyLastPressed[j]) && player[i].keyPressed[j];
		}

		//player.pos.y += 2;
		player[i].runFlag = false;
		if (player[i].WinCnt < 0)
		{
			player[i].WinCnt = 0;
		}
		if (player[i].WinCnt > 2)
		{
			player[i].WinCnt = 2;
		}



		if (player[i].Life > player[i].LifeLimit)
		{
			player[i].Life = player[i].LifeLimit;
		}
		if (player[i].Ex > player[i].ExLimit)
		{
			player[i].Ex = player[i].ExLimit;
		}
		
		// ��ڲ԰�̈ړ�	(�L�[����)
		if (player[i].flag)
		{
			if (PlayerKeyCheck(i))
			{
				if (player[i].moveDir == DIR_RIGHT) 					// �E
				{
					player[i].velocity.x += ACC_RUN;					// ���x�̍X�V
					player[i].runFlag = true;
					if (player[i].velocity.x > VELOCITY_X_MAX) {
						player[i].velocity.x = VELOCITY_X_MAX;
					}
					
				}

				if (player[i].moveDir == DIR_LEFT) {								// ��			
					player[i].velocity.x -= ACC_RUN;				// ���x�̍X�V
					player[i].runFlag = true;
					if (player[i].velocity.x < -VELOCITY_X_MAX) {
						player[i].velocity.x = -VELOCITY_X_MAX;
					}
				}
				player[i].animCnt++;
			}
			// �~�܂������̌�������
			if (!player[i].runFlag) {
				if (player[i].velocity.x > 0) {
					player[i].velocity.x -= ACC_STOP;
					if (player[i].velocity.x < 0) {
						player[i].velocity.x = 0;
					}
				}
				if (player[i].velocity.x < 0) {
					player[i].velocity.x += ACC_STOP;
					if (player[i].velocity.x > 0) {
						player[i].velocity.x = 0;
					}
				}
			}

			// ��ڲ԰�̈ړ�(���E)
			movedPos.x += player[i].velocity.x * 1;	// �����̍X�V

			if (player[i].velocity.x > 0) {							// �E
				movedOffset.x = movedPos.x + player[i].hitPosE.x;
			}
			if (player[i].velocity.x < 0) {							// ��
				movedOffset.x = movedPos.x - player[i].hitPosS.x;
			}
			//��ڲ԰�̓���̒��S�̵̾��
			movedOffset2 = movedOffset;
			movedOffset2.y = movedPos.y - player[i].hitPosS.y;
			//��ڲ԰�̑����̒��S�̵̾��
			movedOffset3 = movedOffset;
			movedOffset3.y = movedPos.y + player[i].hitPosE.y - 1;			// �]1�͒���


			if (IsPass(movedOffset) && IsPass(movedOffset2) && IsPass(movedOffset3)) {		// movedOffset����ڲ԰�̒��SmovedOffset2����ڲ԰�̓���̒��SmovedOffset3����ڲ԰�̑����̒��S
				player[i].pos = movedPos;													// 
			}
			else {
				tmpPos = mapPosToMoveIndex(movedOffset, player[i].headFlag, player[i].velocity);
				if (player[i].velocity.x > 0) {			// �E
					player[i].pos.x = tmpPos.x - player[i].hitPosE.x;
				}
				if (player[i].velocity.x < 0) {			// ��
					player[i].pos.x = tmpPos.x + player[i].hitPosS.x;
				}
				movedPos = player[i].pos;
				player[i].velocity.x = 0;
			}

			// �d��
			movedPos = player[i].pos;

			movedPos.y -= player[i].velocity.y * SECOND_PER_FRAME;
			player[i].velocity.y -= ACC_G * SECOND_PER_FRAME;

			// ��ۯ�������
			// �������ۯ�������

			movedOffset = movedPos;
			movedOffset.y = movedPos.y - player[i].hitPosS.y;
			movedOffset2 = movedOffset;							// ����
			movedOffset2.x = movedPos.x - player[i].hitPosS.x;
			movedOffset3 = movedOffset;							// �E��
			movedOffset3.x = movedPos.x + player[i].hitPosE.x - 1;
			//	SetOffset(OFFSET_HEAD);

			if (IsPass(movedOffset) && IsPass(movedOffset2) && IsPass(movedOffset3))
			{
				player[i].pos = movedPos;
			}
			else {
			/*	player[i].headFlag = true;*/
				//tmpPos = mapPosToMoveIndex(movedOffset, player[i].headFlag, player[i].velocity);
				tmpindex = mapPosToIndex(movedOffset);
				tmpindex.y++;
				tmpPos = mapIndexToPos(tmpindex);
				
				player[i].pos.y = tmpPos.y + player[i].hitPosS.y;
				player[i].velocity.y *= -1;
			}
			movedPos = player[i].pos;


			// ��������ۯ�������

			movedOffset = movedPos;
			movedOffset.y = movedPos.y + player[i].hitPosE.y;
			movedOffset.y = movedPos.y + player[i].hitPosE.y;
			movedOffset2 = movedOffset;							// ����
			movedOffset2.x = movedPos.x - player[i].hitPosS.x;
			movedOffset3 = movedOffset;							// �E��
			movedOffset3.x = movedPos.x + player[i].hitPosE.x - 1;

			//	SetOffset(OFFSET_FOOT);

			if (IsPass(movedOffset) && IsPass(movedOffset2) && IsPass(movedOffset3)) {
				player[i].pos = movedPos;
			}
			else {
				tmpPos = mapPosToMoveIndex(movedOffset, player[i].headFlag, player[i].velocity);
				player[i].pos.y = tmpPos.y - player[i].hitPosE.y;
				player[i].velocity.y = 0;
				player[i].jumpFlag = false;
			}
			movedPos = player[i].pos;

			//�@�ެ���
			// 1Ͻ�̂Ƃ���ł̓W�����v���Ȃ�
			movedOffset = movedPos;
			movedOffset.y = movedPos.y - player[i].hitPosS.y;
			movedOffset2 = movedOffset;							// ����
			movedOffset2.x = movedPos.x - player[i].hitPosS.x;
			movedOffset3 = movedOffset;							// �E��
			movedOffset3.x = movedPos.x + player[i].hitPosE.x - 1;


			//SetOffset(OFFSET_NOTJUMP);
			if (IsPass(movedOffset) && IsPass(movedOffset2) && IsPass(movedOffset3))
			{

				if (!player[i].jumpFlag)
				{
					if (PlayerJumpKeyCheck(i))
					{
						jumpCnt[i]++;
						if (jumpCnt[i] < jumpFrame[i])
						{
							player[i].velocity.y = 25;
						}
						if (player[i].headFlag)
						{
							jumpCnt[i] = jumpFrame[i];
						}
					}
					else
					{
						jumpCnt[i] = 0;
						player[i].jumpFlag = true;
					}
				}
			}
			else
			{
				jumpCnt[i] = 15;
			}
			movedPos = player[i].pos;


			// �ެ�����ۯ�
			// 1Ͻ�̂Ƃ���ł̓W�����v���Ȃ�
			movedOffset = movedPos;
			movedOffset.y = movedPos.y - player[i].hitPosS.y;
			movedOffset2 = movedOffset;							// ����
			movedOffset2.x = movedPos.x - player[i].hitPosS.x;
			movedOffset3 = movedOffset;							// �E��
			movedOffset3.x = movedPos.x + player[i].hitPosE.x - 1;
			//SetOffset(OFFSET_NOTJUMP);
			if (IsPass(movedOffset) && IsPass(movedOffset2) && IsPass(movedOffset3)) 
			{
				movedOffset.y = movedPos.y + player[i].hitPosE.y;		// ����
			}
			movedPos = player[i].pos;

			
		}

		if (PlayerShotKeyCheck(i))
		{
			
			if (player[i].flag == true)
			{
				XY Shotpos = player[i].pos;
				if (player[i].jumpFlag == true)
				{
					Shotpos.y -= 5;
				}
				if (player[i].moveDir == DIR_RIGHT)
				{
					
					if  (i % 2 == 1)
					{
						hposy = 40;
					}
				
					BulletFire({ Shotpos.x + player[i].offsetSize.x + 50,
						Shotpos.y + hposy +25},
						player[i].moveDir, i);

				}
				if (player[i].moveDir == DIR_LEFT)
				{
					if (i % 2 == 1)
					{
						hposy = 40;
					}
					BulletFire({ Shotpos.x - player[i].offsetSize.x - 20, 
						Shotpos.y + hposy + 25 },
						player[i].moveDir, i);

				}
			}

		}

		if (PlayerAtackKeyCheck(i))
		{
			if (player[i].flag == true)
			{
				
					if (i % 2 == 1)
					{
						hposy = 40;
					}
					AtackStartup({
						player[i].pos.x,
						player[i].pos.y + hposy },
						player[i].moveDir, i);
				
			}
		}
		

		//	SetOffset(OFFSET_FOOT);

		
		movedOffset = movedPos;
		movedOffset.y = movedPos.y + player[i].hitPosE.y;
		movedOffset.y = movedPos.y + player[i].hitPosE.y;
		movedOffset2 = movedOffset;							// ����
		movedOffset2.x = movedPos.x - player[i].hitPosS.x;
		movedOffset3 = movedOffset;							// �E��
		movedOffset3.x = movedPos.x + player[i].hitPosE.x - 1;

		if (PlayerExAtackKeyCheck(i))
		{
			if (!IsPass(movedOffset) && !IsPass(movedOffset2) && !IsPass(movedOffset3)) 
			{
				if ((player[i].flag == true) && (player[i].Ex == 100))
				{
					ExAtackStartup({
						player[i].pos.x,
						player[i].pos.y },
						player[i].moveDir, i);
					player[i].Ex = 0;

				}
			}
		}
		
		for (int j = 0; j < SHOT_MAX; j++)
		{
			if (PlayerShotHitCheck(shot[j].pos, shot[j].flag, shot[j].moveDir,i))//shot�����蔻��
			{
				shot[j].flag = false;
				//break;
			}
		}

		
		if (PlayerAtackHitCheck(Atack.pos, Atack.size, Atack.type, Atack.flag,Atack.moveDir))
		{
			Atack.flag = false;

			DrawFormatString(0, 200, 0xffffff, "Hit");
		}
		for (int i = 0; i < EXATACK_MAX; i++)
		{
			if (PlayerExHitCheck(ExAtack[i].pos, ExAtack[i].moveDir, ExAtack[i].type, ExAtack[i].flag))
			{
				if (!ExAtack[i].type == 0)
				{
					ExAtack[i].flag = false;

				}
			}
		}
		if (ITEM.flag)
		{
			if (PlayerItemCheck(ITEM.pos, ITEM.Usetype))
			{
				ITEM.flag = false;

			}
		}
		if (player[i].Life <= 0)
		{
			if ((player[0].flag) && (player[1].flag))
			{
				//  �j���g���̗̑́@<=0�ȉ��@���@�В��̗̑� > 0�ȏ�
				if ((player[0].Life <= 0) && (player[1].Life > 0))
				{
					player[1].WinCnt = player[1].WinCnt + 1;

				}

			}
			if ((player[2].flag) && (player[1].flag))
			{
				//  �ψَ�̗̑́@<=0�ȉ��@���@�В��̗̑� > 0�ȏ�

				if ((player[2].Life <= 0) && (player[1].Life > 0))
				{
					player[1].WinCnt = player[1].WinCnt + 1;

				}
			}
			if ((player[0].flag) && (player[1].flag))
			{
				//  �В��̗̑́@<=0�ȉ��@���@�j���g���̗̑� > 0�ȏ�

				if ((player[1].Life <= 0) && (player[0].Life > 0))
				{
					player[0].WinCnt = player[0].WinCnt + 1;

				}
			}
			if ((player[3].flag) && (player[0].flag))
			{
				//  ��ƈ��̗̑́@<=0�ȉ��@���@�j���g���̗̑� > 0�ȏ�

				if ((player[3].Life <= 0) && (player[0].Life > 0))
				{
					player[0].WinCnt = player[0].WinCnt + 1;

				}
			}
			if ((player[0].flag) && (player[3].flag))
			{
				//  �j���g���̗̑́@<=0�ȉ��@���@��ƈ��̗̑� > 0�ȏ�

				if ((player[0].Life <= 0) && (player[3].Life > 0))
				{
					player[3].WinCnt = player[3].WinCnt + 1;

				}
			}
			if ((player[2].flag) && (player[3].flag))
			{
				//  �ψَ�̗̑́@<=0�ȉ��@���@��ƈ��̗̑� > 0�ȏ�

				if ((player[2].Life <= 0) && (player[3].Life > 0))
				{
					player[3].WinCnt = player[3].WinCnt + 1;

				}
			}
			if ((player[2].flag) && (player[1].flag))
			{
				//  �В��̗̑́@<=0�ȉ��@���@�ψَ�̗̑� > 0�ȏ�
				if ((player[1].Life <= 0) && (player[2].Life > 0))
				{
					player[2].WinCnt = player[2].WinCnt + 1;

				}
			}
			if ((player[3].flag) && (player[2].flag))
			{
				//  ��ƈ��̗̑́@<=0�ȉ��@���@�ψَ�̗̑� > 0�ȏ�

				if ((player[3].Life <= 0) && (player[2].Life > 0))
				{
					player[2].WinCnt = player[2].WinCnt + 1;

				}
			}
			
			WaitTimer(1000);
			PlayerReset();

		}
		if (player[i].WinCnt == 2)
		{
			for (int j = 0; j < PLAYER_MAX; j++)
			{
				player[j].flag = false;
			}
			
			WaitCnt++;
			//WaitTimer(1000);
			if(WaitCnt > 100)
			GMODE = MODE_INIT;
			////PlayerReset();

		}


		if (player[i].AupFlag)
		{
			AupCnt--;
			if (AupCnt < 0)
			{
				player[i].AupFlag = false;

				AupCnt = 300;
			}
		}
	
	}
}


void playerDraw(void)
{
	int tmpx = 0;

	for (int i = 0; i < PLAYER_MAX; i++)
	{
		if (player[i].flag == true)
		{
			if (i % 2 == 0)
			{
				if (player[i].moveDir == DIR_RIGHT)
					DrawGraph(player[i].pos.x, player[i].pos.y, playerimage[i][player[i].animCnt / 10 % 4], true);

				if (player[i].moveDir == DIR_LEFT)
					DrawTurnGraph(player[i].pos.x, player[i].pos.y, playerimage[i][player[i].animCnt / 10 % 4], true);
			}
			if (i % 2 == 1)
			{
				if (player[i].moveDir == DIR_RIGHT)
					DrawTurnGraph(player[i].pos.x, player[i].pos.y, playerimage[i][player[i].animCnt / 10 % 4], true);

				if (player[i].moveDir == DIR_LEFT)
				
				DrawGraph(player[i].pos.x, player[i].pos.y, playerimage[i][player[i].animCnt / 10 % 4], true);
			}
			
		}
	}

	//�X�e�[�^�X�`��(�j���g��)
	if (player[0].flag)
	{
		//�̗͘g
		for (int i = 0; i < player[0].LifeLimit; i++)
		{
			DrawBox(0 + i, 0,
				9 + i, 15, 0xffffff, true);
		}
		//�̗͌�����
		for (int i = 0; i < player[0].LifeLimit; i++)
		{
			DrawBox(2 + i, 2,
				7 + i, 13, 0xff0000, true);
		}
		//�̗�
		for (int i = 0; i < player[0].Life; i++)
		{
			DrawBox(2 + i, 2,
				7 + i, 13, 0x5FFE01, true);
		}
		//�C�̓Q�[�W
		for (int i = 0; i < player[0].ExLimit; i++)
		{
			DrawBox(0 + i, 15,
				10 + i, 24, 0xffffff, false);
		}
		//�C��
		for (int i = 0; i < player[0].Ex; i++)
		{
			DrawBox(0 + i, 17,
				8 + i, 22, 0x0000ff, true);
		}
	}

	//�X�e�[�^�X�`��(�В�)
	if (player[1].flag)
	{
		//�̗͘g
		for (int i = 0; i < player[1].LifeLimit; i++)
		{
			DrawBox(SCREEN_SIZE_X, 0,
				958 - i, 15, 0xffffff, true);
		}
		//�̗͌�����
		for (int i = 0; i < player[1].LifeLimit; i++)
		{
			DrawBox(SCREEN_SIZE_X - 2, 2,
				SCREEN_SIZE_X - i, 13, 0xff0000, true);
		}
		//�̗̓Q�[�W
		for (int i = 0; i < player[1].Life; i++)
		{
			DrawBox(SCREEN_SIZE_X - 2, 2,
				SCREEN_SIZE_X - i, 13, 0x5FFE01, true);

		}
		//�C��
		for (int i = 0; i < player[1].ExLimit; i++)
		{
			DrawBox(SCREEN_SIZE_X, 15,
				958 - i, 24, 0xffffff, true);
		}


		for (int i = 0; i < player[1].Ex; i++)
		{
			DrawBox(SCREEN_SIZE_X, 17,
				960 - i, 22, 0x0000ff, true);
		}

	}

	//�X�e�[�^�X�`��(�ψَ�)
	if (player[2].flag)
	{
		//�̗͘g
		for (int i = 0; i < player[2].LifeLimit; i++)
		{
			DrawBox(0 + i, 0,
				9 + i, 15, 0xffffff, true);
		}
		//�̗͌�����
		for (int i = 0; i < player[2].LifeLimit; i++)
		{
			DrawBox(2 + i, 2,
				7 + i, 13, 0xff0000, true);
		}
		//�̗�
		for (int i = 0; i < player[2].Life; i++)
		{
			DrawBox(2 + i, 2,
				7 + i, 13, 0x5FFE01, true);
		}
		//�C�̓Q�[�W
		for (int i = 0; i < player[2].ExLimit; i++)
		{
			DrawBox(0 + i, 15,
				10 + i, 24, 0xffffff, false);
		}
		//�C��
		for (int i = 0; i < player[2].Ex; i++)
		{
			DrawBox(0 + i, 17,
				8 + i, 22, 0x0000ff, true);
		}

	}
	//�X�e�[�^�X�`��(��ƈ�)
	if (player[3].flag)
	{
		//�̗͘g
		for (int i = 0; i < player[3].LifeLimit; i++)
		{
			DrawBox(SCREEN_SIZE_X, 0,
				958 - i, 15, 0xffffff, true);
		}
		//�̗͌�����
		for (int i = 0; i < player[3].LifeLimit; i++)
		{
			DrawBox(SCREEN_SIZE_X - 2, 2,
				SCREEN_SIZE_X - i, 13, 0xff0000, true);
		}
		//�̗̓Q�[�W
		for (int i = 0; i < player[3].Life; i++)
		{
			DrawBox(SCREEN_SIZE_X - 2, 2,
				SCREEN_SIZE_X - i, 13, 0x5FFE01, true);

		}
		//�C��
		for (int i = 0; i < player[3].ExLimit; i++)
		{
			DrawBox(SCREEN_SIZE_X, 15,
				958 - i, 24, 0xffffff, true);
		}


		for (int i = 0; i < player[3].Ex; i++)
		{
			DrawBox(SCREEN_SIZE_X, 17,
				960 - i, 22, 0x0000ff, true);
		}

	}



		//DrawBox(100, 100, 148, 112, 0xffffff, true);
		for (int i = 0; i < player[0].WinCnt;i++)
		{
			DrawGraph(300 - (i * 48), 20, p1Winimage, true);
		}
		for (int i = 0; i < player[1].WinCnt; i++)
		{
			DrawGraph(500 + (i * 48), 20, p1Winimage, true);
		}
		for (int i = 0; i < player[2].WinCnt; i++)
		{
			DrawGraph(300 - (i * 48), 20, p1Winimage, true);
		}

		for (int i = 0; i < player[3].WinCnt; i++)
		{
			DrawGraph(500 + (i * 48), 20, p1Winimage, true);
		}
		
		if (player[0].AupFlag)
		{
			DrawGraph(300 , 68, Aupimage, true);
		}
		if (player[1].AupFlag)
		{

			DrawGraph(700, 68, Aupimage, true);
		}
		if (player[2].AupFlag)
		{

			DrawGraph(300 , 68, Aupimage, true);
		}
		if (player[3].AupFlag)
		{

			DrawGraph(700, 68, Aupimage, true);
		}
		
		if (player[0].WinCnt >= 2)
		{
			DrawGraph(400, 100, p1Nameimage, true);
			DrawGraph(0, 0, WIN, true);
		}
		 if (player[1].WinCnt >= 2)
		{
			DrawGraph(400, 100, p2Nameimage, true);
			DrawGraph(0, 0, WIN, true);
		}
		 if (player[2].WinCnt >= 2)
		 {
			 DrawGraph(400, 100, p3Nameimage, true);
			 DrawGraph(0, 0, WIN, true);
		 }
		 if (player[3].WinCnt >= 2)
		 {
			 DrawGraph(400, 100, p4Nameimage, true);
			 DrawGraph(0, 0, WIN, true);
		 }
	
		
		 if (player[0].flag)
		 {
			 DrawGraph(0, 17, p1Nameimage, true);

		 }
		 if (player[1].flag)
		 {
			 DrawGraph(SCREEN_SIZE_X - 212, 17, p2Nameimage, true);
		 }
		 if (player[2].flag)
		 {
			 DrawGraph(0, 17, p3Nameimage, true);

		 }
		 if (player[3].flag)
		 {
			 DrawGraph(SCREEN_SIZE_X - 164, 17, p4Nameimage, true);
		 }
}



bool PlayerKeyCheck(int i) {

	switch (i)
	{
	case 0:
		if (player[i].keyPressed[PLAYER_KEY_CONFIG_RIGHT] ) {
			player[i].moveDir = DIR_RIGHT;
			return true;
		}
		
		if (player[i].keyPressed[PLAYER_KEY_CONFIG_LEFT]) {
			player[i].moveDir = DIR_LEFT;
			return true;
		}
		break;
	case 1:
		if (player[i].keyPressed[PLAYER_KEY_CONFIG_RIGHT]) {
			player[i].moveDir = DIR_RIGHT;
			return true;
		}
	
		if (player[i].keyPressed[PLAYER_KEY_CONFIG_LEFT]) {
			player[i].moveDir = DIR_LEFT;
			return true;
		}
		break;
	case 2:
		if (player[i].keyPressed[PLAYER_KEY_CONFIG_RIGHT]) {
			player[i].moveDir = DIR_RIGHT;
			return true;
		}
		if (player[i].keyPressed[PLAYER_KEY_CONFIG_LEFT]) {
			player[i].moveDir = DIR_LEFT;
			return true;
		}
		break;
	case 3:
		if (player[i].keyPressed[PLAYER_KEY_CONFIG_RIGHT]) {
			player[i].moveDir = DIR_RIGHT;
			return true;
		}
			
		if (player[i].keyPressed[PLAYER_KEY_CONFIG_LEFT]) {
			player[i].moveDir = DIR_LEFT;
			return true;
		}
			break;
	default:
		break;
	}

	return false;
}

bool PlayerJumpKeyCheck(int i) {


	switch (i) {
	case 0:
		if (player[i].keyPressed[PLAYER_KEY_CONFIG_UP]) {
			return true;
		}
		break;
	case 1:
		if (player[i].keyPressed[PLAYER_KEY_CONFIG_UP]) {

			return true;
		}
		break;
	case 2:
		if (player[i].keyPressed[PLAYER_KEY_CONFIG_UP]) {
			return true;
		}
		break;
	case 3:
		if (player[i].keyPressed[PLAYER_KEY_CONFIG_UP]) {
			return true;
		}
		break;
	}
	return false;
}
bool PlayerShotKeyCheck(int i)
{

	switch (i) {
	case 0:
		if (player[i].keyDown[PLAYER_KEY_CONFIG_FIRE]) {
			return true;
		}
		break;
	case 1:
		if (player[i].keyDown[PLAYER_KEY_CONFIG_FIRE]) {
			return true;
		}
		break;
	case 2:
		if (player[i].keyDown[PLAYER_KEY_CONFIG_FIRE]) {
			return true;
		}
		break;
	case 3:
		if (player[i].keyDown[PLAYER_KEY_CONFIG_FIRE]) {
			return true;
		}
		break;
	}
	return false;
}
bool PlayerAtackKeyCheck(int i)
{
	switch (i) {
	case 0:
		if (player[i].keyDown[PLAYER_KEY_CONFIG_ATACK]) {
			return true;
		}
		break;
	case 1:
		if (player[i].keyDown[PLAYER_KEY_CONFIG_ATACK]) {
			return true;
		}
		break;
	case 2:
		if (player[i].keyDown[PLAYER_KEY_CONFIG_ATACK]) {
			return true;
		}
		break;
	case 3:
		if (player[i].keyDown[PLAYER_KEY_CONFIG_ATACK]) {
			return true;
		}
		break;
	}
	return false;
}
bool PlayerExAtackKeyCheck(int i)
{
	i = i % 2;
	switch (i) {
	case 0:
		if (player[i].keyDown[PLAYER_KEY_CONFIG_EXATACK]) {
			return true;
		}
		break;
	case 1:
		if (player[i].keyDown[PLAYER_KEY_CONFIG_EXATACK]) {
			return true;
		}
		break;

	}
	return false;
}
bool PlayerShotHitCheck(XY pos,bool flag, /*XY size,*/ MOVE_DIR Sdir,int j)
{
	if ((player[0].flag) && (flag)) //�{
	{
		if (((player[0].pos.x - player[0].hitPosS.x) <= pos.x
			&& (player[0].pos.x + player[0].hitPosE.x) >= pos.x
			&& (player[0].pos.y + player[0].hitPosE.y) >= pos.y
			&& (player[0].pos.y - player[0].hitPosS.y) <= pos.y))
		{
			if ((player[1].AupFlag) || (player[3].AupFlag))
			{
				player[0].Life = player[0].Life - 20;
				player[0].Ex = player[0].Ex + 20;
				if (player[1].flag)
				{
					player[1].Ex = player[1].Ex + 10;
				}
				if (player[3].flag)
				{
					player[3].Ex = player[3].Ex + 10;
				}

			}
			if ((!player[1].AupFlag) && (!player[3].AupFlag))
			{
				player[0].Life = player[0].Life - 10;
				player[0].Ex = player[0].Ex + 10;
				if (player[1].flag)
				{
					player[1].Ex = player[1].Ex + 10;
				}
				if (player[3].flag)
				{
					player[3].Ex = player[3].Ex + 10;
				}
			}
			PlaySoundMem(HitSound, DX_PLAYTYPE_BACK);

			return true;
		}
	}
	if ((player[1].flag) && (flag)) //�В�
	{
		if (((player[1].pos.x - player[1].hitPosS.x) <= pos.x
			&& (player[1].pos.x + player[1].hitPosE.x) >= pos.x
			&& (player[1].pos.y + player[1].hitPosE.y) >= pos.y
			&& (player[1].pos.y - player[1].hitPosS.y) <= pos.y))
		{
			if ((player[0].AupFlag) || (player[2].AupFlag))
			{
				player[1].Life = player[1].Life - 20;
				player[1].Ex = player[1].Ex + 20;
				if (player[0].flag)
				{
					player[0].Ex = player[0].Ex + 10;
				}
				if (player[2].flag)
				{
					player[2].Ex = player[2].Ex + 10;
				}

			}
			if ((!player[0].AupFlag) && (!player[2].AupFlag))
			{
				player[1].Life = player[1].Life - 10;
				player[1].Ex = player[1].Ex + 10;
				if (player[0].flag)
				{
					player[0].Ex = player[0].Ex + 10;
				}
				if (player[2].flag)
				{
					player[2].Ex = player[2].Ex + 10;
				}
			}
			PlaySoundMem(HitSound, DX_PLAYTYPE_BACK);

			return true;
		}
	}
	if ((player[2].flag) && (flag)) //�ψَ�
	{
		if (((player[2].pos.x - player[2].hitPosS.x) <= pos.x
			&& (player[2].pos.x + player[2].hitPosE.x) >= pos.x
			&& (player[2].pos.y + player[2].hitPosE.y) >= pos.y
			&& (player[2].pos.y - player[2].hitPosS.y) <= pos.y))
		{
			if ((player[1].AupFlag) || (player[3].AupFlag))
			{
				player[2].Life = player[2].Life - 20;
				player[2].Ex = player[2].Ex + 20;
				if (player[1].flag)
				{
					player[1].Ex = player[1].Ex + 10;
				}
				if (player[3].flag)
				{
					player[3].Ex = player[3].Ex + 10;
				}

			}
			if ((!player[1].AupFlag) && (!player[3].AupFlag))
			{
				player[2].Life = player[2].Life - 10;
				player[2].Ex = player[2].Ex + 10;
				if (player[1].flag)
				{
					player[1].Ex = player[1].Ex + 10;
				}
				if (player[3].flag)
				{
					player[3].Ex = player[3].Ex + 10;
				}
			}
			PlaySoundMem(HitSound, DX_PLAYTYPE_BACK);

			return true;
		}
	}
	if ((player[3].flag) && (flag)) //�{
	{
		if (((player[3].pos.x - player[3].hitPosS.x) <= pos.x
			&& (player[3].pos.x + player[3].hitPosE.x) >= pos.x
			&& (player[3].pos.y + player[3].hitPosE.y) >= pos.y
			&& (player[3].pos.y - player[3].hitPosS.y) <= pos.y))
		{
			if ((player[0].AupFlag) || (player[2].AupFlag))
			{
				player[3].Life = player[3].Life - 20;
				player[3].Ex = player[3].Ex + 20;
				if (player[0].flag)
				{
					player[0].Ex = player[0].Ex + 10;
				}
				if (player[2].flag)
				{
					player[2].Ex = player[2].Ex + 10;
				}

			}
			if ((!player[0].AupFlag) && (!player[2].AupFlag))
			{
				player[3].Life = player[3].Life - 10;
				player[3].Ex = player[3].Ex + 10;
				if (player[0].flag)
				{
					player[0].Ex = player[0].Ex + 10;
				}
				if (player[2].flag)
				{
					player[2].Ex = player[2].Ex + 10;
				}
			}
			PlaySoundMem(HitSound, DX_PLAYTYPE_BACK);

			return true;
		}
	}
		

	return false;
}


bool PlayerAtackHitCheck(XY pos, XY size, int type,bool flag,MOVE_DIR Sdir)
{
	int Cnt = 0;
	int Cnt2 = 0;
	for (int i = 0; i < PLAYER_MAX; i++)
	{
		if (player[i].flag) 
		{
			//�����΂�
			if (((type == 0)&&(flag))&&(i % 2 ==1))
			{
				if (((player[i].pos.x - player[i].hitPosS.x) <= pos.x
				    && (player[i].pos.y + player[i].hitPosE.y) >= pos.y
			   	    && (player[i].pos.x + player[i].hitPosE.x) >= pos.x+5
			        && (player[i].pos.y - player[i].hitPosS.y) <= pos.y+size.y))
				{

					Cnt += 1;
				}
				if (((player[i].pos.x - player[i].hitPosS.x) <= pos.x +5
				  && (player[i].pos.y + player[i].hitPosE.y) >= pos.y +2
				  && (player[i].pos.x + player[i].hitPosE.x) >= pos.x +10
				  && (player[i].pos.y - player[i].hitPosS.y) <= pos.y +47))
				{

					Cnt += 1;
				}
				if (((player[i].pos.x - player[i].hitPosS.x) <= pos.x + 10
					&& (player[i].pos.y + player[i].hitPosE.y) >= pos.y + 5
					&& (player[i].pos.x + player[i].hitPosE.x) >= pos.x + 15
					&& (player[i].pos.y - player[i].hitPosS.y) <= pos.y + 45))
				{

					Cnt += 1;
				}
				if (((player[i].pos.x - player[i].hitPosS.x) <= pos.x + 15
					&& (player[i].pos.y + player[i].hitPosE.y) >= pos.y + 8
					&& (player[i].pos.x + player[i].hitPosE.x) >= pos.x + 20
					&& (player[i].pos.y - player[i].hitPosS.y) <= pos.y + 43))
				{

					Cnt += 1;
				}
				if (((player[i].pos.x - player[i].hitPosS.x) <= pos.x + 20
					&& (player[i].pos.y + player[i].hitPosE.y) >= pos.y + 11
					&& (player[i].pos.x + player[i].hitPosE.x) >= pos.x + 25
					&& (player[i].pos.y - player[i].hitPosS.y) <= pos.y + 39))
				{
					Cnt += 1;
				}
				if (((player[i].pos.x - player[i].hitPosS.x) <= pos.x + 25
					&& (player[i].pos.y + player[i].hitPosE.y) >= pos.y + 14
					&& (player[i].pos.x + player[i].hitPosE.x) >= pos.x + 30
					&& (player[i].pos.y - player[i].hitPosS.y) <= pos.y + 36))
				{

					Cnt += 1;
				}
				if (((player[i].pos.x - player[i].hitPosS.x) <= pos.x + 30
					&& (player[i].pos.y + player[i].hitPosE.y) >= pos.y + 17
					&& (player[i].pos.x + player[i].hitPosE.x) >= pos.x + 35
					&& (player[i].pos.y - player[i].hitPosS.y) <= pos.y + 33))
				{

					Cnt += 1;
				}
				if (((player[i].pos.x - player[i].hitPosS.x) <= pos.x + 35
					&& (player[i].pos.y + player[i].hitPosE.y) >= pos.y + 20
					&& (player[i].pos.x + player[i].hitPosE.x) >= pos.x + 40
					&& (player[i].pos.y - player[i].hitPosS.y) <= pos.y + 30))
				{

					Cnt += 1;
				}
				if (((player[i].pos.x - player[i].hitPosS.x) <= pos.x + 40
					&& (player[i].pos.y + player[i].hitPosE.y) >= pos.y + 23
					&& (player[i].pos.x + player[i].hitPosE.x) >= pos.x + 45
					&& (player[i].pos.y - player[i].hitPosS.y) <= pos.y + 27))
				{

					Cnt += 1;
				}

				if (Cnt != 0)
				{
					player[i].Life = player[i].Life - 20;
					player[i].Ex = player[i].Ex + 20;
					PlaySoundMem(HitSound, DX_PLAYTYPE_BACK);

					return true;

				}

			}


			//�}
			if (((type == 1) && (flag)) && (i % 2 == 0))
			{
				if	 (((player[i].pos.x - player[i].hitPosS.x) <= pos.x
					&& (player[i].pos.y + player[i].hitPosE.y) >= pos.y+15
					&& (player[i].pos.x + player[i].hitPosE.x) >= pos.x +12
					&& (player[i].pos.y - player[i].hitPosS.y) <= pos.y + 24))
				{
				

					Cnt2 += 1;
				}
				if (((player[i].pos.x - player[i].hitPosS.x) <= pos.x+12
					&& (player[i].pos.y + player[i].hitPosE.y) >= pos.y+15
					&& (player[i].pos.x + player[i].hitPosE.x) >= pos.x + 20
					&& (player[i].pos.y - player[i].hitPosS.y) <= pos.y + 24))
				{


					Cnt2 += 1;
				}
				if	 (((player[i].pos.x - player[i].hitPosS.x) <= pos.x+20
					&& (player[i].pos.y + player[i].hitPosE.y) >= pos.y +15
					&& (player[i].pos.x + player[i].hitPosE.x) >= pos.x + 28
					&& (player[i].pos.y - player[i].hitPosS.y) <= pos.y + 24))
				{
				

					Cnt2 += 1;
				}
				if (((player[i].pos.x - player[i].hitPosS.x) <= pos.x + 28
					&& (player[i].pos.y + player[i].hitPosE.y) >= pos.y + 15
					&& (player[i].pos.x + player[i].hitPosE.x) >= pos.x + 36
					&& (player[i].pos.y - player[i].hitPosS.y) <= pos.y + 24))
				{


					Cnt2 += 1;
				}
				if (((player[i].pos.x - player[i].hitPosS.x) <= pos.x + 36
					&& (player[i].pos.y + player[i].hitPosE.y) >= pos.y + 15
					&& (player[i].pos.x + player[i].hitPosE.x) >= pos.x + 44
					&& (player[i].pos.y - player[i].hitPosS.y) <= pos.y + 24))
				{

					Cnt2 += 1;
				}
				if (((player[i].pos.x - player[i].hitPosS.x) <= pos.x + 44
					&& (player[i].pos.y + player[i].hitPosE.y) >= pos.y + 15
					&& (player[i].pos.x + player[i].hitPosE.x) >= pos.x + 52
					&& (player[i].pos.y - player[i].hitPosS.y) <= pos.y + 24))
				{

					Cnt2 += 1;
				}



				if (Cnt2 != 0)
				{
					player[i].Life = player[i].Life - 20;
					player[i].Ex = player[i].Ex+20;
					PlaySoundMem(HitSound, DX_PLAYTYPE_BACK);
					return true;

				}
			}

		}
	}
	return false;
}

bool PlayerExHitCheck(XY pos, MOVE_DIR dir, int type, bool flag)
{
	int Cnt = 0;
	int Cnt2 = 0;
	for (int i = 0; i < PLAYER_MAX; i++)
	{
		if (player[i].flag)
		{

			if (((type == 0) && (flag)) && (i % 2 == 1) && (dir == DIR_RIGHT))
			{
				if (((player[i].pos.x - player[i].hitPosS.x) <= pos.x
					&& (player[i].pos.y + player[i].hitPosE.y) >= pos.y
					&& (player[i].pos.x + player[i].hitPosE.x) >= pos.x + 10
					&& (player[i].pos.y - player[i].hitPosS.y) <= pos.y + 48))
				{

					Cnt += 1;
				}
				if (((player[i].pos.x - player[i].hitPosS.x) <= pos.x + 10
					&& (player[i].pos.y + player[i].hitPosE.y) >= pos.y + 2
					&& (player[i].pos.x + player[i].hitPosE.x) >= pos.x + 20
					&& (player[i].pos.y - player[i].hitPosS.y) <= pos.y + 47))
				{

					Cnt += 1;
				}
				if (((player[i].pos.x - player[i].hitPosS.x) <= pos.x + 20
					&& (player[i].pos.y + player[i].hitPosE.y) >= pos.y + 5
					&& (player[i].pos.x + player[i].hitPosE.x) >= pos.x + 30
					&& (player[i].pos.y - player[i].hitPosS.y) <= pos.y + 45))
				{

					Cnt += 1;
				}
				if (((player[i].pos.x - player[i].hitPosS.x) <= pos.x + 30
					&& (player[i].pos.y + player[i].hitPosE.y) >= pos.y + 8
					&& (player[i].pos.x + player[i].hitPosE.x) >= pos.x + 40
					&& (player[i].pos.y - player[i].hitPosS.y) <= pos.y + 43))
				{

					Cnt += 1;
				}
				if (((player[i].pos.x - player[i].hitPosS.x) <= pos.x + 40
					&& (player[i].pos.y + player[i].hitPosE.y) >= pos.y + 11
					&& (player[i].pos.x + player[i].hitPosE.x) >= pos.x + 50
					&& (player[i].pos.y - player[i].hitPosS.y) <= pos.y + 39))
				{
					Cnt += 1;
				}
				if (((player[i].pos.x - player[i].hitPosS.x) <= pos.x + 50
					&& (player[i].pos.y + player[i].hitPosE.y) >= pos.y + 14
					&& (player[i].pos.x + player[i].hitPosE.x) >= pos.x + 60
					&& (player[i].pos.y - player[i].hitPosS.y) <= pos.y + 36))
				{

					Cnt += 1;
				}
				if (((player[i].pos.x - player[i].hitPosS.x) <= pos.x + 60
					&& (player[i].pos.y + player[i].hitPosE.y) >= pos.y + 17
					&& (player[i].pos.x + player[i].hitPosE.x) >= pos.x + 70
					&& (player[i].pos.y - player[i].hitPosS.y) <= pos.y + 33))
				{

					Cnt += 1;
				}
				if (((player[i].pos.x - player[i].hitPosS.x) <= pos.x + 70
					&& (player[i].pos.y + player[i].hitPosE.y) >= pos.y + 20
					&& (player[i].pos.x + player[i].hitPosE.x) >= pos.x + 80
					&& (player[i].pos.y - player[i].hitPosS.y) <= pos.y + 30))
				{

					Cnt += 1;
				}
				if (((player[i].pos.x - player[i].hitPosS.x) <= pos.x + 80
					&& (player[i].pos.y + player[i].hitPosE.y) >= pos.y + 23
					&& (player[i].pos.x + player[i].hitPosE.x) >= pos.x + 90
					&& (player[i].pos.y - player[i].hitPosS.y) <= pos.y + 27))
				{

					Cnt += 1;
				}

				if (Cnt != 0)
				{
					player[i].Life = player[i].Life - 1;
					player[i].Ex = player[i].Ex + 1;
					return true;

				}

			}

			if (((type == 0) && (flag)) && (i % 2 == 1) && (dir == DIR_LEFT))
			{
				if (((player[i].pos.x - player[i].hitPosS.x) <= pos.x + 5
					&& (player[i].pos.y + player[i].hitPosE.y) >= pos.y + 24
					&& (player[i].pos.x + player[i].hitPosE.x) >= pos.x + 10
					&& (player[i].pos.y - player[i].hitPosS.y) <= pos.y + 26))
				{

					Cnt += 1;
				}
				if (((player[i].pos.x - player[i].hitPosS.x) <= pos.x + 10
					&& (player[i].pos.y + player[i].hitPosE.y) >= pos.y + 23
					&& (player[i].pos.x + player[i].hitPosE.x) >= pos.x + 20
					&& (player[i].pos.y - player[i].hitPosS.y) <= pos.y + 27))
				{

					Cnt += 1;
				}
				if (((player[i].pos.x - player[i].hitPosS.x) <= pos.x + 20
					&& (player[i].pos.y + player[i].hitPosE.y) >= pos.y + 20
					&& (player[i].pos.x + player[i].hitPosE.x) >= pos.x + 30
					&& (player[i].pos.y - player[i].hitPosS.y) <= pos.y + 30))
				{

					Cnt += 1;
				}
				if (((player[i].pos.x - player[i].hitPosS.x) <= pos.x + 30
					&& (player[i].pos.y + player[i].hitPosE.y) >= pos.y + 17
					&& (player[i].pos.x + player[i].hitPosE.x) >= pos.x + 40
					&& (player[i].pos.y - player[i].hitPosS.y) <= pos.y + 33))
				{

					Cnt += 1;
				}
				if (((player[i].pos.x - player[i].hitPosS.x) <= pos.x + 40
					&& (player[i].pos.y + player[i].hitPosE.y) >= pos.y + 14
					&& (player[i].pos.x + player[i].hitPosE.x) >= pos.x + 50
					&& (player[i].pos.y - player[i].hitPosS.y) <= pos.y + 36))
				{

					Cnt += 1;
				}
				if (((player[i].pos.x - player[i].hitPosS.x) <= pos.x + 50
					&& (player[i].pos.y + player[i].hitPosE.y) >= pos.y + 11
					&& (player[i].pos.x + player[i].hitPosE.x) >= pos.x + 60
					&& (player[i].pos.y - player[i].hitPosS.y) <= pos.y + 39))
				{
					Cnt += 1;
				}
				if (((player[i].pos.x - player[i].hitPosS.x) <= pos.x + 60
					&& (player[i].pos.y + player[i].hitPosE.y) >= pos.y + 8
					&& (player[i].pos.x + player[i].hitPosE.x) >= pos.x + 70
					&& (player[i].pos.y - player[i].hitPosS.y) <= pos.y + 43))
				{

					Cnt += 1;
				}
				if (((player[i].pos.x - player[i].hitPosS.x) <= pos.x + 70
					&& (player[i].pos.y + player[i].hitPosE.y) >= pos.y + 5
					&& (player[i].pos.x + player[i].hitPosE.x) >= pos.x + 80
					&& (player[i].pos.y - player[i].hitPosS.y) <= pos.y + 45))
				{

					Cnt += 1;
				}
				if (((player[i].pos.x - player[i].hitPosS.x) <= pos.x + 80
					&& (player[i].pos.y + player[i].hitPosE.y) >= pos.y + 2
					&& (player[i].pos.x + player[i].hitPosE.x) >= pos.x + 90
					&& (player[i].pos.y - player[i].hitPosS.y) <= pos.y + 47))
				{

					Cnt += 1;
				}


				if (Cnt != 0)
				{
					player[i].Life = player[i].Life - 20;
					player[i].Ex = player[i].Ex + 20;
					return true;

				}
			}






			if (((type == 1) && (flag)) && (i % 2 == 0))
			{

				//�~���Ă����
				if (((player[i].pos.x - player[i].hitPosS.x) <= pos.x + 24
					&& (player[i].pos.y + player[i].hitPosE.y) >= pos.y + 5
					&& (player[i].pos.x + player[i].hitPosE.x) >= pos.x + 45
					&& (player[i].pos.y - player[i].hitPosS.y) <= pos.y + 21))
				{
					Cnt2 += 1;
				}
				if (((player[i].pos.x - player[i].hitPosS.x) <= pos.x + 24
					&& (player[i].pos.y + player[i].hitPosE.y) >= pos.y + 21
					&& (player[i].pos.x + player[i].hitPosE.x) >= pos.x + 45
					&& (player[i].pos.y - player[i].hitPosS.y) <= pos.y + 37))
				{
					Cnt2 += 1;
				}
				if (((player[i].pos.x - player[i].hitPosS.x) <= pos.x + 24
					&& (player[i].pos.y + player[i].hitPosE.y) >= pos.y + 37
					&& (player[i].pos.x + player[i].hitPosE.x) >= pos.x + 45
					&& (player[i].pos.y - player[i].hitPosS.y) <= pos.y + 53))
				{
					Cnt2 += 1;
				}
				if (((player[i].pos.x - player[i].hitPosS.x) <= pos.x + 24
					&& (player[i].pos.y + player[i].hitPosE.y) >= pos.y + 53
					&& (player[i].pos.x + player[i].hitPosE.x) >= pos.x + 45
					&& (player[i].pos.y - player[i].hitPosS.y) <= pos.y + 69))
				{
					Cnt2 += 1;
				}


				if (((player[i].pos.x - player[i].hitPosS.x) <= pos.x + 3
					&& (player[i].pos.y + player[i].hitPosE.y) >= pos.y + 5
					&& (player[i].pos.x + player[i].hitPosE.x) >= pos.x + 24
					&& (player[i].pos.y - player[i].hitPosS.y) <= pos.y + 21))
				{
					Cnt2 += 1;
				}
				if (((player[i].pos.x - player[i].hitPosS.x) <= pos.x + 3
					&& (player[i].pos.y + player[i].hitPosE.y) >= pos.y + 21
					&& (player[i].pos.x + player[i].hitPosE.x) >= pos.x + 24
					&& (player[i].pos.y - player[i].hitPosS.y) <= pos.y + 37))
				{
					Cnt2 += 1;
				}
				if (((player[i].pos.x - player[i].hitPosS.x) <= pos.x + 3
					&& (player[i].pos.y + player[i].hitPosE.y) >= pos.y + 37
					&& (player[i].pos.x + player[i].hitPosE.x) >= pos.x + 24
					&& (player[i].pos.y - player[i].hitPosS.y) <= pos.y + 53))
				{
					Cnt2 += 1;
				}
				if (((player[i].pos.x - player[i].hitPosS.x) <= pos.x + 3
					&& (player[i].pos.y + player[i].hitPosE.y) >= pos.y + 53
					&& (player[i].pos.x + player[i].hitPosE.x) >= pos.x + 24
					&& (player[i].pos.y - player[i].hitPosS.y) <= pos.y + 69))
				{
					Cnt2 += 1;
				}


				if (((player[i].pos.x - player[i].hitPosS.x) <= pos.x - 18
					&& (player[i].pos.y + player[i].hitPosE.y) >= pos.y + 5
					&& (player[i].pos.x + player[i].hitPosE.x) >= pos.x + 3
					&& (player[i].pos.y - player[i].hitPosS.y) <= pos.y + 21))
				{
					Cnt2 += 1;
				}
				if (((player[i].pos.x - player[i].hitPosS.x) <= pos.x - 18
					&& (player[i].pos.y + player[i].hitPosE.y) >= pos.y + 21
					&& (player[i].pos.x + player[i].hitPosE.x) >= pos.x + 3
					&& (player[i].pos.y - player[i].hitPosS.y) <= pos.y + 37))
				{
					Cnt2 += 1;
				}
				if (((player[i].pos.x - player[i].hitPosS.x) <= pos.x - 18
					&& (player[i].pos.y + player[i].hitPosE.y) >= pos.y + 37
					&& (player[i].pos.x + player[i].hitPosE.x) >= pos.x + 3
					&& (player[i].pos.y - player[i].hitPosS.y) <= pos.y + 53))
				{
					Cnt2 += 1;
				}
				if (((player[i].pos.x - player[i].hitPosS.x) <= pos.x - 18
					&& (player[i].pos.y + player[i].hitPosE.y) >= pos.y + 53
					&& (player[i].pos.x + player[i].hitPosE.x) >= pos.x + 3
					&& (player[i].pos.y - player[i].hitPosS.y) <= pos.y + 69))
				{
					Cnt2 += 1;
				}



				if (((player[i].pos.x - player[i].hitPosS.x) <= pos.x - 43
					&& (player[i].pos.y + player[i].hitPosE.y) >= pos.y + 5
					&& (player[i].pos.x + player[i].hitPosE.x) >= pos.x - 18
					&& (player[i].pos.y - player[i].hitPosS.y) <= pos.y + 21))
				{
					Cnt2 += 1;
				}
				if (((player[i].pos.x - player[i].hitPosS.x) <= pos.x - 43
					&& (player[i].pos.y + player[i].hitPosE.y) >= pos.y + 21
					&& (player[i].pos.x + player[i].hitPosE.x) >= pos.x - 18
					&& (player[i].pos.y - player[i].hitPosS.y) <= pos.y + 37))
				{
					Cnt2 += 1;
				}
				if (((player[i].pos.x - player[i].hitPosS.x) <= pos.x - 43
					&& (player[i].pos.y + player[i].hitPosE.y) >= pos.y + 37
					&& (player[i].pos.x + player[i].hitPosE.x) >= pos.x - 18
					&& (player[i].pos.y - player[i].hitPosS.y) <= pos.y + 53))
				{
					Cnt2 += 1;
				}
				if (((player[i].pos.x - player[i].hitPosS.x) <= pos.x - 43
					&& (player[i].pos.y + player[i].hitPosE.y) >= pos.y + 53
					&& (player[i].pos.x + player[i].hitPosE.x) >= pos.x - 18
					&& (player[i].pos.y - player[i].hitPosS.y) <= pos.y + 69))
				{
					Cnt2 += 1;
				}






				if (Cnt2 != 0)
				{
					player[i].Life = player[i].Life - 20;
					player[i].Ex = player[i].Ex + 20;

					PlaySoundMem(ExHitSound, DX_PLAYTYPE_BACK);

					return true;
				}
			}

			if (((type == 2) && (flag)) && (i % 2 == 1))
			{
				if (((player[i].pos.x - player[i].hitPosS.x) <= pos.x
					&& (player[i].pos.x + player[i].hitPosE.x) >= pos.x
					&& (player[i].pos.y + player[i].hitPosE.y) >= pos.y
					&& (player[i].pos.y - player[i].hitPosS.y) <= pos.y))
				{
					player[i].Life = player[i].Life - 30;
					player[i].Ex = player[i].Ex + 30;
					PlaySoundMem(ExHitSound, DX_PLAYTYPE_BACK);

					return true;
				}
			}
			if (((type == 3) && (flag)) && (i % 2 == 0))
			{
				//�}

				if (((player[i].pos.x - player[i].hitPosS.x) <= pos.x
					&& (player[i].pos.y + player[i].hitPosE.y) >= pos.y + 15
					&& (player[i].pos.x + player[i].hitPosE.x) >= pos.x + 12
					&& (player[i].pos.y - player[i].hitPosS.y) <= pos.y + 24))
				{


					Cnt2 += 1;
				}
				if (((player[i].pos.x - player[i].hitPosS.x) <= pos.x + 12
					&& (player[i].pos.y + player[i].hitPosE.y) >= pos.y + 15
					&& (player[i].pos.x + player[i].hitPosE.x) >= pos.x + 20
					&& (player[i].pos.y - player[i].hitPosS.y) <= pos.y + 24))
				{


					Cnt2 += 1;
				}
				if (((player[i].pos.x - player[i].hitPosS.x) <= pos.x + 20
					&& (player[i].pos.y + player[i].hitPosE.y) >= pos.y + 15
					&& (player[i].pos.x + player[i].hitPosE.x) >= pos.x + 28
					&& (player[i].pos.y - player[i].hitPosS.y) <= pos.y + 24))
				{


					Cnt2 += 1;
				}
				if (((player[i].pos.x - player[i].hitPosS.x) <= pos.x + 28
					&& (player[i].pos.y + player[i].hitPosE.y) >= pos.y + 15
					&& (player[i].pos.x + player[i].hitPosE.x) >= pos.x + 36
					&& (player[i].pos.y - player[i].hitPosS.y) <= pos.y + 24))
				{


					Cnt2 += 1;
				}
				if (((player[i].pos.x - player[i].hitPosS.x) <= pos.x + 36
					&& (player[i].pos.y + player[i].hitPosE.y) >= pos.y + 15
					&& (player[i].pos.x + player[i].hitPosE.x) >= pos.x + 44
					&& (player[i].pos.y - player[i].hitPosS.y) <= pos.y + 24))
				{

					Cnt2 += 1;
				}
				if (((player[i].pos.x - player[i].hitPosS.x) <= pos.x + 44
					&& (player[i].pos.y + player[i].hitPosE.y) >= pos.y + 15
					&& (player[i].pos.x + player[i].hitPosE.x) >= pos.x + 52
					&& (player[i].pos.y - player[i].hitPosS.y) <= pos.y + 24))
				{

					Cnt2 += 1;
				}



				if (Cnt2 != 0)
				{
					player[i].Life = player[i].Life - 30;
					player[i].Ex = player[i].Ex + 30;
					PlaySoundMem(ExHitSound, DX_PLAYTYPE_BACK);
					return true;


				}
			}
		}
	}
	//ExAtack.pos = { 0,0 };

	return false;

}

bool PlayerItemCheck(XY pos, int type)
{
	int Cnt = 0;
	for (int i = 0; i < PLAYER_MAX; i++)
	{
		if (player[i].flag)
		{

			if (type == 0) //�����G�i
			{
				if (((player[i].pos.x - player[i].hitPosS.x)  <= pos.x
					&& (player[i].pos.y + player[i].hitPosE.y) >= pos.y
					&& (player[i].pos.x + player[i].hitPosE.x) >= pos.x+24 
					&& (player[i].pos.y - player[i].hitPosS.y) <= pos.y+24))
				{
					Cnt += 1;
				}
				if (((player[i].pos.x - player[i].hitPosS.x) <= pos.x
					&& (player[i].pos.y + player[i].hitPosE.y) >= pos.y
					&& (player[i].pos.x + player[i].hitPosE.x) >= pos.x+24
					&& (player[i].pos.y - player[i].hitPosS.y) <= pos.y+48))
				{
					Cnt += 1;
				}
				if (((player[i].pos.x - player[i].hitPosS.x) <= pos.x
					&& (player[i].pos.y + player[i].hitPosE.y) >= pos.y
					&& (player[i].pos.x + player[i].hitPosE.x) >= pos.x+48
					&& (player[i].pos.y - player[i].hitPosS.y) <= pos.y+24))
				{
					Cnt += 1;
				}
				if (((player[i].pos.x - player[i].hitPosS.x) <= pos.x
					&& (player[i].pos.y + player[i].hitPosE.y) >= pos.y
					&& (player[i].pos.x + player[i].hitPosE.x) >= pos.x+48
					&& (player[i].pos.y - player[i].hitPosS.y) <= pos.y+48))
				{
					Cnt += 1;
				}
				//�����蔻��(���P���s��)
				/*if (((player[i].pos.x - player[i].hitPosS.x) <= pos.x
					&& (player[i].pos.y + player[i].hitPosE.y) >= pos.y
					&& (player[i].pos.x + player[i].hitPosE.x) >= pos.x + 12
					&& (player[i].pos.y - player[i].hitPosS.y) <= pos.y + 12))
				{
					Cnt += 1;
				}
				if (((player[i].pos.x - player[i].hitPosS.x) <= pos.x
					&& (player[i].pos.y + player[i].hitPosE.y) >= pos.y
					&& (player[i].pos.x + player[i].hitPosE.x) >= pos.x + 12
					&& (player[i].pos.y - player[i].hitPosS.y) <= pos.y + 24))
				{
					Cnt += 1;
				}
				if (((player[i].pos.x - player[i].hitPosS.x) <= pos.x
					&& (player[i].pos.y + player[i].hitPosE.y) >= pos.y
					&& (player[i].pos.x + player[i].hitPosE.x) >= pos.x + 12
					&& (player[i].pos.y - player[i].hitPosS.y) <= pos.y + 36))
				{
					Cnt += 1;
				}
				if (((player[i].pos.x - player[i].hitPosS.x) <= pos.x
					&& (player[i].pos.y + player[i].hitPosE.y) >= pos.y
					&& (player[i].pos.x + player[i].hitPosE.x) >= pos.x + 12
					&& (player[i].pos.y - player[i].hitPosS.y) <= pos.y + 48))
				{
					Cnt += 1;
				}
				if (((player[i].pos.x - player[i].hitPosS.x) <= pos.x
					&& (player[i].pos.y + player[i].hitPosE.y) >= pos.y
					&& (player[i].pos.x + player[i].hitPosE.x) >= pos.x + 24
					&& (player[i].pos.y - player[i].hitPosS.y) <= pos.y + 12))
				{
					Cnt += 1;
				}
				if (((player[i].pos.x - player[i].hitPosS.x) <= pos.x
					&& (player[i].pos.y + player[i].hitPosE.y) >= pos.y
					&& (player[i].pos.x + player[i].hitPosE.x) >= pos.x + 24
					&& (player[i].pos.y - player[i].hitPosS.y) <= pos.y + 36))
				{
					Cnt += 1;
				}

				if (((player[i].pos.x - player[i].hitPosS.x) <= pos.x
					&& (player[i].pos.y + player[i].hitPosE.y) >= pos.y
					&& (player[i].pos.x + player[i].hitPosE.x) >= pos.x + 36
					&& (player[i].pos.y - player[i].hitPosS.y) <= pos.y + 12))
				{
					Cnt += 1;
				}
				if (((player[i].pos.x - player[i].hitPosS.x) <= pos.x
					&& (player[i].pos.y + player[i].hitPosE.y) >= pos.y
					&& (player[i].pos.x + player[i].hitPosE.x) >= pos.x + 36
					&& (player[i].pos.y - player[i].hitPosS.y) <= pos.y + 24))
				{
					Cnt += 1;
				}
				if (((player[i].pos.x - player[i].hitPosS.x) <= pos.x
					&& (player[i].pos.y + player[i].hitPosE.y) >= pos.y
					&& (player[i].pos.x + player[i].hitPosE.x) >= pos.x + 36
					&& (player[i].pos.y - player[i].hitPosS.y) <= pos.y + 36))
				{
					Cnt += 1;
				}
				if (((player[i].pos.x - player[i].hitPosS.x) <= pos.x
					&& (player[i].pos.y + player[i].hitPosE.y) >= pos.y
					&& (player[i].pos.x + player[i].hitPosE.x) >= pos.x + 36
					&& (player[i].pos.y - player[i].hitPosS.y) <= pos.y + 48))
				{
					Cnt += 1;
				}

				if (((player[i].pos.x - player[i].hitPosS.x) <= pos.x
					&& (player[i].pos.y + player[i].hitPosE.y) >= pos.y
					&& (player[i].pos.x + player[i].hitPosE.x) >= pos.x + 48
					&& (player[i].pos.y - player[i].hitPosS.y) <= pos.y + 12))
				{
					Cnt += 1;
				}

				if (((player[i].pos.x - player[i].hitPosS.x) <= pos.x
					&& (player[i].pos.y + player[i].hitPosE.y) >= pos.y
					&& (player[i].pos.x + player[i].hitPosE.x) >= pos.x + 48
					&& (player[i].pos.y - player[i].hitPosS.y) <= pos.y + 36))
				{
					Cnt += 1;
				}*/




				if (Cnt != 0)
				{
					player[i].AupFlag = true;
					PlaySoundMem(GetSound, DX_PLAYTYPE_BACK);
					return true;

				}


			}
			if (((type == 1) && (i % 2 == 0)))
			{
				if (((player[i].pos.x - player[i].hitPosS.x) <= pos.x
					&& (player[i].pos.y + player[i].hitPosE.y) >= pos.y
					&& (player[i].pos.x + player[i].hitPosE.x) >= pos.x + 24
					&& (player[i].pos.y - player[i].hitPosS.y) <= pos.y + 24))
				{
					Cnt += 1;
				}
				if (((player[i].pos.x - player[i].hitPosS.x) <= pos.x
					&& (player[i].pos.y + player[i].hitPosE.y) >= pos.y
					&& (player[i].pos.x + player[i].hitPosE.x) >= pos.x + 24
					&& (player[i].pos.y - player[i].hitPosS.y) <= pos.y + 48))
				{
					Cnt += 1;
				}
				if (((player[i].pos.x - player[i].hitPosS.x) <= pos.x
					&& (player[i].pos.y + player[i].hitPosE.y) >= pos.y
					&& (player[i].pos.x + player[i].hitPosE.x) >= pos.x + 48
					&& (player[i].pos.y - player[i].hitPosS.y) <= pos.y + 24))
				{
					Cnt += 1;
				}
				if (((player[i].pos.x - player[i].hitPosS.x) <= pos.x
					&& (player[i].pos.y + player[i].hitPosE.y) >= pos.y
					&& (player[i].pos.x + player[i].hitPosE.x) >= pos.x + 48
					&& (player[i].pos.y - player[i].hitPosS.y) <= pos.y + 48))
				{
					Cnt += 1;
				}

				if (Cnt != 0)
				{
					player[i].Life -= 30;
					PlaySoundMem(GetSound, DX_PLAYTYPE_BACK);

					return true;

				}
				
			}	

			if (((type == 1) && (i % 2 == 1)))
			{
				if (((player[i].pos.x - player[i].hitPosS.x) <= pos.x
					&& (player[i].pos.y + player[i].hitPosE.y) >= pos.y
					&& (player[i].pos.x + player[i].hitPosE.x) >= pos.x + 24
					&& (player[i].pos.y - player[i].hitPosS.y) <= pos.y + 24))
				{
					Cnt += 1;
				}
				if (((player[i].pos.x - player[i].hitPosS.x) <= pos.x
					&& (player[i].pos.y + player[i].hitPosE.y) >= pos.y
					&& (player[i].pos.x + player[i].hitPosE.x) >= pos.x + 24
					&& (player[i].pos.y - player[i].hitPosS.y) <= pos.y + 48))
				{
					Cnt += 1;
				}
				if (((player[i].pos.x - player[i].hitPosS.x) <= pos.x
					&& (player[i].pos.y + player[i].hitPosE.y) >= pos.y
					&& (player[i].pos.x + player[i].hitPosE.x) >= pos.x + 48
					&& (player[i].pos.y - player[i].hitPosS.y) <= pos.y + 24))
				{
					Cnt += 1;
				}
				if (((player[i].pos.x - player[i].hitPosS.x) <= pos.x
					&& (player[i].pos.y + player[i].hitPosE.y) >= pos.y
					&& (player[i].pos.x + player[i].hitPosE.x) >= pos.x + 48
					&& (player[i].pos.y - player[i].hitPosS.y) <= pos.y + 48))
				{
					Cnt += 1;
				}

				if (Cnt != 0)
				{
					player[i].Life += 30;
					PlaySoundMem(GetSound, DX_PLAYTYPE_BACK);

					return true;
				}
			}



			if (((type == 2) /*&& (i % 2 == 1)*/))
			{
				if (((player[i].pos.x - player[i].hitPosS.x) <= pos.x
					&& (player[i].pos.y + player[i].hitPosE.y) >= pos.y
					&& (player[i].pos.x + player[i].hitPosE.x) >= pos.x + 24
					&& (player[i].pos.y - player[i].hitPosS.y) <= pos.y + 24))
				{
					Cnt += 1;
				}
				if (((player[i].pos.x - player[i].hitPosS.x) <= pos.x
					&& (player[i].pos.y + player[i].hitPosE.y) >= pos.y
					&& (player[i].pos.x + player[i].hitPosE.x) >= pos.x + 24
					&& (player[i].pos.y - player[i].hitPosS.y) <= pos.y + 48))
				{
					Cnt += 1;
				}
				if (((player[i].pos.x - player[i].hitPosS.x) <= pos.x
					&& (player[i].pos.y + player[i].hitPosE.y) >= pos.y
					&& (player[i].pos.x + player[i].hitPosE.x) >= pos.x + 48
					&& (player[i].pos.y - player[i].hitPosS.y) <= pos.y + 24))
				{
					Cnt += 1;
				}
				if (((player[i].pos.x - player[i].hitPosS.x) <= pos.x
					&& (player[i].pos.y + player[i].hitPosE.y) >= pos.y
					&& (player[i].pos.x + player[i].hitPosE.x) >= pos.x + 48
					&& (player[i].pos.y - player[i].hitPosS.y) <= pos.y + 48))
				{
					Cnt += 1;
				}
				if(Cnt != 0)
				{
					player[i].Life = player[i].Life - player[i].LifeLimit / 10 * 3;
					PlaySoundMem(ExpSound, DX_PLAYTYPE_BACK);

					return true;

				}
			}

			if (((type == 3) && (i % 2 == 0)))
			{
				if (((player[i].pos.x - player[i].hitPosS.x) <= pos.x
					&& (player[i].pos.y + player[i].hitPosE.y) >= pos.y
					&& (player[i].pos.x + player[i].hitPosE.x) >= pos.x + 24
					&& (player[i].pos.y - player[i].hitPosS.y) <= pos.y + 24))
				{
					Cnt += 1;
				}
				if (((player[i].pos.x - player[i].hitPosS.x) <= pos.x
					&& (player[i].pos.y + player[i].hitPosE.y) >= pos.y
					&& (player[i].pos.x + player[i].hitPosE.x) >= pos.x + 24
					&& (player[i].pos.y - player[i].hitPosS.y) <= pos.y + 48))
				{
					Cnt += 1;
				}
				if (((player[i].pos.x - player[i].hitPosS.x) <= pos.x
					&& (player[i].pos.y + player[i].hitPosE.y) >= pos.y
					&& (player[i].pos.x + player[i].hitPosE.x) >= pos.x + 48
					&& (player[i].pos.y - player[i].hitPosS.y) <= pos.y + 24))
				{
					Cnt += 1;
				}
				if (((player[i].pos.x - player[i].hitPosS.x) <= pos.x
					&& (player[i].pos.y + player[i].hitPosE.y) >= pos.y
					&& (player[i].pos.x + player[i].hitPosE.x) >= pos.x + 48
					&& (player[i].pos.y - player[i].hitPosS.y) <= pos.y + 48))
				{
					Cnt += 1;
				}
				if(Cnt != 0)
				{
					player[i].Life += 30;
					PlaySoundMem(GetSound, DX_PLAYTYPE_BACK);

					return true;
				}
			}
			if (((type == 3) && (i % 2 == 1)))
			{
				if (((player[i].pos.x - player[i].hitPosS.x) <= pos.x
					&& (player[i].pos.y + player[i].hitPosE.y) >= pos.y
					&& (player[i].pos.x + player[i].hitPosE.x) >= pos.x + 24
					&& (player[i].pos.y - player[i].hitPosS.y) <= pos.y + 24))
				{
					Cnt += 1;
				}
				if (((player[i].pos.x - player[i].hitPosS.x) <= pos.x
					&& (player[i].pos.y + player[i].hitPosE.y) >= pos.y
					&& (player[i].pos.x + player[i].hitPosE.x) >= pos.x + 24
					&& (player[i].pos.y - player[i].hitPosS.y) <= pos.y + 48))
				{
					Cnt += 1;
				}
				if (((player[i].pos.x - player[i].hitPosS.x) <= pos.x
					&& (player[i].pos.y + player[i].hitPosE.y) >= pos.y
					&& (player[i].pos.x + player[i].hitPosE.x) >= pos.x + 48
					&& (player[i].pos.y - player[i].hitPosS.y) <= pos.y + 24))
				{
					Cnt += 1;
				}
				if (((player[i].pos.x - player[i].hitPosS.x) <= pos.x
					&& (player[i].pos.y + player[i].hitPosE.y) >= pos.y
					&& (player[i].pos.x + player[i].hitPosE.x) >= pos.x + 48
					&& (player[i].pos.y - player[i].hitPosS.y) <= pos.y + 48))
				{
					Cnt += 1;
				}
				if(Cnt !=0)
				{
					player[i].Life -= 30;
					PlaySoundMem(GetSound, DX_PLAYTYPE_BACK);

					return true;


				}


			}
			if (type == 4) //�����G�i(�K�E��)
			{
				if (((player[i].pos.x - player[i].hitPosS.x) <= pos.x
					&& (player[i].pos.y + player[i].hitPosE.y) >= pos.y
					&& (player[i].pos.x + player[i].hitPosE.x) >= pos.x + 24
					&& (player[i].pos.y - player[i].hitPosS.y) <= pos.y + 24))
				{
					Cnt += 1;
				}
				if (((player[i].pos.x - player[i].hitPosS.x) <= pos.x
					&& (player[i].pos.y + player[i].hitPosE.y) >= pos.y
					&& (player[i].pos.x + player[i].hitPosE.x) >= pos.x + 24
					&& (player[i].pos.y - player[i].hitPosS.y) <= pos.y + 48))
				{
					Cnt += 1;
				}
				if (((player[i].pos.x - player[i].hitPosS.x) <= pos.x
					&& (player[i].pos.y + player[i].hitPosE.y) >= pos.y
					&& (player[i].pos.x + player[i].hitPosE.x) >= pos.x + 48
					&& (player[i].pos.y - player[i].hitPosS.y) <= pos.y + 24))
				{
					Cnt += 1;
				}
				if (((player[i].pos.x - player[i].hitPosS.x) <= pos.x
					&& (player[i].pos.y + player[i].hitPosE.y) >= pos.y
					&& (player[i].pos.x + player[i].hitPosE.x) >= pos.x + 48
					&& (player[i].pos.y - player[i].hitPosS.y) <= pos.y + 48))
				{
					Cnt += 1;
				}

				if (Cnt != 0)
				{
					player[i].Ex = player[i].Ex + 30;
					PlaySoundMem(GetSound, DX_PLAYTYPE_BACK);
					return true;

				}

			}
		}
	}
	return false;
}

void PlayerReset(void)
{
	for (int i = 0; i < PLAYER_MAX; i++)
	{
		player[i].pos = player[i].defaltpos;
		player[i].Life = player[i].LifeLimit;
		Atack.flag = false;
		ITEM.flag = false;
		player[i].moveDir = DIR_LEFT;

		if (i % 2 == 0)
		{
			player[i].moveDir = DIR_RIGHT;
		}
		/*player[]*/

	}
	for (int i = 0; i < SHOT_MAX; i++)
	{
		shot[i].flag = false;
	}
	for (int i = 0; i < EXATACK_MAX; i++)
	{
		ExAtack[i].flag = false;
	}

}
