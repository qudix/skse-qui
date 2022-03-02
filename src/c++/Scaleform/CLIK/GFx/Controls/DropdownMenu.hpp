#pragma once

#include "Scaleform/CLIK/GFx/Controls/Button.hpp"

namespace CLIK::GFx::Controls
{
	class DropdownMenu :
		public Button
	{
	private:
		using super = Button;

	public:
		DropdownMenu() = default;
		DropdownMenu(const DropdownMenu&) = default;
		DropdownMenu(DropdownMenu&&) = default;
		using super::super;

		DropdownMenu(const super& a_rhs) :
			super(a_rhs)
		{}

		DropdownMenu(super&& a_rhs) :
			super(std::move(a_rhs))
		{}

		~DropdownMenu() = default;

		DropdownMenu& operator=(const DropdownMenu&) = default;
		DropdownMenu& operator=(DropdownMenu&&) = default;
		using super::operator=;

		DropdownMenu& operator=(const super& a_rhs)
		{
			super::operator=(a_rhs);
			return *this;
		}

		DropdownMenu& operator=(super&& a_rhs)
		{
			super::operator=(std::move(a_rhs));
			return *this;
		}

		Object Dropdown() const { return GetObject("dropdown"); }
		void Dropdown(const Object& a_dropdown) { SetObject("dropdown", a_dropdown); }

		Object ItemRenderer() const { return GetObject("itemRenderer"); }
		void ItemRenderer(const Object& a_itemRenderer) { SetObject("itemRenderer", a_itemRenderer); }

		Object ScrollBar() const { return GetObject("scrollBar"); }
		void ScrollBar(const Object& a_scrollBar) { SetObject("scrollBar", a_scrollBar); }

		Object DropdownWidth() const { return GetObject("scrollBar"); }
		void DropdownWidth(const Object& a_dropdownWidth) { SetObject("scrollBar", a_dropdownWidth); }

		double RowCount() const { return GetNumber("rowCount"); }
		void RowCount(double a_rowCount) { SetNumber("rowCount", a_rowCount); }

		Object DataProvider() const { return GetObject("dataProvider"); }
		void DataProvider(const Object& a_dataProvider) { SetObject("dataProvider", a_dataProvider); }

		double SelectedIndex() const { return GetNumber("selectedIndex"); }
		void SelectedIndex(double a_selectedIndex) { SetNumber("selectedIndex", a_selectedIndex); }

		std::string LabelField() const { return GetString("labelField"); }
		void LabelField(std::string_view a_selectedIndex) { SetString("labelField", a_selectedIndex); }

		//Function LabelFunction() const;
		//void LabelFunction(const Function& a_labelFunction);

		std::string ItemToLabel(Object& a_item)
		{
			enum
			{
				kItem,
				kNumArgs
			};

			std::array<RE::GFxValue, kNumArgs> args;

			args[kItem] = a_item.GetInstance();

			RE::GFxValue str;
			[[maybe_unused]] const auto success =
				Invoke("itemToLabel", std::addressof(str), args.data(), args.size());
			assert(success);

			return str.GetString();
		}

		void Open()
		{
			[[maybe_unused]] const auto success =
				Invoke("open");
			assert(success);
		}

		void Close()
		{
			[[maybe_unused]] const auto success =
				Invoke("close");
			assert(success);
		}

		void InvalidateData()
		{
			[[maybe_unused]] const auto success =
				Invoke("invalidateData");
			assert(success);
		}

		void SetSize(double a_width, double a_height)
		{
			enum
			{
				kWidth,
				kHeight,
				kNumArgs
			};

			std::array<RE::GFxValue, kNumArgs> args;

			args[kWidth] = a_width;
			assert(args[kWidth].IsNumber());

			args[kHeight] = a_height;
			assert(args[kHeight].IsNumber());

			[[maybe_unused]] const auto success =
				Invoke("setSize", nullptr, args.data(), args.size());
			assert(success);
		}

		//bool HandleInput(InputDetails& a_details, Array& a_pathToFocus);

		void RemoveMovieClip()
		{
			[[maybe_unused]] const auto success =
				Invoke("removeMovieClip");
			assert(success);
		}

		std::string ToString()
		{
			RE::GFxValue str;
			[[maybe_unused]] const auto success =
				Invoke("toString", std::addressof(str));
			assert(success);
			return str.GetString();
		}
	};
}
