#include "Core/Core.hpp"

SKSE_PLUGIN_LOAD(const SKSE::LoadInterface* a_skse)
{
	SKSE::Init(a_skse);

	Core::Init();

	return true;
}
