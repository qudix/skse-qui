#pragma once

template <class T>
class ISingleton
{
public:
	ISingleton() = default;
	ISingleton(const ISingleton&) = delete;
	ISingleton(ISingleton&&) = delete;
	ISingleton& operator=(const ISingleton&) = delete;
	ISingleton& operator=(ISingleton&&) = delete;
	~ISingleton() = default;

public:
	static T* GetSingleton()
	{
		static T singleton;
		return std::addressof(singleton);
	}
};
