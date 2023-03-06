#pragma once
#include "MouseState.h"

class MouseHurtState : public MouseState
{
private:
	const int maxAnimFrame = 4;
public:
	MouseHurtState();
	void Update(Mouse* m_mice) override;
	void Render(Mouse* m_mice) override;
};
