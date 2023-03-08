#include "pch.h"
#include "MainMenuState.h"
#include "MainGameState.h"
#include "../UI/Button.h"
#include "../MainGame.h"
#include "../GameTool/Timer.h"
#include "../Manager/ResourceMgr.h"
#include "../Particle/ParticleManager.h"


static const char* cz_01 = "cz_brie";
static const char* cz_02 = "cz_camembert";
static const char* cz_03 = "cz_cheddar";
static const char* cz_04 = "cz_edam";
static const char* cz_05 = "cz_emmental";
static const char* cz_06 = "cz_gorgonzola";
static const char* cz_07 = "cz_Manchego";
static const char* cz_08 = "cz_mozzarella";
static const char* cz_09 = "cz_parmesan";
static const char* cz_010 = "cz_provolone";
static const char* cz_011 = "cz_ricotta";
static const char* cz_012 = "cz_sandwich";
static const char* cz_013 = "cz_smoked";
static const char* cz_014 = "cz_stilton";
static const char* cz_015 = "cz_swiss";
static const char* cz_016 = "cz_wensleydale";
static std::vector<const char* > chesse_list{ cz_01,cz_02,cz_03,cz_04,cz_05,cz_06,cz_07,cz_08,cz_09,cz_010,cz_011,cz_012,cz_013,cz_014,cz_015,cz_016 };

MainMenuState::MainMenuState()
{

}

MainMenuState::~MainMenuState()
{

}

void MainMenuState::OnEnter()
{
	using namespace Play;
	ParticleEmitter* emitter = ParticleMgr::GetInstance().CreateNewEmitter(
		{ DISPLAY_WIDTH / 2,0 },
		//init emitter scale
		Vector2f{ DISPLAY_WIDTH, 100.0f },
		//init emitter rotation based on intial direction { 0 , -1 }
		120.0f,
		//init particle num
		10,///cant do one has a bug
		//init random speed extent
		Vector2f(1.5f, 3.5f),
		//init lifetime min and max
		Vector2f(2.3f, 3.2f),
		//init random particle direction of motion range
		180.0f,
		//init size range
		Vector2f(0.2f, 1.0f),
		//init delay time
		0.2f,
		//init gravity & direction
		5.0f,
		Vector2f(0.0f, 1.0f),
		//init three color
		Play::Colour(242, 242, 242),
		Play::Colour(242, 200, 242),
		Play::Colour(200, 242, 242),
		//init three alpha
		Play::Vector3D(0.6f, 0.2f, 0.4f),
		"smoke",
		//rotate speed and increment value
		Play::Vector3D(-3.0f, 3.0f, 0.0f),
		//size life time
		Play::Vector3D(1.0f, 1.0f, 1.0f)
	);
	emitter->SetLooping(true);
	emitter->SetRandomImage(chesse_list);
}


GameFlowState* MainMenuState::OnUpdate()
{
	//Update Will Only Draw the UI OnPanel
	Play::DrawFontText(ResoureMgr::GetFontName(E_FONTS::ABNORMAL_40), "@Power - by - Haita0:)", { DISPLAY_HEIGHT / 3,DISPLAY_WIDTH / 2 }, Play::CENTRE);
	Play::DrawFontText("RubikIso-Regular126px_10x10", "Nibbled - 2 - Bits", { DISPLAY_WIDTH / 2 ,DISPLAY_HEIGHT / 4 }, Play::CENTRE);

	ParticleMgr::GetInstance().UpdateEmitterList();

	if (Play::KeyPressed(VK_SPACE))
	{
		return new MainGameState();
	}
	return nullptr;
}


void MainMenuState::OnExit()
{
	if(!MainMenuPanel)
	delete MainMenuPanel;
	ParticleMgr::GetInstance().ClearEmitter();
}
