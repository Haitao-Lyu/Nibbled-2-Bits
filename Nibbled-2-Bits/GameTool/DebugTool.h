#pragma once
#include "../PlayCustom.h"

void DebugText(std::string text, Play::Point2D pos = { 960 ,900 }, Play::Colour color = Play::cRed);

void DebugValue(int text,  const char* prefix = "",int yoffset = 0, Play::Colour color = Play::cRed);

void DebugValue(float text, const char* prefix = "", int yoffset = 0, Play::Colour color = Play::cRed);

void DebugValue(Play::Vector2D text, const char* prefix = "", int yoffset = 0, Play::Colour color = Play::cRed);