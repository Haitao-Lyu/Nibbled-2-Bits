#pragma once
#include "PlayCustom.h"

constexpr int DISPLAY_WIDTH = 2731;
constexpr int DISPLAY_HEIGHT = 1536;
constexpr int DISPLAY_SCALE = 1;

void MainGameEntry(PLAY_IGNORE_COMMAND_LINE);

bool MainGameUpdate(float elapsedTime);

int MainGameExit(void);
