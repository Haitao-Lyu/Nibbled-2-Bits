#include "pch.h"
#include "Timer.h"

static float deltaTime;

void Timer::SetInterval(float interval)
{
	m_timeInterval = interval;
}

bool Timer::isReachTimeInterval()
{
	m_timeCounter += deltaTime;
	if (m_timeCounter >= m_timeInterval)
	{
		m_timeCounter = 0;
		return true;
	}
	else
		return false;
}

void Timer::Restart()
{
	m_timeCounter = 0;
}

void Timer::UpdateDeltaTime(float elaspedTime)
{
	deltaTime = elaspedTime;
}


float Timer::DeltaTime()
{
	return deltaTime;
}