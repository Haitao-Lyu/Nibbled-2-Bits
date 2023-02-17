#pragma once

#include "../PlayCustom.h"

// enum by default will expose all the value to global --
// can use a namespace to implicit cast into integer
// after c++11 has a new feature call enum class will always cast value into integer.
// always need a name to IntelliCode suggest
enum class E_CULLINGMASK
{
	E_NULL = -1,
	E_DIAMOND,
	E_LINE,
	E_TRIANGLE
};

struct DiamondMask
{
	Play::Point2D top, left, right, bot;

	float sidelength = 100;

	DiamondMask(float _sidelength);


	DiamondMask(Play::Point2D p1, Play::Point2D p2, Play::Point2D p3, Play::Point2D p4);

	void DrawOutline(Play::Colour color = Play::cRed);

	//half - space test
	bool isInSide(Play::Point2D pos);

};

struct LineMask
{
	Play::Point2D start_pos, end_pos;
	Play::Vector2f v;
	Play::Vector2f v_perp_n;
	LineMask(Play::Point2D p1, Play::Point2D p2);

	void DrawOutline(Play::Colour color = Play::cRed);

	bool isOnLine(Play::Point2D pos);

	bool isOnEnd(Play::Point2D pos);

	bool isOnRightSide(Play::Point2D pos);

	float PointDistance(Play::Point2D pos);
};

struct TriangleMask
{
	float theta{ 0 };
	Play::Point2D start_pos;
	Play::Point2D v_b;
	Play::Point2D v_t;
	float size = 300;

	TriangleMask(float _theta, Play::Point2D pos);

	void DrawOutline(Play::Colour color = Play::cRed);
	//half - space test
	bool isInSide(Play::Point2D pos);

};
