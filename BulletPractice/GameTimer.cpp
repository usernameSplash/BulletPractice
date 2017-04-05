#include "GameTimer.h"

GameTimer::GameTimer():
	m_SecondsPerCount(0.0),
	m_DeltaTime(-1.0),
	m_BaseTime(0),
	m_PausedTime(0),
	m_StopTime(0),
	m_PrevTime(0),
	m_CurTime(0),
	m_Stopped(false)
{
	INT64 countsPerSec;
	QueryPerformanceFrequency((LARGE_INTEGER *)&countsPerSec);
	m_SecondsPerCount = 1.0 / (double)countsPerSec;
}

float GameTimer::TotalTime()const
{
	if (m_Stopped)
	{
		return (float)(m_SecondsPerCount * (m_StopTime - m_PausedTime - m_BaseTime));
	}
	else
	{
		return (float)(m_SecondsPerCount * (m_CurTime - m_PausedTime - m_BaseTime));
	}
}

float GameTimer::DeltaTime()const
{
	return (float)m_DeltaTime;
}

void GameTimer::Reset()
{
	INT64 curTime;
	QueryPerformanceCounter((LARGE_INTEGER *)&curTime);

	m_BaseTime = curTime;
	m_PrevTime = curTime;
	m_StopTime = 0;
	m_PausedTime = 0;
	m_Stopped = false;
}

void GameTimer::Start()
{
	if (m_Stopped)
	{
		INT64 curTime;
		QueryPerformanceCounter((LARGE_INTEGER *)&curTime);

		m_PausedTime += curTime - m_StopTime;
		m_PrevTime = curTime;
		m_StopTime = 0;
		m_Stopped = false;
	}
}

void GameTimer::Stop()
{
	if (!m_Stopped)
	{
		INT64 curTime;
		QueryPerformanceCounter((LARGE_INTEGER *)&curTime);

		m_StopTime = curTime;
		m_Stopped = true;
	}
}

void GameTimer::Tick()
{
	if (m_Stopped)
	{
		m_DeltaTime = 0.0;
		return;
	}

	m_PrevTime = m_CurTime;

	INT64 curTime;
	QueryPerformanceCounter((LARGE_INTEGER *)&curTime);
	m_CurTime = curTime;

	m_DeltaTime = (m_CurTime - m_PrevTime) * m_SecondsPerCount;

	if (m_DeltaTime < 0)
	{
		m_DeltaTime = 0.0;
	}
}