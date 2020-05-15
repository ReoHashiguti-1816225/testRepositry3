#include "DxLib.h"
#include "main.h"
#include "player.h"
#include "keycheck.h"
#include "stage.h"

PLAYER player[PLAYER_MAX];
int playerimage[PLAYER_MAX][PLAYER_IMAGE_MAX];
int p1Lifeimage;
int jumpCnt[PLAYER_MAX];
int jumpFrame[PLAYER_MAX];

XY movedpos;




void playerInit(void)
{
	for (int i = 0; i < PLAYER_MAX; i++)
	{
		player[i].pos = { SCREEN_SIZE_X / 2,0 };
		player[i].flag = true;
		player[i].velocity = { 0,0 };
		//player.jumpFlag = false;
		player[i].moveDir = DIR_RIGHT;
		player[i].hitPosS = { 0,  0 };									// 鶏の左上
		player[i].hitPosE = { 48,  40 };									// の右下
		if(i % 2 == 1)
		{
			player[i].hitPosS = { 0,  0 };									// 人間の左上
			player[i].hitPosE = { 48,  96 };								// 人間の右下
		}
		player[0].Life = 300;
		player[0].LifeLimit = 300;
		player[1].Life = 500;
		player[1].LifeLimit = 00;

		player[i].Ex = 0;
		player[i].ExLimit = 100;
		
		p1Lifeimage = LoadGraph("image/体力メーター.png", true);
		jumpFrame[i] = 15;
		jumpCnt[i] = 0;
	}
	LoadDivGraph("image/tori.png", 4, 4, 1, 48, 48, playerimage[0]);
	LoadDivGraph("image/社長.png", 4, 4, 1, 48, 96, playerimage[1]);

}


