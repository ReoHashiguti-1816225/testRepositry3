#pragma once

#define SCREEN_SIZE_X 960/*864*/	//画面の横ｻｲｽﾞ
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
	MODE_SELECT,
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
enum {
	PLAYER_KEY_CONFIG_UP,
	PLAYER_KEY_CONFIG_DOWN,
	PLAYER_KEY_CONFIG_LEFT,
	PLAYER_KEY_CONFIG_RIGHT,
	PLAYER_KEY_CONFIG_FIRE,
	PLAYER_KEY_CONFIG_ATACK,
	PLAYER_KEY_CONFIG_EXATACK,
	PLAYER_KEY_CONFIG_MAX,
};

typedef struct
{
	XY pos;
	XY defaltpos;
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
	bool AupFlag;		//アイテムによる攻撃力アップフラグ
	int Life;				//体力
	int LifeLimit;			//体力上限
	int Ex;					//必殺ゲージ
	int ExLimit;			//必殺ゲージ上限
	int WinCnt;				//勝利数
	//int Damage;
	int keyConfig[PLAYER_KEY_CONFIG_MAX];
	int keyPressed[PLAYER_KEY_CONFIG_MAX];		//今押されているキー
	int keyLastPressed[PLAYER_KEY_CONFIG_MAX];	//1フレーム前に押されたキー
	int keyDown[PLAYER_KEY_CONFIG_MAX];			//今押されたキー
	int tyep;
	int Usetype;
	int Ptype;
	
}CHARACTER;

extern GameMode GMODE;

void Init(void);
void Title(void);
void TitleDraw(void);

void Select(void);
void SelectDraw(void);


void Game(void);
void GameDraw(void);

void End(void);
void EndDraw(void);
