#pragma once

namespace General::Skyrim
{
	inline uint32_t GetCombinedIndex(const RE::TESFile* a_file)
	{
		return static_cast<uint32_t>(a_file->compileIndex + a_file->smallFileCompileIndex);
	}

	inline bool ActivateRef(RE::TESObjectREFR* a_self, RE::TESObjectREFR* a_activator, uint8_t a_arg2, RE::TESBoundObject* a_object, int32_t a_count, bool a_defaultProcessingOnly)
	{
		using func_t = decltype(&ActivateRef);
		REL::Relocation<func_t> func{ RELOCATION_ID(19369, 19796) };
		return func(a_self, a_activator, a_arg2, a_object, a_count, a_defaultProcessingOnly);
	}
}
