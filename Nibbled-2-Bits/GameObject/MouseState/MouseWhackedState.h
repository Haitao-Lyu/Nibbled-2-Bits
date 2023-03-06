#pragma once
#include "MouseState.h"

class MouseWhackedState : public MouseState
{
private:
	const int maxAnimFrame = 15;
public:
	MouseWhackedState();
	void Update(Mouse* m_mice) override;
	void Render(Mouse* m_mice) override;

	void OnWhacked(float whackTime, Mouse* m_mice);
};
