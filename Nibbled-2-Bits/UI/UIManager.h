#pragma once
#include "UIElement.h"
#include <vector>

enum class ParticleChoice
{
	E_NULL,
	E_FIRE,
	E_Water,
	E_Fairy,
	E_Bubble,
	E_SONW,
	E_Cloud,
	E_Window,
	E_Line,
	E_Triangle,
};

struct MouseState
{
	bool isOnUI = false;
	ParticleChoice Current_Particle = ParticleChoice::E_SONW;
};

class UIManager
{
private:
	//vector can only hold same size in consistent
	//static related to class not entity
	static std::vector<UIElement*> UIComponents_List;//base class must be pointer or reference
private:
	UIManager() {}

	UIManager(const UIManager& instance) = delete;

	UIManager& operator=(UIManager& instance) = delete;	

	void DisableMouseActionWhenOnUI();
public:
	static UIManager& GetInstance();

	static std::vector<UIElement*>& GetUIList();

	void AddNewUIElement(UIElement& component);

	void UIInitialize();

	void DrawUIElements();

	void CheckUIEvent();
};

