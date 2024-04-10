#pragma once
#include "Engine/src/core/EngineCore.h"
#include <memory>
#include <unordered_map>
#include <atomic>
#ifdef _DEBUG | MEMORY_DEBUG
#include <sstream>
#endif


namespace WLD
{
	struct MemoryData
	{
		size_t Map = 0;
		size_t numberOfAllocations = 0;
		bool WasCreatedManually = 0;
#ifdef _DEBUG | MEMORY_DEBUG
		::std::string Location = "";
#endif
	};

	struct Memory
	{
		inline static size_t Allocated = 0;
		inline static size_t AllocatedSmart = 0;
		inline static ::std::unordered_map<void*, MemoryData> Map = {};
	};

	static size_t GetAllocatedMemory() { return Memory::Allocated; }
	static size_t GetAllocatedSmartMemory() { return Memory::AllocatedSmart; }
	static size_t GetAllocatedTotalMemory() { return Memory::Allocated + Memory::AllocatedSmart; }

	template<typename T>
	class Ref;

	template<typename T>
#ifdef _DEBUG
	static T* _CreateMemory(const char* file, int line)
#else
	static T* _CreateMemory()
#endif
	{
		T* ptr = new(::std::nothrow) T;
		if (!ptr)
			WLD_CORE_ASSERT(false, "Failed to allocate memory!");
		Memory::Allocated += sizeof(T);
		MemoryData data;
		data.Map = sizeof(T);
		data.numberOfAllocations = 1;
		data.WasCreatedManually = true;
#ifdef _DEBUG
		::std::stringstream ss;
		ss << file << " " << line;
		data.Location = ss.str();
#endif
		Memory::Map.insert({ (void*)ptr, data });
		return ptr;
	}

	template<typename T, typename... Args>
#ifdef _DEBUG
	static T* _CreateMemory(const char* file, int line, Args&&... args)
#else
	static T* _CreateMemory(Args&&... args)
#endif
	{
		T* ptr = new(::std::nothrow) T(::std::forward<Args>(args)...);
		if (!ptr)
			WLD_CORE_ASSERT(false, "Failed to allocate memory!");

		Memory::Allocated += sizeof(T);
		MemoryData data;
		data.Map = sizeof(T);
		data.numberOfAllocations = 1;
		data.WasCreatedManually = true;
#ifdef _DEBUG
		::std::stringstream ss;
		ss << file << " " << line;
		data.Location = ss.str();
#endif
		Memory::Map.insert({ (void*)ptr, data });
		return ptr;
	}

	template<typename T>
	static T* _DestroyMemory(T* ptr, bool FromRef = false)
	{
		if (Memory::Map.find((void*)ptr) == Memory::Map.end())
		{
			WLD_CORE_CRITICAL("Memory not found at {0}, No memory was deleted!", (size_t)ptr);
			return ptr;
		}

		MemoryData data = Memory::Map[(void*)ptr];
		if (!FromRef)
			Memory::Allocated -= data.Map * data.numberOfAllocations;
		Memory::Map.erase((void*)ptr);
		delete ptr;
		return nullptr;
	}

#if _DEBUG
	template<typename T, typename... Args>
	static T* __CreateMemory()
	{
		T* ptr = new(::std::nothrow) T();
		if (!ptr)
			WLD_CORE_ASSERT(false, "Failed to allocate memory!");

		Memory::Allocated += sizeof(T);
		MemoryData data;
		data.Map = sizeof(T);
		data.numberOfAllocations = 1;
		data.WasCreatedManually = true;
		Memory::Map.insert({ (void*)ptr, data });
		return ptr;
	}

	template<typename T, typename... Args>
	static T* __CreateMemory(Args&&... args)
	{
		T* ptr = new(::std::nothrow) T(::std::forward<Args>(args)...);
		if (!ptr)
			WLD_CORE_ASSERT(false, "Failed to allocate memory!");

		Memory::Allocated += sizeof(T);
		MemoryData data;
		data.Map = sizeof(T);
		data.numberOfAllocations = 1;
		data.WasCreatedManually = true;
		Memory::Map.insert({ (void*)ptr, data });
		return ptr;
	}
#endif

	template<typename T, typename... Args>
#ifdef _DEBUG
	static T* _CreateArray(const char* file, int line, size_t numberOfT, Args&&... args)
#else
	static T* _CreateArray(size_t numberOfT, Args&&... args)
#endif
	{
		T* ptr = new(::std::nothrow) T(::std::forward<Args>(args)...)[numberOfT];
		if (!ptr)
			WLD_CORE_ASSERT(false, "Failed to allocate memory!");
		Memory::Allocated += sizeof(T) * numberOfT;
		MemoryData data;
		data.Map = sizeof(T);
		data.numberOfAllocations = numberOfT;
		data.WasCreatedManually = true;
#ifdef _DEBUG
		::std::stringstream ss;
		ss << file << " " << line;
		data.Location = ss.str();
#endif
		Memory::Map.insert({ (void*)ptr, data });
		return ptr;
	}

