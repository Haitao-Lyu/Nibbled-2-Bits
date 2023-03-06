#pragma once
#include "MouseState.h"
class MouseRunState : public MouseState
{
private:
	const int maxAnimFrame = 7;
public:
	MouseRunState();
	void Update(Mouse* m_mice) override;
	void Render(Mouse* m_mice) override;
};