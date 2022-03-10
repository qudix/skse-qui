#pragma once

#include "General/Singleton.hpp"

namespace Core
{
	class LocaleStrings :
		public General::Singleton<LocaleStrings>
	{
		std::string unhandled{ "[Unhandled]" };

	public:	
		const std::string& FormType(RE::FormType a_type)
		{
			switch (a_type) {
				case RE::FormType::AlchemyItem:
					return formALCH;
				case RE::FormType::Ammo:
					return formAMMO;
				case RE::FormType::Armor:
					return formARMO;
				case RE::FormType::Book:
					return formBOOK;
				case RE::FormType::Ingredient:
					return formINGR;
				case RE::FormType::KeyMaster:
					return formKEYM;
				case RE::FormType::Misc:
					return formMISC;
				case RE::FormType::Note:
					return formNOTE;
				case RE::FormType::SoulGem:
					return formSLGM;
				case RE::FormType::Spell:
					return formSPEL;
				case RE::FormType::Weapon:
					return formWEAP;
				default:
					return unhandled;
			}
		}

	public:
		std::string formALCH{ "$QDX_QUI_FORM_ALCH" };
		std::string formAMMO{ "$QDX_QUI_FORM_AMMO" };
		std::string formARMO{ "$QDX_QUI_FORM_ARMO" };
		std::string formBOOK{ "$QDX_QUI_FORM_BOOK" };
		std::string formINGR{ "$QDX_QUI_FORM_INGR" };
		std::string formKEYM{ "$QDX_QUI_FORM_KEYM" };
		std::string formMISC{ "$QDX_QUI_FORM_MISC" };
		std::string formNOTE{ "$QDX_QUI_FORM_NOTE" };
		std::string formSLGM{ "$QDX_QUI_FORM_SLGM" };
		std::string formSPEL{ "$QDX_QUI_FORM_SPEL" };
		std::string formWEAP{ "$QDX_QUI_FORM_WEAP" };

		std::string plugPlugins{ "$QDX_QUI_PLUGINEXPLORER_PLUGINS" };
	};
}
