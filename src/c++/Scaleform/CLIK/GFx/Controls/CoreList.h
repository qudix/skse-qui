#pragma once

#include "Scaleform/CLIK/GFx/Core/UIComponent.h"

namespace CLIK
{
	class Array;

	namespace GFx
	{
		namespace Controls
		{
			class CoreList :
				public Core::UIComponent
			{
			private:
				using super = Core::UIComponent;

			public:
				CoreList() = default;
				CoreList(const CoreList&) = default;
				CoreList(CoreList&&) = default;
				using super::super;

				CoreList(const super& a_rhs) :
					super(a_rhs)
				{}

				CoreList(super&& a_rhs) :
					super(std::move(a_rhs))
				{}

				~CoreList() = default;

				CoreList& operator=(const CoreList&) = default;
				CoreList& operator=(CoreList&&) = default;
				using super::operator=;

				CoreList& operator=(const super& a_rhs)
				{
					super::operator=(a_rhs);
					return *this;
				}

				CoreList& operator=(super&& a_rhs)
				{
					super::operator=(std::move(a_rhs));
					return *this;
				}

				std::string ItemRenderer() const { return GetString("itemRenderer"); }
				void ItemRenderer(std::string_view a_itemRenderer) { SetString("itemRenderer", a_itemRenderer); }

				Object DataProvider() const { return GetObject("dataProvider"); }
				void DataProvider(const Object& a_dataProvider) { SetObject("dataProvider", a_dataProvider); }

				double SelectedIndex() const { return GetNumber("selectedIndex"); }
				void SelectedIndex(double a_selectedIndex) { SetNumber("selectedIndex", a_selectedIndex); }

				void ScrollToIndex(double a_index)
				{
					enum
					{
						kIndex,
						kNumArgs
					};

					std::array<RE::GFxValue, kNumArgs> args;

					args[kIndex] = a_index;
					assert(args[kIndex].IsNumber());

					[[maybe_unused]] const auto success =
						Invoke("scrollToIndex", nullptr, args.data(), args.size());
					assert(success);
				}

				std::string LabelField() const { return GetString("labelField"); }
				void LabelField(std::string_view a_labelField) { SetString("labelField", a_labelField); }

				//Function& LabelFunction() const;
				//void LabelFunction(Function& a_labelFunction);

				std::string ItemToLabel(Object& a_item)
				{
					enum
					{
						kItem,
						kNumArgs
					};

					std::array<RE::GFxValue, kNumArgs> args;

					args[kItem] = a_item.GetInstance();
					assert(args[kItem].IsObject());

					RE::GFxValue str;
					[[maybe_unused]] const auto success =
						Invoke("itemToLabel", std::addressof(str), args.data(), args.size());
					assert(success);

					return str.GetString();
				}

				void InvalidateData()
				{
					[[maybe_unused]] const auto success =
						Invoke("invalidateData");
					assert(success);
				}

				double AvailableWidth() const { return GetNumber("availableWidth"); }

				double AvailableHeight() const { return GetNumber("availableHeight"); }

				void SetRendererList(Array& a_value)
				{
					enum
					{
						kValue,
						kNumArgs
					};

					std::array<RE::GFxValue, kNumArgs> args;

					args[kValue] = a_value.GetInstance();
					assert(args[kValue].IsArray());

					[[maybe_unused]] const auto success =
						Invoke("setRendererList", nullptr, args.data(), args.size());
					assert(success);
				}

				std::string RendererInstanceName() const { return GetString("rendererInstanceName"); }
				void RendererInstanceName(std::string_view a_rendererInstanceName) { SetString("rendererInstanceName", a_rendererInstanceName); }

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
	}
}
