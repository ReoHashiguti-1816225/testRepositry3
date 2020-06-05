#pragma once
#define SHOT_MAX 100

typedef struct {
	bool flag;
	MOVE_DIR moveDir;	// 向いている向き
	XY pos;				// 位置
	XY size;			// ｻｲｽﾞ
	XY offsetSize;		// ｷｬﾗ中央からの左上位置
	int animCnt;		// ｱﾆﾒｰｼｮﾝ用
	int movespeed;
	int lifeMax;
	int life;
	int type;			//鶏側or人間側
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