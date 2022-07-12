#pragma once

#include "Scaleform/Array.hpp"
#include "Scaleform/CLIK/GFx/Core/UIComponent.hpp"

namespace SF::CLIK::GFx::Controls
{
	class CoreList :
		public Core::UIComponent
	{
	private:
		using super = Core::UIComponent;

	public:
		using super::super;
		using super::operator=;

		CoreList() = default;
		CoreList(const CoreList&) = default;
		CoreList(CoreList&&) = default;
		CoreList(const super& a_rhs);
		CoreList(super&& a_rhs);

		~CoreList() = default;

		CoreList& operator=(const CoreList&) = default;
		CoreList& operator=(CoreList&&) = default;
		CoreList& operator=(const super& a_rhs);
		CoreList& operator=(super&& a_rhs);

	public:
		double      AvailableWidth() const { return GetNumber("availableWidth"); }
		double      AvailableHeight() const { return GetNumber("availableHeight"); }
		Object      DataProvider() const { return GetObject("dataProvider"); }
		void        DataProvider(const Object& a_dataProvider) { SetObject("dataProvider", a_dataProvider); }
		std::string ItemRenderer() const { return GetString("itemRenderer"); }
		void        ItemRenderer(std::string_view a_itemRenderer) { SetString("itemRenderer", a_itemRenderer); }
		std::string LabelField() const { return GetString("labelField"); }
		void        LabelField(std::string_view a_labelField) { SetString("labelField", a_labelField); }
		std::string RendererInstanceName() const { return GetString("rendererInstanceName"); }
		void        RendererInstanceName(std::string_view a_rendererInstanceName) { SetString("rendererInstanceName", a_rendererInstanceName); }
		double      SelectedIndex() const { return GetNumber("selectedIndex"); }
		void        SelectedIndex(double a_selectedIndex) { SetNumber("selectedIndex", a_selectedIndex); }

	public:
		std::string ItemToLabel(Object& a_item);
		void        InvalidateData();
		void        ScrollToIndex(double a_index);
		void        SetRendererList(Array& a_value);
		std::string ToString();
	};
}

#include "CoreList.inl"
