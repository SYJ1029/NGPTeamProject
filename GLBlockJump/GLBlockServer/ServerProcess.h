#pragma once

#include "stdafx.h"
#include "ServerMacro.h"
#include "Player.h"


extern PktFrameState Fs;
extern int winnerId;
extern PlayerInputs pi[MAX_CLIENTS];

extern bool clientQuitFlags[MAX_CLIENTS];
extern bool clientRestartFlags[MAX_CLIENTS];
DWORD WINAPI ServerProcess(LPVOID arg);
