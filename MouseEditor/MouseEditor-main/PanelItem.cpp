
#include "Play.h"
#include "PanelItem.h"
#include "Button.h"

PanelItem::PanelItem()
{

}

PanelItem::PanelItem(int id_, ItemType type_, std::string name_, int sprite_) : Button(sprite_, Play::Point2D(0, 0), Play::Point2D(100, 100))
{
	m_id = id_;
	m_name = name_;
	m_type = type_;

	m_subtractButton = Button(Play::GetSpriteId("minus_UI"), m_pos, Play::Vector2D(24, 24));
	m_addButton = Button(Play::GetSpriteId("plus_UI"), m_pos, Play::Vector2D(24, 24));
}

// update/draw ========================================================
void PanelItem::Update()
{
	Button::Update();

	m_subtractButton.Update();
	if (m_subtractButton.Pressed())
	{
		int min = m_type == CONFIGURATION ? 0 : -1;

		m_playerInventory = std::clamp(--m_playerInventory, min, MAX_INVENTORY);
	}

	m_addButton.Update();
	if (m_addButton.Pressed())
	{
		int min = m_type == CONFIGURATION ? 0 : -1;

		m_playerInventory = std::clamp(++m_playerInventory, min, MAX_INVENTORY);
	}
}

void PanelItem::Draw()
{ 
	if (Held())
	{
		DrawSprite(m_pos);
	}
	else if (Hovering() && m_type != CONFIGURATION)
	{
		// draw with shifted effect based on mouse position
		Play::Point2D mousePos = Play::GetMousePos();
		Play::Point2D newPos = Play::Point2D(int(mousePos.x) - m_size.x / 2, int(mousePos.y) - m_size.y / 2);
		newPos = m_pos + (newPos - m_pos) / 4;
		DrawSprite(newPos);
	}
	else
	{
		DrawSprite(m_pos);
	}
	
	// name
	Play::DrawFontText("ABNORMAL40px_10x10", m_name, Play::Point2D(m_pos.x + m_size.x/2, m_pos.y - 17), Play::CENTRE);
	// inventory count
	if (m_playerInventory >= 0)
	{
		Play::DrawFontText("ABNORMAL40px_10x10", std::to_string(m_playerInventory), Play::Point2D(m_pos.x + m_size.x / 2, m_pos.y - 48), Play::CENTRE);
	}
	else
	{
		Play::DrawSprite(Play::GetSpriteId("infinity_ui"), { m_pos.x + m_size.x/2, m_pos.y - 48}, 0);
	}
	m_subtractButton.Draw();
	m_addButton.Draw();
}


// functions =================================================
bool PanelItem::Pressed()
{
	return m_type != CONFIGURATION ? Button::Pressed() : false;
}

std::string PanelItem::ItemTypeName(int i)
{
	switch (i)
	{
		case ENVIRONMENT:   return "Environment";
		case PROTECTIVE:	return "Protective";
		case REWARD:		return "Reward";
		case HAZARD:		return "Hazard";
		case CONFIGURATION: return "Configuration";
		default:			return "Invalid";
	}
}

void PanelItem::DrawSprite(Play::Point2D position)
{
	Button::DrawSprite(position);
}


// get/set ================================================
void PanelItem::SetInventory(int n)
{
	m_playerInventory = n;
}

int PanelItem::GetInventory()
{
	return m_playerInventory;
}

void PanelItem::SetPos(Play::Point2D pos_)
{
	m_pos = pos_;

	int yOffset = -37 ;

	m_subtractButton.SetPos(m_pos + Play::Point2D(0, yOffset - m_subtractButton.GetSize().y));
	m_addButton.SetPos(m_pos + Play::Point2D(m_size.x - m_addButton.GetSize().x, yOffset - m_addButton.GetSize().y));
}

void PanelItem::SetID(int id)
{
	m_id = id;
}

int PanelItem::GetID()
{
	return m_id;
}

ItemType PanelItem::GetType()
{
	return m_type;
}