#include "pch.h"
#include "ParticleCullingMask.h"

DiamondMask::DiamondMask(float _sidelength) : sidelength(_sidelength)
{
}

DiamondMask::DiamondMask(Play::Point2D p1, Play::Point2D p2, Play::Point2D p3, Play::Point2D p4) : top(p1), left(p2), right(p3), bot(p4)
{
}

void DiamondMask::DrawOutline(Play::Colour color)
{
	Play::DrawLine(top, left, color);
	Play::DrawLine(left, bot, color);
	Play::DrawLine(bot, right, color);
	Play::DrawLine(right, top, color);
}

bool DiamondMask::isInSide(Play::Point2D pos)
{
	using namespace Play;
	Vector2f v_lt = top - left;
	Vector2f v_rt = top - right;
	Vector2f v_rb = bot - right;
	Vector2f v_lb = bot - left;
	Vector2f v_lt_p = perpendicular(v_lt);
	Vector2f v_lb_p = perpendicular(v_lb);
	Vector2f v_rt_p = perpendicular(v_rt);
	Vector2f v_rb_p = perpendicular(v_rb);
	Vector2f vr = pos - right;
	Vector2f vl = pos - left;
	if (dot(vl, v_lt_p) > 0 && dot(vl, v_lb_p) < 0)
	{
		if (dot(vr, v_rb_p) > 0 && dot(vr, v_rt_p) < 0)
		{
			return true;
		}
	}
	return false;
}

LineMask::LineMask(Play::Point2D p1, Play::Point2D p2) :start_pos(p1), end_pos(p2)
{
	v = p2 - p1;
	v_perp_n = perpendicular(v);
	v_perp_n = normalize(v_perp_n);
}

void LineMask::DrawOutline(Play::Colour color)
{
	Play::DrawLine(start_pos, end_pos, color);
}

bool LineMask::isOnLine(Play::Point2D pos)
{
	Play::Vector2f v_start = pos - start_pos;
	Play::Vector2f v_start_n = normalize(v_start);
	Play::Vector2f v_n = normalize(v);
	float d = dot(v_start_n, v_n);
	if (d == 1 || d == -1)
	{
		return true;
	}
	return false;
}

bool LineMask::isOnEnd(Play::Point2D pos)
{
	Play::Vector2f temp = pos - start_pos;

	return length(temp) > length(v);
}

bool LineMask::isOnRightSide(Play::Point2D pos)
{
	Play::Vector2f vp = perpendicular(v);
	Play::Vector2f v_start = pos - start_pos;
	if (dot(v_start, vp) > 0)
	{
		return true;
	}
	else
		return false;
}

float LineMask::PointDistance(Play::Point2D pos)
{
	Play::Vector2f vp = pos - start_pos;
	Play::Vector2f np = normalize(perpendicular(v));
	return dot(vp, np);
}

TriangleMask::TriangleMask(float _theta, Play::Point2D pos) :theta(Play::DegToRad(_theta)), start_pos(pos)
{
	v_b = Play::Point2D{ start_pos.x + size * cos(theta), start_pos.y };
	v_t = Play::Point2D{ start_pos.x + size * cos(theta),  start_pos.y - size * sin(theta) };
}

void TriangleMask::DrawOutline(Play::Colour color)
{
	Play::DrawLine(start_pos, v_t, color);
	Play::DrawLine(start_pos, v_b, color);
	Play::DrawLine(v_t, v_b, color);
}

bool TriangleMask::isInSide(Play::Point2D pos)
{
	using namespace Play;
	Vector2f v_bt = v_b - start_pos;
	Vector2f v_tp = v_t - start_pos;
	Vector2f v_op = v_t - v_b;
	Vector2f v_bt_p = perpendicular(v_bt);
	Vector2f v_tb_p = perpendicular(v_tp);
	Vector2f v_op_p = perpendicular(v_op);
	Vector2f vl = pos - start_pos;
	Vector2f vr = pos - v_b;
	if (dot(vl, v_tb_p) > 0 && dot(vl, v_bt_p) < 0)
	{
		if (dot(vr, v_op_p) < 0)
		{
			return true;
		}
	}
	return false;
}

