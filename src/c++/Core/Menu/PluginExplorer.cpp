#include "Core/Menu/PluginExplorer.hpp"
#include "Core/Menu/PluginExplorerMenu.hpp"

#include "Core/Config.hpp"

#include "General/Skyrim.hpp"

namespace Core::Menu
{
	void PluginExplorer::PluginInfo::AddForm(RE::TESForm* a_form, RE::FormType a_type)
	{
		auto formName = a_form->GetName();
		if (!formName || !a_form->GetPlayable())
			return;

		auto formID = a_form->GetFormID();
		using Type = RE::FormType;
		switch (a_type) {
			case Type::AlchemyItem:
			case Type::Ammo:
			case Type::Armor:
			case Type::Ingredient:
			case Type::KeyMaster:
			case Type::Misc:
			case Type::Note:
			case Type::Scroll:
			case Type::SoulGem:
			case Type::Weapon:
				_forms[a_type].insert_or_assign(formID, formName);
				_count += 1;
				break;
			case Type::Book:
				{
					auto book = a_form->As<RE::TESObjectBOOK>();
					if (book && !book->TeachesSpell()) {
						_forms[a_type].insert_or_assign(formID, formName);
						_count += 1;
					}
					break;
				}
			case Type::Spell:
				{
					auto book = a_form->As<RE::TESObjectBOOK>();
					if (book && book->TeachesSpell()) {
						_forms[a_type].insert_or_assign(formID, formName);
						_count += 1;
					}
					break;
				}
			default:
				logger::warn("Unhandled FormType: {}", static_cast<int32_t>(a_type));
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

		auto& config = Config::Get();
		auto& exclude = config.PluginExplorer.Plugin.Enable;
		for (auto file : handler->files) {
			auto it = exclude.find(file->fileName);
			if (it != exclude.end()) {
				if (!it->second)
					continue;
			}

			if (file->compileIndex != 0xFF) {
				auto index = General::Skyrim::GetCombinedIndex(file);
				PluginInfo info{ file->fileName, index };
				_cache.insert({ file->fileName, index });
				_plugins.insert({ index, std::move(info) });
			}
		}

		AddForms(RE::FormType::AlchemyItem);
		AddForms(RE::FormType::Ammo);
		AddForms(RE::FormType::Armor);
		AddForms(RE::FormType::Book);
		AddForms(RE::FormType::Ingredient);
		AddForms(RE::FormType::KeyMaster);
		AddForms(RE::FormType::Misc);
		AddForms(RE::FormType::Note);
		AddForms(RE::FormType::Scroll);
		AddForms(RE::FormType::SoulGem);
		AddForms(RE::FormType::Spell);
		AddForms(RE::FormType::Weapon);

		InitContainer();
	}

	void PluginExplorer::InitContainer()
	{
		// TODO: Figure out how to access the container in an unloaded cell

		auto factoryCELL = RE::IFormFactory::GetConcreteFormFactoryByType<RE::TESObjectCELL>();
		_cell = factoryCELL ? factoryCELL->Create() : nullptr;
		if (!_cell) {
			logger::error("Failed to create cell");
			return;
		}

		auto handler = RE::TESDataHandler::GetSingleton();
		auto lighting = handler->LookupForm<RE::BGSLightingTemplate>(RE::FormID(0x300E2), "Skyrim.esm");
		if (!lighting) {
			logger::error("Failed to lookup default lighting template");
			return;
		}

		_cell->SetFormEditorID("QUIPluginExplorerCELL");
		_cell->fullName = "QUIPluginExplorerCELL";
		_cell->cellFlags.set(RE::TESObjectCELL::Flag::kIsInteriorCell);
		_cell->lightingTemplate = lighting;
		_cell->waterHeight = 0;

		auto factoryCONT = RE::IFormFactory::GetConcreteFormFactoryByType<RE::TESObjectCONT>();
		_container = factoryCONT ? factoryCONT->Create() : nullptr;
		if (!_container) {
			logger::error("Failed to create container");
			return;
		}

		_container->SetFormEditorID("QUIPluginExplorerCONT");
		_container->fullName = "QUIPluginExplorerContainer";
		_container->boundData = { { 0, 0, 0 }, { 0, 0, 0 } };
		//_container->SetModel("furniture/noble/noblechest01.nif"); // FOR TESTING ONLY!
	}

	void PluginExplorer::InitContainerRef()
	{
		auto factoryREFR = RE::IFormFactory::GetConcreteFormFactoryByType<RE::TESObjectREFR>();
		auto containerRef = factoryREFR ? factoryREFR->Create() : nullptr;
		if (!containerRef) {
			logger::error("Failed to create container reference");
			return;
		}

		auto player = RE::PlayerCharacter::GetSingleton();
		auto playerRef = player->GetObjectReference();
		containerRef->formFlags |= RE::TESForm::RecordFlags::kTemporary;
		containerRef->data.objectReference = _container;
		containerRef->extraList.SetOwner(playerRef);
		containerRef->SetParentCell(_cell);
		containerRef->SetStartingPosition({ 0, 0, 0 });
		_containerRef = containerRef->CreateRefHandle();
	}

	RE::TESObjectREFRPtr PluginExplorer::GetContainer()
	{
		auto ref = _containerRef.get();
		if (ref)
			return ref;

		InitContainerRef();
		return _containerRef.get();
	}

	bool PluginExplorer::OpenContainer(uint32_t a_index, RE::FormType a_type)
	{
		auto container = GetContainer();
		if (!container || container->IsActivationBlocked())
			return false;

		auto plugin = FindPlugin(a_index);
		if (!plugin) {
			logger::warn("Could not find plugin ({})", plugin->GetName());
			return false;
		}

		container->SetDisplayName(plugin->GetName(), true);

		auto inv = container->GetInventory();
		for (auto& [obj, data] : inv) {
			auto& [count, entry] = data;
			if (count > 0 && entry) {
				container->RemoveItem(obj, count, RE::ITEM_REMOVE_REASON::kRemove, nullptr, nullptr);
			}
		}

		for (auto& [formID, name] : plugin->GetForms(a_type)) {
			auto object = RE::TESForm::LookupByID(formID)->As<RE::TESBoundObject>();
			if (object && _container) {
				auto count = GetTypeCount(a_type);
				container->AddObjectToContainer(object, nullptr, count, nullptr);
			}
		}

		auto player = RE::PlayerCharacter::GetSingleton();
		auto playerRef = player->AsReference();
		bool success = General::Skyrim::ActivateRef(container.get(), playerRef, 0, nullptr, 0, false);
		if (!success) {
			logger::warn("Could not call `Activate` on ObjectReference");
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

	uint32_t PluginExplorer::GetTypeCount(RE::FormType a_type)
	{
		auto& config = Config::Get();
		auto& count = config.PluginExplorer.Count;
		switch (a_type) {
			case RE::FormType::AlchemyItem:
				return count.Alchemy;
			case RE::FormType::Ammo:
				return count.Ammo;
			case RE::FormType::Armor:
				return count.Armor;
			case RE::FormType::Book:
				return count.Book;
			case RE::FormType::Ingredient:
				return count.Ingredient;
			case RE::FormType::KeyMaster:
				return count.Key;
			case RE::FormType::Misc:
				return count.Misc;
			case RE::FormType::Note:
				return count.Note;
			case RE::FormType::Scroll:
				return count.Scroll;
			case RE::FormType::SoulGem:
				return count.Soul;
			case RE::FormType::Spell:
				return count.Spell;
			case RE::FormType::Weapon:
				return count.Weapon;
			default:
				return 1;
		}
	}

	void PluginExplorer::AddForms(RE::FormType a_type)
	{
		RE::FormType type = a_type;
		switch (a_type) {
			case RE::FormType::Spell:
				{
					type = RE::FormType::Book;
					break;
				}
		}

		auto handler = RE::TESDataHandler::GetSingleton();
		auto& items = handler->GetFormArray(type);
		for (auto form : items) {
			auto file = form->GetFile(0);
			if (!file || !(file->compileIndex < 0xFF))
				continue;

			auto it = _cache.find(file->fileName);
			if (it == _cache.end())
				continue;

			auto index = General::Skyrim::GetCombinedIndex(file);
			auto info = _plugins.find(index);
			if (info != _plugins.end()) {
				info->second.AddForm(form, a_type);
			}
		}
	}
}
