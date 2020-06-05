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
int Start;
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

			if (CheckHitKey(KEY_INPUT_RETURN))
			{
				StopMusic();
				GMODE = MODE_SELECT;
				PlayMusic("Sound/セレクト.mp3", DX_PLAYTYPE_LOOP);


			}
			Title();
			TitleDraw();
			break;
		case MODE_SELECT:
			Select();
			SelectDraw();
			
			break;
		case MODE_GAME:

			Game();
			GameDraw();


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
	Start = 190;
	iteminit();
	AtackInit();
	ExAtackInit();
	playerInit();
	ShotInit();
	PlayMusic("Sound/タイトル.mp3", DX_PLAYTYPE_LOOP);
}



void Title(void)
{
	
	taiimege = LoadGraph("image/タイトル.png", true);

}



void TitleDraw(void)
{
	Flashing++;

	DrawBox(0, 0, SCREEN_SIZE_X, SCREEN_SIZE_Y, 0xffffff, true);


	DrawFormatString(0, 0, 0xffffff, "タイトル");
//Extend
	DrawGraph(70, 0,/* SCREEN_SIZE_X, SCREEN_SIZE_Y,*/ taiimege, true);


	if (Flashing / 30 % 2 == 0)
	{
		DrawFormatString(SCREEN_SIZE_X / 2 - 100, SCREEN_SIZE_Y / 2 + 80, 0x000000, "PRESS ENTER KEY");
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
		}
	
	}
	if (CheckHitKey(KEY_INPUT_N))
	{
		lock = false;
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
		}
	}
	if (CheckHitKey(KEY_INPUT_NUMPADENTER))
	{
		lock2 = false;
	}

	if ((lock == true) && (lock2 == true))
	{
		Start--;
	}
	if ((lock == false) || (lock2 == false))
	{
		Start = 190;
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
	if (Start < 0)
	{
		StopMusic();

		GMODE = MODE_GAME;

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
		DrawString(140, 500, "にわとり\n\n\n必殺技;ドリルくちばし", 0xffffff);
	}
	if (SelectCnt1p == 1)
	{
		DrawBox(240, 360, 288, 408, 0xffffff, false);
		if (lock == true)
		{
			DrawBox(240, 360, 288, 408, 0xff0000, false);
		}
		DrawString(140, 500, "にわとり改\n\n\n必殺技;赤玉子発射", 0xffffff);

	}
	if (SelectCnt2p == 0)
	{
		DrawBox(600, 360, 648, 456, 0xffffff, false);
		if (lock2 == true)
		{
			DrawBox(600, 360, 648, 456, 0xff0000, false);
		}
		DrawString(640, 500, "社長\n\n\n必殺技;支援要請　ハンマー投擲", 0xffffff);

	}
	if (SelectCnt2p == 1)
	{
		DrawBox(720, 360, 768, 456, 0xffffff, false);
		if (lock2 == true)
		{
			DrawBox(720, 360, 768, 456, 0xff0000, false);
		}
		DrawString(640, 500, "作業員\n\n\n必殺技;鉄パイプ投げ", 0xffffff);
	}

	DrawString(100, 100, "Which character do you use?", 0xffffff);
	DrawString(140, 150, "SPACE ; 決定", 0xffffff);
	DrawString(140, 200, "N ; キャンセル", 0xffffff);


	DrawString(600, 100, "Which character do you use?", 0xffffff);
	DrawString(600, 150, "NUMPAD 0 ; 決定", 0xffffff);
	DrawString(600, 200, "NUMPAD ENTER ; キャンセル", 0xffffff);


	if ((lock == true) && (lock2 == true))
	{
		DrawFormatString(400, 100, 0xffffff, "START ; %d", Start);
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






