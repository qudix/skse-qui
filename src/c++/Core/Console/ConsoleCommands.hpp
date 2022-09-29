#pragma once

namespace Core::ConsoleCommand
{
	class Clear
	{
	public:
		static constexpr const auto FUNC_NAME = "Clear";
		static constexpr const auto SHORT_NAME = "";
		static constexpr const auto HELP_STR = "\"Clear\"";

		static void Register();

	private:
		static bool Execute(
			const RE::SCRIPT_PARAMETER* a_paramInfo,
			RE::SCRIPT_FUNCTION::ScriptData* a_scriptData,
			RE::TESObjectREFR* a_thisObj,
			RE::TESObjectREFR* a_containingObj,
			RE::Script* a_scriptObj,
			RE::ScriptLocals* a_locals,
			double& a_result,
			uint32_t& a_opcodeOffsetPtr);
	};

	void Register();
}
