#include "pch.h"
#include "MouseWalkState.h"
#include "../Mouse.h"

MouseWalkState::MouseWalkState() 
{

}

void MouseWalkState::Update(Mouse* m_mice)
{
	spritePrefix += m_mice->m_Color;
	spritePrefix += "walk_0";
	spriteNameWithOutSuffix = spritePrefix;

	switch (m_mice->m_dir)
	{
	case E_MOUSE_DIR::UP:
		m_mice->m_pos.y -= m_mice->m_speed;
		break;
	case E_MOUSE_DIR::LEFT:
		m_mice->m_pos.x -= m_mice->m_speed;
		break;
	case E_MOUSE_DIR::DOWN:
		m_mice->m_pos.y += m_mice->m_speed;
		break;
	case E_MOUSE_DIR::RIGHT:
		m_mice->m_pos.x += m_mice->m_speed;
		break;
	default:
		break;
	}
	Render(m_mice);
}

void MouseWalkState::Render(Mouse* m_mice)
{
	if (timer.isReachTimeInterval())
	{
		frame++;
		if (frame > maxAnimFrame)
		{
			frame = 0;
		}
	}
	MouseState::Render(m_mice);
}