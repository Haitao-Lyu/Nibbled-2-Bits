#pragma once
#include <vector>
#include "ParticleEmitter.h"
class ParticleMgr
{
private:
	static std::vector<ParticleEmitter> m_particle_emitter_list;// can't be static??
	bool isDebugging = false;
	static ParticleMgr* _instance;

private:
	ParticleMgr(){}

	ParticleMgr(const ParticleMgr& instance) = delete;

	ParticleMgr& operator=(ParticleMgr& instance) = delete;

	~ParticleMgr() { delete _instance; }

public:
	static ParticleMgr& GetInstance();

	static std::vector<ParticleEmitter>& GetEmitterList();

	void CreateNewEmitter(
		Play::Point2f pos = Play::Point2f(0.0f, 0.0f),
		//init emitter scale
		Play::Vector2f scale = Play::Vector2f{ 20.0f, 10.0f },
		//init emitter rotation based on intial direction { 0 , -1 }
		float rot = 0.0f,
		//init particle num
		int quantities = 5,///cant do one has a bug
		//init random speed extent
		Play::Vector2f p_speedRange = Play::Vector2f(2.2f, 2.5f),
		//init lifetime min and max
		Play::Vector2f p_lifeTimeRange = Play::Vector2f(1.2f, 3.2f),
		//init random particle direction of motion range
		float p_randomDirRange = 30.0f,
		//init size range
		Play::Vector2f p_sizeRange = Play::Vector2f(0.5f, 1.5f),
		//init delay time
		float spwanDelay = 0.2f,
		//init gravity & direction
		float p_gravity_acceleration = 1.0f,
		Play::Vector2f p_gravity_direction = Play::Vector2f(0.0f, 1.0f),
		//init three color
		Play::Colour start_color = Play::Colour(235, 128, 0),
		Play::Colour midway_color = Play::Colour(255, 77, 95),
		Play::Colour end_color = Play::Colour(255, 153, 102),
		//init three alpha
		Play::Vector3D p_alpha_range = Play::Vector3D(0.8f, 0.4f, 0.2f),
		std::string spriteName = "circle",
		Play::Vector3D p_rot_range = Play::Vector3D(0.0f, 0.0f, 0.0f),
		Play::Vector3D p_size_lifeTime = Play::Vector3D(1.0f, 1.0f, 1.0f),
		E_CULLINGMASK culling = E_CULLINGMASK::E_NULL);

	void AddNewEmitter(ParticleEmitter emitter);

	void UpdateEmitterList();

	void ClearEmitter();

	void DrawDebugLine();
	
	void Destroy();
};

