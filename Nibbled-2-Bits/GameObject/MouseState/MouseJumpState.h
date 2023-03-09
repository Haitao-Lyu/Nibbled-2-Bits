#pragma once
#include "MouseState.h"

class MouseJumpState : public MouseState
{
private:
	const int maxAnimFrame = 9;
	Timer timer{ 0.02f };
public:
	MouseJumpState();
	void Update(Mouse* m_mice)override;
	void Render(Mouse* m_mice) override;
};