#include "pch.h"
#include "Particle.h"
#include "../GameTool/Timer.h"

void Particle::UpdateParticle()
{
	float elapsedTime = Timer::DeltaTime();
	//random direction of motion for each particle
	float degree = angle;

	//Generate random angle for each particle//
	//because direction is { 0 , -1 }, so equation is x = sin() y = -cos()
	float dir_x = speed * (sin((degree + emitterRotation) / 180 * 3.14159f));
	float dir_y = -speed * (cos((degree + emitterRotation) / 180 * 3.14159f));

	Play::Vector2D velocity{ dir_x, dir_y };
	gravity += p_gravity_acceleration * p_gravity_direction * elapsedTime;

	rotIncrement += (rotSped * elapsedTime);
	pos += (velocity + gravity);

	float center_time = lifeTime / 2;
	float period_one = center_time / 2;
	float period_two = (lifeTime - period_one) / 2;
	float renderSize = scale;
	float renderAplha = 0.0f;
	Play::Colour renderColor{ 0,0,0 };

	timeCounter += elapsedTime;
	//change render color based on time
	if (timeCounter > 0 && timeCounter < period_one)
	{
		renderSize  = interpolate(renderSize, p_size_lifeTime.x,0.0f, period_one, timeCounter);
		renderColor = interpolate(start_color, midway_color, 0.0f, period_one, timeCounter);
		renderAplha = p_alpha_range.x;
	}
	else if (timeCounter >= period_one && timeCounter < period_two)
	{
		renderSize  = interpolate(p_size_lifeTime.x, p_size_lifeTime.y, period_one, period_two, timeCounter);
	
		renderColor = interpolate(midway_color, end_color, period_one, period_two, timeCounter);
		renderAplha = p_alpha_range.y;
	}
	else
	{
		renderSize  = interpolate(p_size_lifeTime.y, p_size_lifeTime.w, period_two, lifeTime, timeCounter);
		renderColor = end_color;
		renderAplha = p_alpha_range.w;
	}

	if (timeCounter > lifeTime)
	{
		isDead = true;
	}

	if (p_size_lifeTime == Play::Vector3f(1.0f,1.0f,1.0f))
	{
		renderSize = scale;
	}

	Play::SetDrawingBlendMode(Play::BLEND_ADD);

	Play::DrawSpriteRotated(spriteName.c_str(), pos, 0, rotIncrement, renderSize, renderAplha, renderColor);
}

void Particle::InitializeParticle()
{

}
