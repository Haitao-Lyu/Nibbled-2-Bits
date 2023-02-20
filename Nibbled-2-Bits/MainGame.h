#pragma once

constexpr int DISPLAY_WIDTH = 1280;
constexpr int DISPLAY_HEIGHT = 720;
constexpr int DISPLAY_SCALE = 1;

void MainGameEntry(PLAY_IGNORE_COMMAND_LINE);

bool MainGameUpdate(float elapsedTime);

int MainGameExit(void);
