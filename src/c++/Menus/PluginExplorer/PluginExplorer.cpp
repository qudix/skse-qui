#include "Menus/PluginExplorer/PluginExplorer.h"
#include "Menus/PluginExplorer/PluginExplorerMenu.h"

#include "Script/Script.h"

namespace Menus
{
	template <class T>
	void PluginExplorer::PluginInfo::AddForm(T a_form)
	{
		auto formName = a_form->GetName();
		if (!formName || !a_form->GetPlayable())
			return;

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
				_forms[formType].insert_or_assign(a_form, formName);
				_count += 1;
				break;
			default:
				logger::warn("Unhandled FormType: {}", formType);
				break;
		}
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

		InitContainer();
	}

	void PluginExplorer::InitContainer()
	{
		// TODO: Figure out how to access the container in an unloaded cell
		
		auto factoryCELL = RE::IFormFactory::GetConcreteFormFactoryByType<RE::TESObjectCELL>();
		auto cell = factoryCELL ? factoryCELL->Create() : nullptr;
		if (!cell)
			return;

		auto handler = RE::TESDataHandler::GetSingleton();
		auto lighting = handler->LookupForm(RE::FormID(0x300E2), "Skyrim.esm")->As<RE::BGSLightingTemplate>();
		if (!lighting)
			return;

		cell->SetFormEditorID("PluginExplorerCELL");
		cell->fullName = "PluginExplorerCELL";
		cell->cellFlags.set(RE::TESObjectCELL::Flag::kIsInteriorCell);
		cell->lightingTemplate = lighting;
		cell->waterHeight = 0;

		auto factoryCONT = RE::IFormFactory::GetConcreteFormFactoryByType<RE::TESObjectCONT>();
		auto container = factoryCONT ? factoryCONT->Create() : nullptr;
		if (!container)
			return;

		container->SetFormEditorID("PluginExplorerCONT");
		container->fullName = "PluginExplorerContainer";
		container->boundData = { { 0, 0, 0 }, { 0, 0, 0 } };
	
		auto factoryREFR = RE::IFormFactory::GetConcreteFormFactoryByType<RE::TESObjectREFR>();
		_container = factoryREFR ? factoryREFR->Create() : nullptr;
		if (!_container)
			return;

		_container->formFlags |= RE::TESObjectREFR::RecordFlags::kPersistent;
		_container->data.objectReference = container;
		_container->SetParentCell(cell);
		_container->SetStartingPosition({ 0, 0, 0 });
	}

	bool PluginExplorer::OpenContainer(uint32_t a_index, RE::FormType a_type)
	{
		if (!_container || _container->IsActivationBlocked())
			return false;

		auto plugin = FindPlugin(a_index);
		if (!plugin) {
			logger::info("Could not find plugin ({})", plugin->GetName());
			return false;
		}

		_container->SetDisplayName(plugin->GetName(), true);

		auto inv = _container->GetInventory();
		for (auto& [obj, data] : inv) {
			auto& [count, entry] = data;
			if (count > 0 && entry) {
				_container->RemoveItem(obj, count, RE::ITEM_REMOVE_REASON::kRemove, nullptr, nullptr);
			}
		}

		for (auto& [form, name] : plugin->GetForms(a_type)) {
			auto bound = form ? form->As<RE::TESBoundObject>() : nullptr;
			if (bound && _container) {
				auto count = GetTypeCount(a_type);
				_container->AddObjectToContainer(bound, nullptr, count, nullptr);
			}
		}

		auto obj = Script::GetObject(_container, "ObjectReference", true);
		if (!obj) {
			logger::info("Could not obtain ObjectReference");
			return false;
		}

		Script::CallbackPtr callback;
		auto playerRef = RE::PlayerCharacter::GetSingleton()->AsReference();
		bool success = Script::DispatchMethodCall(obj, "Activate", callback, std::move(playerRef), true);
		if (!success) {
			logger::info("Could not dispatch `Activate` on ObjectReference");
			return false;
		}

		return true;
	}

	PluginExplorer::PluginInfo* PluginExplorer::FindPlugin(uint32_t a_index)
	{
		auto it = _plugins.find(a_index);
		if (it != _plugins.end()) {
			return &it->second;
		}

		return nullptr;
	}

	uint32_t PluginExplorer::GetCombinedIndex(const RE::TESFile* a_file)
	{
		return static_cast<uint32_t>(a_file->compileIndex + a_file->smallFileCompileIndex);
	}

	uint32_t PluginExplorer::GetTypeCount(RE::FormType a_type)
	{
		auto& count = Settings::PluginExplorer.Count;
		switch (a_type) {
		case RE::FormType::AlchemyItem:
			return count.Alchemy;
		case RE::FormType::Ammo:
			return count.Ammo;
		case RE::FormType::Armor:
			return count.Armor;
		case RE::FormType::Book:
			return count.Book;
		case RE::FormType::KeyMaster:
			return count.Key;
		case RE::FormType::Misc:
			return count.Misc;
		case RE::FormType::Note:
			return count.Note;
		case RE::FormType::Weapon:
			return count.Weapon;
		default:
			return 1;
		}
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
