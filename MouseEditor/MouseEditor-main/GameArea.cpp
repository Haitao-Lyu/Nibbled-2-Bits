#include "GameArea.h"

using namespace Play;

float PI{ 3.14159265358979323846 };
int GAME_AREA_WIDTH{ 870 };
int GAME_AREA_HEIGHT{ 720 };
int SQUARE_SIZE{ 50 };
int BOARDER_PIXELS{ 35 };

GameArea::GameArea() {
	//Get sprite ID's for each mouse hole rotated sprite
	mouseHoleSpriteIDs[0] = Play::GetSpriteId("mouse_hole_top");
	mouseHoleSpriteIDs[1] = Play::GetSpriteId("mouse_hole_left");
	mouseHoleSpriteIDs[2] = Play::GetSpriteId("mouse_hole_bottom");
	mouseHoleSpriteIDs[3] = Play::GetSpriteId("mouse_hole_right");
}

void GameArea::Update() {
	//Increase and decrease the misc variable of the last selected object when up and down arrors are pressed
	if (m_lastSelected.x != -1 && m_lastSelected.y != -1) {
		if (Play::KeyPressed(VK_UP)) {
			GameAreaObject& gameAreaObject = GetGameAreaObject(m_lastSelected);
			gameAreaObject.misc += 1;
		}
		if (Play::KeyPressed(VK_DOWN)) {
			GameAreaObject& gameAreaObject = GetGameAreaObject(m_lastSelected);
			gameAreaObject.misc -= 1;
		}
	}

	//Rotate object if the right mouse button is pressed
	if (Play::KeyPressed(VK_RBUTTON)) {
		GridPos mouseGridPos = GetMouseGridPos();
		if (mouseGridPos.x < 0 || mouseGridPos.y < 0 || mouseGridPos.x > GRID_WIDTH || mouseGridPos.y > GRID_HEIGHT) {
			return;
		}
		int& rotation = GetGameAreaObject(mouseGridPos).rot;
		rotation += 1;
		if (rotation > 3) {
			rotation = 0;
		}
	}
}

