#pragma once
#include "../PlayCustom.h"
//多文件编写的默认参数只需要出现在声明不需要出现在定义的当中
namespace GameTool
{
	//void SetMoveTowards(GameObject& origin, GameObject& Target);

	//void SetMoveTowards(GameObject& origin, Point2D Target);

	void myDrawRect(Play::Point2D center, float length, Play::Colour color = Play::cGreen);

	void CameraFocus(Play::Point2D pos);

	Play::Point2D MouseToWorldPos(Play::Point2D camNowPos, Play::Point2D MousePos);
}




