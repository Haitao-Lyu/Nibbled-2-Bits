#include "pch.h"
#include "ParticleEmitter.h"
#include "Particle.h"
#include "../GameTool/Timer.h"

using namespace Play;

void ParticleEmitter::InitParticleEmitter(Point2f _pos, Vector2f _scale, float _rot, int _quantities, Vector2f _p_speedRange, Vector2f _p_lifeTimeRange, float _p_randomDirRange, Vector2f _p_sizeRange, float _spwanDelay, float _p_gravity_acceleration, Vector2f _p_gravity_direction, Play::Colour _start_color, Play::Colour _midway_color, Play::Colour _end_color, Play::Vector3D _p_alpha_range, std::string _spriteName, Play::Vector3D _p_rot_range, Play::Vector3D _p_size_lifeTime, E_CULLINGMASK _culling)
{
	this->pos = _pos;
	this->scale = _scale;
	this->rot = _rot;
	this->quantities = _quantities;
	this->p_speedRange = _p_speedRange;
	this->p_lifeTimeRange = _p_lifeTimeRange;
	this->p_randomDirRange = _p_randomDirRange;
	this->p_dirRange = Vector2f(-_p_randomDirRange / 2, _p_randomDirRange / 2);
	this->p_sizeRange = _p_sizeRange;
	this->spwanDelay = _spwanDelay;
	this->p_gravity_acceleration = _p_gravity_acceleration;
	this->p_gravity_direction = _p_gravity_direction;
	this->start_color = _start_color;
	this->midway_color = _midway_color;
	this->end_color = _end_color;
	this->p_alpha_range = _p_alpha_range;
	this->spriteName = _spriteName;
	this->p_rot_range = _p_rot_range;
	this->p_size_lifeTime = _p_size_lifeTime;
	this->e_cullingshape = _culling;
}

void ParticleEmitter::InitParticles()
{
	// every time generate a new group push into list
	for (int i = 0; i < quantities; i++)
	{
		Particle particle;
		//init name
		particle.spriteName = spriteName;

		if (e_cullingshape == E_CULLINGMASK::E_LINE)
		{
			float offset = 100;
			LineMask linemask = LineMask(Point2D(pos.x, pos.y + offset), Point2D(pos.x, pos.y - offset));
			particle.pos = linemask.start_pos;
			//init random size scale
			particle.scale = static_cast<float>(GetRandomFloat(p_sizeRange.x, p_sizeRange.y));
			//init random speed
			particle.speed = static_cast<float>(GetRandomFloat(p_speedRange.x, p_speedRange.y));
			//init lifetime
			particle.lifeTime = static_cast<float>(GetRandomFloat(p_lifeTimeRange.x, p_lifeTimeRange.y));

			//init random direction range
			particle.angle = static_cast<float>(GetRandomFloat(p_dirRange.x, p_dirRange.y));

			//init random rot speed and increment value
			particle.rotSped = GetRandomFloat(p_rot_range.x, p_rot_range.y);
			particle.rotIncrement = p_rot_range.w;

			

		}
		else
		{
			//init random pos for particle
			float randPosX = GetRandomFloat(pos.x - scale.x, pos.x + scale.x);
			float randPosY = GetRandomFloat(pos.y - scale.y, pos.y + scale.y);
			particle.pos = Point2f(randPosX, randPosY);

			//init random size scale
			particle.scale = static_cast<float>(GetRandomFloat(p_sizeRange.x, p_sizeRange.y));

			//init random speed
			particle.speed = static_cast<float>(GetRandomFloat(p_speedRange.x, p_speedRange.y));

			//init lifetime
			particle.lifeTime = static_cast<float>(GetRandomFloat(p_lifeTimeRange.x, p_lifeTimeRange.y));

			//init random direction range
			particle.angle = static_cast<float>(GetRandomFloat(p_dirRange.x, p_dirRange.y));

			//init random rot speed and increment value
			particle.rotSped = GetRandomFloat(p_rot_range.x, p_rot_range.y);
			particle.rotIncrement = p_rot_range.w;
		}

		particle.p_alpha_range   = p_alpha_range;
		particle.start_color     = start_color;
		particle.midway_color	 = midway_color;
		particle.end_color		 = end_color;
		particle.p_size_lifeTime = p_size_lifeTime;
		particle.p_gravity_acceleration = p_gravity_acceleration;
		particle.p_gravity_direction = p_gravity_direction;
		particle.emitterRotation = rot;

		//add into list
		particle_list.push_back(particle);// will execute copy constructor
	}
}

