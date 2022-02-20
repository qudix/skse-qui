#pragma once

namespace REX
{
	namespace TESFile
	{
		uint32_t GetCombinedIndex(const RE::TESFile* a_file);
	}

	namespace TESObjectREFR
	{
		bool ActivateRef(RE::TESObjectREFR* a_self, RE::TESObjectREFR* a_activator, std::uint8_t a_arg2, RE::TESBoundObject* a_object, std::int32_t a_count, bool a_defaultProcessingOnly);
	}
}