void playerUpdate(void)
{
	for (int i = 0; i < PLAYER_MAX; i++)
	{
		XY tmpPos;

		XY movedPos = player[i].pos;

		// offsetは今のﾌﾟﾚｲﾔｰの1ﾏｽあとの座標
		XY movedOffset = movedPos;
		XY movedOffset2 = movedPos;
		XY movedOffset3 = movedPos;
		XY tmpindex;

		//player.pos.y += 2;
		player[i].runFlag = false;
		//デバッグ用
		if (CheckHitKey(KEY_INPUT_LEFT))
		{
			player[0].Life--;
		}
		if (CheckHitKey(KEY_INPUT_RIGHT))
		{
			player[0].Life++;
		}
		if (CheckHitKey(KEY_INPUT_DOWN))
		{
			player[0].Ex--;
		}
		if (CheckHitKey(KEY_INPUT_UP))
		{
			player[0].Ex++;
		}

		if (player[0].Life > player[0].LifeLimit)
		{
			player[0].Life = player[0].LifeLimit;
		}
		if (player[0].Ex > player[0].ExLimit)
		{
			player[0].Ex = player[0].ExLimit;
		}

		/*if (CheckHitKey(KEY_INPUT_W))
		{
			DrawString(SCREEN_SIZE_X/2, SCREEN_SIZE_Y/2, "hit", 0xffffff);
		}*/
		// ﾌﾟﾚｲﾔｰの移動	(キー操作)
		if (player[i].flag)
		{
			if (PlayerKeyCheck(i))
			{
				if (player[i].moveDir == DIR_RIGHT) 					// 右
				{
					player[i].velocity.x += ACC_RUN;					// 速度の更新
					player[i].runFlag = true;
					if (player[i].velocity.x > VELOCITY_X_MAX) {
						player[i].velocity.x = VELOCITY_X_MAX;
					}
					
				}

				if (player[i].moveDir == DIR_LEFT) {								// 左			
					player[i].velocity.x -= ACC_RUN;				// 速度の更新
					player[i].runFlag = true;
					if (player[i].velocity.x < -VELOCITY_X_MAX) {
						player[i].velocity.x = -VELOCITY_X_MAX;
					}
				}
				player[i].animCnt++;
			}
			// 止まった時の減速処理
			if (!player[i].runFlag) {
				if (player[i].velocity.x > 0) {
					player[i].velocity.x -= ACC_STOP;
					if (player[i].velocity.x < 0) {
						player[i].velocity.x = 0;
					}
				}
				if (player[i].velocity.x < 0) {
					player[i].velocity.x += ACC_STOP;
					if (player[i].velocity.x > 0) {
						player[i].velocity.x = 0;
					}
				}
			}

			// ﾌﾟﾚｲﾔｰの移動(左右)
			movedPos.x += player[i].velocity.x * 1;	// 距離の更新

			if (player[i].velocity.x > 0) {							// 右
				movedOffset.x = movedPos.x + player[i].hitPosE.x;
			}
			if (player[i].velocity.x < 0) {							// 左
				movedOffset.x = movedPos.x - player[i].hitPosS.x;
			}
			//ﾌﾟﾚｲﾔｰの頭上の中心のｵﾌｾｯﾄ
			movedOffset2 = movedOffset;
			movedOffset2.y = movedPos.y - player[i].hitPosS.y;
			//ﾌﾟﾚｲﾔｰの足下の中心のｵﾌｾｯﾄ
			movedOffset3 = movedOffset;
			movedOffset3.y = movedPos.y + player[i].hitPosE.y - 1;			// ‐1は調整

			//SetOffset(OFFSET_LEFT_RIGHT);

			if (IsPass(movedOffset) && IsPass(movedOffset2) && IsPass(movedOffset3)) {		// movedOffsetはﾌﾟﾚｲﾔｰの中心movedOffset2はﾌﾟﾚｲﾔｰの頭上の中心movedOffset3はﾌﾟﾚｲﾔｰの足下の中心
				player[i].pos = movedPos;													// 
			}
			else {
				tmpPos = mapPosToMoveIndex(movedOffset, player[i].headFlag, player[i].velocity);
				if (player[i].velocity.x > 0) {			// 右
					player[i].pos.x = tmpPos.x - player[i].hitPosE.x;
				}
				if (player[i].velocity.x < 0) {			// 左
					player[i].pos.x = tmpPos.x + player[i].hitPosS.x;
				}
				movedPos = player[i].pos;
				player[i].velocity.x = 0;
			}

			// 重力
			movedPos = player[i].pos;

			movedPos.y -= player[i].velocity.y * SECOND_PER_FRAME;
			player[i].velocity.y -= ACC_G * SECOND_PER_FRAME;

			// ﾌﾞﾛｯｸのﾁｪｯｸ
			// 頭上のﾌﾞﾛｯｸのﾁｪｯｸ

			movedOffset = movedPos;
			movedOffset.y = movedPos.y - player[i].hitPosS.y;
			movedOffset2 = movedOffset;							// 左上
			movedOffset2.x = movedPos.x - player[i].hitPosS.x;
			movedOffset3 = movedOffset;							// 右上
			movedOffset3.x = movedPos.x + player[i].hitPosE.x - 1;
			//	SetOffset(OFFSET_HEAD);

			if (IsPass(movedOffset) && IsPass(movedOffset2) && IsPass(movedOffset3))
			{
				player[i].pos = movedPos;
			}
			else {
			/*	player[i].headFlag = true;*/
				//tmpPos = mapPosToMoveIndex(movedOffset, player[i].headFlag, player[i].velocity);
				tmpindex = mapPosToIndex(movedOffset);
				tmpindex.y++;
				tmpPos = mapIndexToPos(tmpindex);
				
				player[i].pos.y = tmpPos.y + player[i].hitPosS.y;
				player[i].velocity.y *= -1;
			}
			movedPos = player[i].pos;


			// 足下のﾌﾞﾛｯｸのﾁｪｯｸ

			movedOffset = movedPos;
			movedOffset.y = movedPos.y + player[i].hitPosE.y;
			movedOffset.y = movedPos.y + player[i].hitPosE.y;
			movedOffset2 = movedOffset;							// 左上
			movedOffset2.x = movedPos.x - player[i].hitPosS.x;
			movedOffset3 = movedOffset;							// 右上
			movedOffset3.x = movedPos.x + player[i].hitPosE.x - 1;

			//	SetOffset(OFFSET_FOOT);

			if (IsPass(movedOffset) && IsPass(movedOffset2) && IsPass(movedOffset3)) {
				player[i].pos = movedPos;
			}
			else {
				tmpPos = mapPosToMoveIndex(movedOffset, player[i].headFlag, player[i].velocity);
				player[i].pos.y = tmpPos.y - player[i].hitPosE.y;
				player[i].velocity.y = 0;
				player[i].jumpFlag = false;
			}
			movedPos = player[i].pos;

			//　ｼﾞｬﾝﾌﾟ
			// 1ﾏｽのところではジャンプしない
			movedOffset = movedPos;
			movedOffset.y = movedPos.y - player[i].hitPosS.y;
			movedOffset2 = movedOffset;							// 左上
			movedOffset2.x = movedPos.x - player[i].hitPosS.x;
			movedOffset3 = movedOffset;							// 右上
			movedOffset3.x = movedPos.x + player[i].hitPosE.x - 1;


			//SetOffset(OFFSET_NOTJUMP);
			if (IsPass(movedOffset) && IsPass(movedOffset2) && IsPass(movedOffset3))
			{

				if (!player[i].jumpFlag)
				{
					if (PlayerJumpKeyCheck(i))
					{
						jumpCnt[i]++;
						if (jumpCnt[i] < jumpFrame[i])
						{
							player[i].velocity.y = 25;
						}
						if (player[i].headFlag)
						{
							jumpCnt[i] = jumpFrame[i];
						}
					}
					else
					{
						jumpCnt[i] = 0;
						player[i].jumpFlag = true;
					}
				}
			}
			else
			{
				jumpCnt[i] = 15;
			}
			movedPos = player[i].pos;

			//// ﾄﾗｯﾌﾟの判定
			//// ﾃﾚﾎﾟｰﾄ
			//if (!TelIsPass(player[i].pos)) {
			//	player[i].pos = { 100000 , 0 };
			//}

			//// 針ブロック
			//if (!NeedleIsPass(player[i].pos)) {
			//	TobichiriGenerator(player[i].pos);
			//	player[i].flag = false;
			//}

			// ｼﾞｬﾝﾌﾟﾌﾞﾛｯｸ
			// 1ﾏｽのところではジャンプしない
			movedOffset = movedPos;
			movedOffset.y = movedPos.y - player[i].hitPosS.y;
			movedOffset2 = movedOffset;							// 左上
			movedOffset2.x = movedPos.x - player[i].hitPosS.x;
			movedOffset3 = movedOffset;							// 右上
			movedOffset3.x = movedPos.x + player[i].hitPosE.x - 1;
			//SetOffset(OFFSET_NOTJUMP);
			if (IsPass(movedOffset) && IsPass(movedOffset2) && IsPass(movedOffset3)) {
				movedOffset.y = movedPos.y + player[i].hitPosE.y;		// 足元
				/*if (!JumpIsPass(movedOffset)) {
					player[i].velocity.y = 80;
				}*/
			}
			movedPos = player[i].pos;

			//// セーブ
			//if (!SaveIsPass(player[i].pos)) 
			//{
			//	savePos[i] = player[i].pos;
			//}

			//if (!GoalIsPass(player[i].pos)) {
			//	if (!player[i].goalFlag) {
			//		player[i].flag = false;
			//		player[i].goalFlag = true;
			//		player[i].jyuni = goalCnt;
			//		goalCnt++;
			//	}
			//}

			//// 画面外にﾌﾟﾚｲﾔｰが出たら
			//if (player[i].pos.y > SCREEN_SIZE_Y)
			//{
			//	player[i].flag = false;
			//}

			//if (trgKey[BACK]) {
			//	player[i].selectFlag = false;
			//}


			//if (bulletKeyCheck(i))
			//{
			//	if (player[i].flag == true)
			//	{
			//		XY Shotpos = player[i].pos;
			//		if (player[i].jumpFlag == true)
			//		{
			//			Shotpos.y -= 5;
			//		}
			//		if (player[i].moveDir == DIR_RIGHT)
			//		{
			//			BulletFire({ Shotpos.x + player[i].offsetSize.x,Shotpos.y - 3 },
			//				player[i].moveDir);
			//		}
			//		else if (player[i].moveDir == DIR_LEFT)
			//		{
			//			BulletFire({ player[i].pos.x - player[i].offsetSize.x - 3, player[i].pos.y - 3 },
			//				player[i].moveDir);

			//		}
			//	}

			//}

		}
		//else {	// ﾌﾟﾚｰﾔｰが死んだとき
		//	if (!player[i].goalFlag) {
		//		player[i].pos = savePos[i];
		//		player[i].velocity = { 0,0 };
		//		if (trgKey[ENTER]) {
		//			player[i].flag = true;
		//		}
		//	}
		//}
		
		//player[i].animCnt++;
	}



		//自分版
		//// 足下のﾌﾞﾛｯｸのﾁｪｯｸ
		//	movedOffset = movedPos;
		//	movedOffset.y = movedPos.y + player[i].hitPosE.y;
		//	movedOffset.y = movedPos.y + player[i].hitPosE.y;
		//	movedOffset2 = movedOffset;							// 左上
		//	movedOffset2.x = movedPos.x - player[i].hitPosS.x;
		//	movedOffset3 = movedOffset;							// 右上
		//	movedOffset3.x = movedPos.x + player[i].hitPosE.x - 1;
		////	SetOffset(OFFSET_FOOT);
		//	if (IsPass(movedOffset) && IsPass(movedOffset2) && IsPass(movedOffset3)) {
		//		player[i].pos = movedPos;
		//	}
		//	else {
		//		tmpPos = MapPosToMoveIndex(movedOffset, player[i].headFlag, player[i].velocity);
		//		player[i].pos.y = tmpPos.y - player[i].hitPosE.y;
		//		player[i].velocity.y = 0;
		//		player[i].jumpFlag = false;
		//	}
		//	movedPos = player[i].pos;


	////PlayerKeyCheck(player);
	//movedOffset = movedPos;
	//movedOffset.y = movedPos.y - player.hitPosS.y;
	//movedOffset2 = movedOffset;							// 左上
	//movedOffset2.x = movedPos.x - player.hitPosS.x;
	//movedOffset3 = movedOffset;							// 右上
	//movedOffset3.x = movedPos.x + player.hitPosE.x - 1;
	//if (CheckHitKey(KEY_INPUT_A))
	//{

	//	player.moveDir = DIR_LEFT;

	//	player.velocity.x -= ACC_RUN;					// 速度の更新
	//	player.runFlag = true;
	//	if (player.velocity.x > VELOCITY_X_MAX) {
	//		player.velocity.x = VELOCITY_X_MAX;
	//	}
	//	player.animCnt++;

	//
	//}
	//if (CheckHitKey(KEY_INPUT_D))
	//{
	//	player.moveDir = DIR_RIGHT;

	//	player.velocity.x += ACC_RUN;				// 速度の更新
	//	player.runFlag = true;
	//	if (player.velocity.x < -VELOCITY_X_MAX) {
	//		player.velocity.x = -VELOCITY_X_MAX;
	//	}

	//	player.animCnt++;

	//}

	//// 止まった時の減速処理
	//if (!player.runFlag) {
	//	if (player.velocity.x > 0) {
	//		player.velocity.x -= ACC_STOP;
	//		if (player.velocity.x < 0) {
	//			player.velocity.x = 0;
	//		}
	//	}
	//	if (player.velocity.x < 0) {
	//		player.velocity.x += ACC_STOP;
	//		if (player.velocity.x > 0) {
	//			player.velocity.x = 0;
	//		}
	//	}
	//}	
	//movedPos.x += player.velocity.x * 1;	// 距離の更新


	//
	//
	//if (player.pos.y >= SCREEN_SIZE_Y / 2)
	//{
	//	player.velocity.y = 0;
	//}


	////SetOffset(OFFSET_NOTJUMP);
	//if (IsPass(movedOffset) && IsPass(movedOffset2) && IsPass(movedOffset3))
	//{

	//	if (!player.jumpFlag)
	//	{
	//		if (CheckHitKey(KEY_INPUT_W))
	//		{
	//			jumpCnt++;
	//			if (jumpCnt < jumpFrame)
	//			{
	//				player.velocity.y = 25;
	//			}
	//			/*if (player.headFlag)
	//			{
	//				jumpCnt = jumpFrame;
	//			}*/
	//		}
	//		else
	//		{
	//			jumpCnt = 0;
	//			player.jumpFlag = true;
	//		}
	//	}
	//}
	//else
	//{
	//	jumpCnt = 15;
	//}
	//movedPos = player.pos;

	/////*if (player.jumpFlag == false) 
	////{*/
	////	if (/*newKey[P2_UP]*/CheckHitKey(KEY_INPUT_W))
	////		/*if (player.velocity.y == 0)
	////		{*/
	////			{

	////				jumpCnt++;
	////				if (jumpCnt/*[0]*/ < jumpFrame/*[0]*/)
	////				{
	////					player.velocity.y = 25;
	////				}

	////			}
	////		//}
	////		else
	////		{
	////			jumpCnt = 0;
	////			player.jumpFlag = true;
	////		}

	//	/*if (CheckHitKey(KEY_INPUT_B))
	//	{

	//	}*/
	//		
	///*}*/
	//
	////重力
	//movedPos.y -= player.velocity.y * SECOND_PER_FRAME;
	//player.velocity.y -= ACC_G * SECOND_PER_FRAME;
	//
	////
	//player.pos = movedPos;
	////player.velocity.y -= ACC_G * SECOND_PER_FRAME;
	//

	//if (player.pos.x >= SCREEN_SIZE_X-48)
	//{
	//	player.pos.x = SCREEN_SIZE_X-48;
	//}
	//if (player.pos.x <= 0)
	//{
	//	player.pos.x = 0;
	//}
	
}

