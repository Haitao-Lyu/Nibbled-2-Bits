#include "pch.h"
#include "MouseIdleState.h"
#include "../Mouse.h"
MouseState::~MouseState()
{
}

MouseIdleState::MouseIdleState() 
{

}

//update logic
void MouseIdleState::Update(Mouse* m_mice)
{
	spritePrefix += m_mice->m_Color;
	spritePrefix += "idle_0";
	spriteNameWithOutSuffix = spritePrefix;
	Render(m_mice);
}
//update anim
void MouseIdleState::Render(Mouse* m_mice)
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
