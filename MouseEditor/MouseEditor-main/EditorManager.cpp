#include "EditorManager.h"
#include "ReadCSV.h"

EditorManager::EditorManager()
{
	m_currentHeld = { -1, 0, 0 };
}

EditorManager::EditorManager(std::vector<ObjectCSV> objects)
{
	m_currentHeld = {- 1, 0, 0};
	objectCSVs = objects;
	m_panel = Panel(objects);
	m_gameArea = GameArea();
}

void EditorManager::Update()
{
	//Don't update if ui is open
	if (m_loadUI) {
		LoadUI();
		return;
	}
	else if (m_saveUI) {
		SaveUI();
		return;
	}
	else {
		//If L or S buttons are pressed ui is active
		m_fileText = "";
		if (Play::KeyPressed('L')) {
			m_loadUI = true;
			return;
		}
		else if (Play::KeyPressed('S')) {
			m_saveUI = true;
			return;
		}
	}

	// handle grabbing
	if (Play::KeyPressed(VK_LBUTTON))
	{
		m_currentHeld = { m_panel.GetSelection(), 0, 0 };
		if (m_currentHeld.id == - 1)
		{
			m_currentHeld = m_gameArea.GetObject();
		}
	}

	//Handle placing
	if (!Play::KeyDown(VK_LBUTTON))
	{
		if (m_currentHeld.id >= 0)
		{
			m_gameArea.PlaceObject(m_currentHeld);
		}

		m_currentHeld = { -1, 0, 0 };
	}

	m_panel.Update();
	m_gameArea.Update();
}

void EditorManager::Draw()
{
	m_gameArea.DrawGameArea();

	m_panel.Draw();

	// draw held item
	if (m_currentHeld.mouseHole) {
		Play::Point2D mousePos = Play::GetMousePos();

		Play::DrawSprite(m_gameArea.mouseHoleSpriteIDs[0], mousePos, 0);
	}
	else {
		if (m_currentHeld.id >= 0)
		{
			Play::Point2D mousePos = Play::GetMousePos();

			int spriteID = GetSpriteIDFromObjectID(m_currentHeld.id, m_currentHeld.rot);

			PLAY_ASSERT_MSG(spriteID != -1, "invalid sprite id");
			Play::DrawSprite(spriteID, mousePos, 0);
		}
	}

	if (m_loadUI || m_saveUI) {
		DrawUI();
	}
}

void EditorManager::LoadNewLevel(std::string levelName) {
	std::ifstream levelFile;
	levelFile.open("data\\" + levelName + ".lev");
	//Do nothing if the file does not exsist
	if (levelFile.fail()) {
		return;
	}

	GameAreaObject objects[GRID_WIDTH][GRID_HEIGHT]{};

	std::string object;

	//Ignore first line
	std::getline(levelFile, object);

	GameAreaObject tmpObject;

	//Read the next 2 lines as the mouse hole positions
	std::getline(levelFile, object);
	std::istringstream ss{ object };
	std::string token;
	std::vector<std::string> tokens;
	while (std::getline(ss, token, ',')) {
		tokens.push_back(token);
	}

	m_gameArea.m_holeEntry.posx = stoi(tokens[0]);
	m_gameArea.m_holeEntry.posy = stoi(tokens[1]);

	std::getline(levelFile, object);
	ss = std::istringstream{ object };
	tokens.clear();
	while (std::getline(ss, token, ',')) {
		tokens.push_back(token);
	}

	m_gameArea.m_holeExit.posx = stoi(tokens[0]);
	m_gameArea.m_holeExit.posy = stoi(tokens[1]);

	while (!levelFile.eof()) {
		std::getline(levelFile, object);
		if (object == "") continue; // ignore empty lines
		if (object == "Inventory") break; //Stop if we reach the inventory part of the save file

		//Create a vector of strings from the comma seperated variables
		std::istringstream ss{ object };
		std::string token;
		std::vector<std::string> tokens;

		while (std::getline(ss, token, ',')) {
			tokens.push_back(token);
		}

		tmpObject.id = idMap[tokens[0]];
		tmpObject.posx = stoi(tokens[1]);
		tmpObject.posy = stoi(tokens[2]);
		tmpObject.rot = stoi(tokens[3]);
		tmpObject.misc = stoi(tokens[4]);
		objects[tmpObject.posx][tmpObject.posy] = tmpObject;
	}

	std::vector<std::tuple<int, int>> playerInventory;

	while (!levelFile.eof()) {
		std::getline(levelFile, object);
		if (object == "") continue; // ignore empty lines

		std::istringstream ss{ object };
		std::string token;
		std::vector<std::string> tokens;

		while (std::getline(ss, token, ',')) {
			tokens.push_back(token);
		}

		playerInventory.push_back({ idMap[tokens[0]], stoi(tokens[1]) });
	}

	m_panel.SetPlayerInventory(playerInventory);

	levelFile.close();

	m_gameArea.SetGameAreaObjects(objects);

	m_gameArea.m_lastSelected = { -1,-1 };
}

