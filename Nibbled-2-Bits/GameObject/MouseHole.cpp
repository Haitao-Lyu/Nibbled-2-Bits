#include "pch.h"
#include "MouseHole.h"

const char* mouseHoleName_b = "mouse_hole_bottom";
const char* mouseHoleName_l = "mouse_hole_left";
const char* mouseHoleName_r = "mouse_hole_right";
const char* mouseHoleName_t = "mouse_hole_top";

MouseHole::MouseHole(Play::Point2D pos):Obstacle(pos,E_OBJTYPE::E_MOUSEHOLE)
{
	spriteName = mouseHoleName_t;
	m_circleCollider.Init(pos, Play::GetSpriteHeight(spriteName) / 2 * m_scale);
}

MouseHole::~MouseHole()
{

}
