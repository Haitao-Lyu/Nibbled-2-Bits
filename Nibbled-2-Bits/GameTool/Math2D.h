#pragma once
#include "../PlayCustom.h"

float GetRandomFloat(float a, float b);

//// Converts radians to degrees
//constexpr float RadToDeg(float radians) { return (radians / PLAY_PI) * 180.0f; }
//// Converts radians to degrees
//constexpr float DegToRad(float degrees) { return (degrees / 180.0f) * PLAY_PI; }
//
//inline Play::Vector2f perpendicular(const Play::Vector2f& rhs);

enum class InterpMode
{
	INTERP_LINEAR = 0,
	INTERP_EASE_IN,
	INTERP_EASE_OUT,
	INTERP_EASE_INOUT,
	INTERP_PROPORTIONAL,
	INTERP_SPRING,
	MAX_INTERPS
};

Play::Colour interpolate(Play::Colour c_start, Play::Colour c_end, float startTime, float endTime, float currentTime);

float interpolate(float startValue, float endValue, float startTime, float endTime, float currentTime);

