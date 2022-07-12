#pragma once

#include "Scaleform/CLIK/GFx/Core/UIComponent.hpp"

namespace SF::CLIK::GFx::Controls
{
	class ButtonBar :
		public Core::UIComponent
	{
	private:
		using super = Core::UIComponent;

	public:
		using super::super;
		using super::operator=;

		ButtonBar() = default;
		ButtonBar(const ButtonBar&) = default;
		ButtonBar(ButtonBar&&) = default;
		ButtonBar(const super& a_rhs);
		ButtonBar(super&& a_rhs);

		~ButtonBar() = default;

		ButtonBar& operator=(const ButtonBar&) = default;
		ButtonBar& operator=(ButtonBar&&) = default;
		ButtonBar& operator=(const super& a_rhs);
		ButtonBar& operator=(super&& a_rhs);

	public:
		// Properties
		std::string AutoSize() { return GetString("autoSize"); }
		void        AutoSize(std::string_view a_value) { return SetString("autoSize", a_value); }
		double      ButtonWidth() { return GetNumber("buttonWidth"); }
		void        ButtonWidth(double a_value) { return SetNumber("buttonWidth", a_value); }
		Object      Data() { return GetObject("data"); }
		Object      DataProvider() { return GetObject("dataProvider"); }
		void        DataProvider(const Object& a_value) { return SetObject("dataProvider", a_value); }
		std::string Direction() { return GetString("direction"); }
		void        Direction(std::string_view a_value) { return SetString("direction", a_value); }
		bool        Disabled() { return GetBoolean("disabled"); }
		void        Disabled(bool a_value) { return SetBoolean("disabled", a_value); }
		std::string ItemRenderer() { return GetString("itemRenderer"); }
		void        ItemRenderer(std::string_view a_value) { return SetString("itemRenderer", std::move(a_value)); }
		std::string LabelField() { return GetString("labelField"); }
		void        LabelField(std::string_view a_value) { return SetString("labelField", a_value); }
		double      SelectedIndex() { return GetNumber("selectedIndex"); }
		void        SelectedIndex(double a_value) { return SetNumber("selectedIndex", a_value); }
		Object      SelectedItem() { return GetObject("selectedItem"); }
		double      Spacing() { return GetNumber("spacing"); }
		void        Spacing(double a_value) { return SetNumber("spacing", a_value); }

	public:
		// Methods
		void        InvalidateData();
		std::string ItemToLabel(Object a_item);
		std::string ToString();
	};
}

#include "ButtonBar.inl"
