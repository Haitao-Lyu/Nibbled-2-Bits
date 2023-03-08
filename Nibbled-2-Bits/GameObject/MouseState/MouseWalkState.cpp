#include "pch.h"
#include "MouseWalkState.h"
#include "../Mouse.h"
#include "../../Particle/ParticleManager.h"
#include "../../GameTool/Timer.h"
const char* foot_bottom_down_name = "foot_bottom_down";
const char* foot_bottom_left_name = "foot_bottom_left";
const char* foot_bottom_right_name = "foot_bottom_right";
const char* foot_bottom_up_name = "foot_bottom_up";
MouseWalkState::MouseWalkState() 
{

}

void MouseWalkState::Update(Mouse* m_mice)
{
	using namespace Play;
	spritePrefix += m_mice->m_Color;
	spritePrefix += "walk_0";
	spriteNameWithOutSuffix = spritePrefix;

	static Timer foot_timer{ 0.2f };
	ParticleEmitter* emitter = nullptr;
	if(foot_timer.isReachTimeInterval())
		emitter = ParticleMgr::GetInstance().CreateNewEmitter(
		//init emitter pos
		m_mice->m_pos,
		//init emitter scale
		Vector2f{ 15.0f, 15.0f },
		//init emitter rotation based on intial direction { 0 , -1 }
		m_mice->m_rot,
		//init particle num
		2,///cant do one has a bug
		//init random speed extent
		Vector2f(0.0f, 0.0f),
		//init lifetime min and max
		Vector2f(0.2f, 0.5f),
		//init random particle direction of motion range
		0.0f,
		//init size range
		Vector2f(1.0f, 0.8f),
		//init delay time
		0.2f,
		//init gravity & direction
		0.0f,
		Vector2f(0.0f, 0.0f),
		//init three color
		Play::Colour(213, 255, 112),
		Play::Colour(189, 255, 102),
		Play::Colour(255, 255, 102),
		//init three alpha
		Play::Vector3D(0.8f, 0.6f, 0.4f),
		"foot_bottom",
		//ROT RANGE
		Play::Vector3D(0, 0, 0),
		//SIZE LIFE TIME
		Play::Vector3D(1.0f, 1.0f, 1.0f)
	);

	switch (m_mice->m_dir)
	{
	case E_MOUSE_DIR::UP:
		m_mice->m_pos.y -= m_mice->m_speed;
		if (emitter)
		{
			emitter->SetSpriteName(foot_bottom_up_name);
			emitter->SetPosition(m_mice->m_pos);
		}

		break;
	case E_MOUSE_DIR::LEFT:
		m_mice->m_pos.x -= m_mice->m_speed;
		if (emitter)
		{
			emitter->SetPosition(m_mice->m_pos);
			emitter->SetSpriteName(foot_bottom_left_name);
		}
		break;
	case E_MOUSE_DIR::DOWN:
		m_mice->m_pos.y += m_mice->m_speed;
		if (emitter)
		{
			emitter->SetPosition(m_mice->m_pos);
			emitter->SetSpriteName(foot_bottom_down_name);
		}
		break;
	case E_MOUSE_DIR::RIGHT:
		m_mice->m_pos.x += m_mice->m_speed;
		if (emitter)
		{
		emitter->SetPosition(m_mice->m_pos);
		emitter->SetSpriteName(foot_bottom_right_name);
		}
		break;
	default:
		break;
	}
	Render(m_mice);
}

void MouseWalkState::Render(Mouse* m_mice)
{
	if (timer.isReachTimeInterval())
	{
		frame++;
		if (frame > maxAnimFrame)
		{
			frame = 0;
		}
	}
	MouseState::Render(m_mice);
}