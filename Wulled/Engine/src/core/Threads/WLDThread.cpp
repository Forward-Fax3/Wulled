#include <WLDPCH.h>
#include "WLDThread.h"

#include "Application.h"

#include <sstream>
#include <chrono>
#include <thread>


namespace WLD
{
	WLDThreads* WLDThreads::s_Instance = nullptr;

	WLDThreads::WLDThreads()
	{
		if (s_Instance)
		{
			LOG_CORE_ERROR("WLDThreads already exists!");
			return;
		}
		s_Instance = this;

		m_Threads = CreateArray(std::thread, s_ThreadCount);
		m_ThreadsFinished = CreateArray(bool, s_ThreadCount);
		for (size_t i = 0; i < s_ThreadCount; i++)
		{
			m_ThreadsFinished[i] = false;
			std::thread thread(WLDThreads::StaticThreadRunner, (void*)(m_ThreadsFinished + i));
			m_Threads[i].swap(thread);
			m_Threads[i].detach();
		}
	}

	WLDThreads::~WLDThreads()
	{
		m_Finished = true;
		m_MutexCondition.notify_all();
		for (size_t i = 0; i < s_ThreadCount; i++)
			while (!m_ThreadsFinished[i])
				std::this_thread::sleep_for(std::chrono::nanoseconds(50));

		DestroyArray(m_Threads);
		DestroyArray(m_ThreadsFinished);

		while (!m_Functions.empty())
			m_Functions.pop();

		m_MutexCondition.~condition_variable();
		s_Instance = nullptr;
	}

	void WLDThreads::PushFunction(std::function<void(void*)> function, void* data)
	{
		{
			std::unique_lock<std::mutex> lock(m_QueueMutex);
			m_Functions.push({ function, data });
		}
		m_MutexCondition.notify_one();
	}

	int WLDThreads::ThreadRunner(bool* isFinished)
	{
		Application& app = Application::Get();
		std::pair<std::function<void(void*)>, void*> func;
		while (app.GetRun()[0] && !m_Finished)
		{
			std::unique_lock<std::mutex> lock(m_QueueMutex);
			m_MutexCondition.wait(lock, [&] { return !m_Functions.empty() || m_Finished; });
			if (m_Finished)
				break;
			func = m_Functions.front();
			m_Functions.pop();
			func.first(func.second);
		}

		*isFinished = true;
		return 0;
	}

	int WLDThreads::StaticThreadRunner(void* isFinished)
	{
		return s_Instance->ThreadRunner((bool*)isFinished);
	}
}
