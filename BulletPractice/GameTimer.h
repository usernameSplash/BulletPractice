#pragma once
#include <Windows.h>

class GameTimer
{
public:
	GameTimer();
	GameTimer(GameTimer&) = default;
	~GameTimer() = default;

	float TotalTime()const;
	float DeltaTime()const;

	void Reset();
	void Start();
	void Stop();
	void Tick();
private:
	double m_SecondsPerCount;
	double m_DeltaTime;

	INT64 m_BaseTime;
	INT64 m_PausedTime;
	INT64 m_StopTime;
	INT64 m_PrevTime;
	INT64 m_CurTime;

	bool m_Stopped;
};