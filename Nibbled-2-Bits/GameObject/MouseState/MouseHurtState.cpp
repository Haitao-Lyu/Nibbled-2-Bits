#include "pch.h"
#include "MouseHurtState.h"
#include "../Mouse.h"
MouseHurtState::MouseHurtState() 
{

}

void MouseHurtState::Update(Mouse* m_mice)
{
	spritePrefix += m_mice->m_Color;
	spritePrefix += "hurt_0";
	spriteNameWithOutSuffix = spritePrefix;
	Render(m_mice);
}

void MouseHurtState::Render(Mouse* m_mice)
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