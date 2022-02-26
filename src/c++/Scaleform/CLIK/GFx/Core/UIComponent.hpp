#pragma once

#include "Scaleform/CLIK/MovieClip.hpp"

namespace CLIK
{
    namespace GFx
    {
        namespace Core
        {
            class UIComponent :
                public MovieClip
            {
            private:
                using super = MovieClip;

            public:
                UIComponent() = default;
                UIComponent(const UIComponent&) = default;
                UIComponent(UIComponent&&) = default;
                using super::super;

                UIComponent(const super& a_rhs) :
                    super(a_rhs)
                {}

                UIComponent(super&& a_rhs) :
                    super(std::move(a_rhs))
                {}

                ~UIComponent() = default;

                UIComponent& operator=(const UIComponent&) = default;
                UIComponent& operator=(UIComponent&&) = default;
                using super::operator=;

                UIComponent& operator=(const super& a_rhs)
                {
                    super::operator=(a_rhs);
                    return *this;
                }

                UIComponent& operator=(super&& a_rhs)
                {
                    super::operator=(std::move(a_rhs));
                    return *this;
                }

                bool Disabled() const { return GetBoolean("disabled"); }
                void Disabled(bool a_disabled) { SetBoolean("disabled", a_disabled); }

                bool Visible() const { return GetBoolean("visible"); }
                void Visible(bool a_visible) { SetBoolean("visible", a_visible); }

                double Width() const { return GetNumber("width"); }
                void Width(double a_width) { SetNumber("width", a_width); }

                double Height() const { return GetNumber("height"); }
                void Height(double a_height) { SetNumber("height", a_height); }

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

                double Focused() const { return GetNumber("focused"); }
                void Focused(double a_focused) { SetNumber("focused", a_focused); }

                bool DisplayFocus() const { return GetBoolean("displayFocus"); }
                void DisplayFocus(bool a_displayFocus) { SetBoolean("displayFocus", a_displayFocus); }

                //bool HandleInput(InputDetails& a_details, Array& a_pathToFocus);

                void Invalidate()
                {
                    [[maybe_unused]] const auto success =
                        Invoke("invalidate");
                    assert(success);
                }

                void ValidateNow()
                {
                    [[maybe_unused]] const auto success =
                        Invoke("validateNow");
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

                void DispatchEventToGame(Object& a_event)
                {
                    enum
                    {
                        kEvent,
                        kNumArgs
                    };

                    std::array<RE::GFxValue, kNumArgs> args;

                    args[kEvent] = a_event.GetInstance();
                    assert(args[kEvent].IsObject());

                    [[maybe_unused]] const auto success =
                        Invoke("dispatchEventToGame", nullptr, args.data(), args.size());
                    assert(success);
                }
            };
        }
    }
}
