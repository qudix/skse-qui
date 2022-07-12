#pragma once

#include "Scaleform/CLIK/GFx/Controls/CoreList.hpp"

namespace SF::CLIK::GFx::Controls
{
	class ScrollingList :
		public CoreList
	{
	private:
		using super = CoreList;

	public:
		using super::super;
		using super::operator=;

		ScrollingList() = default;
		ScrollingList(const ScrollingList&) = default;
		ScrollingList(ScrollingList&&) = default;
		ScrollingList(const super& a_rhs);
		ScrollingList(super&& a_rhs);

		~ScrollingList() = default;

		ScrollingList& operator=(const ScrollingList&) = default;
		ScrollingList& operator=(ScrollingList&&) = default;
		ScrollingList& operator=(const super& a_rhs);
		ScrollingList& operator=(super&& a_rhs);

	public:
		// Properties
		double AvailableWidth() const { return GetNumber("availableWidth"); }
		bool   Disabled() const { return GetBoolean("disabled"); }
		void   Disabled(bool a_value) { SetBoolean("disabled", a_value); }
		double RowCount() const { return GetNumber("rowCount"); }
		void   RowCount(double a_value) { SetNumber("rowCount", a_value); }
		double RowHeight() const { return GetNumber("rowHeight"); }
		void   RowHeight(double a_value) { SetNumber("rowHeight", a_value); }
		Object ScrollBar() const { return GetObject("scrollBar"); }
		void   ScrollBar(const Object& a_value) { SetObject("scrollBar", a_value); }
		double ScrollPosition() const { return GetNumber("scrollPosition"); }
		void   ScrollPosition(double a_value) { SetNumber("scrollPosition", a_value); }
		double SelectedIndex() const { return GetNumber("selectedIndex"); }
		void   SelectedIndex(double a_value) { SetNumber("selectedIndex", a_value); }

	public:
		// Methods
		void InvalidateData();
		void ScrollToIndex(double a_index);
		std::string ToString();
	};
}

#include "ScrollingList.inl"
