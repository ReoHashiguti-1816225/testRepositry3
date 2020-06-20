#pragma once
#define SHOT_MAX 100

typedef struct {
	bool flag;
	MOVE_DIR moveDir;	// �����Ă������
	XY pos;				// �ʒu
	XY size;			// ����
	XY offsetSize;		// ��ג�������̍���ʒu
	//HIT_TYPE type;
	int animCnt;		// ��Ұ��ݗp
	int movespeed;
	int lifeMax;
	int life;
	int type;			//�{��or�l�ԑ�
}SHOT;


extern SHOT shot[SHOT_MAX];


void ShotSysinit(void);
void ShotInit(void);
void Shotcontrol(void);
void ShotDraw(void);
void BulletFire(XY pPos, MOVE_DIR pDir, int type);
SHOT Getshot(int i);
void DeleteShot(int i);
//bool bulletKeyCheck(int i);