#include "pch.h"
#include "Cheese.h"
#include <vector>
#include "../MainGame.h"
#include "GameObjectMgr.h"
const char* cz_01 = "cz_brie";
const char* cz_02 = "cz_camembert";
const char* cz_03 = "cz_cheddar";
const char* cz_04 = "cz_edam";
const char* cz_05 = "cz_emmental";
const char* cz_06 = "cz_gorgonzola";
const char* cz_07 = "cz_Manchego";
const char* cz_08 = "cz_mozzarella";
const char* cz_09 = "cz_parmesan";
const char* cz_010 = "cz_provolone";
const char* cz_011 = "cz_ricotta";
const char* cz_012 = "cz_sandwich";
const char* cz_013 = "cz_smoked";
const char* cz_014 = "cz_stilton";
const char* cz_015 = "cz_swiss";
const char* cz_016 = "cz_wensleydale";

static std::vector<const char* > chesse_list{ cz_01,cz_02,cz_03,cz_04,cz_05,cz_06,cz_07,cz_08,cz_09,cz_010,cz_011,cz_012,cz_013,cz_014,cz_015,cz_016,}; 

Cheese::Cheese(Play::Point2D pos):ConsumableObj(pos,E_OBJTYPE::E_CHEESE)
{
	spriteName = chesse_list[Play::RandomRollRange(0, 15)];
	m_spriteHeight = Play::GetSpriteHeight(spriteName);
	m_spriteWidth = Play::GetSpriteWidth(spriteName);
	m_boxCollider.Init(m_spriteWidth, m_spriteHeight,pos,this);
	m_circleCollider.Init(pos, m_spriteHeight / 2 * m_scale);
}

Cheese::~Cheese()
{
}

void Cheese::Update()
{
	if (isConsumed)
	{
		GameObjectMgr::RemoveGameObject(*this);
	}
	Render();
	//m_boxCollider.DrawBoundingBox();
	//m_circleCollider.DrawBoundingBox(Play::cBlue);
}

void Cheese::Render()
{
	Play::Matrix2D rotMt = Play::MatrixRotation(Play::DegToRad(m_rot));
	const Play::Matrix2D scaleMt = Play::Matrix2D(
		{ m_scale ,0.0f,0.0f },
		{ 0.0f,m_scale ,0.0f },
		{ m_pos.x,DISPLAY_HEIGHT - m_pos.y,0.0f });
	Play::DrawSpriteTransformed(Play::GetSpriteId(spriteName), scaleMt * rotMt, 0);
}
