#include "pch.h"
#include "BoxCollider.h"

BoxCollider::BoxCollider()
{
}

BoxCollider::BoxCollider(float width, float height, Play::Point2D pos, GameObject* info) : Collider(pos), m_width(width), m_height(height)
{
	lt = { m_pos.x - m_width / 2,m_pos.y - m_height / 2 };
	lb = { m_pos.x - m_width / 2,m_pos.y + m_height / 2 };
	rt = { m_pos.x + m_width / 2,m_pos.y - m_height / 2 };
	rb = { m_pos.x + m_width / 2,m_pos.y + m_height / 2 };
	m_holderInfo = info;
}

void BoxCollider::Init(float width, float height, Play::Point2D pos, GameObject* info)
{
	m_width = width;
	m_height = height;
	m_pos = pos;
	lt = { m_pos.x - m_width / 2,m_pos.y - m_height / 2 };
	lb = { m_pos.x - m_width / 2,m_pos.y + m_height / 2 };
	rt = { m_pos.x + m_width / 2,m_pos.y - m_height / 2 };
	rb = { m_pos.x + m_width / 2,m_pos.y + m_height / 2 };
	m_holderInfo = info;
}

void BoxCollider::UpdateShape(float width, float height, Play::Point2D pos)
{
	m_width = width;
	m_height = height;
	m_pos = pos;
	lt = { m_pos.x - m_width / 2,m_pos.y - m_height / 2 };
	lb = { m_pos.x - m_width / 2,m_pos.y + m_height / 2 };
	rt = { m_pos.x + m_width / 2,m_pos.y - m_height / 2 };
	rb = { m_pos.x + m_width / 2,m_pos.y + m_height / 2 };
}

bool BoxCollider::collidesWith(Collider& other)
{
	// Check collision with another box collider
	if (BoxCollider* otherBox = dynamic_cast<BoxCollider*>(&other))
	{
		//      float dis = (otherBox->GetPos() - m_pos).Length();
		//      float dis1 = otherBox->GetHeight() * otherBox->GetHeight() + m_width * m_width;
		//      float dis2 = otherBox->GetWidth() * otherBox->GetWidth() + m_height * m_height;
			  //float dis3 = otherBox->GetHeight() * otherBox->GetHeight() + m_height * m_height;
			  //float dis4 = otherBox->GetWidth() * otherBox->GetWidth() + m_width * m_width;
		//      float maxDis = std::max(dis1, dis2);
		//      maxDis = std::max(maxDis, dis3);
		//      maxDis = std::max(maxDis, dis4);
		//      if (dis < std::sqrt(maxDis))
		//      {
		//          return true;
		//      }
		if (otherBox->lt.x > lt.x && otherBox->lt.x < rb.x && otherBox->lt.y > lt.y && otherBox->lt.y < rb.y)
		{
			// m_opponentInfo = otherBox->m_holderInfo;
			return true;
		}
		else if (otherBox->rt.x > lt.x && otherBox->rt.x < rb.x && otherBox->rt.y > lt.y && otherBox->rt.y < rb.y)
		{
			//m_opponentInfo = otherBox->m_holderInfo;
			return true;
		}
		else if (otherBox->lb.x > lt.x && otherBox->lb.x < rb.x && otherBox->lb.y > lt.y && otherBox->lb.y < rb.y)
		{
			//m_opponentInfo = otherBox->m_holderInfo;
			return true;
		}
		else if (otherBox->rb.x > lt.x && otherBox->rb.x < rb.x && otherBox->rb.y > lt.y && otherBox->rb.y < rb.y)
		{
			//m_opponentInfo = otherBox->m_holderInfo;
			return true;
		}
		///check if this box point is in the other box
		else if (lt.x > otherBox->lt.x && lt.x < otherBox->rb.x && lt.y > otherBox->lt.y && lt.y < otherBox->rb.y)
		{
			// m_opponentInfo = otherBox->m_holderInfo;
			return true;
		}
		else if (rt.x > otherBox->lt.x && rt.x < otherBox->rb.x && rt.y > otherBox->lt.y && rt.y < otherBox->rb.y)
		{
			//m_opponentInfo = otherBox->m_holderInfo;
			return true;
		}
		else if (lb.x > otherBox->lt.x && lb.x < otherBox->rb.x && lb.y > otherBox->lt.y && lb.y < otherBox->rb.y)
		{
			//m_opponentInfo = otherBox->m_holderInfo;
			return true;
		}
		else if (rb.x > otherBox->lt.x && rb.x < otherBox->rb.x && rb.y > otherBox->lt.y && rb.y < otherBox->rb.y)
		{
			//m_opponentInfo = otherBox->m_holderInfo;
			return true;
		}
		else
			// m_opponentInfo = nullptr;
			return false;
	}
	// Check collision with other types of colliders (e.g. circle collider)
	else
	{
		// TODO: implement collision detection with other collider types
		return false;
	}
}

void BoxCollider::DrawBoundingBox(Play::Colour color )
{
	Play::DrawRect(lt, rb, color);
	Play::DrawDebugText(m_pos, std::to_string(m_id).c_str(), color);
}

void BoxCollider::OnCollision(std::function<void()> fun)
{
	if (m_opponentInfo != nullptr)
	{
		fun();
	}
}

float BoxCollider::GetWidth()
{
	return m_width;
}

float BoxCollider::GetHeight()
{
	return m_height;
}

Play::Point2D BoxCollider::GetPos()
{
	return m_pos;
}