void ParticleEmitter::GenerateParticles()
{
	if (!isPlaying)
	{
		return;
	}
	//-- called in UpdateEmitter --
	timeCounter += Timer::DeltaTime();
	if (timeCounter >= spwanDelay)
	{
		InitParticles();
		timeCounter = 0;
		if (!islooping)
		{
			isPlaying = false;
		}
	}

}

void ParticleEmitter::UpdateEmitter()
{
	#ifdef P_DEBUG
	if (isShowDebugLine)
	DrawParticleCenter();
	#endif
	
	float elapsedTime = Timer::DeltaTime();

	GenerateParticles();
	for (int i = 0; i != particle_list.size(); i++)
	{
		Particle& particle = particle_list[i];
		//chose culling
		switch (e_cullingshape)
		{
		case E_CULLINGMASK::E_DIAMOND:
		{
		
			float x_offset = 100;
			float y_offset = 200;
			DiamondMask diamondmask = DiamondMask(Point2D(pos.x, pos.y - y_offset), Point2D(pos.x - x_offset, pos.y), Point2D(pos.x + x_offset, pos.y), Point2D(pos.x, pos.y + y_offset));
			#ifdef P_DEBUG
			if (isShowDebugLine)
			diamondmask.DrawOutline();
			#endif // DEBUG

			//remove from list
			if (!diamondmask.isInSide(particle.pos))
			{
				particle.isDead = true;
			}
			break;
		}
		case E_CULLINGMASK::E_LINE:
		{
			float offset = 100;
			LineMask linemask = LineMask(Point2D(pos.x, pos.y + offset), Point2D(pos.x, pos.y - offset));
			#ifdef P_DEBUG
			if (isShowDebugLine)
			linemask.DrawOutline();
			#endif // DEBUG
			//float _distance = linemask.PointDistance(particle.pos);
			//renderAplha = abs(1/_distance);
			if (linemask.isOnEnd(particle.pos))
			{
				particle.isDead = true;
			}
			if (linemask.isOnRightSide(particle.pos))
				particle.gravity += linemask.PointDistance(particle.pos) * -linemask.v_perp_n * p_gravity_acceleration * elapsedTime;
			else
				particle.gravity += linemask.PointDistance(particle.pos) * -linemask.v_perp_n * p_gravity_acceleration * elapsedTime;

			break;
		}
		case E_CULLINGMASK::E_TRIANGLE:
		{
			TriangleMask triangle(60, pos);
			#ifdef P_DEBUG
			if (isShowDebugLine)
			triangle.DrawOutline();
			#endif // DEBUG
			if (!triangle.isInSide(particle.pos))
			{
				particle.isDead = true;
			}
			break;
		}
		}

		if (particle.isDead)
		{
			particle_list.erase(particle_list.begin() + i);
			i--;
			continue;
		}

		particle.UpdateParticle();
	}

}

void ParticleEmitter::DrawParticleCenter()
{
	Play::DrawSpriteRotated("circle", pos, 0, 0, 0.5f, 0.5f, Play::Colour(0, 255, 0));
}

void ParticleEmitter::DrawDebugLine(bool isDebugging)
{
	isShowDebugLine = isDebugging;
}

bool ParticleEmitter::isEndPlaying()
{
	if (!isPlaying)
	{
		if (particle_list.empty())
			return true;
	}
	return false;
}

void ParticleEmitter::SetLooping(bool bl)
{
	islooping = bl;
}

void ParticleEmitter::SetPlaying(bool bl)
{
	isPlaying = bl;
}