void GameArea::DrawGameArea() {
	//Draw each item in the grid if it has a valid id
	for (int i = 0; i < GRID_WIDTH; ++i) {
		for (int j = 0; j < GRID_HEIGHT; j++) {
			if (m_gameAreaObjects[i][j].id != -1) {
				GameAreaObject obj = m_gameAreaObjects[i][j];
				Play::Point2D worldPos{ GameToWorld({ obj.posx * SQUARE_SIZE + SQUARE_SIZE / 2, obj.posy * SQUARE_SIZE + SQUARE_SIZE / 2 }) };
				Play::DrawSprite(GetSpriteIDFromObjectID(obj.id, obj.rot), worldPos, 0);
			}
		}
	}

	//Draw the correct mouse hole sprite and the E and X text. The text should be below if it's on the top of the screen and above otherwise
	if (m_holeEntry.vis) {
		Play::Point2D worldPos{ GameToWorld({ m_holeEntry.posx * SQUARE_SIZE + SQUARE_SIZE / 2, m_holeEntry.posy * SQUARE_SIZE + SQUARE_SIZE / 2 }) };
		int IDIndex{ 0 };
		if (m_holeEntry.posy == GRID_HEIGHT) {
			IDIndex = 0;
		}else if (m_holeEntry.posx == -1) {
			IDIndex = 1;
		}
		else if (m_holeEntry.posy == -1) {
			IDIndex = 2;
		}
		else if (m_holeEntry.posx == GRID_WIDTH) {
			IDIndex = 3;
		}
		Play::DrawSprite(mouseHoleSpriteIDs[IDIndex], worldPos, 0);

		if (m_holeEntry.posy == GRID_HEIGHT) {
			Play::DrawFontText("fontui64px", "E", worldPos + Point2D{ 0, -SQUARE_SIZE }, Play::CENTRE);
		}
		else {
			Play::DrawFontText("fontui64px", "E", worldPos + Point2D{ 0, SQUARE_SIZE }, Play::CENTRE);
		}
	}

	if (m_holeExit.vis) {
		Play::Point2D worldPos{ GameToWorld({ m_holeExit.posx * SQUARE_SIZE + SQUARE_SIZE / 2, m_holeExit.posy * SQUARE_SIZE + SQUARE_SIZE / 2 }) };
		int IDIndex{ 0 };
		if (m_holeExit.posy == GRID_HEIGHT) {
			IDIndex = 0;
		}
		else if (m_holeExit.posx == -1) {
			IDIndex = 1;
		}
		else if (m_holeExit.posy == -1) {
			IDIndex = 2;
		}
		else if (m_holeExit.posx == GRID_WIDTH) {
			IDIndex = 3;
		}
		Play::DrawSprite(mouseHoleSpriteIDs[IDIndex], worldPos, 0);

		if (m_holeExit.posy == GRID_HEIGHT) {
			Play::DrawFontText("fontui64px", "X", worldPos + Point2D{ 0, -SQUARE_SIZE }, Play::CENTRE);
		}
		else {
			Play::DrawFontText("fontui64px", "X", worldPos + Point2D{ 0, SQUARE_SIZE }, Play::CENTRE);
		}
	}

	//Draw the misc variable above the last selected object
	if (m_lastSelected.x != -1 && m_lastSelected.y != -1) {
		Play::Point2D worldPos{ GameToWorld({ m_lastSelected.x * SQUARE_SIZE + SQUARE_SIZE / 2, m_lastSelected.y * SQUARE_SIZE + SQUARE_SIZE / 2 }) };
		Play::DrawFontText("fontui64px", std::to_string(GetGameAreaObject(m_lastSelected).misc).c_str(), worldPos + Point2D{ 0, SQUARE_SIZE }, Play::CENTRE);	
	}
}

Point2f GameArea::GameToWorld(Point2f pos) {
	Point2f botLeftGrid{ DISPLAY_WIDTH - GAME_AREA_WIDTH + BOARDER_PIXELS, DISPLAY_HEIGHT - GAME_AREA_HEIGHT + BOARDER_PIXELS };
	return pos + botLeftGrid;
}

Point2f GameArea::WorldToGame(Point2f pos) {
	Point2f botLeftGrid{ DISPLAY_WIDTH - GAME_AREA_WIDTH + BOARDER_PIXELS, DISPLAY_HEIGHT - GAME_AREA_HEIGHT + BOARDER_PIXELS };
	return pos - botLeftGrid;
}

void GameArea::PlaceObject(FloatingObject obj) {
	GridPos mouseGridPos = GetMouseGridPos();

	//Place a mouse hole object, can't be removed so will snap to the closest valid location
	if (obj.mouseHole) {
		int x = mouseGridPos.x;
		int y = mouseGridPos.y;

		if (x < -1) {
			x = -1;
		}
		if (y < -1) {
			y = -1;
		}
		if (x > GRID_WIDTH) {
			x = GRID_WIDTH;
		}
		if (y > GRID_HEIGHT) {
			y = GRID_HEIGHT;
		}
		
		int distToleft = abs(-1 - x);
		int distToRight = abs(GRID_WIDTH - x);
		int distToDown = abs(-1 - y);
		int distToUp = abs(GRID_HEIGHT - y);

		if (std::min(distToleft, distToRight) < std::min(distToDown, distToUp)) {
			if (distToleft > distToRight) {
				x = GRID_WIDTH;
			}
			else {
				x = -1;
			}
		}
		else {
			if (distToDown > distToUp) {
				y = GRID_HEIGHT;
			}
			else {
				y = -1;
			}
		}

		if (x == -1 || x == GRID_WIDTH) {
			if (y == -1) {
				y = 0;
			}
			else if (y == GRID_HEIGHT) {
				y = GRID_HEIGHT - 1;
			}
		}

		if (obj.id == 0) {
			m_holeEntry.posx = x;
			m_holeEntry.posy = y;
			m_holeEntry.vis = true;
		}
		else if (obj.id == 1) {
			m_holeExit.posx = x;
			m_holeExit.posy = y;
			m_holeExit.vis = true;
		}

		return;
	}

	//Check if the object has been dropped within the game area
	if (mouseGridPos.x < 0 || mouseGridPos.y < 0 || mouseGridPos.x >= GRID_WIDTH || mouseGridPos.y >= GRID_HEIGHT) {
		return;
	}

	//Set the object at the mouse location to be the held item
	GameAreaObject tmpGameAreaObject;
	tmpGameAreaObject.id = obj.id;
	tmpGameAreaObject.rot = obj.rot;
	tmpGameAreaObject.misc = obj.misc;
	tmpGameAreaObject.posx = mouseGridPos.x;
	tmpGameAreaObject.posy = mouseGridPos.y;
	m_gameAreaObjects[mouseGridPos.x][mouseGridPos.y] = tmpGameAreaObject;
	m_lastSelected.x = mouseGridPos.x;
	m_lastSelected.y = mouseGridPos.y;
}

