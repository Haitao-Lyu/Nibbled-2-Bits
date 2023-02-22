#pragma once
class Timer
{
private:
	float m_timeCounter = 0;
	float m_timeInterval = 0;
public:
	Timer() {};
	/*Set Interval*/
	Timer(float interval) : m_timeInterval(interval) {}
	void SetInterval(float interval);
	/*Return true when meet time interval*/
	bool isReachTimeInterval();
	/*Restart the timer*/
	void Restart();
	/*Put in main update to set delta time*/
	static void UpdateDeltaTime(float elapsedTime);
	/*Get delta time*/
	static float DeltaTime();
};


