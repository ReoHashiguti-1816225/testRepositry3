#include "DxLib.h"
#include "main.h"
#include "player.h"
#include "stage.h"
#include "shot.h"
#include "Atack.h"
#include "アイテム.h"
#include "keycheck.h"


GameMode GMODE;

int Cnt;
int SelectCnt1p = 0;
int SelectCnt2p = 0;
int Flashing = 0;
int Start = 180;
int Start2 = 3;
int SelectSound;
int CancelSound;
bool Howto;
bool HowtoItem;
int taiimege;
bool lock;
bool lock2;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	GMODE = MODE_INIT;


	SetGraphMode(
		SCREEN_SIZE_X, SCREEN_SIZE_Y,   // int ScreenSizeX, ScreenSizeY
		32                              // int ColorBitDepth
										// int RefreshRate = 60
	);
	
	

	ChangeWindowMode(true);

	SetWindowText("逆襲のチキン");

	if (DxLib_Init() == -1)		// ＤＸライブラリ初期化処理
	{
		return -1;			// エラーが起きたら直ちに終了
	}

	//SoundHundle = LoadSoundMem("Sound/bgm_maoudamashii_8bit27.mp3");

	SetDrawScreen(DX_SCREEN_BACK);



	SelectSound = LoadSoundMem("Sound/選択音.mp3");
	CancelSound = LoadSoundMem("Sound/キャンセル.mp3");
	ShotSysinit();
	AtackSysinit();
	
	ExAtackSysinit();

	StageSystemInit();
	
	while (ProcessMessage() == 0   // while=0の場合繰り返し
		&& CheckHitKey(KEY_INPUT_ESCAPE) == 0) //&=演算記号 &&=どちらも満たしている場合
	{
		

		ClsDrawScreen();	

		switch (GMODE)
		{

		case MODE_INIT:
			Init();
			GMODE = MODE_TITLE;

			break;
		case MODE_TITLE:

			
			Title();
			TitleDraw();
			break;
		case MODE_SELECT:
			Select();
			SelectDraw();
			
			break;
		case MODE_HOWTO:
			HowTo();
			HowToDraw();

			break;
		case MODE_GAME:
			/*PlayMusic("Sound/bgm_maoudamashii_8bit24.mp3", DX_PLAYTYPE_LOOP);*/

			Game();
			GameDraw();

			/*if (CheckHitKey(KEY_INPUT_O))
			{
				GMODE = MODE_END;
			}*/

			break;
		case MODE_END:
			End();
			EndDraw();


			break;
		case MODE_MAX:
			break;
		default:
			break;
		}

		
		ScreenFlip();
	}

	DxLib_End();

	return 0;				// ソフトの終了 
}




void Init(void)
{
	lock = false;
	lock2 = false;
	Howto = false;
	HowtoItem = false;

	iteminit();
	AtackInit();
	ExAtackInit();
	playerInit();
	ShotInit();
	PlayMusic("Sound/タイトル.mp3", DX_PLAYTYPE_LOOP);
	SetVolumeMusic(200);

}



void Title(void)
{
	taiimege = LoadGraph("image/タイトル.png", true);

	if ((CheckHitKey(KEY_INPUT_DOWN)||(CheckHitKey(KEY_INPUT_S))))
	{
		Howto = true;
	}

	if ((CheckHitKey(KEY_INPUT_UP) || (CheckHitKey(KEY_INPUT_W))))
	{
		Howto = false;
	}

	if ((CheckHitKey(KEY_INPUT_RETURN) && (Howto == false)))
	{
		StopMusic();
		GMODE = MODE_SELECT;
		PlayMusic("Sound/セレクト.mp3", DX_PLAYTYPE_LOOP);
	}
	if ((CheckHitKey(KEY_INPUT_RETURN) && (Howto == true)))
	{
		StopMusic();
		GMODE = MODE_HOWTO;
		PlayMusic("Sound/説明.mp3", DX_PLAYTYPE_LOOP);
	}
}



