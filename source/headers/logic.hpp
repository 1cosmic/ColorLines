#pragma once

#ifndef _H_LOGIC
#define _H_LOGIC

#include "mainStruts.h"

void initField(void); // init field.

void destroyLogic(void); // destroy all logic dynamic blocks.

int checkFreeSpace(void); // check free space in field.

bool wayIsExists(pointField start, pointField end);

void swapStar(pointField last, pointField current);

void randomColors(void); // create list random colors.

void randomPutStar(void); // put color from random color-list.

void searchLines(int count); // search of multiplie colors in one line.

void printField(void); // output field in terminal.

#endif // !_H_LOGIC
