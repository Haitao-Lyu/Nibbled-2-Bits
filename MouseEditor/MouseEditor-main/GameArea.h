#pragma once
#include "ReadCSV.h"

struct GridPos {
	int x{ 0 };
	int y{ 0 };
};

struct FloatingObject {
	int id{ 0 };
	int rot{ 0 };
	int misc{ 0 };
	bool mouseHole{ false };
};

struct GameAreaObject {
	int id{ -1 };
	int posx{ 0 };
	int posy{ 0 };
	int rot{ 0 };
	int misc{ 0 };
	bool mouseHole{ false };
	bool vis{ true };
};

using namespace Play;

extern int GAME_AREA_WIDTH;
extern int GAME_AREA_HEIGHT;
extern int SQUARE_SIZE;
constexpr int GRID_WIDTH{ 16 };
constexpr int GRID_HEIGHT{ 13 };
extern int BOARDER_PIXELS;
extern int DISPLAY_WIDTH;
extern int DISPLAY_HEIGHT;
extern int DISPLAY_SCALE;

class GameArea {
private:
	Point2f GameToWorld(Point2f pos);
	Point2f WorldToGame(Point2f pos);
	GridPos GetMouseGridPos();
	GameAreaObject m_gameAreaObjects[GRID_WIDTH][GRID_HEIGHT];

public:
	GameAreaObject m_holeEntry{ 0, 0, -1, 0, 0, true };
	GameAreaObject m_holeExit{ 1, GRID_WIDTH - 1, GRID_HEIGHT, 0, 0, true };
	int mouseHoleSpriteIDs[4]{};
	GridPos m_lastSelected{ -1,-1 };
	GameArea();
	void Update();
	void PlaceObject(FloatingObject obj);
	FloatingObject GetObject();
	void DrawGameArea();
	void SetGameAreaObjects(GameAreaObject gameAreaObjects[GRID_WIDTH][GRID_HEIGHT]);
	GameAreaObject& GetGameAreaObject(GridPos pos);
};