#include "pch.h"
#include "UIManager.h"
#include "Button.h"
#include "Slider.h"
#include <string.h>
#include "InputBox.h"
#include "../GameTool/DebugTool.h"
#include "../Particle/ParticleManager.h"

MouseState lyu_mouse;

std::vector<UIElement*> UIManager::UIComponents_List = {};

std::vector<UIElement*>& UIManager::GetUIList()
{
	return UIComponents_List;
}

void UIManager::DisableMouseActionWhenOnUI()
{
	//check UI hover
	int btnCount = 0;
	for (UIElement*& uielement : UIManager::GetUIList())
	{
		if (uielement->OnHover())
		{
			lyu_mouse.isOnUI = true;
			btnCount++;
		}
	}
	if (btnCount == 0)
		lyu_mouse.isOnUI = false;
}

UIManager& UIManager::GetInstance()
{
	static UIManager _instance;
	return _instance;
}

void UIManager::AddNewUIElement(UIElement& component)
{
	UIComponents_List.push_back(&component);
}

void UIManager::DrawUIElements()
{
	for (UIElement*& element : UIComponents_List)
	{
		element->DrawSprite();
	}
}

void UIManager::UIInitialize()
{
	using namespace Play;

	Button* btn_fire = new Button(Point2f(150.f, 100.f), "Button_1", 50, 100, []() {
	lyu_mouse.Current_Particle = ParticleChoice::E_FIRE;
	DebugText("CLick");
		}, "FIRE");

	Button* btn_snow = new Button(Point2f(250.f, 100.f), "Button_1", 50, 100, []() {
	lyu_mouse.Current_Particle = ParticleChoice::E_SONW;
	DebugText("CLick"); },"SNOW");

	Button* btn_water = new Button(Point2f(350.f, 100.f), "Button_1", 50, 100, []() {					
	lyu_mouse.Current_Particle = ParticleChoice::E_Water;
	DebugText("CLick"); }, "WATER");

	Button* btn_fairy = new Button(Point2f(450.f, 100.f), "Button_1", 50, 100, []() {
		lyu_mouse.Current_Particle = ParticleChoice::E_Fairy;
		DebugText("CLick");
		}, "FAIRY");

	Button* btn_Bubble = new Button(Point2f(550.f, 100.f), "Button_1", 50, 100, []() {
		lyu_mouse.Current_Particle = ParticleChoice::E_Bubble;
		DebugText("CLick");
		}, "BUBBLE");

	Button* btn_cloud = new Button(Point2f(650.f, 100.f), "Button_1", 50, 100, []() {
		lyu_mouse.Current_Particle = ParticleChoice::E_Cloud;
		DebugText("CLick");
		},"CLOUD");

	Button* btn_window = new Button(Point2f(750.f, 100.f), "Button_1", 50, 100, []() {
		lyu_mouse.Current_Particle = ParticleChoice::E_Window;
		DebugText("CLick");
		},"WINDOW");

	Button* btn_line = new Button(Point2f(850.f, 100.f), "Button_1", 50, 100, []() {
		lyu_mouse.Current_Particle = ParticleChoice::E_Line;
		DebugText("CLick");
		}, "LINEMASK");

	Button* btn_triangle = new Button(Point2f(950.f, 100.f), "Button_1", 50, 100, []() {
		lyu_mouse.Current_Particle = ParticleChoice::E_Triangle;
		DebugText("CLick");
		},"TRIANGLE");

	Slider* sldier_test  = new Slider({ 1050.f,100.f }, "roundbtn", 50, 50, "sliderbk", 25, 100);
	InputBox* inputBox_test = new InputBox({ 1050.f,200.f }, "sliderbk", 25, 100, "quantites:");

	UIManager::GetInstance().AddNewUIElement(*sldier_test);
	UIManager::GetInstance().AddNewUIElement(*inputBox_test);
	UIManager::GetInstance().AddNewUIElement(*btn_fire);
	UIManager::GetInstance().AddNewUIElement(*btn_snow);
	UIManager::GetInstance().AddNewUIElement(*btn_water);
	UIManager::GetInstance().AddNewUIElement(*btn_fairy);
	UIManager::GetInstance().AddNewUIElement(*btn_Bubble);
	UIManager::GetInstance().AddNewUIElement(*btn_cloud);
	UIManager::GetInstance().AddNewUIElement(*btn_window);
	UIManager::GetInstance().AddNewUIElement(*btn_line);
	UIManager::GetInstance().AddNewUIElement(*btn_triangle);
}

