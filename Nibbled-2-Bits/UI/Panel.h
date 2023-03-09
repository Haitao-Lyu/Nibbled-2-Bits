#pragma once
#include "../PlayCustom.h"
#include <vector>
#include "UIElement.h"
#include "Component/GridComponent.h"


class Panel:public UIElement
{
private:

	//TODO: All elements in a panel should scale by the scale of panel
	// So Panel should have a children list of all elements
	float x_scale = 1.0f;
	float y_scale = 1.0f;

public:
	std::map<const char*,UIElement*> childUIMap;
	GridComponent gridComponent;//component should always be public
	Play::Point2D m_lt_pos;
	Play::Point2D m_rt_pos;
	Play::Point2D m_rb_pos;
	Play::Point2D m_lb_pos;

public:
	Panel(Play::Point2D pos, float height , float width, const char* spriteName = "");
	~Panel();
	void SetScale(float x, float y);
	void SetSpriteScale(float x, float y);
	void Update() override;
	void Render() override;

	void SetVisibility(bool value);
	void SetActive(bool value);
	void AddToPanel(const char* name, UIElement* UIelement);
	void Clear();
};