void EditorManager::SaveCurrentLevel(std::string levelName) {
	std::ofstream levelFile;
	levelFile.open("data\\" + levelName + ".lev");

	levelFile << "ID, x pos, y pos, rotation, Misc variable\n";

	//Save the mouse hole positions
	levelFile << m_gameArea.m_holeEntry.posx << "," << m_gameArea.m_holeEntry.posy << "\n";
	levelFile << m_gameArea.m_holeExit.posx << "," << m_gameArea.m_holeExit.posy << "\n";

	//For each grid square save the object if it has a valid id
	for (int i = 0; i < GRID_WIDTH; ++i) {
		for (int j = 0; j < GRID_HEIGHT; j++) {
			if (m_gameArea.GetGameAreaObject({ i, j }).id != -1) {
				GameAreaObject obj = m_gameArea.GetGameAreaObject({ i, j });
				levelFile << idToString[obj.id] << "," << obj.posx << "," << obj.posy << "," << obj.rot << "," << obj.misc << "\n";
			}
		}
	}

	//Save the player inventory items
	levelFile << "Inventory\n";

	std::vector<std::tuple<int, int>> playerInventory = m_panel.GetPlayerInventory();

	for (std::tuple<int, int> item : playerInventory) {
		levelFile << idToString[std::get<0>(item)] << "," << std::get<1>(item) << "\n";
	}

	levelFile.close();
}

void EditorManager::DrawUI() {
	int xOffset{ 256 };
	int yOffset{ 48 };
	Play::DrawRect({ DISPLAY_WIDTH / 2 - xOffset - 32, DISPLAY_HEIGHT / 2 - yOffset }, { DISPLAY_WIDTH / 2 + xOffset, DISPLAY_HEIGHT / 2 + yOffset }, Play::cBlack, true);
	Play::DrawFontText("font64px", m_fileText, { DISPLAY_WIDTH / 2 - xOffset, DISPLAY_HEIGHT / 2 });
}

void EditorManager::LoadUI() {
	if (Play::KeyPressed(VK_DELETE)) {
		m_loadUI = false;
		return;
	}
	if (Play::KeyPressed(VK_BACK) && m_fileText.size() > 0) {
		m_fileText.pop_back();
	}
	if (Play::KeyPressed(VK_RETURN) && m_fileText.size() > 0) {
		LoadNewLevel(m_fileText);
		m_loadUI = false;
		m_fileText = "";
		return;
	}
	m_fileText += GetCharacterPressed();
}

void EditorManager::SaveUI() {
	if (Play::KeyPressed(VK_DELETE)) {
		m_saveUI = false;
		return;
	}
	if (Play::KeyPressed(VK_BACK) && m_fileText.size() > 0) {
		m_fileText.pop_back();
	}
	if (Play::KeyPressed(VK_RETURN) && m_fileText.size() > 0) {
		SaveCurrentLevel(m_fileText);
		m_saveUI = false;
		m_fileText = "";
		return;
	}
	m_fileText += GetCharacterPressed();
}

std::string EditorManager::GetCharacterPressed() {
	const char keys[] = {
	'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M',
	'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z',
	'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'
	};

	for (const char key : keys) {
		if (Play::KeyPressed(key)) {
			return std::string{ key };
		}
	}

	return "";
}