#pragma once

namespace CLIK
{
	class Object
	{
	public:
		Object() :
			_instance()
		{}

		Object(const Object& a_rhs) :
			_instance()
		{
			SetInstance(a_rhs);
		}

		Object(Object&& a_rhs) :
			_instance()
		{
			SetInstance(std::move(a_rhs));
		}

		explicit Object(std::nullptr_t) :
			_instance()
		{
			SetInstance(nullptr);
		}

		explicit Object(double a_rhs) :
			_instance()
		{
			SetInstance(a_rhs);
		}

		explicit Object(bool a_rhs) :
			_instance()
		{
			SetInstance(a_rhs);
		}

		explicit Object(const char* a_rhs) :
			_instance()
		{
			SetInstance(a_rhs);
		}

		explicit Object(std::string_view a_rhs) :
			_instance()
		{
			SetInstance(a_rhs);
		}

		explicit Object(const wchar_t* a_rhs) :
			_instance()
		{
			SetInstance(a_rhs);
		}

		explicit Object(std::wstring_view a_rhs) :
			_instance()
		{
			SetInstance(a_rhs);
		}

		explicit Object(const RE::GFxValue& a_rhs) :
			_instance()
		{
			SetInstance(a_rhs);
			assert(IsObject());
		}

		explicit Object(RE::GFxValue&& a_rhs) :
			_instance()
		{
			SetInstance(std::move(a_rhs));
			assert(IsObject());
		}

		~Object() = default;

		Object& operator=(const Object& a_rhs)
		{
			SetInstance(a_rhs);
			return *this;
		}

		Object& operator=(Object&& a_rhs)
		{
			SetInstance(std::move(a_rhs));
			return *this;
		}

		Object& operator=(std::nullptr_t)
		{
			SetInstance(nullptr);
			return *this;
		}

		Object& operator=(double a_rhs)
		{
			SetInstance(a_rhs);
			return *this;
		}

		Object& operator=(bool a_rhs)
		{
			SetInstance(a_rhs);
			return *this;
		}

		Object& operator=(const char* a_rhs)
		{
			SetInstance(a_rhs);
			return *this;
		}

		Object& operator=(std::string_view a_rhs)
		{
			SetInstance(a_rhs);
			return *this;
		}

		Object& operator=(const wchar_t* a_rhs)
		{
			SetInstance(a_rhs);
			return *this;
		}

		Object& operator=(std::wstring_view a_rhs)
		{
			SetInstance(a_rhs);
			return *this;
		}

		Object& operator=(const RE::GFxValue& a_rhs)
		{
			SetInstance(a_rhs);
			assert(IsObject());
			return *this;
		}

		Object& operator=(RE::GFxValue&& a_rhs)
		{
			SetInstance(std::move(a_rhs));
			assert(IsObject());
			return *this;
		}

		RE::GFxValue& GetInstance() { return _instance; }

		// properties
		Object Constructor() const { return GetObject("constructor"); }

		Object Prototype() const { return GetObject("__proto__"); }

		Object Resolve() const { return GetObject("__resolve"); }
		void Resolve(Object& a_resolve) { SetObject("__resolve", a_resolve); }

		// methods
		//bool AddProperty(std::string_view a_name, Function& a_getter, Function& a_setter);
		bool HasOwnProperty(std::string_view a_name)
		{
			enum
			{
				kName,
				kNumArgs
			};

			std::array<RE::GFxValue, kNumArgs> args;

			args[kName] = a_name;
			assert(args[kName].IsString());

			RE::GFxValue boolean;
			[[maybe_unused]] const auto success =
				Invoke("hasOwnProperty", std::addressof(boolean), args.data(), args.size());
			assert(success);

			return boolean.GetBool();
		}

		bool IsPropertyEnumerable(std::string_view a_name)
		{
			enum
			{
				kName,
				kNumArgs
			};

			std::array<RE::GFxValue, kNumArgs> args;

			args[kName] = a_name;
			assert(args[kName].IsString());

			RE::GFxValue boolean;
			[[maybe_unused]] const auto success =
				Invoke("isPropertyEnumerable", std::addressof(boolean), args.data(), args.size());
			assert(success);

			return boolean.GetBool();
		}

		bool IsPrototypeOf(Object& a_theClass)
		{
			enum
			{
				kTheClass,
				kNumArgs
			};

			std::array<RE::GFxValue, kNumArgs> args;

			args[kTheClass] = a_theClass._instance;
			assert(args[kTheClass].IsObject());

			RE::GFxValue boolean;
			[[maybe_unused]] const auto success =
				Invoke("isPrototypeOf", std::addressof(boolean), args.data(), args.size());
			assert(success);

			return boolean.GetBool();
		}

