#pragma once
#include "../GameTool/Timer.h"
#include <string>

class Mouse;

class MouseState
{
protected:
	Mouse* m_mice = nullptr;
	std::string spritePrefix = "Mouse_";
	std::string spriteNameWithOutSuffix;
	int frame = 0;
	Timer timer{ 0.1f };
public:
	virtual void Update() = 0;
	virtual void Render();
	virtual ~MouseState();
	MouseState(Mouse* mice);
	void ResetAnimFrame();
};

class MouseIdleState : public MouseState
{
private:
	const int maxAnimFrame = 17;
public:
	MouseIdleState(Mouse& mouse);
	void Update() override;
	void Render() override;
};

class MouseJumpState : public MouseState
{
private:
	const int maxAnimFrame = 9;
public:
	MouseJumpState(Mouse& mouse);
	void Update()override;
	void Render() override;
};

class MouseRunState : public MouseState
{
private:
	const int maxAnimFrame = 7;
public:
	MouseRunState(Mouse& mouse);
	void Update() override;
	void Render() override;
};

class MouseWalkState : public MouseState
{
private:
	const int maxAnimFrame = 7;
public:
	MouseWalkState(Mouse& mouse);
	void Update() override;
	void Render() override;
};

class MouseWhackedState : public MouseState
{
private:
	const int maxAnimFrame = 15;
public:
	MouseWhackedState(Mouse& mouse);
	void Update() override;
	void Render() override;
};

class MouseHurtState : public MouseState
{
private:
	const int maxAnimFrame = 4;
public:
	MouseHurtState(Mouse& mouse);
	void Update() override;
	void Render() override;
};

class MouseDieState : public MouseState
{
private:
	const int maxAnimFrame = 4;
public:
	MouseDieState(Mouse& mouse);
	void Update()override;
	void Render() override;
};
