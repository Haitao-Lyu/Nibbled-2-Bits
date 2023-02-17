#include "Play.h"
#include "Panel.h"
#include "PanelItem.h"
#include "Button.h"

Panel::Panel()
{
}


Panel::Panel(std::vector<ObjectCSV> objects)
{
	m_type = ItemType::ENVIRONMENT;

	Play::Vector2D sideButtonSize = Play::Vector2D(64, 64);
	m_leftButton = Button(Play::GetSpriteId("arrow_left_UI"), Play::Point2D(25, HEIGHT - 90), sideButtonSize);
	m_rightButton = Button(Play::GetSpriteId("arrow_right_UI"), Play::Point2D(WIDTH - 90, HEIGHT - 90), sideButtonSize);

	Play::Vector2D verticalButtonSize = Play::Vector2D(64, 32);
	m_upButton = Button(Play::GetSpriteId("arrow_up_UI"), Play::Point2D(WIDTH / 2 - 32, HEIGHT - 145), verticalButtonSize);
	m_downButton = Button(Play::GetSpriteId("arrow_down_UI"), Play::Point2D(WIDTH / 2 - 32, 20), verticalButtonSize);


	std::vector<PanelItem> items;
	for (ObjectCSV object : objects)
	{
		items.push_back(PanelItem(object.id, ItemType(object.group), object.name, object.spriteID[4]));
		//items.push_back(PanelItem(ENVIRONMENT, object.name, "mouse_trap"));
	}

	SetItems(items);
}

// update/draw ================================================================
void Panel::Update() 
{
	// go between category pages
	if (m_leftButton.Pressed()) {
		m_type = ItemType(std::clamp((m_type - 1), 0, int(COUNT)-1));
		m_scroll = 0;
	}
	if (m_rightButton.Pressed()) {
		m_type = ItemType(std::clamp((m_type + 1), 0, int(COUNT)-1));
		m_scroll = 0;
	}

	// scroll up and down
	if (m_upButton.Pressed()) {
		int numScrolls = NumScrolls();

		m_scroll = std::clamp((m_scroll - 1), 0, numScrolls);
	}
	if (m_downButton.Pressed()) {
		int numScrolls = NumScrolls();

		m_scroll = std::clamp( (m_scroll + 1) , 0, numScrolls);
	}

	m_leftButton.Update();
	m_rightButton.Update();
	m_upButton.Update();
	m_downButton.Update();

	// update items
	for (PanelItem& item : m_organisedItems[m_type])
	{
		item.Update();
	}

	GetPlayerInventory();
}


void Panel::Draw()
{
	static Play::Point2D pos = Play::Point2D(0, 0);
	Draw(pos);
}

void Panel::Draw(Play::Point2D pos)
{
	// heading
	Play::DrawFontText("font64px_10x10", PanelItem::ItemTypeName(m_type), Play::Point2D(WIDTH / 2, HEIGHT - 55), Play::CENTRE);

	if (!(m_type <= 0))
	{
		m_leftButton.Draw();
	}
	if (!(m_type >= ItemType::COUNT-1))
	{
		m_rightButton.Draw();
	}

	int numScrolls = NumScrolls();
	
	// draw buttons which are usable
	if (m_scroll > 0)
	{
		m_upButton.Draw();
	}
	if (m_scroll < numScrolls)
	{
		m_downButton.Draw();
	}

	// draw items which are visible
	for (int i = 0; i < m_organisedItems[m_type].size(); i++)
	{
		if (int(i / (ROWS * COLUMNS)) == m_scroll) {
			m_organisedItems[m_type][i].Draw();
		}
	}
}


// get/set ===============================================================
void Panel::SetItems(std::vector<PanelItem> items) {

	for (int i = 0; i < ItemType(COUNT); i++)
	{
		// organise into a 2d vector based on categories
		std::vector<PanelItem> categorisedItems;
		for (PanelItem& item : items)
		{
			if (item.GetType() == i)
			{
				categorisedItems.push_back(item);
			}
		}
		m_organisedItems.push_back(categorisedItems);

		// set positions
		for (int j = 0; j < m_organisedItems[i].size(); j++)
		{
			int spacing = (WIDTH - ITEM_SIZE * COLUMNS) / (COLUMNS + 1);
			int xpos = spacing + ((j % (ROWS * COLUMNS) % COLUMNS * (ITEM_SIZE + spacing)));
			int ypos = HEIGHT - ((j % (ROWS * COLUMNS) / COLUMNS * (ITEM_SIZE + spacing))) - ITEM_SIZE - spacing - LIST_POSITION + 15;

			m_organisedItems[i][j].SetPos(Play::Point2D(xpos, ypos));
		}
	}
}

int Panel::GetSelection()
{
	for (int i = 0; i < m_organisedItems[m_type].size(); i ++ )
	{
		PanelItem& item = m_organisedItems[m_type][i];
		if (int(i / (ROWS * COLUMNS)) == m_scroll && item.Pressed())
		{
			return item.GetID();
		}
	}
	return -1;
}

std::vector<std::tuple<int, int>> Panel::GetPlayerInventory()
{
	std::vector<std::tuple<int, int>> inventory;

	for (std::vector<PanelItem>& itemGroup : m_organisedItems)
	{
		for (PanelItem& item : itemGroup)
		{
			std::tuple<int, int> element{ item.GetID(), item.GetInventory() };
			inventory.push_back(element);
		}
	}
	

	return inventory;
}

void Panel::SetPlayerInventory(std::vector<std::tuple<int, int>> inventory)
{
	for (std::vector<PanelItem>& itemGroup : m_organisedItems)
	{
		for (PanelItem& item : itemGroup)
		{
			for (std::tuple<int, int> quantity: inventory)
			{
				if (std::get<0>(quantity) == item.GetID())
				{
					item.SetInventory(std::get<1>(quantity));
				}
			}
		}
	}
}


// functions =================================================
int Panel::NumScrolls()
{
	return std::clamp(int((m_organisedItems[m_type].size() - 1) / (COLUMNS * ROWS)), 0, std::numeric_limits<int>::max());
}