//void PlayerUpdate(void)
//{
//	for (int i = 0; i < PLAYER_MAX; i++)
//	{
//		//　1ﾙｰﾌﾟ毎に初期化する変数
//		XY tmpPos;
//		//XY playeroldPos = player.pos;
//		XY movedPos = player[i].pos;
//
//		// offsetは今のﾌﾟﾚｲﾔｰの1ﾏｽあとの座標
//		XY movedOffset = movedPos;
//		XY movedOffset2 = movedPos;
//		XY movedOffset3 = movedPos;
//
//		player[i].runFlag = false;
//		//player[i].headFlag = false;
//
//		// ﾌﾟﾚｲﾔｰの移動	(キー操作)
//		if (player[i].flag)
//		{
//			if (PlayerKeyCheck(i)) {
//				if (player[i].moveDir == DIR_RIGHT) {								// 右
//					player[i].velocity.x += ACC_RUN;					// 速度の更新
//					player[i].runFlag = true;
//					if (player[i].velocity.x > VELOCITY_X_MAX) {
//						player[i].velocity.x = VELOCITY_X_MAX;
//					}
//				}
//
//				if (player[i].moveDir == DIR_LEFT) {								// 左			
//					player[i].velocity.x -= ACC_RUN;				// 速度の更新
//					player[i].runFlag = true;
//					if (player[i].velocity.x < -VELOCITY_X_MAX) {
//						player[i].velocity.x = -VELOCITY_X_MAX;
//					}
//				}
//			}
//			// 止まった時の減速処理
//			if (!player[i].runFlag) {
//				if (player[i].velocity.x > 0) {
//					player[i].velocity.x -= ACC_STOP;
//					if (player[i].velocity.x < 0) {
//						player[i].velocity.x = 0;
//					}
//				}
//				if (player[i].velocity.x < 0) {
//					player[i].velocity.x += ACC_STOP;
//					if (player[i].velocity.x > 0) {
//						player[i].velocity.x = 0;
//					}
//				}
//			}
//
//			// ﾌﾟﾚｲﾔｰの移動(左右)
//			movedPos.x += player[i].velocity.x * 1;	// 距離の更新
//
//			if (player[i].velocity.x > 0) {							// 右
//				movedOffset.x = movedPos.x + player[i].hitPosE.x;
//			}
//			if (player[i].velocity.x < 0) {							// 左
//				movedOffset.x = movedPos.x - player[i].hitPosS.x;
//			}
//			//ﾌﾟﾚｲﾔｰの頭上の中心のｵﾌｾｯﾄ
//			movedOffset2 = movedOffset;
//			movedOffset2.y = movedPos.y - player[i].hitPosS.y;
//			//ﾌﾟﾚｲﾔｰの足下の中心のｵﾌｾｯﾄ
//			movedOffset3 = movedOffset;
//			movedOffset3.y = movedPos.y + player[i].hitPosE.y - 1;			// ‐1は調整
//
//			//SetOffset(OFFSET_LEFT_RIGHT);
//
//			//if (IsPass(movedOffset) && IsPass(movedOffset2) && IsPass(movedOffset3)) {		// movedOffsetはﾌﾟﾚｲﾔｰの中心movedOffset2はﾌﾟﾚｲﾔｰの頭上の中心movedOffset3はﾌﾟﾚｲﾔｰの足下の中心
//			//	player[i].pos = movedPos;													// 
//			//}
//			//else {
//			//	tmpPos = MapPosToMoveIndex(movedOffset, player[i].headFlag, player[i].velocity);
//			//if (player[i].velocity.x > 0) {			// 右
//			//	player[i].pos.x = tmpPos.x - player[i].hitPosE.x;
//			//}
//			//if (player[i].velocity.x < 0) {			// 左
//			//	player[i].pos.x = tmpPos.x + player[i].hitPosS.x;
//			//}
//			movedPos = player[i].pos;
//			player[i].velocity.x = 0;
//			/*			*/
//		}
//
//		// 重力
//		movedPos = player[i].pos;
//
//		movedPos.y -= player[i].velocity.y * SECOND_PER_FRAME;
//		player[i].velocity.y -= ACC_G * SECOND_PER_FRAME;
//
//		// ﾌﾞﾛｯｸのﾁｪｯｸ
//		// 頭上のﾌﾞﾛｯｸのﾁｪｯｸ
//
//		movedOffset = movedPos;
//		movedOffset.y = movedPos.y - player[i].hitPosS.y;
//		movedOffset2 = movedOffset;							// 左上
//		movedOffset2.x = movedPos.x - player[i].hitPosS.x;
//		movedOffset3 = movedOffset;							// 右上
//		movedOffset3.x = movedPos.x + player[i].hitPosE.x - 1;
//		//	SetOffset(OFFSET_HEAD);
//
//		//if (IsPass(movedOffset) && IsPass(movedOffset2) && IsPass(movedOffset3)) {
//		//	player[i].pos = movedPos;
//		//}
//		//else {
//		//	player[i].headFlag = true;
//		//	tmpPos = MapPosToMoveIndex(movedOffset, player[i].headFlag, player[i].velocity);
//		//	player[i].pos.y = tmpPos.y + player[i].hitPosS.y;
//		//	player[i].velocity.y *= -1;
//		//}
//		movedPos = player[i].pos;
//
//
//		// 足下のﾌﾞﾛｯｸのﾁｪｯｸ
//
//		movedOffset = movedPos;
//		movedOffset.y = movedPos.y + player[i].hitPosE.y;
//		movedOffset.y = movedPos.y + player[i].hitPosE.y;
//		movedOffset2 = movedOffset;							// 左上
//		movedOffset2.x = movedPos.x - player[i].hitPosS.x;
//		movedOffset3 = movedOffset;							// 右上
//		movedOffset3.x = movedPos.x + player[i].hitPosE.x - 1;
//
//		//	SetOffset(OFFSET_FOOT);
//
//		/*if (IsPass(movedOffset) && IsPass(movedOffset2) && IsPass(movedOffset3)) {
//			player[i].pos = movedPos;
//		}
//		else {
//			tmpPos = MapPosToMoveIndex(movedOffset, player[i].headFlag, player[i].velocity);
//			player[i].pos.y = tmpPos.y - player[i].hitPosE.y;
//			player[i].velocity.y = 0;
//			player[i].jumpFlag = false;
//		}
//		movedPos = player[i].pos;*/
//
//		//　ｼﾞｬﾝﾌﾟ
//		// 1ﾏｽのところではジャンプしない
//		movedOffset = movedPos;
//		movedOffset.y = movedPos.y - player[i].hitPosS.y;
//		movedOffset2 = movedOffset;							// 左上
//		movedOffset2.x = movedPos.x - player[i].hitPosS.x;
//		movedOffset3 = movedOffset;							// 右上
//		movedOffset3.x = movedPos.x + player[i].hitPosE.x - 1;
//		//SetOffset(OFFSET_NOTJUMP);
//		/*if (IsPass(movedOffset) && IsPass(movedOffset2) && IsPass(movedOffset3)) {*/
//		if (!player[i].jumpFlag) {
//			if (PlayerJumpKeyCheck(i)) {
//				jumpCnt[i]++;
//				if (jumpCnt[i] < jumpFrame[i]) {
//					player[i].velocity.y = 25;
//				}
//				/*if (player[i].headFlag) {
//					jumpCnt[i] = jumpFrame[i];
//				}*/
//			}
//			else {
//				jumpCnt[i] = 0;
//				player[i].jumpFlag = true;
//			}
//		}
//		//}
//		else {
//			jumpCnt[i] = 15;
//		}
//		movedPos = player[i].pos;
//
//
//
//		//// ｼﾞｬﾝﾌﾟﾌﾞﾛｯｸ
//		//// 1ﾏｽのところではジャンプしない
//		//movedOffset = movedPos;
//		//movedOffset.y = movedPos.y - player[i].hitPosS.y;
//		//movedOffset2 = movedOffset;							// 左上
//		//movedOffset2.x = movedPos.x - player[i].hitPosS.x;
//		//movedOffset3 = movedOffset;							// 右上
//		//movedOffset3.x = movedPos.x + player[i].hitPosE.x - 1;
//		////SetOffset(OFFSET_NOTJUMP);
//		//if (IsPass(movedOffset) && IsPass(movedOffset2) && IsPass(movedOffset3)) {
//		//	movedOffset.y = movedPos.y + player[i].hitPosE.y;		// 足元
//		//	if (!JumpIsPass(movedOffset)) {
//		//		player[i].velocity.y = 80;
//		//	}
//		//}
//		//movedPos = player[i].pos;
//
//
//
//
//		player[i].animCnt++;
//	}
//
//
//
//	//selectCnt = 0;
//	//for (int j = 0; j < 4; j++) {
//	//	cycleCnt[j] = 0;
//	//}
//	//for (int i = 0; i < playerMax; i++) 
//	//{
//	//	if (player[i].selectFlag) {
//	//		selectCnt++;
//	//		if (player[i].selectType == 1) {
//	//			cycleCnt[0]++;
//	//		}
//	//		if (player[i].selectType == 2) {
//	//			cycleCnt[1]++;
//	//		}
//	//		if (player[i].selectType == 3) {
//	//			cycleCnt[2]++;
//	//		}
//	//		if (player[i].selectType == 4) {
//	//			cycleCnt[3]++;
//	//		}
//	//	}
//	//}
//}

