#pragma once
#include "pch.h"
#include "MouseRunState.h"

#include "../Mouse.h"

MouseRunState::MouseRunState() 
{

}

void MouseRunState::Update(Mouse* m_mice)
{
	spritePrefix += m_mice->m_Color;
	spritePrefix += "run_0";
	spriteNameWithOutSuffix = spritePrefix;
	Render(m_mice);
}

void MouseRunState::Render(Mouse* m_mice)
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
