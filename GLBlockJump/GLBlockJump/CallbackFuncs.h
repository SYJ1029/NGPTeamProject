#ifndef CALLBACK_FUNCS_H
#define CALLBACK_FUNCS_H

#include "stdafx.h"

void Mouse(int button, int state, int x, int y);
void Motion(int x, int y);
void TimerFunction(int value);
void Keyboard(unsigned char key, int x, int y);
void KeyboardUp(unsigned char key, int x, int y);
void SpecialInput(int key, int x, int y);

#endif