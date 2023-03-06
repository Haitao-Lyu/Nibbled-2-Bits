#include "pch.h"
#include "MouseJumpState.h"
#include "../Mouse.h"
MouseJumpState::MouseJumpState() 
{

}

void MouseJumpState::Update(Mouse* m_mice)
{
	spritePrefix += m_mice->m_Color;
	spritePrefix += "jump_0";
	spriteNameWithOutSuffix = spritePrefix;
	Render(m_mice);
}

void MouseJumpState::Render(Mouse* m_mice)
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