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

	SetWindowText("�t�P�̃`�L��");
	if (DxLib_Init() == -1)		// �c�w���C�u��������������
	{
		return -1;			// �G���[���N�����璼���ɏI��
	}

	//SoundHundle = LoadSoundMem("Sound/bgm_maoudamashii_8bit27.mp3");

	SetDrawScreen(DX_SCREEN_BACK);

	
	playerInit();
	StageSystemInit();
	
	while (ProcessMessage() == 0   // while=0�̏ꍇ�J��Ԃ�
		&& CheckHitKey(KEY_INPUT_ESCAPE) == 0) //&=���Z�L�� &&=�ǂ�����������Ă���ꍇ
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

	return 0;				// �\�t�g�̏I�� 
}







