#pragma once
#include "PlayCustom.h"

constexpr int DISPLAY_WIDTH = 1920;
constexpr int DISPLAY_HEIGHT = 1080;
constexpr int DISPLAY_SCALE = 1;

void MainGameEntry(PLAY_IGNORE_COMMAND_LINE);

bool MainGameUpdate(float elapsedTime);

int MainGameExit(void);
