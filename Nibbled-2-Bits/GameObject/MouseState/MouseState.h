#pragma once
#include "../../GameTool/Timer.h"
#include <string>

class Mouse;

class MouseState
{
protected:
	std::string spritePrefix = "Mouse_";
	std::string spriteNameWithOutSuffix;
	int frame = 0;
	Timer timer{ 0.1f };
public:
	virtual void Update(Mouse* m_mice) = 0;
	virtual void Render(Mouse* m_mice);
	virtual ~MouseState();
	MouseState();
	void ResetAnimFrame();
};











