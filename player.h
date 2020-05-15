#pragma once
#include "DxLib.h"

#define INIT_VELOCITY 50		// ｼﾞｬﾝﾌﾟの初期加速度
#define SECOND_PER_FRAME 0.45	// 1フレーム当たりの秒数	

#define ACC_RUN 0.25				// 走る加速度
#define ACC_STOP 0.30			// 停止加速度
#define VELOCITY_X_MAX 5		// ﾌﾟﾚｲﾔｰ最大速度

#define PLAYER_MAX 2
#define PLAYER_IMAGE_MAX 4

//typedef struct
//{
//	XY pos;
//	MOVE_DIR moveDir;	// 向いている向き
//	XY offsetSize;		// ｷｬﾗ中央からの左上位置
//	XY hitPosS;			// 当たり判定用左上
//	XY hitPosE;			// 当たり判定用右下
//	bool runFlag;		// 走っているか
//	bool jumpFlag;		// ｼﾞｬﾝﾌﾟ中か
//	int animCnt;		// ｱﾆﾒｰｼｮﾝ用
//	XY_F velocity;		// 移動速度
//	bool flag;
//}PLAYER;




extern PLAYER player[PLAYER_MAX];

void playerInit(void);
void playerUpdate(void);
void playerDraw(void);
bool PlayerKeyCheck(int);
bool PlayerJumpKeyCheck(int);

//bool PlayerKeyCheck(int);


