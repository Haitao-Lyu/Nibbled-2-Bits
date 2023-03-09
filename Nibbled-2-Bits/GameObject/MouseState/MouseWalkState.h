#pragma once
#include "MouseState.h"

class MouseWalkState : public MouseState
{
private:
	const int maxAnimFrame = 7;
	Timer timer{ 0.02f };
public:
	MouseWalkState();
	void Update(Mouse* m_mice) override;
	void Render(Mouse* m_mice) override;
};