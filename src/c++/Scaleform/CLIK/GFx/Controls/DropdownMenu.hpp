#pragma once

#include "Scaleform/CLIK/GFx/Controls/Button.hpp"

namespace SF::CLIK::GFx::Controls
{
	class DropdownMenu :
		public Button
	{
		using super = Button;

	public:
		using super::super;
		using super::operator=;

		DropdownMenu() = default;
		DropdownMenu(const DropdownMenu&) = default;
		DropdownMenu(DropdownMenu&&) = default;
		DropdownMenu(const super& a_rhs);
		DropdownMenu(super&& a_rhs);

		~DropdownMenu() = default;

		DropdownMenu& operator=(const DropdownMenu&) = default;
		DropdownMenu& operator=(DropdownMenu&&) = default;
		DropdownMenu& operator=(const super& a_rhs);
		DropdownMenu& operator=(super&& a_rhs);

	public:
		// Properties
		Object      DataProvider() const { return GetObject("dataProvider"); }
		void        DataProvider(const Object& a_value) { SetObject("dataProvider", a_value); }
		Object      Dropdown() const { return GetObject("dropdown"); }
		void        Dropdown(const Object& a_value) { SetObject("dropdown", a_value); }
		Object      DropdownWidth() const { return GetObject("scrollBar"); }
		void        DropdownWidth(const Object& a_value) { SetObject("scrollBar", a_value); }
		Object      ItemRenderer() const { return GetObject("itemRenderer"); }
		void        ItemRenderer(const Object& a_value) { SetObject("itemRenderer", a_value); }
		std::string LabelField() const { return GetString("labelField"); }
		void        LabelField(std::string_view a_value) { SetString("labelField", a_value); }
		double      RowCount() const { return GetNumber("rowCount"); }
		void        RowCount(double a_value) { SetNumber("rowCount", a_value); }
		Object      ScrollBar() const { return GetObject("scrollBar"); }
		void        ScrollBar(const Object& a_value) { SetObject("scrollBar", a_value); }
		double      SelectedIndex() const { return GetNumber("selectedIndex"); }
		void        SelectedIndex(double a_value) { SetNumber("selectedIndex", a_value); }

	public:
		// Methods
		void        Close();
		void        InvalidateData();
		std::string ItemToLabel(Object& a_item);
		void        Open();
		void        RemoveMovieClip();
		void        SetSize(double a_width, double a_height);
		std::string ToString();
	};
}

#include "DropdownMenu.inl"