FloatingObject GameArea::GetObject() {
	GridPos mouseGridPos = GetMouseGridPos();
	
	//Return a mouse hole object
	if (mouseGridPos.x == m_holeEntry.posx && mouseGridPos.y == m_holeEntry.posy) {
		m_holeEntry.vis = false;
		m_lastSelected.x = -1;
		m_lastSelected.y = -1;
		return { m_holeEntry.id, 0, 0, true };
	}
	if (mouseGridPos.x == m_holeExit.posx && mouseGridPos.y == m_holeExit.posy) {
		m_holeExit.vis = false;
		m_lastSelected.x = -1;
		m_lastSelected.y = -1;
		return { m_holeExit.id, 0, 0, true };
	}

	if (mouseGridPos.x < 0 || mouseGridPos.y < 0 || mouseGridPos.x >= GRID_WIDTH || mouseGridPos.y >= GRID_HEIGHT) {
		return { -1, 0 };
	}

	//If within the game area and the grid location contains a valid object return it
	GameAreaObject tmpGameAreaObject = m_gameAreaObjects[mouseGridPos.x][mouseGridPos.y];
	m_gameAreaObjects[mouseGridPos.x][mouseGridPos.y].id = -1;

	if (tmpGameAreaObject.id != -1) {
	m_lastSelected.x = -1;
	m_lastSelected.y = -1;
	}

	return { tmpGameAreaObject.id, tmpGameAreaObject.rot, tmpGameAreaObject.misc };
}

GridPos GameArea::GetMouseGridPos() {
	Point2f mouseWorldPos = Play::GetMousePos();
	Point2f mouseGamePos = WorldToGame(mouseWorldPos);
	Point2f mouseSnapPos = mouseGamePos;
	mouseSnapPos.x -= abs(((int)mouseSnapPos.x) % SQUARE_SIZE);
	mouseSnapPos.y -= abs(((int)mouseSnapPos.y) % SQUARE_SIZE);

	return { mouseSnapPos.x >= 0 ? int(mouseSnapPos.x / SQUARE_SIZE) : int(mouseSnapPos.x / SQUARE_SIZE) - 1, mouseSnapPos.y >= 0 ? int(mouseSnapPos.y / SQUARE_SIZE) : int(mouseSnapPos.y / SQUARE_SIZE) - 1 };
}

void GameArea::SetGameAreaObjects(GameAreaObject gameAreaObjects[GRID_WIDTH][GRID_HEIGHT]) {
	std::memcpy(m_gameAreaObjects, gameAreaObjects, sizeof(GameAreaObject) * GRID_WIDTH * GRID_HEIGHT);
}

GameAreaObject& GameArea::GetGameAreaObject(GridPos pos) {
	return m_gameAreaObjects[pos.x][pos.y];
}