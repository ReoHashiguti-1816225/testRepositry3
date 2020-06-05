#pragma once
#include "DxLib.h"

#define INIT_VELOCITY 50		// ｼﾞｬﾝﾌﾟの初期加速度
#define SECOND_PER_FRAME 0.45	// 1フレーム当たりの秒数	

#define ACC_RUN 0.25				// 走る加速度
#define ACC_STOP 0.30			// 停止加速度
#define VELOCITY_X_MAX 5		// ﾌﾟﾚｲﾔｰ最大速度

#define PLAYER_MAX 4
#define PLAYER_IMAGE_MAX 4
#define PLAYER_TYPE 2






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