	template<typename T>
#ifdef _DEBUG
	static T* _CreateArray(const char* file, int line, size_t numberOfT)
#else
	static T* _CreateArray(size_t numberOfT)
#endif
	{
		T* ptr = new(::std::nothrow) T[numberOfT];
		if (!ptr)
			WLD_CORE_ASSERT(false, "Failed to allocate memory!");
		Memory::Allocated += sizeof(T) * numberOfT;
		MemoryData data;
		data.Map = sizeof(T);
		data.numberOfAllocations = numberOfT;
		data.WasCreatedManually = true;
#ifdef _DEBUG
		::std::stringstream ss;
		ss << file << " " << line;
		data.Location = ss.str();
#endif
		Memory::Map.insert({ (void*)ptr, data });
		return ptr;
	}

	template<typename T>
#ifdef _DEBUG
	static Ref<T> _CreateRef(const char* file, int line)
#else
	static Ref<T> _CreateRef()
#endif
	{
#ifdef _DEBUG
		Ref<T> ptr(__CreateMemory<T>());
		MemoryData& data = Memory::Map[(void*)ptr.get()];
		::std::stringstream ss;
		ss << file << " " << line;
		data.Location = ss.str();
#else
		Ref<T> ptr(_CreateMemory<T>());
#endif
		return ptr;
	}

	template<typename T, typename... Args>
#ifdef _DEBUG
	static Ref<T> _CreateRef(const char* file, int line, Args&&... args)
#else
	static Ref<T> _CreateRef(Args&&... args)
#endif
	{
#ifdef _DEBUG
		Ref<T> ptr(__CreateMemory<T>(::std::forward<Args>(args)...));
		MemoryData& data = Memory::Map[(void*)ptr.get()];
		::std::stringstream ss;
		ss << file << " " << line;
		data.Location = ss.str();
#else
		Ref<T> ptr(_CreateMemory<T>(::std::forward<Args>(args)...));
#endif
		return ptr;
	}

	template<typename T>
#ifdef _DEBUG
	static Scope<T> _CreateScope(const char* file, int line)
#else
	static Scope<T> _CreateScope()
#endif
	{
		::std::unique_ptr<T> ptr(::std::make_unique<T>());
		Memory::AllocatedSmart += sizeof(T);
		MemoryData data;
		data.Map = sizeof(T);
		data.numberOfAllocations = 1;
		data.WasCreatedManually = false;
#ifdef _DEBUG
		::std::stringstream ss;
		ss << file << " " << line;
		data.Location = ss.str();
#endif
		Memory::Map.insert({ (void*)ptr.get(), data });
		return ptr;
	}

	template<typename T, typename... Args>
#ifdef _DEBUG
	static Scope<T> _CreateScope(const char* file, int line, Args&&... args)
#else
	static Scope<T> _CreateScope(Args&&... args)
#endif
	{
		Scope<T> ptr(::std::make_unique<T>(::std::forward<Args>(args)...));
		Memory::AllocatedSmart += sizeof(T);
		MemoryData data;
		data.Map = sizeof(T);
		data.numberOfAllocations = 1;
		data.WasCreatedManually = false;
#ifdef _DEBUG
		::std::stringstream ss;
		ss << file << " " << line;
		data.Location = ss.str();
#endif
		Memory::Map.insert({ (void*)ptr.get(), data });
		return ptr;
	}

#define _DestroyScope(x)\
	if (::WLD::Memory::Map.find((void*)x.get()) == ::WLD::Memory::Map.end())\
	{\
		WLD_CORE_CRITICAL("Memory not found at {0}, No memory was deleted!", (size_t)x.get());\
		return;\
	}\
	::WLD::MemoryData data = ::WLD::Memory::Map[(void*)x.get()];\
	if (data.WasCreatedManually)\
	{\
		::WLD::_DestroyMemory(x.get());\
		x.reset();\
	}\
	else\
	{\
		::WLD::Memory::AllocatedSmart -= data.Map;\
		::WLD::Memory::Map.erase((void*)x.get());\
		x.reset();\
	}

#ifdef _DEBUG

#define CreateMemory(x, ...)   ::WLD::_CreateMemory<x>(__FILE__, __LINE__, __VA_ARGS__)
#define CreateArray(x, y, ...) ::WLD::_CreateArray<x>(__FILE__, __LINE__, y, __VA_ARGS__)
#define CreateRef(x, ...)      ::WLD::_CreateRef<x>(__FILE__, __LINE__, __VA_ARGS__)
#define CreateScope(x, ...)    ::WLD::_CreateScope<x>(__FILE__, __LINE__, __VA_ARGS__)

#define DestroyMemory(x) ::WLD::_DestroyMemory(x)
#define DestroyScope(x)  _DestroyScope(x)

#else

#define CreateMemory(x, ...)   ::WLD::_CreateMemory<x>(__VA_ARGS__)
#define CreateArray(x, y, ...) ::WLD::_CreateArray<x>(y, __VA_ARGS__)
#define CreateRef(x, ...)      ::WLD::_CreateRef<x>(__VA_ARGS__)
#define CreateScope(x, ...)    ::WLD::_CreateScope<x>(__VA_ARGS__)

#define DestroyMemory(x) ::WLD::_DestroyMemory(x)
#define DestroyScope(x)  _DestroyScope(x)

#endif