void TitleDraw(void)
{
	Flashing++;

	DrawBox(0, 0, SCREEN_SIZE_X, SCREEN_SIZE_Y, 0xffffff, true);


	DrawFormatString(0, 0, 0xffffff, "タイトル");
	//Extend
	DrawGraph(70, 0,/* SCREEN_SIZE_X, SCREEN_SIZE_Y,*/ taiimege, true);


	//if (Flashing / 30 % 2 == 0)
	//{
	//	DrawFormatString(SCREEN_SIZE_X / 2 - 100, SCREEN_SIZE_Y / 2 + 80, 0x000000, "PRESS ENTER KEY");
	//}

	DrawFormatString(SCREEN_SIZE_X / 2 - 100, SCREEN_SIZE_Y / 2 + 80, 0x000000, "GAME START");

	DrawFormatString(SCREEN_SIZE_X / 2 - 100, SCREEN_SIZE_Y / 2 + 140, 0x000000, "HOW TO PLAY");

	if (Howto == false)
	{
		DrawFormatString(SCREEN_SIZE_X / 2 - 130, SCREEN_SIZE_Y / 2 + 80, 0x000000, "→");
	}
	if (Howto == true)
	{
		DrawFormatString(SCREEN_SIZE_X / 2 - 130, SCREEN_SIZE_Y / 2 + 140, 0x000000, "→");
	}
	DrawRotaGraph(200, 600, 4, 0, playerimage[0][0], true);
	//DrawRotaGraph(100, 600, 2.5, 0, playerimage[2][0], true);

	DrawRotaGraph(750, 500, 4, 0, playerimage[1][0], true);
	//DrawGraph(600, 600, playerimage[3][0], true);
	
}

