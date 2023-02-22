#include "pch.h"
#include "MouseState.h"
#include "../GameTool/DebugTool.h"
#include "../MainGame.h"
#include "Mouse.h"
#include "GameObjectMgr.h"

static const Play::Matrix2D dir_left = Play::MatrixRotation(Play::DegToRad(90.0f));
static const Play::Matrix2D dir_down = Play::MatrixRotation(Play::DegToRad(180.0f));
static const Play::Matrix2D dir_right = Play::MatrixRotation(Play::DegToRad(270.0f));
static const Play::Matrix2D dir_up = Play::MatrixIdentity();

MouseState::MouseState(Mouse* mice)
{
	m_mice = mice;
}

void MouseState::ResetAnimFrame()
{
	frame = 0;
}

void MouseState::Render()
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
	m_mice->m_height = Play::GetSpriteHeight(spriteID);
	m_mice->m_width = Play::GetSpriteWidth(spriteID);

	Play::DrawSpriteTransformed(spriteID, scaleMt * rtMt,0);

	spritePrefix = spriteNameWithOutSuffix;
}

MouseState::~MouseState()
{
}

MouseIdleState::MouseIdleState(Mouse& mouse):MouseState(&mouse)
{
	spritePrefix += mouse.m_Color;
	spritePrefix += "idle_0";
	spriteNameWithOutSuffix = spritePrefix;
}

//update logic
void MouseIdleState::Update()
{
	Render();
}
//update anim
void MouseIdleState::Render()
{

	if (timer.isReachTimeInterval())
	{
		frame++;
		if (frame > maxAnimFrame)
		{
			frame = 0;
		}
	}
	MouseState::Render();
}

MouseJumpState::MouseJumpState(Mouse& mouse) :MouseState(&mouse)
{
	spritePrefix += mouse.m_Color;
	spritePrefix += "jump_0";
	spriteNameWithOutSuffix = spritePrefix;
}

void MouseJumpState::Update()
{
	Render();
}

void MouseJumpState::Render()
{
	if (timer.isReachTimeInterval())
	{
		frame++;
		if (frame > maxAnimFrame)
		{
			frame = 0;
		}
	}
	MouseState::Render();
}

MouseWalkState::MouseWalkState(Mouse& mouse) :MouseState(&mouse)
{
	spritePrefix += mouse.m_Color;
	spritePrefix += "walk_0";
	spriteNameWithOutSuffix = spritePrefix;
}

void MouseWalkState::Update()
{
	Render();
}

void MouseWalkState::Render()
{
	if (timer.isReachTimeInterval())
	{
		frame++;
		if (frame > maxAnimFrame)
		{
			frame = 0;
		}
	}
	MouseState::Render();
}

MouseWhackedState::MouseWhackedState(Mouse& mouse) :MouseState(&mouse)
{
	spritePrefix += mouse.m_Color;
	spritePrefix += "whacked_0";
	spriteNameWithOutSuffix = spritePrefix;
}

void MouseWhackedState::Update()
{
	OnWhacked(3.0f);
	Render();
}

void MouseWhackedState::Render()
{
	if (timer.isReachTimeInterval())
	{
		frame++;
		if (frame > maxAnimFrame)
		{
			frame = 0;
		}
	}
	MouseState::Render();
}

void MouseWhackedState::OnWhacked(float whackTime)
{
	static Timer timer(whackTime);
	if (m_mice->isWhacked)
	{
		m_mice->m_pos = m_mice->prev_pos;
		m_mice->SetMouseState(E_MOUSE_STATE::whackedState);
		if (timer.isReachTimeInterval())
		{
			m_mice->isWhacked = false;
			m_mice->SetMouseState(E_MOUSE_STATE::idleState);
		}
	}
	else
	{
		timer.Restart();
	}
}

MouseHurtState::MouseHurtState(Mouse& mouse) :MouseState(&mouse)
{
	spritePrefix += mouse.m_Color;
	spritePrefix += "hurt_0";
	spriteNameWithOutSuffix = spritePrefix;
}

void MouseHurtState::Update()
{
	Render();
}

void MouseHurtState::Render()
{
	if (timer.isReachTimeInterval())
	{
		frame++;
		if (frame > maxAnimFrame)
		{
			frame = 0;
		}
	}
	MouseState::Render();
}

MouseDieState::MouseDieState(Mouse& mouse) :MouseState(&mouse)
{
	spritePrefix += mouse.m_Color;
	spritePrefix += "die_0";
	spriteNameWithOutSuffix = spritePrefix;
}

void MouseDieState::Update()
{
	Render();
	OnDead();
}

void MouseDieState::Render()
{
	if (timer.isReachTimeInterval())
	{
		frame++;
		if (frame > maxAnimFrame)
		{
			frame = 0;
		}
	}
	MouseState::Render();
}

void MouseDieState::OnDead()
{
	if (m_mice->isDead)
	{
		m_mice->m_pos = m_mice->prev_pos;
	}
	if (frame == maxAnimFrame)
	{
		GameObjectMgr::RemoveGameObject(*m_mice);
	}
}

MouseRunState::MouseRunState(Mouse& mouse) :MouseState(&mouse)
{
	spritePrefix += mouse.m_Color;
	spritePrefix += "run_0";
	spriteNameWithOutSuffix = spritePrefix;
}

void MouseRunState::Update()
{
	Render();
}

void MouseRunState::Render()
{
	if (timer.isReachTimeInterval())
	{
		frame++;
		if (frame > maxAnimFrame)
		{
			frame = 0;
		}
	}
	MouseState::Render();
}
