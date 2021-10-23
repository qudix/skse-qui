#include "Menus/PluginExplorer/PluginExplorer.h"

namespace Menus
{
	template <class T>
	void PluginExplorer::PluginInfo::AddForm(T a_form)
	{
		auto formName = a_form->GetName();
		if (!formName || !a_form->GetPlayable())
			return;

		RE::FormID formID = a_form->GetFormID();
		RE::FormType formType = a_form->GetFormType();
		switch (formType) {
			case RE::FormType::AlchemyItem:
			case RE::FormType::Ammo:
			case RE::FormType::Armor:
			case RE::FormType::Book:
			case RE::FormType::KeyMaster:
			case RE::FormType::Misc:
			case RE::FormType::Note:
			case RE::FormType::Weapon:
				_forms[formType].insert_or_assign(formID, formName);
				break;
			default:
				logger::warn("Unhandled FormType: {}", formType);
				break;
		}
	}

	size_t PluginExplorer::PluginInfo::GetCount()
	{
		size_t result{ 0 };
		for (auto& [type, map] : _forms) {
			result += map.size();
		}

		return result;
	}

	void PluginExplorer::Init()
	{
		auto handler = RE::TESDataHandler::GetSingleton();
		if (!handler) {
			logger::error("Missing TESDataHandler!"sv);
			return;
		}

		for (auto file : handler->files) {
			if (file->compileIndex != 0xFF) {
				auto index = GetCombinedIndex(file);
				PluginInfo info{ file->fileName, index };
				_cache.insert({ file->fileName, index });
				_plugins.insert({ index, std::move(info) });
			}
		}

		AddForms(RE::FormType::AlchemyItem);
		AddForms(RE::FormType::Ammo);
		AddForms(RE::FormType::Armor);
		AddForms(RE::FormType::Book);
		AddForms(RE::FormType::KeyMaster);
		AddForms(RE::FormType::Misc);
		AddForms(RE::FormType::Note);
		AddForms(RE::FormType::Weapon);
	}

	PluginExplorer::PluginInfo* PluginExplorer::FindPlugin(uint32_t a_formID)
	{
		auto it = _plugins.find(a_formID);
		if (it != _plugins.end()) {
			return &it->second;
		}

		return nullptr;
	}

	uint32_t PluginExplorer::GetCombinedIndex(const RE::TESFile* a_file)
	{
		return static_cast<uint32_t>(a_file->compileIndex + a_file->smallFileCompileIndex);
	}

	void PluginExplorer::AddForms(RE::FormType a_type)
	{
		auto handler = RE::TESDataHandler::GetSingleton();
		auto& items = handler->GetFormArray(a_type);
		for (auto form : items) {
			auto file = form->GetFile(0);
			if (!file || !(file->compileIndex < 0xFF))
				continue;

			auto it = _cache.find(file->fileName);
			if (it == _cache.end())
				continue;

			auto info = _plugins.find(GetCombinedIndex(file));
			if (info != _plugins.end()) {
				info->second.AddForm(form);
			}
		}
	}
}