void Select(void)
{
	if (lock == false)
	{
		if (CheckHitKey(KEY_INPUT_A))
		{
			SelectCnt1p = 0;
		}
		if (CheckHitKey(KEY_INPUT_D))
		{
			SelectCnt1p = 1;
		}
		if (CheckHitKey(KEY_INPUT_SPACE))
		{
			lock = true;
			PlaySoundMem(SelectSound, DX_PLAYTYPE_BACK);

		}
	
	}
	if (CheckHitKey(KEY_INPUT_N))
	{
		if (lock == true)
		{
			lock = false;
			PlaySoundMem(CancelSound, DX_PLAYTYPE_BACK);
		}
	}
	if (lock2 == false)
	{
		if (CheckHitKey(KEY_INPUT_LEFT))
		{
			SelectCnt2p = 0;
		}
		if (CheckHitKey(KEY_INPUT_RIGHT))
		{
			SelectCnt2p = 1;
		}
		if (CheckHitKey(KEY_INPUT_NUMPAD0))
		{
			lock2 = true;
			PlaySoundMem(SelectSound, DX_PLAYTYPE_BACK);

		}
	}
	if (CheckHitKey(KEY_INPUT_ADD))
	{
		if (lock2 == true)
		{
			lock2 = false;
			PlaySoundMem(CancelSound, DX_PLAYTYPE_BACK);
		}
	}
	if ((!lock) && (!lock2))
	{
		if ((CheckHitKey(KEY_INPUT_N) || (CheckHitKey(KEY_INPUT_ADD))))
		{
			GMODE = MODE_INIT;
		}
	}
	if ((lock == true) && (lock2 == true))
	{
		Start--;
	}
	if ((lock == false) || (lock2 == false))
	{
		Start = 180;
		Start2 = 3;
	}
	if (SelectCnt1p < 0)
	{
		SelectCnt1p = 0;
	}
	if (SelectCnt1p > 1)
	{
		SelectCnt1p = 1;
	}
	if (SelectCnt2p < 0)
	{
		SelectCnt2p = 0;
	}
	if (SelectCnt2p > 1)
	{
		SelectCnt2p = 1;
	}
	if (SelectCnt1p == 0)
	{
		player[0].flag = true;
		player[2].flag = false;

	}
	if (SelectCnt1p == 1)
	{
		player[0].flag = false;
		player[2].flag = true;
	}
	if (SelectCnt2p == 0)
	{
		player[1].flag = true;
		player[3].flag = false;

	}
	if (SelectCnt2p == 1)
	{
		player[1].flag = false;
		player[3].flag = true;
	}
	if (Start <= 0)
	{
		StopMusic();

		GMODE = MODE_GAME;
		PlayMusic("Sound/バトル2.mp3", DX_PLAYTYPE_BACK);
		SetVolumeMusic(200);

	}

}
void SelectDraw(void)
{
	DrawGraph(120, SCREEN_SIZE_Y / 2, playerimage[0][0], true);
	DrawString(140, 300, "A", 0xffffff);
	DrawGraph(240, SCREEN_SIZE_Y / 2, playerimage[2][0], true);
	DrawString(260, 300, "D", 0xffffff);

	DrawGraph(600, SCREEN_SIZE_Y / 2, playerimage[1][0], true);
	DrawString(620, 300, "←", 0xffffff);

	DrawGraph(720, SCREEN_SIZE_Y / 2, playerimage[3][0], true);
	DrawString(740, 300, "→", 0xffffff);


	if (SelectCnt1p == 0)
	{
		DrawBox(120, 360, 168, 408, 0xffffff, false);
		if (lock == true)
		{
			DrawBox(120, 360, 168, 408, 0xff0000, false);
		}
		DrawString(70,500, "にわとり\n\n\n必殺技;ドリルくちばし\n\nエネルギーをくちばしに集中、ドリル状に成型し、\n相手を貫く", 0xffffff);

	}
	if (SelectCnt1p == 1)
	{
		DrawBox(240, 360, 288, 408, 0xffffff, false);
		if (lock == true)
		{
			DrawBox(240, 360, 288, 408, 0xff0000, false);
		}
		DrawString(70, 500, "にわとり改\n\n\n必殺技;赤玉子発射\n\n通常の玉子より威力、速度共に高い赤玉子を発射する", 0xffffff);

	}
	if (SelectCnt2p == 0)
	{
		DrawBox(600, 360, 648, 456, 0xffffff, false);
		if (lock2 == true)
		{
			DrawBox(600, 360, 648, 456, 0xff0000, false);
		}
		DrawString(550, 500, "社長\n\n\n必殺技;支援要請　ハンマー投擲\n\n後ろで控えている作業員にハンマーを投げさせ\n攻撃する", 0xffffff);

	}
	if (SelectCnt2p == 1)
	{
		DrawBox(720, 360, 768, 456, 0xffffff, false);
		if (lock2 == true)
		{
			DrawBox(720, 360, 768, 456, 0xff0000, false);
		}
		DrawString(550, 500, "作業員\n\n\n必殺技;鉄パイプ投げ\n\n壁の補強などに使う予定だった鉄パイプを掴み\n投げる", 0xffffff);
	}

	DrawString(250, 50, "どちらも選んでいない時キャンセルキー : タイトルへ", 0xffffff);


	DrawString(100, 100, "Which character do you use?", 0xffffff);
	DrawString(140, 150, "SPACE ; 決定", 0xffffff);
	DrawString(140, 200, "N ; キャンセル", 0xffffff);


	DrawString(600, 100, "Which character do you use?", 0xffffff);
	DrawString(600, 150, "NUMPAD 0 ; 決定", 0xffffff);
	DrawString(600, 200, "NUMPAD + ; キャンセル", 0xffffff);


	/*if ((lock == true) && (lock2 == true))
	{
		DrawFormatString(400, 100, 0xffffff, "START ; %d", Start);
	}*/
	if (Start < 180)
	{
		//DrawString(400, 130, "3", 0xffffff);
		DrawFormatString(450, 100, 0xffffff, "%d", Start2);
	}
	if (Start < 120)
	{
		Start2 = 2;
		//DrawString(400, 130, "2", 0xffffff);
	}
	if (Start < 60)
	{
		Start2 = 1;
		//DrawString(400, 130, "1", 0xffffff);
	}
}

