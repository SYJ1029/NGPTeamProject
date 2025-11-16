#pragma once

#include "stdafx.h"
#include "ServerMacro.h"
#include "Player.h"


extern PktFrameState Fs;
extern PlayerInputs pi[MAX_CLIENTS];
DWORD WINAPI ServerProcess(LPVOID arg);
