#include "pch.h"
#include "MouseDieState.h"
#include "../Mouse.h"
#include "../../Manager/GameObjectMgr.h"
MouseDieState::MouseDieState()
{

}

void MouseDieState::Update(Mouse* m_mice)
{
	spritePrefix += m_mice->m_Color;
	spritePrefix += "die_0";
	spriteNameWithOutSuffix = spritePrefix;

	Render(m_mice);

	OnDead(m_mice);
}

void MouseDieState::Render(Mouse* m_mice)
{
	if (isLooping)
	{
		if (timer.isReachTimeInterval())
		{
			frame++;
			if (frame > maxAnimFrame)
			{
				isAnimEnd = true;
				isLooping = false;
				frame = maxAnimFrame - 1;
			}
		}
	}
	MouseState::Render(m_mice);
}

void MouseDieState::OnDead(Mouse* m_mice)
{
	if (m_mice->isDead)
	{
		m_mice->m_pos = m_mice->prev_pos;
	}
	if (frame == maxAnimFrame)
	{
		//GameObjectMgr::RemoveGameObject(*m_mice);
	}
}