void HowTo(void)
{
	if ((CheckHitKey(KEY_INPUT_RIGHT) || (CheckHitKey(KEY_INPUT_D))))
	{
		HowtoItem = true;
	}

	if ((CheckHitKey(KEY_INPUT_LEFT) || (CheckHitKey(KEY_INPUT_A))))
	{
		HowtoItem = false;
	}
	if ((CheckHitKey(KEY_INPUT_N) || (CheckHitKey(KEY_INPUT_NUMPAD0))))
	{
		if (HowtoItem == true)
		{
			StopMusic();
			GMODE = MODE_INIT;
		}
	}

}
void HowToDraw(void)
{
	if (HowtoItem == false)
	{
		DrawLine(SCREEN_SIZE_X / 2, SCREEN_SIZE_Y / 2, SCREEN_SIZE_X / 2, SCREEN_SIZE_Y, 0xffffff);
		DrawLine(0, SCREEN_SIZE_Y / 2, SCREEN_SIZE_X, SCREEN_SIZE_Y / 2, 0xffffff);

		DrawString(100, 100, "ルール\n\nこのゲームは対戦ゲームです。お互いのキャラクターを動かし攻撃し合い、体力を削り合います。\n\n相手の体力を０にしたプレイヤーがラウンドの勝者となり、2ラウンド先取したプレイヤーの勝利となります。\n\n近接攻撃は遠距離より威力は高めですが当てた相手には少しの間近接が当たらなくなります\n\n必殺ゲージを最大まで溜めることで必殺技が使用できます\n\n必殺ゲージは攻撃を当てる、当てられる他に出現するアイテムを取得することで溜めることができます",0xffffff);

		DrawString(650, 300, "Dキー\n→キー", 0xffffff);
		DrawString(730, 310, "次へ", 0xffffff);


		DrawString(100, 380, "左プレイヤー", 0xffffff);
		DrawString(100, 410, "Aキー : 左移動", 0xffffff);
		DrawString(100, 440, "Dキー : 右移動", 0xffffff);
		DrawString(100, 470, "Wキー : ジャンプ", 0xffffff);
		DrawString(100, 500, "SPACE : 射撃", 0xffffff);
		DrawString(100, 530, "Bキー : 近接攻撃", 0xffffff);
		DrawString(100, 560, "Gキー : 必殺ゲージが満タン時必殺技", 0xffffff);

		//体力枠
		for (int i = 0; i < player[0].LifeLimit; i++)
		{
			DrawBox(0 + i, 0,
				9 + i, 15, 0xffffff, true);
		}
		//体力
		for (int i = 0; i < player[0].Life; i++)
		{
			DrawBox(2 + i, 2,
				7 + i, 13, 0x5FFE01, true);
		}
		//気力ゲージ
		for (int i = 0; i < player[0].ExLimit; i++)
		{
			DrawBox(0 + i, 15,
				10 + i, 24, 0xffffff, false);
		}
		//気力
		for (int i = 0; i < 100; i++)
		{
			DrawBox(0 + i, 17,
				8 + i, 22, 0x0000ff, true);
		}
		DrawString(140, 15, "体力", 0xffffff);

		DrawString(0, 30, "必殺ゲージ", 0xffffff);

		DrawString(800, 15, "体力", 0xffffff);
		DrawString(870, 30, "必殺ゲージ", 0xffffff);

		DrawString(600, 380, "右プレイヤー", 0xffffff);
		DrawString(600, 410, "←キー : 左移動", 0xffffff);
		DrawString(600, 440, "→キー : 右移動", 0xffffff);
		DrawString(600, 470, "↑キー : ジャンプ", 0xffffff);
		DrawString(600, 500, "NUMPAD　0 : 射撃", 0xffffff);
		DrawString(600, 530, "NUMPAD ENTER : 近接攻撃", 0xffffff);
		DrawString(600, 560, "NUMPAD　5 : 必殺ゲージが満タン時必殺技", 0xffffff);
		
		
		for (int i = 0; i < player[3].LifeLimit; i++)
		{
			DrawBox(SCREEN_SIZE_X, 0,
				958 - i, 15, 0xffffff, true);
		}
		for (int i = 0; i < player[3].Life; i++)
		{
			DrawBox(SCREEN_SIZE_X - 2, 2,
				SCREEN_SIZE_X - i, 13, 0x5FFE01, true);

		}
		//気力ゲージ
		//気力
		for (int i = 0; i < player[3].ExLimit; i++)
		{
			DrawBox(SCREEN_SIZE_X, 15,
				958 - i, 24, 0xffffff, true);
		}


		for (int i = 0; i < 100; i++)
		{
			DrawBox(SCREEN_SIZE_X, 17,
				960 - i, 22, 0x0000ff, true);
		}

		DrawString(900, 700, "1/2", 0xffffff);
	}
	if (HowtoItem == true)
	{
		DrawLine(SCREEN_SIZE_X / 2, 100, SCREEN_SIZE_X / 2, SCREEN_SIZE_Y, 0xffffff);

		DrawLine(0, 100, SCREEN_SIZE_X, 100, 0xffffff);

		DrawString(400, 50, "アイテム　効果説明", 0xffffff);

		DrawString(150, 50, "Aキー\n←キー", 0xffffff);
		DrawString(230, 60, "戻る", 0xffffff);

		DrawString(650, 50, "Nキー\nNUMPAD 0", 0xffffff);
		DrawString(730, 60, "タイトルへ", 0xffffff);

		DrawString(160, 140, "左プレイヤー", 0xffffff);


		DrawGraph(100, 200, itemimage[0], true);
		DrawString(148, 220, ": 射撃攻撃力上昇", 0xffffff);

		DrawGraph(100, 300, itemimage[1], true);
		DrawString(148, 320, ": 体力減少", 0xffffff);

		DrawGraph(100, 400, itemimage[2], true);
		DrawString(148, 420, ": 体力20%減少", 0xffffff);

		DrawGraph(100, 500, itemimage[3], true);
		DrawString(148, 520, ": 体力回復", 0xffffff);

		DrawGraph(100, 600, itemimage[4], true);
		DrawString(148, 620, ": 必殺ゲージ上昇", 0xffffff);


		DrawString(660, 140, "右プレイヤー", 0xffffff);

		DrawGraph(600, 200, itemimage[0], true);
		DrawString(648, 220, ": 射撃攻撃力上昇", 0xffffff);

		DrawGraph(600, 300, itemimage[1], true);
		DrawString(648, 320, ": 体力回復", 0xffffff);

		DrawGraph(600, 400, itemimage[2], true);
		DrawString(648, 420, ": 体力20%減少", 0xffffff);

		DrawGraph(600, 500, itemimage[3], true);
		DrawString(648, 520, ": 体力減少", 0xffffff);

		DrawGraph(600, 600, itemimage[4], true);
		DrawString(648, 620, ": 必殺ゲージ上昇", 0xffffff);

		DrawString(900, 700, "2/2", 0xffffff);

	}
}

void Game(void)
{

	{
		playerUpdate();
		itemUpdate();
		Shotcontrol();
		Atackcontrol();
		ExAtackcontrol();
	}


}
void GameDraw(void)
{
	//DrawBox(0, 0, SCREEN_SIZE_X, SCREEN_SIZE_Y, 0xffffff, true);
	{

		StageDraw();
		playerDraw();
		itemDraw();
		ShotDraw();

		AtackDraw();
		ExAtackDraw();
	}

}

void End(void)
{
	//StopMusic();
	if (CheckHitKey(KEY_INPUT_P))
	{
		GMODE = MODE_INIT;
	}
}
void EndDraw(void)
{


	if (Cnt / 30 % 2 == 0)
	{
		DrawFormatString(SCREEN_SIZE_X / 2 - 50, SCREEN_SIZE_Y / 2 + 80, 0xffffff, "PRESS SPACE KEY");
	}
}






