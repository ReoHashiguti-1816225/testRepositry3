#pragma once

#define SCREEN_SIZE_X 864	//��ʂ̉�����
#define SCREEN_SIZE_Y 720	//��ʂ̏c����

#define G 9.8
#define ACC_G 10

typedef struct {
	int x;
	int y;
}XY;

typedef struct {
	float x;
	float y;
}XY_F;

enum GameMode {
	MODE_INIT,
	MODE_TITLE,
	MODE_GAME,
	MODE_END,
	MODE_MAX
};

enum MOVE_DIR {
	DIR_UP,
	DIR_RIGHT,
	DIR_DOWN,
	DIR_LEFT,
	DIR_MAX
};

typedef struct
{
	XY pos;
	MOVE_DIR moveDir;	// �����Ă������
	XY offsetSize;		// ��ג�������̍���ʒu
	XY hitPosS;			// �����蔻��p����
	XY hitPosE;			// �����蔻��p�E��
	bool runFlag;		// �����Ă��邩
	bool jumpFlag;		// �ެ��ߒ���
	bool headFlag;
	int animCnt;		// ��Ұ��ݗp
	XY_F velocity;		// �ړ����x
	bool flag;
	int Life;
	int LifeLimit;
	int Ex;
	int ExLimit;

}PLAYER;

//void Init(void);
//void Title(void);
//void TitleDraw(void);
//
//void Game(void);
//void GameDraw(void);
//
//void End(void);
//void EndDraw(void);
