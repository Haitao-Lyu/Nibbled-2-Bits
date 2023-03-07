#include "pch.h"
#include "TextField.h"
#include "../Manager/ResourceMgr.h"
TextField::TextField():UIElement({ 0,0 }, 0, 0)
{

}

TextField::TextField(Play::Point2f pos, short height, short width, const char* text, const char* spriteName /*= ""*/) :UIElement(pos, height, width)
{
	m_text = text;
	m_spriteName = spriteName;
}

void TextField::Render()
{
	UIElement::Render();
	Play::DrawFontText(ResoureMgr::GetFontName(E_FONTS::BOLD_64), m_text, m_pos, Play::CENTRE);
	DrawBoundingBox();
}

void TextField::SetText(const char* text)
{
	m_text = text;
}
