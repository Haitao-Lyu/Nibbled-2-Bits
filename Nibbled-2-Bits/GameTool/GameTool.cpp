#include "GameTool.h"

using namespace Play;
//void GameTool::SetMoveTowards(GameObject& origin, GameObject& Target)
//{
//	Vector2D dir = Target.pos - origin.pos;
//	dir.Normalize();
//	//set velocity
//	origin.velocity = dir;
//}
//
//void GameTool::SetMoveTowards(GameObject& origin, Point2D Target)
//{
//	Vector2D dir = Target - origin.pos;
//	dir.Normalize();
//	//set velocity
//	origin.velocity = dir;
//}

void GameTool::myDrawRect(Point2D center, float length, Play::Colour color)
{
	Point2D lt = Point2D{ center.x - length / 2,center.y - length / 2 };
	Point2D rb = Point2D{ center.x + length / 2,center.y + length / 2 };
	Play::DrawRect(lt, rb, color, true);
}


void GameTool::CameraFocus(Point2D pos)
{
	Point2D camPos = { pos.x - DISPLAY_WIDTH / 2,pos.y - DISPLAY_HEIGHT / 2 };
	Play::SetCameraPosition(camPos);
}

Point2D GameTool::MouseToWorldPos(Point2D camNowPos,Point2D MousePos)
{
	Point2D offset = camNowPos - CamStartPos;
	return MousePos + offset;
}

