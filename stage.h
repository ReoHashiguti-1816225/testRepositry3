#pragma once




#define MAP_CHIP_SIZE_X 48
#define MAP_CHIP_SIZE_Y 48

#define CHIP_MAX_X 48
#define CHIP_MAX_Y 15

extern XY mappos;
extern XY move;
extern XY playerpos;


void StageSystemInit(void);
void StageGameInit(void);
void StageDraw(void);

XY mapPosToIndex(XY pos);
XY mapIndexToPos(XY index);
XY mapPosToMoveIndex(XY pos, bool flag, XY_F velocity);

bool IsPass(XY pos);
