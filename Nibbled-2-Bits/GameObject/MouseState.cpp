#include "pch.h"
#include "MouseState.h"
#include "../GameTool/DebugTool.h"
#include "../MainGame.h"
#include "Mouse.h"

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
	m_mice->SetSpriteName(spritePrefix.c_str());//not working maybe because const char
	Play::DrawSpriteTransformed(Play::GetSpriteId(spritePrefix.c_str()), scaleMt,0);
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
