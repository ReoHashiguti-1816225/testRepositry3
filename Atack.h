#pragma once
#define EXATACK_MAX 10

typedef struct {
	bool flag;
	MOVE_DIR moveDir;	// 向いている向き
	XY pos;				// 位置


	XY size;			// ｻｲｽﾞ
	XY size2;			// ｻｲｽﾞ

	XY offsetSize;		// ｷｬﾗ中央からの左上位置
	//HIT_TYPE type;
	int animCnt;		// ｱﾆﾒｰｼｮﾝ用
	int movespeed;
	int lifeMax;
	int life;
	float defaltangle;
	float angle;
	float angle2;
	int type;			//鶏側or人間側
	int Cnt;		//デバッグ用

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
