#pragma once
#include "MouseState.h"
class MouseRunState : public MouseState
{
private:
	const int maxAnimFrame = 7;
	Timer timer{ 0.02f };
public:
	MouseRunState();
	void Update(Mouse* m_mice) override;
	void Render(Mouse* m_mice) override;
};