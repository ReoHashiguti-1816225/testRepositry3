#pragma once
#include "DxLib.h"

#define INIT_VELOCITY 50		// �ެ��߂̏��������x
#define SECOND_PER_FRAME 0.45	// 1�t���[��������̕b��	

#define ACC_RUN 0.25				// ��������x
#define ACC_STOP 0.30			// ��~�����x
#define VELOCITY_X_MAX 5		// ��ڲ԰�ő呬�x

#define PLAYER_MAX 4
#define PLAYER_IMAGE_MAX 4
#define PLAYER_TYPE 2

//typedef struct
//{
//	XY pos;
//	MOVE_DIR moveDir;	// �����Ă������
//	XY offsetSize;		// ��ג�������̍���ʒu
//	XY hitPosS;			// �����蔻��p����
//	XY hitPosE;			// �����蔻��p�E��
//	bool runFlag;		// �����Ă��邩
//	bool jumpFlag;		// �ެ��ߒ���
//	int animCnt;		// ��Ұ��ݗp
//	XY_F velocity;		// �ړ����x
//	bool flag;
//}PLAYER;





extern CHARACTER player[PLAYER_MAX];
extern int playerimage[PLAYER_MAX][PLAYER_IMAGE_MAX];

void playerInit(void);
void playerUpdate(void);
void playerDraw(void);
bool PlayerKeyCheck(int);
bool PlayerJumpKeyCheck(int);
bool PlayerShotKeyCheck(int);
bool PlayerAtackKeyCheck(int);
bool PlayerExAtackKeyCheck(int);

bool PlayerShotHitCheck(XY pos, bool flag,/* XY size,*/ MOVE_DIR Sdir,int j);

bool PlayerAtackHitCheck(XY pos,XY size, int type, bool flag, MOVE_DIR Sdir);

bool PlayerExHitCheck(XY pos,  MOVE_DIR dir, int type, bool flag);

bool PlayerItemCheck(XY pos, int type);


void PlayerReset(void);
void SoundChange(void);
