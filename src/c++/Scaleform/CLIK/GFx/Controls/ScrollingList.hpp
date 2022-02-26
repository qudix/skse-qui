#pragma once

#include "Scaleform/CLIK/GFx/Controls/CoreList.hpp"

namespace CLIK
{
    namespace GFx
    {
        namespace Controls
        {
            class ScrollingList :
                public CoreList
            {
            private:
                using super = CoreList;

            public:
                ScrollingList() = default;
                ScrollingList(const ScrollingList&) = default;
                ScrollingList(ScrollingList&&) = default;
                using super::super;

                ScrollingList(const super& a_rhs) :
                    super(a_rhs)
                {}

                ScrollingList(super&& a_rhs) :
                    super(std::move(a_rhs))
                {}

                ~ScrollingList() = default;

                ScrollingList& operator=(const ScrollingList&) = default;
                ScrollingList& operator=(ScrollingList&&) = default;
                using super::operator=;

                ScrollingList& operator=(const super& a_rhs)
                {
                    super::operator=(a_rhs);
                    return *this;
                }

                ScrollingList& operator=(super&& a_rhs)
                {
                    super::operator=(std::move(a_rhs));
                    return *this;
                }

                Object ScrollBar() const { return GetObject("scrollBar"); }
                void ScrollBar(const Object& a_scrollBar) { SetObject("scrollBar", a_scrollBar); }

                double RowHeight() const { return GetNumber("rowHeight"); }
                void RowHeight(double a_rowHeight) { SetNumber("rowHeight", a_rowHeight); }

                double ScrollPosition() const { return GetNumber("scrollPosition"); }
                void ScrollPosition(double a_scrollPosition) { SetNumber("scrollPosition", a_scrollPosition); }

                double SelectedIndex() const { return GetNumber("selectedIndex"); }
                void SelectedIndex(double a_selectedIndex) { SetNumber("selectedIndex", a_selectedIndex); }

                bool Disabled() const { return GetBoolean("disabled"); }
                void Disabled(bool a_disabled) { SetBoolean("disabled", a_disabled); }

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

                double RowCount() const { return GetNumber("rowCount"); }
                void RowCount(double a_rowCount) { SetNumber("rowCount", a_rowCount); }

                void InvalidateData()
                {
                    [[maybe_unused]] const auto success =
                        Invoke("invalidateData");
                    assert(success);
                }

                //bool handleInput(InputDetails& a_details, Array& a_pathToFocus);

                double AvailableWidth() const { return GetNumber("availableWidth"); }

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
