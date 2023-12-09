#pragma once
#include "Engine/src/core/EngineCore.h"
#include "Engine/src/core/layers/Layer.h"


namespace WLD
{
	class WLD_API Time : public Layer
	{
	public:
		Time();
		~Time();

		virtual void OnUpdate() override;

		inline static float GetDeltaTime()    { return s_Instance->m_DeltaTime; }
		inline static float GetTime()         { return s_Instance->m_Time; }
		inline static float GetFPS()          { return s_Instance->m_FPS; }
		inline static float GetFrameTime_ms() { return s_Instance->m_FrameTime; }
		inline static float GetFrameTime_s()  { return GetDeltaTime(); }

	private:
		inline static Time* s_Instance = nullptr;
		float m_DeltaTime = 0.0f;
		float m_Time = 0.0f;
		float m_FPS = 0.0f;
		float m_FrameTime = 0.0f;
	};

	class Timer
	{
		void Start();
		void Stop();
		void Reset();
		void Pause();
		void Resume();
		float GetTime();

	private:
		float m_TimeStart = 0.0f;
		float m_EndTime = 0.0f;
		bool m_IsPaused = false;

		float* m_PausedTime = nullptr;
		float* m_ResumedTime = nullptr;
		size_t m_NumOfPauses = 0;
	};
}