#pragma once
#define EXATACK_MAX 10

typedef struct {
	bool flag;
	MOVE_DIR moveDir;	// �����Ă������
	XY pos;				// �ʒu


	XY size;			// ����
	XY size2;			// ����

	XY offsetSize;		// ��ג�������̍���ʒu
	//HIT_TYPE type;
	int animCnt;		// ��Ұ��ݗp
	int movespeed;
	int lifeMax;
	int life;
	float defaltangle;
	float angle;
	float angle2;
	int type;			//�{��or�l�ԑ�
	int Cnt;		//�f�o�b�O�p

}ATACK;

extern ATACK Atack/*[PLAYER_TYPE]*/;
extern ATACK ExAtack[EXATACK_MAX];

void AtackSysinit(void);
void AtackInit(void);
void Atackcontrol(void);
void AtackStartup(XY pPos, MOVE_DIR pDir, int type);

void AtackDraw(void);

void ExAtackSysinit(void);
void ExAtackInit(void);
void ExAtackcontrol(void);

void ExAtackStartup(XY pPos, MOVE_DIR pDir, int type);

void ExAtackDraw(void);

//void BulletFire(XY pPos, MOVE_DIR pDir);
