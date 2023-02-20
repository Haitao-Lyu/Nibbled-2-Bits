#include "pch.h"
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

void logDebugInfo(const std::string& message, const std::string& filename) {
	// open the file in append mode
	std::ofstream file;
	file.open(filename, std::ios_base::app);

	if (file.is_open()) {
		// write the message to the file
		file << message << std::endl;

		// close the file
		file.close();
	}
	else {
		// if the file can't be opened, print an error message to the console
		std::cerr << "Error: Could not open file " << filename << " for writing." << std::endl;
	}
}