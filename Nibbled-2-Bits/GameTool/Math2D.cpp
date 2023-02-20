#include "pch.h"
#include "Math2D.h"
#include "Timer.h"
using namespace std;

float GetRandomFloat(float a, float b)
{
	return ((b - a) * ((float)rand() / RAND_MAX)) + a;
}

//inline Play::Vector2f perpendicular(const Play::Vector2f& rhs)
//{
//	//vector 2 perpendicular -> (y, -x)
//	Play::Vector2f ret;
//	ret.v[0] = -rhs.v[1];
//	ret.v[1] = rhs.v[0];
//	return ret;
//}

Play::Colour interpolate(Play::Colour c_start, Play::Colour c_end, float startTime, float endTime, float currentTime)
{
	float r = interpolate(c_start.red, c_end.red, startTime, endTime, currentTime);
	float g = interpolate(c_start.green, c_end.green, startTime, endTime, currentTime);
	float b = interpolate(c_start.blue, c_end.blue, startTime, endTime, currentTime);
	return Play::Colour(r,g,b);
}

float interpolate(float startValue, float endValue, float startTime, float endTime, float currentTime) {
	// Calculate the time interval between the start and end times
	float timeInterval = endTime - startTime;

	// Calculate the value interval between the start and end values
	float valueInterval = endValue - startValue;

	// Calculate the fraction of time that has elapsed
	float timeFraction = (currentTime - startTime) / timeInterval;

	// Calculate the interpolated value
	float interpolatedValue = startValue + (valueInterval * timeFraction);

	// Return the interpolated value
	return interpolatedValue;
}


void rotateClockwise(std::vector<std::vector<GameAreaObject*>>& arr) {

	int n = arr.size();
	int m = arr[0].size();
	std::vector<std::vector<GameAreaObject*>> rotated(m, std::vector<GameAreaObject* >(n));

	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++) {
			rotated[i][j] = arr[n - j - 1][i];
		}
	}

	arr = rotated;
}