void UIManager::CheckUIEvent()
{
	std::vector<UIElement*> uilist = UIManager::GetUIList();

	DisableMouseActionWhenOnUI();

	//check button click event
	for (UIElement* &uicomponent : uilist)
	{
		uicomponent->OnDrag();
		uicomponent->OnClick();
	}
}

void UIControl()
{
	using namespace Play;
	if (lyu_mouse.isOnUI)
		return;
	if (Play::KeyPressed(VK_LBUTTON))
	{
		Point2f clickPos = Play::GetMousePos();
		ParticleEmitter emitter{};
		switch (lyu_mouse.Current_Particle)
		{
		case ParticleChoice::E_SONW:
			emitter.InitParticleEmitter(
				clickPos,
				//init emitter scale
				Vector2f{ 100.0f, 100.0f },
				//init emitter rotation based on intial direction { 0 , -1 }
				160.0f,
				//init particle num
				20,///cant do one has a bug
				//init random speed extent
				Vector2f(0.5f, 3.5f),
				//init lifetime min and max
				Vector2f(0.3f, 1.8f),
				//init random particle direction of motion range
				180.0f,
				//init size range
				Vector2f(0.2f, 0.6f),
				//init delay time
				0.5f,
				//init gravity & direction
				2.0f,
				Vector2f(1.0f, -0.5f),
				//init three color
				Play::Colour(242, 242, 242),
				Play::Colour(242, 200, 242),
				Play::Colour(200, 242, 242),
				//init three alpha
				Play::Vector3D(0.6f, 0.2f, 0.4f),
				"snow",
				//rotate speed and increment value
				Play::Vector3D(-3.0f, 3.0f, 0.0f),
				Play::Vector3D(1.0f, 1.0f, 1.0f)
			);
			break;
		case ParticleChoice::E_FIRE:
			emitter.InitParticleEmitter(
				//init emitter pos
				clickPos,
				//init emitter scale
				Vector2f{ 10.0f, 10.0f },
				//init emitter rotation based on intial direction { 0 , -1 }
				0.0f,
				//init particle num
				10,///cant do one has a bug
				//init random speed extent
				Vector2f(3.5f, 4.0f),
				//init lifetime min and max
				Vector2f(0.3f, 0.5f),
				//init random particle direction of motion range
				360.0f,
				//init size range
				Vector2f(0.2f, 1.0f),
				//init delay time
				0.2f,
				//init gravity & direction
				5.0f,
				Vector2f(0.0f, 1.0f),
				//init three color
				Play::Colour(235, 128, 0),
				Play::Colour(255, 77, 95),
				Play::Colour(255, 153, 102),
				//init three alpha
				Play::Vector3D(0.8f, 0.4f, 0.2f),
				"flare",
				//rotate speed and increment value
				Play::Vector3D(3.0f, 5.0f, 2.5f),
				Play::Vector3D(1.0f, 1.0f, 1.0f)
				//E_CULLINGMASK::E_LINE
			);
			break;
		case ParticleChoice::E_Water:
			emitter.InitParticleEmitter(
				//init emitter pos
				clickPos,
				//init emitter scale
				Vector2f{ 10.0f, 10.0f },
				//init emitter rotation based on intial direction { 0 , -1 }
				0.0f,
				//init particle num
				8,///cant do one has a bug
				//init random speed extent
				Vector2f(0.5f, 3.5f),
				//init lifetime min and max
				Vector2f(0.3f, 2.8f),
				//init random particle direction of motion range
				360.0f,
				//init size range
				Vector2f(0.1f, 1.0f),
				//init delay time
				0.5f,
				//init gravity & direction
				3.0f,
				Vector2f(0.0f, 1.0f),
				//init three color
				Play::Colour(63, 135, 230),
				Play::Colour(36, 113, 215),
				Play::Colour(112, 163, 229),
				//init three alpha
				Play::Vector3D(0.8f, 0.6f, 0.4f),
				"fluid",
				Play::Vector3D(3.0f, 5.0f, 2.5f),
				Play::Vector3D(1.0f, 1.0f, 1.0f),
				E_CULLINGMASK::E_NULL
			);
			break;
		case ParticleChoice::E_Fairy:
			//emitter_electric
			emitter.InitParticleEmitter(
				//init emitter pos
				clickPos,
				//init emitter scale
				Vector2f{ 100.0f, 100.0f },
				//init emitter rotation based on intial direction { 0 , -1 }
				300.0f,
				//init particle num
				10,///cant do one has a bug
				//init random speed extent
				Vector2f(0.5f, 3.5f),
				//init lifetime min and max
				Vector2f(0.3f, 1.8f),
				//init random particle direction of motion range
				30.0f,
				//init size range
				Vector2f(0.2f, 0.6f),
				//init delay time
				0.1f,
				//init gravity & direction
				2.0f,
				Vector2f(1.0f, -0.5f),
				//init three color
				Play::Colour(213, 255, 112),
				Play::Colour(189, 255, 102),
				Play::Colour(255, 255, 102),
				//init three alpha
				Play::Vector3D(0.8f, 0.2f, 0.0f),
				"flare",
				Play::Vector3D(3.0f, 5.0f, 2.5f),
				Play::Vector3D(1.0f, 1.0f, 1.0f)

			);
			break;
		case ParticleChoice::E_Bubble:
			emitter.InitParticleEmitter(
				//init emitter pos
				clickPos,
				//init emitter scale
				Vector2f{ 10.0f, 10.0f },
				//init emitter rotation based on intial direction { 0 , -1 }
				300.0f,
				//init particle num
				20,///cant do one has a bug
				//init random speed extent
				Vector2f(3.5f, 4.5f),
				//init lifetime min and max
				Vector2f(0.2f, 1.5f),
				//init random particle direction of motion range
				20.0f,
				//init size range
				Vector2f(0.2f, 0.6f),
				//init delay time
				0.2f,
				//init gravity & direction
				3.5f,
				Vector2f(1.0f, -0.6f),
				//init three color
				Play::Colour(172, 123, 246),
				Play::Colour(131, 255, 255),
				Play::Colour(131, 255, 210),
				//init three alpha
				Play::Vector3D(0.6f, 0.05f, 0.15f),
				"ring",
				//init rot
				Play::Vector3D(1.0f, 5.0f, 0.0f),
				Play::Vector3D(1.0f, 1.0f, 1.0f)

			);
			break;
		case ParticleChoice::E_Cloud:
			emitter.InitParticleEmitter(
				//init emitter pos
				clickPos,
				//init emitter scale
				Vector2f{ 500.0f, 500.0f },
				//init emitter rotation based on intial direction { 0 , -1 }
				0.0f,
				//init particle num
				10,///cant do one has a bug
				//init random speed extent
				Vector2f(0.2f, 0.5f),
				//init lifetime min and max
				Vector2f(5.3f, 8.0f),
				//init random particle direction of motion range
				360.0f,
				//init size range
				Vector2f(5.0f, 10.0f),
				//init delay time
				1.0f,
				//init gravity & direction
				2.0f,
				Vector2f(1.0f, 0.0f),
				//init three color
				Play::Colour(255, 255, 255),
				Play::Colour(240, 250, 235),
				Play::Colour(220, 250, 255),
				//init three alpha
				Play::Vector3D(0.1f, 0.1f, 0.1f),
				"cloud"
				//rotate speed and increment value
				//Play::Vector3D(-1.0f, 1.0f, 0.0f)
			);
			break;
		case ParticleChoice::E_Window:
			emitter.InitParticleEmitter(
				//init emitter pos
				clickPos,
				//init emitter scale
				Vector2f{ 100.0f, 200.0f },
				//init emitter rotation based on intial direction { 0 , -1 }
				0.0f,
				//init particle num
				40,///cant do one has a bug
				//init random speed extent
				Vector2f(0.4f, 0.7f),
				//init lifetime min and max
				Vector2f(5.3f, 8.0f),
				//init random particle direction of motion range
				360.0f,
				//init size range
				Vector2f(0.3f, 0.5f),
				//init delay time
				1.0f,
				//init gravity & direction
				0.0f,
				Vector2f(1.0f, 0.0f),
				//init three color
				Play::Colour(255, 255, 255),
				Play::Colour(240, 250, 235),
				Play::Colour(220, 250, 255),
				//init three alpha
				Play::Vector3D(0.5f, 0.5f, 0.5f),
				"flare",
				//rotate speed and increment value
				Play::Vector3D(0.0f, 0.0f, 0.0f),
				Play::Vector3D(1.0f, 1.0f, 1.0f),
				E_CULLINGMASK::E_DIAMOND
			);
			break;
		case ParticleChoice::E_Line:
			emitter.InitParticleEmitter(
				//init emitter pos
				clickPos,
				//init emitter scale
				Vector2f{ 100.0f, 100.0f },
				//init emitter rotation based on intial direction { 0 , -1 }
				0.0f,
				//init particle num
				10,///cant do one has a bug
				//init random speed extent
				Vector2f(1.5f, 2.0f),
				//init lifetime min and max
				Vector2f(1.3f, 2.5f),
				//init random particle direction of motion range
				120.0f,
				//init size range
				Vector2f(0.3f, 0.3f),
				//init delay time
				0.4f,
				//init gravity accelerate & direction
				0.2f,
				Vector2f(0.0f, 0.0f),
				//init three color
				Play::Colour(255, 255, 255),
				Play::Colour(240, 250, 235),
				Play::Colour(220, 250, 255),
				//init three alpha
				Play::Vector3D(0.6f, 0.6f, 0.6f),
				"flare",
				//rotate speed and increment value
				Play::Vector3D(0.0f, 0.0f, 0.0f),
				Play::Vector3D(1.0f, 1.0f, 1.0f),
				E_CULLINGMASK::E_LINE
			);
			break;
		case ParticleChoice::E_Triangle:
			emitter.InitParticleEmitter(
				//init emitter pos
				clickPos,
				//init emitter scale
				Vector2f{ 100.0f, 100.0f },
				//init emitter rotation based on intial direction { 0 , -1 }
				0.0f,
				//init particle num
				50,///cant do one has a bug
				//init random speed extent
				Vector2f(1.4f, 2.7f),
				//init lifetime min and max
				Vector2f(5.3f, 8.0f),
				//init random particle direction of motion range
				360.0f,
				//init size range
				Vector2f(0.3f, 0.5f),
				//init delay time
				0.3f,
				//init gravity & direction
				0.0f,
				Vector2f(0.0f, 0.0f),
				//init three color
				Play::Colour(255, 255, 255),
				Play::Colour(240, 250, 235),
				Play::Colour(220, 250, 255),
				//init three alpha
				Play::Vector3D(0.5f, 0.5f, 0.5f),
				"flare",
				//rotate speed and increment value
				Play::Vector3D(0.0f, 0.0f, 0.0f),
				Play::Vector3D(1.0f, 1.0f, 1.0f),
				E_CULLINGMASK::E_TRIANGLE
			);
			break;
		default:
			return;
		}
		//Event c = Event([emitter]() { ParticleMgr::GetInstance().AddNewEmitter(emitter); });
		//EventCenter::PostEvent("LeftMouseClicked", c);

		//Event d = Event([emitter]() { DebugText("event2 triggered"); });
		//EventCenter::PostEvent("LeftMouseClicked2", d);
		////ParticleMgr::GetInstance().AddNewEmitter(emitter);
	}
}