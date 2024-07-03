#include "wldpch.h"
#include "EngineCore.h"
#include "WLDMem.h"
#include "Window.h"

#include <bits.h>

#include "WinWindow.h"


namespace WLD
{
#if defined(_DEBUG)
	void WLD_SDLCheckError(int32_t sdlResult)
	{
		WLD_CORE_ASSERT(sdlResult == 0, "SDL Error: {0}", SDL_GetError());
	}

	void WLD_SDLCheckError(SDL_bool sdlResult)
	{
		WLD_CORE_ASSERT(sdlResult == SDL_TRUE, "SDL Error: {0}", SDL_GetError());
	}

	void WLD_SDLCheckError(SDL_Window* sdlResult)
	{
		WLD_CORE_ASSERT(sdlResult, "SDL Window Error: {0}", SDL_GetError());
	}

	void WLD_SDLCheckError(SDL_GLContext sdlResult)
	{
		WLD_CORE_ASSERT(sdlResult, "SDL GL Context Error: {0}", SDL_GetError());
	}
#endif

	Window* Window::Create(WindowProps& props)
	{
		return CreateMemory(WinWindow, props);
	}

	WindowProps::WindowProps()
		: Title(nullptr), TitleC(nullptr), Width(NULL), Height(NULL)
	{
		m_CreatedMethod = BIT(0);
	}

	WindowProps::WindowProps(const char* title, uint32_t width, uint32_t height)
		: Title(nullptr), TitleC((char*)title), Width(width), Height(height)
	{
		m_CreatedMethod = 0;
		size_t length = strlen(TitleC) + 1;
		Title = CreateArray(wchar_t, length);
		mbstowcs(Title, TitleC, length);
	}

	WindowProps::WindowProps(const wchar_t* title, uint32_t width, uint32_t height)
		: Title((wchar_t*)title), TitleC(nullptr), Width(width), Height(height)
	{
		m_CreatedMethod = 0;
		m_CreatedMethod |= BIT(1);
		size_t outSize;
		size_t length = wcslen(Title) + 1;
		TitleC = CreateArray(char, length);
		wcstombs_s(&outSize, TitleC, length, Title, wcslen(Title));
	}

	WindowProps::WindowProps(WindowProps&& props) noexcept
	{
		std::swap(Title, props.Title);
		std::swap(TitleC, props.TitleC);

		Width = props.Width;
		Height = props.Height;
		props.Width = NULL;
		props.Height = NULL;

		m_CreatedMethod ^= props.m_CreatedMethod;
		props.m_CreatedMethod ^= m_CreatedMethod;
		m_CreatedMethod ^= props.m_CreatedMethod;
		props.~WindowProps();

		props.Title = nullptr;
		props.TitleC = nullptr;
		props.m_CreatedMethod = BIT(0);
	}

	WindowProps::~WindowProps()
	{
		if (m_CreatedMethod & BIT(0))
			return;

		if (m_CreatedMethod & BIT(1))
			DestroyArray(TitleC);
		else
			DestroyArray(Title);

		Title = nullptr;
		TitleC = nullptr;
		Width = NULL;
		Height = NULL;
		m_CreatedMethod = BIT(0);
	}

	WindowProps& WindowProps::operator=(WindowProps&& props) noexcept
	{
		if (this == &props)
			return *this;

		std::swap(Title, props.Title);
		std::swap(TitleC, props.TitleC);

		Width = props.Width;
		Height = props.Height;

		m_CreatedMethod ^= props.m_CreatedMethod;
		props.m_CreatedMethod ^= m_CreatedMethod;
		m_CreatedMethod ^= props.m_CreatedMethod;

		return *this; // props will call its own destructor
	}
}