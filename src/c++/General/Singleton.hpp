#pragma once

namespace General
{
	template <class T>
	class Singleton
	{
	public:
		Singleton() = default;
		Singleton(const Singleton&) = delete;
		Singleton(Singleton&&) = delete;
		Singleton& operator=(const Singleton&) = delete;
		Singleton& operator=(Singleton&&) = delete;
		~Singleton() = default;

	public:
		static T* GetSingleton()
		{
			static T singleton;
			return std::addressof(singleton);
		}
	};
}