	template<typename T>
	class BassRefPtr
	{
	};

	template<typename T>
	class Ref
	{
	public:
		constexpr Ref() noexcept
			: m_Ptr(nullptr), m_RefCount(nullptr) {}

		constexpr Ref(::std::nullptr_t) noexcept
			: m_Ptr(nullptr), m_RefCount(nullptr) {}

		inline Ref(T* ptr)
		{
			m_Ptr = ptr;
			m_RefCount = new(::std::nothrow) ::std::atomic<size_t>;
			if (!m_RefCount)
				WLD_CORE_ASSERT(false, "Failed to allocate memory!");
			*m_RefCount = 1;

			if (Memory::Map.find((void*)m_Ptr) == Memory::Map.end())
			{
				MemoryData data;
				data.Map = 0;
				data.numberOfAllocations = 0;
				data.WasCreatedManually = false;
#ifdef _DEBUG
				data.Location = "unkown creation location as data was created outside of Wuled memory functions!";
#endif
				Memory::Map.insert({ (void*)m_Ptr, data });
			}
			else
			{
				MemoryData& data = Memory::Map[(void*)m_Ptr];
				data.WasCreatedManually = false;
				Memory::Allocated -= data.Map * data.numberOfAllocations;
				Memory::AllocatedSmart += data.Map * data.numberOfAllocations;
			}
		}

		template<class child>
		inline Ref(child* ptr)
		{
			m_Ptr = (T*)ptr;
			m_RefCount = new(::std::nothrow) ::std::atomic<size_t>;
			if (!m_RefCount)
				WLD_CORE_ASSERT(false, "Failed to allocate memory!");
			*m_RefCount = 1;


			if (Memory::Map.find((void*)m_Ptr) == Memory::Map.end())
			{
				MemoryData data;
				data.Map = 0;
				data.numberOfAllocations = 0;
				data.WasCreatedManually = false;
#ifdef _DEBUG
				data.Location = "unkown creation location as data was created outside of Wuled memory functions!";
#endif
				Memory::Map.insert({ (void*)m_Ptr, data });
			}
			else
			{
				MemoryData& data = Memory::Map[(void*)m_Ptr];
				data.WasCreatedManually = false;
				Memory::Allocated -= data.Map * data.numberOfAllocations;
				Memory::AllocatedSmart += data.Map * data.numberOfAllocations;
			}
		}

		inline Ref(::std::shared_ptr<T> ptr)
		{
			m_Ptr = ptr.get();
			m_RefCount = new(::std::nothrow) ::std::atomic<size_t>;
			if (!m_RefCount)
				WLD_CORE_ASSERT(false, "Failed to allocate memory!");
			*m_RefCount = ptr.use_count();

			if (Memory::Map.find((void*)m_Ptr) == Memory::Map.end())
			{
				MemoryData data;
				data.Map = 0;
				data.numberOfAllocations = 0;
				data.WasCreatedManually = false;
			}
		}

		inline Ref(const Ref& oldRef)
		{
			m_Ptr = oldRef.m_Ptr;
			m_RefCount = oldRef.m_RefCount;
			(*m_RefCount)++;
		}

		inline Ref(Ref&& oldRef)
		{
			m_Ptr = oldRef.m_Ptr;
			m_RefCount = oldRef.m_RefCount;
			oldRef.m_Ptr = nullptr;
			oldRef.m_RefCount = nullptr;
		}

		template<class child>
		inline Ref(const Ref<child>& oldRef)
		{
			m_Ptr = oldRef.m_Ptr;
			m_RefCount = oldRef.m_RefCount;
			(*m_RefCount)++;
		}

		template<class child>
		inline Ref(Ref<child>&& oldRef)
		{
			m_Ptr = (T*)oldRef.m_Ptr;
			m_RefCount = oldRef.m_RefCount;
			oldRef.m_Ptr = nullptr;
			oldRef.m_RefCount = nullptr;
		}

