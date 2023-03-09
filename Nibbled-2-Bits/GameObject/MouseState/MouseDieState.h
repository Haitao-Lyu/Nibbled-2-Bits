#pragma once
#include "MouseState.h"

class MouseDieState : public MouseState
{
private:
	const int maxAnimFrame = 4;
	bool isAnimEnd = false;
	bool isLooping = true;
	Timer timer{ 0.2f };
public:
	MouseDieState();
	void Update(Mouse* m_mice)override;

	void Render(Mouse* m_mice) override;

	void OnDead(Mouse* m_mice);
};