void playerDraw(void)
{
	for (int i = 0; i < PLAYER_MAX; i++)
	{
		if (player[i].flag == true)
		{
			if (player[i].moveDir == DIR_RIGHT)
				DrawGraph(player[i].pos.x, player[i].pos.y, playerimage[i][player[i].animCnt / 10 % 4], true);

			if (player[i].moveDir == DIR_LEFT)
				DrawTurnGraph(player[i].pos.x, player[i].pos.y, playerimage[i][player[i].animCnt / 10 % 4], true);

			if (i % 2 == 1)
			{
				if (player[i].moveDir == DIR_RIGHT)
					DrawTurnGraph(player[i].pos.x, player[i].pos.y, playerimage[i][player[i].animCnt / 10 % 4], true);

				if (player[i].moveDir == DIR_LEFT)
				
				DrawGraph(player[i].pos.x, player[i].pos.y, playerimage[i][player[i].animCnt / 10 % 4], true);
			}



			DrawFormatString(0, 32, 0xffffff, "pos.y  = %d", player[i].pos.y);
		}
	}
	DrawFormatString(0, 48, 0xffffff, "velocity.x  = %d", player[0].velocity.x);
	DrawFormatString(0, 56, 0xffffff, "velocity.y  = %d", player[0].velocity.y);
		DrawGraph(0, 0, p1Lifeimage, true);

		for (int i = 0; i < player[0].Life; i++)
		{
			DrawBox(0+i, 0, 9+i, 15, 0x5FFE01, true);
		}
		for (int i = 0; i < player[0].Ex; i++)
		{
			DrawBox(0 + i, 15,  8+ i, 20, 0xffff00, true);
		}
		for (int i = 0; i < player[1].Life; i++)
		{
			DrawBox(SCREEN_SIZE_X, 0, 9 + i, 15, 0x5FFE01, true);
		}
		for (int i = 0; i < player[1].Ex; i++)
		{
			DrawBox(0 + i, 15, 8 + i, 20, 0xffff00, true);
		}
}