		//bool Watch(std::string_view a_name, Function& a_callback, Object& a_userData);
		bool Unwatch(std::string_view a_name)
		{
			enum
			{
				kName,
				kNumArgs
			};

			std::array<RE::GFxValue, kNumArgs> args;

			args[kName] = a_name;
			assert(args[kName].IsString());

			RE::GFxValue boolean;
			[[maybe_unused]] const auto success =
				Invoke("unwatch", std::addressof(boolean), args.data(), args.size());
			assert(success);

			return boolean.GetBool();
		}

		std::string ToString()
		{
			RE::GFxValue str;
			[[maybe_unused]] const auto success =
				Invoke("toString", std::addressof(str));
			assert(success);
			return str.GetString();
		}

		Object ValueOf()
		{
			RE::GFxValue object;
			[[maybe_unused]] const auto success =
				Invoke("valueOf", std::addressof(object));
			assert(success);
			return Object(object);
		}

	protected:
		bool IsArray() const { return _instance.IsArray(); }
		bool IsObject() const { return _instance.IsObject(); }

		bool Invoke(const char* a_name) { return _instance.Invoke(a_name, nullptr, nullptr, 0); }
		bool Invoke(const char* a_name, RE::GFxValue* a_result) { return _instance.Invoke(a_name, a_result, nullptr, 0); }
		bool Invoke(const char* a_name, RE::GFxValue* a_result, const RE::GFxValue* a_args, RE::UPInt a_numArgs) { return _instance.Invoke(a_name, a_result, a_args, a_numArgs); }

		bool GetBoolean(const char* a_path) const
		{
			RE::GFxValue boolean;
			[[maybe_unused]] const auto success =
				_instance.GetMember(a_path, &boolean);
			assert(success);
			return boolean.GetBool();
		}

		double GetNumber(const char* a_path) const
		{
			RE::GFxValue number;
			[[maybe_unused]] const auto success =
				_instance.GetMember(a_path, &number);
			assert(success);
			return number.GetNumber();
		}

		Object GetObject(const char* a_path) const
		{
			RE::GFxValue object;
			[[maybe_unused]] const auto success =
				_instance.GetMember(a_path, &object);
			assert(success);
			return Object(object);
		}

		std::string GetString(const char* a_path) const
		{
			RE::GFxValue str;
			[[maybe_unused]] const auto success =
				_instance.GetMember(a_path, &str);
			assert(success);
			return str.GetString();
		}

		void CreateArray(RE::GPtr<RE::GFxMovieView> a_view)
		{
			a_view->CreateArray(std::addressof(_instance));
			assert(IsArray());
		}

		void SetBoolean(const char* a_path, bool a_boolean)
		{
			RE::GFxValue boolean(a_boolean);
			[[maybe_unused]] const auto success =
				_instance.SetMember(a_path, boolean);
			assert(success);
		}

		void SetNumber(const char* a_path, double a_number)
		{
			RE::GFxValue number(a_number);
			[[maybe_unused]] const auto success =
				_instance.SetMember(a_path, number);
			assert(success);
		}

		void SetObject(const char* a_path, const Object& a_object)
		{
			[[maybe_unused]] const auto success =
				_instance.SetMember(a_path, a_object._instance);
			assert(success);
		}

		void SetString(const char* a_path, std::string_view a_string)
		{
			RE::GFxValue str(a_string);
			[[maybe_unused]] const auto success =
				_instance.SetMember(a_path, str);
			assert(success);
		}

		void SetInstance(std::nullptr_t) { _instance = nullptr; }
		void SetInstance(double a_val) { _instance = a_val; }
		void SetInstance(bool a_val) { _instance = a_val; }
		void SetInstance(const char* a_val) { _instance = a_val; }
		void SetInstance(std::string_view a_val) { _instance = a_val; }
		void SetInstance(const wchar_t* a_val) { _instance = a_val; }
		void SetInstance(std::wstring_view a_val) { _instance = a_val; }
		void SetInstance(const RE::GFxValue& a_val) { _instance = a_val; }
		void SetInstance(RE::GFxValue&& a_val) { _instance = std::move(a_val); }

	private:
		void SetInstance(const Object& a_val)
		{
			if (this != std::addressof(a_val)) {
				_instance = a_val._instance;
			}
		}

		void SetInstance(Object&& a_val)
		{
			if (this != std::addressof(a_val)) {
				_instance = std::move(a_val._instance);
			}
		}

		RE::GFxValue _instance;
	};
}
