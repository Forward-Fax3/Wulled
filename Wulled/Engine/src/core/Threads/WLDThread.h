#pragma once
#include <thread>
#include <vector>
#include <queue>
#include <functional>
#include <mutex>
#include <condition_variable>


namespace WLD
{
	class WLDThreads
	{
	// Functions
	public:
		WLDThreads();
		~WLDThreads();

		void PushFunction(std::function<void(void*)> function, void* data);

		int ThreadRunner(bool* isFinished);

		static int StaticThreadRunner(void* isFinished);

	// Data
	private:
#if (__cplusplus >= 202002L)
		std::jthread* m_Threads = nullptr;
#else
		std::thread* m_Threads = nullptr;
#endif
		bool* m_ThreadsFinished = nullptr;
		bool m_Finished = false;

		std::queue<std::pair<std::function<void(void*)>, void*>> m_Functions;
		std::condition_variable m_MutexCondition;
		std::mutex m_QueueMutex;

		static WLDThreads* s_Instance;
		static const size_t s_ThreadCount = 16;
	};
}
