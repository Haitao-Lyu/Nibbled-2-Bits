#pragma once
#include "../GameTool/Math2D.h"

class Particle
{
private:
	std::string spriteName{ "" };
	Play::Point2f pos{ 0.0f, 0.0f };
	Play::Vector3f p_alpha_range{ 1.0f,0.6f,0.2f };
	Play::Vector3f p_size_lifeTime{ 1.0f, 1.0f, 1.0f };
	Play::Vector2f gravity{ 0.0f,0.0f };
	Play::Vector2f p_gravity_direction{ 0.0f, 1.0f };
	Play::Colour start_color{ 255,0,0 };
	Play::Colour end_color{ 0,0,255 };
	Play::Colour midway_color{ 0,255,0 };
	float p_gravity_acceleration{ 1.0f };
	float emitterRotation = { 0.0f };
	float angle{ 0.0f };//for calculation align to emitter direction
	float speed{ 0.0f };
	float scale{ 1.0f };
	float lifeTime{ 1.0f };
	float timeCounter{ 0.0f };
	float rotSped{ 0.0f };
	float rotIncrement{ 0.0f };
	bool isDead{ false };
public:
	friend class ParticleEmitter;

	void InitializeParticle();

	void UpdateParticle();
};

