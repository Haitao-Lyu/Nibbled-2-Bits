#pragma once
#include "../PlayCustom.h"
#include <vector>
#include "UIElement.h"
#include "Component/GridComponent.h"


class Panel:public UIElement
{
private:

	Play::Point2D m_lt_pos;
	Play::Point2D m_rt_pos;
	Play::Point2D m_rb_pos;
	Play::Point2D m_lb_pos;
	//TODO: All elements in a panel should scale by the scale of panel
	float x_scale = 1.0f;
	float y_scale = 1.0f;

public:
	GridComponent gridComponent;//component should always be public

	Panel(Play::Point2D pos, short height , short width, const char* spriteName = "");
	~Panel();

	void Update() override;
	void Render() override;
};
