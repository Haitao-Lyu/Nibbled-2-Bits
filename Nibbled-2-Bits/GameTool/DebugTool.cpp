#include "DebugTool.h"

//debug offset
static int DebugX_Offset = 100;
static int DebugPrefixOffset = 40;

void DebugText(std::string text, Play::Point2D pos, Play::Colour color)
{
	Play::DrawDebugText(pos, text.c_str(), color, true);
}

void DebugValue(int text, const char* prefix, int yoffset, Play::Colour color)
{
	char* tempCache = new char[10]{};
	std::string num = std::to_string(text);
	std::copy(num.begin(), num.end(), tempCache);
	Play::DrawDebugText({ DebugPrefixOffset,20 + yoffset }, prefix, color, true);
	Play::DrawDebugText({ DebugX_Offset,20 + yoffset }, tempCache, color, true);
	delete[]tempCache;
}

void DebugValue(float text,  const char* prefix, int yoffset, Play::Colour color)
{
	Play::DrawDebugText({ DebugPrefixOffset,20 + yoffset }, prefix, color, true);
	Play::DrawDebugText({ DebugX_Offset,20 + yoffset }, std::to_string(text).c_str(), color, true);
}

void DebugValue(Play::Vector2D text,  const char* prefix, int yoffset, Play::Colour color)
{
	Play::DrawDebugText({ DebugPrefixOffset,60 + yoffset }, prefix, Play::cRed, true);
	Play::DrawDebugText({ DebugX_Offset,60 + yoffset }, std::to_string(text.x).c_str(), color, true);

	Play::DrawDebugText({ DebugPrefixOffset,80 + yoffset }, prefix, Play::cRed, true);
	Play::DrawDebugText({ DebugX_Offset,80 + yoffset }, std::to_string(text.y).c_str(), color, true);
}
