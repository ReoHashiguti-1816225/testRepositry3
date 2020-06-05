#pragma once

#define SCREEN_SIZE_X 960/*864*/	//��ʂ̉�����
#define SCREEN_SIZE_Y 720	//��ʂ̏c����

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
	MOVE_DIR moveDir;	// �����Ă������
	XY offsetSize;		// ��ג�������̍���ʒu
	XY hitPosS;			// �����蔻��p����
	XY hitPosE;			// �����蔻��p�E��
	bool runFlag;		// �����Ă��邩
	bool jumpFlag;		// �ެ��ߒ���
	bool headFlag;
	int animCnt;		// ��Ұ��ݗp
	XY_F velocity;		// �ړ����x
	bool flag;
	bool AupFlag;		//�A�C�e���ɂ��U���̓A�b�v�t���O
	int Life;				//�̗�
	int LifeLimit;			//�̗͏��
	int Ex;					//�K�E�Q�[�W
	int ExLimit;			//�K�E�Q�[�W���
	int WinCnt;				//������
	//int Damage;
	int keyConfig[PLAYER_KEY_CONFIG_MAX];
	int keyPressed[PLAYER_KEY_CONFIG_MAX];		//��������Ă���L�[
	int keyLastPressed[PLAYER_KEY_CONFIG_MAX];	//1�t���[���O�ɉ����ꂽ�L�[
	int keyDown[PLAYER_KEY_CONFIG_MAX];			//�������ꂽ�L�[
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
