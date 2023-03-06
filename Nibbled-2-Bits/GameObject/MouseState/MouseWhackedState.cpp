#include "pch.h"
#include "MouseWhackedState.h"
#include "../Mouse.h"

MouseWhackedState::MouseWhackedState() 
{

}

void MouseWhackedState::Update(Mouse* m_mice)
{
	spritePrefix += m_mice->m_Color;
	spritePrefix += "whacked_0";
	spriteNameWithOutSuffix = spritePrefix;
	OnWhacked(3.0f, m_mice);
	Render(m_mice);
}

void MouseWhackedState::Render(Mouse* m_mice)
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

void MouseWhackedState::OnWhacked(float whackTime, Mouse* m_mice)
{
	static Timer whacktimer(whackTime);
	if (m_mice->isWhacked)
	{
		m_mice->m_pos = m_mice->prev_pos;
		m_mice->SetMouseState(E_MOUSE_STATE::whackedState);
		if (whacktimer.isReachTimeInterval())
		{
			m_mice->isWhacked = false;
			m_mice->SetMouseState(E_MOUSE_STATE::walkState);
		}
	}
	else
	{
		whacktimer.Restart();
	}
}