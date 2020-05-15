#pragma once
#include "DxLib.h"

#define INIT_VELOCITY 50		// �ެ��߂̏��������x
#define SECOND_PER_FRAME 0.45	// 1�t���[��������̕b��	

#define ACC_RUN 0.25				// ��������x
#define ACC_STOP 0.30			// ��~�����x
#define VELOCITY_X_MAX 5		// ��ڲ԰�ő呬�x

#define PLAYER_MAX 2
#define PLAYER_IMAGE_MAX 4

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




extern PLAYER player[PLAYER_MAX];

void playerInit(void);
void playerUpdate(void);
void playerDraw(void);
bool PlayerKeyCheck(int);
bool PlayerJumpKeyCheck(int);

//bool PlayerKeyCheck(int);


