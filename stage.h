#pragma once

//enum STAGE_ID {
//	STAGE_ID_START,
//	STAGE_ID_MAZE,
//	STAGE_ID_MAX
//};
//
//enum MAZE_CHIP_ID {
//	MAZE_CHIP_MOVE = 0,
//	MAZE_CHIP_FOOT = 2,
//	MAZE_CHIP_STAIRS = 15,
//};


#define MAP_CHIP_SIZE_X 48
#define MAP_CHIP_SIZE_Y 48

#define CHIP_MAX_X 48
#define CHIP_MAX_Y 15

extern XY mappos;
extern XY move;
extern XY playerpos;
//extern XY mapoffset;


void StageSystemInit(void);
void StageGameInit(void);
void StageDraw(void);

XY mapPosToIndex(XY pos);
XY mapIndexToPos(XY index);
XY mapPosToMoveIndex(XY pos, bool flag, XY_F velocity);

//XY mapPosToMoveIndexpos(XY pos, MOVE_DIR dir);
bool IsPass(XY pos);
