#pragma once

constexpr int DISPLAY_WIDTH{ 1280 };
constexpr int DISPLAY_HEIGHT{ 720};
constexpr int DISPLAY_SCALE{ 1 };
const int GAME_AREA_WIDTH{ 870 };
const int GAME_AREA_HEIGHT{ 720 };
const int GRID_SIZE{ 50 };
const int BOARDER_PIXELS{ 35 };
const int GRID_COL{ 16 };
const int GRID_ROW{ 13 };

void MainGameEntry(PLAY_IGNORE_COMMAND_LINE);

bool MainGameUpdate(float elapsedTime);

int MainGameExit(void);
