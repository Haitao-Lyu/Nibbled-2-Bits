#include "Play.h"
#include "Button.h"

Button::Button()
{

}

Button::Button(int sprite_, Play::Point2D pos_, Play::Vector2D size_)
{
	m_sprite = sprite_;
	m_pos = pos_;
	m_size = size_;
}

// draw/update ===============================================
void Button::Update()
{

}

void Button::Draw()
{
	if (Held()) 
	{
		//Play::ColourSprite(m_sprite.c_str(), Play::Colour(75, 75, 75));
		//Play::DrawSprite(Play::GetSpriteId(sprite.c_str()), pos + Play::Point2D(0, -5), 0);
		DrawSprite(m_pos + Play::Point2D(0, -5));
	}
	else
	{
		//Play::ColourSprite(m_sprite.c_str(), Play::Colour(100, 100, 100));
		//Play::DrawSprite(Play::GetSpriteId(sprite.c_str()), pos, 0);
		DrawSprite(m_pos);
	}
}


// interaction ==================================================
bool Button::Pressed()
{
	Play::Point2D mousePos = Play::GetMousePos();
	if (mousePos.x >= m_pos.x && mousePos.x <= (m_pos.x + m_size.x) && mousePos.y >= m_pos.y && mousePos.y <= (m_pos.y + m_size.y))
	{
		if (Play::KeyPressed(VK_LBUTTON)) {
			return true;
		}
	}
	return false;
}

bool Button::Held() 
{
	Play::Point2D mousePos = Play::GetMousePos();
	if (mousePos.x >= m_pos.x && mousePos.x <= (m_pos.x + m_size.x) && mousePos.y >= m_pos.y && mousePos.y <= (m_pos.y + m_size.y))
	{
		if (Play::KeyDown(VK_LBUTTON)) {
			return true;
		}
	}
	return false;
}

bool Button::Hovering()
{
	Play::Point2D mousePos = Play::GetMousePos();
	if (mousePos.x >= m_pos.x && mousePos.x <= (m_pos.x + m_size.x) && mousePos.y >= m_pos.y && mousePos.y <= (m_pos.y + m_size.y))
	{
		return true;
	}
	return false;
}

// functions ==============================================
void Button::DrawSprite(Play::Point2D position)
{
	int spriteWidth = Play::GetSpriteWidth(m_sprite);
	int spriteHeight = Play::GetSpriteHeight(m_sprite);

	if (spriteHeight == m_size.y && spriteWidth == m_size.x)
	{
		Play::DrawSprite(m_sprite, position + Play::Vector2D(m_size.x / 2, m_size.y / 2), 0);
	}
	// scale sprite if necessary
	else
	{
		Play::DrawSpriteRotated(m_sprite, position + Play::Vector2D(m_size.x/2, m_size.y/2), 0, PLAY_PI / 2, m_size.y / spriteHeight);
	}
}

// get/set =============================================
void Button::SetPos(Play::Point2D pos_)
{
	m_pos = pos_;
}

Play::Vector2D Button::GetSize()
{
	return m_size;
}