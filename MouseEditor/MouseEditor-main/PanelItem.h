#pragma once
#include "Play.h"
#include "Button.h"

enum ItemType {
	CONFIGURATION = 0,
	ENVIRONMENT,
	PROTECTIVE,
	REWARD,
	HAZARD,
	COUNT
};

class PanelItem : public Button
{
public:
	static constexpr int MAX_INVENTORY = 99;

	PanelItem();
	PanelItem(int id, ItemType type, std::string name, int);

	void Update() override;
	void Draw() override;

	bool Pressed() override;

	void DrawSprite(Play::Point2D position) override;

	void SetVisible(bool);
	static std::string ItemTypeName(int);

	void SetInventory(int n);
	int GetInventory();

	void SetPos(Play::Point2D pos) override;

	void SetID(int id);
	int GetID();
	ItemType GetType();

private:
	int m_id;
	ItemType m_type;
	std::string m_name;

	int m_playerInventory = 0;
	Button m_subtractButton;
	Button m_addButton;

};