//bool PlayerKeyCheck(int i) {
//	switch (i) {
//	case 0:
//		if (CheckHitKey(KEY_INPUT_A)) {
//			player.moveDir = DIR_RIGHT;
//			return true;
//		}
//
//		if (CheckHitKey(KEY_INPUT_D)) {
//			player.moveDir = DIR_LEFT;
//			return true;
//		}
//		break;
//
//	default:
//		break;
//	}
//
//	return false;
//}




bool PlayerKeyCheck(int i) {
	switch (i)
	{
	case 0:
		if (CheckHitKey(KEY_INPUT_D)) {
			player[i].moveDir = DIR_RIGHT;
			return true;
		}
		
		if (CheckHitKey(KEY_INPUT_A)) {
			player[i].moveDir = DIR_LEFT;
			return true;
		}
		break;
	case 1:
		if (CheckHitKey(KEY_INPUT_RIGHT)) {
			player[i].moveDir = DIR_RIGHT;
			return true;
		}
	
		if (CheckHitKey(KEY_INPUT_LEFT)) {
			player[i].moveDir = DIR_LEFT;
			return true;
		}
		break;
		//case 2:
		//	if (newKey[P3_RIGHT]) {
		//		player[i].moveDir = DIR_RIGHT;
		//		return true;
		//	}

		//	if (newKey[P3_LEFT]) {
		//		player[i].moveDir = DIR_LEFT;
		//		return true;
		//	}
		//	break;
		//case 3:
		//	if (newKey[P4_RIGHT]) {
		//		player[i].moveDir = DIR_RIGHT;
		//		return true;
		//	}

		//	if (newKey[P4_LEFT]) {
		//		player[i].moveDir = DIR_LEFT;
		//		return true;
		//	}
		//	break;
	default:
		break;
	}

	return false;
}

bool PlayerJumpKeyCheck(int i) {
	switch (i) {
	case 0:
		if (CheckHitKey(KEY_INPUT_W)) {
			return true;
		}
		break;
	case 1:
		if (CheckHitKey(KEY_INPUT_UP)) {
			return true;
		}
		break;
	//case 2:
	//	if (newKey[P3_A]) {
	//		return true;
	//	}
	//	break;
	//case 3:
	//	if (newKey[P4_A]) {
	//		return true;
	//	}
	//	break;
	}
	return false;
}
