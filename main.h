#pragma once

#define SCREEN_SIZE_X 864	//画面の横ｻｲｽﾞ
#define SCREEN_SIZE_Y 720	//画面の縦ｻｲｽﾞ

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
	MOVE_DIR moveDir;	// 向いている向き
	XY offsetSize;		// ｷｬﾗ中央からの左上位置
	XY hitPosS;			// 当たり判定用左上
	XY hitPosE;			// 当たり判定用右下
	bool runFlag;		// 走っているか
	bool jumpFlag;		// ｼﾞｬﾝﾌﾟ中か
	bool headFlag;
	int animCnt;		// ｱﾆﾒｰｼｮﾝ用
	XY_F velocity;		// 移動速度
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
