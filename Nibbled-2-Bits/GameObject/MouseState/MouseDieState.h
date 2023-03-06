#pragma once
#include "MouseState.h"

class MouseDieState : public MouseState
{
private:
	const int maxAnimFrame = 4;
public:
	MouseDieState();
	void Update(Mouse* m_mice)override;

	void Render(Mouse* m_mice) override;

	void OnDead(Mouse* m_mice);
};
