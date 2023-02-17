#pragma once
#include "Play.h"
#include "PanelItem.h"
#include "Button.h"
#include "ReadCSV.h"


class Panel
{
public:
	static constexpr int WIDTH = 410;
	static constexpr int HEIGHT = 720;

	static constexpr int ROWS = 3;
	static constexpr int COLUMNS = 2;

	static constexpr int ITEM_SIZE = 100;

	static constexpr int LIST_POSITION = 100;

	Panel(std::vector<ObjectCSV> objects);
	Panel();

	void Update();
	void Draw();
	void Draw(Play::Point2D);

	void SetItems(std::vector<PanelItem>);

	int GetSelection();

	std::vector<std::tuple<int, int>> GetPlayerInventory();
	void SetPlayerInventory(std::vector<std::tuple<int, int>>);

private:
	std::vector<std::vector<PanelItem>> m_organisedItems;

	ItemType m_type;
	int m_scroll{ 0 };

	Button m_leftButton;
	Button m_rightButton;

	Button m_upButton;
	Button m_downButton;

	int NumScrolls();
};