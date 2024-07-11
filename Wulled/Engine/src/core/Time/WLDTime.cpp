#include "WLDPCH.h"
#include "EngineCore.h"

#include "WLDTime.h"
#include <chrono>

namespace WLD
{
	// Time
	Time::Time()
		: Layer("Time")
	{
		WLD_CORE_ASSERT(!s_Instance, "Time already exists!");

		s_Instance = this;
	}

	Time::~Time()
	{
		s_Instance = nullptr;
	}

	void Time::OnUpdate()
	{
		auto now = std::chrono::high_resolution_clock::now();
		static auto last = now;
		m_DeltaTime = std::chrono::duration<float>(now - last).count();
		last = now;
		m_Time += m_DeltaTime;
		m_FPS = 1.0f / m_DeltaTime;
		m_FrameTime = m_DeltaTime * 1000;
	}

	// Timer
	void Timer::Start()
	{
		m_TimeStart = Time::GetTime();
	}

	void Timer::Stop()
	{
		if (m_IsPaused)
			return;

		m_EndTime = Time::GetTime() - m_TimeStart;
	}

	void Timer::Reset()
	{
		m_TimeStart = 0.0f;
		m_EndTime = 0.0f;
		m_IsPaused = false;

		if (m_PausedTime)
			delete[] m_PausedTime;
		if (m_ResumedTime)
			delete[] m_ResumedTime;
	}

	void Timer::Pause()
	{
		if (m_IsPaused) return;

		m_IsPaused = true;
		m_NumOfPauses++;
		m_PausedTime = new float[m_NumOfPauses];
		m_PausedTime[m_NumOfPauses - 1] = Time::GetTime();
	}

	void Timer::Resume()
	{
		if (!m_IsPaused) return;

		m_IsPaused = false;
		m_ResumedTime = new float[m_NumOfPauses];
		m_ResumedTime[m_NumOfPauses - 1] = Time::GetTime();
	}

	float Timer::GetTime()
	{
		if (m_NumOfPauses)
		{
			float pausedTime = 0.0f;
			for (size_t i = 0; i < m_NumOfPauses; i++)
			{
				pausedTime += m_ResumedTime[i] - m_PausedTime[i];
			}
			return m_EndTime - pausedTime;
		}
		else
		{
			return m_EndTime;
		}
	}
}