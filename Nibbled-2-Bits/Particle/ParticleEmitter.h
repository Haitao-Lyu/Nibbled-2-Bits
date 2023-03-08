#pragma once
#include "Particle.h"
#include "ParticleCullingMask.h"
#define P_DEBUG

class ParticleEmitter
{
private:
	std::vector<Particle> particle_list;
	std::string spriteName= { "circle" };
	Play::Vector3D p_rot_range{ 0.0f,0.0f,0.0f };//rot degree
	Play::Vector3D p_alpha_range{ 1.0f,0.6f,0.2f };
	Play::Vector3D p_size_lifeTime{ 1.0f, 1.0f, 1.0f };
	Play::Colour start_color{ 255,0,0 };
	Play::Colour end_color{ 0,0,255 };
	Play::Colour midway_color{ 0,255,0 };
	Play::Vector2f scale{ 10.0f, 10.0f };
	Play::Vector2f p_speedRange{ 0.1f, 2.0f };//min & max
	Play::Vector2f p_lifeTimeRange{ 0.0f, 0.0f };//min & max
	Play::Vector2f p_dirRange{ 0.0f, 0.0f }; // will generate from p_randomDirRange
	Play::Vector2f p_sizeRange{ 0.0f,1.0f };
	Play::Vector2f p_gravity_direction{ 0.0f,1.0f };
	Play::Point2f pos{ 0.0f, 0.0f };
	float p_gravity_acceleration{ 0.0f };
	float rot{ 0.0f };
	float p_randomDirRange = 0.0f;
	float spwanDelay = 1.0f;
	float timeCounter = 0.0f;
	float blendMode = 0;
	float velocity_decay = 0.6f;
	int quantities = 10;
	bool isShowDebugLine = false;
	bool islooping = false;
	bool isPlaying = true;
	E_CULLINGMASK e_cullingshape = E_CULLINGMASK::E_NULL;
	std::vector<const char* > randomImgList{};
public:
	ParticleEmitter()
	{
		InitParticleEmitter();
	}
	// -- Called first-- //
	void InitParticleEmitter(
		Play::Point2f pos = Play::Point2f(100.0f, 100.0f),
		//init emitter scale
		Play::Vector2f scale = Play::Vector2f{ 10.0f, 10.0f },
		//init emitter rotation based on intial direction { 0 , -1 }
		float rot = 0.0f,
		//init particle num
		int quantities = 5,///cant do one has a bug
		//init random speed extent
		Play::Vector2f p_speedRange = Play::Vector2f(1.0f, 1.5f),
		//init lifetime min and max
		Play::Vector2f p_lifeTimeRange = Play::Vector2f(1.0f, 3.2f),
		//init random particle direction of motion range
		float p_randomDirRange = 30.0f,
		//init size range
		Play::Vector2f p_sizeRange = Play::Vector2f(0.5f, 1.5f),
		//init delay time
		float spwanDelay = 0.1f,
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
		E_CULLINGMASK culling = E_CULLINGMASK::E_NULL
	);
	// -- Called in Generate Particle-- //
	void InitParticles();
	// -- Called in UpdateEmitter -- //
	void GenerateParticles();
	// -- Called in Update Emitter List-- //
	void UpdateEmitter();

	void SetPosition(Play::Point2D _pos);

	void DrawParticleCenter();

	void DrawDebugLine(bool isDebugging);

	bool isEndPlaying();

	void SetLooping(bool bl);

	void SetPlaying(bool bl);

	void SetSpriteName(const char* name);

	void SetRandomImage(std::vector<const char* > list);

};

extern std::vector<ParticleEmitter> g_emitter_list;


