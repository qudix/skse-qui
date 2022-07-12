#pragma once

namespace SF
{
	inline Object::Object(std::nullptr_t) :
		_instance(nullptr)
	{}

	inline Object::Object(double a_rhs) :
		_instance(a_rhs)
	{}

	inline Object::Object(bool a_rhs) :
		_instance(a_rhs)
	{}

	inline Object::Object(const char* a_rhs) :
		_instance(a_rhs)
	{}

	inline Object::Object(std::string_view a_rhs) :
		_instance(a_rhs)
	{}

	inline Object::Object(const wchar_t* a_rhs) :
		_instance(a_rhs)
	{}

	inline Object::Object(std::wstring_view a_rhs) :
		_instance(a_rhs)
	{}

	inline Object::Object(const RE::GFxValue& a_rhs) :
		_instance(a_rhs)
	{
		Assert(IsObject());
	}

	inline Object::Object(RE::GFxValue&& a_rhs) :
		_instance(std::move(a_rhs))
	{
		Assert(IsObject());
	}

	inline Object& Object::operator=(const Object& a_rhs)
	{
		_instance = a_rhs._instance;
		return *this;
	}

	inline Object& Object::operator=(Object&& a_rhs)
	{
		_instance = std::move(a_rhs._instance);
		return *this;
	}

	inline Object& Object::operator=(std::nullptr_t)
	{
		_instance = nullptr;
		return *this;
	}

	inline Object& Object::operator=(double a_rhs)
	{
		_instance = a_rhs;
		return *this;
	}

	inline Object& Object::operator=(bool a_rhs)
	{
		_instance = a_rhs;
		return *this;
	}

	inline Object& Object::operator=(const char* a_rhs)
	{
		_instance = a_rhs;
		return *this;
	}

	inline Object& Object::operator=(std::string_view a_rhs)
	{
		_instance = a_rhs;
		return *this;
	}

	inline Object& Object::operator=(const wchar_t* a_rhs)
	{
		_instance = a_rhs;
		return *this;
	}

	inline Object& Object::operator=(std::wstring_view a_rhs)
	{
		_instance = a_rhs;
		return *this;
	}

	inline Object& Object::operator=(const RE::GFxValue& a_rhs)
	{
		_instance = a_rhs;
		Assert(IsObject());
		return *this;
	}

	inline Object& Object::operator=(RE::GFxValue&& a_rhs)
	{
		_instance = std::move(a_rhs);
		Assert(IsObject());
		return *this;
	}

	inline Object::operator RE::GFxValue&()
	{
		return _instance;
	}

	inline Object::operator const RE::GFxValue&() const
	{
		return _instance;
	}
}

namespace SF
{
	inline RE::GFxValue& Object::GetInstance()
	{
		return _instance;
	}

	inline Object Object::Constructor() const
	{
		return GetObject("constructor");
	}

	inline Object Object::Prototype() const
	{
		return GetObject("__proto__");
	}

	inline Object Object::Resolve() const
	{
		return GetObject("__resolve");
	}

	inline void Object::Resolve(Object& a_resolve)
	{
		SetObject("__resolve", a_resolve);
	}

	inline bool Object::HasOwnProperty(std::string_view a_name)
	{
		RE::GFxValue boolean;
		Assert(InvokeA("hasOwnProperty", std::addressof(boolean), a_name));
		return boolean.GetBool();
	}

	inline bool Object::IsPropertyEnumerable(std::string_view a_name)
	{
		RE::GFxValue boolean;
		Assert(InvokeA("isPropertyEnumerable", std::addressof(boolean), a_name));
		return boolean.GetBool();
	}

	inline bool Object::IsPrototypeOf(Object& a_theClass)
	{
		RE::GFxValue boolean;
		Assert(InvokeA("isPrototypeOf", std::addressof(boolean), a_theClass));
		return boolean.GetBool();
	}

	inline bool Object::Unwatch(std::string_view a_name)
	{
		RE::GFxValue boolean;
		Assert(InvokeA("unwatch", std::addressof(boolean), a_name));
		return boolean.GetBool();
	}

	inline std::string Object::ToString()
	{
		RE::GFxValue str;
		Assert(Invoke("toString", std::addressof(str)));
		return str.GetString();
	}

	inline Object Object::ValueOf()
	{
		RE::GFxValue object;
		Assert(Invoke("valueOf", std::addressof(object)));
		return Object(object);
	}
}

namespace SF
{
	inline void Object::CreateArray(RE::GPtr<RE::GFxMovieView> a_view)
	{
		a_view->CreateArray(std::addressof(_instance));
		Assert(IsArray());
	}

	inline bool Object::GetBoolean(const char* a_path) const
	{
		RE::GFxValue boolean;
		Assert(_instance.GetMember(a_path, &boolean));
		return boolean.GetBool();
	}

	inline double Object::GetNumber(const char* a_path) const
	{
		RE::GFxValue number;
		Assert(_instance.GetMember(a_path, &number));
		return number.GetNumber();
	}

	inline Object Object::GetObject(const char* a_path) const
	{
		RE::GFxValue object;
		Assert(_instance.GetMember(a_path, &object));
		return Object(object);
	}

	inline std::string Object::GetString(const char* a_path) const
	{
		RE::GFxValue str;
		Assert(_instance.GetMember(a_path, &str));
		return str.GetString();
	}

	inline bool Object::Invoke(const char* a_name)
	{
		return _instance.Invoke(a_name, nullptr, nullptr, 0);
	}

	inline bool Object::Invoke(const char* a_name, RE::GFxValue* a_result)
	{
		return _instance.Invoke(a_name, a_result, nullptr, 0);
	}

	inline bool Object::Invoke(const char* a_name, RE::GFxValue* a_result, const RE::GFxValue* a_args, RE::UPInt a_numArgs)
	{
		return _instance.Invoke(a_name, a_result, a_args, a_numArgs);
	}

	inline bool Object::IsArray() const
	{
		return _instance.IsArray();
	}

	inline bool Object::IsObject() const
	{
		return _instance.IsObject();
	}

	inline void Object::SetBoolean(const char* a_path, bool a_boolean)
	{
		RE::GFxValue boolean(a_boolean);
		Assert(_instance.SetMember(a_path, boolean));
	}

	inline void Object::SetNumber(const char* a_path, double a_number)
	{
		RE::GFxValue number(a_number);
		Assert(_instance.SetMember(a_path, number));
	}

	inline void Object::SetObject(const char* a_path, const Object& a_object)
	{
		Assert(_instance.SetMember(a_path, a_object));
	}

	inline void Object::SetString(const char* a_path, const char* a_str)
	{
		RE::GFxValue str(a_str);
		Assert(_instance.SetMember(a_path, str));
	}

	inline void Object::SetString(const char* a_path, std::string_view a_str)
	{
		RE::GFxValue str(a_str);
		Assert(_instance.SetMember(a_path, str));
	}

	inline void Object::SetStringW(const char* a_path, const wchar_t* a_str)
	{
		RE::GFxValue str(a_str);
		Assert(_instance.SetMember(a_path, str));
	}

	inline void Object::SetStringW(const char* a_path, std::wstring_view a_str)
	{
		RE::GFxValue str(a_str);
		Assert(_instance.SetMember(a_path, str));
	}

	template <class... Args>
	inline bool Object::InvokeA(const char* a_name, RE::GFxValue* a_result, Args... a_args)
	{
		std::array<RE::GFxValue, sizeof...(a_args)> args{ (std::forward<Args>(a_args), ...) };
		return Invoke(a_name, a_result, args.data(), args.size());
	}
}
