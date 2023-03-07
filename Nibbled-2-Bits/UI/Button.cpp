#include "pch.h"
#include "Button.h"
#include "../GameTool/DebugTool.h"
#include "UIManager.h"
#include "../MainGame.h"
#include "../Manager/ResourceMgr.h"
Button::Button() :UIElement(Play::Point2D(0, 0), 0, 0)
{
	
}

Button::Button(float x, float y, short height, short width, const char* spriteName, FunctionType OnClickHandler, const char* btnName):UIElement(Play::Point2D(x, y), height, width)
{
	m_spriteName = spriteName;
	m_btnText = btnName;
	m_OnClickHandler = OnClickHandler;
}

Button::Button(Play::Point2f pos,  short height, short width,  const char* spriteName, FunctionType OnClickHandler, const char* btnName):UIElement(pos.x,pos.y, height, width)
{
	m_spriteName = spriteName;
	m_btnText = btnName;
	m_OnClickHandler = OnClickHandler;
}

void Button::SetSpriteName(const char* name)
{
	m_spriteName = name;
}

void Button::Render()
{
	//Scale from the defined height and width
	if (std::strcmp(m_spriteName, "") != 0)
		m_scale = static_cast<float>(m_height) / Play::GetSpriteHeight(m_spriteName);

	Play::Matrix2D rotMt = Play::MatrixRotation(Play::DegToRad(m_rot));

	const Play::Matrix2D scaleMt = Play::Matrix2D(
		{ m_scale,0.0f,0.0f },
		{ 0.0f,m_scale,0.0f },
		{ m_pos.x,DISPLAY_HEIGHT - m_pos.y,0.0f });
	Play::DrawSpriteTransformed(Play::GetSpriteId(m_spriteName), scaleMt * rotMt, 0);
	//btn text show
	Play::DrawFontText(ResoureMgr::GetFontName(E_FONTS::ABNORMAL_40), m_btnText, m_pos, Play::Align::CENTRE);
	//DEBUG UI
	//DrawBoundingBox();
}

bool Button::OnDrag()
{
	if (!isActive)
		return false;
	return UIElement::OnDrag();
}

bool Button::OnHover()
{
	if (!isActive)
		return false;
	return UIElement::OnHover();
}
bool Button::OnClick()
{
	if (!isActive)
 		return false;

	if (UIElement::OnClick())
	{
		m_OnClickHandler();
		return true;
	}
	return false;
}

void Button::AddOnClickHandler(FunctionType fun)
{
	m_OnClickHandler = fun;
}


