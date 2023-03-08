#include "pch.h"
#include "ParticleManager.h"
#include "../GameTool/DebugTool.h"

using namespace Play;

std::vector<ParticleEmitter> ParticleMgr::m_particle_emitter_list;

ParticleMgr* ParticleMgr::_instance;

ParticleMgr& ParticleMgr::GetInstance()
{
	if (_instance == nullptr)
	{
		_instance = new ParticleMgr();
	}
	return  *_instance;
}

std::vector<ParticleEmitter>& ParticleMgr::GetEmitterList()
{
	return GetInstance().m_particle_emitter_list;
}

ParticleEmitter* ParticleMgr::CreateNewEmitter(Point2f _pos, Vector2f _scale, float _rot, int _quantities, Vector2f _p_speedRange, Vector2f _p_lifeTimeRange, float _p_randomDirRange, Vector2f _p_sizeRange, float _spwanDelay, float _p_gravity_acceleration, Vector2f _p_gravity_direction, Play::Colour _start_color, Play::Colour _midway_color, Play::Colour _end_color, Play::Vector3D _p_alpha_range, std::string _spriteName, Play::Vector3D _p_rot_range, Play::Vector3D _p_size_lifeTime, E_CULLINGMASK _culling)
{
	ParticleEmitter emitter;
	emitter.InitParticleEmitter(_pos, _scale, _rot, _quantities, _p_speedRange, _p_lifeTimeRange, _p_randomDirRange, _p_sizeRange, _spwanDelay, _p_gravity_acceleration, _p_gravity_direction, _start_color, _midway_color, _end_color, _p_alpha_range, _spriteName, _p_rot_range, _p_size_lifeTime, _culling);
	AddNewEmitter(emitter);
	return &m_particle_emitter_list.back();
}


void ParticleMgr::AddNewEmitter(ParticleEmitter emitter)
{
	m_particle_emitter_list.push_back(emitter);
}

void ParticleMgr::UpdateEmitterList()
{
	//Update each emitter
	//for (ParticleEmitter& emitter : m_particle_emitter_list)
	//{
	//	emitter.UpdateEmitter();
	//}
	int length = static_cast<int>(m_particle_emitter_list.size());
	DebugValue(length,"emitter",50,Play::cGreen);

	for (int i= 0;i < m_particle_emitter_list.size(); i++)
	{
		if (m_particle_emitter_list[i].isEndPlaying())
		{
			m_particle_emitter_list.erase(m_particle_emitter_list.begin() + i);
			i--;
			continue;
		}
		m_particle_emitter_list[i].UpdateEmitter();
	}
}

void ParticleMgr::ClearEmitter()
{
	m_particle_emitter_list.clear();
}

void ParticleMgr::DrawDebugLine()
{
	isDebugging = !isDebugging;
	for (ParticleEmitter& emitter : m_particle_emitter_list)
	{
		emitter.DrawDebugLine(isDebugging);
	}
	
}

void ParticleMgr::Destroy()
{
	delete _instance;
}
//UIManager::GetInstance().UIInitialize();
//
//ParticleMgr::GetInstance().CreateNewEmitter(
//	{ DISPLAY_HEIGHT / 2,DISPLAY_WIDTH / 2 },
//	//init emitter scale
//	Play::Vector2f{ 10.0f, 10.0f },
//	//init emitter rotation based on intial direction { 0 , -1 }
//	0.0f,
//	//init particle num
//	1,///cant do one has a bug
//	//init random speed extent
//	Play::Vector2f(3.f, 3.f),
//	//init lifetime min and max
//	Play::Vector2f(3.f, 3.f),
//	//init random particle direction of motion range
//	30.0f,
//	//init size range
//	Play::Vector2f(1.0f, 1.0f),
//	//init delay time
//	0.2f,
//	//init gravity & direction
//	1.0f,
//	Play::Vector2f(1.0f, -0.5f),
//	//init three color
//	Play::Colour(255, 0, 0),
//	Play::Colour(0, 255, 0),
//	Play::Colour(0, 0, 255),
//	//init three alpha
//	Play::Vector3D(0.8f, 0.5f, 0.2f),
//	"smoke",
//	//random rotate speed clamp and increment value
//	Play::Vector3D(-3.0f, 3.0f, 0.0f),
//	//size over lifetime 3 stages
//	Play::Vector3D(1.0f, 0.6f, 0.1f)
//);