		template<class child, ::std::enable_if_t<::std::_SP_pointer_compatible<T, child>::value, int> = 0>
		inline Ref(const Ref<child>& oldRef)
		{
			m_Ptr = oldRef.m_Ptr;
			m_RefCount = oldRef.m_RefCount;
			(*m_RefCount)++;
		}

		template<class child, ::std::enable_if_t<::std::_SP_pointer_compatible<T, child>::value, int> = 0>
		inline Ref(Ref<child>&& oldRef)
		{
			m_Ptr = oldRef.m_Ptr;
			m_RefCount = oldRef.m_RefCount;
			oldRef.m_Ptr = nullptr;
			oldRef.m_RefCount = nullptr;
		}

		inline ~Ref()
		{
			if (m_RefCount == nullptr)
				return;

			(*m_RefCount)--;
			if (*m_RefCount == 0)
			{
				if (Memory::Map.find((void*)m_Ptr) != Memory::Map.end())
				{
					MemoryData& data = Memory::Map[(void*)m_Ptr];
					Memory::AllocatedSmart -= data.Map * data.numberOfAllocations;
				}

				m_Ptr = _DestroyMemory(m_Ptr, true);
				delete m_RefCount;
			}
			else
				m_Ptr = nullptr;
			m_RefCount = nullptr;
		}

		inline Ref& operator=(const Ref& oldRef)
		{
			if (this == &oldRef)
				return *this;

			m_Ptr = oldRef.m_Ptr;
			m_RefCount = oldRef.m_RefCount;
			(*m_RefCount)++;
			return *this;
		}

		inline Ref& operator=(Ref&& oldRef) noexcept
		{
			if (this == &oldRef)
				return *this;

			m_Ptr = oldRef.m_Ptr;
			m_RefCount = oldRef.m_RefCount;
			oldRef.m_Ptr = nullptr;
			oldRef.m_RefCount = nullptr;
			return *this;
		}

		template <class child, ::std::enable_if<::std::_SP_pointer_compatible<T, child>::value, int> = 0>
		inline Ref& operator=(const Ref<child>& oldRef)
		{
			if (this == &oldRef)
				return *this;

			m_Ptr = oldRef.m_Ptr;
			m_RefCount = oldRef.m_RefCount;
			(*m_RefCount)++;
			return *this;
		}

		template <class child, ::std::enable_if<::std::_SP_pointer_compatible<T, child>::value, int> = 0>
		inline Ref& operator=(Ref<child>&& oldRef)
		{
			if (this == &oldRef)
				return *this;

			m_Ptr = oldRef.m_Ptr;
			m_RefCount = oldRef.m_RefCount;
			oldRef.m_Ptr = nullptr;
			oldRef.m_RefCount = nullptr;
			return *this;
		}

		inline T& operator*() const { return *m_Ptr; }
		inline T* operator->() const { return m_Ptr; }

		inline bool operator==(const Ref& other) const { return m_Ptr == other.m_Ptr; }
		template <class child> inline bool operator==(const Ref<child>& other) const { return m_Ptr == other.m_Ptr; }
		inline bool operator==(const T* other) const { return m_Ptr == other; }

		inline bool operator!=(const Ref& other) const { return m_Ptr != other.m_Ptr; }
		template <class child> inline bool operator!=(const Ref<child>& other) const { return m_Ptr != other.m_Ptr; }
		inline bool operator!=(const T* other) const { return m_Ptr != other; }

		inline T* get() const { return m_Ptr; }
		inline size_t use_count() const { return *m_RefCount; }

		inline void reset()
		{
			this->~Ref();
		}

		inline void reset(T* ptr)
		{
			Ref<T> temp(ptr);
			swap(temp);
		}

		template<class child>
		inline void reset(child* ptr)
		{
			Ref<T> temp(ptr);
			swap(temp);
		}

		inline void reset(Ref<T>& other)
		{
			Ref<T> temp(other);
			swap(temp);
		}

		inline void reset(Ref<T>&& other)
		{
			Ref<T> temp(other);
			swap(temp);
		}

		inline void swap(Ref& other)
		{
			::std::swap(m_Ptr, other.m_Ptr);
			::std::swap(m_RefCount, other.m_RefCount);
		}

		template<class child>
		inline void swap(Ref<child>& other)
		{
			::std::swap(m_Ptr, other.m_Ptr);
			::std::swap(m_RefCount, other.m_RefCount);
		}

		inline operator bool() const { return m_Ptr != nullptr; }

	private:
		T* m_Ptr;
		::std::atomic<size_t>* m_RefCount;

		template<class child>
		friend class Ref;
	};
}