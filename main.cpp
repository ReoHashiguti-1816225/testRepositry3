#include "DxLib.h"
#include "main.h"
#include "player.h"
#include "stage.h"
#include "keycheck.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	//GMODE = MODE_INIT;


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

	
	playerInit();
	StageSystemInit();
	
	while (ProcessMessage() == 0   // while=0の場合繰り返し
		&& CheckHitKey(KEY_INPUT_ESCAPE) == 0) //&=演算記号 &&=どちらも満たしている場合
	{
		

		ClsDrawScreen();	

		
		

		playerUpdate();

		{
		
			StageDraw();
			playerDraw();
		}
		ScreenFlip();
	}

	DxLib_End();

	return 0;				// ソフトの終了 
}







