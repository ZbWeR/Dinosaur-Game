#pragma once
#ifndef __FUNCTION_H__
#define __FUNCTION_H__

#include "StdHeader.h"

void Startgame();

int rand_range(int, int);

void PutPng(int x, int y, IMAGE* im_show1, IMAGE* im_show2);

void change_location();

void input_game();

void recircle();

void skill_require();

void ground_dino();

bool dino_collision();

void input_key();


#endif // !__FUNCTION_H__
