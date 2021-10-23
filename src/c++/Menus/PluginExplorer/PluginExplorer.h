#pragma once

namespace Menus
{
	class PluginExplorer
	{
	public:
		class PluginInfo
		{
		public:
			using FormMap = std::map<RE::FormID, std::string_view>;
			using TypeMap = std::unordered_map<RE::FormType, FormMap>;

			PluginInfo(std::string_view a_name, uint32_t a_index) :
				_name(a_name),
				_index(a_index)
			{}

			template<class T>
			void AddForm(T a_form);

			std::string_view GetName() const noexcept { return _name; }
			TypeMap GetForms() { return _forms; }
			size_t GetCount();

		private:
			std::string_view _name{ "" };
			TypeMap _forms;
			uint32_t _index;
		};

		using PluginList = std::map<uint32_t, PluginInfo>;
		using PluginCache = std::unordered_map<std::string, uint32_t>;

		static void Init();
		static void Reset() { _plugins.clear(); }

		static PluginList& GetPlugins() { return _plugins; }
		static PluginInfo* FindPlugin(uint32_t a_formID);

	private:
		static uint32_t GetCombinedIndex(const RE::TESFile* a_file);

		static void AddForms(RE::FormType a_type);

	private:
		static inline PluginList _plugins;
		static inline PluginCache _cache;
	};
}
