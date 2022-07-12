#pragma once

#include "Scaleform/System/Assert.hpp"

namespace SF
{
	class Object
	{
	public:
		Object() = default;
		Object(const Object&) = default;
		Object(Object&&) = default;

		explicit Object(std::nullptr_t);
		explicit Object(double a_rhs);
		explicit Object(bool a_rhs);
		explicit Object(const char* a_rhs);
		explicit Object(std::string_view a_rhs);
		explicit Object(const wchar_t* a_rhs);
		explicit Object(std::wstring_view a_rhs);
		explicit Object(const RE::GFxValue& a_rhs);
		explicit Object(RE::GFxValue&& a_rhs);

		~Object() = default;

		Object& operator=(const Object& a_rhs);
		Object& operator=(Object&& a_rhs);
		Object& operator=(std::nullptr_t);
		Object& operator=(double a_rhs);
		Object& operator=(bool a_rhs);
		Object& operator=(const char* a_rhs);
		Object& operator=(std::string_view a_rhs);
		Object& operator=(const wchar_t* a_rhs);
		Object& operator=(std::wstring_view a_rhs);
		Object& operator=(const RE::GFxValue& a_rhs);
		Object& operator=(RE::GFxValue&& a_rhs);

		operator RE::GFxValue&();
		operator const RE::GFxValue&() const;

	public:
		Object        Constructor() const;
		RE::GFxValue& GetInstance();
		bool          HasOwnProperty(std::string_view a_name);
		bool          IsPropertyEnumerable(std::string_view a_name);
		bool          IsPrototypeOf(Object& a_theClass);
		Object        Prototype() const;
		Object        Resolve() const;
		void          Resolve(Object& a_resolve);
		std::string   ToString();
		bool          Unwatch(std::string_view a_name);
		Object        ValueOf();

	public:
		void        CreateArray(RE::GPtr<RE::GFxMovieView> a_view);
		bool        GetBoolean(const char* a_path) const;
		double      GetNumber(const char* a_path) const;
		Object      GetObject(const char* a_path) const;
		std::string GetString(const char* a_path) const;
		bool        Invoke(const char* a_name);
		bool        Invoke(const char* a_name, RE::GFxValue* a_result);
		bool        Invoke(const char* a_name, RE::GFxValue* a_result, const RE::GFxValue* a_args, RE::UPInt a_numArgs);
		bool        IsArray() const;                                                                                
		bool        IsObject() const;
		void        SetBoolean(const char* a_path, bool a_bool);
		void        SetNumber(const char* a_path, double a_num);
		void        SetObject(const char* a_path, const Object& a_object);
		void        SetString(const char* a_path, const char* a_str);
		void        SetString(const char* a_path, std::string_view a_str);
		void        SetStringW(const char* a_path, const wchar_t* a_str);
		void        SetStringW(const char* a_path, std::wstring_view a_str);

		template <class... Args>
		bool InvokeA(const char* a_name, RE::GFxValue* a_result, Args... a_args);

	protected:
		RE::GFxValue _instance{};
	};
}

#include "Object.inl"
