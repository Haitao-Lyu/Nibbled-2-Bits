#pragma once

void DebugText(std::string text, Play::Point2D pos = { 260 ,200 }, Play::Colour color = Play::cRed);

void DebugValue(int text,  const char* prefix = "",int yoffset = 0, Play::Colour color = Play::cRed);

void DebugValue(float text, const char* prefix = "", int yoffset = 0, Play::Colour color = Play::cRed);

void DebugValue(Play::Vector2D text, const char* prefix = "", int yoffset = 0, Play::Colour color = Play::cRed);

void logDebugInfo(const std::string& message, const std::string& filename = "debug.log");