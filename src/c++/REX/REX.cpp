#include "REX/REX.h"

namespace REX
{
	namespace TESFile
	{
		uint32_t GetCombinedIndex(const RE::TESFile* a_file)
		{
			return static_cast<uint32_t>(a_file->compileIndex + a_file->smallFileCompileIndex);
		}
	}

	namespace TESObjectREFR
	{
		bool ActivateRef(RE::TESObjectREFR* a_self, RE::TESObjectREFR* a_activator, std::uint8_t a_arg2, RE::TESBoundObject* a_object, std::int32_t a_count, bool a_defaultProcessingOnly)
		{
			using func_t = decltype(&TESObjectREFR::ActivateRef);
		#ifdef IS_SKYRIM_AE
			REL::Relocation<func_t> func{ REL::ID(19796) };
		#elif
			REL::Relocation<func_t> func{ REL::ID(19369) };
		#endif
			return func(a_self, a_activator, a_arg2, a_object, a_count, a_defaultProcessingOnly);
		}
	}
}
