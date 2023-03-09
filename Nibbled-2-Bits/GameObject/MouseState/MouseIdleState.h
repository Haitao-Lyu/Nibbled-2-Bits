#pragma once
#include "MouseState.h"

class MouseIdleState : public MouseState
{
private:
	const int maxAnimFrame = 17;
	Timer timer{ 0.02f };
public:
	MouseIdleState();
	void Update(Mouse* m_mice) override;
	void Render(Mouse* m_mice) override;
};