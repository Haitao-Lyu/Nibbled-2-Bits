#include "pch.h"
#include "MouseState.h"
#include "../../GameTool/DebugTool.h"
#include "../../MainGame.h"
#include "../Mouse.h"

static const Play::Matrix2D dir_left = Play::MatrixRotation(Play::DegToRad(90.0f));
static const Play::Matrix2D dir_down = Play::MatrixRotation(Play::DegToRad(180.0f));
static const Play::Matrix2D dir_right = Play::MatrixRotation(Play::DegToRad(270.0f));
static const Play::Matrix2D dir_up = Play::MatrixIdentity();

MouseState::MouseState()
{

}

void MouseState::ResetAnimFrame()
{
	frame = 0;
}

void MouseState::Render(Mouse* m_mice)
{
	if (frame < 10)
	{
		spritePrefix += "0";
	}
	spritePrefix += std::to_string(frame);
	spritePrefix += "_";
	//Play::DrawSprite(spritePrefix.c_str(), m_mice->GetPosition(), 0);
	const Play::Matrix2D scaleMt = Play::Matrix2D(
		{ m_mice->m_scale,0.0f,0.0f },
		{ 0.0f,m_mice->m_scale ,0.0f },
		{ m_mice->GetPosition().x,DISPLAY_HEIGHT - m_mice->GetPosition().y,0.0f});

	Play::Matrix2D rtMt;
	switch (m_mice->m_dir)
	{
	case E_MOUSE_DIR::UP:
		rtMt = dir_up;
		break;
	case E_MOUSE_DIR::LEFT:
		rtMt = dir_left;
		break;
	case E_MOUSE_DIR::DOWN:
		rtMt = dir_down;
		break;
	case E_MOUSE_DIR::RIGHT:
		rtMt = dir_right;
		break;
	default:
		break;
	}


	int spriteID = Play::GetSpriteId(spritePrefix.c_str());
	//m_mice->SetSpriteName(spritePrefix.c_str());//not working maybe because const char ? ? ?
	m_mice->m_spriteHeight = static_cast<float>(Play::GetSpriteHeight(spriteID));
	m_mice->m_spriteWidth = static_cast<float>(Play::GetSpriteWidth(spriteID));

	Play::DrawSpriteTransformed(spriteID, scaleMt * rtMt,0);

	spritePrefix = "Mouse_";
}








