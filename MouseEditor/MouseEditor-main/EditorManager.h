#pragma once
#include "Play.h"
#include "Panel.h"
#include "GameArea.h"

extern std::map<std::string, int> idMap;
extern std::vector<std::string> idToString;
extern float PI;

class EditorManager
{
public:

	EditorManager(const EditorManager&) = delete;
	EditorManager& operator = (const EditorManager&) = delete;

	EditorManager();
	EditorManager(/*Panel& panel, GameArea& gameArea, */std::vector<ObjectCSV> objects);

	void Update();
	void Draw();

	void LoadNewLevel(std::string levelName);
	void SaveCurrentLevel(std::string levelName);

private:
	GameArea m_gameArea{};
	Panel m_panel;

	FloatingObject m_currentHeld;
	std::vector<ObjectCSV> objectCSVs;

	bool m_held = false;

	bool m_loadUI{ false };
	bool m_saveUI{ false };
	std::string m_fileText{""};

	void DrawUI();
	void LoadUI();
	void SaveUI();

	std::string GetCharacterPressed();

	int SpriteFromObjectID(int id);
};